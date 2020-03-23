/*
 * Author: Madhur Chauhan
 * Use: Returns nth fibonacci number 
 * Time Complexity: O(log N) with very small constant (iterative)
 * Notes: much faster than matrix exponentiation or recursive table doubling
 */
 
 template<typename T, typename U=uint64_t>
T fibonacci(const U& n){
    // it was hard to write, so it should be easy to understand :)
    if(n<=3) return (n+1)>>1;
    T a = 1, b = 1;
    U mask = U(1)<<(numeric_limits<U>::digits - 1);
    if(is_unsigned<U>::value) mask>>=1+__builtin_clzll(n);
    else for(; !(n & mask); mask >>= 1) ;
    for(mask>>=1; mask; mask>>=1){
        tie(a,b) = make_tuple(a*(2*b-a), b*b+a*a);
        if(mask & n) tie(a,b) = make_tuple(b, a+b);
    }
    return a;
}
