#ifndef DUALSENSECONTROLLER_TYPES_H
#define DUALSENSECONTROLLER_TYPES_H

#include <Arduino.h>

enum class DualSenseControllerStateEvent : byte {
    INITIALIZED = 0,
    CONNECTED = 1,
    DISCONNECTED = 2,
    PAIRING = 3
};

enum class DualSenseControllerValueId : byte {
    PLAYSTATION = 0,
    CREATE = 1,
    OPTIONS = 2,
    TOUCHPAD = 3,
    MICROPHONE = 4,
    LEFT_HAT_X = 5,
    LEFT_HAT_Y = 6,
    RIGHT_HAT_X = 7,
    RIGHT_HAT_Y = 8,
    ANALOG_L2 = 9,
    ANALOG_R2 = 10,
    L1 = 11,
    R1 = 12,
    L2 = 13,
    R2 = 14,
    L3 = 15,
    R3 = 16,
    RIGHT = 17,
    DOWN = 18,
    LEFT = 19,
    UP = 20,
    TRIANGLE = 21,
    CIRCLE = 22,
    CROSS = 23,
    SQUARE = 24,
    ACCELEROMETER_X = 25,
    ACCELEROMETER_Y = 26,
    ACCELEROMETER_Z = 27,
    GYROSCOPE_X = 28,
    GYROSCOPE_Y = 29,
    GYROSCOPE_Z = 30,
    ORIENTATION_PITCH = 31,
    ORIENTATION_ROLL = 32,
    FINGER_1_IS_TOUCHING = 33,
    FINGER_1_X = 34,
    FINGER_1_Y = 35,
    FINGER_2_IS_TOUCHING = 36,
    FINGER_2_X = 37,
    FINGER_2_Y = 38
};

template<typename T>
struct DualSenseControllerValueItem {
    byte ps5LibId;
    DualSenseControllerValueId id;
    T value;
};


struct DualSenseControllerOtherValues {
    bool micLed;
    uint8_t bigRumble;
    uint8_t smallRumble;
};

enum class DualSenseControllerLedColor : uint32_t {
    /** r = 255, g = 0, b = 0 */
    RED = 0xFF0000,
    /** r = 0, g = 255, b = 0 */
    GREEN = 0xFF00,
    /** r = 0, g = 0, b = 255 */
    BLUE = 0xFF,
    /** r = 255, g = 235, b = 4 */
    YELLOW = 0xFFEB04,
    /** r = 0, g = 255, b = 255 */
    LIGHTBLUE = 0xFFFF,
    /** r = 255, g = 0, b = 255 */
    PURPLE = 0xFF00FF,
    /** r = 255, g = 255, b = 255 */
    WHITE = 0xFFFFFF,
    /** r = 0, g = 0, b = 0 */
    BLACK = 0x00,
    OFF = 0x00,
    GREY = 0x808080,
};

using DualSenseControllerStateEventCallback = void (*)(DualSenseControllerStateEvent event);

using DualSenseControllerValueChangeEventCallback = void (*)(DualSenseControllerValueId id, int16_t value);

struct DualSenseControllerOptions {
    DualSenseControllerOptions(
            DualSenseControllerStateEventCallback stateEventCallback = nullptr,
            DualSenseControllerValueChangeEventCallback valueChangeEventCallback = nullptr,
            uint16_t pollingInterval = 25,
            bool pollDigitalButtons = true,
            bool pollAnalogButtons = true,
            bool pollAnalogHats = true,
            bool pollImu = false,
            bool pollTouchpad = false,
            bool pollOrientation = false,
            uint8_t analogHatThreshold = 2
    ) :
            stateEventCallback{stateEventCallback},
            valueChangeEventCallback{valueChangeEventCallback},
            pollingInterval{pollingInterval},
            pollDigitalButtons{pollDigitalButtons},
            pollAnalogButtons{pollAnalogButtons},
            pollAnalogHats{pollAnalogHats},
            pollImu{pollImu},
            pollTouchpad{pollTouchpad},
            pollOrientation{pollOrientation},
            analogHatThreshold{analogHatThreshold} {};

    DualSenseControllerStateEventCallback stateEventCallback;
    DualSenseControllerValueChangeEventCallback valueChangeEventCallback;
    uint16_t pollingInterval; // interval for value change check
    bool pollDigitalButtons;
    bool pollAnalogButtons;
    bool pollAnalogHats;
    bool pollImu;
    bool pollTouchpad;
    bool pollOrientation;
    uint8_t analogHatThreshold;
};


#endif //DUALSENSECONTROLLER_TYPES_H

