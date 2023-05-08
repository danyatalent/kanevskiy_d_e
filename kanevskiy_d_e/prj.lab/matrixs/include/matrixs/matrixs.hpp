#ifndef MATRIXS_MATRIXS_HPP_2023
#define MATRIXS_MATRIXS_HPP_2023

#include <cstddef>
#include <initializer_list>
#include <tuple>

class MatrixS {
public:
    using SizeType = std::tuple<std::ptrdiff_t, std::ptrdiff_t>;
    MatrixS() = default;
    explicit MatrixS(const std::ptrdiff_t& rows, const std::ptrdiff_t& columns);
    explicit MatrixS(const SizeType& size);
    MatrixS(const MatrixS&);
    MatrixS& operator=(const MatrixS&);
    MatrixS(std::initializer_list<std::initializer_list<int>> lst);

    MatrixS(MatrixS&& mat);
    MatrixS& operator=(MatrixS&& mat);
    
    ~MatrixS();

    [[nodiscard]] int& at(const std::ptrdiff_t& row, const std::ptrdiff_t& column);
    [[nodiscard]] const int& at(const std::ptrdiff_t& row, const std::ptrdiff_t& column) const;

    [[nodiscard]] int& at(const SizeType& elem);
    [[nodiscard]] const int& at(const SizeType& elem) const;

    void resize(const std::ptrdiff_t m, std::ptrdiff_t n);
    void resize(const SizeType& new_size);

    std::ptrdiff_t nCols() const noexcept;
    std::ptrdiff_t nRows() const noexcept;
    const SizeType& ssize() const noexcept;
    // int& operator()(const std::ptrdiff_t& row, const std::ptrdiff_t& column);
    // const int& operator()(const std::ptrdiff_t & row, const std::ptrdiff_t& column) const;

private:
    std::ptrdiff_t rows_ = 0;
    std::ptrdiff_t columns_ = 0;
    SizeType size_ = { 0, 0 };
    int* data_ = nullptr;
};
#endif