#include "device.h"

Device *Device::m_Device = NULL;
std::mutex Device::m_Mutex;

Device *&Device::getInstance() {
    if (m_Device == NULL) {
        std::unique_lock <std::mutex> lock(m_Mutex);
        if (m_Device == NULL) {
            m_Device = new(std::nothrow) Device;
        }
    }

    return m_Device;
}

void Device::deleteInstance() {
    std::unique_lock <std::mutex> lock(m_Mutex);
    if (m_Device) {
        delete m_Device;
        m_Device = NULL;
    }
}

Device::Device() {
}

Device::~Device() {
}

void Device::loop() {
    // read all values from sensors
    // check if not in range
    // send alarm
    // mark alarm
    // if in range reset alarm
}
