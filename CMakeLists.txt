cmake_minimum_required(VERSION 3.20.0)
#set(CMAKE_VERBOSE_MAKEFILE ON)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(autosar_os)


target_sources(app PRIVATE src/main.c)