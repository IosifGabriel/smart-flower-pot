//
// Created by alexandru.jilavu on 21.05.2021.
//

#ifndef SMART_FLOWER_POT_CHANGESENSORSETTINGS_H
#define SMART_FLOWER_POT_CHANGESENSORSETTINGS_H

#include <string>
#include "../groundSensor/SensorType.h"


class ChangeSensorSettings {

private:
    double minValue;

    double maxValue;

    SensorType sensorType;

    std::string nutrientType;

public:
    ChangeSensorSettings(nlohmann::json reqBody) {
        sensorType = reqBody["sensorType"].get<SensorType>();
        minValue = reqBody["minValue"].get<nlohmann::json::number_float_t>();
        maxValue = reqBody["maxValue"].get<nlohmann::json::number_float_t>();
        if (!reqBody["nutrientType"].is_null()) {
            nutrientType = (std::string) reqBody["nutrientType"];
        }
    }

    double getMinValue() const {
        return minValue;
    }

    void setMinValue(double minValue) {
        ChangeSensorSettings::minValue = minValue;
    }

    double getMaxValue() const {
        return maxValue;
    }

    void setMaxValue(double maxValue) {
        ChangeSensorSettings::maxValue = maxValue;
    }

    SensorType getSensorType() const {
        return sensorType;
    }

    void setSensorType(SensorType sensorType) {
        ChangeSensorSettings::sensorType = sensorType;
    }

    const std::string &getNutrientType() const {
        return nutrientType;
    }

    void setNutrientType(const std::string &nutrientType) {
        ChangeSensorSettings::nutrientType = nutrientType;
    }

};


#endif //SMART_FLOWER_POT_CHANGESENSORSETTINGS_H
