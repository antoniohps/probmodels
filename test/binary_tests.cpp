
#include "google/gtest/include/gtest/gtest.h"
#include "dist/binary.hpp"

using namespace probmodels::dist;
using namespace std;


TEST(Referencing, SingleVariable) {

    conditional_multivar_binary_distribution<string> dist("A");
    EXPECT_DOUBLE_EQ(0.5, dist.get_probability());

    dist.set_probability(0.35);
    EXPECT_DOUBLE_EQ(0.35, dist.get_probability());
}


TEST(Referencing, MultiVariable) {

    conditional_multivar_binary_distribution<string> dist("A","B","C");
    EXPECT_DOUBLE_EQ(0.5, dist.get_probability(false, false));
    EXPECT_DOUBLE_EQ(0.5, dist.get_probability(false, true));
    EXPECT_DOUBLE_EQ(0.5, dist.get_probability(true, false));
    EXPECT_DOUBLE_EQ(0.5, dist.get_probability(true, true));

    dist.set_probability(0.2, false, true);
    EXPECT_DOUBLE_EQ(0.2, dist.get_probability(false, true));
    EXPECT_DOUBLE_EQ(0.2, dist.get_value(true, false, true));
    EXPECT_DOUBLE_EQ(0.8, dist.get_value(false, false, true));
}

TEST(Variable, Adding) {

    conditional_multivar_binary_distribution<string> dist("A","B","C");
    dist.set_probability(0.3, true, true);

    dist.add_condition("D");
    EXPECT_DOUBLE_EQ(0.3, dist.get_probability(true, true, true));
    EXPECT_DOUBLE_EQ(0.3, dist.get_probability(true, true, false));
}


int main(int argc, char **argv) {

    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
