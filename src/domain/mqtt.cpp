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
	this->mosq = mosquitto_new(NULL, clean_session, NULL);
	if (!this->mosq) {
		cout << "Error: Out of memory.\n";
		return;
	}

	mosquitto_log_callback_set(this->mosq, MqttClient::logCallback);
	mosquitto_connect_callback_set(this->mosq, MqttClient::connectCallback);
	mosquitto_message_callback_set(this->mosq, MqttClient::messageCallback);
	mosquitto_subscribe_callback_set(this->mosq, MqttClient::subscribeCallback);

	if (mosquitto_connect(this->mosq, host, port, keepalive)) {
		cout << "Unable to connect to MQTT server.\n";
		return ;
	}

    mosquitto_loop_forever(this->mosq, -1, 1);
}

void MqttClient::disconnect() {
    cout << "Disconnecting MQTT Client...\n";

	mosquitto_destroy(this->mosq);
	mosquitto_lib_cleanup();
}

void MqttClient::messageCallback(struct mosquitto *mosq, void *userdata, const struct mosquitto_message *message) {
	if(message->payloadlen){
		printf("%s %s\n", message->topic, message->payload);
	}else{
		printf("%s (null)\n", message->topic);
	}
	fflush(stdout);
}

void MqttClient::connectCallback(struct mosquitto *mosq, void *userdata, int result) {
	if(!result){
		// TODO
		mosquitto_subscribe(mosq, NULL, "test-ip/#", 2);
	}else{
		fprintf(stderr, "Connect failed\n");
	}
}

void MqttClient::subscribeCallback(struct mosquitto *mosq, void *userdata, int mid, int qos_count, const int *granted_qos) {
	printf("Subscribed (mid: %d): %d", mid, granted_qos[0]);
	for(int i=1; i<qos_count; i++){
		printf(", %d", granted_qos[i]);
	}
	printf("\n");
}

void MqttClient::logCallback(struct mosquitto *mosq, void *userdata, int level, const char *str) {
	/* Pring all log messages regardless of level. */
	printf("%s\n", str);
}
