//
// Created by alexandru.jilavu on 25.03.2021.
//

#ifndef SMART_FLOWER_POT_CONSTANTS_H
#define SMART_FLOWER_POT_CONSTANTS_H

#include <string>

class Constants {
public:
    inline static const std::string EXAMPLE_JSON_FILE_PATH = "/resources/example.json";
    inline static const std::string EXAMPLE_JSON_SAVE_FILE_PATH = "/resources/exampleSave.json";
    inline static const std::string GROUND_SENSOR_PATH = "/resources/groundSensor.json";
    inline static const std::string HUMIDITY_SENSOR_PATH = "/resources/humiditySensor.json";
    inline static const std::string TEMPERATURE_SENSOR_PATH = "/resources/temperatureSensor.json";
    inline static const std::string LIGHT_SENSOR_PATH = "/resources/lightSensor.json";
    inline static const std::string FERTILIZER_SENSOR_PATH = "/resources/fertilizerSensor.json";
    inline static const std::string PROJECT_SRC_ROOT = "/home/gabriel/Projects/smart-flower-pot/src";
};

#endif //SMART_FLOWER_POT_CONSTANTS_H
