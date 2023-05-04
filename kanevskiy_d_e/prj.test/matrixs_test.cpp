#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <matrixs/matrixs.hpp>

TEST_CASE("constructor") {
    SUBCASE("default constructor") {
        auto matrix = MatrixS();
        CHECK(matrix.nCols() == 0);
        CHECK(matrix.nRows() == 0);
        CHECK(matrix.ssize() == std::make_tuple(0, 0));
    }
    SUBCASE("rows and columns constructor") {
        auto matrix = MatrixS(5, 3);
        CHECK(matrix.nCols() == 3);
        CHECK(matrix.nRows() == 5);
        CHECK(matrix.ssize() == std::make_tuple(5, 3));
        CHECK(matrix.at(3, 2) == 0);
    }
    SUBCASE("size constructor") {
        auto matrix = MatrixS(std::make_tuple(5, 3));
        CHECK(matrix.nCols() == 3);
        CHECK(matrix.nRows() == 5);
        CHECK(matrix.ssize() == std::make_tuple(5, 3));
        CHECK(matrix.at(3, 2) == 0);
    }
    SUBCASE("initializer list") {
        auto matrix = MatrixS({ {1, 3, 4}, {2, 5, 6} });
        CHECK(matrix.nCols() == 3);
        CHECK(matrix.nRows() == 2);
        CHECK(matrix.ssize() == std::make_tuple(2, 3));
        CHECK(matrix.at(0, 0) == 1);
        CHECK(matrix.at(1, 1) == 5);

        auto matrix_empty = MatrixS({ {}, {}, {} });
        CHECK(matrix_empty.nCols() == 0);
        CHECK(matrix_empty.nRows() == 0);
        CHECK(matrix_empty.ssize() == std::make_tuple(0, 0));

    }
}

TEST_CASE("at method") {
    auto matrix = MatrixS(5, 5);
    CHECK(matrix.at(0, 0) == 0);
    CHECK(matrix.at(4, 4) == 0);
    CHECK(matrix.at(std::make_tuple(3, 3)) == 0);
    CHECK(matrix.at(std::make_tuple(0, 0)) == 0);

    CHECK_THROWS_AS(matrix.at(-1, 3) == 0, std::out_of_range);
    CHECK_THROWS_AS(matrix.at(6, 3) == 0, std::out_of_range);
    CHECK_THROWS_AS(matrix.at(5, -1) == 0, std::out_of_range);
    CHECK_THROWS_AS(matrix.at(5, 12) == 0, std::out_of_range);

    for (std::ptrdiff_t i = 0; i < matrix.nRows(); i += 1) {
        for (std::ptrdiff_t j = 0; j < matrix.nCols(); j += 1) {
            matrix.at(i, j) = i + j;
        }
    }

    for (std::ptrdiff_t i = 0; i < matrix.nRows(); i += 1) {
        for (std::ptrdiff_t j = 0; j < matrix.nCols(); j += 1) {
            CHECK(matrix.at(i, j) == i + j);
        }
    }
}

TEST_CASE("copy constructor") {
    auto matrix1 = MatrixS(3, 4);
    for (std::ptrdiff_t i = 0; i < matrix1.nRows(); i += 1) {
        for (std::ptrdiff_t j = 0; j < matrix1.nCols(); j += 1) {
            matrix1.at(i, j) = i + j;
        }
    }

    auto matrix2 = MatrixS(matrix1);
    CHECK(matrix2.nCols() == 4);
    CHECK(matrix2.nRows() == 3);
    CHECK(matrix2.ssize() == std::make_tuple(3, 4));
    for (std::ptrdiff_t i = 0; i < matrix2.nRows(); i += 1) {
        for (std::ptrdiff_t j = 0; j < matrix2.nCols(); j += 1) {
            CHECK(matrix2.at(i, j) == i + j);
        }
    }
    matrix2.at(0, 0) = 15;
    CHECK(matrix1.at(0, 0) != 15);
}

TEST_CASE("assigment operator") {
    auto matrix1 = MatrixS(3, 4);
    for (std::ptrdiff_t i = 0; i < matrix1.nRows(); i += 1) {
        for (std::ptrdiff_t j = 0; j < matrix1.nCols(); j += 1) {
            matrix1.at(i, j) = i + j;
        }
    }
    auto matrix2 = matrix1;
    CHECK(matrix2.nCols() == 4);
    CHECK(matrix2.nRows() == 3);
    CHECK(matrix2.ssize() == std::make_tuple(3, 4));
    for (std::ptrdiff_t i = 0; i < matrix2.nRows(); i += 1) {
        for (std::ptrdiff_t j = 0; j < matrix2.nCols(); j += 1) {
            CHECK(matrix2.at(i, j) == i + j);
        }
    }
    matrix2.at(0, 0) = 15;
    CHECK(matrix1.at(0, 0) != 15);

}

