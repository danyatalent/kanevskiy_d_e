#ifndef TEMPLATE_ARRAY_HPP_2023
#define TEMPLATE_ARRAY_HPP_2023

#include <cstddef>

template <typename T>
class ArrayT {
public:
    ArrayT() = default;
    explicit ArrayT(const std::ptrdiff_t size);
    ArrayT(const ArrayT&);
    ArrayT<T>& operator=(const ArrayT&);

    ArrayT(ArrayT&& arr);
    ArrayT<T>& operator=(ArrayT&& arr);

    ~ArrayT();

    [[nodiscard]] T& operator[] (const std::ptrdiff_t indx);
    [[nodiscard]] const T& operator[](const std::ptrdiff_t indx) const;

    [[nodiscard]] ptrdiff_t ssize() const noexcept;
    void resize(const std::ptrdiff_t new_size);
    void insert(const std::ptrdiff_t indx, const T value);
    void remove(const std::ptrdiff_t indx);

private:
    std::ptrdiff_t ssize_{ 0 };
    T* data_ = nullptr;
//    std::ptrdiff_t capacity_{ 0 };
};

template <typename T>
ArrayT<T>::ArrayT(const ArrayT& arr) {
    ssize_ = arr.ssize_;
    data_ = new T[ssize_];
    std::copy(arr.data_, arr.data_ + arr.ssize_, data_);
}

template <typename T>
ArrayT<T>& ArrayT<T>::operator=(const ArrayT& rhs) {
    if (data_ != rhs.data_) {
        this->resize(rhs.ssize_);
        auto* new_data = new T[ssize_];
        std::copy(rhs.data_, rhs.data_ + rhs.ssize_, new_data);
        delete[] data_;
        data_ = new_data;
    }
    return *this;
}

template <typename T>
ArrayT<T>::ArrayT(ArrayT&& arr) 
    : ssize_(arr.ssize_)
    , data_(arr.data_)
{
    arr.ssize_ = 0;
    arr.data_ = nullptr;
}

template <typename T>
ArrayT<T>& ArrayT<T>::operator=(ArrayT&& arr) {
    if (this != &arr) {
        ssize_ = arr.ssize_;
        delete[] data_;
        data_ = arr.data_;
        arr.ssize_ = 0;
        arr.data_ = nullptr;
    }
    return *this;
}

template<typename T>
ArrayT<T>::~ArrayT() {
    delete[] data_;
}

template <typename T>
[[nodiscard]] T& ArrayT<T>::operator[](const std::ptrdiff_t indx) {
    if (indx < 0 || indx >= ssize_) {
        throw std::out_of_range("index must be in size range");
    }
    return data_[indx];
}

template <typename T>
[[nodiscard]] const T& ArrayT<T>::operator[](const std::ptrdiff_t indx) const {
    if (indx < 0 || indx >= ssize_) {
        throw std::out_of_range("index must be in size range");
    }
    return data_[indx];
}

template<typename T>
[[nodiscard]] std::ptrdiff_t ArrayT<T>::ssize() const noexcept {
    return ssize_;
}

template <typename T>
void ArrayT<T>::insert(const std::ptrdiff_t indx, const T value) {
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

template <typename T>
void ArrayT<T>::remove(const std::ptrdiff_t indx) {
    if (indx < 0 || indx >= ssize_) {
        throw std::out_of_range("index must be in size range");
    }
    auto value = data_[indx];
    for (std::ptrdiff_t i = indx; i < ssize_ - 1; i += 1) {
        data_[i] = data_[i + 1];
    }
    ssize_ -= 1;
}

template <typename T>
void ArrayT<T>::resize(const std::ptrdiff_t new_size) {
    if (new_size <= 0) {
        throw std::invalid_argument("new_size must be >= 0");
    }
    else {
        auto* new_data = new T[new_size] {};
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

template <typename T>
ArrayT<T>::ArrayT(const std::ptrdiff_t size)
    : ssize_(size)
{
    if (size < 0) {
        throw std::invalid_argument("size must be >= 0");
    }
    else {
        data_ = new T[ssize_]{ T() };
    }
}
#endif