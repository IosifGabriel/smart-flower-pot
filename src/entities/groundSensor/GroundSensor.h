#ifndef SMART_FLOWER_POT_GROUNDSENSOR_H
#define SMART_FLOWER_POT_GROUNDSENSOR_H


#include <string>
#include <iostream>
#include "../../libs/json.hpp"
#include "GroundNutrient.h"
#include "SensorType.h"
#include <vector>

using nlohmann::json;
using namespace std;

class GroundSensor {

private:

    std::string updatedAt;

    vector<GroundNutrient> nutrients;

    SensorType sensorType;



public:

    GroundSensor(nlohmann::json groundData) {
        updatedAt = groundData["updatedAt"].get<nlohmann::json::string_t>();
        sensorType = groundData["sensorType"].get<SensorType>();
        for (auto& elem : groundData["groundNutrient"]) {
            nutrients.push_back(GroundNutrient(elem)) ;
        }
    }

    const GroundNutrient &getNutrient(int i) const {
        return nutrients[i];
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
        nutrients.push_back(nutrientToAdd);
    }

    void update(ChangeSensorSettings settings) {
        for (GroundNutrient nutrient : nutrients) {
            if (nutrient.getType() == settings.getNutrientType()) {
                nutrient.setMaxValue(settings.getMaxValue());
                nutrient.setMinValue(settings.getMinValue());
            }
        }
    }

    void removeNutrient(string nutrientName) {
        vector<GroundNutrient>::iterator itToRemove;
        for (auto it = nutrients.begin(); it != nutrients.end(); ++it) {
            if ((*it).getType() == nutrientName)
                itToRemove = it;
        }

        nutrients.erase(itToRemove);
    }
//    void deleteNutrient(const string nutrientToDeleteType){
//        for(int i =0; i<= nutrientCounter;i++)
//            if(nutrient[i].getType() == nutrientToDeleteType)
//            {
//                cout<<"am intrat";
//
//            }}
    nlohmann::json to_json() {
        nlohmann::json j;
        json nutrientObjects = json::array();
        for (GroundNutrient nutrient : nutrients) {
            nutrientObjects.push_back(nutrient.to_json());
        }
        j = json{{"updatedAt",      this->updatedAt},
                 {"sensorType",     this->sensorType},
                 {"groundNutrient", nutrientObjects}};
        return j;
    }
};


#endif //SMART_FLOWER_POT_GROUNDSENSOR_H
