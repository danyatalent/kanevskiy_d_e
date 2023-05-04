#include <matrixs/matrixs.hpp>

#include <stdexcept>
#include <vector>
#include <cstring>
#include <iostream>

MatrixS::~MatrixS() {
    delete[] data_;
}

MatrixS::MatrixS(const std::ptrdiff_t& rows, const std::ptrdiff_t& columns)
    : rows_(rows)
    , columns_(columns)
    , size_(std::make_tuple(rows, columns))
{
    data_ = new int[rows * columns];
    for (std::ptrdiff_t i = 0; i < rows_ * columns_; i += 1) {
        data_[i] = 0;
    }
}

MatrixS::MatrixS(const MatrixS& rhs) {
    size_ = rhs.size_;
    columns_ = rhs.columns_;
    rows_ = rhs.rows_;
    data_ = new int[rows_ * columns_];
    std::copy(rhs.data_, rhs.data_ + (rhs.columns_ * rhs.rows_), data_);
}

MatrixS& MatrixS::operator=(const MatrixS& rhs) {
    if (data_ != rhs.data_) {
        resize(rhs.size_);
        auto* new_data = new int[rhs.columns_ * rhs.rows_];
        std::copy(rhs.data_, rhs.data_ + (rhs.columns_ * rhs.rows_), new_data);
        delete[] data_;
        data_ = new_data;
    }
    return *this;
}

MatrixS::MatrixS(const SizeType& size)
    : rows_(std::get<0>(size)),
    columns_(std::get<1>(size)),
    size_(size)
{
    data_ = new int[rows_ * columns_];
    for (std::ptrdiff_t i = 0; i < rows_ * columns_; i += 1) {
        data_[i] = 0;
    }
}

MatrixS::MatrixS(std::initializer_list<std::initializer_list<int>> lst) {
    if (lst.size() == 0 || lst.begin()->size() == 0) {
        size_ = std::make_tuple(0, 0);
        rows_ = 0;
        columns_ = 0;
        data_ = nullptr;
    }
    else {
        rows_ = lst.size();
        columns_ = lst.begin()->size();
        size_ = std::make_tuple(rows_, columns_);
        int i = 0;
        int j = 0;
        data_ = new int[rows_ * columns_];
        for (const auto& l : lst) {
            for (const auto& v : l) {
                data_[i * columns_ + j] = v;
                ++j;
            }
            j = 0;
            ++i;
        }
    }


}

[[nodiscard]] int& MatrixS::at(const std::ptrdiff_t& row, const std::ptrdiff_t& column) {
    if (row >= rows_ || row < 0 || column >= columns_ || column < 0) {
        throw std::out_of_range("indexies must be in size range");
    }
    return data_[row * columns_ + column];
}

[[nodiscard]] const int& MatrixS::at(const std::ptrdiff_t& row, const std::ptrdiff_t& column) const {
    if (row >= rows_ || row < 0 || column >= columns_ || column < 0) {
        throw std::out_of_range("indexies must be in size range");
    }
    return data_[row * columns_ + column];
}

[[nodiscard]] int& MatrixS::at(const SizeType& elem) {
    if (std::get<0>(elem) >= rows_ || std::get<0>(elem) < 0 || std::get<1>(elem) >= columns_ || std::get<1>(elem) < 0) {
        throw std::out_of_range("indixies must be in size range");
    }
    return data_[std::get<0>(elem) * columns_ + std::get<1>(elem)];
}

[[nodiscard]] const int& MatrixS::at(const SizeType& elem) const {
    if (std::get<0>(elem) >= rows_ || std::get<0>(elem) < 0 || std::get<1>(elem) >= columns_ || std::get<1>(elem) < 0) {
        throw std::out_of_range("indixies must be in size range");
    }
    return data_[std::get<0>(elem) * columns_ + std::get<1>(elem)];
}

void MatrixS::resize(const std::ptrdiff_t m, std::ptrdiff_t n) {
    if (m <= 0 || n <= 0) {
        throw std::out_of_range("n and m must be > 0");
    }
    else {
        auto* new_data = new int[m * n] {};
        for (std::ptrdiff_t i = 0; i < std::min(rows_, m); i += 1) {
            for (std::ptrdiff_t j = 0; j < std::min(columns_, n); j += 1) {
                new_data[i * n + j] = at({ i, j });
            }
        }
        delete[] data_;
        data_ = new_data;
        for (std::ptrdiff_t i = rows_ * columns_; i < n * m; i += 1) {
            data_[i] = 0;
        }
        rows_ = m;
        columns_ = n;
        size_ = std::make_tuple(m, n);
    }
}

void MatrixS::resize(const SizeType& new_size) {
    std::ptrdiff_t m = std::get<0>(new_size);
    std::ptrdiff_t n = std::get<1>(new_size);
    if (m <= 0 || n <= 0) {
        throw std::invalid_argument("n and m must be > 0");
    }
    else {
        auto* new_data = new int[m * n] {};
        for (std::ptrdiff_t i = 0; i < std::min(rows_, m); i += 1) {
            for (std::ptrdiff_t j = 0; j < std::min(columns_, n); j += 1) {
                new_data[i * n + j] = at({ i, j });
            }
        }
        delete[] data_;
        data_ = new_data;
        for (std::ptrdiff_t i = rows_ * columns_; i < n * m; i += 1) {
            data_[i] = 0;
        }
        rows_ = m;
        columns_ = n;
        size_ = new_size;
    }
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