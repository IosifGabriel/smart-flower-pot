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
    SensorData sensorData;

    sensorData = SensorData(JSONUtils::readJsonFromFile(Constants::PROJECT_SRC_ROOT + Constants::HUMIDITY_SENSOR_PATH));
    cout << "HUMIDITY" << sensorData.getValue() << "\n";

    sensorData = SensorData(JSONUtils::readJsonFromFile(Constants::PROJECT_SRC_ROOT + Constants::LIGHT_SENSOR_PATH));
    cout << "LIGHT" << sensorData.getValue() << "\n";

    sensorData = SensorData(JSONUtils::readJsonFromFile(Constants::PROJECT_SRC_ROOT + Constants::TEMPERATURE_SENSOR_PATH));
    cout << "TEMPERATURE" << sensorData.getValue() << "\n";

    sensorData = SensorData(JSONUtils::readJsonFromFile(Constants::PROJECT_SRC_ROOT + Constants::FERTILIZER_SENSOR_PATH));
    cout << "FERTILIZER" << sensorData.getValue() << "\n";

    MqttClient::getInstance()->publish("smart-flower-pot/notification", "loop");
}
