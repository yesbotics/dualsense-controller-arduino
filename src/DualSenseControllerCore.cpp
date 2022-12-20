#include "DualSenseControllerCore.h"
#include "dual-sense-controller-util.h"
#include "dual-sense-controller-values.h"

DualSenseControllerCore::DualSenseControllerCore(
        USB* usbPtr,
        PS5Parser* ps5Parser,
        const DualSenseControllerOptions* optionsPtr
) :
        usbPtr_{usbPtr},
        ps5Parser_{ps5Parser} {
    this->optionsPtr_ = new DualSenseControllerOptions;
    this->optionsPtr_->stateEventCallback = optionsPtr->stateEventCallback;
    this->optionsPtr_->valueChangeEventCallback = optionsPtr->valueChangeEventCallback;
    this->optionsPtr_->pollingInterval = optionsPtr->pollingInterval;
    this->optionsPtr_->pollDigitalButtons = optionsPtr->pollDigitalButtons;
    this->optionsPtr_->pollAnalogButtons = optionsPtr->pollAnalogButtons;
    this->optionsPtr_->pollAnalogHats = optionsPtr->pollAnalogHats;
    this->optionsPtr_->pollImu = optionsPtr->pollImu;
    this->optionsPtr_->pollTouchpad = optionsPtr->pollTouchpad;
    this->optionsPtr_->pollOrientation = optionsPtr->pollOrientation;
    this->optionsPtr_->analogHatThreshold = optionsPtr->analogHatThreshold;
}

DualSenseControllerCore::~DualSenseControllerCore() {
    delete this->optionsPtr_;
}

void DualSenseControllerCore::reset() {
    for (int i = 0; i < DIGITAL_BUTTONS_SIZE; i++)
        DIGITAL_BUTTONS[i].value = DEFAULT_DIGITAL_BUTTON_VALUE;
    for (int i = 0; i < ANALOG_BUTTONS_SIZE; i++)
        ANALOG_BUTTONS[i].value = DEFAULT_ANALOG_BUTTON_VALUE;
    for (int i = 0; i < ANALOG_HATS_SIZE; i++)
        ANALOG_HATS[i].value = DEFAULT_ANALOG_HAT_VALUE;
    for (int i = 0; i < SENSOR_VALUES_SIZE; i++)
        SENSOR_VALUES[i].value = DEFAULT_SENSOR_VALUE;
    OTHER_VALUES.micLed = DEFAULT_MIC_LED_VALUE;
    OTHER_VALUES.bigRumble = DEFAULT_BIG_RUMBLE_VALUE;
    OTHER_VALUES.smallRumble = DEFAULT_SMALL_RUMBLE_VALUE;
}

bool DualSenseControllerCore::init() {
    if (this->isInitialized_) return false;
    if (this->usbPtr_->Init() == -1)return false;
    this->setState(DualSenseControllerState::INITIALIZED);
    this->isInitialized_ = true;
    return true;
}

void DualSenseControllerCore::poll() {
    this->usbPtr_->Task();
    if (!this->isInitialized_)return;
    bool isConn = this->isConnected();
    if (isConn != this->wasConnected_) {
        this->wasConnected_ = isConn;
        this->onConnectionChange(isConn);
        this->setState(
                isConn ?
                DualSenseControllerState::CONNECTED :
                DualSenseControllerState::DISCONNECTED
        );
    }
    if (!isConn)return;

    if (this->lastMessageCounter_ == this->ps5Parser_->getMessageCounter())return;

    if (!this->optionsPtr_->valueChangeEventCallback)return;

    if (this->optionsPtr_->pollTouchpad) this->pollTouchpadIsTouched();
    if (this->optionsPtr_->pollDigitalButtons) this->pollDigitalButtons();
    unsigned long currentMillis = millis();
    if ((currentMillis - this->lastMillis_) >= this->optionsPtr_->pollingInterval) {
        this->lastMillis_ = currentMillis;
        if (this->optionsPtr_->pollAnalogButtons) this->pollAnalogButtons();
        if (this->optionsPtr_->pollAnalogHats) this->pollAnalogHats();
        if (this->optionsPtr_->pollImu) this->pollImu();
        if (this->optionsPtr_->pollTouchpad) this->pollTouchpadFingerPos();
        if (this->optionsPtr_->pollOrientation) this->pollOrientation();
    }
}

bool DualSenseControllerCore::isConnected() const {
    return true;
}

void DualSenseControllerCore::onConnectionChange(bool isConnected) {
    if (isConnected) {
        this->reset();
        this->setLed(DualSenseControllerLedColor::GREEN);
    }
}

void DualSenseControllerCore::pollDigitalButtons() {
    for (int i = 0; i < DIGITAL_BUTTONS_SIZE; i++) {
        DualSenseControllerValueItem<bool>& dscvi = DIGITAL_BUTTONS[i];
        auto ps5id = static_cast<ButtonEnum>(dscvi.ps5LibId);
        bool newValue = this->ps5Parser_->getButtonPress(ps5id);
        this->compare<bool>(
                &dscvi.value,
                newValue,
                dscvi.id
        );
    }
}

void DualSenseControllerCore::pollAnalogButtons() {
    for (int i = 0; i < ANALOG_BUTTONS_SIZE; i++) {
        DualSenseControllerValueItem<uint8_t>& dscvi = ANALOG_BUTTONS[i];
        auto ps5id = static_cast<ButtonEnum>(dscvi.ps5LibId);
        uint8_t newValue = this->ps5Parser_->getAnalogButton(ps5id);
        this->compare<uint8_t>(
                &dscvi.value,
                newValue,
                dscvi.id
        );
    }
}

void DualSenseControllerCore::pollAnalogHats() {
    for (int i = 0; i < ANALOG_HATS_SIZE; i++) {
        DualSenseControllerValueItem<uint8_t>& dscvi = ANALOG_HATS[i];
        auto ps5id = static_cast<AnalogHatEnum>(dscvi.ps5LibId);
        uint8_t newValue = this->ps5Parser_->getAnalogHat(ps5id);
        this->compare<uint8_t>(
                &dscvi.value,
                newValue,
                dscvi.id,
                this->optionsPtr_->analogHatThreshold
        );
    }
}

void DualSenseControllerCore::pollImu() {
    for (int i = 0; i < SENSOR_VALUES_SIZE; i++) {
        DualSenseControllerValueItem<int16_t>& dscvi = SENSOR_VALUES[i];
        auto ps5id = static_cast<SensorEnum>(dscvi.ps5LibId);
        int16_t newValue = this->ps5Parser_->getSensor(ps5id);
        this->compare<int16_t>(
                &dscvi.value,
                newValue,
                dscvi.id
        );
    }
};

void DualSenseControllerCore::pollTouchpadIsTouched() {
    for (int i = 0; i < FINGER_IS_TOUCHING_VALUES_SIZE; i++) {
        DualSenseControllerValueItem<bool>& dscvi = FINGER_IS_TOUCHING_VALUES[i];
        auto ps5id = static_cast<uint8_t>(dscvi.ps5LibId);
        bool newValue = this->ps5Parser_->isTouching(ps5id);
        this->compare<bool>(
                &dscvi.value,
                newValue,
                dscvi.id
        );
    }
}

void DualSenseControllerCore::pollTouchpadFingerPos() {
    for (int i = 0; i < FINGER_X_VALUES_SIZE; i++) {
        DualSenseControllerValueItem<uint16_t>& dscvi = FINGER_X_VALUES[i];
        auto ps5id = static_cast<uint8_t>(dscvi.ps5LibId);
        if (!this->ps5Parser_->isTouching(ps5id))continue;
        uint16_t newValue = this->ps5Parser_->getX(ps5id);
        this->compare<uint16_t>(
                &dscvi.value,
                newValue,
                dscvi.id
        );
    }
    for (int i = 0; i < FINGER_Y_VALUES_SIZE; i++) {
        DualSenseControllerValueItem<uint16_t>& dscvi = FINGER_Y_VALUES[i];
        auto ps5id = static_cast<uint8_t>(dscvi.ps5LibId);
        uint16_t newValue = this->ps5Parser_->getY(ps5id);
        if (!this->ps5Parser_->isTouching(ps5id))continue;
        this->compare<uint16_t>(
                &dscvi.value,
                newValue,
                dscvi.id
        );
    }
}

void DualSenseControllerCore::pollOrientation() {
    for (int i = 0; i < ORIENTATION_VALUES_SIZE; i++) {
        DualSenseControllerValueItem<float>& dscvi = ORIENTATION_VALUES[i];
        auto ps5id = static_cast<AngleEnum>(dscvi.ps5LibId);
        float newValue = this->ps5Parser_->getAngle(ps5id);
        this->compare<float>(
                &dscvi.value,
                newValue,
                dscvi.id
        );
    }
}

void DualSenseControllerCore::triggerStateEvent(DualSenseControllerState state) {
    if (this->optionsPtr_->stateEventCallback) {
        this->optionsPtr_->stateEventCallback(state);
    }
}

void DualSenseControllerCore::triggerValueEvent(DualSenseControllerValueId id, int16_t newValue) {
    if (this->optionsPtr_->valueChangeEventCallback) {
        this->optionsPtr_->valueChangeEventCallback(id, newValue);
    }
}


// FCT //////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DualSenseControllerCore::setMicLed(bool on) {
    OTHER_VALUES.micLed = on;
    this->ps5Parser_->setMicLed(on);
}

void DualSenseControllerCore::toggleMicLed() {
    this->setMicLed(!OTHER_VALUES.micLed);
}

void DualSenseControllerCore::setRumble(uint8_t bigRumble, uint8_t smallRumble) {
    OTHER_VALUES.bigRumble = bigRumble;
    OTHER_VALUES.smallRumble = smallRumble;
    this->ps5Parser_->setRumbleOn(bigRumble, smallRumble);
}

void DualSenseControllerCore::setBigRumble(uint8_t bigRumble) {
    OTHER_VALUES.bigRumble = bigRumble;
    this->setRumble(OTHER_VALUES.bigRumble, OTHER_VALUES.smallRumble);
}

void DualSenseControllerCore::setSmallRumble(uint8_t smallRumble) {
    OTHER_VALUES.smallRumble = smallRumble;
    this->setRumble(OTHER_VALUES.bigRumble, OTHER_VALUES.smallRumble);
}

void DualSenseControllerCore::setRumbleOff() {
    OTHER_VALUES.smallRumble = 0;
    OTHER_VALUES.bigRumble = 0;
    this->setRumble(OTHER_VALUES.bigRumble, OTHER_VALUES.smallRumble);
}

void DualSenseControllerCore::setRumbleOn() {
    this->setRumble(255, 255);
}

void DualSenseControllerCore::setBigRumbleOn() {
    this->setBigRumble(255);
}

void DualSenseControllerCore::setSmallRumbleOn() {
    this->setSmallRumble(255);
}

void DualSenseControllerCore::setBigRumbleOff() {
    this->setBigRumble(0);
}

void DualSenseControllerCore::setSmallRumbleOff() {
    this->setSmallRumble(0);
}

void DualSenseControllerCore::setLeftTriggerForce(uint8_t start, uint8_t force) {
    this->ps5Parser_->leftTrigger.setTriggerForce(start, force);
}

void DualSenseControllerCore::setLeftTriggerSection(uint8_t start, uint8_t end) {
    this->ps5Parser_->leftTrigger.setTriggerForceSection(start, end);
}

/**
 * @param start Start position of the continuous force
 * @param keep Indicates weather the effect should keep playing (vibration) when the
 *             trigger is fully pressed.
 * @param beginForce Force for the section with trigger value ≥ 128.
 * @param midForce Force for the section with trigger value ≤ 128
 * @param endForce Force applied when the trigger is fully pressed / would go beyond
 *                 255
 * @param frequency Frequency with witch the effect is executed. More a scalar value to
 *                  scale between two fixed frequency than an real frequency parameter.
 */

void DualSenseControllerCore::setLeftTriggerForceEffect(
        uint8_t start, bool keep,
        uint8_t beginForce, uint8_t midForce, uint8_t endForce,
        uint8_t frequency
) {
    // here i modded the lib, inside setTriggerForceEffect there was wrong EffecType
    // for details see: https://github.com/felis/USB_Host_Shield_2.0/pull/756
    this->ps5Parser_->leftTrigger.setTriggerForceEffect(
            start, keep, beginForce, midForce, endForce, frequency
    );
}

void DualSenseControllerCore::clearLeftTriggerForce() {
    this->ps5Parser_->leftTrigger.clearTriggerForce();
}

void DualSenseControllerCore::setRightTriggerForce(uint8_t start, uint8_t force) {
    this->ps5Parser_->rightTrigger.setTriggerForce(start, force);
}

void DualSenseControllerCore::setRightTriggerSection(uint8_t start, uint8_t end) {
    this->ps5Parser_->rightTrigger.setTriggerForceSection(start, end);
}

void DualSenseControllerCore::setRightTriggerForceEffect(
        uint8_t start, bool keep,
        uint8_t beginForce, uint8_t midForce, uint8_t endForce,
        uint8_t frequency
) {
    this->ps5Parser_->rightTrigger.setTriggerForceEffect(
            start, keep, beginForce, midForce, endForce, frequency
    );
}

void DualSenseControllerCore::clearRightTriggerForce() {
    this->ps5Parser_->rightTrigger.clearTriggerForce();
}

void DualSenseControllerCore::setLed(uint8_t red, uint8_t green, uint8_t blue) {
    this->ps5Parser_->setLed(red, green, blue);
}

void DualSenseControllerCore::setLed(DualSenseControllerLedColor color) {
    this->ps5Parser_->setLed(static_cast<ColorsEnum>(color));
}

void DualSenseControllerCore::setLedOff() {
    this->ps5Parser_->setLedOff();
};

void DualSenseControllerCore::setPlayerLedsOff() {
    this->ps5Parser_->setPlayerLedOff();
};

/**
 * Use this to set five player LEDs.
 * @param bitmask it mask to set the five player LEDs. The first 5 bits represent a LED each.
 */
void DualSenseControllerCore::setPlayerLeds(uint8_t bitMask) {
    this->ps5Parser_->setPlayerLed(bitMask);
}

void DualSenseControllerCore::setState(DualSenseControllerState state) {
    this->state_ = state;
    this->triggerStateEvent(state);
}

DualSenseControllerState DualSenseControllerCore::getState() {
    return this->state_;
}




