#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <arrayd/arrayd.hpp>

TEST_CASE("resize") {
    auto arr = ArrayD();

    SUBCASE("default") {
        CHECK(arr.ssize() == 0);
        CHECK_THROWS_AS(arr[-1] = 5, std::invalid_argument&);
        CHECK_THROWS_AS(arr[0] = 5, std::invalid_argument&);
        CHECK_THROWS_AS(arr[5] = 5, std::invalid_argument&);
    }
    SUBCASE("resize") {
        arr.resize(5);
        CHECK(arr.ssize() == 5);
    }
    SUBCASE("resize to 0") {
        arr.resize(0);
        CHECK(arr.ssize() == 0);
    }
}

TEST_CASE("acces by index") {
    auto arr = ArrayD();
    arr.resize(8);
    CHECK_THROWS(arr[-1] = 5);
    for (std::ptrdiff_t i = 0; i < arr.ssize(); i += 1) {
        REQUIRE_NOTHROW(arr[i] = i);
    }
    for (std::ptrdiff_t i = 0; i < arr.ssize(); i += 1) {
        CHECK(arr[i] == i);
    }
}

TEST_CASE("check resize values") {
    auto arr = ArrayD();
    SUBCASE("check ranges after resize") {
        arr.resize(5);
        CHECK_THROWS_AS(arr[-1] = 5, std::invalid_argument&);
        CHECK_THROWS_AS(arr[8] = 5, std::invalid_argument&);
        REQUIRE_NOTHROW(arr[0] = 8);
        arr.resize(10);
        CHECK_THROWS_AS(arr[-1] = 5, std::invalid_argument&);
        REQUIRE_NOTHROW(arr[5] = 8);
        REQUIRE_NOTHROW(arr[9] = 8);
    }
    SUBCASE("values after resize") {
        arr.resize(5);
        for (std::ptrdiff_t i = 0; i < 5; i += 1) {
            arr[i] = i;
        }
        arr.resize(10);
        for (std::ptrdiff_t i = 0; i < arr.ssize(); i += 1) {
            if (i < 5) {
                CHECK(arr[i] == i);
            }
            else {
                CHECK(arr[i] == 0);
            }
        }
    }
}

TEST_CASE("insert/remove") {
    auto arr = ArrayD();
    SUBCASE("insert") {
        arr.resize(6);
        for (std::ptrdiff_t i = 0; i < arr.ssize(); i += 1) {
            arr[i] = i + 1;
        }
        CHECK_THROWS_AS(arr.insert(123, -1), std::invalid_argument&);
        arr.insert(3, 9);
        CHECK(arr.ssize() == 7);
        for (std::ptrdiff_t i = 0; i < arr.ssize(); i += 1) {
            if (i < 3) CHECK(arr[i] == i + 1);
            else if (i == 3) CHECK(arr[i] == 9);
            else CHECK(arr[i] == i);
        }
        arr.insert(arr.ssize(), 8);
        CHECK(arr[7] == 8);
    }
    SUBCASE("remove") {
        arr.resize(6);
        for (std::ptrdiff_t i = 0; i < arr.ssize(); i += 1) {
            arr[i] = i + 1;
        }
        CHECK_THROWS_AS(arr.remove(-1), std::invalid_argument&);
        REQUIRE_NOTHROW(arr.remove(3));
        CHECK(arr.ssize() == 5);
        for (std::ptrdiff_t i = 0; i < arr.ssize(); i += 1) {
            if (i < 3) CHECK(arr[i] == i + 1);
            else CHECK(arr[i] == i + 2);
        }
    }
}