//
// Created by alexandru.jilavu on 25.03.2021.
//

#ifndef SMART_FLOWER_POT_SENSORDATAEXAMPLE_H
#define SMART_FLOWER_POT_SENSORDATAEXAMPLE_H

#include <iostream>
#include "../../libs/json.hpp"

class SensorDataExample {

private:
    double luminosity;

    double humidity;

    double temperature;

public:
    SensorDataExample(nlohmann::json sensorData) {
        luminosity = std::stod(sensorData["luminosity"].get<nlohmann::json::string_t>());
        humidity = std::stod(sensorData["humidity"].get<nlohmann::json::string_t>());
        temperature = std::stod(sensorData["temperature"].get<nlohmann::json::string_t>());
    }

    SensorDataExample() {}

    double getLuminosity() const {
        return luminosity;
    }

    void setLuminosity(double luminosity) {
        SensorDataExample::luminosity = luminosity;
    }

    double getHumidity() const {
        return humidity;
    }

    void setHumidity(double humidity) {
        SensorDataExample::humidity = humidity;
    }

    double getTemperature() const {
        return temperature;
    }

    void setTemperature(double temperature) {
        SensorDataExample::temperature = temperature;
    }
};


#endif //SMART_FLOWER_POT_SENSORDATAEXAMPLE_H
