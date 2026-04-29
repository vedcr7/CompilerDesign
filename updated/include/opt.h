/*
 * ============================================================
 *  opt.h  —  Phase 5: TAC Code Optimizer Interface
 *  Compiler Design Project | GEU
 * ============================================================
 */

#ifndef OPT_H
#define OPT_H

#include "icg.h"

/* Phase 5: TAC Code Optimizer
 * Runs optimization passes on the TAC instruction list:
 * - Constant folding
 * - Constant/Copy propagation
 * - Algebraic identities
 * - Common subexpression elimination
 * - Dead code elimination
 * - Unreachable code elimination
 *
 * This function modifies the TAC instruction list in-place,
 * optimizing it through multiple fixed-point iterations.
 */
void opt_optimize(ICGCtx *ctx);

#endif /* OPT_H */
