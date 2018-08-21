#pragma warning(push)
#pragma warning(disable : 4365 5026 5027)
#include <gtest/gtest.h>
#pragma warning(pop)

#include "bdm/bdm.h"

TEST(TestComputations, NegateVec)
{
    bdm::vec4<int> v{-2, -5, 1, 3};
    ASSERT_EQ(-v, bdm::vec4<int>(2, 5, -1, -3));
}

TEST(TestComputations, NegateMat)
{
    bdm::vec4<int> v{-2, -5, 1, 3};
    bdm::mat4<int> m{v};
    auto nm = -m;
    bdm::vec4<int> expected{2, 5, -1, -3};
    ASSERT_EQ(nm[0], expected);
    ASSERT_EQ(nm[1], expected);
    ASSERT_EQ(nm[2], expected);
    ASSERT_EQ(nm[3], expected);
}

TEST(TestComputations, CrossProduct)
{
    bdm::vec3<int> v1{1, 2, 3};
    bdm::vec3<int> v2{4, 5, 6};
    auto res = bdm::cross(v1, v2);
    ASSERT_EQ(res, bdm::vec3<int>(-3, 6, -3));
}

TEST(TestComputations, DotProduct)
{
    bdm::vec4<int> v1{1, 2, 3, 4};
    bdm::vec4<int> v2{5, 6, 7, 8};
    auto res = bdm::dot(v1, v2);
    ASSERT_EQ(res, 70);
}

TEST(TestComputations, LengthVec)
{
    bdm::vec4<float> v{0.5f, -0.78f, 0.12f, 1.0f};
    ASSERT_NEAR(bdm::length(v), 1.3685f, 0.0001f);
}

TEST(TestComputations, NormalizeVec)
{
    bdm::vec4<float> v{0.5f, -0.5f, -0.2f, 1.0f};
    auto normalized = bdm::normalize(v);
    ASSERT_NEAR(normalized[0], 0.4029f, 0.0001f);
    ASSERT_NEAR(normalized[1], -0.4029f, 0.0001f);
    ASSERT_NEAR(normalized[2], -0.1611f, 0.0001f);
    ASSERT_NEAR(normalized[3], 0.8058f, 0.0001f);
    // Make sure original vector remains untouched
    ASSERT_NEAR(v[0], 0.5f, 0.0001f);
    ASSERT_NEAR(v[1], -0.5f, 0.0001f);
    ASSERT_NEAR(v[2], -0.2f, 0.0001f);
    ASSERT_NEAR(v[3], 1.0f, 0.0001f);
}

TEST(TestComputations, TransposeSquare)
{
    bdm::vec4<int> v{1, 2, 3, 4};
    bdm::mat4<int> m{v};
    auto transposed = bdm::transpose(m);
    ASSERT_EQ(transposed[0], bdm::vec4<int>(1, 1, 1, 1));
    ASSERT_EQ(transposed[1], bdm::vec4<int>(2, 2, 2, 2));
    ASSERT_EQ(transposed[2], bdm::vec4<int>(3, 3, 3, 3));
    ASSERT_EQ(transposed[3], bdm::vec4<int>(4, 4, 4, 4));
}

TEST(TestComputations, TransposeNonSquare)
{
    bdm::mat<4, 2, int> m{bdm::vec2<int>{1, 1},
                          bdm::vec2<int>{2, 2},
                          bdm::vec2<int>{3, 3},
                          bdm::vec2<int>{4, 4}};
    bdm::mat<2, 4, int> transposed = bdm::transpose(m);
    ASSERT_EQ(transposed[0], bdm::vec4<int>(1, 2, 3, 4));
    ASSERT_EQ(transposed[1], bdm::vec4<int>(1, 2, 3, 4));
}

TEST(TestComputations, DeterminantMat2)
{
    bdm::mat2<int> m{bdm::vec2<int>{1, 2}, bdm::vec2<int>{3, 4}};
    auto res = bdm::determinant(m);
    ASSERT_EQ(res, -2);
}

TEST(TestComputations, DeterminantMat3)
{
    bdm::mat3<int> m{bdm::vec3<int>{2, -3, 1},
                     bdm::vec3<int>{2, 0, -1},
                     bdm::vec3<int>{1, 4, 5}};
    auto res = bdm::determinant(m);
    ASSERT_EQ(res, 49);
}

TEST(TestComputations, DeterminantMat4)
{
    bdm::mat4<int> m{bdm::vec4<int>{4, 3, 2, 2},
                     bdm::vec4<int>{0, 1, -3, 3},
                     bdm::vec4<int>{0, -1, 3, 3},
                     bdm::vec4<int>{0, 3, 1, 1}};
    auto res = bdm::determinant(m);
    ASSERT_EQ(res, -240);
}

TEST(TestComputations, DeterminantMat5)
{
    bdm::mat<5, 5, int> m{bdm::vec<5, int>{1, 2, 3, 3, 5},
                          bdm::vec<5, int>{3, 2, 1, 2, 2},
                          bdm::vec<5, int>{1, 2, 3, 4, 5},
                          bdm::vec<5, int>{-1, 0, -8, 1, 2},
                          bdm::vec<5, int>{7, 2, 1, 3, 2}};
    auto res = bdm::determinant(m);
    ASSERT_EQ(res, -224);
}

TEST(TestComputations, InverseMat3)
{
    bdm::mat3<int> m{bdm::vec3<int>{1, 2, 3},
                     bdm::vec3<int>{0, 1, 4},
                     bdm::vec3<int>{5, 6, 0}};
    auto mi = bdm::inverse(m);
    ASSERT_EQ(mi[0], bdm::vec3<int>(-24, 18, 5));
    ASSERT_EQ(mi[1], bdm::vec3<int>(20, -15, -4));
    ASSERT_EQ(mi[2], bdm::vec3<int>(-5, 4, 1));
}

TEST(TestComputations, InverseMat4)
{
    bdm::mat4<float> m{bdm::vec4<float>{0.6f, 0.2f, 0.3f, 0.4f},
                       bdm::vec4<float>{0.2f, 0.7f, 0.5f, 0.3f},
                       bdm::vec4<float>{0.3f, 0.5f, 0.7f, 0.2f},
                       bdm::vec4<float>{0.4f, 0.3f, 0.2f, 0.6f}};
    auto mi = bdm::inverse(m);
    bdm::mat4<float>
        expected{bdm::vec4<float>{3.9649f, 1.4035f, -1.9298f, -2.7017f},
                 bdm::vec4<float>{1.4035f, 3.8596f, -2.8070f, -1.9298f},
                 bdm::vec4<float>{-1.9298f, -2.8070f, 3.8596f, 1.4035f},
                 bdm::vec4<float>{-2.7017f, -1.9298f, 1.4035f, 3.9649f}};
    for (bdm::dim_t y = 0u; y < m.rows; ++y)
    {
        for (bdm::dim_t x = 0u; x < m.cols; ++x)
        {
            ASSERT_NEAR(mi[y][x], expected[y][x], 0.0001f);
        }
    }
}

TEST(TestComputations, InverseMat7)
{
    bdm::mat<7, 7, float>
        m{bdm::vec<7, float>{0.6f, 0.2f, 0.3f, 0.4f, 0.5f, 0.7f, 0.8f},
          bdm::vec<7, float>{0.2f, 0.7f, 0.5f, 0.3f, 0.4f, 0.1f, 0.6f},
          bdm::vec<7, float>{0.3f, 0.5f, 0.7f, 0.2f, 0.6f, 0.4f, 0.1f},
          bdm::vec<7, float>{0.4f, 0.3f, 0.2f, 0.6f, 0.1f, 0.5f, 0.7f},
          bdm::vec<7, float>{0.5f, 0.4f, 0.6f, 0.1f, 0.2f, 0.8f, 0.3f},
          bdm::vec<7, float>{0.7f, 0.1f, 0.4f, 0.5f, 0.8f, 0.3f, 0.2f},
          bdm::vec<7, float>{0.8f, 0.6f, 0.1f, 0.7f, 0.3f, 0.2f, 0.4f}};
    auto identity = m * bdm::inverse(m);
    auto expected = decltype(m)::identity();
    for (bdm::dim_t y = 0u; y < m.rows; ++y)
    {
        for (bdm::dim_t x = 0u; x < m.cols; ++x)
        {
            ASSERT_NEAR(identity[y][x], expected[y][x], 0.0001f);
        }
    }
}
