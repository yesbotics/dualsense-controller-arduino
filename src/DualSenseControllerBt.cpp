#include "DualSenseControllerBt.h"

static USB usb;
static BTD btd(&usb);
static PS5BT ps5bt(&btd);


DualSenseControllerBt::DualSenseControllerBt(DualSenseControllerOptions options) :
        btdPtr_{&btd},
        ps5BtPtr_{&ps5bt},
        DualSenseControllerCore(
                &usb,
                &ps5bt,
                &options
        ) {
}


bool DualSenseControllerBt::isConnected() const {
    return this->ps5BtPtr_->connected();
}

bool DualSenseControllerBt::isPairing() const {
    return this->isPairing_;
}

void DualSenseControllerBt::pair() {
    if (this->isPairing_)return;
    this->isPairing_ = true;
    this->ps5BtPtr_->pair();
    this->triggerStateEvent(DualSenseControllerStateEvent::PAIRING);
}

void DualSenseControllerBt::disconnect() {
    this->ps5BtPtr_->disconnect();
}

void DualSenseControllerBt::onConnectionChange(bool isConnected) {
    DualSenseControllerCore::onConnectionChange(isConnected);
    if (this->isPairing_) this->isPairing_ = false;
}


