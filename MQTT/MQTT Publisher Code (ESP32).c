#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MQTTClient.h"

#define ADDRESS    "tcp://broker.hivemq.com:1883"  // Public MQTT Broker
#define CLIENTID   "ESP32_Publisher"
#define TOPIC      "esp32/test"
#define PAYLOAD    "Hello from ESP32 Publisher!"
#define QOS        1
#define TIMEOUT    10000L

int main() {
    MQTTClient client;
    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;

    // Create MQTT client
    MQTTClient_create(&client, ADDRESS, CLIENTID, MQTTCLIENT_PERSISTENCE_NONE, NULL);
    
    // Set connection options
    conn_opts.keepAliveInterval = 20;
    conn_opts.cleansession = 1;

    // Connect to MQTT broker
    if (MQTTClient_connect(client, &conn_opts) != MQTTCLIENT_SUCCESS) {
        printf("Failed to connect to MQTT broker\n");
        return -1;
    }

    // Publish message
    MQTTClient_message pubmsg = MQTTClient_message_initializer;
    pubmsg.payload = (void*)PAYLOAD;
    pubmsg.payloadlen = strlen(PAYLOAD);
    pubmsg.qos = QOS;
    pubmsg.retained = 0;
    MQTTClient_deliveryToken token;

    MQTTClient_publishMessage(client, TOPIC, &pubmsg, &token);
    printf("Message Published: %s\n", PAYLOAD);

    MQTTClient_waitForCompletion(client, token, TIMEOUT);
    MQTTClient_disconnect(client, 10000);
    MQTTClient_destroy(&client);

    return 0;
}


/*
    stdio.h → Standard Input/Output functions (e.g., printf).

    stdlib.h → General purpose functions (e.g., memory allocation).

    string.h → String handling functions.

    MQTTClient.h → MQTT client library from Eclipse Paho, used for MQTT communication.

    ADDRESS → The MQTT broker URL (tcp://broker.hivemq.com:1883).

    CLIENTID → Unique ID for this MQTT client (ESP32_Publisher).

    TOPIC → The topic where this client will publish (esp32/test).

    PAYLOAD → The actual message that will be sent ("Hello from ESP32 Publisher!").

    QOS → Quality of Service (QoS) level (1 → message is delivered at least once).

    TIMEOUT → Time in milliseconds (10 seconds) to wait for message delivery.


    MQTTClient client;
    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;

    MQTTClient client; → Declares an MQTT client instance.
    
    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;

    Initializes connection options using default values.
    
*/