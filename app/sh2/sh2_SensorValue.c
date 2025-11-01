/*
 * Copyright 2015-21 CEVA, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License and 
 * any applicable agreements you may have with CEVA, Inc.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*
 * BNO080 Sensor Event decoding
 */

#include "sh2_SensorValue.h"
#include "sh2_err.h"
#include "sh2_util.h"

#include <stdio.h>

#define SCALE_Q(n) (1.0f / (1 << n))

const float scaleRadToDeg = 180.0f / 3.14159265358f;

// ------------------------------------------------------------------------
// Forward declarations

static int decodeGameRotationVector(sh2_SensorValue_t *value, const sh2_SensorEvent_t *event);
static int decodeRawAccelerometer(sh2_SensorValue_t *value, const sh2_SensorEvent_t *event);

// ------------------------------------------------------------------------
// Public API

int sh2_decodeSensorEvent(sh2_SensorValue_t *value, const sh2_SensorEvent_t *event)
{
    // Fill out fields of *value based on *event, converting data from message representation
    // to natural representation.

    int rc = SH2_OK;

    value->sensorId = event->reportId;
    value->timestamp = event->timestamp_uS;

    if (value->sensorId != SH2_GYRO_INTEGRATED_RV) {
        value->sequence = event->report[1];
        value->status = event->report[2] & 0x03;
    }
    else {
        value->sequence = 0;
        value->status = 0;
    }

    // extract delay field (100uS units)
    
    
    switch (value->sensorId) {
        case SH2_GAME_ROTATION_VECTOR:
            rc = decodeGameRotationVector(value, event);
            break;
        case SH2_RAW_ACCELEROMETER:
            rc = decodeRawAccelerometer(value, event);
        default:
            // Unknown report id
            rc = SH2_ERR;
            break;
    }

    return rc;
}

// ------------------------------------------------------------------------
// Private utility functions

static int decodeGameRotationVector(sh2_SensorValue_t *value, const sh2_SensorEvent_t *event)
{
    value->un.gameRotationVector.i = read16(&event->report[4]) * SCALE_Q(14);
    value->un.gameRotationVector.j = read16(&event->report[6]) * SCALE_Q(14);
    value->un.gameRotationVector.k = read16(&event->report[8]) * SCALE_Q(14);
    value->un.gameRotationVector.real = read16(&event->report[10]) * SCALE_Q(14);

    return SH2_OK;
}

static int decodeRawAccelerometer(sh2_SensorValue_t *value, const sh2_SensorEvent_t *event)
{
    value->un.rawAccelerometer.x = read16(&event->report[4]);
    value->un.rawAccelerometer.y = read16(&event->report[6]);
    value->un.rawAccelerometer.z = read16(&event->report[8]);
    value->un.rawAccelerometer.timestamp = read32(&event->report[12]);

    return SH2_OK;
}
