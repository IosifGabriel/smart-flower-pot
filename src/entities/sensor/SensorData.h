#ifndef SMART_FLOWER_POT_SENSORDATA_H
#define SMART_FLOWER_POT_SENSORDATA_H

#include <iostream>
#include <string>
#include "../../libs/json.hpp"
using namespace std;
using nlohmann::json;

enum class SensorTypeS {humidity, temperature, light, feritlizers};

class SensorData {

private:

    string updatedAt;

    double minValue;

    double maxValue;

    double value;

    SensorTypeS sensorType;


public:
    SensorData(nlohmann::json sensorData) {
        updatedAt = sensorData["updatedAt"].get<nlohmann::json::string_t>();
        minValue = sensorData["minValue"].get<double>();
        maxValue = sensorData["maxValue"].get<double>();
        sensorType = sensorData["sensorType"].get<SensorTypeS>();
        value = sensorData["value"].get<double>();
    }

    SensorData() {}

    double getMinValue() const {
        return minValue;
    }

    void setMinValue(double minValue) {
        SensorData::minValue = minValue;
    }

    double getMaxValue() const {
        return maxValue;
    }

    void setMaxValue(double maxValue) {
        SensorData::maxValue = maxValue;
    }

    SensorTypeS getSensorType() const {
        return sensorType;
    }

    void setSensorType(SensorTypeS sensorType) {
        SensorData::sensorType = sensorType;
    }

    double getValue() const {
        return value;
    }

    void setValue(double value) {
        SensorData::value = value;
    }

    string getUpdatedAt() const {
        return updatedAt;
    }

    void setUpdatedAt(double updatedAt) {
        SensorData::updatedAt = updatedAt;
    }

    nlohmann::json to_json(){
        nlohmann::json j;
        j = json{{"updatedAt", this->updatedAt}, {"minValue", this->minValue}, {"maxValue", this->maxValue}, {"sensorType", this->sensorType}, {"value", this->value}};
        return j;
    }
};
#endif //SMART_FLOWER_POT_SENSORDATA_H