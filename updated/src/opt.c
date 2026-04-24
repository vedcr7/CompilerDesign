/*
 * ============================================================
 *  opt.c  —  Phase 5: TAC Code Optimizer
 *  Compiler Design Project | GEU
 *
 *  Operates on the TACInstr linked-list produced by icg.c.
 *  Include AFTER icg.c (shares TACInstr / TACKind / ICGCtx).
 *
 *  Optimisation passes implemented
 *  ────────────────────────────────
 *  1. Constant Folding
 *       t0 = 3 + 4          →   t0 = 7
 *       t1 = 10 * 0         →   t1 = 0
 *       t2 = 6 / 2          →   t2 = 3
 *
 *  2. Constant Propagation
 *       t0 = 5
 *       t1 = t0 + x         →   t1 = 5 + x
 *
 *  3. Copy Propagation
 *       t0 = a
 *       t1 = t0 + b         →   t1 = a + b
 *
 *  4. Algebraic Identities
 *       x + 0 / 0 + x       →   x
 *       x * 1 / 1 * x       →   x
 *       x * 0 / 0 * x       →   0
 *       x - 0               →   x
 *       x / 1               →   x
 *       x - x               →   0
 *
 *  5. Dead Code Elimination
 *       Remove assignments whose result is never used again.
 *       Remove instructions after unconditional return/goto
 *       (within a function, before next label).
 *
 *  6. Common Subexpression Elimination (CSE)
 *       t0 = a + b
 *       ...  (no a or b redefined)
 *       t1 = a + b          →   t1 = t0   (reuse t0)
 *
 *  7. Unreachable-Code Elimination
 *       goto / return followed by non-label instructions
 *       → those instructions are removed.
 *
 *  Passes are run in a fixed-point loop until no changes occur.
 *  Each pass reports what it did for educational output.
 * ============================================================
 */

/* icg.c must be included before this file.
   It defines TACInstr, TACKind, ICGCtx.                      */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

/* ── colour macros (guarded; icg.c already defines them) ─── */
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

/* ════════════════════════════════════════════════════════════
 *  OPTIMIZER STATISTICS
 * ════════════════════════════════════════════════════════════*/
typedef struct {
    int const_fold;       /* constant folding hits      */
    int const_prop;       /* constant propagation hits  */
    int copy_prop;        /* copy propagation hits      */
    int algebraic;        /* algebraic identity hits    */
    int dead_code;        /* dead assignments removed   */
    int cse;              /* common subexpressions hit  */
    int unreachable;      /* unreachable instrs removed */
    int iterations;       /* fixed-point iterations     */
} OptStats;

/* ════════════════════════════════════════════════════════════
 *  HELPERS
 * ════════════════════════════════════════════════════════════*/

/* true if string is an integer literal (optional leading -) */
static int is_int_lit(const char *s)
{
    if (!s || !*s) return 0;
    const char *p = s;
    if (*p == '-') p++;
    if (!*p) return 0;
    while (*p) { if (!isdigit((unsigned char)*p)) return 0; p++; }
    return 1;
}

/* true if string is a numeric literal (int or float)        */
static int is_num_lit(const char *s)
{
    if (!s || !*s) return 0;
    const char *p = s;
    if (*p == '-') p++;
    int dots = 0;
    while (*p) {
        if (*p == '.') { dots++; if (dots > 1) return 0; }
        else if (!isdigit((unsigned char)*p)) return 0;
        p++;
    }
    return p != s + (*s == '-' ? 1 : 0);
}

static double num_val(const char *s) { return atof(s); }

/* replace a string field in-place */
static void str_set(char **field, const char *val)
{
    free(*field);
    *field = val ? strdup(val) : NULL;
}

/* does name look like a temp (t followed by digits)? */
static int is_temp(const char *s)
{
    if (!s || s[0] != 't') return 0;
    for (int i = 1; s[i]; i++)
        if (!isdigit((unsigned char)s[i])) return 0;
    return s[1] != '\0';
}

/* count instructions in list */
static int tac_count(const ICGCtx *ctx)
{
    int n = 0;
    for (TACInstr *i = ctx->head; i; i = i->next) n++;
    return n;
}

/* ════════════════════════════════════════════════════════════
 *  PASS 1 — CONSTANT FOLDING
 *  If both operands of a BINOP are literals, evaluate now.
 * ════════════════════════════════════════════════════════════*/
static int pass_const_fold(ICGCtx *ctx, OptStats *st)
{
    int changed = 0;
    for (TACInstr *ins = ctx->head; ins; ins = ins->next) {
        if (ins->kind != TAC_BINOP) continue;
        if (!is_num_lit(ins->arg1) || !is_num_lit(ins->arg2)) continue;
        if (!ins->op) continue;

        double a = num_val(ins->arg1);
        double b = num_val(ins->arg2);
        double r = 0.0;
        int    valid = 1;
        int    is_int_result = is_int_lit(ins->arg1) && is_int_lit(ins->arg2);

        if      (strcmp(ins->op, "+")  == 0) r = a + b;
        else if (strcmp(ins->op, "-")  == 0) r = a - b;
        else if (strcmp(ins->op, "*")  == 0) r = a * b;
        else if (strcmp(ins->op, "/")  == 0) {
            if (b == 0.0) { valid = 0; } /* keep — semantic already warned */
            else r = a / b;
        }
        else if (strcmp(ins->op, "%")  == 0) {
            if ((long long)b == 0) { valid = 0; }
            else r = (double)((long long)a % (long long)b);
            is_int_result = 1;
        }
        else if (strcmp(ins->op, "<")  == 0) { r = (a <  b) ? 1 : 0; is_int_result=1; }
        else if (strcmp(ins->op, ">")  == 0) { r = (a >  b) ? 1 : 0; is_int_result=1; }
        else if (strcmp(ins->op, "<=") == 0) { r = (a <= b) ? 1 : 0; is_int_result=1; }
        else if (strcmp(ins->op, ">=") == 0) { r = (a >= b) ? 1 : 0; is_int_result=1; }
        else if (strcmp(ins->op, "==") == 0) { r = (a == b) ? 1 : 0; is_int_result=1; }
        else if (strcmp(ins->op, "!=") == 0) { r = (a != b) ? 1 : 0; is_int_result=1; }
        else valid = 0;

        if (!valid) continue;

        /* convert result → string and turn instr into COPY  */
        char buf[64];
        if (is_int_result) snprintf(buf, sizeof(buf), "%lld", (long long)r);
        else               snprintf(buf, sizeof(buf), "%g",   r);

        ins->kind = TAC_COPY;
        str_set(&ins->arg1, buf);
        str_set(&ins->arg2, NULL);
        str_set(&ins->op,   NULL);
        changed = 1;
        st->const_fold++;
    }
    return changed;
}

/* ════════════════════════════════════════════════════════════
 *  PASS 2 — CONSTANT / COPY PROPAGATION
 *  Track assignments of the form  t = literal  or  t = var.
 *  Replace later uses of t with the known value.
 *  Invalidate on any re-assignment or function call.
 * ════════════════════════════════════════════════════════════*/
#define MAX_VALS 256

typedef struct { char name[64]; char val[64]; } ValEntry;

static int pass_prop(ICGCtx *ctx, OptStats *st)
{
    int changed = 0;

    /* We do one forward pass per function (reset at BeginFunc) */
    ValEntry vals[MAX_VALS];
    int      vcnt = 0;

    /* lookup a known value */
    #define LOOKUP(nm) ({                                        \
        const char *_r = NULL;                                   \
        for (int _i = 0; _i < vcnt; _i++)                       \
            if (strcmp(vals[_i].name, (nm)) == 0)               \
                { _r = vals[_i].val; break; }                    \
        _r; })

    /* set / update a known value */
    #define RECORD(nm, vl) do {                                  \
        int _found = 0;                                          \
        for (int _i = 0; _i < vcnt; _i++)                       \
            if (strcmp(vals[_i].name, (nm)) == 0) {             \
                strncpy(vals[_i].val,(vl),63); _found=1; break; \
            }                                                    \
        if (!_found && vcnt < MAX_VALS) {                        \
            strncpy(vals[vcnt].name,(nm),63);                    \
            strncpy(vals[vcnt].val, (vl),63);                    \
            vcnt++;                                              \
        }                                                        \
    } while(0)

    /* kill a known value (e.g. on call or re-assign)           */
    #define KILL(nm) do {                                        \
        for (int _i = 0; _i < vcnt; _i++)                       \
            if (strcmp(vals[_i].name,(nm))==0) {                 \
                vals[_i] = vals[--vcnt]; break;                  \
            }                                                    \
    } while(0)

    /* try to substitute one operand pointer */
    #define TRY_SUBST(fld, stype) do {                           \
        if ((fld) && !is_num_lit(fld)) {                         \
            const char *_kv = LOOKUP(fld);                       \
            if (_kv) {                                           \
                str_set(&(fld), _kv);                            \
                changed = 1; (stype)++;                          \
            }                                                    \
        }                                                        \
    } while(0)

    for (TACInstr *ins = ctx->head; ins; ins = ins->next) {
        switch (ins->kind) {

        case TAC_BEGIN_FUNC:
            vcnt = 0;   /* fresh scope per function */
            break;

        case TAC_END_FUNC:
            vcnt = 0;
            break;

        /* propagate into operands first, then record result   */
        case TAC_BINOP:
            TRY_SUBST(ins->arg1, st->const_prop);
            TRY_SUBST(ins->arg2, st->const_prop);
            if (ins->result) KILL(ins->result);
            break;

        case TAC_UNOP:
            TRY_SUBST(ins->arg1, st->const_prop);
            if (ins->result) KILL(ins->result);
            break;

        case TAC_COPY:
        case TAC_ASSIGN: {
            TRY_SUBST(ins->arg1, st->copy_prop);
            /* record the new mapping                          */
            if (ins->result && ins->arg1) {
                if (is_num_lit(ins->arg1))
                    RECORD(ins->result, ins->arg1);
                else
                    RECORD(ins->result, ins->arg1);
            }
            break;
        }

        case TAC_ARR_LOAD:
            TRY_SUBST(ins->arg2, st->const_prop); /* index */
            if (ins->result) KILL(ins->result);
            break;

        case TAC_ARR_STORE:
            TRY_SUBST(ins->arg1, st->const_prop); /* value */
            TRY_SUBST(ins->arg2, st->const_prop); /* index */
            break;

        case TAC_PARAM:
            TRY_SUBST(ins->arg1, st->const_prop);
            break;

        case TAC_IF_FALSE:
            TRY_SUBST(ins->arg1, st->const_prop);
            break;

        case TAC_RETURN:
            TRY_SUBST(ins->arg1, st->const_prop);
            break;

        case TAC_CALL:
            /* calls may modify globals — conservatively kill all temps */
            vcnt = 0;
            if (ins->result) KILL(ins->result);
            break;

        case TAC_LABEL:
            /* a label is a join point; we can't trust values from
               one predecessor — conservatively flush                */
            vcnt = 0;
            break;

        default: break;
        }
    }

    #undef LOOKUP
    #undef RECORD
    #undef KILL
    #undef TRY_SUBST

    return changed;
}

/* ════════════════════════════════════════════════════════════
 *  PASS 3 — ALGEBRAIC IDENTITIES
 * ════════════════════════════════════════════════════════════*/
static int pass_algebraic(ICGCtx *ctx, OptStats *st)
{
    int changed = 0;
    for (TACInstr *ins = ctx->head; ins; ins = ins->next) {
        if (ins->kind != TAC_BINOP) continue;
        if (!ins->op || !ins->arg1 || !ins->arg2) continue;

        const char *op = ins->op;
        const char *a  = ins->arg1;
        const char *b  = ins->arg2;
        const char *replace = NULL;  /* set to the surviving operand */

        /* x + 0 or 0 + x → x */
        if (strcmp(op, "+") == 0) {
            if (is_num_lit(b) && num_val(b) == 0.0) replace = a;
            else if (is_num_lit(a) && num_val(a) == 0.0) replace = b;
        }
        /* x - 0 → x */
        else if (strcmp(op, "-") == 0) {
            if (is_num_lit(b) && num_val(b) == 0.0) replace = a;
            /* x - x → 0 */
            else if (strcmp(a, b) == 0 && !is_num_lit(a)) {
                ins->kind = TAC_COPY;
                str_set(&ins->arg1, "0");
                str_set(&ins->arg2, NULL);
                str_set(&ins->op,   NULL);
                changed = 1; st->algebraic++;
                continue;
            }
        }
        /* x * 1 or 1 * x → x */
        else if (strcmp(op, "*") == 0) {
            if (is_num_lit(b) && num_val(b) == 1.0) replace = a;
            else if (is_num_lit(a) && num_val(a) == 1.0) replace = b;
            /* x * 0 or 0 * x → 0 */
            else if (is_num_lit(b) && num_val(b) == 0.0) {
                ins->kind = TAC_COPY; str_set(&ins->arg1, "0");
                str_set(&ins->arg2, NULL); str_set(&ins->op, NULL);
                changed = 1; st->algebraic++; continue;
            }
            else if (is_num_lit(a) && num_val(a) == 0.0) {
                ins->kind = TAC_COPY; str_set(&ins->arg1, "0");
                str_set(&ins->arg2, NULL); str_set(&ins->op, NULL);
                changed = 1; st->algebraic++; continue;
            }
        }
        /* x / 1 → x */
        else if (strcmp(op, "/") == 0) {
            if (is_num_lit(b) && num_val(b) == 1.0) replace = a;
        }

        if (replace) {
            ins->kind = TAC_COPY;
            str_set(&ins->arg1, replace);
            str_set(&ins->arg2, NULL);
            str_set(&ins->op,   NULL);
            changed = 1; st->algebraic++;
        }
    }
    return changed;
}

/* ════════════════════════════════════════════════════════════
 *  PASS 4 — COMMON SUBEXPRESSION ELIMINATION (CSE)
 *  Within a straight-line sequence (no labels/calls between),
 *  if we see  t0 = a op b  and later  t1 = a op b  (same a,
 *  op, b and neither a nor b was redefined), replace with
 *  t1 = t0.
 * ════════════════════════════════════════════════════════════*/
#define MAX_CSE 128

typedef struct {
    char arg1[64];
    char arg2[64];
    char op[16];
    char result[64];
    int  valid;    /* set 0 when arg1 or arg2 is killed */
} CSEEntry;

static int pass_cse(ICGCtx *ctx, OptStats *st)
{
    int      changed = 0;
    CSEEntry tab[MAX_CSE];
    int      tcnt = 0;

    /* invalidate entries that use a given name */
    #define CSE_KILL(nm) do {                                    \
        for (int _i = 0; _i < tcnt; _i++) {                     \
            if (strcmp(tab[_i].arg1, (nm)) == 0 ||              \
                strcmp(tab[_i].arg2, (nm)) == 0 ||              \
                strcmp(tab[_i].result,(nm)) == 0)               \
                tab[_i].valid = 0;                               \
        }                                                        \
    } while(0)

    for (TACInstr *ins = ctx->head; ins; ins = ins->next) {

        if (ins->kind == TAC_BEGIN_FUNC ||
            ins->kind == TAC_END_FUNC   ||
            ins->kind == TAC_LABEL      ||
            ins->kind == TAC_CALL) {
            tcnt = 0;  /* flush on scope/join boundaries */
            continue;
        }

        if (ins->kind == TAC_BINOP && ins->arg1 && ins->arg2 && ins->op) {
            /* search table */
            int found = -1;
            for (int i = 0; i < tcnt; i++) {
                if (!tab[i].valid) continue;
                if (strcmp(tab[i].op,   ins->op)   == 0 &&
                    strcmp(tab[i].arg1, ins->arg1)  == 0 &&
                    strcmp(tab[i].arg2, ins->arg2)  == 0) {
                    found = i; break;
                }
                /* commutative operators */
                if ((strcmp(ins->op,"+") == 0 || strcmp(ins->op,"*") == 0 ||
                     strcmp(ins->op,"==")== 0 || strcmp(ins->op,"!=")== 0) &&
                    strcmp(tab[i].op,   ins->op)   == 0 &&
                    strcmp(tab[i].arg1, ins->arg2)  == 0 &&
                    strcmp(tab[i].arg2, ins->arg1)  == 0) {
                    found = i; break;
                }
            }

            if (found >= 0) {
                /* replace with copy of previously computed temp */
                ins->kind = TAC_COPY;
                str_set(&ins->arg1, tab[found].result);
                str_set(&ins->arg2, NULL);
                str_set(&ins->op,   NULL);
                changed = 1; st->cse++;
                if (ins->result) CSE_KILL(ins->result);
            } else {
                /* add to table */
                if (tcnt < MAX_CSE && ins->result) {
                    strncpy(tab[tcnt].arg1,   ins->arg1,  63);
                    strncpy(tab[tcnt].arg2,   ins->arg2,  63);
                    strncpy(tab[tcnt].op,     ins->op,    15);
                    strncpy(tab[tcnt].result, ins->result,63);
                    tab[tcnt].valid = 1;
                    tcnt++;
                }
                if (ins->result) CSE_KILL(ins->result);
            }
        } else {
            /* any write kills CSE entries that depend on the result */
            if (ins->result) CSE_KILL(ins->result);
        }
    }

    #undef CSE_KILL
    return changed;
}

/* ════════════════════════════════════════════════════════════
 *  PASS 5 — DEAD CODE ELIMINATION
 *
 *  (a) Unreachable instructions after goto/return (before
 *      the next label).
 *  (b) Assignments to temps that are never read again.
 *
 *  Uses a two-pass approach:
 *    forward:  mark unreachable
 *    backward: mark live/dead uses
 * ════════════════════════════════════════════════════════════*/

/* tag field reuse: we add a `dead` flag to each instruction
   by walking with a pointer array                            */

static int pass_dead_code(ICGCtx *ctx, OptStats *st)
{
    /* ── (a) unreachable after goto/return ─────────────── */
    int changed = 0;
    {
        int unreachable = 0;
        TACInstr *prev = NULL;
        TACInstr *ins  = ctx->head;
        while (ins) {
            if (unreachable && ins->kind != TAC_LABEL &&
                ins->kind != TAC_BEGIN_FUNC &&
                ins->kind != TAC_END_FUNC) {
                /* remove this instruction                   */
                TACInstr *next = ins->next;
                if (prev) prev->next = next;
                else       ctx->head = next;
                if (ins == ctx->tail) ctx->tail = prev;
                free(ins->result); free(ins->arg1);
                free(ins->arg2);   free(ins->op);
                free(ins);
                ins = next;
                changed = 1; st->unreachable++;
                continue;
            }
            if (ins->kind == TAC_GOTO || ins->kind == TAC_RETURN)
                unreachable = 1;
            else if (ins->kind == TAC_LABEL ||
                     ins->kind == TAC_BEGIN_FUNC)
                unreachable = 0;
            prev = ins;
            ins  = ins->next;
        }
    }

    /* ── (b) dead temp assignments ─────────────────────── */
    /*  Collect all instructions into an array for backward scan */
    int  n   = tac_count(ctx);
    if (n == 0) return changed;

    TACInstr **arr = (TACInstr**)malloc(n * sizeof(TACInstr*));
    {
        int i = 0;
        for (TACInstr *ins = ctx->head; ins; ins = ins->next)
            arr[i++] = ins;
    }

    /* live[i] = 1 if instruction i should be kept           */
    int *live = (int*)calloc(n, sizeof(int));

    /* backward pass: track which temps are "needed"         */
    /* use a simple set of needed names                       */
#define MAX_LIVE 512
    char needed[MAX_LIVE][64];
    int  ncnt = 0;

    #define NEED(nm) do {                                        \
        if ((nm) && !is_num_lit(nm)) {                           \
            int _f = 0;                                          \
            for (int _i=0;_i<ncnt;_i++)                         \
                if(strcmp(needed[_i],(nm))==0){_f=1;break;}     \
            if (!_f && ncnt < MAX_LIVE)                         \
                strncpy(needed[ncnt++],(nm),63);                 \
        }                                                        \
    } while(0)

    #define IS_NEEDED(nm) ({                                     \
        int _f = 0;                                              \
        if (nm) for(int _i=0;_i<ncnt;_i++)                      \
            if(strcmp(needed[_i],(nm))==0){_f=1;break;}         \
        _f; })

    #define DROP(nm) do {                                        \
        if (nm) for(int _i=0;_i<ncnt;_i++)                      \
            if(strcmp(needed[_i],(nm))==0){                      \
                strcpy(needed[_i],needed[--ncnt]); break; }      \
    } while(0)

    for (int i = n - 1; i >= 0; i--) {
        TACInstr *ins = arr[i];

        /* instructions that always live                     */
        if (ins->kind == TAC_BEGIN_FUNC || ins->kind == TAC_END_FUNC ||
            ins->kind == TAC_LABEL      || ins->kind == TAC_GOTO     ||
            ins->kind == TAC_IF_FALSE   || ins->kind == TAC_CALL     ||
            ins->kind == TAC_PARAM      || ins->kind == TAC_RETURN   ||
            ins->kind == TAC_ARR_STORE) {
            live[i] = 1;
            /* operands of these are needed                  */
            NEED(ins->arg1);
            NEED(ins->arg2);
            NEED(ins->result);
            continue;
        }

        /* for assignments/copies/binops/unops/arr_load:     */
        /* live if result is needed                          */
        if (ins->result && (IS_NEEDED(ins->result) || !is_temp(ins->result))) {
            live[i] = 1;
            DROP(ins->result);     /* defined here — remove from needed */
            NEED(ins->arg1);
            NEED(ins->arg2);
        } else if (ins->result && is_temp(ins->result) && !IS_NEEDED(ins->result)) {
            /* dead temp — will be removed                   */
            live[i] = 0;
        } else {
            live[i] = 1;
            NEED(ins->arg1);
            NEED(ins->arg2);
        }
    }

    /* rebuild list keeping only live instructions           */
    ctx->head = ctx->tail = NULL;
    ctx->instr_cnt = 0;
    for (int i = 0; i < n; i++) {
        TACInstr *ins = arr[i];
        if (!live[i] && ins->result && is_temp(ins->result)) {
            /* discard */
            free(ins->result); free(ins->arg1);
            free(ins->arg2);   free(ins->op);
            free(ins);
            changed = 1; st->dead_code++;
            continue;
        }
        ins->next = NULL;
        if (!ctx->head) ctx->head = ctx->tail = ins;
        else { ctx->tail->next = ins; ctx->tail = ins; }
        ctx->instr_cnt++;
    }

    #undef NEED
    #undef IS_NEEDED
    #undef DROP
    #undef MAX_LIVE
    free(arr);
    free(live);
    return changed;
}

/* ════════════════════════════════════════════════════════════
 *  MASTER OPTIMIZER
 *  Runs all passes in a fixed-point loop.
 * ════════════════════════════════════════════════════════════*/
static void opt_run(ICGCtx *ctx, OptStats *st)
{
    memset(st, 0, sizeof(*st));
    int any;
    do {
        any  = 0;
        any |= pass_const_fold(ctx, st);
        any |= pass_prop(ctx, st);
        any |= pass_algebraic(ctx, st);
        any |= pass_cse(ctx, st);
        any |= pass_dead_code(ctx, st);
        st->iterations++;
    } while (any && st->iterations < 20);   /* cap at 20 to guarantee termination */
}

/* ════════════════════════════════════════════════════════════
 *  REPORT  — human-readable optimisation summary
 * ════════════════════════════════════════════════════════════*/
static void opt_report(const OptStats *st,
                       int before, int after)
{
    printf("\n" C_BOLD C_CYAN
           "  ══════════════════════════════════════════════════════════\n"
           "  PHASE 5 — CODE OPTIMISATION REPORT\n"
           "  ══════════════════════════════════════════════════════════\n"
           C_RESET);

    printf(C_BOLD "  %-34s  %s%5s%s\n" C_RESET,
           "Pass", C_YELLOW, "Hits", C_RESET);
    printf(C_GRAY "  ──────────────────────────────────────────\n" C_RESET);

    #define ROW(label, field, col)                                           \
        printf("  %-34s  %s%5d%s\n", label,                                 \
               (st->field > 0) ? col : C_GRAY,                              \
               st->field, C_RESET)

    ROW("Constant Folding",              const_fold,   C_GREEN);
    ROW("Constant/Copy Propagation",     const_prop,   C_GREEN);
    ROW("Copy Propagation",              copy_prop,    C_GREEN);
    ROW("Algebraic Identities",          algebraic,    C_GREEN);
    ROW("Common Subexpr Elimination",    cse,          C_GREEN);
    ROW("Dead Code Elimination",         dead_code,    C_GREEN);
    ROW("Unreachable Code Removal",      unreachable,  C_GREEN);

    #undef ROW

    printf(C_GRAY "  ──────────────────────────────────────────\n" C_RESET);
    printf("  Fixed-point iterations        :  " C_CYAN "%d\n" C_RESET,
           st->iterations);
    printf("  Instructions before optimise  :  " C_WHITE "%d\n" C_RESET, before);
    printf("  Instructions after  optimise  :  " C_WHITE "%d\n" C_RESET, after);

    int saved = before - after;
    double pct = before > 0 ? (saved * 100.0 / before) : 0.0;
    const char *col = saved > 0 ? C_GREEN : C_GRAY;
    printf("  Instructions eliminated       :  %s%d  (%.1f%% reduction)%s\n\n",
           col, saved, pct, C_RESET);
}

/* ════════════════════════════════════════════════════════════
 *  DIFF PRINTER
 *  Shows BEFORE vs AFTER side-by-side for changed functions.
 *  (Prints two labelled columns in the terminal.)
 * ════════════════════════════════════════════════════════════*/
static void opt_print_comparison(ICGCtx *before_ctx,
                                  ICGCtx *after_ctx)
{
    printf("\n" C_BOLD C_BLUE
           "  Optimised TAC\n" C_RESET);
    printf(C_GRAY "  (Use icg_print() for the full unoptimised listing.)\n\n"
           C_RESET);
    icg_print(after_ctx);
}

/* ════════════════════════════════════════════════════════════
 *  DEEP-COPY of an ICGCtx  (needed for before/after compare)
 * ════════════════════════════════════════════════════════════*/
static void icg_copy(const ICGCtx *src, ICGCtx *dst)
{
    memset(dst, 0, sizeof(*dst));
    dst->temp_cnt  = src->temp_cnt;
    dst->label_cnt = src->label_cnt;

    for (TACInstr *s = src->head; s; s = s->next) {
        TACInstr *d = (TACInstr*)calloc(1, sizeof(TACInstr));
        d->kind   = s->kind;
        d->result = s->result ? strdup(s->result) : NULL;
        d->arg1   = s->arg1   ? strdup(s->arg1)   : NULL;
        d->arg2   = s->arg2   ? strdup(s->arg2)   : NULL;
        d->op     = s->op     ? strdup(s->op)     : NULL;
        d->n_args = s->n_args;
        if (!dst->head) dst->head = dst->tail = d;
        else { dst->tail->next = d; dst->tail = d; }
        dst->instr_cnt++;
    }
}

/* ════════════════════════════════════════════════════════════
 *  PUBLIC ENTRY POINT
 *  Call this after icg_generate():
 *
 *    icg_generate(&icg, parse_root);
 *    opt_optimize(&icg);           ← runs all passes + prints
 *
 *  Or, for finer control:
 *    ICGCtx before;
 *    icg_copy(&icg, &before);
 *    OptStats st;
 *    opt_run(&icg, &st);
 *    int after_n = tac_count(&icg);
 *    opt_report(&st, before.instr_cnt, after_n);
 *    icg_print(&icg);
 *    icg_free(&before);
 * ════════════════════════════════════════════════════════════*/
void opt_optimize(ICGCtx *ctx)
{
    /* snapshot before */
    ICGCtx before;
    icg_copy(ctx, &before);
    int before_n = before.instr_cnt;

    /* run all passes */
    OptStats st;
    opt_run(ctx, &st);

    /* report */
    opt_report(&st, before_n, ctx->instr_cnt);

    /* print optimised code */
    opt_print_comparison(&before, ctx);

    /* clean up snapshot */
    icg_free(&before);
}
