cmake_minimum_required(VERSION 3.20.0)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(Car_OS_Zephyr)


set(CMAKE_VERBOSE_MAKEFILE TRUE)

# The default app target from Zephyr
target_sources(app PRIVATE src/main.c)



include(${CMAKE_CURRENT_SOURCE_DIR}/car-os/path_defs.cmake)
#######################################################################################################
# Implementation as per the link below:
# https://github.com/zephyrproject-rtos/zephyr/tree/main/samples/application_development/external_lib
#######################################################################################################
# The external static library that we are linking with (i.e., libCar_OS) does not know how to build for
# this platform. So we export all the flags used in this zephyr build to the external build system.
#
# Other external build systems may be self-contained enough that they do not need any build information
# from zephyr. Or they may be incompatible with certain zephyr options and need them to be filtered out
zephyr_get_include_directories_for_lang_as_string(
  C includes
)
zephyr_get_system_include_directories_for_lang_as_string(
  C system_includes
)
zephyr_get_compile_definitions_for_lang_as_string(
  C definitions
)
zephyr_get_compile_options_for_lang_as_string(
  C options
)

set(
  external_project_cflags
  "${includes} ${definitions} ${options} ${system_includes}"
)

include(ExternalProject)


# Add an external project to be able download and build the third
# party library. In this case downloading is not necessary as it has
# been committed to the repository.
set(CAR_OS_SRC_DIR   ${CMAKE_CURRENT_SOURCE_DIR}/car-os)
set(CAR_OS_BUILD_DIR ${CMAKE_CURRENT_BINARY_DIR}/car-os)
set(CAR_OS_INCLUDE_DIR ${CAR_OS_SRC_DIR}/include)

if(CMAKE_GENERATOR STREQUAL "Unix Makefiles")
  # https://www.gnu.org/software/make/manual/html_node/MAKE-Variable.html
  set(submake "$(MAKE)")
else() # Obviously no MAKEFLAGS. Let's hope a "make" can be found somewhere.
  set(submake "make")
endif()


ExternalProject_Add(
  Car_OS_project                 # Name for custom target
  PREFIX     ${CAR_OS_BUILD_DIR} # Root dir for entire project
  SOURCE_DIR ${CAR_OS_SRC_DIR}
  BINARY_DIR ${CAR_OS_SRC_DIR}   # This particular build system is invoked from the root
  CONFIGURE_COMMAND ""           # Skip configuring the project, e.g. with autoconf
  BUILD_COMMAND ${submake}
  PREFIX=${CAR_OS_BUILD_DIR}
  CC=${CMAKE_C_COMPILER}
  AR=${CMAKE_AR}
  CFLAGS=${external_project_cflags}
  INSTALL_COMMAND ""             # This particular build system has no install command
  BUILD_BYPRODUCTS ${CAR_OS_BASE_DIR_PATH}/libCar_OS.a
)


# Create a wrapper CMake library that our app can link with
add_library(Car_OS_lib STATIC IMPORTED GLOBAL)
add_dependencies(
  Car_OS_lib
  Car_OS_project
)
set_target_properties(Car_OS_lib PROPERTIES IMPORTED_LOCATION             ${CAR_OS_BASE_DIR_PATH}/libCar_OS.a)
set_target_properties(Car_OS_lib PROPERTIES INTERFACE_INCLUDE_DIRECTORIES ${CAR_OS_INCLUDE_DIR})

target_link_libraries(app PUBLIC Car_OS_lib)
target_include_directories(app PUBLIC
  ${CAR_OS_BOARDSOC_PATH}
  ${CAR_OS_INCLUDE_DIR}/autosar
  ${CAR_OS_INCLUDE_DIR}/car_os
  ${CAR_OS_SYSGEN_S_PATH}
  ${CAR_OS_ASR_SRVC_PATH}/Os/include
  ${CAR_OS_ASR_SRVC_PATH}/EcuM/api
  ${CAR_OS_ASR_MCAL_PATH}/Dio/api
)

message(STATUS "Added Car-OS project's makefile to the CMake list.")
