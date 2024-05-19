#include <iostream>
#include <cstdint>
#include <string>
#include <memory>

#include "sample_communicator.h"

uint32_t Communicator::Send(
    void        *data,
    uint32_t    mode=0
){
    uint32_t ret    = 0;
    uint32_t mode_  = mode;

    ret = connector_->SendDevice(mode, data);
    return ret;
}

uint32_t Communicator::Receive(
    void        *data,
    uint32_t    size
){
    uint32_t ret = 0;

    ret = connector_->ReceiveData(data, size);

    return ret;
}

