#include <Arduino.h>
#include <dual-sense-controller-types.h>
#include <DualSenseControllerBt.h>


void onStateEvent(DualSenseControllerStateEvent event);

void onValueEvent(DualSenseControllerValueId id, int16_t value);

DualSenseControllerOptions options = {
        .stateEventCallback = onStateEvent,
        .valueEventCallback = onValueEvent,
        .pollingInterval = 30,
        .checkDigitalButtons = true,
        .checkAnalogButtons = true,
        .checkAnalogHats = true,
        .checkImu = false,
        .checkTouchpad = false,
        .checkOrientation = false,
        .analogHatThreshold = 2
};
DualSenseControllerBt dsController(&options);

void setup() {
    
}

void loop() {

}