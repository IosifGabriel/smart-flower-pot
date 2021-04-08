#include <signal.h>
#include <thread>
#include <chrono>
#include "server.h"
#include "device.h"
#include "libs/json.hpp"

using namespace std;

void startHttpServer(Server *server) {
    Address address(Ipv4::any(), Port(9080));
    server = new Server(address);

    // Initialize and start the server
    server->init();
    server->start();
}

void startDevice() {
    Device::getInstance()->isRunning = true;
    while (Device::getInstance()->isRunning) {
        Device::getInstance()->loop();
        this_thread::sleep_for (chrono::milliseconds (500));
    }
}

int main(int argc, char *argv[]) {
    // This code is needed for gracefully shutdown of the server when no longer needed.
    sigset_t signals;
    if (sigemptyset(&signals) != 0
        || sigaddset(&signals, SIGTERM) != 0
        || sigaddset(&signals, SIGINT) != 0
        || sigaddset(&signals, SIGHUP) != 0
        || pthread_sigmask(SIG_BLOCK, &signals, nullptr) != 0) {
        perror("install signal handler failed");
        return 1;
    }

    Server *server = NULL;
    thread serverThread(startHttpServer, server);

    thread deviceThread(startDevice);

    // Code that waits for the shutdown signal for the server
    int signal = 0;
    int status = sigwait(&signals, &signal);
    if (status == 0) {
        std::cout << "received signal " << signal << std::endl;
    } else {
        std::cerr << "sigwait returns " << status << std::endl;
    }

    Device::getInstance()->isRunning = false;
    deviceThread.join();

    // TODO Solve 'Segmentation fault' on exit
    serverThread.join();
    server->stop();
}
