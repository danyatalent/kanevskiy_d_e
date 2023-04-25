#include <arrayd/arrayd.hpp>

#include <stdexcept>
#include <cstring>
#include <algorithm>

ArrayD::~ArrayD() {
    delete[] data_;
}

ArrayD::ArrayD(const std::ptrdiff_t size)
    : ssize_(size),
    capacity_(2 * size)
{
    if (size < 0) {
        throw std::invalid_argument("size must be >= 0");
    }
    else if (size != 0) {
        data_ = new double[ssize_];
    }
}

ArrayD::ArrayD(const ArrayD& arr) {
    ssize_ = arr.ssize_;
    capacity_ = 2 * ssize_;
    data_ = new double[ssize_];
    std::copy(arr.data_, arr.data_ + arr.ssize_, data_);
}

ArrayD& ArrayD::operator=(const ArrayD& rhs) {
    if (data_ != rhs.data_) {
        this->resize(rhs.ssize_);
        auto* new_data = new double[ssize_];
        std::copy(rhs.data_, rhs.data_ + rhs.ssize_, new_data);
        delete[] data_;
        data_ = new_data;
    }
    return *this;
}

void ArrayD::resize(const std::ptrdiff_t new_size) {
    if (new_size < 0) {
        throw std::invalid_argument("new_size must be >= 0");
    }
    if (new_size == 0) {
        data_ = nullptr;
        ssize_ = 0;
    }
    else {
        auto* new_data = new double[new_size] {};
        if (data_ != nullptr) {
            std::copy(data_, data_ + std::min(ssize_, new_size), new_data);
            delete[] data_;
        }
        data_ = new_data;
        for (std::ptrdiff_t i = ssize_; i < new_size; i += 1) {
            data_[i] = 0;
        }
        ssize_ = new_size;
    }
}

[[nodiscard]] double& ArrayD::operator[](const std::ptrdiff_t indx) {
    if (indx < 0 || indx >= ssize_) {
        throw std::out_of_range("index must be in size range");
    }
    return data_[indx];
}

[[nodiscard]] const double& ArrayD::operator[](const std::ptrdiff_t indx) const {
    if (indx < 0 || indx >= ssize_) {
        throw std::out_of_range("index must be in size range");
    }
    return data_[indx];
}

void ArrayD::insert(const std::ptrdiff_t indx, const double value) {
    if (indx > ssize_ || indx < 0) {
        throw std::out_of_range("index must be in size range");
    }
    this->resize(1 + ssize_);
    if (indx != ssize_) {
        for (std::ptrdiff_t i = ssize_ - 1; i > indx; i -= 1) {
            data_[i] = data_[i - 1];
        }
    }
    data_[indx] = value;
}

void ArrayD::remove(const std::ptrdiff_t indx) {
    if (indx < 0 || indx >= ssize_) {
        throw std::out_of_range("index must be in size range");
    }
    auto value = data_[indx];
    for (std::ptrdiff_t i = indx; i < ssize_ - 1; i += 1) {
        data_[i] = data_[i + 1];
    }
    ssize_ -= 1;
}

std::ptrdiff_t ArrayD::ssize() const noexcept {
    return ssize_;
}