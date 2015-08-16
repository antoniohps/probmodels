#include "google/gtest/include/gtest/gtest.h"
#include "util/tuple_algorithm.hpp"

using namespace probmodels::util;
using namespace std;


TEST(TupleSum, NumericDefault) {
    EXPECT_EQ(6, tuple_sum(std::make_tuple(1,2,3), 0));
}

TEST(TupleSum, Numeric) {

    EXPECT_EQ(24, tuple_sum(
                  make_tuple(1,2,3,4), 1,
                  [](const int& a, const int& b) { return a * b;}
    ));
}

TEST(TupleSum, Text) {
    EXPECT_EQ("abc", tuple_sum(
                  make_tuple("a","b","c"), string(),
                  [](string&& a, const string& b) {
                  a.append(b);
                  return a;
              }));
}

TEST(TupleReverseSum, Numeric) {

    EXPECT_EQ(24, tuple_reverse_sum(
                  make_tuple(1,2,3,4), 1,
                  [](const int& a, const int& b) { return a * b;}
    ));
}

TEST(TupleReverseSum, Text) {
    EXPECT_EQ("cba", tuple_reverse_sum(
                  make_tuple("a","b","c"), string(),
                  [](string&& a, const string& b) {
                  a.append(b);
                  return a;
              }));
}


int main(int argc, char **argv) {

    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
