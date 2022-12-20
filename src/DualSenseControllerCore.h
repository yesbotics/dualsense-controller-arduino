#ifndef DUALSENSECONTROLLERCORE_H
#define DUALSENSECONTROLLERCORE_H

#include <Usb.h>
#include <PS5Parser.h>
#include "dual-sense-controller-types.h"
#include "dual-sense-controller-values.h"


class DualSenseControllerCore {

private:

    USB* usbPtr_ = nullptr;
    PS5Parser* ps5Parser_ = nullptr;
    bool isInitialized_ = false;
    bool wasConnected_ = false;
    DualSenseControllerState state_ = DualSenseControllerState::UNINITIALIZED;
    unsigned long lastMillis_ = 0;
    uint16_t lastMessageCounter_ = -1;
    DualSenseControllerOptions* optionsPtr_;

    void reset();

    void triggerValueEvent(DualSenseControllerValueId id, int16_t newValue);

    void pollDigitalButtons();

    void pollAnalogButtons();

    void pollAnalogHats();

    void pollImu();

    void pollTouchpadIsTouched();

    void pollTouchpadFingerPos();

    void pollOrientation();

    void triggerStateEvent(DualSenseControllerState state);

    template<typename TValue>
    void compare(TValue* valuePtr, TValue& newValue, DualSenseControllerValueId id, uint8_t threshold = 0) {
        if ((*valuePtr) == newValue) return;
        if (threshold > 0) {
            TValue diff = abs(newValue - *valuePtr);
            if (diff < threshold) return;
        }
        *valuePtr = newValue;
        this->triggerValueEvent(id, newValue);
    }

protected:
    explicit DualSenseControllerCore(
            USB* usbPtr,
            PS5Parser* ps5Parser,
            const DualSenseControllerOptions* optionsPtr
    );

    // virtual ~DualSenseControllerCore(); nicht notwendig,
    // da die Klasse nicht instanzierbar ist und 'delete (DualSenseControllerCore*) dscc' ist nicht möglich
    // siehe C++ Aufbaukurs Seite 200
    ~DualSenseControllerCore();

    void setState(DualSenseControllerState state);

    virtual void onConnectionChange(bool isConnected);

public:

    virtual bool isConnected() const;

    bool init();

    void poll();

    DualSenseControllerState getState();

    ///////////////////////////////////////////////////

    void setMicLed(bool on);

    void toggleMicLed();

    void setLeftTriggerForce(uint8_t start, uint8_t force);

    void setLeftTriggerSection(uint8_t start, uint8_t end);

    void setRightTriggerForce(uint8_t start, uint8_t force);

    void setRightTriggerSection(uint8_t start, uint8_t end);

    void setLeftTriggerForceEffect(
            uint8_t start, bool keep, uint8_t begin_force, uint8_t mid_force, uint8_t end_force, uint8_t frequency
    );

    void setRightTriggerForceEffect(
            uint8_t start, bool keep, uint8_t beginForce, uint8_t midForce, uint8_t endForce, uint8_t frequency
    );

    void clearLeftTriggerForce();

    void clearRightTriggerForce();

    void setLed(uint8_t red, uint8_t green, uint8_t blue);

    void setLed(DualSenseControllerLedColor col);

    void setLedOff();


    void setRumble(uint8_t bigRumble, uint8_t smallRumble);

    void setRumbleOn();

    void setRumbleOff();

    void setBigRumble(uint8_t bigRumble);

    void setBigRumbleOn();

    void setBigRumbleOff();

    void setSmallRumble(uint8_t smallRumble);

    void setSmallRumbleOn();

    void setSmallRumbleOff();

    void setPlayerLedsOff();

    void setPlayerLeds(uint8_t bitMask);

};


#endif // DUALSENSECONTROLLERCORE_H
