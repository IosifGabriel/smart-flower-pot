#include "server.h"
#include "utils/JSONUtils.h"
#include "utils/Constants.h"
#include "entities/example/Example.h"
#include "entities/groundSensor/GroundSensor.h"
#include "entities/groundSensor/GroundNutrient.h"
#include "libs/json.hpp"
#include "entities/request/ChangeSensorSettings.h"
#include "entities/sensor/SensorData.h"

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
    httpEndpoint->shutdown();
}

void Server::setupRoutes() {
    Rest::Routes::Get(router, "/hello", Rest::Routes::bind(&Server::hello, this));
    Rest::Routes::Get(router, "/testReadJson", Rest::Routes::bind(&Server::testReadJson, this));
    Rest::Routes::Get(router, "/testSaveJson", Rest::Routes::bind(&Server::testSaveJson, this));
    Rest::Routes::Get(router, "/groundSensor", Rest::Routes::bind(&Server::groundSensorJson, this));
    Rest::Routes::Post(router, "/settings", Rest::Routes::bind(&Server::changeSettings, this));

}

void Server::hello(const Rest::Request &request, Http::ResponseWriter response) {
    response.send(Pistache::Http::Code::Ok, "Hello World\n");
}

void Server::testReadJson(const Rest::Request &request, Http::ResponseWriter response) {

    Example example = Example(JSONUtils::readJsonFromFile(Constants::PROJECT_SRC_ROOT + Constants::EXAMPLE_JSON_FILE_PATH));

    response.send(Pistache::Http::Code::Ok, example.getPersonalData().getLastName());
}

void Server::testSaveJson(const Rest::Request &request, Http::ResponseWriter response) {
	Example example = Example(JSONUtils::readJsonFromFile(Constants::PROJECT_SRC_ROOT + Constants::EXAMPLE_JSON_FILE_PATH));	
	
	JSONUtils::writeJsonToFile(Constants::PROJECT_SRC_ROOT + Constants::EXAMPLE_JSON_SAVE_FILE_PATH, example.to_json().dump(4));
	
	response.send(Pistache::Http::Code::Ok, "Check project source folder");
}


void Server::groundSensorJson(const Rest::Request &request, Http::ResponseWriter response) {

    GroundSensor groundData = GroundSensor(JSONUtils::readJsonFromFile(Constants::PROJECT_SRC_ROOT + Constants::GROUND_SENSOR_PATH));
    response.send(Pistache::Http::Code::Ok, std::to_string(groundData.getNutrient().getValue()));
}

void Server::changeSettings(const Rest::Request &request, Http::ResponseWriter response) {
    ChangeSensorSettings req = ChangeSensorSettings(nlohmann::json::parse(request.body()));
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
        default:
            response.send(Pistache::Http::Code::Not_Acceptable, "The sensorType provided is not valid");
            return;
    }
    SensorData sensor = SensorData(JSONUtils::readJsonFromFile(Constants::PROJECT_SRC_ROOT + filePath));

    if (sensor.getMaxValue() == req.getMaxValue() && sensor.getMinValue() == req.getMinValue()) {
        response.send(Pistache::Http::Code::Not_Modified, "The same values are already set!");
        return;
    }

    if (req.getMinValue() > req.getMaxValue()) {
        response.send(Pistache::Http::Code::Not_Acceptable, "MinValue must be lower that maxValue!");
        return;
    }

    sensor.update(req);
    JSONUtils::writeJsonToFile(Constants::PROJECT_SRC_ROOT + filePath, sensor.to_json().dump(4));

    response.send(Pistache::Http::Code::Ok, "Success");
}
