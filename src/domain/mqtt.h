#ifndef SMART_FLOWER_POT_MQTT_H
#define SMART_FLOWER_POT_MQTT_H

#include <iostream>
#include <mutex>
#include <mosquitto.h>

using namespace std;

class MqttClient {
public:
    static MqttClient *&getInstance();

    static void deleteInstance();

    void connectAndListen();

    void disconnect();

private:
    MqttClient();

    ~MqttClient();

    MqttClient(const MqttClient &signal);

    const MqttClient &operator=(const MqttClient &signal);

    static void messageCallback(struct mosquitto *mosquitto, void *userdata, const struct mosquitto_message *message);

	static void connectCallback(struct mosquitto *mosquitto, void *userdata, int result);

 	static void subscribeCallback(struct mosquitto *mosquitto, void *userdata, int mid, int qos_count, const int *granted_qos);

 	static void logCallback(struct mosquitto *mosquitto, void *userdata, int level, const char *str);

private:
    static MqttClient *m_MqttClient;
    static std::mutex m_Mutex;
};

#endif //SMART_FLOWER_POT_MQTT_H
