//
// Created by by iosif.gabriel on 23.05.2021.
//

#ifndef SMART_FLOWER_POT_CHANGESENSORVALUE_H
#define SMART_FLOWER_POT_CHANGESENSORVALUE_H

#include <string>
#include <stdlib.h>
#include "../groundSensor/SensorType.h"

class ChangeSensorValue {

private:
    double value;
    SensorType sensorType;
    std::string nutrientType;

public:
    ChangeSensorValue(nlohmann::json reqBody) {
        sensorType = reqBody["sensorType"].get<SensorType>();
        value = reqBody["value"].get<nlohmann::json::number_float_t>();
                if (!reqBody["nutrientType"].is_null()) {
            nutrientType = (std::string) reqBody["nutrientType"];
        }
    }

    double getValue() const {
        return value;
    }

    void setValue(double value) {
        ChangeSensorValue::value = value;
    }
    
    SensorType getSensorType() const {
        return sensorType;
    }

    void setSensorType(SensorType sensorType) {
        ChangeSensorValue::sensorType = sensorType;
    }
    
    const std::string &getNutrientType() const {
        return nutrientType;
    }

    void setNutrientType(const std::string &nutrientType) {
        ChangeSensorValue::nutrientType = nutrientType;
    }
};

#endif //SMART_FLOWER_POT_CHANGESENSORVALUE_H

