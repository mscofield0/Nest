cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

# ==============================================
# = Project
# ==============================================
project(
  Nest
  VERSION 0.1.0
  LANGUAGES CXX
)

# ==============================================
# = In-source builds
# ==============================================
if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
  message(
    FATAL_ERROR
      "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there."
  )
endif()

# ==============================================
# = Dependencies
# ==============================================
include(cmake/CPM.cmake)

# PackageProject.cmake will be used to make our target installable
CPMAddPackage("gh:TheLartians/PackageProject.cmake@1.8.0")

# Include Conan
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)


# ==============================================
# = Source files
# ==============================================
file(GLOB_RECURSE headers CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/include/*.hxx")
file(GLOB_RECURSE sources CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cxx"
     "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hxx"
)

# ==============================================
# = Library
# ==============================================
add_library(${PROJECT_NAME} ${headers} ${sources})

# ==============================================
# = Target properties
# ==============================================
set_target_properties(${PROJECT_NAME} PROPERTIES
  CXX_STANDARD 20
  CXX_STANDARD_REQUIRED ON
  CXX_EXTENSIONS OFF
)

# ==============================================
# = Target definitions
# ==============================================
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  target_compile_definitions(${PROJECT_NAME} PUBLIC NEST_GCC)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "(Apple)?Clang")
  target_compile_definitions(${PROJECT_NAME} PUBLIC NEST_CLANG)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  target_compile_definitions(${PROJECT_NAME} PUBLIC NEST_MSVC)
endif()

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
  target_compile_definitions(${PROJECT_NAME} PUBLIC NEST_DEBUG)
endif()


# ==============================================
# = Compile options
# ==============================================
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID MATCHES "GNU")
  target_compile_options(${PROJECT_NAME} PUBLIC -Wall -Wpedantic -Wextra -fcoroutines)
elseif(MSVC)
  target_compile_options(${PROJECT_NAME} PUBLIC /W4 /permissive- /await)
endif()

# ==============================================
# = Sanitizers
# ==============================================
include(cmake/sanitizers.cmake)

if(NOT DEFINED USE_SANITIZER)
  set(USE_SANITIZER "")
endif()

enable_sanitizers(${PROJECT_NAME} ${USE_SANITIZER})

# ==============================================
# = Link libraries
# ==============================================
target_link_libraries(
  ${PROJECT_NAME} PRIVATE
  CONAN_PKG::spdlog_header_only
  CONAN_PKG::backward
)

target_link_libraries(${PROJECT_NAME} PUBLIC
  CONAN_PKG::fmt-header-only
  CONAN_PKG::concurrentqueue
)

# ==============================================
# = Include directories
# ==============================================
target_include_directories(
  ${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
                         $<INSTALL_INTERFACE:include/${PROJECT_NAME}-${PROJECT_VERSION}>
)

target_include_directories(
  ${PROJECT_NAME} PRIVATE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src/detail>
)

# ==============================================
# = Generated headers
# ==============================================
set(VERSION_HEADER_LOCATION ${PROJECT_NAME}/Version.hxx)
set(EXPORT_HEADER_LOCATION ${PROJECT_NAME}/Export.hxx)

# ==============================================
# = Export project
# ==============================================
packageProject(
  NAME ${PROJECT_NAME}
  VERSION ${PROJECT_VERSION}
  NAMESPACE ${PROJECT_NAME}
  BINARY_DIR ${PROJECT_BINARY_DIR}
  INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include
  INCLUDE_DESTINATION include/${PROJECT_NAME}-${PROJECT_VERSION}
  VERSION_HEADER "${VERSION_HEADER_LOCATION}"
  EXPORT_HEADER "${EXPORT_HEADER_LOCATION}"
  COMPATIBILITY SameMajorVersion
  DEPENDENCIES "fmt 8.0.1;spdlog 1.9.2"
)
