cmake_minimum_required(VERSION 3.20)

project(cloudpong)

include(FetchContent)


# protocol dependencies
FetchContent_Declare(
  yyjson
  GIT_REPOSITORY https://github.com/ibireme/yyjson
  GIT_TAG master
)
set(YYJSON_BUILD_TESTS OFF CACHE BOOL "" FORCE)  # disable tests
set(YYJSON_BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)  # static linking
FetchContent_MakeAvailable(yyjson)

FetchContent_Declare(
    civetweb
    GIT_REPOSITORY https://github.com/civetweb/civetweb.git
    GIT_TAG master  # Use a stable release tag or specific commit
)
set(CIVETWEB_ENABLE_CXX ON CACHE BOOL "" FORCE)  # Enable C++ wrapper
set(CIVETWEB_BUILD_TESTING OFF CACHE BOOL "" FORCE)  # Disable tests
set(CIVETWEB_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)  # Disable examples
FetchContent_MakeAvailable(civetweb)

# server dependencies


# client dependencies
FetchContent_Declare(
  SDL3
  GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
  GIT_TAG main
)
set(SDL_SHARED OFF CACHE BOOL "" FORCE)  # for static linking
set(SDL_STATIC ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(SDL3)

FetchContent_Declare(
  wxWidgets
  GIT_REPOSITORY https://github.com/wxWidgets/wxWidgets.git
  GIT_TAG master  # or latest stable
)
set(wxBUILD_SHARED OFF CACHE BOOL "" FORCE)
set(wxBUILD_TESTS OFF CACHE BOOL "" FORCE)
set(wxBUILD_SAMPLES OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(wxWidgets)

add_executable(cloudpong client/main.cpp)
target_link_libraries(cloudpong PRIVATE wx::core wx::base SDL3-static)

