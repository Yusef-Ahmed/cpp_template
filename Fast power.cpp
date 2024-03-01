ll fp(ll base, ll power) {
    ll result = 1;
    while (power > 0) {
        if (power & 1) result *= base;
        base *= base;
        power /= 2;
    }
    return result;
}
