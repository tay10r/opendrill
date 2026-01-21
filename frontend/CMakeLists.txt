cmake_minimum_required(VERSION 3.20)

project(opendrill)

if(POLICY CMP0135)
  cmake_policy(SET CMP0135 NEW)
endif()

include(FetchContent)

FetchContent_Declare(glow
  URL "https://github.com/tay10r/glow/archive/refs/tags/v0.3.0.zip"
  URL_HASH "SHA256=3ea2705da47e9d415f08df1aa1cb69568009a95aefc6814c63bcd50b93e068a0"
)

FetchContent_MakeAvailable(glow)

add_executable(opendrill
  src/app.cpp
  src/map_widget.h
  src/map_widget.cpp
  src/tool.h
  src/line_tool.h
  src/line_tool.cpp
  src/drill.h
  src/drill.cpp
)

target_compile_features(opendrill PRIVATE cxx_std_20)

target_link_libraries(opendrill
  PRIVATE
    glow::glow
    glow::main
)

if(EMSCRIPTEN)
  file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/index.html" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
endif()
