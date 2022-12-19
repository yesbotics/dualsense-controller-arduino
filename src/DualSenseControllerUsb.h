
#ifndef DUALSENSECONTROLLERUSB_H
#define DUALSENSECONTROLLERUSB_H

#include <PS5USB.h>
#include "DualSenseControllerCore.h"

class DualSenseControllerUsb : public DualSenseControllerCore {

private:
    PS5USB* ps5UsbPtr_ = nullptr;

public:
    explicit DualSenseControllerUsb(const DualSenseControllerOptions& optionsRef);

    explicit DualSenseControllerUsb(const DualSenseControllerOptions* optionsPtr);

    ~DualSenseControllerUsb() = default;

    DualSenseControllerUsb(const DualSenseControllerUsb&) = delete; // forbid copy-ctor
    DualSenseControllerUsb& operator=(const DualSenseControllerUsb&) = delete; // forbid copy-assignment

    bool isConnected() const override;

};


#endif //DUALSENSECONTROLLERUSB_H
