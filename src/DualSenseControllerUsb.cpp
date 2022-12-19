#include "DualSenseControllerUsb.h"

static USB usb;
static PS5USB ps5Usb(&usb);

DualSenseControllerUsb::DualSenseControllerUsb(DualSenseControllerOptions options) :
        ps5UsbPtr_{&ps5Usb},
        DualSenseControllerCore(
                &usb,
                &ps5Usb,
                &options
        ) {
}

bool DualSenseControllerUsb::isConnected() const {
    return this->ps5UsbPtr_->connected();
}
