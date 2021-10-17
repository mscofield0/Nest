@echo off

cmake -GNinja -DCMAKE_BUILD_TYPE=Debug -DUSE_CCACHE=True -DUSE_STATIC_ANALYZER="clang-tidy;cppcheck" -DUSE_SANITIZER="Address:Undefined:Leak" -S. -Bbuild/debug
