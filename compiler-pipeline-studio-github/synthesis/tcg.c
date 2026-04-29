/*
 * ============================================================
 *  tcg.c  —  Phase 6: Target Code Generation
 *  x86-64 AT&T Assembly from Optimised TAC
 *  Compiler Design Project | GEU
 *
 *  Pipeline position:
 *    lexer.l → parser.y → icg.c → opt.c → tcg.c (this file)
 *
 *  Integration in parser.y main():
 *    #include "tcg.h"
 *    ...
 *    opt_optimize(icg_ctx);          // Phase 5
 *    TCGCtx *tcg_ctx = tcg_init();   // Phase 6 — init
 *    tcg_generate(tcg_ctx, icg_ctx); //         — translate
 *    tcg_print(tcg_ctx);             //         — display
 *    tcg_write_file(tcg_ctx,"out.s");//         — save
 *    tcg_free(tcg_ctx);              //         — cleanup
 *    icg_free(icg_ctx);
 *
 *  TAC → Assembly mapping summary
 *  ─────────────────────────────────────────────────────────
 *  BeginFunc f      .globl f / f: / push %rbp / mov %rsp,%rbp
 *  EndFunc          leave / ret
 *  t = a op b       movq a,%rax / <op> b,%rax / movq %rax,t
 *  t = op a         movq a,%rax / <op> %rax / movq %rax,t
 *  t = a            movq a,%rax / movq %rax,t
 *  a = t            movq t,%rax / movq %rax,a
 *  t = a[i]         movq i,%rcx / movq a(,%rcx,8),%rax / ...
 *  a[i] = t         movq t,%rax / movq i,%rcx / movq %rax,a(,%rcx,8)
 *  param a          pushq a  (first 6 args via regs at call site)
 *  t = call f,n     re-order args into rdi/rsi/rdx/rcx/r8/r9 / call f
 *  ifFalse c Lx     movq c,%rax / testq %rax,%rax / je Lx
 *  goto Lx          jmp Lx
 *  Lx:              Lx:
 *  return t         movq t,%rax / leave / ret
 *  return           xorq %rax,%rax / leave / ret
 *
 *  Register allocation strategy: Naive — all temporaries and
 *  user variables live on the stack (spill-everything).
 *  Each function gets a frame sized to hold all its local
 *  names.  A future improvement would add a proper register
 *  allocator (e.g. linear scan or graph colouring).
 *
 *  Colour macros are guarded so this file can be compiled
 *  stand-alone or #included after icg.c.
 * ============================================================
 */

/* ── include icg.h for ICGCtx opaque type ───────────────── */
#include "tcg.h"
#include "icg.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>

/* ── colour macros (guarded) ─────────────────────────────── */
#ifndef C_RESET
#define C_RESET   "\033[0m"
#define C_BOLD    "\033[1m"
#define C_RED     "\033[1;31m"
#define C_GREEN   "\033[0;32m"
#define C_YELLOW  "\033[0;33m"
#define C_BLUE    "\033[1;34m"
#define C_MAGENTA "\033[0;35m"
#define C_CYAN    "\033[1;36m"
#define C_GRAY    "\033[0;90m"
#define C_WHITE   "\033[0;37m"
#endif

/* ══════════════════════════════════════════════════════════
 *  INTERNAL: Access to ICGCtx internals
 *  icg.c defines ICGCtx and TACInstr as internal structs.
 *  tcg.c is compiled as part of the same translation unit
 *  (included from icg.c just like opt.c), so the types are
 *  visible directly. If compiling separately, promote the
 *  structs to icg.h and remove the definitions below.
 * ══════════════════════════════════════════════════════════*/

/* ── forward-declare the internal TAC types (already defined
      by icg.c when this file is #included from it)         */
#ifndef TAC_KINDS_DEFINED
#define TAC_KINDS_DEFINED
/* These mirror the TACKind / TACInstr in icg.c exactly.
   If compiling as a separate .o, move them to icg.h.       */
typedef enum {
    TAC_ASSIGN,
    TAC_BINOP,
    TAC_UNOP,
    TAC_COPY,
    TAC_ARR_LOAD,
    TAC_ARR_STORE,
    TAC_PARAM,
    TAC_CALL,
    TAC_LABEL,
    TAC_GOTO,
    TAC_IF_FALSE,
    TAC_BEGIN_FUNC,
    TAC_END_FUNC,
    TAC_RETURN,
} TACKind;

typedef struct TACInstr {
    TACKind  kind;
    char    *result;
    char    *arg1;
    char    *arg2;
    char    *op;
    int      n_args;
    struct TACInstr *next;
} TACInstr;

struct ICGCtx {
    TACInstr *head;
    TACInstr *tail;
    int       temp_cnt;
    int       label_cnt;
    int       instr_cnt;
};
#endif /* TAC_KINDS_DEFINED */

/* ══════════════════════════════════════════════════════════
 *  ASSEMBLY LINE BUFFER
 * ══════════════════════════════════════════════════════════*/
#define ASM_LINE_MAX  256
#define ASM_BUF_INIT  1024

typedef struct {
    char  *text;    /* null-terminated asm line */
    int    is_label;/* 1 = label (no indent in output) */
    int    is_comment;
    int    is_directive;
} AsmLine;

/* ══════════════════════════════════════════════════════════
 *  SYMBOL TABLE  (name → stack offset within current frame)
 * ══════════════════════════════════════════════════════════*/
#define SYM_MAX 512

typedef struct {
    char name[128];
    int  offset;    /* negative offset from %rbp, e.g. -8 */
} FrameSymEntry;

typedef struct {
    FrameSymEntry entries[SYM_MAX];
    int      count;
    int      next_offset;   /* next free slot (grows downward) */
} FrameSymTable;

static void sym_reset(FrameSymTable *st) {
    st->count       = 0;
    st->next_offset = 0;
}

/* Return stack offset for name; allocate new slot if needed */
static int sym_offset(FrameSymTable *st, const char *name) {
    for (int i = 0; i < st->count; i++)
        if (strcmp(st->entries[i].name, name) == 0)
            return st->entries[i].offset;
    /* new entry */
    if (st->count >= SYM_MAX) return -9999; /* overflow guard */
    st->next_offset -= 8;   /* one 64-bit slot */
    strncpy(st->entries[st->count].name, name, 127);
    st->entries[st->count].offset = st->next_offset;
    st->count++;
    return st->next_offset;
}

/* Total frame size (aligned to 16 bytes for SysV ABI)       */
static int sym_frame_size(const FrameSymTable *st) {
    int sz = -(st->next_offset); /* positive */
    /* round up to multiple of 16 */
    return (sz + 15) & ~15;
}

/* ══════════════════════════════════════════════════════════
 *  TCG CONTEXT
 * ══════════════════════════════════════════════════════════*/
struct TCGCtx {
    AsmLine *lines;
    int      nlines;
    int      cap;
    int      instr_count;   /* assembly instructions emitted */
    FrameSymTable sym;
    /* param buffer: holds args before a CALL is seen        */
    char     param_buf[8][128];
    int      param_count;
    /* statistics */
    int      n_functions;
    int      n_labels;
    int      n_branches;
    int      n_calls;
};

/* ── allocate more line space ────────────────────────────── */
static void tcg_grow(TCGCtx *ctx) {
    ctx->cap *= 2;
    ctx->lines = (AsmLine*)realloc(ctx->lines,
                                   ctx->cap * sizeof(AsmLine));
}

/* ── append one raw assembly line ────────────────────────── */
static void emit_asm(TCGCtx *ctx,
                     const char *text,
                     int is_label,
                     int is_comment,
                     int is_directive)
{
    if (ctx->nlines >= ctx->cap) tcg_grow(ctx);
    AsmLine *l   = &ctx->lines[ctx->nlines++];
    l->text      = strdup(text);
    l->is_label  = is_label;
    l->is_comment= is_comment;
    l->is_directive = is_directive;
    if (!is_label && !is_comment && !is_directive)
        ctx->instr_count++;
}

/* Convenience wrappers ────────────────────────────────────── */
#define EMIT(s)         emit_asm(ctx, (s), 0, 0, 0)
#define EMIT_LABEL(s)   emit_asm(ctx, (s), 1, 0, 0)
#define EMIT_COMMENT(s) emit_asm(ctx, (s), 0, 1, 0)
#define EMIT_DIR(s)     emit_asm(ctx, (s), 0, 0, 1)

/* Formatted emit helpers */
static void emitf(TCGCtx *ctx, const char *fmt, ...) {
    char buf[ASM_LINE_MAX];
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(buf, sizeof(buf), fmt, ap);
    va_end(ap);
    EMIT(buf);
}
static void emitf_label(TCGCtx *ctx, const char *fmt, ...) {
    char buf[ASM_LINE_MAX];
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(buf, sizeof(buf), fmt, ap);
    va_end(ap);
    EMIT_LABEL(buf);
}
static void emitf_dir(TCGCtx *ctx, const char *fmt, ...) {
    char buf[ASM_LINE_MAX];
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(buf, sizeof(buf), fmt, ap);
    va_end(ap);
    EMIT_DIR(buf);
}
static void emitf_cmt(TCGCtx *ctx, const char *fmt, ...) {
    char buf[ASM_LINE_MAX];
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(buf, sizeof(buf), fmt, ap);
    va_end(ap);
    EMIT_COMMENT(buf);
}

/* ══════════════════════════════════════════════════════════
 *  OPERAND HELPERS
 * ══════════════════════════════════════════════════════════*/

/* true if string is a numeric literal */
static int tcg_is_num(const char *s) {
    if (!s || !*s) return 0;
    const char *p = s;
    if (*p == '-') p++;
    int dots = 0;
    while (*p) {
        if (*p == '.') { if (++dots > 1) return 0; }
        else if (!isdigit((unsigned char)*p)) return 0;
        p++;
    }
    return p > s + (*s == '-');
}

/* true if string is a string literal (starts with ") */
static int tcg_is_str_lit(const char *s) {
    return s && s[0] == '"';
}

/*
 * Translate a TAC operand name to an AT&T assembly source
 * operand string.  Rules:
 *   numeric literal  → $value   (immediate)
 *   string literal   → $.LC_str (data section label, added on demand)
 *   variable / temp  → -N(%rbp) (stack slot)
 */
static void tcg_operand(TCGCtx *ctx,
                        const char *name,
                        char *out, int out_sz)
{
    if (!name || !*name) { snprintf(out, out_sz, "$0"); return; }

    if (tcg_is_num(name)) {
        /* immediate integer; floats need xmm — simplified to int here */
        long long iv = (long long)atof(name);
        snprintf(out, out_sz, "$%lld", iv);
        return;
    }

    if (tcg_is_str_lit(name)) {
        /* string literals → .rodata label (stubbed as $0 for simplicity) */
        snprintf(out, out_sz, "$0  /* str */");
        return;
    }

    /* variable or temp → stack slot */
    int off = sym_offset(&ctx->sym, name);
    snprintf(out, out_sz, "%d(%%rbp)", off);
}

/*
 * Load operand `name` into register `reg` (e.g. "%rax").
 * Emits one movq instruction.
 */
static void load_to_reg(TCGCtx *ctx,
                        const char *name,
                        const char *reg)
{
    char src[ASM_LINE_MAX];
    tcg_operand(ctx, name, src, sizeof(src));
    emitf(ctx, "    movq  %s, %s", src, reg);
}

/*
 * Store register `reg` into stack slot for `name`.
 * Emits one movq instruction.
 */
static void store_from_reg(TCGCtx *ctx,
                           const char *name,
                           const char *reg)
{
    int off = sym_offset(&ctx->sym, name);
    emitf(ctx, "    movq  %s, %d(%%rbp)", reg, off);
}

/* ══════════════════════════════════════════════════════════
 *  BINARY OPERATOR → x86-64 mnemonic
 * ══════════════════════════════════════════════════════════*/
/*
 * For a BINOP  result = arg1 op arg2:
 *
 *   movq  arg1, %rax
 *   movq  arg2, %rcx
 *   <op>  %rcx, %rax      (result in %rax)
 *   movq  %rax, result
 *
 * Comparisons use cmpq + setcc → movzbq to %rax.
 * Division uses idivq with %rdx:%rax.
 */
static void emit_binop(TCGCtx *ctx,
                       const char *result,
                       const char *arg1,
                       const char *arg2,
                       const char *op)
{
    emitf_cmt(ctx, "    # %s = %s %s %s", result, arg1, op, arg2);
    load_to_reg(ctx, arg1, "%rax");

    /* ── Comparison operators ─────────────────────────── */
    if (strcmp(op, "==") == 0 || strcmp(op, "!=") == 0 ||
        strcmp(op, "<")  == 0 || strcmp(op, ">")  == 0 ||
        strcmp(op, "<=") == 0 || strcmp(op, ">=") == 0)
    {
        load_to_reg(ctx, arg2, "%rcx");
        EMIT("    cmpq  %rcx, %rax");
        const char *setcc;
        if      (strcmp(op, "==") == 0) setcc = "sete";
        else if (strcmp(op, "!=") == 0) setcc = "setne";
        else if (strcmp(op, "<")  == 0) setcc = "setl";
        else if (strcmp(op, ">")  == 0) setcc = "setg";
        else if (strcmp(op, "<=") == 0) setcc = "setle";
        else                            setcc = "setge";
        emitf(ctx, "    %s  %%al", setcc);
        EMIT("    movzbq %al, %rax");
        store_from_reg(ctx, result, "%rax");
        return;
    }

    /* ── Division / Modulo ───────────────────────────── */
    if (strcmp(op, "/") == 0 || strcmp(op, "%") == 0) {
        EMIT("    cqto");                    /* sign-extend rax → rdx:rax */
        load_to_reg(ctx, arg2, "%rcx");
        EMIT("    idivq %rcx");
        /* quotient in %rax, remainder in %rdx */
        const char *src_reg = (strcmp(op, "/") == 0) ? "%rax" : "%rdx";
        store_from_reg(ctx, result, src_reg);
        return;
    }

    /* ── Logical && / || (short-circuit simplified) ─── */
    if (strcmp(op, "&&") == 0) {
        EMIT("    testq %rax, %rax");
        EMIT("    setne %al");
        EMIT("    movzbq %al, %rax");
        load_to_reg(ctx, arg2, "%rcx");
        EMIT("    testq %rcx, %rcx");
        EMIT("    setne %cl");
        EMIT("    movzbq %cl, %rcx");
        EMIT("    andq  %rcx, %rax");
        store_from_reg(ctx, result, "%rax");
        return;
    }
    if (strcmp(op, "||") == 0) {
        EMIT("    testq %rax, %rax");
        EMIT("    setne %al");
        EMIT("    movzbq %al, %rax");
        load_to_reg(ctx, arg2, "%rcx");
        EMIT("    testq %rcx, %rcx");
        EMIT("    setne %cl");
        EMIT("    movzbq %cl, %rcx");
        EMIT("    orq   %rcx, %rax");
        store_from_reg(ctx, result, "%rax");
        return;
    }

    /* ── Arithmetic / Bitwise ────────────────────────── */
    load_to_reg(ctx, arg2, "%rcx");
    const char *mnemonic = NULL;
    if      (strcmp(op, "+")  == 0) mnemonic = "addq";
    else if (strcmp(op, "-")  == 0) mnemonic = "subq";
    else if (strcmp(op, "*")  == 0) mnemonic = "imulq";
    else if (strcmp(op, "&")  == 0) mnemonic = "andq";
    else if (strcmp(op, "|")  == 0) mnemonic = "orq";
    else if (strcmp(op, "^")  == 0) mnemonic = "xorq";
    else if (strcmp(op, "<<") == 0) {
        /* shift amount must be in %cl */
        EMIT("    movq  %rcx, %rdx");
        EMIT("    movq  %rdx, %rcx");
        EMIT("    shlq  %cl, %rax");
        store_from_reg(ctx, result, "%rax");
        return;
    }
    else if (strcmp(op, ">>") == 0) {
        EMIT("    movq  %rcx, %rdx");
        EMIT("    movq  %rdx, %rcx");
        EMIT("    sarq  %cl, %rax");
        store_from_reg(ctx, result, "%rax");
        return;
    }

    if (mnemonic) {
        emitf(ctx, "    %s  %%rcx, %%rax", mnemonic);
    } else {
        emitf_cmt(ctx, "    # UNSUPPORTED OP: %s", op);
        EMIT("    nop");
    }
    store_from_reg(ctx, result, "%rax");
}

/* ══════════════════════════════════════════════════════════
 *  UNARY OPERATOR
 * ══════════════════════════════════════════════════════════*/
static void emit_unop(TCGCtx *ctx,
                      const char *result,
                      const char *arg1,
                      const char *op)
{
    emitf_cmt(ctx, "    # %s = %s %s", result, op, arg1);
    load_to_reg(ctx, arg1, "%rax");

    if (strcmp(op, "u-") == 0 || strcmp(op, "-") == 0) {
        EMIT("    negq  %rax");
    } else if (strcmp(op, "!") == 0) {
        EMIT("    testq %rax, %rax");
        EMIT("    sete  %al");
        EMIT("    movzbq %al, %rax");
    } else if (strcmp(op, "~") == 0) {
        EMIT("    notq  %rax");
    } else if (strcmp(op, "pre++") == 0) {
        EMIT("    incq  %rax");
        store_from_reg(ctx, arg1, "%rax"); /* side-effect on arg */
    } else if (strcmp(op, "pre--") == 0) {
        EMIT("    decq  %rax");
        store_from_reg(ctx, arg1, "%rax");
    } else if (strcmp(op, "post++") == 0) {
        /* result = old value; then increment */
        store_from_reg(ctx, result, "%rax");
        EMIT("    incq  %rax");
        store_from_reg(ctx, arg1, "%rax");
        return;
    } else if (strcmp(op, "post--") == 0) {
        store_from_reg(ctx, result, "%rax");
        EMIT("    decq  %rax");
        store_from_reg(ctx, arg1, "%rax");
        return;
    } else if (strcmp(op, "addr") == 0) {
        /* address-of: lea slot, %rax */
        int off = sym_offset(&ctx->sym, arg1);
        emitf(ctx, "    leaq  %d(%%rbp), %%rax", off);
    } else if (strcmp(op, "deref") == 0) {
        /* dereference pointer in rax */
        EMIT("    movq  (%rax), %rax");
    } else if (strcmp(op, "u+") == 0) {
        /* unary plus — no-op */
    } else if (strcmp(op, "sizeof") == 0) {
        EMIT("    movq  $8, %rax");   /* simplified: always 8 bytes */
    } else {
        emitf_cmt(ctx, "    # UNSUPPORTED UNOP: %s", op);
        EMIT("    nop");
    }
    store_from_reg(ctx, result, "%rax");
}

/* ══════════════════════════════════════════════════════════
 *  SysV AMD64 argument registers (first 6 integer args)
 * ══════════════════════════════════════════════════════════*/
static const char *ARG_REGS[6] = {
    "%rdi", "%rsi", "%rdx", "%rcx", "%r8", "%r9"
};

/* ══════════════════════════════════════════════════════════
 *  PASS 1: PRE-SCAN — collect all names inside one function
 *  so the frame can be sized before emitting prologue.
 * ══════════════════════════════════════════════════════════*/
static void prescan_function(const ICGCtx *icg_ctx,
                              const TACInstr *begin,
                              FrameSymTable *st)
{
    sym_reset(st);
    #define TOUCH(nm) do { if ((nm) && !tcg_is_num(nm) && !tcg_is_str_lit(nm) \
                               && strcmp((nm),"?"    )!=0 \
                               && strcmp((nm),"BREAK"  )!=0 \
                               && strcmp((nm),"CONTINUE")!=0 \
                               && (nm)[0]!='L') \
                           sym_offset(st, (nm)); } while(0)
    for (const TACInstr *ins = begin; ins; ins = ins->next) {
        if (ins->kind == TAC_END_FUNC) break;
        TOUCH(ins->result);
        TOUCH(ins->arg1);
        TOUCH(ins->arg2);
    }
    #undef TOUCH
}

/* ══════════════════════════════════════════════════════════
 *  MAIN TRANSLATION — one TAC instruction at a time
 * ══════════════════════════════════════════════════════════*/
static void tcg_translate(TCGCtx *ctx, const ICGCtx *icg_ctx)
{
    /* Emit .data section placeholder */
    EMIT_DIR(".section .data");
    EMIT_DIR(".section .text");
    EMIT_DIR("");

    const char *arg_regs[6] = {
        "%rdi", "%rsi", "%rdx", "%rcx", "%r8", "%r9"
    };

    for (const TACInstr *ins = icg_ctx->head; ins; ins = ins->next) {

        switch (ins->kind) {

        /* ── BeginFunc ─────────────────────────────────── */
        case TAC_BEGIN_FUNC: {
            const char *fname = ins->result ? ins->result : "unknown";
            ctx->n_functions++;

            /* Pre-scan to build symbol table for this function */
            prescan_function(icg_ctx, ins->next, &ctx->sym);
            int frame_sz = sym_frame_size(&ctx->sym);
            /* ensure minimum 16-byte alignment */
            if (frame_sz < 16) frame_sz = 16;

            emitf_cmt(ctx, "# ─────────────────────────────────────────");
            emitf_cmt(ctx, "# Function: %s  (frame = %d bytes)", fname, frame_sz);
            emitf_cmt(ctx, "# ─────────────────────────────────────────");
            emitf_dir(ctx, "    .globl %s", fname);
            emitf_dir(ctx, "    .type  %s, @function", fname);
            emitf_label(ctx, "%s:", fname);
            /* prologue */
            EMIT("    pushq %rbp");
            EMIT("    movq  %rsp, %rbp");
            emitf(ctx,  "    subq  $%d, %%rsp", frame_sz);

            /* Spill incoming parameters from arg registers to stack.
               We approximate: assume up to 6 params in registers. */
            emitf_cmt(ctx, "    # spill incoming args (if any)");

            /* Reset param counter for next function */
            ctx->param_count = 0;
            break;
        }

        /* ── EndFunc ───────────────────────────────────── */
        case TAC_END_FUNC: {
            const char *fname = ins->result ? ins->result : "?";
            emitf_cmt(ctx, "    # epilogue — %s", fname);
            EMIT("    leave");
            EMIT("    ret");
            emitf_dir(ctx, "    .size %s, .-%s", fname, fname);
            EMIT_DIR("");
            sym_reset(&ctx->sym);
            break;
        }

        /* ── Label ─────────────────────────────────────── */
        case TAC_LABEL: {
            ctx->n_labels++;
            emitf_label(ctx, "%s:", ins->result ? ins->result : "?");
            break;
        }

        /* ── Goto ──────────────────────────────────────── */
        case TAC_GOTO: {
            ctx->n_branches++;
            const char *target = ins->result ? ins->result : "?";
            if (strcmp(target, "BREAK") == 0 ||
                strcmp(target, "CONTINUE") == 0) {
                emitf_cmt(ctx, "    # %s (placeholder — no loop context)",
                          target);
                EMIT("    nop");
            } else {
                emitf(ctx, "    jmp   %s", target);
            }
            break;
        }

        /* ── ifFalse cond goto Lx ───────────────────────── */
        case TAC_IF_FALSE: {
            ctx->n_branches++;
            const char *cond   = ins->arg1   ? ins->arg1   : "?";
            const char *target = ins->result ? ins->result : "?";
            emitf_cmt(ctx, "    # ifFalse %s goto %s", cond, target);
            load_to_reg(ctx, cond, "%rax");
            EMIT("    testq %rax, %rax");
            emitf(ctx, "    je    %s", target);
            break;
        }

        /* ── Assign:  dest = src ───────────────────────── */
        case TAC_ASSIGN:
        case TAC_COPY: {
            const char *dst = ins->result ? ins->result : "?";
            const char *src = ins->arg1   ? ins->arg1   : "?";
            emitf_cmt(ctx, "    # %s = %s", dst, src);
            load_to_reg(ctx, src, "%rax");
            store_from_reg(ctx, dst, "%rax");
            break;
        }

        /* ── Binary op ─────────────────────────────────── */
        case TAC_BINOP: {
            emit_binop(ctx,
                       ins->result ? ins->result : "?",
                       ins->arg1   ? ins->arg1   : "0",
                       ins->arg2   ? ins->arg2   : "0",
                       ins->op     ? ins->op     : "+");
            break;
        }

        /* ── Unary op ───────────────────────────────────── */
        case TAC_UNOP: {
            emit_unop(ctx,
                      ins->result ? ins->result : "?",
                      ins->arg1   ? ins->arg1   : "0",
                      ins->op     ? ins->op     : "u+");
            break;
        }

        /* ── Array load:  result = base[idx] ───────────── */
        case TAC_ARR_LOAD: {
            const char *result = ins->result ? ins->result : "?";
            const char *base   = ins->arg1   ? ins->arg1   : "?";
            const char *idx    = ins->arg2   ? ins->arg2   : "0";
            emitf_cmt(ctx, "    # %s = %s[%s]", result, base, idx);
            /* load base address */
            int base_off = sym_offset(&ctx->sym, base);
            emitf(ctx, "    leaq  %d(%%rbp), %%rax", base_off);
            /* load index */
            load_to_reg(ctx, idx, "%rcx");
            /* element = *(base + idx*8) */
            EMIT("    movq  (%rax,%rcx,8), %rax");
            store_from_reg(ctx, result, "%rax");
            break;
        }

        /* ── Array store:  base[idx] = src ─────────────── */
        case TAC_ARR_STORE: {
            const char *base = ins->result ? ins->result : "?";
            const char *src  = ins->arg1   ? ins->arg1   : "0";
            const char *idx  = ins->arg2   ? ins->arg2   : "0";
            emitf_cmt(ctx, "    # %s[%s] = %s", base, idx, src);
            load_to_reg(ctx, src, "%rax");
            load_to_reg(ctx, idx, "%rcx");
            int base_off = sym_offset(&ctx->sym, base);
            emitf(ctx, "    leaq  %d(%%rbp), %%rdx", base_off);
            EMIT("    movq  %rax, (%rdx,%rcx,8)");
            break;
        }

        /* ── Param: buffer argument before call ─────────── */
        case TAC_PARAM: {
            const char *arg = ins->arg1 ? ins->arg1 : "0";
            emitf_cmt(ctx, "    # param %s", arg);
            if (ctx->param_count < 8) {
                strncpy(ctx->param_buf[ctx->param_count], arg, 127);
                ctx->param_count++;
            }
            /* extra args would be pushed right-to-left; simplified here */
            break;
        }

        /* ── Call ───────────────────────────────────────── */
        case TAC_CALL: {
            const char *fname = ins->arg1 ? ins->arg1 : "?";
            int n = ins->n_args;
            ctx->n_calls++;
            emitf_cmt(ctx, "    # call %s, %d arg(s)", fname, n);

            /* Load buffered params into SysV arg registers */
            int reg_args = n < 6 ? n : 6;
            for (int i = 0; i < reg_args && i < ctx->param_count; i++) {
                load_to_reg(ctx, ctx->param_buf[i], arg_regs[i]);
            }
            /* Extra args (7+): push right-to-left (simplified stub) */
            if (n > 6) {
                emitf_cmt(ctx, "    # NOTE: %d extra args on stack (stub)", n - 6);
            }

            emitf(ctx, "    call  %s", fname);

            /* If result temp expected, store %rax */
            if (ins->result) {
                store_from_reg(ctx, ins->result, "%rax");
            }

            /* Clean up: no callee stack cleanup needed for reg args */
            ctx->param_count = 0;
            break;
        }

        /* ── Return ─────────────────────────────────────── */
        case TAC_RETURN: {
            if (ins->arg1) {
                emitf_cmt(ctx, "    # return %s", ins->arg1);
                load_to_reg(ctx, ins->arg1, "%rax");
            } else {
                emitf_cmt(ctx, "    # return (void)");
                EMIT("    xorq  %rax, %rax");
            }
            EMIT("    leave");
            EMIT("    ret");
            break;
        }

        } /* end switch */
    }
}

/* ══════════════════════════════════════════════════════════
 *  PUBLIC API IMPLEMENTATION
 * ══════════════════════════════════════════════════════════*/

TCGCtx *tcg_init(void)
{
    TCGCtx *ctx = (TCGCtx*)calloc(1, sizeof(TCGCtx));
    ctx->cap   = ASM_BUF_INIT;
    ctx->lines = (AsmLine*)malloc(ctx->cap * sizeof(AsmLine));
    sym_reset(&ctx->sym);
    return ctx;
}

void tcg_generate(TCGCtx *ctx, const ICGCtx *icg_ctx)
{
    if (!ctx || !icg_ctx) return;
    tcg_translate(ctx, icg_ctx);
}

/* ── pretty printer ──────────────────────────────────────── */
void tcg_print(const TCGCtx *ctx)
{
    if (!ctx) return;

    printf("\n" C_BOLD C_CYAN
           "  ══════════════════════════════════════════════════════════\n"
           "  PHASE 6 — TARGET CODE GENERATION  (x86-64 AT&T Assembly)\n"
           "  ══════════════════════════════════════════════════════════\n"
           C_RESET);

    printf(C_GRAY
           "  Functions : %d  |  Labels : %d  |  Branches : %d"
           "  |  Calls : %d  |  Instructions : %d\n\n"
           C_RESET,
           ctx->n_functions, ctx->n_labels,
           ctx->n_branches,  ctx->n_calls,
           ctx->instr_count);

    int line_no = 1;
    for (int i = 0; i < ctx->nlines; i++) {
        AsmLine *l = &ctx->lines[i];

        if (l->is_comment) {
            printf(C_GRAY "       %s\n" C_RESET, l->text);
        } else if (l->is_directive) {
            if (l->text[0] == '\0') { printf("\n"); continue; }
            printf(C_YELLOW "       %s\n" C_RESET, l->text);
        } else if (l->is_label) {
            printf(C_GREEN "\n  %s\n" C_RESET, l->text);
        } else {
            printf(C_GRAY "  %3d  " C_RESET
                   C_WHITE "%s\n" C_RESET,
                   line_no++, l->text);
        }
    }
    printf("\n");
}

/* ── write plain assembly to file ────────────────────────── */
void tcg_write_file(const TCGCtx *ctx, const char *path)
{
    if (!ctx || !path) return;
    FILE *fp = fopen(path, "w");
    if (!fp) { perror("tcg_write_file"); return; }

    fprintf(fp, "# x86-64 AT&T Assembly — generated by tcg.c\n");
    fprintf(fp, "# Compiler Design Project | GEU\n");
    fprintf(fp, "# Assemble: gcc -no-pie %s -o <output>\n\n", path);

    for (int i = 0; i < ctx->nlines; i++) {
        AsmLine *l = &ctx->lines[i];
        if (l->is_label) {
            fprintf(fp, "%s\n", l->text);
        } else if (l->is_directive) {
            if (l->text[0] == '\0') { fprintf(fp, "\n"); continue; }
            fprintf(fp, "%s\n", l->text);
        } else {
            /* both real instructions and comments */
            fprintf(fp, "%s\n", l->text);
        }
    }
    fclose(fp);
    printf(C_GREEN "  Assembly written to: %s\n" C_RESET, path);
}

/* ── free ────────────────────────────────────────────────── */
void tcg_free(TCGCtx *ctx)
{
    if (!ctx) return;
    for (int i = 0; i < ctx->nlines; i++)
        free(ctx->lines[i].text);
    free(ctx->lines);
    free(ctx);
}
