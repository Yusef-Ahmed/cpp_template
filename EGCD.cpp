void movestep(int &a, int &b, int q) {
    int next = a - q * b;
    a = b;
    b = next;
}

int egcd(int a, int b, int &x0, int &y0) {
    int r0 = a, r1 = b;
    int x1, y1;
    x1 = y0 = 0;
    x0 = y1 = 1;
    while (r1 != 0) {
        int q = r0 / r1;
        movestep(x0, x1, q);
        movestep(y0, y1, q);
        movestep(r0, r1, q);
    }
    return r0;
}
