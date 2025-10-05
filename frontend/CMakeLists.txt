cmake_minimum_required(VERSION 3.20)

project(opendrill)

if(POLICY CMP0135)
  cmake_policy(SET CMP0135 NEW)
endif()

include(FetchContent)

FetchContent_Declare(uikit
  URL "https://github.com/tay10r/glow/archive/refs/tags/v0.2.3.zip"
  URL_HASH "SHA256=977d949fb8deafa425feb956a99515e0920b8dfa747fd09cfaff349dc8a54015"
)

FetchContent_MakeAvailable(uikit)

add_executable(opendrill
  app.cpp
)

target_compile_features(opendrill PRIVATE cxx_std_20)

target_link_libraries(opendrill
  PRIVATE
    uikit::uikit
    uikit::main
)

if(EMSCRIPTEN)
  file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/index.html" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
endif()
