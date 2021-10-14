cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

# ==============================================
# = Project
# ==============================================
project(NestApp LANGUAGES CXX)
set(MAIN_PROJECT "Nest")


# ==============================================
# = Dependencies
# ==============================================
include(../cmake/tools.cmake)
include(../cmake/CPM.cmake)

CPMAddPackage(
  GITHUB_REPOSITORY jarro2783/cxxopts
  VERSION 2.2.1
  OPTIONS "CXXOPTS_BUILD_EXAMPLES NO" "CXXOPTS_BUILD_TESTS NO" "CXXOPTS_ENABLE_INSTALL YES"
)

CPMAddPackage(NAME ${MAIN_PROJECT} SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/..)


# ==============================================
# = Source files
# ==============================================
file(GLOB headers CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hxx)
file(GLOB sources CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cxx)

# ==============================================
# = Executable
# ==============================================
add_executable(${PROJECT_NAME} ${sources} ${headers})


# ==============================================
# = Target properties
# ==============================================
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17 OUTPUT_NAME "${MAIN_PROJECT}")

# ==============================================
# = Compile options
# ==============================================
# --- empty


# ==============================================
# = Link libraries
# ==============================================
target_link_libraries(${PROJECT_NAME} ${MAIN_PROJECT}::${MAIN_PROJECT} cxxopts)
