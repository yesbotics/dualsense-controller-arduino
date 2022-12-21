#include <dual-sense-controller-types.h>

#include <Arduino.h>

void onStateEvent(DualSenseControllerState state);

void onValueChangeEvent(DualSenseControllerValueId id, int16_t value);

void printValueIfDebugPrint(String s, int16_t value);

#define DUALSENSE_CONTROLLER_VARIANT_USB 0x00
#define DUALSENSE_CONTROLLER_VARIANT_BLUETOOTH 0x01

/****************************** CONFIG START ****************************************/

/* For Bluetooth connected Controller uncomment following line */
#define DUALSENSE_CONTROLLER_VARIANT DUALSENSE_CONTROLLER_VARIANT_BLUETOOTH
/* OR for USB connected Controller comment previous line and uncomment following line */
//#define DUALSENSE_CONTROLLER_VARIANT DUALSENSE_CONTROLLER_VARIANT_USB

/* start sketch in pairing mode set to true (only relevant for Bluetooth variant) */
const bool PAIR_CONTROLLER_WHILE_SETUP = false;

/* enable serial print outs for debugging purposes */
const bool DEBUG_PRINT = true;

/****************************** CONFIG END ******************************************/

DualSenseControllerOptions controllerOptions{
        onStateEvent,
        onValueChangeEvent,
        10,
        true,
        true,
        true,
        false,
        false,
        false,
        2
};


#if DUALSENSE_CONTROLLER_VARIANT == DUALSENSE_CONTROLLER_VARIANT_BLUETOOTH

#include <DualSenseControllerBt.h>

DualSenseControllerBt controller(controllerOptions);

#else

#include <DualSenseControllerUsb.h>

DualSenseControllerUsb controller(controllerOptions);

#endif


uint8_t playerLedMask = 0b00011;

void setup() {
    Serial.begin(115200);
    Serial.println(F("setup(): "));
    delay(1000);
    bool inited = controller.init();
    if (!inited) {
        Serial.println(F("Error: initialization failed"));
        while (true);
    }
#if DUALSENSE_CONTROLLER_VARIANT == DUALSENSE_CONTROLLER_VARIANT_BLUETOOTH
    if (PAIR_CONTROLLER_WHILE_SETUP) {
        Serial.println(F("pair()"));
        controller.pair();
    }
#endif
}

void loop() {
    controller.poll();
}

void onStateEvent(DualSenseControllerState state) {
    if (DEBUG_PRINT) Serial.println(F("onStateEvent(): "));
    switch (state) {
        case DualSenseControllerState::INITIALIZED:
            if (DEBUG_PRINT) Serial.println(F("INITIALIZED"));
            break;
        case DualSenseControllerState::CONNECTED:
            if (DEBUG_PRINT) Serial.println(F("CONNECTED"));
            break;
        case DualSenseControllerState::DISCONNECTED:
            if (DEBUG_PRINT) Serial.println(F("DISCONNECTED"));
            break;
    }
}

void onValueChangeEvent(DualSenseControllerValueId id, int16_t value) {
    if (DEBUG_PRINT) Serial.println(F("onValueEvent(): "));
    switch (id) {

        case DualSenseControllerValueId::PLAYSTATION:
            printValueIfDebugPrint(F("PLAYSTATION"), value);
#if DUALSENSE_CONTROLLER_VARIANT == DUALSENSE_CONTROLLER_VARIANT_BLUETOOTH
            if (value) controller.disconnect();
#endif
            break;
        case DualSenseControllerValueId::MICROPHONE:
            printValueIfDebugPrint(F("MICROPHONE"), value);
            if (value) controller.toggleMicLed();
            break;
        case DualSenseControllerValueId::TOUCHPAD:
            printValueIfDebugPrint(F("TOUCHPAD"), value);
            controller.setLed(value ? DualSenseControllerLedColor::LIGHTBLUE : DualSenseControllerLedColor::BLUE);
            break;
        case DualSenseControllerValueId::CREATE:
            printValueIfDebugPrint(F("CREATE"), value);
            if (value) controller.setLed(DualSenseControllerLedColor::YELLOW);
            break;
        case DualSenseControllerValueId::OPTIONS:
            printValueIfDebugPrint(F("OPTIONS"), value);
            if (value) controller.setLed(DualSenseControllerLedColor::PURPLE);
            break;

        case DualSenseControllerValueId::UP:
            printValueIfDebugPrint(F("UP"), value);
            if (value) {
                controller.setLeftTriggerForce(0, 255);
                controller.setLed(DualSenseControllerLedColor::WHITE);
            } else controller.setLed(DualSenseControllerLedColor::GREY);
            break;
        case DualSenseControllerValueId::RIGHT:
            printValueIfDebugPrint(F("RIGHT"), value);
            if (value) {
                controller.setLeftTriggerSection(80, 160);
                controller.setLed(DualSenseControllerLedColor::WHITE);
            } else controller.setLed(DualSenseControllerLedColor::GREY);
            break;
        case DualSenseControllerValueId::LEFT:
            printValueIfDebugPrint(F("LEFT"), value);
            if (value) {
                controller.setLeftTriggerForceEffect(
                        0, true, 0, 80, 255, 50
                );
                controller.setLed(DualSenseControllerLedColor::WHITE);
            } else controller.setLed(DualSenseControllerLedColor::GREY);
            break;
        case DualSenseControllerValueId::DOWN:
            printValueIfDebugPrint(F("DOWN"), value);
            if (value) {
                controller.clearLeftTriggerForce();
                controller.setLed(DualSenseControllerLedColor::WHITE);
            } else controller.setLed(DualSenseControllerLedColor::GREY);
            break;

        case DualSenseControllerValueId::TRIANGLE:
            printValueIfDebugPrint(F("TRIANGLE"), value);
            if (value) {
                controller.setRightTriggerForce(0, 255);
                controller.setLed(DualSenseControllerLedColor::WHITE);
            } else controller.setLed(DualSenseControllerLedColor::GREY);
            break;
        case DualSenseControllerValueId::CIRCLE:
            printValueIfDebugPrint(F("CIRCLE"), value);
            if (value) {
                controller.setRightTriggerSection(80, 160);
                controller.setLed(DualSenseControllerLedColor::WHITE);
            } else controller.setLed(DualSenseControllerLedColor::GREY);
            break;
        case DualSenseControllerValueId::SQUARE:
            printValueIfDebugPrint(F("SQUARE"), value);
            if (value) {
                controller.setRightTriggerForceEffect(
                        0, true, 0, 80, 255, 20
                );
                controller.setLed(DualSenseControllerLedColor::WHITE);
            } else controller.setLed(DualSenseControllerLedColor::GREY);
            break;
        case DualSenseControllerValueId::CROSS:
            printValueIfDebugPrint(F("CROSS"), value);
            if (value) {
                controller.clearRightTriggerForce();
                controller.setLed(DualSenseControllerLedColor::WHITE);
            } else controller.setLed(DualSenseControllerLedColor::GREY);
            break;

        case DualSenseControllerValueId::L3:
            printValueIfDebugPrint(F("L3"), value);
            controller.setBigRumble(value ? 128 : 0);
            break;
        case DualSenseControllerValueId::R3:
            printValueIfDebugPrint(F("R3"), value);
            controller.setSmallRumble(value ? 128 : 0);
            break;

        case DualSenseControllerValueId::L1:
            printValueIfDebugPrint(F("L1"), value);
            if (value) {
                if (playerLedMask <= 1)playerLedMask = 0;
                else playerLedMask = (playerLedMask >> 1) | 1;
                controller.setPlayerLeds(playerLedMask);
            }
            break;
        case DualSenseControllerValueId::R1:
            printValueIfDebugPrint(F("R1"), value);
            if (value) {
                playerLedMask = (playerLedMask << 1) | 1;
                if (playerLedMask > 0x1F)playerLedMask = 0x1F;
                controller.setPlayerLeds(playerLedMask);
            }
            break;

        case DualSenseControllerValueId::L2:
            printValueIfDebugPrint(F("L2"), value);
            break;
        case DualSenseControllerValueId::R2:
            printValueIfDebugPrint(F("R2"), value);
            break;

        case DualSenseControllerValueId::ANALOG_L2:
            printValueIfDebugPrint(F("ANALOG_L2"), value);
            break;
        case DualSenseControllerValueId::ANALOG_R2:
            printValueIfDebugPrint(F("ANALOG_R2"), value);
            break;

        case DualSenseControllerValueId::LEFT_HAT_X:
            printValueIfDebugPrint(F("LEFT_HAT_X"), value);
            break;
        case DualSenseControllerValueId::LEFT_HAT_Y:
            printValueIfDebugPrint(F("LEFT_HAT_Y"), value);
            break;
        case DualSenseControllerValueId::RIGHT_HAT_X:
            printValueIfDebugPrint(F("RIGHT_HAT_X"), value);
            break;
        case DualSenseControllerValueId::RIGHT_HAT_Y:
            printValueIfDebugPrint(F("RIGHT_HAT_Y"), value);
            break;

        case DualSenseControllerValueId::ACCELEROMETER_X:
            printValueIfDebugPrint(F("ACCELEROMETER_X"), value);
            break;
        case DualSenseControllerValueId::ACCELEROMETER_Y:
            printValueIfDebugPrint(F("ACCELEROMETER_Y"), value);
            break;
        case DualSenseControllerValueId::ACCELEROMETER_Z:
            printValueIfDebugPrint(F("ACCELEROMETER_Z"), value);
            break;

        case DualSenseControllerValueId::GYROSCOPE_X:
            printValueIfDebugPrint(F("GYROSCOPE_X"), value);
            break;
        case DualSenseControllerValueId::GYROSCOPE_Y:
            printValueIfDebugPrint(F("GYROSCOPE_Y"), value);
            Serial.print("GYROSCOPE_Y");
            break;
        case DualSenseControllerValueId::GYROSCOPE_Z:
            printValueIfDebugPrint(F("GYROSCOPE_Z"), value);
            break;

        case DualSenseControllerValueId::ORIENTATION_PITCH:
            printValueIfDebugPrint(F("ORIENTATION_PITCH"), value);
            break;
        case DualSenseControllerValueId::ORIENTATION_ROLL:
            printValueIfDebugPrint(F("ORIENTATION_ROLL"), value);
            break;

        case DualSenseControllerValueId::FINGER_1_IS_TOUCHING:
            printValueIfDebugPrint(F("FINGER_1_IS_TOUCHING"), value);
            break;
        case DualSenseControllerValueId::FINGER_1_X:
            printValueIfDebugPrint(F("FINGER_1_X"), value);
            break;
        case DualSenseControllerValueId::FINGER_1_Y:
            printValueIfDebugPrint(F("FINGER_1_Y"), value);
            break;
        case DualSenseControllerValueId::FINGER_2_IS_TOUCHING:
            printValueIfDebugPrint(F("FINGER_2_IS_TOUCHING"), value);
            break;
        case DualSenseControllerValueId::FINGER_2_X:
            printValueIfDebugPrint(F("FINGER_2_X"), value);
            break;
        case DualSenseControllerValueId::FINGER_2_Y:
            printValueIfDebugPrint(F("FINGER_2_Y"), value);
            break;
    }

}

void printValueIfDebugPrint(String s, int16_t value) {
    if (!DEBUG_PRINT) return;
    Serial.print(s);
    Serial.print(": ");
    Serial.println(value);
}
