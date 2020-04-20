// Binary GCD algorithm (supposed to be faster than Euclid's)
template <typename T>
constexpr T gcd(T u, T v) {
    if (!u || !v)
        return u | v;
    unsigned shift = __builtin_ctz(u | v);
    u >>= __builtin_ctz(u);
    do {
        v >>= __builtin_ctz(v);
        if (u > v) swap(u, v);
        v -= u;
    } while (v);
    return u << shift;
}
