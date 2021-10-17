@echo off
<<<<<<< Updated upstream
cmake -DCMAKE_BUILD_TYPE=Debug -DUSE_CCACHE=True -DUSE_STATIC_ANALYZER="clang-tidy;cppcheck" -DUSE_SANITIZER="Address:Undefined:Leak" -Stest -Bbuild/test/debug && cmake --build build/test/debug -- -warnAsMessage:MSB8065,LNK4300
=======
cmake -G "Visual Studio 16 2019" -DCMAKE_BUILD_TYPE=Debug -DUSE_CCACHE=True -DUSE_STATIC_ANALYZER="clang-tidy;cppcheck" -DUSE_SANITIZER="Address:Undefined:Leak" -Stest -Bbuild/test/debug && cmake --build build/test/debug -- -warnAsMessage:MSB8065,LNK4300
>>>>>>> Stashed changes

echo Build done!