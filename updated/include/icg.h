/*
 * ============================================================
 *  icg.h  —  Phase 4: Intermediate Code Generation Interface
 *  Three-Address Code (TAC) from the AST
 * ============================================================
 */

#ifndef ICG_H
#define ICG_H

#include "ast.h"

typedef struct ICGCtx ICGCtx;

/* Initialize ICG context */
ICGCtx *icg_init(void);

/* Generate TAC from AST root */
void icg_generate(ICGCtx *ctx, ASTNode *root);

/* Print the generated TAC */
void icg_print(const ICGCtx *ctx);

/* Write TAC to file */
void icg_write_file(const ICGCtx *ctx, const char *path);

/* Free ICG context (heap-allocated) */
void icg_free(ICGCtx *ctx);

/* Clear TAC instructions from a context (for stack-allocated contexts) */
void icg_clear(ICGCtx *ctx);

#endif /* ICG_H */
