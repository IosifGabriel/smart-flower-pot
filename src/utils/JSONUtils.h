//
// Created by alexandru.jilavu on 25.03.2021.
//

#ifndef SMART_FLOWER_POT_JSONUTILS_H
#define SMART_FLOWER_POT_JSONUTILS_H

#include <string>
#include <fstream>
#include "../libs/json.hpp"
#include <iostream>

class JSONUtils {

public:
    static nlohmann::json readJsonFromFile(const std::string& fileName) {

        std::ifstream ifs(fileName);

        nlohmann::json jf = nlohmann::json::parse(ifs);

        return jf;
    }
	
    static void writeJsonToFile(const std::string& fileName, const std::string jsonDump) {

	std::ofstream ofs(fileName);
	ofs << jsonDump << std::endl;
    }
};


#endif //SMART_FLOWER_POT_JSONUTILS_H
