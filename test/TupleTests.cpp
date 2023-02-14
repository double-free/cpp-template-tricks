#include "../yy/tuple/TupleElementCheck.hpp"
#include "../yy/tuple/TupleElementFind.hpp"

#include <gtest/gtest.h>

struct A
{
};

struct B: public A
{
};

TEST(TupleTests, IrrelevantTypes)
{
    constexpr auto val1 = yy::are_irrelevant_types<int, double>();
    EXPECT_TRUE(val1);
    // base and derived
    constexpr auto val2 = yy::are_irrelevant_types<A, B>();
    EXPECT_FALSE(val2);
    // derived and base
    constexpr auto val3 = yy::are_irrelevant_types<B, A>();
    EXPECT_FALSE(val3);
    // same type
    constexpr auto val4 = yy::are_irrelevant_types<int, int>();
    EXPECT_FALSE(val4);
}

TEST(TupleTests, IrrelevantTupleTypes)
{
    // empty tuple
    EXPECT_TRUE(yy::irrelevant_element_types<std::tuple<>>());
    // tuple with one element
    EXPECT_TRUE(yy::irrelevant_element_types<std::tuple<int>>());

    using ValidTuple = std::tuple<std::string, int, double>;
    EXPECT_TRUE(yy::irrelevant_element_types<ValidTuple>());

    using InvalidTuple = std::tuple<std::string, A, int, B>;
    EXPECT_FALSE(yy::irrelevant_element_types<InvalidTuple>());
}

TEST(TupleTests, FindType)
{
  // empty tuple, not found
  EXPECT_EQ(0, (yy::element_index<int, std::tuple<>>()));
  // tuple with one element, found
  EXPECT_EQ(0, (yy::element_index<int, std::tuple<int>>()));
  // tuple with one element, not found
  EXPECT_EQ(1, (yy::element_index<double, std::tuple<int>>()));

  // tuple with multiple elements, found
  EXPECT_EQ(2, (yy::element_index<B, std::tuple<int, A, B>>()));
  // tuple with multiple elements, not found
  EXPECT_EQ(3, (yy::element_index<double, std::tuple<int, A, B>>()));
}
