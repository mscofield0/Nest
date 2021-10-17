@echo off
cmake -G "Visual Studio 16 2019" -DCMAKE_BUILD_TYPE=Release -DUSE_CCACHE=True -DUSE_STATIC_ANALYZER="clang-tidy;cppcheck" -S. -Bbuild/release && cmake --build build/release

echo Build done!