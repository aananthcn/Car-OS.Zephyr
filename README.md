About
=====
The name of the project is AUTOSAR OS - Zephyr. This project will become the OSAL (Operating Systems Abstraction Layer) for CAR-OS (currently this is called as NammaAUTOSAR) project.

<br>
Idea: just like how Linux is the OSAL for Android, [Zephyr OS](https://www.zephyrproject.org/) will be the OSAL for CAR-OS.
<br><br><br>

Getting Started
===============

Pre-requisites
--------------
 * Setup zephyr project and SDK as given in https://docs.zephyrproject.org/latest/develop/getting_started/index.html
 * Preferably use Linux machine and setup in $HOME directory.


Setup and Build
---------------
 * `cd <base-path>`
 * `git clone https://github.com/aananthcn/autosar_os-zephyr.git`
 * `cd autosar_os-zephyr/`
 * `source ~/zephyrproject/.venv/bin/activate`
 * `source ~/zephyrproject/zephyr/zephyr-env.sh`
 * `west build -b rpi_pico .`

For further reading: https://blog.golioth.io/how-to-build-your-zephyr-app-in-a-standalone-folder/
