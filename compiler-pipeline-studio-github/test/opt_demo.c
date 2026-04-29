int get_constant(void) {
    return 16 / 4;
}

int get_identity(void) {
    return 10 * 1;
}

int get_zero(void) {
    return 0 * 999;
}

int main(void) {
    return get_constant() + get_identity() + get_zero();
}
