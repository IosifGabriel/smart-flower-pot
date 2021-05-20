#include "mqtt.h"

MqttClient *MqttClient::m_MqttClient = NULL;
std::mutex MqttClient::m_Mutex;

MqttClient *&MqttClient::getInstance() {
    if (m_MqttClient == NULL) {
        std::unique_lock <std::mutex> lock(m_Mutex);
        if (m_MqttClient == NULL) {
            m_MqttClient = new(std::nothrow) MqttClient;
        }
    }

    return m_MqttClient;
}

void MqttClient::deleteInstance() {
	cout << "Delete MqttClient instance\n";

    std::unique_lock <std::mutex> lock(m_Mutex);
    if (m_MqttClient) {
        delete m_MqttClient;
        m_MqttClient = NULL;
    }
}

MqttClient::MqttClient() {
}

MqttClient::~MqttClient() {
}

void MqttClient::connectAndListen() {
	char *host = "test.mosquitto.org";
	int port = 1883;
	int keepalive = 60;
	bool clean_session = true;

	mosquitto_lib_init();
	this->mosquitto = mosquitto_new(NULL, clean_session, NULL);
	if (!this->mosquitto) {
		cout << "Error: Out of memory.\n";
		return;
	}

	mosquitto_connect_callback_set(this->mosquitto, MqttClient::connectCallback);
	mosquitto_message_callback_set(this->mosquitto, MqttClient::messageCallback);

	if (mosquitto_connect(this->mosquitto, host, port, keepalive)) {
		cout << "Unable to connect to MQTT server.\n";
		return;
	}

    mosquitto_loop_forever(this->mosquitto, -1, 1);
}

void MqttClient::disconnect() {
    cout << "Disconnecting MQTT Client...\n";

	mosquitto_destroy(this->mosquitto);
	mosquitto_lib_cleanup();
}

void MqttClient::messageCallback(struct mosquitto *mosquitto, void *userdata, const struct mosquitto_message *message) {
	if (message->payloadlen) {
		cout << "Received message on topic '" << message->topic << "': " << (char *)message->payload << "\n";
	}
	fflush(stdout);
}

void MqttClient::connectCallback(struct mosquitto *mosquitto, void *userdata, int error) {
	if (error) {
		cout << "MQTT connection failed\n";
		return;
	}

	cout << "MQTT connection succeded\n";

	mosquitto_subscribe(mosquitto, NULL, "test-ip/#", 2);
}
