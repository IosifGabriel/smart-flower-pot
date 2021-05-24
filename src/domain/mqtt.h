#ifndef SMART_FLOWER_POT_MQTT_H
#define SMART_FLOWER_POT_MQTT_H

#include <iostream>
#include <mutex>
#include <string.h>
#include <mosquitto.h>

using namespace std;

class MqttClient {
public:
    static MqttClient *&getInstance();

    static void deleteInstance();

    void connectAndListen();

    void disconnect();

    void publish(const char *topic, string payload);

private:
	struct mosquitto *mosquitto = NULL;

    MqttClient();

    ~MqttClient();

    MqttClient(const MqttClient &signal);

    const MqttClient &operator=(const MqttClient &signal);

    static void messageCallback(struct mosquitto *mosquitto, void *userdata, const struct mosquitto_message *message);

	static void connectCallback(struct mosquitto *mosquitto, void *userdata, int result);

private:
    static MqttClient *m_MqttClient;
    static std::mutex m_Mutex;
};

#endif //SMART_FLOWER_POT_MQTT_H
