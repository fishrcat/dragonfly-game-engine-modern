// vector_test.cpp — Unit tests for 2D vector object and math overrides

#include "vector.h"

#include <gtest/gtest.h>

namespace df {

// Helper for concise vector comparisons
inline void expectVectorEQ(const Vector& v, const float x, const float y) {
    EXPECT_FLOAT_EQ(v.x, x);
    EXPECT_FLOAT_EQ(v.y, y);
}

TEST(VectorTest, Constructors) {
    expectVectorEQ(Vector{}, 0.F, 0.F);
    expectVectorEQ(Vector(3.F, -4.F), 3.F, -4.F);
}

TEST(VectorTest, MagnitudeAndNormalize) {
    Vector v(3.F, 4.F);
    EXPECT_FLOAT_EQ(v.magnitude(), 5.F);

    v.normalize();
    EXPECT_NEAR(v.magnitude(), 1.F, 1e-6F);

    Vector zero(0.F, 0.F);
    zero.normalize();
    expectVectorEQ(zero, 0.F, 0.F);
}

TEST(VectorTest, UnaryAndBinaryOperators) {
    constexpr Vector a(1.F, 2.F);
    constexpr Vector b(3.F, 4.F);

    expectVectorEQ(a + b, 4.F, 6.F);
    expectVectorEQ(b - a, 2.F, 2.F);
    expectVectorEQ(-a, -1.F, -2.F);
}

TEST(VectorTest, ScalarOperators) {
    constexpr Vector v(2.F, -3.F);
    expectVectorEQ(v * 2.F, 4.F, -6.F);
    expectVectorEQ((v * 2.F) / 2.F, 2.F, -3.F);
}

TEST(VectorTest, CompoundAssignments) {
    Vector v(1.F, 2.F);
    constexpr Vector w(3.F, 4.F);

    v += w;
    expectVectorEQ(v, 4.F, 6.F);
    v -= w;
    expectVectorEQ(v, 1.F, 2.F);
    v *= 2.F;
    expectVectorEQ(v, 2.F, 4.F);
    v /= 2.F;
    expectVectorEQ(v, 1.F, 2.F);
}

TEST(VectorTest, Comparisons) {
    constexpr Vector a(1.F, 2.F);
    constexpr Vector b(1.F, 2.F);
    constexpr Vector c(2.F, 3.F);

    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a != b);
    EXPECT_TRUE(a != c);
    EXPECT_FALSE(a == c);
}

}  // namespace df
