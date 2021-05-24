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
    static const std::string HUMIDITY_SENSOR_PATH;
    static const std::string TEMPERATURE_SENSOR_PATH;
    static const std::string LIGHT_SENSOR_PATH;
    static const std::string FERTILIZER_SENSOR_PATH;
    static const std::string PLANT_INFO_PATH;
    static const std::string SENSOR_PATH;

};

const std::string Constants::EXAMPLE_JSON_FILE_PATH = "/resources/example.json";
const std::string Constants::EXAMPLE_JSON_SAVE_FILE_PATH = "/resources/exampleSave.json";
const std::string Constants::GROUND_SENSOR_PATH = "/resources/groundSensor.json";
const std::string Constants::PROJECT_SRC_ROOT = "/mnt/c/Users/Fane/Desktop/smart-flower-pot/src/";
const std::string Constants::HUMIDITY_SENSOR_PATH = "/resources/humiditySensor.json";
const std::string Constants::TEMPERATURE_SENSOR_PATH = "/resources/temperatureSensor.json";
const std::string Constants::LIGHT_SENSOR_PATH = "/resources/lightSensor.json";
const std::string Constants::FERTILIZER_SENSOR_PATH = "/resources/fertilizerSensor.json";
const std::string Constants::PLANT_INFO_PATH = "/resources/plantInfo.json";
const std::string Constants::PROJECT_SRC_ROOT = "/home/alexandru.jilavu/CLionProjects/smart-flower-pot/src";

#endif //SMART_FLOWER_POT_CONSTANTS_H
