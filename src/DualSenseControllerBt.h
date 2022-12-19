#ifndef DUALSENSECONTROLLERBT_H
#define DUALSENSECONTROLLERBT_H

#include <PS5BT.h>
#include "DualSenseControllerCore.h"
#include "dual-sense-controller-values.h"


class DualSenseControllerBt : public DualSenseControllerCore {

private:

    BTD* btdPtr_ = nullptr;
    PS5BT* ps5BtPtr_ = nullptr;
    bool isPairing_ = false;

protected:

    void onConnectionChange(bool isConnected) override;

public:

    explicit DualSenseControllerBt(const DualSenseControllerOptions& optionsRef);
    explicit DualSenseControllerBt(const DualSenseControllerOptions* optionsPtr);

    ~DualSenseControllerBt() = default;

    DualSenseControllerBt(const DualSenseControllerBt&) = delete; // forbid copy-ctor
    DualSenseControllerBt& operator=(const DualSenseControllerBt&) = delete; // forbid copy-assignment


    void pair();

    void disconnect();

    bool isPairing() const;

    bool isConnected() const override ;

};


#endif // DUALSENSECONTROLLERBT_H
