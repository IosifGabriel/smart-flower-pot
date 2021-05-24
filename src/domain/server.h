#ifndef SMART_FLOWER_POT_SERVER_H
#define SMART_FLOWER_POT_SERVER_H

#include <pistache/endpoint.h>
#include <pistache/router.h>
#include "device.h"

using namespace Pistache;

class Server {
public:
    explicit Server(Address address) : httpEndpoint(std::make_shared<Http::Endpoint>(address)) {
    }

    void init(size_t thr = 2);

    void start();

    void stop();

private:
    std::shared_ptr <Http::Endpoint> httpEndpoint;
    Rest::Router router;

    void setupRoutes();

    void hello(const Rest::Request &request, Http::ResponseWriter response);

    void testReadJson(const Rest::Request &request, Http::ResponseWriter response);

    void testSaveJson(const Rest::Request &request, Http::ResponseWriter response);

    void groundSensorJson(const Rest::Request &request, Http::ResponseWriter response);

    void changeSettings(const Rest::Request &request, Http::ResponseWriter response);
    
    void changeValue(const Rest::Request &request, Http::ResponseWriter response);
};

#endif //SMART_FLOWER_POT_SERVER_H
