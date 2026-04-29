/*
 * ============================================================
 *  tcg.h  —  Phase 6: Target Code Generation
 *  x86-64 AT&T Assembly Output
 *  Compiler Design Project | GEU
 *
 *  Consumes the optimised TACInstr list from ICGCtx (icg.c)
 *  and emits GNU/AT&T x86-64 assembly suitable for GAS/gcc.
 *
 *  Calling Convention: System V AMD64 ABI
 *    - Integer args: rdi, rsi, rdx, rcx, r8, r9 (then stack)
 *    - Return value: rax
 *    - Caller-saved: rax, rcx, rdx, rsi, rdi, r8, r9, r10, r11
 *    - Callee-saved: rbx, rbp, r12–r15
 *
 *  Include AFTER icg.h (shares ICGCtx opaque handle).
 * ============================================================
 */

#ifndef TCG_H
#define TCG_H

#include "icg.h"
#include <stdio.h>

/* ── opaque TCG context ─────────────────────────────────── */
typedef struct TCGCtx TCGCtx;

/* ── public API ─────────────────────────────────────────── */

/*
 * tcg_init()
 *   Allocate and initialise a new TCG context.
 *   Must be called once before any other tcg_* function.
 */
TCGCtx *tcg_init(void);

/*
 * tcg_generate(ctx, icg_ctx)
 *   Walk the optimised TAC list inside icg_ctx and translate
 *   each instruction to x86-64 AT&T assembly stored in ctx.
 */
void tcg_generate(TCGCtx *ctx, const ICGCtx *icg_ctx);

/*
 * tcg_print(ctx)
 *   Pretty-print the generated assembly to stdout with
 *   colour-coded annotations (phase banner, line numbers).
 */
void tcg_print(const TCGCtx *ctx);

/*
 * tcg_write_file(ctx, path)
 *   Write the raw assembly text to 'path' so it can be
 *   assembled with:
 *     gcc -no-pie output.s -o output
 */
void tcg_write_file(const TCGCtx *ctx, const char *path);

/*
 * tcg_free(ctx)
 *   Release all memory owned by the TCG context.
 */
void tcg_free(TCGCtx *ctx);

#endif /* TCG_H */
