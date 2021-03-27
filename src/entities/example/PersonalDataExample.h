//
// Created by alexandru.jilavu on 25.03.2021.
//

#ifndef SMART_FLOWER_POT_PERSONALDATAEXAMPLE_H
#define SMART_FLOWER_POT_PERSONALDATAEXAMPLE_H
#include <string>
#include "../../libs/json.hpp"

using nlohmann::json;

class PersonalDataExample {

private:
    std::string address;

    std::string firstName;

    std::string lastName;

    std::string personalIDNumber;

public:
    PersonalDataExample(nlohmann::json personalData) {
        address = (std::string) personalData["address"];
        firstName = (std::string) personalData["firstName"];
        lastName = (std::string) personalData["lastName"];
        personalIDNumber = (std::string) personalData["personalIDNumber"];
    }

    PersonalDataExample() {}

    const std::string &getAddress() const {
        return address;
    }

    void setAddress(const std::string &address) {
        PersonalDataExample::address = address;
    }

    const std::string &getFirstName() const {
        return firstName;
    }

    void setFirstName(const std::string &firstName) {
        PersonalDataExample::firstName = firstName;
    }

    const std::string &getLastName() const {
        return lastName;
    }

    void setLastName(const std::string &lastName) {
        PersonalDataExample::lastName = lastName;
    }

    const std::string &getPersonalIdNumber() const {
        return personalIDNumber;
    }

    void setPersonalIdNumber(const std::string &personalIdNumber) {
        personalIDNumber = personalIdNumber;
    }
    
    void to_json(json& j){
    	j = json{{"address", this->address}, {"firstName", this->firstName}, {"lastName", this->lastName}, {"personalIDNumber", this->personalIDNumber}};
    }
};


#endif //SMART_FLOWER_POT_PERSONALDATAEXAMPLE_H
