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
    cout << "Delete MqttClient instance\n";

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
    json notifications = json::array();

    if(!JSONUtils::checkJsonFilesMinMax(Constants::PROJECT_SRC_ROOT + Constants::HUMIDITY_SENSOR_PATH)) {
        notifications.push_back("HUMIDITY not in parameters");
    }
    if(!JSONUtils::checkJsonFilesMinMax(Constants::PROJECT_SRC_ROOT + Constants::LIGHT_SENSOR_PATH)) {
        notifications.push_back("LIGHT not in parameters");
    }
    if(!JSONUtils::checkJsonFilesMinMax(Constants::PROJECT_SRC_ROOT + Constants::TEMPERATURE_SENSOR_PATH)) {
        notifications.push_back("TEMPERATURE not in parameters");
    }
    if(!JSONUtils::checkJsonFilesMinMax(Constants::PROJECT_SRC_ROOT + Constants::FERTILIZER_SENSOR_PATH)) {
        notifications.push_back("FERTILIZER not in parameters");
    }

    if(!notifications.empty()) {
        MqttClient::getInstance()->publish("smart-flower-pot/notification", notifications.dump(4));
    }
}
