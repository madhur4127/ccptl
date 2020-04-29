/*
 * Author: Madhur Chauhan, Ankur Dua
 * Use: Easy and expressive matrix operations
 * Features: Highly optimized for modular arithmetic and matrix multiplication, matrix exponentiation
 * Time Complexity: O(N^3) cache-efficient matrix multiplication
 * Notes: 1. Use Modular class from modular.h to take advantage of optimized modular arithmetic
 *        2. There are helper member functions like mexp (modular exponentiation)
 * Status: Tested
 */
template <typename T>
struct matrix_base {
	matrix_base(int r, int c) : data(r, vector<T>(c)) {}
	matrix_base(int r, int c, const T init) : data(r, vector<T>(c, init)) {}

	constexpr matrix_base operator+(const matrix_base &o) const {
		matrix_base ret(row(), col());
		transform(ret.data, data, o.data, std::plus<T>());
		return ret;
	}
	constexpr matrix_base operator-(const matrix_base &o) const {
		matrix_base ret(row(), col());
		transform(ret.data, data, o.data, std::minus<T>());
		return ret;
	}
	constexpr matrix_base &operator+=(const matrix_base &o) {
		transform(data, data, o.data, std::plus<T>());
		return *this;
	}
	constexpr matrix_base &operator-=(const matrix_base &o) {
		transform(data, data, o.data, std::minus<T>());
		return *this;
	}
	
	vector<T> &operator[](const size_t idx) { return data[idx]; }

	vector<vector<T>> data;
	constexpr int row() const { return data.size(); }
	constexpr int col() const { return data[0].size(); }

	// this is called by op: +,-,+=,-=
	template <typename F>
	constexpr void transform(vector<vector<T>> &rhs, const vector<vector<T>> &op1, const vector<vector<T>> &op2, const F &&op) const {
		for (size_t i = 0; i < rhs.size(); ++i)
			std::transform(begin(op1[i]), end(op1[i]), begin(op2[i]), begin(rhs[i]), op);
	}
};

template <typename T>
struct matrix : public matrix_base<T> {
	using base_type = matrix_base<T>;

	matrix(int r, int c) : base_type(r, c) {}
	matrix(int r, int c, const T init) : base_type(r, c, init) {}
	matrix(const base_type &o) : base_type(o) {}

	constexpr matrix operator*(const matrix &tp) const {
		const int x = base_type::row(), y = base_type::col(), z = tp.row();
		matrix ret(x, z);
		for (int i = 0; i < x; ++i)
			for (int k = 0; k < y; ++k)
				for (int j = 0; j < z; ++j)
					ret[i][j] += base_type::data[i][k] * tp.data[k][j]; // interchanged loops for cache efficiency
		return ret;
	}

	matrix &operator*=(const matrix &o) {
		(*this) = (*this) * o;
		return *this;
	}
};

template <int MOD>
struct matrix<modular<MOD>> : public matrix_base<modular<MOD>> {
	using base_type = matrix_base<modular<MOD>>;

	matrix(int r, int c) : base_type(r, c) {}
	matrix(int r, int c, const modular<MOD> init) : base_type(r, c, init) {}
	matrix(const base_type &o) : base_type(o) {}

	constexpr matrix operator*(const matrix &o) const {
		// N^3/16 modulo operations instead of N^3 in a tiled fashion
		const int32_t x = base_type::row(), y = base_type::col(), z = o.row();
		matrix ret(x, z);
		const int BS = 16; // depends on L1d cache and cache line size
		for (int32_t i1 = 0; i1 < x; i1 += BS)
			for (int32_t j1 = 0; j1 < y; j1 += BS)
				for (int32_t k1 = 0; k1 < z; k1 += BS)
					for (int32_t i = i1, lim_i = min(i1 + BS, x); i < lim_i; ++i)
						for (int32_t j = j1, lim_j = min(j1 + BS, y); j < lim_j; ++j) {
							uint64_t temp = 0; // following loop can be unrolled
							for (int32_t k = k1, lim_k = min(k1 + BS, z); k < lim_k; ++k)
								temp += base_type::data[i][k].value * static_cast<uint64_t>(o.data[k][j].value);
							ret[i][j].value = (ret[i][j].value + temp) % MOD;
						}

		return ret;
	}

	matrix &operator*=(const matrix &o) {
		(*this) = (*this) * o;
		return *this;
	}
};

template <typename T>
constexpr matrix<T> mexp(matrix<T> a, long long e) {
	int n = a.row();
	matrix<T> ret(n, n, 0);
	for (int i = 0; i < n; ++i)
		ret[i][i] = 1;
	while (e) {
		if (e & 1) ret *= a;
		a *= a, e >>= 1;
	}
	return ret;
}
