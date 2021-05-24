//
// Created by alexandru.jilavu on 24.05.2021.
//

#ifndef SMART_FLOWER_POT_PLANTINFO_H
#define SMART_FLOWER_POT_PLANTINFO_H

#include <string>
#include "../../libs/json.hpp"
#include "../../utils/JSONUtils.h"

using namespace std;
using nlohmann::json;

class PlantInfo {

private:
    string species;

    string color;

    string type;

    string updatedAt;

    double height;

public:
    PlantInfo(nlohmann::json plantInfo) {
        species = plantInfo["species"].get<std::string>();
        color = plantInfo["color"].get<std::string>();
        type = plantInfo["type"].get<std::string>();
        height = plantInfo["height"].get<double>();

        if (plantInfo["updatedAt"].is_null()) {
            updatedAt = JSONUtils::getCurrentDate();
        } else {
            updatedAt = plantInfo["updatedAt"].get<std::string>();
        }
    }

    PlantInfo() {

    }

    string getSpecies() {
        return this->species;
    }

    void setSpecies(string species) {
        this->species = species;
    }

    string getColor() {
        return this->color;
    }

    void setColor(string color) {
        this->color = color;
    }

    string getType() {
        return this->type;
    }

    void setType(string type) {
        this->type = type;
    }

    double getHeight() {
        return this->height;
    }

    void setHeight(double height) {
        this->height = height;
    }

    nlohmann::json to_json() {
        nlohmann::json j;
        j = json{{"updatedAt", this->updatedAt},
                 {"species",   this->species},
                 {"color",     this->color},
                 {"type",      this->type},
                 {"height",    this->height}};
        return j;
    }


};

#endif //SMART_FLOWER_POT_PLANTINFO_H
