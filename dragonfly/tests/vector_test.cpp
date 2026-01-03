#include <gtest/gtest.h>

#include <df/vector.h>

namespace {

TEST(VectorTest, DefaultConstructedIsZero) {
  df::Vector v;
  EXPECT_FLOAT_EQ(v.getX(), 0.0f);
  EXPECT_FLOAT_EQ(v.getY(), 0.0f);
}

TEST(VectorTest, ConstructsWithValues) {
  df::Vector v{3.0f, -4.5f};
  EXPECT_FLOAT_EQ(v.getX(), 3.0f);
  EXPECT_FLOAT_EQ(v.getY(), -4.5f);
}

TEST(VectorTest, SettersWork) {
  df::Vector v;
  v.setX(1.5f);
  v.setY(2.5f);
  EXPECT_FLOAT_EQ(v.getX(), 1.5f);
  EXPECT_FLOAT_EQ(v.getY(), 2.5f);
}

TEST(VectorTest, AdditionCreatesNewVector) {
  df::Vector a{1.0f, 2.0f};
  df::Vector b{3.0f, 4.0f};

  df::Vector c = a + b;

  EXPECT_FLOAT_EQ(c.getX(), 4.0f);
  EXPECT_FLOAT_EQ(c.getY(), 6.0f);
}

TEST(VectorTest, PlusEqualsMutatesLeftHandSide) {
  df::Vector a{1.0f, 2.0f};
  df::Vector b{3.0f, 4.0f};

  a += b;

  EXPECT_FLOAT_EQ(a.getX(), 4.0f);
  EXPECT_FLOAT_EQ(a.getY(), 6.0f);
}

TEST(VectorTest, EqualityOperatorsWork) {
  df::Vector a{1.0f, 2.0f};
  df::Vector b{1.0f, 2.0f};
  df::Vector c{2.0f, 3.0f};

  EXPECT_TRUE(a == b);
  EXPECT_FALSE(a != b);
  EXPECT_TRUE(a != c);
}

}  // namespace
