//
// Created by alexandru.jilavu on 25.03.2021.
//

#ifndef SMART_FLOWER_POT_EXAMPLE_H
#define SMART_FLOWER_POT_EXAMPLE_H


#include <string>
#include <iostream>
#include "../../libs/json.hpp"
#include "PersonalDataExample.h"
#include "SensorDataExample.h"

using nlohmann::json;

class Example {

private:

    PersonalDataExample personalData;

    SensorDataExample sensorDataExample;

    std::string editedBy;

public:

    Example(nlohmann::json example) {
        personalData = PersonalDataExample(example["personalData"]);
        sensorDataExample = SensorDataExample(example["sensorData"]);
        editedBy = (std::string) example["editedBy"];
    }

    const PersonalDataExample &getPersonalData() const {
        return personalData;
    }

    void setPersonalData(const PersonalDataExample &personalData) {
        Example::personalData = personalData;
    }

    const SensorDataExample &getSensorDataExample() const {
        return sensorDataExample;
    }

    void setSensorDataExample(const SensorDataExample &sensorDataExample) {
        Example::sensorDataExample = sensorDataExample;
    }

    const std::string &getEditedBy() const {
        return editedBy;
    }

    void setEditedBy(const std::string &editedBy) {
        Example::editedBy = editedBy;
    }
    
    nlohmann::json to_json(){
        nlohmann::json j;
    	j = json{{"personalData", this->personalData.to_json()}, {"sensorData", this->sensorDataExample.to_json()}, {"editedBy", this->editedBy}};
    	return j;
    }
};


#endif //SMART_FLOWER_POT_EXAMPLE_H
