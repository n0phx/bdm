#pragma warning(push)
#pragma warning(disable : 4201 4365)
#include <benchmark/benchmark.h>
#include <glm/glm.hpp>
#pragma warning(pop)

#include "bdm/bdm.h"

static void GLMDotVec3(benchmark::State& state)
{
    glm::vec3 v1;
    glm::vec3 v2;
    for (auto _ : state)
    {
        benchmark::DoNotOptimize(v1);
        benchmark::DoNotOptimize(v2);
        benchmark::DoNotOptimize(glm::dot(v1, v2));
    }
}

static void GLMDotVec4(benchmark::State& state)
{
    glm::vec4 v1;
    glm::vec4 v2;
    for (auto _ : state)
    {
        benchmark::DoNotOptimize(v1);
        benchmark::DoNotOptimize(v2);
        benchmark::DoNotOptimize(glm::dot(v1, v2));
    }
}

static void GLMTransposeMat3(benchmark::State& state)
{
    glm::mat3 m;
    for (auto _ : state)
    {
        benchmark::DoNotOptimize(m);
        benchmark::DoNotOptimize(glm::transpose(m));
    }
}

static void GLMTransposeMat4(benchmark::State& state)
{
    glm::mat4 m;
    for (auto _ : state)
    {
        benchmark::DoNotOptimize(m);
        benchmark::DoNotOptimize(glm::transpose(m));
    }
}

static void GLMIncMat2(benchmark::State& state)
{
    glm::mat2 m2;
    for (auto _ : state)
    {
        benchmark::DoNotOptimize(++m2);
    }
}

static void GLMIncMat3(benchmark::State& state)
{
    glm::mat3 m3;
    for (auto _ : state)
    {
        benchmark::DoNotOptimize(++m3);
    }
}

static void GLMIncMat4(benchmark::State& state)
{
    glm::mat4 m4;
    for (auto _ : state)
    {
        benchmark::DoNotOptimize(++m4);
    }
}

static void GLMCompoundAssignmentAddScalarMat3(benchmark::State& state)
{
    glm::mat3 m;
    for (auto _ : state)
    {
        benchmark::DoNotOptimize(m += 12);
    }
}

static void GLMCompoundAssignmentAddMatMat3(benchmark::State& state)
{
    glm::mat3 m;
    glm::mat3 rhs;
    for (auto _ : state)
    {
        benchmark::DoNotOptimize(m += rhs);
    }
}

static void GLMCompoundAssignmentAddScalarMat4(benchmark::State& state)
{
    glm::mat4 m;
    for (auto _ : state)
    {
        benchmark::DoNotOptimize(m += 12.0f);
    }
}

static void GLMCompoundAssignmentAddMatMat4(benchmark::State& state)
{
    glm::mat4 m;
    glm::mat4 rhs;
    for (auto _ : state)
    {
        benchmark::DoNotOptimize(m += rhs);
    }
}

static void GLMMultiplyMat3(benchmark::State& state)
{
    glm::mat3 ma;
    glm::mat3 mb;
    for (auto _ : state)
    {
        benchmark::DoNotOptimize(ma);
        benchmark::DoNotOptimize(mb);
        benchmark::DoNotOptimize(ma * mb);
    }
}

static void GLMMultiplyMat4(benchmark::State& state)
{
    glm::mat4 ma;
    glm::mat4 mb;
    for (auto _ : state)
    {
        benchmark::DoNotOptimize(ma);
        benchmark::DoNotOptimize(mb);
        benchmark::DoNotOptimize(ma * mb);
    }
}

static void GLMDeterminantMat3(benchmark::State& state)
{
    glm::mat3 m{glm::vec3{2.0f, 2.0f, 1.0f},
                glm::vec3{-3.0f, 0.0f, 4.0f},
                glm::vec3{1.0f, -1.0f, 5.0f}};
    for (auto _ : state)
    {
        benchmark::DoNotOptimize(m);
        benchmark::DoNotOptimize(glm::determinant(m));
    }
}

static void GLMDeterminantMat4(benchmark::State& state)
{
    glm::mat4 m{glm::vec4{4.0f, 0.0f, 0.0f, 0.0f},
                glm::vec4{3.0f, 1.0f, -1.0f, 3.0f},
                glm::vec4{2.0f, -3.0f, 3.0f, 1.0f},
                glm::vec4{2.0f, 3.0f, 3.0f, 1.0f}};
    for (auto _ : state)
    {
        benchmark::DoNotOptimize(m);
        benchmark::DoNotOptimize(glm::determinant(m));
    }
}

static void GLMInverseMat3(benchmark::State& state)
{
    glm::mat3 m{glm::vec3{0.6f, 0.2f, 0.3f},
                glm::vec3{0.2f, 0.7f, 0.5f},
                glm::vec3{0.3f, 0.5f, 0.7f}};
    for (auto _ : state)
    {
        benchmark::DoNotOptimize(m);
        benchmark::DoNotOptimize(glm::inverse(m));
    }
}

static void GLMInverseMat4(benchmark::State& state)
{
    glm::mat4 m{glm::vec4{0.6f, 0.2f, 0.3f, 0.4f},
                glm::vec4{0.2f, 0.7f, 0.5f, 0.3f},
                glm::vec4{0.3f, 0.5f, 0.7f, 0.2f},
                glm::vec4{0.4f, 0.3f, 0.2f, 0.6f}};
    for (auto _ : state)
    {
        benchmark::DoNotOptimize(m);
        benchmark::DoNotOptimize(glm::inverse(m));
    }
}

static void BDMDotVec3(benchmark::State& state)
{
    bdm::vec3<float> v1;
    bdm::vec3<float> v2;
    for (auto _ : state)
    {
        benchmark::DoNotOptimize(v1);
        benchmark::DoNotOptimize(v2);
        benchmark::DoNotOptimize(bdm::dot(v1, v2));
    }
}

static void BDMDotVec4(benchmark::State& state)
{
    bdm::vec4<float> v1;
    bdm::vec4<float> v2;
    for (auto _ : state)
    {
        benchmark::DoNotOptimize(v1);
        benchmark::DoNotOptimize(v2);
        benchmark::DoNotOptimize(bdm::dot(v1, v2));
    }
}

static void BDMTransposeMat3(benchmark::State& state)
{
    bdm::mat3<float> m;
    for (auto _ : state)
    {
        benchmark::DoNotOptimize(m);
        benchmark::DoNotOptimize(bdm::transpose(m));
    }
}

static void BDMTransposeMat4(benchmark::State& state)
{
    bdm::mat4<float> m;
    for (auto _ : state)
    {
        benchmark::DoNotOptimize(m);
        benchmark::DoNotOptimize(bdm::transpose(m));
    }
}

static void BDMIncMat2(benchmark::State& state)
{
    bdm::mat2<float> m2;
    for (auto _ : state)
    {
        benchmark::DoNotOptimize(++m2);
    }
}

static void BDMIncMat3(benchmark::State& state)
{
    bdm::mat3<float> m3;
    for (auto _ : state)
    {
        benchmark::DoNotOptimize(++m3);
    }
}

static void BDMIncMat4(benchmark::State& state)
{
    bdm::mat4<float> m4;
    for (auto _ : state)
    {
        benchmark::DoNotOptimize(++m4);
    }
}

static void BDMCompoundAssignmentAddScalarMat3(benchmark::State& state)
{
    bdm::mat3<float> m;
    for (auto _ : state)
    {
        benchmark::DoNotOptimize(m += 12.0f);
    }
}

static void BDMCompoundAssignmentAddMatMat3(benchmark::State& state)
{
    bdm::mat3<float> m;
    bdm::mat3<float> rhs;
    for (auto _ : state)
    {
        benchmark::DoNotOptimize(m += rhs);
    }
}

static void BDMCompoundAssignmentAddScalarMat4(benchmark::State& state)
{
    bdm::mat4<float> m;
    for (auto _ : state)
    {
        benchmark::DoNotOptimize(m += 12.0f);
    }
}

static void BDMCompoundAssignmentAddMatMat4(benchmark::State& state)
{
    bdm::mat4<float> m;
    bdm::mat4<float> rhs;
    for (auto _ : state)
    {
        benchmark::DoNotOptimize(m += rhs);
    }
}

static void BDMMultiplyMat3(benchmark::State& state)
{
    bdm::mat3<float> ma;
    bdm::mat3<float> mb;
    for (auto _ : state)
    {
        benchmark::DoNotOptimize(ma);
        benchmark::DoNotOptimize(mb);
        benchmark::DoNotOptimize(ma * mb);
    }
}

static void BDMMultiplyMat4(benchmark::State& state)
{
    bdm::mat4<float> ma;
    bdm::mat4<float> mb;
    for (auto _ : state)
    {
        benchmark::DoNotOptimize(ma);
        benchmark::DoNotOptimize(mb);
        benchmark::DoNotOptimize(ma * mb);
    }
}

static void BDMDeterminantMat3(benchmark::State& state)
{
    bdm::mat3<float> m{bdm::vec3<float>{2.0f, -3.0f, 1.0f},
                       bdm::vec3<float>{2.0f, 0.0f, -1.0f},
                       bdm::vec3<float>{1.0f, 4.0f, 5.0f}};
    for (auto _ : state)
    {
        benchmark::DoNotOptimize(m);
        benchmark::DoNotOptimize(bdm::determinant(m));
    }
}

static void BDMDeterminantMat4(benchmark::State& state)
{
    bdm::mat4<float> m{bdm::vec4<float>{4.0f, 3.0f, 2.0f, 2.0f},
                       bdm::vec4<float>{0.0f, 1.0f, -3.0f, 3.0f},
                       bdm::vec4<float>{0.0f, -1.0f, 3.0f, 3.0f},
                       bdm::vec4<float>{0.0f, 3.0f, 1.0f, 1.0f}};
    for (auto _ : state)
    {
        benchmark::DoNotOptimize(m);
        benchmark::DoNotOptimize(bdm::determinant(m));
    }
}

static void BDMInverseMat3(benchmark::State& state)
{
    bdm::mat3<float> m{bdm::vec3<float>{0.6f, 0.2f, 0.3f},
                       bdm::vec3<float>{0.2f, 0.7f, 0.5f},
                       bdm::vec3<float>{0.3f, 0.5f, 0.7f}};
    for (auto _ : state)
    {
        benchmark::DoNotOptimize(m);
        benchmark::DoNotOptimize(bdm::inverse(m));
    }
}

static void BDMInverseMat4(benchmark::State& state)
{
    bdm::mat4<float> m{bdm::vec4<float>{0.6f, 0.2f, 0.3f, 0.4f},
                       bdm::vec4<float>{0.2f, 0.7f, 0.5f, 0.3f},
                       bdm::vec4<float>{0.3f, 0.5f, 0.7f, 0.2f},
                       bdm::vec4<float>{0.4f, 0.3f, 0.2f, 0.6f}};
    for (auto _ : state)
    {
        benchmark::DoNotOptimize(m);
        benchmark::DoNotOptimize(bdm::inverse(m));
    }
}

BENCHMARK(BDMDotVec3);
BENCHMARK(GLMDotVec3);
BENCHMARK(BDMDotVec4);
BENCHMARK(GLMDotVec4);
BENCHMARK(BDMTransposeMat3);
BENCHMARK(GLMTransposeMat3);
BENCHMARK(BDMTransposeMat4);
BENCHMARK(GLMTransposeMat4);
BENCHMARK(BDMIncMat2);
BENCHMARK(GLMIncMat2);
BENCHMARK(BDMIncMat3);
BENCHMARK(GLMIncMat3);
BENCHMARK(BDMIncMat4);
BENCHMARK(GLMIncMat4);
BENCHMARK(BDMCompoundAssignmentAddScalarMat3);
BENCHMARK(GLMCompoundAssignmentAddScalarMat3);
BENCHMARK(BDMCompoundAssignmentAddScalarMat4);
BENCHMARK(GLMCompoundAssignmentAddScalarMat4);
BENCHMARK(BDMCompoundAssignmentAddMatMat3);
BENCHMARK(GLMCompoundAssignmentAddMatMat3);
BENCHMARK(BDMCompoundAssignmentAddMatMat4);
BENCHMARK(GLMCompoundAssignmentAddMatMat4);
BENCHMARK(BDMMultiplyMat3);
BENCHMARK(GLMMultiplyMat3);
BENCHMARK(BDMMultiplyMat4);
BENCHMARK(GLMMultiplyMat4);
BENCHMARK(BDMDeterminantMat3);
BENCHMARK(GLMDeterminantMat3);
BENCHMARK(BDMDeterminantMat4);
BENCHMARK(GLMDeterminantMat4);
BENCHMARK(BDMInverseMat3);
BENCHMARK(GLMInverseMat3);
BENCHMARK(BDMInverseMat4);
BENCHMARK(GLMInverseMat4);

BENCHMARK_MAIN();
