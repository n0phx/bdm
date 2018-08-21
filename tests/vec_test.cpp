#pragma warning(push)
#pragma warning(disable : 4365 5026 5027)
#include <gtest/gtest.h>
#pragma warning(pop)

#include "bdm/bdm.h"

TEST(VecTestConstruction, DefaultConstructVec2)
{
    bdm::vec2<int> v;
    ASSERT_EQ(v.x, 0);
    ASSERT_EQ(v.y, 0);
}

TEST(VecTestConstruction, DefaultConstructVec3)
{
    bdm::vec3<int> v;
    ASSERT_EQ(v.x, 0);
    ASSERT_EQ(v.y, 0);
    ASSERT_EQ(v.z, 0);
}

TEST(VecTestConstruction, DefaultConstructVec4)
{
    bdm::vec4<int> v;
    ASSERT_EQ(v.x, 0);
    ASSERT_EQ(v.y, 0);
    ASSERT_EQ(v.z, 0);
    ASSERT_EQ(v.w, 0);
}

TEST(VecTestConstruction, DefaultConstructVecArbitrary)
{
    bdm::vec<5, int> v;
    ASSERT_EQ(v[0], 0);
    ASSERT_EQ(v[1], 0);
    ASSERT_EQ(v[2], 0);
    ASSERT_EQ(v[3], 0);
    ASSERT_EQ(v[4], 0);
}

TEST(VecTestConstruction, ConstructFromArgsVec2)
{
    bdm::vec2<int> v{1, 2};
    ASSERT_EQ(v.x, 1);
    ASSERT_EQ(v.y, 2);
}

TEST(VecTestConstruction, ConstructFromArgsVec3)
{
    bdm::vec3<int> v{1, 2, 3};
    ASSERT_EQ(v.x, 1);
    ASSERT_EQ(v.y, 2);
    ASSERT_EQ(v.z, 3);
}

TEST(VecTestConstruction, ConstructFromArgsVec4)
{
    bdm::vec4<int> v{1, 2, 3, 4};
    ASSERT_EQ(v.x, 1);
    ASSERT_EQ(v.y, 2);
    ASSERT_EQ(v.z, 3);
    ASSERT_EQ(v.w, 4);
}

TEST(VecTestConstruction, ConstructFromArgsVecArbitrary)
{
    bdm::vec<5, int> v{1, 2, 3, 4, 5};
    ASSERT_EQ(v[0], 1);
    ASSERT_EQ(v[1], 2);
    ASSERT_EQ(v[2], 3);
    ASSERT_EQ(v[3], 4);
    ASSERT_EQ(v[4], 5);
}

TEST(VecTestConstruction, ConstructFromVec2)
{
    bdm::vec2<long int> v{bdm::vec2<int>{1, 2}};
    ASSERT_EQ(v.x, 1);
    ASSERT_EQ(v.y, 2);
}

TEST(VecTestConstruction, ConstructFromVec3)
{
    bdm::vec3<long int> v{bdm::vec3<int>{1, 2, 3}};
    ASSERT_EQ(v.x, 1);
    ASSERT_EQ(v.y, 2);
    ASSERT_EQ(v.z, 3);
}

TEST(VecTestConstruction, ConstructFromVec4)
{
    bdm::vec4<long int> v{bdm::vec4<int>{1, 2, 3, 4}};
    ASSERT_EQ(v.x, 1);
    ASSERT_EQ(v.y, 2);
    ASSERT_EQ(v.z, 3);
    ASSERT_EQ(v.w, 4);
}

TEST(VecTestConstruction, ConstructFromVecArbitrary)
{
    bdm::vec<5, long int> v{bdm::vec<5, int>{1, 2, 3, 4, 5}};
    ASSERT_EQ(v[0], 1);
    ASSERT_EQ(v[1], 2);
    ASSERT_EQ(v[2], 3);
    ASSERT_EQ(v[3], 4);
    ASSERT_EQ(v[4], 5);
}

TEST(VecTestConstruction, ConstructFromScalarVec2)
{
    bdm::vec2<int> v{42};
    ASSERT_EQ(v.x, 42);
    ASSERT_EQ(v.y, 42);
}

TEST(VecTestConstruction, ConstructFromScalarVec3)
{
    bdm::vec3<int> v{42};
    ASSERT_EQ(v.x, 42);
    ASSERT_EQ(v.y, 42);
    ASSERT_EQ(v.z, 42);
}

TEST(VecTestConstruction, ConstructFromScalarVec4)
{
    bdm::vec4<int> v{42};
    ASSERT_EQ(v.x, 42);
    ASSERT_EQ(v.y, 42);
    ASSERT_EQ(v.z, 42);
    ASSERT_EQ(v.w, 42);
}

TEST(VecTestConstruction, ConstructFromScalarVecArbitrary)
{
    bdm::vec<5, int> v{42};
    ASSERT_EQ(v[0], 42);
    ASSERT_EQ(v[1], 42);
    ASSERT_EQ(v[2], 42);
    ASSERT_EQ(v[3], 42);
    ASSERT_EQ(v[4], 42);
}

TEST(VecTestOperators, AssignVec2)
{
    bdm::vec2<long int> v;
    v = bdm::vec2<int>{1, 2};
    ASSERT_EQ(v.x, 1);
    ASSERT_EQ(v.y, 2);
}

TEST(VecTestOperators, AssignVec3)
{
    bdm::vec3<long int> v;
    v = bdm::vec3<int>{1, 2, 3};
    ASSERT_EQ(v.x, 1);
    ASSERT_EQ(v.y, 2);
    ASSERT_EQ(v.z, 3);
}

TEST(VecTestOperators, AssignVec4)
{
    bdm::vec4<long int> v;
    v = bdm::vec4<int>{1, 2, 3, 4};
    ASSERT_EQ(v.x, 1);
    ASSERT_EQ(v.y, 2);
    ASSERT_EQ(v.z, 3);
    ASSERT_EQ(v.w, 4);
}

TEST(VecTestOperators, AssignVecArbitrary)
{
    bdm::vec<5, long int> v1;
    const bdm::vec<5, int> v2{1, 2, 3, 4, 5};
    v1 = v2;
    ASSERT_EQ(v1[0], 1);
    ASSERT_EQ(v1[1], 2);
    ASSERT_EQ(v1[2], 3);
    ASSERT_EQ(v1[3], 4);
    ASSERT_EQ(v1[4], 5);
}

TEST(VecTestOperators, TestSubscript)
{
    bdm::vec4<int> v{1, 2, 3, 4};
    ASSERT_EQ(v[0], 1);
    ASSERT_EQ(v[1], 2);
    ASSERT_EQ(v[2], 3);
    ASSERT_EQ(v[3], 4);
}

TEST(VecTestOperators, TestSubscriptModify)
{
    bdm::vec4<int> v{1, 2, 3, 4};
    v[0] = 5;
    ASSERT_EQ(v[0], 5);
    ASSERT_EQ(v[1], 2);
    ASSERT_EQ(v[2], 3);
    ASSERT_EQ(v[3], 4);
}

TEST(VecTestOperators, TestSubscriptConst)
{
    const bdm::vec4<int> v{1, 2, 3, 4};
    ASSERT_EQ(v[0], 1);
    ASSERT_EQ(v[1], 2);
    ASSERT_EQ(v[2], 3);
    ASSERT_EQ(v[3], 4);
}

TEST(VecTestOperators, TestIncrement)
{
    bdm::vec4<int> v{1, 2, 3, 4};
    ++v;
    ASSERT_EQ(v, bdm::vec4<int>(2, 3, 4, 5));
}

TEST(VecTestOperators, TestDecrement)
{
    bdm::vec4<int> v{1, 2, 3, 4};
    --v;
    ASSERT_EQ(v, bdm::vec4<int>(0, 1, 2, 3));
}

TEST(VecTestOperators, TestCompoundAssignmentAddScalar)
{
    bdm::vec4<long int> v{1, 2, 3, 4};
    v += 2;
    ASSERT_EQ(v, bdm::vec4<long int>(3, 4, 5, 6));
}

TEST(VecTestOperators, TestCompoundAssignmentAddInitializer)
{
    bdm::vec4<long int> v{1, 2, 3, 4};
    v += {1, 2, 3, 4};
    ASSERT_EQ(v, bdm::vec4<long int>(2, 4, 6, 8));
}

TEST(VecTestOperators, TestCompoundAssignmentAddVec)
{
    bdm::vec4<long int> v1{1, 2, 3, 4};
    bdm::vec4<int> v2{1, 2, 3, 4};
    v1 += v2;
    ASSERT_EQ(v1, bdm::vec4<long int>(2, 4, 6, 8));
}

TEST(VecTestOperators, TestCompoundAssignmentSubtractScalar)
{
    bdm::vec4<long int> v{5, 8, 11, 14};
    v -= 2;
    ASSERT_EQ(v, bdm::vec4<long int>(3, 6, 9, 12));
}

TEST(VecTestOperators, TestCompoundAssignmentSubtractInitializer)
{
    bdm::vec4<long int> v{5, 8, 11, 14};
    v -= {1, 2, 3, 4};
    ASSERT_EQ(v, bdm::vec4<long int>(4, 6, 8, 10));
}

TEST(VecTestOperators, TestCompoundAssignmentSubtractVec)
{
    bdm::vec4<long int> v1{5, 8, 11, 14};
    bdm::vec4<int> v2{1, 2, 3, 4};
    v1 -= v2;
    ASSERT_EQ(v1, bdm::vec4<long int>(4, 6, 8, 10));
}

TEST(VecTestOperators, TestCompoundAssignmentMultiplyScalar)
{
    bdm::vec4<long int> v{1, 2, 3, 4};
    v *= 2;
    ASSERT_EQ(v, bdm::vec4<long int>(2, 4, 6, 8));
}

TEST(VecTestOperators, TestCompoundAssignmentMultiplyInitializer)
{
    bdm::vec4<long int> v{1, 2, 3, 4};
    v *= {1, 2, 3, 4};
    ASSERT_EQ(v, bdm::vec4<long int>(1, 4, 9, 16));
}

TEST(VecTestOperators, TestCompoundAssignmentMultiplyVec)
{
    bdm::vec4<long int> v1{1, 2, 3, 4};
    bdm::vec4<int> v2{4, 3, 2, 1};
    v1 *= v2;
    ASSERT_EQ(v1, bdm::vec4<long int>(4, 6, 6, 4));
}

TEST(VecTestOperators, TestCompoundAssignmentDivideScalar)
{
    bdm::vec4<long int> v{8, 24, 36, 32};
    v /= 2;
    ASSERT_EQ(v, bdm::vec4<long int>(4, 12, 18, 16));
}

TEST(VecTestOperators, TestCompoundAssignmentDivideInitializer)
{
    bdm::vec4<long int> v{8, 24, 36, 32};
    v /= {1, 2, 3, 4};
    ASSERT_EQ(v, bdm::vec4<long int>(8, 12, 12, 8));
}

TEST(VecTestOperators, TestCompoundAssignmentDivideVec)
{
    bdm::vec4<long int> v1{8, 24, 36, 32};
    bdm::vec4<int> v2{4, 3, 2, 1};
    v1 /= v2;
    ASSERT_EQ(v1, bdm::vec4<long int>(2, 8, 18, 32));
}

TEST(VecTestOperators, TestCompoundAssignmentModScalar)
{
    bdm::vec4<long int> v{9, 24, 37, 32};
    v %= 2;
    ASSERT_EQ(v, bdm::vec4<long int>(1, 0, 1, 0));
}

TEST(VecTestOperators, TestCompoundAssignmentModinitializer)
{
    bdm::vec4<long int> v{9, 24, 37, 32};
    v %= {2, 3, 5, 7};
    ASSERT_EQ(v, bdm::vec4<long int>(1, 0, 2, 4));
}

TEST(VecTestOperators, TestCompoundAssignmentModVec)
{
    bdm::vec4<long int> v1{9, 24, 37, 32};
    bdm::vec4<int> v2{4, 3, 5, 6};
    v1 %= v2;
    ASSERT_EQ(v1, bdm::vec4<long int>(1, 0, 2, 2));
}

TEST(VecTestOperators, TestAddVecVec)
{
    bdm::vec4<int> v1{1, 2, 3, 4};
    bdm::vec4<int> v2{5, 6, 7, 8};
    auto res = v1 + v2;
    ASSERT_EQ(res, bdm::vec4<int>(6, 8, 10, 12));
}

TEST(VecTestOperators, TestAddScalarVec)
{
    bdm::vec4<int> v{1, 2, 3, 4};
    auto res = 4 + v;
    ASSERT_EQ(res, bdm::vec4<int>(5, 6, 7, 8));
}

TEST(VecTestOperators, TestAddVecScalar)
{
    bdm::vec4<int> v{1, 2, 3, 4};
    auto res = v + 7;
    ASSERT_EQ(res, bdm::vec4<int>(8, 9, 10, 11));
}

TEST(VecTestOperators, TestSubtractVecVec)
{
    bdm::vec4<int> v1{1, 2, 3, 4};
    bdm::vec4<int> v2{8, 7, 6, 5};
    auto res = v1 - v2;
    ASSERT_EQ(res, bdm::vec4<int>(-7, -5, -3, -1));
}

TEST(VecTestOperators, TestSubtractScalarVec)
{
    bdm::vec4<int> v{1, 2, 3, 4};
    auto res = 4 - v;
    ASSERT_EQ(res, bdm::vec4<int>(3, 2, 1, 0));
}

TEST(VecTestOperators, TestSubtractVecScalar)
{
    bdm::vec4<int> v{1, 2, 3, 4};
    auto res = v - 7;
    ASSERT_EQ(res, bdm::vec4<int>(-6, -5, -4, -3));
}

TEST(VecTestOperators, TestMultiplyVecVec)
{
    bdm::vec4<int> v1{1, 2, 3, 4};
    bdm::vec4<int> v2{5, 6, 7, 8};
    auto res = v1 * v2;
    ASSERT_EQ(res, bdm::vec4<int>(5, 12, 21, 32));
}

TEST(VecTestOperators, TestMultiplyScalarVec)
{
    bdm::vec4<int> v{1, 2, 3, 4};
    auto res = 4 * v;
    ASSERT_EQ(res, bdm::vec4<int>(4, 8, 12, 16));
}

TEST(VecTestOperators, TestMultiplyVecScalar)
{
    bdm::vec4<int> v{1, 2, 3, 4};
    auto res = v * -2;
    ASSERT_EQ(res, bdm::vec4<int>(-2, -4, -6, -8));
}

TEST(VecTestOperators, TestDivideVecVec)
{
    bdm::vec4<int> v1{1, 2, 3, 4};
    bdm::vec4<int> v2{5, 6, 7, 8};
    auto res = v2 / v1;
    ASSERT_EQ(res, bdm::vec4<int>(5, 3, 2, 2));
}

TEST(VecTestOperators, TestDivideScalarVec)
{
    bdm::vec4<int> v{1, 2, 3, 4};
    auto res = 10 / v;
    ASSERT_EQ(res, bdm::vec4<int>(10, 5, 3, 2));
}

TEST(VecTestOperators, TestDivideVecScalar)
{
    bdm::vec4<int> v{1, 2, 3, 4};
    auto res = v / 2;
    ASSERT_EQ(res, bdm::vec4<int>(0, 1, 1, 2));
}

TEST(VecTestOperators, TestModuloVecVec)
{
    bdm::vec4<int> v1{1, 2, 3, 4};
    bdm::vec4<int> v2{5, 6, 7, 8};
    auto res = v2 % v1;
    ASSERT_EQ(res, bdm::vec4<int>(0, 0, 1, 0));
}

TEST(VecTestOperators, TestModuloScalarVec)
{
    bdm::vec4<int> v{1, 2, 3, 4};
    auto res = 10 % v;
    ASSERT_EQ(res, bdm::vec4<int>(0, 0, 1, 2));
}

TEST(VecTestOperators, TestModuloVecScalar)
{
    bdm::vec4<int> v{1, 2, 3, 4};
    auto res = v % 3;
    ASSERT_EQ(res, bdm::vec4<int>(1, 2, 0, 1));
}

TEST(VecTestOperators, TestUnaryPlus)
{
    bdm::vec4<int> v1{-4, -3, 5, 6};
    bdm::vec4<int> v2 = +v1;
    ASSERT_EQ(v1, v2);
}

TEST(VecTestOperators, TestUnaryMinus)
{
    bdm::vec4<int> v1{-4, -3, 5, 6};
    bdm::vec4<int> v2 = -v1;
    ASSERT_EQ(v2, bdm::vec4<int>(4, 3, -5, -6));
}

TEST(VecTestOperators, TestEquality)
{
    bdm::vec4<int> v1{4, 3, 5, 6};
    bdm::vec4<int> v2;
    ASSERT_TRUE(v1 == v1);
    ASSERT_FALSE(v1 == v2);
}

TEST(VecTestOperators, TestNonEquality)
{
    bdm::vec4<int> v1{4, 3, 5, 6};
    bdm::vec4<int> v2;
    ASSERT_FALSE(v1 != v1);
    ASSERT_TRUE(v1 != v2);
}

TEST(VecTestMembers, TestApplyVec3)
{
    bdm::vec3<int> v{1, 2, 3};
    int count{};
    v.apply([&count](int& val) {
        ASSERT_EQ(val, count + 1);
        ++count;
    });
    ASSERT_EQ(count, 3);
}

TEST(VecTestMembers, TestApplyVec4)
{
    bdm::vec4<int> v{1, 2, 3, 4};
    int count{};
    v.apply([&count](int& val) {
        ASSERT_EQ(val, count + 1);
        ++count;
    });
    ASSERT_EQ(count, 4);
}

TEST(VecTestMembers, TestApplyVecVec3)
{
    int count{};
    bdm::vec3<int> v1{1, 2, 3};
    bdm::vec3<double> v2{1.0, 1.0, 1.0};
    v1.apply(
        [&count, &v2](int& val, double d) {
            ASSERT_EQ(val, count + 1);
            ASSERT_EQ(d, v2[static_cast<bdm::dim_t>(count)]);
            ++count;
        },
        v2);
    ASSERT_EQ(count, 3);
}

TEST(VecTestMembers, TestApplyVecVec4)
{
    int count{};
    bdm::vec4<int> v1{1, 2, 3, 4};
    bdm::vec4<double> v2{1.0, 1.0, 1.0, 1.0};
    v1.apply(
        [&count, &v2](int& val, double d) {
            ASSERT_EQ(val, count + 1);
            ASSERT_EQ(d, v2[static_cast<bdm::dim_t>(count)]);
            ++count;
        },
        v2);
    ASSERT_EQ(count, 4);
}

TEST(VecTestMembers, TestLength)
{
    bdm::vec4<float> v1{0.5f, -0.5f, -0.2f, 1.0f};
    ASSERT_NEAR(v1.length(), 1.2409, 0.0001);

    bdm::vec4<double> v2{9.0, 24.0, 37.0, 32.0};
    ASSERT_NEAR(v2.length(), 55.2268, 0.0001);

    v2 = {0.0, 0.0, 0.0, 0.0};
    ASSERT_NEAR(v2.length(), 0.0, 0.0001);
}

#define ASSERT_VEC_NEAR(v1, v2, threshold)                                     \
    ASSERT_EQ(v1.dimension, v2.dimension);                                     \
    for (bdm::dim_t ri = 0u; ri < v1.dimension; ++ri)                          \
    {                                                                          \
        ASSERT_NEAR(v1[ri], v2[ri], threshold);                                \
    }

TEST(VecTestMembers, TestNormalize)
{
    bdm::vec4<float> v1{0.5f, -0.5f, -0.2f, 1.0f};
    v1.normalize();
    ASSERT_VEC_NEAR(v1,
                    bdm::vec4<float>(0.4029f, -0.4029f, -0.1611f, 0.8058f),
                    0.0001f);

    bdm::vec4<double> v2{9.0, 24.0, 37.0, 32.0};
    v2.normalize();
    ASSERT_VEC_NEAR(v2,
                    bdm::vec4<double>(0.1629, 0.4345, 0.6699, 0.5794),
                    0.0001);

    v2 = {1.0, 0.0, 0.0, 0.0};
    v2.normalize();
    ASSERT_VEC_NEAR(v2, bdm::vec4<double>(1.0, 0.0, 0.0, 0.0), 0.0001);
}

TEST(VecTestMembers, TestSum)
{
    bdm::vec4<int> v{1, 2, 3, 4};
    ASSERT_EQ(v.sum(), 10);
}

TEST(VecTestMembers, TestProd)
{
    bdm::vec4<int> v{1, 2, 3, 4};
    ASSERT_EQ(v.prod(), 24);
}
