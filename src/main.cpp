#include <iostream>
#include <csignal>
#include <thread>
#include <chrono>
#include "domain/server.h"
#include "domain/device.h"
#include "domain/mqtt.h"
#include "libs/json.hpp"

using namespace std;

Server *server = NULL;

void startHttpServer(Server *server) {
    cout << "Starting HTTP Server..\n";
    Address address(Ipv4::any(), Port(9080));
    server = new Server(address);

    // Initialize and start the server
    server->init();
    server->start();
}

void startMqttClient() {
    cout << "Starting MQTT Client..\n";
    MqttClient::getInstance()->connectAndListen();
}

void startDevice() {
    cout << "Starting Event Loop..\n";
    Device::getInstance()->isRunning = true;
    while (Device::getInstance()->isRunning) {
        Device::getInstance()->loop();
        this_thread::sleep_for(chrono::milliseconds(500));
    }
}

void signalHandler(int signum) {
    cout << "Interrupt signal (" << signum << ") received.\n";

    Device::getInstance()->isRunning = false;
    Device::getInstance()->deleteInstance();

    MqttClient::getInstance()->disconnect();
    MqttClient::getInstance()->deleteInstance();

    server->stop();

    // terminate program
    exit(signum);
}

int main(int argc, char *argv[]) {
    // register signal SIGINT and signal handler
    signal(SIGINT, signalHandler);

    thread serverThread(startHttpServer, server);
    thread mqttThread(startMqttClient);
    thread deviceThread(startDevice);

    return 0;
}
