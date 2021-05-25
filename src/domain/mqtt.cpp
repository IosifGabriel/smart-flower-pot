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

		if (strcmp(message->topic, "smart-flower-pot/music") == 0) {
			cout << "Playing music: " << (char *)message->payload << "\n";
		}
		else if (strcmp(message->topic, "smart-flower-pot/update") == 0) {
			auto rawCommand = json::parse((char *)message->payload);

			SensorType sensorType = rawCommand["sensorType"].get<SensorType>();
			double sensorValue = rawCommand["value"].get<double>();

			std::string filePath;
			switch (sensorType) {
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
					return;
			}

			if (sensorType != SensorType::GROUND) {
				SensorData sensor = SensorData(JSONUtils::readJsonFromFile(Constants::PROJECT_SRC_ROOT + filePath));
				sensor.update(sensorValue);
				JSONUtils::writeJsonToFile(Constants::PROJECT_SRC_ROOT + filePath, sensor.to_json().dump(4));
			} else {
				// TODO
			}
		}
	}

	fflush(stdout);
}

void MqttClient::connectCallback(struct mosquitto *mosquitto, void *userdata, int error) {
	if (error) {
		cout << "MQTT connection failed\n";
		return;
	}

	cout << "MQTT connection succeded\n";

	mosquitto_subscribe(mosquitto, NULL, "smart-flower-pot/music", 2);
	mosquitto_subscribe(mosquitto, NULL, "smart-flower-pot/update", 2);
}

void MqttClient::publish(const char *topic, string payload) {
	mosquitto_publish(this->mosquitto, NULL, topic, payload.length(), payload.c_str(), 2, false);
}
