/*
 * Created on Thu Aug 11 2022 11:48:03 PM
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
#ifndef STD_TYPES_H
#define STD_TYPES_H


#include "Compiler.h"
#include "Platform_Types.h"


typedef uint8 Std_ReturnType;

// OS
#define E_OK            0
#define E_NOT_OK        1

// SCHM
#define SCHM_E_OK 0 /* [SWS_Rte_07289] */
#define SCHM_E_LIMIT 130 /* [SWS_Rte_07290] */
#define SCHM_E_NO_DATA 131 /* [SWS_Rte_07562] */
#define SCHM_E_TRANSMIT_ACK 132 /* [SWS_Rte_07563] */
#define SCHM_E_IN_EXCLUSIVE_AREA 135 /* [SWS_Rte_02747] */
#define SCHM_E_TIMEOUT 129 /* [SWS_Rte_07054] */
#define SCHM_E_LOST_DATA 64 /* [SWS_Rte_02312] */


typedef struct {
        uint16 vendorID;
        uint16 moduleID;
        uint8 sw_major_version;
        uint8 sw_minor_version;
        uint8 sw_patch_version;
} Std_VersionInfoType;


#endif