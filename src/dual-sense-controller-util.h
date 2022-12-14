#ifndef DUALSENSECONTROLLERUTIL_H
#define DUALSENSECONTROLLERUTIL_H

#include "dual-sense-controller-types.h"

template<typename T, size_t N>
size_t getArraySize(T (&)[N]) {
    return N;
}

#endif //DUALSENSECONTROLLERUTIL_H
