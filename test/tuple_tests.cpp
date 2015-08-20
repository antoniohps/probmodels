#include "google/gtest/include/gtest/gtest.h"
#include "util/tuple_algorithm.hpp"
#include "util/tuple_operations.hpp"

using namespace probmodels::util;
using namespace std;

TEST(TupleOps, BelongsTo) {
    EXPECT_EQ(true, ((bool)belongs_to<char, tuple<int,float,char,double> >()));
    EXPECT_EQ(false, ((bool)belongs_to<void, tuple<int,float,char,double> >()));
}

TEST(TupleOps, Union) {
    EXPECT_EQ(4, (tuple_size<typename tuple_union<tuple<int,char>,tuple<float,double>>::type>::value) );
    EXPECT_EQ(3, (tuple_size<typename tuple_union<tuple<int,char>,tuple<char,double>>::type>::value) );
}


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
