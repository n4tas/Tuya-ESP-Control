#ifndef TUYA_H
#define TUYA_H
#include "utilities.h"
#include "ubus.h"
#include <signal.h>
#include <stdlib.h>
#include <mqtt_client_interface.h>
#include <tuyalink_core.h>
#include <syslog.h>

/*
Callback function called when the MQTT connection is established.
This function logs the connection event when the MQTT client successfully connects to
the broker.
@param context Pointer to the MQTT context structure, providing the necessary
context for the MQTT operations.
@param user_data Pointer to user-defined data passed to the callback function.
This can be used to carry additional information or state.
*/
void on_connected(tuya_mqtt_context_t* context, void* user_data);

/*
Callback function called when the MQTT connection is lost or disconnected.
This function is designed to handle the event of the MQTT client disconnecting
from the broker.
@param context Pointer to the MQTT context structure, providing the necessary
context for the MQTT operations.
@param user_data Pointer to user-defined data passed to the callback function.
This can be used to carry additional information or state.
*/
void on_disconnect(tuya_mqtt_context_t* context, void* user_data);

/*
Callback function called when an MQTT message is received.
This function is executed whenever the MQTT client receives a message from the broker.
It logs the received message data.
@param context Pointer to the MQTT context structure, providing the necessary
context for the MQTT operations.
@param user_data Pointer to user-defined data passed to the callback function.
This can be used to carry additional information or state.
@param msg Pointer to the received message structure containing the message data.
*/
void on_messages(tuya_mqtt_context_t* context, void* user_data, const tuyalink_message_t* msg);

/**
 * Initializing and connecting to MQTT.
 * *device_id device ID
 * *device_secret device Secret
 */
int connect_init(tuya_mqtt_context_t *client, char *device_id, char *device_secret);

/**
 * Deinitializing and disconnecting from MQTT
 */
void disconnect_deinit(tuya_mqtt_context_t *client);

/**
 * Parses received cloud's message.
 */
void check_action_json(const tuyalink_message_t* msg, cJSON **main, cJSON **actionCode);

/**
 * Generates needed params based on action.
 */
void generate_params(const tuyalink_message_t* msg, char *params, char *action, cJSON *main, cJSON *actionCode);

/**
 * Generates payload string from JSON. Transmits to ``output``
 */
void cjson_payload_string(char *buffer, cJSON *main);

/**
 * Generates JSON for ubus ESP Devices function.
 */
int devices_tuya();

/**
 * Generates ESP Response.
 */
int on_tuya(const tuyalink_message_t* msg, cJSON *main, cJSON *actionCode);

/**
 * Generates ESP Response.
 */
int off_tuya(const tuyalink_message_t* msg, cJSON *main, cJSON *actionCode);

/**
 * Generates ESP Response.
 */
int get_tuya(const tuyalink_message_t* msg, cJSON *main, cJSON *actionCode);
#endif
