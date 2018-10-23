#pragma warning(push)
#pragma warning(disable : 4365 5026 5027)
#include <gtest/gtest.h>
#pragma warning(pop)

#include "bdm/bdm.h"
#include "test_ext.h"

TEST(TestTransforms, LookAtLH)
{
    bdm::vec3<float> from{-2.0f, -1.0f, -3.0f};
    bdm::vec3<float> at{1.0f, 1.0f, 1.0f};
    bdm::vec3<float> up{0.0f, 1.0f, 0.0f};
    auto view = bdm::look_at(from, at, up, bdm::handedness::left);
    bdm::mat4<float> expected{0.8f, 0.0f, -0.6f, 0.0f,
                              -0.222834f, 0.928477f, -0.297113f, 0.0f,
                              0.557086f, 0.371391f, 0.742781f, 0.0f,
                              -0.2f, -0.40853f, 3.71391f, 1.0f};
    ASSERT_MAT_NEAR(view, expected, 0.0001f);
}

TEST(TestTransforms, LookAtRH)
{
    bdm::vec3<float> from{-2.0f, -1.0f, -3.0f};
    bdm::vec3<float> at{1.0f, 1.0f, 1.0f};
    bdm::vec3<float> up{0.0f, 1.0f, 0.0f};
    auto view = bdm::look_at(from, at, up);  // Default is right
    bdm::mat4<float> expected{-0.8f, 0.0f, 0.6f, 0.0f,
                              -0.222834f, 0.928477f, -0.297113f, 0.0f,
                              -0.557086f, -0.371391f, -0.742781f, 0.0f,
                              0.2f, -0.40853f, -3.71391f, 1.0f};
    ASSERT_MAT_NEAR(view, expected, 0.0001f);
}

TEST(TestTransforms, PerspectiveLHNO)
{
    bdm::vec4<float> v{0.7f, 0.2f, -3.0f, 1.0f};
    auto proj = bdm::perspective(45.0f,
                                 800.0f / 600.0f,
                                 0.1f,
                                 100.0f,
                                 bdm::handedness::left,
                                 2.0f);
    bdm::mat4<float> expected{1.34444f, 0.0f, 0.0f, 0.0f,
                              0.0f, 1.79259f, 0.0f, 0.0f,
                              0.0f, 0.0f, 1.002f, 1.0f,
                              0.0f, 0.0f, -0.2002f, 0.0f};
    ASSERT_MAT_NEAR(proj, expected, 0.0001f);
}

TEST(TestTransforms, PerspectiveLHZO)
{
    bdm::vec4<float> v{0.7f, 0.2f, -3.0f, 1.0f};
    auto proj = bdm::perspective(45.0f,
                                 800.0f / 600.0f,
                                 0.1f,
                                 100.0f,
                                 bdm::handedness::left,
                                 1.0f);
    bdm::mat4<float> expected{1.34444f, 0.0f, 0.0f, 0.0f,
                              0.0f, 1.79259f, 0.0f, 0.0f,
                              0.0f, 0.0f, 1.002f, 1.0f,
                              0.0f, 0.0f, -0.1001f, 0.0f};
    ASSERT_MAT_NEAR(proj, expected, 0.0001f);
}

TEST(TestTransforms, PerspectiveRHNO)
{
    bdm::vec4<float> v{0.7f, 0.2f, -3.0f, 1.0f};
    auto proj = bdm::perspective(45.0f,
                                 800.0f / 600.0f,
                                 0.1f,
                                 100.0f,
                                 bdm::handedness::right,
                                 2.0f);
    bdm::mat4<float> expected{1.34444f, 0.0f, 0.0f, 0.0f,
                              0.0f, 1.79259f, 0.0f, 0.0f,
                              0.0f, 0.0f, -1.002f, -1.0f,
                              0.0f, 0.0f, -0.2002f, 0.0f};
    ASSERT_MAT_NEAR(proj, expected, 0.0001f);
}

TEST(TestTransforms, PerspectiveRHZO)
{
    bdm::vec4<float> v{0.7f, 0.2f, -3.0f, 1.0f};
    auto proj = bdm::perspective(45.0f,
                                 800.0f / 600.0f,
                                 0.1f,
                                 100.0f,
                                 bdm::handedness::right,
                                 1.0f);
    bdm::mat4<float> expected{1.34444f, 0.0f, 0.0f, 0.0f,
                              0.0f, 1.79259f, 0.0f, 0.0f,
                              0.0f, 0.0f, -1.002f, -1.0f,
                              0.0f, 0.0f, -0.1001f, 0.0f};
    ASSERT_MAT_NEAR(proj, expected, 0.0001f);
}

TEST(TestTransforms, OrthographicLHNO)
{
    bdm::vec4<float> v{0.7f, 0.2f, -3.0f, 1.0f};
    auto proj = bdm::ortho(0.0f,
                           800.0f,
                           0.0f,
                           600.0f,
                           0.1f,
                           100.0f,
                           bdm::handedness::left,
                           2.0f);
    bdm::mat4<float> expected{0.0025f, 0.0f, 0.0f, 0.0f,
                              0.0f, 0.00333333f, 0.0f, 0.0f,
                              0.0f, 0.0f, 0.02002f, 0.0f,
                              -1.0f, -1.0f, -1.002f, 1.0f};
    ASSERT_MAT_NEAR(proj, expected, 0.0001f);
}

TEST(TestTransforms, OrthographicLHZO)
{
    bdm::vec4<float> v{0.7f, 0.2f, -3.0f, 1.0f};
    auto proj = bdm::ortho(0.0f,
                           800.0f,
                           0.0f,
                           600.0f,
                           0.1f,
                           100.0f,
                           bdm::handedness::left,
                           1.0f);
    bdm::mat4<float> expected{0.0025f, 0.0f, 0.0f, 0.0f,
                              0.0f, 0.00333333f, 0.0f, 0.0f,
                              0.0f, 0.0f, 0.01001f, 0.0f,
                              -1.0f, -1.0f, -0.001001f, 1.0f};
    ASSERT_MAT_NEAR(proj, expected, 0.0001f);
}

TEST(TestTransforms, OrthographicRHNO)
{
    bdm::vec4<float> v{0.7f, 0.2f, -3.0f, 1.0f};
    auto proj = bdm::ortho(0.0f,
                           800.0f,
                           0.0f,
                           600.0f,
                           0.1f,
                           100.0f,
                           bdm::handedness::right,
                           2.0f);
    bdm::mat4<float> expected{0.0025f, 0.0f, 0.0f, 0.0f,
                              0.0f, 0.00333333f, 0.0f, 0.0f,
                              0.0f, 0.0f, -0.02002f, 0.0f,
                              -1.0f, -1.0f, -1.002f, 1.0f};
    ASSERT_MAT_NEAR(proj, expected, 0.0001f);
}

TEST(TestTransforms, OrthographicRHZO)
{
    bdm::vec4<float> v{0.7f, 0.2f, -3.0f, 1.0f};
    auto proj = bdm::ortho(0.0f,
                           800.0f,
                           0.0f,
                           600.0f,
                           0.1f,
                           100.0f,
                           bdm::handedness::right,
                           1.0f);
    bdm::mat4<float> expected{0.0025f, 0.0f, 0.0f, 0.0f,
                              0.0f, 0.00333333f, 0.0f, 0.0f,
                              0.0f, 0.0f, -0.01001f, 0.0f,
                              -1.0f, -1.0f, -0.001001f, 1.0f};
    ASSERT_MAT_NEAR(proj, expected, 0.0001f);
}

TEST(TestTransforms, Rotate)
{
    bdm::vec3<float> axis{0.5f, 0.4f, 0.3f};
    auto m = bdm::rotate(axis, bdm::radians(45.0f));
    bdm::mat4<float> expected{0.853553f, 0.417157f, -0.312132f, 0.0f,
                              -0.182843f, 0.800833f, 0.570294f, 0.0f,
                              0.487868f, -0.429706f, 0.759828f, 0.0f,
                              0.0f, 0.0f, 0.0f, 1.0f};
    ASSERT_MAT_NEAR(m, expected, 0.0001f);
}

TEST(TestTransforms, ScaleUniform)
{
    auto m = bdm::mat4<float>::identity();
    m = bdm::scale(m, 3.0f);
    bdm::mat4<float> expected{3.0f, 0.0f, 0.0f, 0.0f,
                              0.0f, 3.0f, 0.0f, 0.0f,
                              0.0f, 0.0f, 3.0f, 0.0f,
                              0.0f, 0.0f, 0.0f, 1.0f};
    ASSERT_MAT_NEAR(m, expected, 0.0001f);
}

TEST(TestTransforms, ScaleNonUniform)
{
    auto m = bdm::mat4<float>::identity();
    m = bdm::scale(m, bdm::vec3<float>{2.0f, 3.0f, 4.0f});
    bdm::mat4<float> expected{2.0f, 0.0f, 0.0f, 0.0f,
                              0.0f, 3.0f, 0.0f, 0.0f,
                              0.0f, 0.0f, 4.0f, 0.0f,
                              0.0f, 0.0f, 0.0f, 1.0f};
    ASSERT_MAT_NEAR(m, expected, 0.0001f);
}

TEST(TestTransforms, Translate)
{
    auto m = bdm::mat4<float>::identity();
    m = bdm::translate(m, bdm::vec3<float>{2.0f, 3.0f, 4.0f});
    bdm::mat4<float> expected{1.0f, 0.0f, 0.0f, 0.0f,
                              0.0f, 1.0f, 0.0f, 0.0f,
                              0.0f, 0.0f, 1.0f, 0.0f,
                              2.0f, 3.0f, 4.0f, 1.0f};
    ASSERT_MAT_NEAR(m, expected, 0.0001f);
}
