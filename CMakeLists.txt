cmake_minimum_required(VERSION 3.0)

project(cloudpong)

find_package(PkgConfig REQUIRED)
pkg_search_module(gstreamer REQUIRED IMPORTED_TARGET gstreamer-1.0)
pkg_search_module(gstreamer-app REQUIRED IMPORTED_TARGET gstreamer-app-1.0)
pkg_search_module(gstreamer-rtsp REQUIRED IMPORTED_TARGET gstreamer-rtsp-1.0)
pkg_search_module(gstreamer-rtsp-server REQUIRED IMPORTED_TARGET gstreamer-rtsp-server-1.0)


add_subdirectory(extern)

#add_subdirectory(src)