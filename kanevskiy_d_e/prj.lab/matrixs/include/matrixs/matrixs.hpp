#ifndef MATRIXS_MATRIXS_HPP_2023
#define MATRIXS_MATRIXS_HPP_2023

#include <cstddef>

class MatrixS {
public:
    MatrixS() = default;
    MatrixS(const MatrixS& rhs);
    MatrixS(const std::ptrdiff_t& rows, const std::ptrdiff_t& columns);
    ~MatrixS();

    int& at(const std::ptrdiff_t& row, const std::ptrdiff_t& column);
    MatrixS& operator=(const MatrixS& rhs);
    void resize(const std::ptrdiff_t new_rows, std::ptrdiff_t new_cols);
    std::ptrdiff_t cols() const noexcept;
    std::ptrdiff_t rows() const noexcept;
    // int& operator()(const std::ptrdiff_t& row, const std::ptrdiff_t& column);
    // const int& operator()(const std::ptrdiff_t & row, const std::ptrdiff_t& column) const;

private:
    std::ptrdiff_t rows_ = 0;
    std::ptrdiff_t columns_ = 0;
    int* data_ = nullptr;
};
#endif