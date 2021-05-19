//
// Created by alexandru.jilavu on 25.03.2021.
//

#ifndef SMART_FLOWER_POT_CONSTANTS_H
#define SMART_FLOWER_POT_CONSTANTS_H

#include <string>

class Constants {
public:

    static const std::string EXAMPLE_JSON_FILE_PATH;
    static const std::string EXAMPLE_JSON_SAVE_FILE_PATH;
    static const std::string PROJECT_SRC_ROOT;
    static const std::string GROUND_SENSOR_PATH;

};

const std::string Constants::EXAMPLE_JSON_FILE_PATH = "/resources/example.json";
const std::string Constants::EXAMPLE_JSON_SAVE_FILE_PATH = "/resources/exampleSave.json";
const std::string Constants::GROUND_SENSOR_PATH = "/resources/groundSensor.json";
const std::string Constants::PROJECT_SRC_ROOT = "/mnt/c/Users/alex0/CLionProjects/smart-flower-pot/src/";

#endif //SMART_FLOWER_POT_CONSTANTS_H
