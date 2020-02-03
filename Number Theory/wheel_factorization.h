/*
 * Author : cp-algorithms.com
 * Use : Factorize a given integer
 * Time Complexity : O(sqrt(N)) but ~25% faster than brute-force trial division
 * Space Complexity: O(1)
 * Input : Number to be factorized
 * Output: A C++ vector containing the prime factors in sorted order.
 * Example: If n = 2^2 * 5^1 * 3^2, then wheel_factor(n)
 *          returns vector<int>{2,2,3,3,5}
 */
inline vector<long long> wheel_factor(long long n) {
    using ll = long long;
    vector<ll> factorization;
    for (int d : {2, 3, 5}) {
        while (n % d == 0) {
            factorization.push_back(d);
            n /= d;
        }
    }
    static array<int, 8> increments = {4, 2, 4, 2, 4, 6, 2, 6};
    int i = 0;
    for (ll d = 7; d * d <= n; d += increments[i++]) {
        while (n % d == 0) {
            factorization.push_back(d);
            n /= d;
        }
        if (i == 8) i = 0;
    }
    if (n > 1) factorization.push_back(n);
    return factorization;
}
