#ifndef SMART_FLOWER_POT_GROUNDSENSOR_H
#define SMART_FLOWER_POT_GROUNDSENSOR_H


#include <string>
#include <iostream>
#include "../../libs/json.hpp"
#include "groundNutrient.h"

using nlohmann::json;
using namespace std;
enum class SensorType {humidity, temperature, light, feritlizers};

class groundSensor {

private:

    std::string updatedAt;

    groundNutrient nutrient;

    SensorType sensorType;

public:

    groundSensor(nlohmann::json groundData) {
        updatedAt = groundData["updatedAt"].get<nlohmann::json::string_t>();
        cout<<"ok3";
        sensorType = groundData["sensorType"].get<SensorType>();
        nutrient = groundNutrient(groundData["groundNutrient"]);

    }

    const groundNutrient &getNutrient() const {
        return nutrient;
    }

    void setNutrient(const groundNutrient &nutrient) {
        groundSensor::nutrient = nutrient;
    }

    SensorType getSensorType() const {
        return sensorType;
    }

    void setSensorType(SensorType sensorType) {
        groundSensor::sensorType = sensorType;
    }

    string &getUpdatedAt() {
        return updatedAt;
    }

    void setUpdatedAt(const string &updatedAt) {
        groundSensor::updatedAt = updatedAt;
    }


    nlohmann::json to_json(){
        nlohmann::json j;
        j = json{{"updatedAt", this->updatedAt}, {"sensorType", this->sensorType}, {"groundNutrient", this->nutrient.to_json()}};
        return j;
    }
};


#endif //SMART_FLOWER_POT_GROUNDSENSOR_H
