#pragma warning(push)
#pragma warning(disable : 4365 5026 5027)
#include <gtest/gtest.h>
#pragma warning(pop)

#include "bdm/bdm.h"

TEST(MatTestConstruction, DefaultConstruct)
{
    bdm::mat4<int> m;
    bdm::vec4<int> v{};
    ASSERT_EQ(m[0], v);
    ASSERT_EQ(m[1], v);
    ASSERT_EQ(m[2], v);
    ASSERT_EQ(m[3], v);
}

TEST(MatTestConstruction, ConstructFromScalar)
{
    bdm::mat4<int> m{4};
    bdm::vec4<int> v{4};
    ASSERT_EQ(m[0], v);
    ASSERT_EQ(m[1], v);
    ASSERT_EQ(m[2], v);
    ASSERT_EQ(m[3], v);
}

TEST(MatTestConstruction, ConstructFromScalarValues)
{
    bdm::mat4<int> m{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    ASSERT_EQ(m[0], bdm::vec4<int>(1, 2, 3, 4));
    ASSERT_EQ(m[1], bdm::vec4<int>(5, 6, 7, 8));
    ASSERT_EQ(m[2], bdm::vec4<int>(9, 10, 11, 12));
    ASSERT_EQ(m[3], bdm::vec4<int>(13, 14, 15, 16));
}

TEST(MatTestConstruction, ConstructFromSingleVec)
{
    bdm::vec4<int> v{4};
    bdm::mat4<int> m{v};
    ASSERT_EQ(m[0], v);
    ASSERT_EQ(m[1], v);
    ASSERT_EQ(m[2], v);
    ASSERT_EQ(m[3], v);
}

TEST(MatTestConstruction, ConstructFromVec2s)
{
    bdm::vec2<int> v{2};
    bdm::mat2<int> m{v, v};
    ASSERT_EQ(m[0], v);
    ASSERT_EQ(m[1], v);
}

TEST(MatTestConstruction, ConstructFromVec3s)
{
    bdm::vec3<int> v{3};
    bdm::mat3<int> m{v, v, v};
    ASSERT_EQ(m[0], v);
    ASSERT_EQ(m[1], v);
    ASSERT_EQ(m[2], v);
}

TEST(MatTestConstruction, ConstructFromVec4s)
{
    bdm::vec4<int> v{4};
    bdm::mat4<int> m{v, v, v, v};
    ASSERT_EQ(m[0], v);
    ASSERT_EQ(m[1], v);
    ASSERT_EQ(m[2], v);
    ASSERT_EQ(m[3], v);
}

TEST(MatTestConstruction, ConstructSquareFromRows)
{
    bdm::vec4<int> v{1, 2, 3, 4};
    bdm::mat4<int> m = bdm::mat4<int>::from_rows(v, v, v, v);
    ASSERT_EQ(m[0], bdm::vec4<int>(1, 2, 3, 4));
    ASSERT_EQ(m[1], bdm::vec4<int>(1, 2, 3, 4));
    ASSERT_EQ(m[2], bdm::vec4<int>(1, 2, 3, 4));
    ASSERT_EQ(m[3], bdm::vec4<int>(1, 2, 3, 4));
}

TEST(MatTestConstruction, ConstructNonSquareFromRows)
{
    bdm::vec2<int> v{1, 2};
    bdm::mat<4, 2, int> m = bdm::mat<4, 2, int>::from_rows(v, v, v, v);
    ASSERT_EQ(m[0], bdm::vec2<int>(1, 2));
    ASSERT_EQ(m[1], bdm::vec2<int>(1, 2));
    ASSERT_EQ(m[2], bdm::vec2<int>(1, 2));
    ASSERT_EQ(m[3], bdm::vec2<int>(1, 2));
}

TEST(MatTestConstruction, ConstructSquareFromCols)
{
    bdm::vec4<int> v{1, 2, 3, 4};
    bdm::mat4<int> m = bdm::mat4<int>::from_cols(v, v, v, v);
    ASSERT_EQ(m[0], bdm::vec4<int>(1, 1, 1, 1));
    ASSERT_EQ(m[1], bdm::vec4<int>(2, 2, 2, 2));
    ASSERT_EQ(m[2], bdm::vec4<int>(3, 3, 3, 3));
    ASSERT_EQ(m[3], bdm::vec4<int>(4, 4, 4, 4));
}

TEST(MatTestConstruction, ConstructNonSquareFromCols)
{
    bdm::vec4<int> v{1, 2, 3, 4};
    bdm::mat<4, 2, int> m = bdm::mat<4, 2, int>::from_cols(v, v);
    ASSERT_EQ(m[0], bdm::vec2<int>(1, 1));
    ASSERT_EQ(m[1], bdm::vec2<int>(2, 2));
    ASSERT_EQ(m[2], bdm::vec2<int>(3, 3));
    ASSERT_EQ(m[3], bdm::vec2<int>(4, 4));
}

TEST(MatTestConstruction, ConstructFromMat)
{
    bdm::mat4<long int> m{bdm::mat4<int>{4}};
    bdm::vec4<long int> v{4};
    ASSERT_EQ(m[0], v);
    ASSERT_EQ(m[1], v);
    ASSERT_EQ(m[2], v);
    ASSERT_EQ(m[3], v);
}

TEST(MatTestConstruction, ConstructIdentityMat)
{
    auto m = bdm::mat4<int>::identity();
    ASSERT_EQ(m[0], bdm::vec4<int>(1, 0, 0, 0));
    ASSERT_EQ(m[1], bdm::vec4<int>(0, 1, 0, 0));
    ASSERT_EQ(m[2], bdm::vec4<int>(0, 0, 1, 0));
    ASSERT_EQ(m[3], bdm::vec4<int>(0, 0, 0, 1));
}

class MatTestOperators : public ::testing::Test
{
protected:
    void SetUp() override
    {
        v1 = bdm::vec4<int>{1, 2, 3, 4};
        v2 = bdm::vec4<int>{5, 6, 7, 8};
        v3 = bdm::vec4<int>{9, 10, 11, 12};
        v4 = bdm::vec4<int>{13, 14, 15, 16};

        m = bdm::mat4<int>{v1, v2, v3, v4};
        m_rev = bdm::mat4<int>{v4, v3, v2, v1};

        invertible = bdm::mat4<int>{bdm::vec4<int>{2, 3, 1, 5},
                                    bdm::vec4<int>{1, 0, 3, 1},
                                    bdm::vec4<int>{0, 2, -3, 2},
                                    bdm::vec4<int>{0, 2, 3, 1}};
    }

protected:
    bdm::vec4<int> v1;
    bdm::vec4<int> v2;
    bdm::vec4<int> v3;
    bdm::vec4<int> v4;
    bdm::mat4<int> m;
    bdm::mat4<int> m_rev;
    bdm::mat4<int> invertible;
};

TEST_F(MatTestOperators, AssignMat)
{
    bdm::vec4<long int> v{4};
    bdm::mat4<long int> lm;
    lm = bdm::mat4<int>{4};
    ASSERT_EQ(lm[0], v);
    ASSERT_EQ(lm[1], v);
    ASSERT_EQ(lm[2], v);
    ASSERT_EQ(lm[3], v);
}

TEST_F(MatTestOperators, TestSubscript)
{
    ASSERT_EQ(m[0], v1);
    ASSERT_EQ(m[1], v2);
    ASSERT_EQ(m[2], v3);
    ASSERT_EQ(m[3], v4);
}

TEST_F(MatTestOperators, TestLookup)
{
    ASSERT_EQ(m(0, 0), 1);
    ASSERT_EQ(m(3, 3), 16);
    ASSERT_EQ(m(1, 2), 7);
    ASSERT_EQ(m(2, 0), 9);
}

TEST_F(MatTestOperators, TestIncrement)
{
    ++m;
    ASSERT_EQ(m[0], v1 + 1);
    ASSERT_EQ(m[1], v2 + 1);
    ASSERT_EQ(m[2], v3 + 1);
    ASSERT_EQ(m[3], v4 + 1);
}

TEST_F(MatTestOperators, TestDecrement)
{
    --m;
    ASSERT_EQ(m[0], v1 - 1);
    ASSERT_EQ(m[1], v2 - 1);
    ASSERT_EQ(m[2], v3 - 1);
    ASSERT_EQ(m[3], v4 - 1);
}

TEST_F(MatTestOperators, TestCompoundAssignmentAddScalar)
{
    m += 2;
    ASSERT_EQ(m[0], v1 + 2);
    ASSERT_EQ(m[1], v2 + 2);
    ASSERT_EQ(m[2], v3 + 2);
    ASSERT_EQ(m[3], v4 + 2);
}

TEST_F(MatTestOperators, TestCompoundAssignmentAddInitializer)
{
    m += {v1, v2, v3, v4};
    ASSERT_EQ(m[0], v1 + v1);
    ASSERT_EQ(m[1], v2 + v2);
    ASSERT_EQ(m[2], v3 + v3);
    ASSERT_EQ(m[3], v4 + v4);
}

TEST_F(MatTestOperators, TestCompoundAssignmentAddMat)
{
    m += m_rev;
    ASSERT_EQ(m[0], v1 + v4);
    ASSERT_EQ(m[1], v2 + v3);
    ASSERT_EQ(m[2], v3 + v2);
    ASSERT_EQ(m[3], v4 + v1);
}

TEST_F(MatTestOperators, TestCompoundAssignmentSubtractScalar)
{
    m -= 2;
    ASSERT_EQ(m[0], v1 - 2);
    ASSERT_EQ(m[1], v2 - 2);
    ASSERT_EQ(m[2], v3 - 2);
    ASSERT_EQ(m[3], v4 - 2);
}

TEST_F(MatTestOperators, TestCompoundAssignmentSubtractInitializer)
{
    m -= {v4, v3, v2, v1};
    ASSERT_EQ(m[0], v1 - v4);
    ASSERT_EQ(m[1], v2 - v3);
    ASSERT_EQ(m[2], v3 - v2);
    ASSERT_EQ(m[3], v4 - v1);
}

TEST_F(MatTestOperators, TestCompoundAssignmentSubtractMat)
{
    m -= m_rev;
    ASSERT_EQ(m[0], v1 - v4);
    ASSERT_EQ(m[1], v2 - v3);
    ASSERT_EQ(m[2], v3 - v2);
    ASSERT_EQ(m[3], v4 - v1);
}

TEST_F(MatTestOperators, TestCompoundAssignmentMultiplyScalar)
{
    m *= 2;
    ASSERT_EQ(m[0], v1 * 2);
    ASSERT_EQ(m[1], v2 * 2);
    ASSERT_EQ(m[2], v3 * 2);
    ASSERT_EQ(m[3], v4 * 2);
}

TEST_F(MatTestOperators, TestCompoundAssignmentMultiplyInitializer)
{
    m *= {v4, v3, v2, v1};
    ASSERT_EQ(m[0], bdm::vec4<int>(50, 60, 70, 80));
    ASSERT_EQ(m[1], bdm::vec4<int>(162, 188, 214, 240));
    ASSERT_EQ(m[2], bdm::vec4<int>(274, 316, 358, 400));
    ASSERT_EQ(m[3], bdm::vec4<int>(386, 444, 502, 560));
}

TEST_F(MatTestOperators, TestCompoundAssignmentMultiplyMat)
{
    m *= m_rev;
    ASSERT_EQ(m[0], bdm::vec4<int>(50, 60, 70, 80));
    ASSERT_EQ(m[1], bdm::vec4<int>(162, 188, 214, 240));
    ASSERT_EQ(m[2], bdm::vec4<int>(274, 316, 358, 400));
    ASSERT_EQ(m[3], bdm::vec4<int>(386, 444, 502, 560));
}

TEST_F(MatTestOperators, TestCompoundAssignmentDivideScalar)
{
    m /= 2;
    ASSERT_EQ(m[0], v1 / 2);
    ASSERT_EQ(m[1], v2 / 2);
    ASSERT_EQ(m[2], v3 / 2);
    ASSERT_EQ(m[3], v4 / 2);
}

#define ASSERT_MAT_NEAR(m1, m2, threshold)                                     \
    ASSERT_EQ(m1.rows, m2.rows);                                               \
    ASSERT_EQ(m1.cols, m2.cols);                                               \
    for (bdm::dim_t ri = 0u; ri < m1.rows; ++ri)                               \
    {                                                                          \
        for (bdm::dim_t ci = 0u; ci < m1.rows; ++ci)                           \
        {                                                                      \
            ASSERT_NEAR(m1[ri][ci], m2[ri][ci], threshold);                    \
        }                                                                      \
    }

TEST_F(MatTestOperators, TestCompoundAssignmentDivideInitializer)
{
    bdm::mat4<float> fm{bdm::vec4<float>{0.6f, 0.2f, 0.3f, 0.4f},
                        bdm::vec4<float>{0.2f, 0.7f, 0.5f, 0.3f},
                        bdm::vec4<float>{0.3f, 0.5f, 0.7f, 0.2f},
                        bdm::vec4<float>{0.4f, 0.3f, 0.2f, 0.6f}};
    fm /= {fm[0], fm[1], fm[2], fm[3]};
    bdm::mat4<float>
        expected{bdm::vec4<float>{1.0f, -5.96046e-08f, 2.38419e-07f, -2.38419e-07f},
                 bdm::vec4<float>{-1.19209e-07f, 1.0f, 4.47035e-07f, -1.19209e-07f},
                 bdm::vec4<float>{-1.19209e-07f, 2.98023e-07f, 1.0f, -2.98023e-07f},
                 bdm::vec4<float>{-1.19209e-07f, 0.0f, 2.98023e-07f, 1.0f}};
    ASSERT_MAT_NEAR(fm, expected, 0.0001f);
}

TEST_F(MatTestOperators, TestCompoundAssignmentDivideMat)
{
    bdm::mat4<float> fm{bdm::vec4<float>{0.6f, 0.2f, 0.3f, 0.4f},
                        bdm::vec4<float>{0.2f, 0.7f, 0.5f, 0.3f},
                        bdm::vec4<float>{0.3f, 0.5f, 0.7f, 0.2f},
                        bdm::vec4<float>{0.4f, 0.3f, 0.2f, 0.6f}};
    bdm::mat4<float> divisor{fm};
    fm /= divisor;
    bdm::mat4<float>
        expected{bdm::vec4<float>{1.0f, -5.96046e-08f, 2.38419e-07f, -2.38419e-07f},
                 bdm::vec4<float>{-1.19209e-07f, 1.0f, 4.47035e-07f, -1.19209e-07f},
                 bdm::vec4<float>{-1.19209e-07f, 2.98023e-07f, 1.0f, -2.98023e-07f},
                 bdm::vec4<float>{-1.19209e-07f, 0.0f, 2.98023e-07f, 1.0f}};
    ASSERT_MAT_NEAR(fm, expected, 0.0001f);
}

TEST_F(MatTestOperators, TestUnaryPlus)
{
    bdm::vec4<int> v{-4, -3, 5, 6};
    bdm::mat4<int> m1{v, v2, v3, v4};
    bdm::mat4<int> m2 = +m1;
    ASSERT_EQ(m2[0], v);
    ASSERT_EQ(m2[1], v2);
    ASSERT_EQ(m2[2], v3);
    ASSERT_EQ(m2[3], v4);
}

TEST_F(MatTestOperators, TestUnaryMinus)
{
    bdm::mat4<int> m1 = -m;
    ASSERT_EQ(m1[0], -v1);
    ASSERT_EQ(m1[1], -v2);
    ASSERT_EQ(m1[2], -v3);
    ASSERT_EQ(m1[3], -v4);
}

TEST_F(MatTestOperators, TestEquality)
{
    auto m1 = m;
    ASSERT_TRUE(m == m1);
    ASSERT_FALSE(m == m_rev);
}

TEST_F(MatTestOperators, TestNonEquality)
{
    auto m1 = m;
    ASSERT_FALSE(m != m1);
    ASSERT_TRUE(m != m_rev);
}

TEST_F(MatTestOperators, TestAddScalarMat)
{
    auto res = 2 + m;
    ASSERT_EQ(res[0], v1 + 2);
    ASSERT_EQ(res[1], v2 + 2);
    ASSERT_EQ(res[2], v3 + 2);
    ASSERT_EQ(res[3], v4 + 2);
}

TEST_F(MatTestOperators, TestAddMatScalar)
{
    auto res = m + 2;
    ASSERT_EQ(res[0], v1 + 2);
    ASSERT_EQ(res[1], v2 + 2);
    ASSERT_EQ(res[2], v3 + 2);
    ASSERT_EQ(res[3], v4 + 2);
}

TEST_F(MatTestOperators, TestAddMatMat)
{
    auto res = m + m_rev;
    ASSERT_EQ(res[0], v1 + v4);
    ASSERT_EQ(res[1], v2 + v3);
    ASSERT_EQ(res[2], v3 + v2);
    ASSERT_EQ(res[3], v4 + v1);
}

TEST_F(MatTestOperators, TestSubtractScalarMat)
{
    auto res = 2 - m;
    ASSERT_EQ(res[0], 2 - v1);
    ASSERT_EQ(res[1], 2 - v2);
    ASSERT_EQ(res[2], 2 - v3);
    ASSERT_EQ(res[3], 2 - v4);
}

TEST_F(MatTestOperators, TestSubtractMatScalar)
{
    auto res = m - 2;
    ASSERT_EQ(res[0], v1 - 2);
    ASSERT_EQ(res[1], v2 - 2);
    ASSERT_EQ(res[2], v3 - 2);
    ASSERT_EQ(res[3], v4 - 2);
}

TEST_F(MatTestOperators, TestSubtractMatMat)
{
    auto res = m - m_rev;
    ASSERT_EQ(res[0], v1 - v4);
    ASSERT_EQ(res[1], v2 - v3);
    ASSERT_EQ(res[2], v3 - v2);
    ASSERT_EQ(res[3], v4 - v1);
}

TEST_F(MatTestOperators, TestMultiplyScalarMat)
{
    auto res = 2 * m;
    ASSERT_EQ(res[0], v1 * 2);
    ASSERT_EQ(res[1], v2 * 2);
    ASSERT_EQ(res[2], v3 * 2);
    ASSERT_EQ(res[3], v4 * 2);
}

TEST_F(MatTestOperators, TestMultiplyMatScalar)
{
    auto res = m * 2;
    ASSERT_EQ(res[0], v1 * 2);
    ASSERT_EQ(res[1], v2 * 2);
    ASSERT_EQ(res[2], v3 * 2);
    ASSERT_EQ(res[3], v4 * 2);
}

TEST_F(MatTestOperators, TestMultiplyMatMat)
{
    auto res = m * m_rev;
    ASSERT_EQ(res[0], bdm::vec4<int>(50, 60, 70, 80));
    ASSERT_EQ(res[1], bdm::vec4<int>(162, 188, 214, 240));
    ASSERT_EQ(res[2], bdm::vec4<int>(274, 316, 358, 400));
    ASSERT_EQ(res[3], bdm::vec4<int>(386, 444, 502, 560));
}

TEST_F(MatTestOperators, TestMultiplyMatVec)
{
    bdm::vec4<int> v{2, 3, 4, 5};
    auto res = m * v;
    ASSERT_EQ(res, bdm::vec4<int>(40, 96, 152, 208));
}

TEST_F(MatTestOperators, TestMultiplyVecMat)
{
    bdm::vec4<int> v{2, 3, 4, 5};
    auto res = v * m;
    ASSERT_EQ(res, bdm::vec4<int>(118, 132, 146, 160));
}

TEST_F(MatTestOperators, TestDivideScalarMat)
{
    auto res = 2 / m;
    ASSERT_EQ(res[0], 2 / v1);
    ASSERT_EQ(res[1], 2 / v2);
    ASSERT_EQ(res[2], 2 / v3);
    ASSERT_EQ(res[3], 2 / v4);
}

TEST_F(MatTestOperators, TestDivideMatScalar)
{
    auto res = m / 2;
    ASSERT_EQ(res[0], v1 / 2);
    ASSERT_EQ(res[1], v2 / 2);
    ASSERT_EQ(res[2], v3 / 2);
    ASSERT_EQ(res[3], v4 / 2);
}

TEST_F(MatTestOperators, TestDivideMatMat)
{
    const bdm::mat4<float> fm{bdm::vec4<float>{0.6f, 0.2f, 0.3f, 0.4f},
                              bdm::vec4<float>{0.2f, 0.7f, 0.5f, 0.3f},
                              bdm::vec4<float>{0.3f, 0.5f, 0.7f, 0.2f},
                              bdm::vec4<float>{0.4f, 0.3f, 0.2f, 0.6f}};
    const bdm::mat4<float> divisor{fm[0], fm[1], fm[2], fm[3]};
    auto res = fm / divisor;
    bdm::mat4<float>
        expected{bdm::vec4<float>{1.0f, -5.96046e-08f, 2.38419e-07f, -2.38419e-07f},
                 bdm::vec4<float>{-1.19209e-07f, 1.0f, 4.47035e-07f, -1.19209e-07f},
                 bdm::vec4<float>{-1.19209e-07f, 2.98023e-07f, 1.0f, -2.98023e-07f},
                 bdm::vec4<float>{-1.19209e-07f, 0.0f, 2.98023e-07f, 1.0f}};
    ASSERT_MAT_NEAR(res, expected, 0.0001f);
}

TEST_F(MatTestOperators, TestDivideMatVec)
{
    bdm::vec4<int> v{2, 3, 4, 5};
    auto res = invertible / v;
    ASSERT_EQ(res, bdm::vec4<int>(-176, -87, 20, 119));
}

TEST_F(MatTestOperators, TestDivideVecMat)
{
    bdm::vec4<int> v{2, 3, 4, 5};
    auto res = v / invertible;
    ASSERT_EQ(res, bdm::vec4<int>(-5, 12, 9, 0));
}

class MatTestMembers : public ::testing::Test
{
protected:
    void SetUp() override
    {
        v1 = bdm::vec4<int>{1, 2, 3, 4};
        v2 = bdm::vec4<int>{5, 6, 7, 8};
        v3 = bdm::vec4<int>{9, 10, 11, 12};
        v4 = bdm::vec4<int>{13, 14, 15, 16};
        m = bdm::mat4<int>{v1, v2, v3, v4};
    }

protected:
    bdm::vec4<int> v1;
    bdm::vec4<int> v2;
    bdm::vec4<int> v3;
    bdm::vec4<int> v4;
    bdm::mat4<int> m;
};

TEST_F(MatTestMembers, TestRow)
{
    ASSERT_EQ(m.row(0), v1);
    ASSERT_EQ(m.row(1), v2);
    ASSERT_EQ(m.row(2), v3);
    ASSERT_EQ(m.row(3), v4);
}

TEST_F(MatTestMembers, TestCol)
{
    ASSERT_EQ(m.col(0), bdm::vec4<int>(1, 5, 9, 13));
    ASSERT_EQ(m.col(1), bdm::vec4<int>(2, 6, 10, 14));
    ASSERT_EQ(m.col(2), bdm::vec4<int>(3, 7, 11, 15));
    ASSERT_EQ(m.col(3), bdm::vec4<int>(4, 8, 12, 16));
}

TEST_F(MatTestMembers, TestSubMatSugarApiSquare)
{
    bdm::mat2<int> sm2 = m.submat<2, 2>(1, 1);
    ASSERT_EQ(sm2[0], bdm::vec2<int>(6, 7));
    ASSERT_EQ(sm2[1], bdm::vec2<int>(10, 11));

    bdm::mat3<int> sm3 = m.submat<3, 3>(1, 0);
    ASSERT_EQ(sm3[0], bdm::vec3<int>(5, 6, 7));
    ASSERT_EQ(sm3[1], bdm::vec3<int>(9, 10, 11));
    ASSERT_EQ(sm3[2], bdm::vec3<int>(13, 14, 15));
}

TEST_F(MatTestMembers, TestSubMatSquare)
{
    // Create 2x2 matrix extracted from the center of the original 4x4 matrix
    bdm::mat2<int> sm2 = m.submat(bdm::dim_seq<1, 2>{}, bdm::dim_seq<1, 2>{});
    ASSERT_EQ(sm2[0], bdm::vec2<int>(6, 7));
    ASSERT_EQ(sm2[1], bdm::vec2<int>(10, 11));

    // Create 3x3 matrix with second row and first column of original dropped
    bdm::mat3<int> sm3 = m.submat(bdm::dim_seq<1, 2, 3>{},
                                  bdm::dim_seq<0, 1, 2>{});  //<3, 3>(1, 0);
    ASSERT_EQ(sm3[0], bdm::vec3<int>(5, 6, 7));
    ASSERT_EQ(sm3[1], bdm::vec3<int>(9, 10, 11));
    ASSERT_EQ(sm3[2], bdm::vec3<int>(13, 14, 15));
}

TEST_F(MatTestMembers, TestSubMatNonSquare)
{
    // Create 3x4 matrix with the second row from the original ignored
    bdm::mat<3, 4, int> sm34 = m.submat(bdm::dim_seq<0, 2, 3>{},
                                        bdm::dim_seq<0, 1, 2, 3>{});
    ASSERT_EQ(sm34[0], bdm::vec4<int>(1, 2, 3, 4));
    ASSERT_EQ(sm34[1], bdm::vec4<int>(9, 10, 11, 12));
    ASSERT_EQ(sm34[2], bdm::vec4<int>(13, 14, 15, 16));

    // Create 4x3 matrix with the second column from the original ignored
    bdm::mat<4, 3, int> sm43 = m.submat(bdm::dim_seq<0, 1, 2, 3>{},
                                        bdm::dim_seq<0, 2, 3>{});
    ASSERT_EQ(sm43[0], bdm::vec3<int>(1, 3, 4));
    ASSERT_EQ(sm43[1], bdm::vec3<int>(5, 7, 8));
    ASSERT_EQ(sm43[2], bdm::vec3<int>(9, 11, 12));
    ASSERT_EQ(sm43[3], bdm::vec3<int>(13, 15, 16));
}

TEST_F(MatTestMembers, TestApplyMat3)
{
    std::size_t count{};
    bdm::mat3<int> m1{bdm::vec3<int>{1, 2, 3},
                      bdm::vec3<int>{4, 5, 6},
                      bdm::vec3<int>{7, 8, 9}};
    m1.apply([&](bdm::mat3<int>::row_type& row) {
        ASSERT_EQ(row, m1[count]);
        ++count;
    });
    ASSERT_EQ(count, 3u);
}

TEST_F(MatTestMembers, TestApplyMat4)
{
    std::size_t count{};
    m.apply([&](bdm::mat4<int>::row_type& row) {
        ASSERT_EQ(row, m[count]);
        ++count;
    });
    ASSERT_EQ(count, 4u);
}

TEST_F(MatTestMembers, TestApplyMatMat3)
{
    std::size_t count{};
    bdm::mat3<int> im3{bdm::vec3<int>{1, 2, 3},
                       bdm::vec3<int>{4, 5, 6},
                       bdm::vec3<int>{7, 8, 9}};
    bdm::mat3<double> dm3{2.0};
    im3.apply(
        [&](bdm::mat3<int>::row_type& irow, const bdm::mat3<double>::row_type& drow) {
            ASSERT_EQ(irow, im3[count]);
            ASSERT_EQ(drow, dm3[count]);
            ++count;
        },
        dm3);
    ASSERT_EQ(count, 3u);
}

TEST_F(MatTestMembers, TestApplyMatMat4)
{
    std::size_t count{};
    bdm::mat4<double> dm4{2.0};
    m.apply(
        [&](bdm::mat4<int>::row_type& irow, const bdm::mat4<double>::row_type& drow) {
            ASSERT_EQ(irow, m[count]);
            ASSERT_EQ(drow, dm4[count]);
            ++count;
        },
        dm4);
    ASSERT_EQ(count, 4u);
}

TEST_F(MatTestMembers, TestTranspose)
{
    auto m_copy = m;
    m.transpose();
    ASSERT_EQ(m[0], m_copy.col(0));
    ASSERT_EQ(m[1], m_copy.col(1));
    ASSERT_EQ(m[2], m_copy.col(2));
    ASSERT_EQ(m[3], m_copy.col(3));
}
