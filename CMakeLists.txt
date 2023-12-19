cmake_minimum_required(VERSION 3.20.0)
#set(CMAKE_VERBOSE_MAKEFILE ON)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(autosar_os)


# The default app target from Zephyr
target_sources(app PRIVATE src/main.c)
add_dependencies(app Car_OS)
target_link_libraries(app PRIVATE libCar_OS)
include(${CMAKE_CURRENT_SOURCE_DIR}/car-os/path_defs.cmake)
target_include_directories(app PUBLIC
  ${CAR_OS_BOARD_PATH}
  ${CMAKE_CURRENT_SOURCE_DIR}/car-os/submodules/SL/Os/include
  ${CMAKE_CURRENT_SOURCE_DIR}/car-os/include/autosar
  ${CMAKE_CURRENT_SOURCE_DIR}/car-os/include/car_os
  ${CMAKE_CURRENT_SOURCE_DIR}/car-os/tools/os_builder/src
)


# Custom target -- this is where Car-OS.Zephyr would come in
add_custom_target(
	Car_OS
	COMMAND make 
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/car-os/
	BYPRODUCTS libCar_OS.la
)
add_library(libCar_OS STATIC IMPORTED)
add_dependencies(libCar_OS Car_OS)
target_link_libraries(libCar_OS INTERFACE debug libCar_OS)
set_target_properties(libCar_OS PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/car-os/libCar_OS.la)
