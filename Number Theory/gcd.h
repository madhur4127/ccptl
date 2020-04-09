template<typename T>
constexpr T gcd(T u, T v) {
   // boundary cases
   if (!u || !v)
	  return u | v;
#if __cpp_lib_gcd_lcm >= 201606L
   return std::gcd(u, v);
#endif
   unsigned shift = __builtin_ctz(u | v);
   u >>= __builtin_ctz(u);
   do
   {
	  v >>= __builtin_ctz(v);
	  if (u > v) swap(u, v);
	  v -= u;
   } while (v);
   return u << shift;
}
