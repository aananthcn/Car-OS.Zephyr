# About
The name of the project is AUTOSAR OS - Zephyr. This project will become the OSAL (Operating Systems Abstraction Layer) for CAR-OS (currently this is called as NammaAUTOSAR) project.

<br>
Idea: just like how Linux is the OSAL for Android, [Zephyr OS](https://www.zephyrproject.org/) will be the OSAL for CAR-OS.
<br><br><br>

# Getting Started

## Linux

### Pre-requisites
 * Setup zephyr project and SDK as given in https://docs.zephyrproject.org/latest/develop/getting_started/index.html
   * Preferably use Linux machine and setup in $HOME directory.


### Setup and Build
 * `cd <base-path>`
 * `git clone https://github.com/aananthcn/autosar_os-zephyr.git`
 * `cd autosar_os-zephyr/`
 * `source ~/zephyrproject/.venv/bin/activate`
 * `source ~/zephyrproject/zephyr/zephyr-env.sh`
 * `west build -b rpi_pico .`

For further reading: https://blog.golioth.io/how-to-build-your-zephyr-app-in-a-standalone-folder/

<br>

## MSYS2 on Windows

### Pre-requisites
 * Setup MSYS2 as described in https://www.msys2.org/
 * Install packages as described below
   * `pacman -S make mingw-w64-x86_64-cmake mingw-w64-x86_64-python3-devel mingw-w64-x86_64-gcc mingw-w64-x86_64-python3 mingw-w64-x86_64-python3-ruamel-yaml mingw-w64-x86_64-ninja mingw-w64-x86_64-gperf mingw-w64-x86_64-wget mingw-w64-x86_64-7zip`
 * Setup zephyr project and SDK as given in https://docs.zephyrproject.org/latest/develop/getting_started/index.html
   * Preferably create a new partion in windows (E:) and install it there.
   * Note: you will find an error "`ERROR: No matching distribution found for windows-curses`". You can safely ingore it for now.


### Setup and Build
 * `cd <base-path>`
 * `git clone https://github.com/aananthcn/autosar_os-zephyr.git`
 * `cd autosar_os-zephyr/`
 * `bash`
 * `source e:/zephyrproject/zephyr/zephyr-env.sh`
 * `west build -b rpi_pico .`

<br>

## CMake learnings
 * Following cflags are used by rpi_pico in Zephyr
   * `-mcpu=cortex-m0plus -mthumb -mabi=aapcs -mfp16-format=ieee -mtp=soft`
 * Following CMakeLists.txt additions helped
    ```
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
    ```
