#pragma once

// #include <stdint.h>
// #include <Arduino.h>
// #include <math.h>
// //DATA TYPES

// #define GetVarName(var) #var
typedef uint8_t ubyte;
// typedef int8_t byte;
typedef uint16_t uint;
typedef uint32_t ulong;
typedef int32_t long;

// // UTILITY
#include "utility\discoMath.h"
#include "utility\discoData.h"

// #include "dataTypes/vec.h"
#include "dataTypes/cstring.h"
#include "dataTypes/crgbw.h"
#include "dataTypes/noType.h"
#include "dataTypes/discoArray.h"
// #include "dataTypes/keyValuePair.h"
#include "dataTypes/color.h"
// #include "dataTypes/vector3int.h"
// #include "dataTypes/vector3Byte.h"
// #include "dataTypes/MPUData.h"

//ACTIONS
#include "actions\action.h"
#include "actions\actionArray.h"
// #include "actions\propertyGetter.h"
// #include "actions\loggerActions.h"
// #include "actions\valueMapper.h"
// #include "actions\functionAction.h"
// #include "actions\polygonConstructor.h"

// #include "event\event.h"

//ROBOT IO TRANSMITTERS
// #include "robot-io/robotIOTransmitterBase.h"
// #include "robot-io/robotIOTransmitter.h"

//SYSTEMS
#include "systems/loopSystem.h"
// #include "systems/robotIOSystem.h"

//DATA GETTERS
// #include "dataGetters/dataGetterAction.h"
// #include "dataGetters/ultraSound.h"
// #include "funcs/ultraSound.h"

//RADIO
// #include "radio/radio.h"
// #include "radio/radioReceiver.h"
// #include "radio/radioTransmitter.h"

// #include "mpu6050/mpuPhysicsAction.h"
// #include "mpu6050/mpu6050Base.h"
// #include "mpu6050/mpu6050.h"

// #include "I2Cdev.h"
// #include "MPU6050_6Axis_MotionApps20.h"
// #include "imu/imuData.h"
// #include "imu/imu_mpu6050.h"
// #include "imu/imu.h"
// #include "actions\mpuRobotIOTransmitter.h"

//SMART ACTIONS
// #include "actions/loopDataLogger.h"
// #include "actions\timeLapseAction.h"
// #include "actions\loopAction.h"
// #include "actions\reverseAction.h"
// #include "actions\smoothAction.h"
// #include "actions\filterZeroAction.h"
// #include "actions\sinusoidLerpAction.h"
// #include "actions\valueChangeAction.h"
// #include "actions\hueAnimAction.h"
// #include "actions\jsonTransmitAction.h"
// #include "actions\mpuTransmitAction.h"

//Actions-Data-Analysis
// #include "actions-data-analysis/directionChangeDetector.h"
// #include "actions-data-analysis/periodDetector.h"

//OBJECTS
// #include "objects/animator.h"
// #include "objects/dataMonitor.h"

//OBSERVABLES
// #include "observable/observable.h"
// #include "observable/obsDataGetter.h"
// #include "observable/transformerObservable.h"
// #include "observable/dataSmoother.h"

// //SENSORS

//leds
#include "colorLight\colorLight.h"
#include "ledStrip/ledStripBase.h"
#include "ledStrip/rgbwLedStrip.h"
#include "ledStrip/rgbLedStrip.h"

// ANIMATION
// #include "actions/rgbAnimAction.h"
