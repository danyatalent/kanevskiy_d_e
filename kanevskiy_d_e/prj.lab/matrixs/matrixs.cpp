#include <matrixs/matrixs.hpp>

#include <stdexcept>

MatrixS::~MatrixS() {
    delete[] data_;
}

MatrixS::MatrixS(const std::ptrdiff_t& rows, const std::ptrdiff_t& columns)
    : rows_(rows)
    , columns_(columns)
    , size_(std::make_tuple(rows, columns))
{
    data_ = new int[rows * columns];
}

MatrixS::MatrixS(const SizeType& size)
    : rows_(std::get<0>(size)),
    columns_(std::get<1>(size)),
    size_(size)
{
    data_ = new int[rows_ * columns_];
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

int& MatrixS::at(const SizeType& elem) {
    if (std::get<0>(elem) >= rows_ || std::get<0>(elem) < 0 || std::get<1>(elem) >= columns_ || std::get<1>(elem) < 0) {
        throw std::out_of_range("indixies must be in size range");
    }
    return data_[std::get<0>(elem) * columns_ + std::get<1>(elem)];
}

const int& MatrixS::at(const SizeType& elem) const {
    if (std::get<0>(elem) >= rows_ || std::get<0>(elem) < 0 || std::get<1>(elem) >= columns_ || std::get<1>(elem) < 0) {
        throw std::out_of_range("indixies must be in size range");
    }
    return data_[std::get<0>(elem) * columns_ + std::get<1>(elem)];
}

void MatrixS::resize(const std::ptrdiff_t new_rows, std::ptrdiff_t new_cols) {

}

void MatrixS::resize(const SizeType& new_size) {

}

std::ptrdiff_t MatrixS::nCols() const noexcept {
    return columns_;
}

std::ptrdiff_t MatrixS::nRows() const noexcept {
    return rows_;
}

const MatrixS::SizeType& MatrixS::ssize() const noexcept{
    return size_;
}