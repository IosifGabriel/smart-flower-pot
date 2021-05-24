//
// Created by alexandru.jilavu on 25.03.2021.
//

#ifndef SMART_FLOWER_POT_JSONUTILS_H
#define SMART_FLOWER_POT_JSONUTILS_H

#include <string>
#include <fstream>
#include "../libs/json.hpp"
#include <iostream>
#include "../entities/sensor/SensorData.h"
#include "../entities/groundSensor/GroundSensor.h"
#include <chrono>
#include <string>
#include <memory>
#include <ctime>

using std::chrono::system_clock;


class JSONUtils {

public:
    static nlohmann::json readJsonFromFile(const std::string &fileName) {

        std::ifstream ifs(fileName);

        nlohmann::json jf = nlohmann::json::parse(ifs);

        return jf;
    }

    static void writeJsonToFile(const std::string &fileName, const std::string jsonDump) {

        std::ofstream ofs(fileName);
        ofs << jsonDump << std::endl;
    }

    static bool checkJsonFilesMinMax(const std::string& fileName,double value,std::string groundNutrientType){
        if(groundNutrientType.empty()) {
            SensorData sensor = SensorData(JSONUtils::readJsonFromFile(fileName));
            double minValue = sensor.getMinValue();
            double maxValue = sensor.getMaxValue();
            if(value < minValue || value > maxValue)
                return false;
            return true;
        }
        else {
            GroundSensor groundData = GroundSensor(JSONUtils::readJsonFromFile(fileName));
            int i = 0;
            GroundNutrient nutrient = groundData.getNutrient(i);
            while(nutrient.getType().empty())
            {
                if(nutrient.getType() == groundNutrientType)
                {
                    double minValue = nutrient.getMinValue();
                    double maxValue = nutrient.getMaxValue();
                    if(value < minValue || value > maxValue)
                        return false;
                    return true;
                }
                i++;
                nutrient = groundData.getNutrient(i);
            }
            return false;
        }
    }


    static std::string getCurrentDate() {
        system_clock::time_point tp = system_clock::now();

        time_t raw_time = system_clock::to_time_t(tp);

        struct tm  *timeinfo  = std::localtime(&raw_time);

        char buf[24] = {0};
        strftime(buf, 24, "%Y-%m-%d %H:%M:%S,", timeinfo);

        std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(tp.time_since_epoch());

        std::string milliseconds_str =  std::to_string(ms.count() % 1000);

        if (milliseconds_str.length() < 3) {
            milliseconds_str = std::string(3 - milliseconds_str.length(), '0') + milliseconds_str;
        }

        return std::string(buf) + milliseconds_str;
    }
};


#endif //SMART_FLOWER_POT_JSONUTILS_H
