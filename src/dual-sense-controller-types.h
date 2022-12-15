#ifndef DUALSENSECONTROLLER_TYPES_H
#define DUALSENSECONTROLLER_TYPES_H

#include <Arduino.h>

enum class DualSenseControllerStateEvent {
    INITIALIZED, CONNECTED, DISCONNECTED
};

enum class DualSenseControllerValueId {
    LEFT_HAT_X, LEFT_HAT_Y, RIGHT_HAT_X, RIGHT_HAT_Y,
    ANALOG_L2, ANALOG_R2,
    L1, R1, L2, R2, L3, R3,
    RIGHT, DOWN, LEFT, UP,
    TRIANGLE, CIRCLE, CROSS, SQUARE,
    CREATE, OPTIONS, PLAYSTATION, TOUCHPAD, MICROPHONE,
    ACCELEROMETER_X, ACCELEROMETER_Y, ACCELEROMETER_Z,
    GYROSCOPE_X, GYROSCOPE_Y, GYROSCOPE_Z,
    ORIENTATION_PITCH, ORIENTATION_ROLL,
    FINGER_1_IS_TOUCHING, FINGER_1_X, FINGER_1_Y,
    FINGER_2_IS_TOUCHING, FINGER_2_X, FINGER_2_Y
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

using DualSenseControllerValueEventCallback = void (*)(DualSenseControllerValueId id, int16_t value);

struct DualSenseControllerOptions {
    DualSenseControllerStateEventCallback stateEventCallback;
    DualSenseControllerValueEventCallback valueEventCallback;
    uint16_t pollingInterval; // interval for value change check
    bool checkDigitalButtons;
    bool checkAnalogButtons;
    bool checkAnalogHats;
    bool checkImu;
    bool checkTouchpad;
    bool checkOrientation;
    uint8_t analogHatThreshold;
};

#endif //DUALSENSECONTROLLER_TYPES_H
