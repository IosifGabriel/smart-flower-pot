#include "server.h"
#include "../utils/JSONUtils.h"
#include "../utils/Constants.h"
#include "../entities/example/Example.h"
#include "../entities/groundSensor/GroundSensor.h"
#include "../entities/groundSensor/GroundNutrient.h"
#include "../libs/json.hpp"
#include "../entities/request/ChangeSensorSettings.h"
#include "../entities/sensor/SensorData.h"
#include "../entities/plant/PlantInfo.h"

using nlohmann::json;

void Server::init(size_t thr) {
    auto opts = Http::Endpoint::options()
            .threads(static_cast<int>(thr));
    httpEndpoint->init(opts);

    setupRoutes();
}

void Server::start() {
    httpEndpoint->setHandler(router.handler());
    httpEndpoint->serveThreaded();
}

void Server::stop() {
    cout << "Shutdown Server\n";
    httpEndpoint->shutdown();
}

void Server::setupRoutes() {
    // Rest::Routes::Get(router, "/hello", Rest::Routes::bind(&Server::hello, this));
    // Rest::Routes::Get(router, "/testReadJson", Rest::Routes::bind(&Server::testReadJson, this));
    // Rest::Routes::Get(router, "/testSaveJson", Rest::Routes::bind(&Server::testSaveJson, this));
    // Rest::Routes::Get(router, "/groundSensor", Rest::Routes::bind(&Server::groundSensorJson, this));
    Rest::Routes::Post(router, "/settings", Rest::Routes::bind(&Server::changeSettings, this));
    Rest::Routes::Post(router, "/value", Rest::Routes::bind(&Server::changeValue, this));
    Rest::Routes::Put(router, "/plantInfo", Rest::Routes::bind(&Server::updatePlantInfo, this));
    Rest::Routes::Get(router, "/plantInfo", Rest::Routes::bind(&Server::getPlantInfo, this));
    Rest::Routes::Post(router, "/addNutrient", Rest::Routes::bind(&Server::addNutrient, this));
    Rest::Routes::Post(router, "/removeNutrient/:nutrientName", Rest::Routes::bind(&Server::removeNutrient, this));
    Rest::Routes::Get(router, "/getStatus/:sensorType", Rest::Routes::bind(&Server::getStatus, this));

}

void Server::hello(const Rest::Request &request, Http::ResponseWriter response) {
    response.send(Pistache::Http::Code::Ok, "Hello World\n");
}

void Server::testReadJson(const Rest::Request &request, Http::ResponseWriter response) {
    Example example = Example(
            JSONUtils::readJsonFromFile(Constants::PROJECT_SRC_ROOT + Constants::EXAMPLE_JSON_FILE_PATH));

    response.send(Pistache::Http::Code::Ok, example.getPersonalData().getLastName());
}

void Server::testSaveJson(const Rest::Request &request, Http::ResponseWriter response) {
    Example example = Example(
            JSONUtils::readJsonFromFile(Constants::PROJECT_SRC_ROOT + Constants::EXAMPLE_JSON_FILE_PATH));

    JSONUtils::writeJsonToFile(Constants::PROJECT_SRC_ROOT + Constants::EXAMPLE_JSON_SAVE_FILE_PATH,
                               example.to_json().dump(4));

    response.send(Pistache::Http::Code::Ok, "Check project source folder");
}


void Server::groundSensorJson(const Rest::Request &request, Http::ResponseWriter response) {

    GroundSensor groundData = GroundSensor(
            JSONUtils::readJsonFromFile(Constants::PROJECT_SRC_ROOT + Constants::GROUND_SENSOR_PATH));
    response.send(Pistache::Http::Code::Ok, std::to_string(groundData.getNutrient(0).getValue()));
}

void Server::changeSettings(const Rest::Request &request, Http::ResponseWriter response) {
    ChangeSensorSettings req = ChangeSensorSettings(nlohmann::json::parse(request.body()));

    if (req.getMinValue() > req.getMaxValue()) {
        response.send(Pistache::Http::Code::Not_Acceptable, "MinValue must be lower that maxValue!");
        return;
    }

    std::string filePath;
    switch (req.getSensorType()) {
        case SensorType::HUMIDITY:
            filePath = Constants::HUMIDITY_SENSOR_PATH;
            break;
        case SensorType::LIGHT:
            filePath = Constants::LIGHT_SENSOR_PATH;
            break;
        case SensorType::TEMPERATURE:
            filePath = Constants::TEMPERATURE_SENSOR_PATH;
            break;
        case SensorType::FERTILIZER:
            filePath = Constants::FERTILIZER_SENSOR_PATH;
            break;
        case SensorType::GROUND:
            filePath = Constants::GROUND_SENSOR_PATH;
            break;
        default:
            response.send(Pistache::Http::Code::Not_Acceptable, "The sensorType provided is not valid");
            return;
    }

    if (req.getSensorType() != SensorType::GROUND) {
        SensorData sensor = SensorData(JSONUtils::readJsonFromFile(Constants::PROJECT_SRC_ROOT + filePath));
        if (sensor.getMaxValue() == req.getMaxValue() && sensor.getMinValue() == req.getMinValue()) {
            response.send(Pistache::Http::Code::Not_Modified, "The same values are already set!");
            return;
        }
        sensor.update(req);
        JSONUtils::writeJsonToFile(Constants::PROJECT_SRC_ROOT + filePath, sensor.to_json().dump(4));
    } else {
        GroundSensor sensor = GroundSensor(JSONUtils::readJsonFromFile(Constants::PROJECT_SRC_ROOT + filePath));
        sensor.update(req);
        JSONUtils::writeJsonToFile(Constants::PROJECT_SRC_ROOT + filePath, sensor.to_json().dump(4));
    }

    response.send(Pistache::Http::Code::Ok, "Success");
}

void Server::changeValue(const Rest::Request &request, Http::ResponseWriter response) {
    ChangeSensorValue req = ChangeSensorValue(nlohmann::json::parse(request.body()));

    std::string filePath;
    switch (req.getSensorType()) {
    	case SensorType::GROUND:
            filePath = Constants::GROUND_SENSOR_PATH;
            break;
        case SensorType::HUMIDITY:
            filePath = Constants::HUMIDITY_SENSOR_PATH;
            break;
        case SensorType::LIGHT:
            filePath = Constants::LIGHT_SENSOR_PATH;
            break;
        case SensorType::TEMPERATURE:
            filePath = Constants::TEMPERATURE_SENSOR_PATH;
            break;
        case SensorType::FERTILIZER:
            filePath = Constants::FERTILIZER_SENSOR_PATH;
            break;
        default:
            response.send(Pistache::Http::Code::Not_Acceptable, "The sensorType provided is not valid");
            return;
    }
    SensorData sensor = SensorData(JSONUtils::readJsonFromFile(Constants::PROJECT_SRC_ROOT + filePath));

    if (sensor.getValue() == req.getValue()) {
        response.send(Pistache::Http::Code::Not_Acceptable, "The same values are already set!");
        return;
    }

    if (req.getValue() < sensor.getMinValue()) {
        response.send(Pistache::Http::Code::Not_Acceptable, "Value is lesser than the minimum value");
        return;
    }

    if (req.getValue() > sensor.getMaxValue()) {
        response.send(Pistache::Http::Code::Not_Acceptable, "Value is great than the maxim value");
        return;
    }

    sensor.update(req);
    JSONUtils::writeJsonToFile(Constants::PROJECT_SRC_ROOT + filePath, sensor.to_json().dump(4));

    response.send(Pistache::Http::Code::Ok, "Success");
}

void Server::addNutrient(const Rest::Request &request, Http::ResponseWriter response) {
    GroundNutrient nutrientToAdd = GroundNutrient(nlohmann::json::parse(request.body()));
    GroundSensor groundData = GroundSensor(JSONUtils::readJsonFromFile(Constants::PROJECT_SRC_ROOT + Constants::GROUND_SENSOR_PATH));

    groundData.addNutrient(nutrientToAdd);
    JSONUtils::writeJsonToFile(Constants::PROJECT_SRC_ROOT + Constants::GROUND_SENSOR_PATH, groundData.to_json().dump(4));
    response.send(Pistache::Http::Code::Ok, "Success");
}

void Server::removeNutrient(const Rest::Request &request, Http::ResponseWriter response) {
    string param = request.param(":nutrientName").as<std::string>();

    GroundSensor groundData = GroundSensor(JSONUtils::readJsonFromFile(Constants::PROJECT_SRC_ROOT + Constants::GROUND_SENSOR_PATH));

    groundData.removeNutrient(param);

    JSONUtils::writeJsonToFile(Constants::PROJECT_SRC_ROOT + Constants::GROUND_SENSOR_PATH, groundData.to_json().dump(4));
    response.send(Pistache::Http::Code::Ok, "Success");
}

void Server::updatePlantInfo(const Rest::Request &request, Http::ResponseWriter response) {
    PlantInfo req = PlantInfo(nlohmann::json::parse(request.body()));

    JSONUtils::writeJsonToFile(Constants::PROJECT_SRC_ROOT + Constants::PLANT_INFO_PATH, req.to_json().dump(4));

    response.send(Pistache::Http::Code::Ok, "Success");
}

void Server::getPlantInfo(const Rest::Request &request, Http::ResponseWriter response) {
    PlantInfo plant = JSONUtils::readJsonFromFile(Constants::PROJECT_SRC_ROOT + Constants::PLANT_INFO_PATH);

    response.send(Pistache::Http::Code::Ok, plant.to_json().dump(4));
}

void Server::getStatus(const Rest::Request &request, Http::ResponseWriter response) {
    auto param = request.param(":sensorType").as<std::string>();
    if (param == "humidity") {
        SensorData sensor = SensorData(JSONUtils::readJsonFromFile(Constants::PROJECT_SRC_ROOT + Constants::HUMIDITY_SENSOR_PATH));
        response.send(Pistache::Http::Code::Ok, sensor.to_json().dump(4));
    } else if (param == "light") {
        SensorData sensor = SensorData(JSONUtils::readJsonFromFile(Constants::PROJECT_SRC_ROOT + Constants::LIGHT_SENSOR_PATH));
        response.send(Pistache::Http::Code::Ok, sensor.to_json().dump(4));
    } else if (param == "temperature") {
        SensorData sensor = SensorData(JSONUtils::readJsonFromFile(Constants::PROJECT_SRC_ROOT + Constants::TEMPERATURE_SENSOR_PATH));
        response.send(Pistache::Http::Code::Ok, sensor.to_json().dump(4));
    } else if (param == "fertilizer") {
        SensorData sensor = SensorData(JSONUtils::readJsonFromFile(Constants::PROJECT_SRC_ROOT + Constants::FERTILIZER_SENSOR_PATH));
        response.send(Pistache::Http::Code::Ok, sensor.to_json().dump(4));
    } else if (param == "ground") {
        GroundSensor sensor1 = GroundSensor(JSONUtils::readJsonFromFile(Constants::PROJECT_SRC_ROOT + Constants::GROUND_SENSOR_PATH));
        response.send(Pistache::Http::Code::Ok, sensor1.to_json().dump(4));
    } else {
        response.send(Pistache::Http::Code::Not_Acceptable, "The sensorType provided is not valid");
    }
}
