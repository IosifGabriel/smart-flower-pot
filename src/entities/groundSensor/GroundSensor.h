#ifndef SMART_FLOWER_POT_GROUNDSENSOR_H
#define SMART_FLOWER_POT_GROUNDSENSOR_H


#include <string>
#include <iostream>
#include "../../libs/json.hpp"
#include "GroundNutrient.h"

using nlohmann::json;
using namespace std;
enum class SensorType {
    humidity, temperature, light, feritlizers
};

class GroundSensor {

private:

    std::string updatedAt;

    GroundNutrient nutrient[100];

    SensorType sensorType;

    int nutrientCounter = 0;

public:

    GroundSensor(nlohmann::json groundData) {
        updatedAt = groundData["updatedAt"].get<nlohmann::json::string_t>();
        sensorType = groundData["sensorType"].get<SensorType>();
        for(int i=0; i<=1; i++) {
            nutrient[i] = GroundNutrient(groundData["groundNutrient"][i]);
            nutrientCounter = i;
        }
    }

    const GroundNutrient &getNutrient(int i) const {
        return nutrient[i];
    }

    //void setNutrient(const GroundNutrient &nutrient) {
      //  GroundSensor::nutrient= nutrient;
    //}

    SensorType getSensorType() const {
        return sensorType;
    }

    void setSensorType(SensorType sensorType) {
        GroundSensor::sensorType = sensorType;
    }

    string &getUpdatedAt() {
        return updatedAt;
    }

    void setUpdatedAt(const string &updatedAt) {
        GroundSensor::updatedAt = updatedAt;
    }

    void addNutrient(GroundNutrient nutrientToAdd) {
        nutrient[nutrientCounter + 1] = nutrientToAdd;
    }
    nlohmann::json to_json() {
        nlohmann::json j;
        j = json{{"updatedAt",      this->updatedAt},
                 {"sensorType",     this->sensorType},
                 {"GroundNutrient", this->nutrient[1].to_json()}};
        return j;
    }
};


#endif //SMART_FLOWER_POT_GROUNDSENSOR_H
