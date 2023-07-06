file(GLOB CLOUDPONG_SOURCES *.cpp)

add_library(cloudpong STATIC ${CLOUDPONG_SOURCES})

target_include_directories(
    cloudpong 
    PUBLIC 
    ${CMAKE_SOURCE_DIR}/src/include)