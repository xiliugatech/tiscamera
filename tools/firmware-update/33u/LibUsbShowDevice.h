/*
 * Copyright 2017 The Imaging Source Europe GmbH
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include "IUsbDevice.h"
#include "../UsbCamera.h"
#include "../UsbSession.h"

#include <cstdint>
#include <memory>

using namespace tis;

namespace lib33u
{
namespace driver_interface
{
namespace libusb
{

class ShowDevice : public IUsbDevice
{
    std::shared_ptr<UsbSession> usb_session;

    libusb_device_handle* dev_handle;

    device_info device;

    int interface;

    void claim_interface();

    void release_interface();

public:
    ShowDevice(std::shared_ptr<UsbSession> ksps, device_info device);
    ~ShowDevice();

    // Inherited via IUSBDevice
    virtual uint16_t product_id() override;
    virtual void open() override;
    virtual void read_vendor_request(uint8_t req,
                                     uint16_t value,
                                     uint16_t index,
                                     uint8_t* buffer,
                                     uint16_t length) override;

    virtual void write_vendor_request(uint8_t req,
                                      uint16_t value,
                                      uint16_t index,
                                      const uint8_t* data,
                                      uint16_t length) override;
};

} // namespace libusb
} /* namespace driver_interface */
} // namespace lib33u
