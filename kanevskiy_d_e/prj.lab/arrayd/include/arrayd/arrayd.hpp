#ifndef DYNAMIC_ARRAY_HPP_2023
#define DYNAMIC_ARRAY_HPP_2023

#include <cstddef>

class ArrayD {
public:
    ArrayD() = default;
    explicit ArrayD(const std::ptrdiff_t size);
    ArrayD(const ArrayD&);
    ArrayD& operator=(const ArrayD&);

    ~ArrayD();

    [[nodiscard]] double& operator[] (const std::ptrdiff_t indx);
    [[nodiscard]] const double& operator[](const std::ptrdiff_t indx) const;

    [[nodiscard]] ptrdiff_t ssize() const noexcept;
    void resize(const std::ptrdiff_t new_size);
    void insert(const std::ptrdiff_t indx, const double value);
    void remove(const std::ptrdiff_t indx);

private:
    std::ptrdiff_t ssize_{ 0 };
    std::ptrdiff_t capacity_{ 0 };
    double* data_ = nullptr;
};
#endif