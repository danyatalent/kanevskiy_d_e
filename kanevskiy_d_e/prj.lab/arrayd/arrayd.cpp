#include <arrayd/arrayd.hpp>

#include <stdexcept>
#include <cstring>

ArrayD::~ArrayD() {
    delete[] data_;
}

ArrayD::ArrayD(const std::ptrdiff_t size)
    : ssize_(size)
{
    data_ = new double[ssize_];
}

void ArrayD::resize(const std::ptrdiff_t new_size) {
    if (new_size < 0) {
        throw std::invalid_argument("new_size must be positive");
    }
    if (new_size == 0) {
        data_ = nullptr;
        ssize_ = 0;
    }
    else {
        auto* new_data = new double[new_size] {};
        if (data_ != nullptr) {
            auto copy_size = std::min(ssize_, new_size) * sizeof(double);
            std::memcpy(new_data, data_, copy_size);
            delete[] data_;
        }
        data_ = new_data;
        ssize_ = new_size;
    }
}

double& ArrayD::operator[](const std::ptrdiff_t indx) {
    if (indx < 0 || indx >= ssize_) {
        throw std::invalid_argument("index must be in size range");
    }
    return data_[indx];
}

const double& ArrayD::operator[](const std::ptrdiff_t indx) const {
    if (indx < 0 || indx >= ssize_) {
        throw std::invalid_argument("index must be in size range");
    }
    return data_[indx];
}

void ArrayD::insert(const double value, const std::ptrdiff_t indx) {
    if (indx > ssize_ || indx < 0) {
        throw std::invalid_argument("index must be in size range");
    }
    this->resize(1 + ssize_);
    if (indx != ssize_) {
        for (std::ptrdiff_t i = ssize_ - 1; i > indx; i -= 1) {
            data_[i] = data_[i - 1];
        }
    }
    data_[indx] = value;
}

double& ArrayD::remove(const std::ptrdiff_t indx) {
    if (indx < 0 || indx >= ssize_) {
        throw std::invalid_argument("index must be in size range");
    }
    auto value = data_[indx];
    for (std::ptrdiff_t i = indx; i < ssize_ - 1; i += 1) {
        data_[i] = data_[i + 1];
    }
    ssize_ -= 1;
    return data_[indx];
}

std::ptrdiff_t ArrayD::ssize() const noexcept {
    return ssize_;
}