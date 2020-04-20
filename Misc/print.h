/*
 * An elegant variadic print function.
 * Source: stackoverflow and cpp_reference
 * Note: C++17 is required.
 */

template <class... Args>
void print(Args... args) { (std::cout << ... << args) << '\n'; }
