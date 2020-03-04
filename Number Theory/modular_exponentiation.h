inline constexpr int32_t mexp(int64_t x, int64_t n, int32_t m = 1'000'000'007) {
    int32_t res = 1;
    x %= m;
	while (n) {
		if (n & 1) res = (res * x) % m;
		n >>= 1;
		x = (x * x) % m;
	}
	return res;
}
