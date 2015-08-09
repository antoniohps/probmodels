#include <iostream>
#include "util/tuple_algorithm.hpp"

using namespace probmodels::util;

int main() {

    std::cout << tuple_sum(
                     std::make_tuple(1,2,3), 0,
                     [](int a, int b) -> int { return a + b;})
              << std::endl;

    std::cout << tuple_sum(
                     std::make_tuple(10,20,30), 5)
              << std::endl;

    return 0;
}
