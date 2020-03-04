/*
 * Author : Jakob Kogler, Madhur Chauhan
 * Use : Modular Arithmetic
 * Time Complexity : O(1)
 * Space Complexity: O(1)
 * Usage Notes: Template argument is the modulus which is set to default: 1e9+7. A modular int can be created by:
 *                  Modular<> m=56; // creates a modular integer initialize to 56 in MOD = 1e9+7
 *                  using MInt = Modular<998244353>; // MInt can be used like regular integer
 *                  vector<MInt> dp(10, Mint(0)); // creater a vector with values initialized to 0
 *                  cout << m * 1'000'000'000'000 << endl; // will not overflow
 */

template <int MOD = 1'000'000'007>
struct Modular {
	int value;
    
	Modular(long long v = 0) {
		value = v % MOD;
		if (value < 0) value += MOD;
	}
	Modular(long long a, long long b) : value(0) {
		*this += a;
		*this /= b;
	}
	Modular &operator+=(Modular const &b) {
		value += b.value;
		if (value >= MOD) value -= MOD;
		return *this;
	}
	Modular &operator-=(Modular const &b) {
		value -= b.value;
		if (value < 0) value += MOD;
		return *this;
	}
	Modular &operator*=(Modular const &b) {
		value = (long long)value * b.value % MOD;
		return *this;
	}

	friend Modular mexp(Modular a, long long e) {
		Modular res = 1;
		while (e) {
			if (e & 1) res *= a;
			a *= a;
			e >>= 1;
		}
		return res;
	}
	friend Modular inverse(Modular a) {
		int phi = MOD - 1; // change this for general MOD where a^phi = 1 (mod MOD)
		return mexp(a, phi - 1);
	}
	
	Modular &operator/=(Modular const &b) { return *this *= inverse(b); }
	friend Modular operator+(Modular a, const Modular b) { return a += b; }
	friend Modular operator-(Modular a, const Modular b) { return a -= b; }
	friend Modular operator-(const Modular a) { return 0 - a; }
	friend Modular operator*(Modular a, const Modular b) { return a *= b; }
	friend Modular operator/(Modular a, const Modular b) { return a /= b; }
	friend std::ostream &operator<<(std::ostream &os, const Modular &a) { return os << a.value; }
	friend std::istream &operator>>(std::istream &is, Modular &a) {
		long long temp;
		is >> temp;
		a = Modular(temp);
		return is;
	}
	friend bool operator==(Modular const &a, Modular const &b) { return a.value == b.value; }
	friend bool operator!=(Modular const &a, Modular const &b) { return a.value != b.value; }
};
