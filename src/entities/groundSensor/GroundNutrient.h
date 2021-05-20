#ifndef SMART_FLOWER_POT_GROUNDNUTRIENT_H
#define SMART_FLOWER_POT_GROUNDNUTRIENT_H

#include <iostream>
#include <string>
#include "../../libs/json.hpp"

using nlohmann::json;
using namespace std;

class GroundNutrient {

private:
    std::string type;

    double minValue;

    double maxValue;

    double value;

public:
    GroundNutrient(nlohmann::json groundData) {
        type = (std::string) groundData["type"];
        minValue = groundData["minValue"].get<nlohmann::json::number_float_t>();
        maxValue = groundData["maxValue"].get<nlohmann::json::number_float_t>();
        value = groundData["value"].get<nlohmann::json::number_float_t>();
    }

    GroundNutrient() {}

    const std::string &getType() const {
        return type;
    }

    void setType(const std::string &type) {
        GroundNutrient::type = type;
    }


    double getMinValue() const {
        return minValue;
    }

    void setMinValue(double minValue) {
        GroundNutrient::minValue = minValue;
    }

    double getMaxValue() const {
        return maxValue;
    }

    void setMaxValue(double maxValue) {
        GroundNutrient::maxValue = maxValue;
    }

    double getValue() const {
        return value;
    }

    void setValue(double value) {
        GroundNutrient::value = value;
    }

    nlohmann::json to_json() {
        nlohmann::json j;
        j = json{{"type",     this->type},
                 {"minValue", this->minValue},
                 {"maxValue", this->maxValue},
                 {"value",    this->value}};
        return j;
    }
};


#endif //SMART_FLOWER_POT_GROUNDNUTRIENT_H
