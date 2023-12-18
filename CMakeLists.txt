cmake_minimum_required(VERSION 3.20.0)
#set(CMAKE_VERBOSE_MAKEFILE ON)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(autosar_os)


# The default app target from Zephyr
target_sources(app PRIVATE src/main.c)
add_dependencies(app Lin)
target_link_libraries(app PRIVATE libLin)


# Custom target -- this is where Car-OS.Zephyr would come in
add_custom_target(
	Lin
	COMMAND make 
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/car-os/Lin
	BYPRODUCTS libLin.la
)
add_library(libLin STATIC IMPORTED)
add_dependencies(libLin Lin)
target_link_libraries(libLin INTERFACE debug libLin)
set_target_properties(libLin PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/car-os/Lin/libLin.la)
