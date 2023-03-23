#include <matrixs/matrixs.hpp>

#include <stdexcept>

MatrixS::~MatrixS() {
    delete[] data_;
}

MatrixS::MatrixS(const std::ptrdiff_t& rows, const std::ptrdiff_t& columns)
    : rows_(rows)
    , columns_(columns)
{
    data_ = new int[rows * columns];
}

int& MatrixS::at(const std::ptrdiff_t& row, const std::ptrdiff_t& column) {
    if (row >= rows_ || row < 0 || column >= columns_ || column < 0) {
        throw std::invalid_argument("indexies must be in size range");
    }
    return data_[row * columns_ + column];
}

const int& MatrixS::at(const std::ptrdiff_t& row, const std::ptrdiff_t& column) const {
    if (row >= rows_ || row < 0 || column >= columns_ || column < 0) {
        throw std::invalid_argument("indexies must be in size range");
    }
    return data_[row * columns_ + column];
}

void MatrixS::resize(const std::ptrdiff_t new_rows, std::ptrdiff_t new_cols) {

}

std::ptrdiff_t MatrixS::cols() const noexcept {
    return columns_;
}

std::ptrdiff_t MatrixS::rows() const noexcept {
    return rows_;
}