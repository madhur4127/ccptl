template <typename T>
struct dynamic_matrix {
    int32_t R, C;        // rows, columns
    unique_ptr<T[]> mat; // holds the matrix, ptr allows move semantics

    // Implement the rule of five
    dynamic_matrix(int32_t rows, int32_t columns) : R{rows}, C{columns}, mat{make_unique<T[]>(R * C)} {}
    dynamic_matrix(int32_t rows, int32_t columns, const T init) : R{rows}, C{columns}, mat{make_unique<T[]>(R * C)} { fill(begin(), end(), init); }
    dynamic_matrix(const dynamic_matrix &other) : R{other.R}, C{other.C}, mat{make_unique<T[]>(R * C)} { copy(other.begin(), other.end(), begin()); }
    dynamic_matrix(dynamic_matrix &&other) = default;
    dynamic_matrix &operator=(const dynamic_matrix &other) {
        R = other.R, C = other.C, mat = make_unique<T[]>(R * C);
        copy(other.begin(), other.end(), begin());
        return *this;
    }
    dynamic_matrix &operator=(dynamic_matrix &&other) = default;
    ~dynamic_matrix() = default;

    constexpr T &operator()(int32_t i, int32_t j) { return mat[i * C + j]; }
    constexpr T operator()(int32_t i, int32_t j) const { return mat[i * C + j]; }

    auto begin() const { return mat.get(); }
    auto end() const { return mat.get() + R * C; }
};
