function(enable_sanitizers target sanitizers)
  message(DEBUG "[SANITIZERS] Target: ${target}")
  message(DEBUG "[SANITIZERS] Sanitizers: ${sanitizers}")

  if(NOT DEFINED target)
    message(ERROR "[SANITIZERS] Target not defined.")
  endif()

  if(NOT DEFINED sanitizers)
    message(ERROR "[SANITIZERS] Sanitizers not defined.")
  endif()

  if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    if(sanitizers MATCHES "([Aa]ddress)")
      message("[SANITIZERS] Building with Address sanitizer.")
      target_compile_options(
        ${target} INTERFACE /fsanitize=address /Oy- /Zo /fsanitize-address-use-after-return
      )

      # Copy over the asan libs to the binary dir
      get_filename_component(MSVC_DIR "${CMAKE_CXX_COMPILER}" DIRECTORY CACHE)

      add_custom_command(
        OUTPUT "${${target}_BINARY_DIR}/clang_rt.asan_dbg_dynamic-x86_64.dll"
        COMMAND "${CMAKE_COMMAND}" -E copy "${MSVC_DIR}/clang_rt.asan_dbg_dynamic-x86_64.dll"
                "$<TARGET_FILE_DIR:${target}>"
      )

      add_custom_target(
        AsanDLL ALL DEPENDS "${${target}_BINARY_DIR}/clang_rt.asan_dbg_dynamic-x86_64.dll"
      )
    endif()
  else()
    if(sanitizers MATCHES "^([Aa]ddress)$")
      message("[SANITIZERS] Building with Address sanitizer.")
      target_compile_options(
        ${target} INTERFACE -fsanitize=address -fno-omit-frame-pointer -fno-optimize-sibling-calls
                            -fsanitize-address-use-after-scope
      )
      target_link_options(
        ${target} INTERFACE -fsanitize=address -fno-omit-frame-pointer -fno-optimize-sibling-calls
        -fsanitize-address-use-after-scope
      )
    endif()
  endif()

  if(NOT CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    if(sanitizers MATCHES "^([Uu]ndefined)$")
      message("[SANITIZERS] Building with Undefined sanitizer.")
      target_compile_options(${target} INTERFACE -fsanitize=undefined)
      target_link_options(${target} INTERFACE -fsanitize=undefined)
    elseif(sanitizers MATCHES "^([Ll]eak)$")
      message("[SANITIZERS] Building with Leak sanitizer.")
      target_compile_options(${target} INTERFACE -fsanitize=leak)
      target_link_options(${target} INTERFACE -fsanitize=leak)
    elseif(sanitizers MATCHES "^([Aa]ddress:[Uu]ndefined)$")
      message("[SANITIZERS] Building with Address and Undefined sanitizers.")
      target_compile_options(
        ${target} INTERFACE -fsanitize=address,undefined -fno-omit-frame-pointer
                            -fno-optimize-sibling-calls -fsanitize-address-use-after-scope
      )
      target_link_options(
        ${target} INTERFACE -fsanitize=address,undefined -fno-omit-frame-pointer
        -fno-optimize-sibling-calls -fsanitize-address-use-after-scope
      )
    elseif(sanitizers MATCHES "^([Aa]ddress:[Uu]ndefined:[Ll]eak)$")
      message("[SANITIZERS] Building with Address, Undefined and Leak sanitizers.")
      target_compile_options(
        ${target} INTERFACE -fsanitize=address,undefined,leak -fno-omit-frame-pointer
                            -fno-optimize-sibling-calls -fsanitize-address-use-after-scope
      )
      target_link_options(
        ${target} INTERFACE -fsanitize=address,undefined,leak -fno-omit-frame-pointer
        -fno-optimize-sibling-calls -fsanitize-address-use-after-scope
      )
    elseif(sanitizers MATCHES "^([Aa]ddress:[Ll]eak)$")
      message("[SANITIZERS] Building with Address and Leak sanitizers.")
      target_compile_options(
        ${target} INTERFACE -fsanitize=address,leak -fno-omit-frame-pointer
                            -fno-optimize-sibling-calls -fsanitize-address-use-after-scope
      )
      target_link_options(
        ${target} INTERFACE -fsanitize=address,leak -fno-omit-frame-pointer
        -fno-optimize-sibling-calls -fsanitize-address-use-after-scope
      )
    elseif(sanitizers MATCHES "^([Uu]ndefined:[Ll]eak)$")
      message("[SANITIZERS] Building with Undefined and Leak sanitizers.")
      target_compile_options(${target} INTERFACE -fsanitize=undefined,leak)
      target_link_options(${target} INTERFACE -fsanitize=undefined,leak)
    elseif(sanitizers MATCHES "^([Mm]emory)$")
      message("[SANITIZERS] Building with Memory sanitizer.")
      target_compile_options(
        ${target} INTERFACE -fsanitize=memory -fno-optimize-sibling-calls
                            -fsanitize-memory-track-origins
      )
      target_link_options(
        ${target} INTERFACE -fsanitize=memory -fno-optimize-sibling-calls
        -fsanitize-memory-track-origins
      )
    elseif(sanitizers MATCHES "^([Tt]hread)$")
      message("[SANITIZERS] Building with Thread sanitizer.")
      target_compile_options(${target} INTERFACE -fsanitize=thread)
      target_link_options(${target} INTERFACE -fsanitize=thread)
    else()
      message("[SANITIZERS] Building with no sanitizer enabled.")
    endif()
  endif()
endfunction()
