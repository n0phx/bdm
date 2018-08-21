cmake_minimum_required(VERSION 3.10)

set(BDM bdm)
set(BDM_VERSION 0.1.0)
project(${BDM} VERSION ${BDM_VERSION} LANGUAGES CXX)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)
set(BDM_INSTALL_CONFIGDIR "${CMAKE_INSTALL_LIBDIR}/cmake/${BDM}")

# Target configuration
add_library(${BDM} INTERFACE)
add_library(bdm::bdm ALIAS ${BDM})
target_compile_features(${BDM} INTERFACE cxx_std_17)
target_include_directories(${BDM} INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

# Tests
enable_testing()
option(BDM_BUILD_TESTS "Build tests" ON)
if(BDM_BUILD_TESTS)
    add_subdirectory(tests)
endif()

# Benchmarks
option(BDM_BUILD_BENCHMARKS "Build benchmarks" OFF)
if(BDM_BUILD_BENCHMARKS)
    add_subdirectory(benchmarks)
endif()

# Export and install targets
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/${BDM}-config-version.cmake"
    VERSION ${BDM_VERSION}
    COMPATIBILITY SameMajorVersion)

install(TARGETS ${BDM} EXPORT bdm-targets)
install(EXPORT bdm-targets
    FILE bdm-config.cmake
    NAMESPACE bdm::
    DESTINATION ${BDM_INSTALL_CONFIGDIR}
)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/${BDM}-config-version.cmake"
    DESTINATION ${BDM_INSTALL_CONFIGDIR})
install(FILES LICENSE DESTINATION ${CMAKE_INSTALL_DOCDIR})
install(DIRECTORY bdm DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
