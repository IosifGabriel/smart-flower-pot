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

    int nutrientCounter = 1;

public:

    GroundSensor(nlohmann::json groundData) {
        updatedAt = groundData["updatedAt"].get<nlohmann::json::string_t>();
        sensorType = groundData["sensorType"].get<SensorType>();
        for(int i = 0; i <= nutrientCounter; i++) {
            nutrient[i] = GroundNutrient(groundData["groundNutrient"][i]);
        }
    }

    const GroundNutrient &getNutrient(int i) const {
        return nutrient[i];
    }
    
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
        nutrientCounter++;
    }

    nlohmann::json to_json() {
        nlohmann::json j;
        json nutrientObjects = json::array();
        for (int i = 0; i <= nutrientCounter; i++)
        {
            nutrientObjects.push_back(nutrient[i].to_json());
        }
        j = json{{"updatedAt",      this->updatedAt},
                 {"sensorType",     this->sensorType},
                 {"GroundNutrient", nutrientObjects}};
        return j;
    }
};


#endif //SMART_FLOWER_POT_GROUNDSENSOR_H
