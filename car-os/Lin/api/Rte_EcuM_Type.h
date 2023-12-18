/*
 * Created on Sat Aug 27 2022 9:11:10 PM
 *
 * The MIT License (MIT)
 * Copyright (c) 2022 Aananth C N
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 * and associated documentation files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial
 * portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
 * TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
#ifndef RTE_ECUM_TYPE_H
#define RTE_ECUM_TYPE_H

#include <Platform_Types.h>



typedef uint8 EcuM_UserType;
typedef uint32 EcuM_TimeType;



#define ECUM_BOOT_TARGET_APP            0
#define ECUM_BOOT_TARGET_OEM_BOOTLOADER 1
#define ECUM_BOOT_TARGET_SYS_BOOTLOADER 2

typedef uint8 EcuM_BootTargetType;



#define ECUM_CAUSE_UNKNOWN      0
#define ECUM_CAUSE_ECU_STATE    1
#define ECUM_CAUSE_WDGM         2
#define ECUM_CAUSE_DCM          3

typedef uint8 EcuM_ShutdownCauseType;



typedef uint16 EcuM_ShutdownModeType;


#define ECUM_SHUTDOWN_TARGET_SLEEP      0x0
#define ECUM_SHUTDOWN_TARGET_RESET      0x1
#define ECUM_SHUTDOWN_TARGET_OFF        0x2

typedef uint8 EcuM_ShutdownTargetType;




#endif