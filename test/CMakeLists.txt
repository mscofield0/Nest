cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

# ==============================================
# = Project
# ==============================================
project(NestTests LANGUAGES CXX)
set(MAIN_PROJECT "Nest")

# ==============================================
# = Options
# ==============================================
option(ENABLE_TEST_COVERAGE "Enable test coverage" OFF)
option(TEST_INSTALLED_VERSION "Test the version found by find_package" OFF)

# ==============================================
# = Dependencies
# ==============================================
include(../cmake/tools.cmake)
include(../cmake/CPM.cmake)

CPMAddPackage("gh:onqtam/doctest#2.4.6")
CPMAddPackage("gh:TheLartians/Format.cmake@1.7.3")

if(TEST_INSTALLED_VERSION)
  find_package(${MAIN_PROJECT} REQUIRED)
else()
  CPMAddPackage(NAME ${MAIN_PROJECT} SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/..)
endif()

# ==============================================
# = Source files
# ==============================================
file(GLOB_RECURSE headers CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hxx)
file(GLOB_RECURSE sources CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cxx)

# ==============================================
# = Executable
# ==============================================
add_executable(${PROJECT_NAME} ${sources} ${headers})

# ==============================================
# = Target properties
# ==============================================
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 20)

# ==============================================
# = Link libraries
# ==============================================
target_link_libraries(${PROJECT_NAME} doctest::doctest ${MAIN_PROJECT}::${MAIN_PROJECT})

# ==============================================
# = Compile options
# ==============================================
if(MSVC)
  target_compile_definitions(${PROJECT_NAME} PUBLIC DOCTEST_CONFIG_USE_STD_HEADERS)
endif()

# ==============================================
# = Include directories
# ==============================================
target_include_directories(
  ${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
                         $<INSTALL_INTERFACE:include/${PROJECT_NAME}-${PROJECT_VERSION}>
)

# ==============================================
# = Tests
# ==============================================
enable_testing()

include(${doctest_SOURCE_DIR}/scripts/cmake/doctest.cmake)
doctest_discover_tests(${PROJECT_NAME})

# ==============================================
# = Code coverage
# ==============================================
if(ENABLE_TEST_COVERAGE)
  target_compile_options(${MAIN_PROJECT} PUBLIC -O0 -g -fprofile-arcs -ftest-coverage)
  target_link_options(${MAIN_PROJECT} PUBLIC -fprofile-arcs -ftest-coverage)
endif()
