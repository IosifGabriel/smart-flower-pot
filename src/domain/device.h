#ifndef SMART_FLOWER_POT_DEVICE_H
#define SMART_FLOWER_POT_DEVICE_H

#include <iostream>
#include <mutex>
#include "mqtt.h"
#include "../utils/JSONUtils.h"
#include "../utils/Constants.h"
#include "../entities/groundSensor/GroundSensor.h"
#include "../entities/groundSensor/GroundNutrient.h"
#include "../entities/sensor/SensorData.h"
#include "../libs/json.hpp"

using namespace std;

class Device {
public:
    bool isRunning = false;

    static Device *&getInstance();

    static void deleteInstance();

    void loop();

private:
    Device();

    ~Device();

    Device(const Device &signal);

    const Device &operator=(const Device &signal);

private:
    static Device *m_Device;
    static std::mutex m_Mutex;
};

#endif //SMART_FLOWER_POT_DEVICE_H
