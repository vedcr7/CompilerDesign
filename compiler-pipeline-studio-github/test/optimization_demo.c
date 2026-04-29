/* optimization_demo.c - Program with clear constant folding opportunities */

int constant_fold_add(void) {
    return 5 + 3;  /* Should fold to 8 */
}

int constant_fold_mul(void) {
    return 7 * 2;  /* Should fold to 14 */
}

int algebraic_identity_zero(void) {
    return 100 * 0;  /* Should fold to 0 */
}

int algebraic_identity_one(void) {
    return 50 * 1;   /* Should fold to 50 */
}

int constant_fold_div(void) {
    return 20 / 4;   /* Should fold to 5 */
}

int main(void) {
    return constant_fold_add() + constant_fold_mul() + algebraic_identity_zero() + algebraic_identity_one() + constant_fold_div();
}
