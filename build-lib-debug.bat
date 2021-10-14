@echo off
cmake -DCMAKE_BUILD_TYPE=Debug -DUSE_CCACHE=True -DUSE_STATIC_ANALYZER="clang-tidy;cppcheck" -DUSE_SANITIZER="Address:Undefined:Leak" -S. -Bbuild/debug && cmake --build build/debug -- -warnAsMessage:MSB8065,LNK4300

echo Build done!
pause >nul