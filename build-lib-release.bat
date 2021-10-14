@echo off
cmake -DCMAKE_BUILD_TYPE=Release -DUSE_CCACHE=True -DUSE_STATIC_ANALYZER="clang-tidy;cppcheck" -S. -Bbuild/release && cmake --build build/release

echo Build done!
pause >nul