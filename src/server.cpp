#include "server.h"
#include "device.h"

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
}

void Server::hello(const Rest::Request &request, Http::ResponseWriter response) {
    Device::getInstance()->test();

    response.send(Pistache::Http::Code::Ok, "Hello");
}