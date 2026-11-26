cmake_minimum_required(VERSION 3.16)
project(GenomeAssembler VERSION 0.1.0 LANGUAGES CXX)

# ---- Language standard -------------------------------------------------
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ---- Options -----------------------------------------------------------
option(BUILD_TESTS "Build unit tests (downloads GoogleTest)" ON)
option(ENABLE_SANITIZERS "Enable AddressSanitizer + UBSan (debug)" OFF)

# Default to Release so benchmarks are fast
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

# ---- Core library (all logic lives here; main.cpp stays tiny) ----------
# Add new .cpp files under src/ (except main.cpp); they are picked up
# automatically after re-running cmake.
file(GLOB CORE_SOURCES CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/src/*.cpp)
list(REMOVE_ITEM CORE_SOURCES ${CMAKE_SOURCE_DIR}/src/main.cpp)

add_library(assembler_core STATIC ${CORE_SOURCES})
target_include_directories(assembler_core PUBLIC ${CMAKE_SOURCE_DIR}/include)

if(MSVC)
  target_compile_options(assembler_core PUBLIC /W4)
else()
  target_compile_options(assembler_core PUBLIC -Wall -Wextra -Wpedantic)
  if(ENABLE_SANITIZERS)
    target_compile_options(assembler_core PUBLIC -fsanitize=address,undefined -fno-omit-frame-pointer)
    target_link_options(assembler_core PUBLIC -fsanitize=address,undefined)
  endif()
endif()

# ---- Command-line executable ------------------------------------------
add_executable(assembler src/main.cpp)
target_link_libraries(assembler PRIVATE assembler_core)

# ---- Tests (GoogleTest) ------------------------------------------------
if(BUILD_TESTS)
  include(FetchContent)
    FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
  )
  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
  FetchContent_MakeAvailable(googletest)

  enable_testing()
  file(GLOB TEST_SOURCES CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/tests/*.cpp)
  add_executable(run_tests ${TEST_SOURCES})
  target_link_libraries(run_tests PRIVATE assembler_core GTest::gtest_main)

  include(GoogleTest)
  gtest_discover_tests(run_tests)
endif()
