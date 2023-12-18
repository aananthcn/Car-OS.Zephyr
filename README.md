# Car-OS.Zephyr
The Car here stands for <u>C</u>lassic <u>a</u>utosa<u>r</u>. And the OS.Zephyr means Operating System software on top of Zephyr RTOS. This means Car-OS runs on top of Zephyr, which is akin to Android on top of Linux. 

<br>

This project is created this way for 3 reasons:
 * Zephyr OS supports variety of boards and therefore this project can easily support any hardware with little effort.
 * People working on this project can focus on new ideas or on AUTOSAR specs than re-doing what Zephyr OS team had done it.
 * [Linux Foundation is making effort to get Safety (SIL3) certification](https://www.zephyrproject.org/update-safety-standard-compliance/). So this work could/will be used on Cars one day.


<br>

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

## Development Setup - HARDWARE:
----
![Pi Pico Development Setup](docs/rpi-pico-dev-setup.png?raw=true "Title")

* Raspberry Pi Pico with pins soldered => [check this link](https://robocraze.com/products/raspberry-pi-pico-with-headers-and-micro-usb-cable)
* Cytron Maker Pi Pico Base => [check this link](https://robu.in/product/cytron-maker-pi-pico-base-without-pico/)
* DTech FTDI USB to TTL Serial Converter => [Amazon: PL2303TA chip](https://amzn.eu/d/eYsRoTC)
  * Note for Win11: Install driver from this link [prolific-driverinstaller-v1200](https://www.driverscloud.com/en/services/GetInformationDriver/72590-84992/delock-pl2303-prolific-driverinstaller-v1200zip)
* Any debugger with SWD pin interface support => [check this link](https://in.rsdelivers.com/product/segger/80800-j-link-base/segger-j-link-base-emulator/1311319)
  * Also planning to support ELF to UF2 image conversion so that developers can flash the image and use print statements to see the debug output.
  * For SWD, buy 20 pin JTAG cable and cut & crimp it for SWD => [check this link](https://robu.in/product/2-54mm-pitch-20-pin-jtag-isp-avr-cable/)
* 2 x Grove 4-pin => [check this link](https://www.fabtolab.com/grove-universal-cable?search=grove%204%20pin)
* ENC28J60 Ethernet LAN controller => [check this link](https://robocraze.com/products/enc28j60-ethernet-lan-module)

<br><br>


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
