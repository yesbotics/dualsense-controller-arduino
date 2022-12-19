
#ifndef DUALSENSECONTROLLER_VALUES_H
#define DUALSENSECONTROLLER_VALUES_H

#include <Arduino.h>
#include "dual-sense-controller-types.h"
#include "dual-sense-controller-util.h"

const static bool DEFAULT_DIGITAL_BUTTON_VALUE = false;
static DualSenseControllerValueItem<bool> DIGITAL_BUTTONS[] = {
        {ButtonEnum::UP,         DualSenseControllerValueId::UP,          DEFAULT_DIGITAL_BUTTON_VALUE},
        {ButtonEnum::LEFT,       DualSenseControllerValueId::LEFT,        DEFAULT_DIGITAL_BUTTON_VALUE},
        {ButtonEnum::RIGHT,      DualSenseControllerValueId::RIGHT,       DEFAULT_DIGITAL_BUTTON_VALUE},
        {ButtonEnum::DOWN,       DualSenseControllerValueId::DOWN,        DEFAULT_DIGITAL_BUTTON_VALUE},
        {ButtonEnum::TRIANGLE,   DualSenseControllerValueId::TRIANGLE,    DEFAULT_DIGITAL_BUTTON_VALUE},
        {ButtonEnum::CIRCLE,     DualSenseControllerValueId::CIRCLE,      DEFAULT_DIGITAL_BUTTON_VALUE},
        {ButtonEnum::CROSS,      DualSenseControllerValueId::CROSS,       DEFAULT_DIGITAL_BUTTON_VALUE},
        {ButtonEnum::SQUARE,     DualSenseControllerValueId::SQUARE,      DEFAULT_DIGITAL_BUTTON_VALUE},
        {ButtonEnum::CREATE,     DualSenseControllerValueId::CREATE,      DEFAULT_DIGITAL_BUTTON_VALUE},
        {ButtonEnum::OPTIONS,    DualSenseControllerValueId::OPTIONS,     DEFAULT_DIGITAL_BUTTON_VALUE},
        {ButtonEnum::PS,         DualSenseControllerValueId::PLAYSTATION, DEFAULT_DIGITAL_BUTTON_VALUE},
        {ButtonEnum::TOUCHPAD,   DualSenseControllerValueId::TOUCHPAD,    DEFAULT_DIGITAL_BUTTON_VALUE},
        {ButtonEnum::MICROPHONE, DualSenseControllerValueId::MICROPHONE,  DEFAULT_DIGITAL_BUTTON_VALUE},
        {ButtonEnum::L1,         DualSenseControllerValueId::L1,          DEFAULT_DIGITAL_BUTTON_VALUE},
        {ButtonEnum::R1,         DualSenseControllerValueId::R1,          DEFAULT_DIGITAL_BUTTON_VALUE},
        {ButtonEnum::L2,         DualSenseControllerValueId::L2,          DEFAULT_DIGITAL_BUTTON_VALUE},
        {ButtonEnum::R2,         DualSenseControllerValueId::R2,          DEFAULT_DIGITAL_BUTTON_VALUE},
        {ButtonEnum::L3,         DualSenseControllerValueId::L3,          DEFAULT_DIGITAL_BUTTON_VALUE},
        {ButtonEnum::R3,         DualSenseControllerValueId::R3,          DEFAULT_DIGITAL_BUTTON_VALUE},
};
const static size_t DIGITAL_BUTTONS_SIZE = getArraySize(DIGITAL_BUTTONS);

const static uint8_t DEFAULT_ANALOG_BUTTON_VALUE = 0;
static DualSenseControllerValueItem <uint8_t> ANALOG_BUTTONS[] = {
        {ButtonEnum::L2, DualSenseControllerValueId::ANALOG_L2, DEFAULT_ANALOG_BUTTON_VALUE},
        {ButtonEnum::R2, DualSenseControllerValueId::ANALOG_R2, DEFAULT_ANALOG_BUTTON_VALUE},
};
const static size_t ANALOG_BUTTONS_SIZE = getArraySize(ANALOG_BUTTONS);

const static uint8_t DEFAULT_ANALOG_HAT_VALUE = 127;
static DualSenseControllerValueItem <uint8_t> ANALOG_HATS[] = {
        {AnalogHatEnum::LeftHatX,  DualSenseControllerValueId::LEFT_HAT_X,  DEFAULT_ANALOG_HAT_VALUE},
        {AnalogHatEnum::LeftHatY,  DualSenseControllerValueId::LEFT_HAT_Y,  DEFAULT_ANALOG_HAT_VALUE},
        {AnalogHatEnum::RightHatX, DualSenseControllerValueId::RIGHT_HAT_X, DEFAULT_ANALOG_HAT_VALUE},
        {AnalogHatEnum::RightHatY, DualSenseControllerValueId::RIGHT_HAT_Y, DEFAULT_ANALOG_HAT_VALUE},
};
const static size_t ANALOG_HATS_SIZE = getArraySize(ANALOG_HATS);


const static int16_t DEFAULT_SENSOR_VALUE = 0;
static DualSenseControllerValueItem <int16_t> SENSOR_VALUES[] = {
        {SensorEnum::aX, DualSenseControllerValueId::ACCELEROMETER_X, DEFAULT_SENSOR_VALUE},
        {SensorEnum::aY, DualSenseControllerValueId::ACCELEROMETER_Y, DEFAULT_SENSOR_VALUE},
        {SensorEnum::aZ, DualSenseControllerValueId::ACCELEROMETER_Z, DEFAULT_SENSOR_VALUE},
        {SensorEnum::gX, DualSenseControllerValueId::GYROSCOPE_X,     DEFAULT_SENSOR_VALUE},
        {SensorEnum::gY, DualSenseControllerValueId::GYROSCOPE_Y,     DEFAULT_SENSOR_VALUE},
        {SensorEnum::gZ, DualSenseControllerValueId::GYROSCOPE_Z,     DEFAULT_SENSOR_VALUE}
};
const static size_t SENSOR_VALUES_SIZE = getArraySize(SENSOR_VALUES);

const static int16_t DEFAULT_ORIENTATION_VALUE = 0;
static DualSenseControllerValueItem<float> ORIENTATION_VALUES[] = {
        {AngleEnum::Pitch, DualSenseControllerValueId::ORIENTATION_PITCH, DEFAULT_ORIENTATION_VALUE},
        {AngleEnum::Roll,  DualSenseControllerValueId::ORIENTATION_ROLL,  DEFAULT_ORIENTATION_VALUE},
};
const static size_t ORIENTATION_VALUES_SIZE = getArraySize(ORIENTATION_VALUES);

const static int16_t DEFAULT_FINGER_IS_TOUCHING_VALUE = 0;
static DualSenseControllerValueItem<bool> FINGER_IS_TOUCHING_VALUES[] = {
        {0, DualSenseControllerValueId::FINGER_1_IS_TOUCHING, DEFAULT_FINGER_IS_TOUCHING_VALUE},
        {1, DualSenseControllerValueId::FINGER_2_IS_TOUCHING, DEFAULT_FINGER_IS_TOUCHING_VALUE},
};
const static size_t FINGER_IS_TOUCHING_VALUES_SIZE = getArraySize(FINGER_IS_TOUCHING_VALUES);

const static int16_t DEFAULT_FINGER_X_VALUE = 0;
static DualSenseControllerValueItem <uint16_t> FINGER_X_VALUES[] = {
        {0, DualSenseControllerValueId::FINGER_1_X, DEFAULT_FINGER_X_VALUE},
        {1, DualSenseControllerValueId::FINGER_2_X, DEFAULT_FINGER_X_VALUE},
};
const static size_t FINGER_X_VALUES_SIZE = getArraySize(FINGER_X_VALUES);

const static int16_t DEFAULT_FINGER_Y_VALUE = 0;
static DualSenseControllerValueItem <uint16_t> FINGER_Y_VALUES[] = {
        {0, DualSenseControllerValueId::FINGER_1_Y, DEFAULT_FINGER_Y_VALUE},
        {1, DualSenseControllerValueId::FINGER_2_Y, DEFAULT_FINGER_Y_VALUE},
};
const static size_t FINGER_Y_VALUES_SIZE = getArraySize(FINGER_Y_VALUES);


const static bool DEFAULT_MIC_LED_VALUE = false;
const static uint8_t DEFAULT_BIG_RUMBLE_VALUE = 0;
const static uint8_t DEFAULT_SMALL_RUMBLE_VALUE = 0;
static DualSenseControllerOtherValues OTHER_VALUES = {
        DEFAULT_MIC_LED_VALUE,
        DEFAULT_BIG_RUMBLE_VALUE,
        DEFAULT_SMALL_RUMBLE_VALUE,
};

#endif //DUALSENSECONTROLLER_VALUES_H


