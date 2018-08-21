project(tests LANGUAGES CXX)

set(BENCHMARK_ENABLE_GTEST_TESTS OFF CACHE BOOL "" FORCE)
add_subdirectory("${CMAKE_SOURCE_DIR}/ext/benchmark" ext/benchmark EXCLUDE_FROM_ALL)
set_target_properties(benchmark PROPERTIES FOLDER ext)

add_subdirectory("${CMAKE_SOURCE_DIR}/ext/glm" ext/glm EXCLUDE_FROM_ALL)

set(BENCHMARK_RUNNER benchmark_runner)
add_executable(${BENCHMARK_RUNNER} bdm_bench.cpp)
target_link_libraries(${BENCHMARK_RUNNER} benchmark glm bdm::bdm)
set_target_properties(${BENCHMARK_RUNNER}
                      PROPERTIES FOLDER benchmarks)
