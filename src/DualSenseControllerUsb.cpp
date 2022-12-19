#include "DualSenseControllerUsb.h"

static USB usb;
static PS5USB ps5Usb(&usb);

DualSenseControllerUsb::DualSenseControllerUsb(const DualSenseControllerOptions& optionsRef) :
        DualSenseControllerUsb{&optionsRef} {}

DualSenseControllerUsb::DualSenseControllerUsb(const DualSenseControllerOptions* optionsPtr) :
        ps5UsbPtr_{&ps5Usb},
        DualSenseControllerCore(
                &usb,
                &ps5Usb,
                optionsPtr
        ) {
}

bool DualSenseControllerUsb::isConnected() const {
    return this->ps5UsbPtr_->connected();
}
