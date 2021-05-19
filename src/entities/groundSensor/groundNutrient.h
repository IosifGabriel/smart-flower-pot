#ifndef SMART_FLOWER_POT_GROUNDNUTRIENT_H
#define SMART_FLOWER_POT_GROUNDNUTRIENT_H
#include <iostream>
#include <string>
#include "../../libs/json.hpp"

using nlohmann::json;
using namespace std;
class groundNutrient {

private:
    std::string type;

    double minValue;

    double maxValue;

    double value;

public:
    groundNutrient(nlohmann::json groundData) {
        cout<<"ok1";
        type = (std::string) groundData["type"];
        minValue = std::stod(groundData["minValue"].get<nlohmann::json::string_t>());
        maxValue = std::stod(groundData["maxValue"].get<nlohmann::json::string_t>());
        value = std::stod(groundData["value"].get<nlohmann::json::string_t>());
        cout<<"ok2";
    }

    groundNutrient() {}

    const std::string &getType() const {
        return type;
    }

    void setType(const std::string &type) {
        groundNutrient::type = type;
    }


    double getMinValue() const {
        return minValue;
    }

    void setMinValue(double minValue) {
        groundNutrient::minValue = minValue;
    }

    double getMaxValue() const {
        return maxValue;
    }

    void setMaxValue(double maxValue) {
        groundNutrient::maxValue = maxValue;
    }

    double getValue() const {
        return value;
    }

    void setValue(double value) {
        groundNutrient::value = value;
    }

    nlohmann::json to_json(){
        nlohmann::json j;
        j = json{{"type", this->type}, {"minValue", this->minValue}, {"maxValue", this->maxValue}, {"value", this->value}};
        return j;
    }
};


#endif //SMART_FLOWER_POT_GROUNDNUTRIENT_H
