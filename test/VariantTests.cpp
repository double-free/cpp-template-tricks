#include "../yy/variant/VariantApply.hpp"

#include <gtest/gtest.h>

TEST(VariantTests, ApplyLambdaToVariant)
{
  std::variant<int, double> v;

  auto multiply2 = [](auto&& num) {
    num*=2;
  };

  // variant is an integer, it shall apply
  v = 3;
  EXPECT_TRUE(yy::try_apply(multiply2, v));
  EXPECT_EQ(6, std::get<int>(v));

  // variant is an double, it shall apply, too
  v = 5.0;
  EXPECT_TRUE(yy::try_apply(multiply2, v));
  EXPECT_DOUBLE_EQ(10.0, std::get<double>(v));
}
