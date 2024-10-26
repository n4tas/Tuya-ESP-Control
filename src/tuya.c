#include "tuya.h"
#include "tuya_cacert.h"

void on_connected(tuya_mqtt_context_t* context, void* user_data) 
{
    syslog(LOG_INFO, "Tuya Connected.\n\n");
}

void on_disconnect(tuya_mqtt_context_t* context, void* user_data)
{
    syslog(LOG_INFO, "Tuya Disconnected.\n\n");
}

void on_messages(tuya_mqtt_context_t* context, void* user_data, const tuyalink_message_t* msg) 
{   
    syslog(LOG_INFO, "Received message: %s", msg->data_string);  
    switch (msg->type) {
        case THING_TYPE_ACTION_EXECUTE:
            printf("\n");
            cJSON *main_object = NULL;
            cJSON *actionCode = NULL;
            check_action_json(msg, &main_object, &actionCode);
            if (strcmp(actionCode->valuestring, "devices") == 0) {
                if (devices_tuya() != 0){
                    cJSON_Delete(main_object);
                    return;
                }
            }
            if (strcmp(actionCode->valuestring, "on") == 0){
                if (on_tuya(msg, main_object, actionCode) != 0){
                    cJSON_Delete(main_object);
                    return;
                }
            }
            if (strcmp(actionCode->valuestring, "off") == 0){
                if (off_tuya(msg, main_object, actionCode) != 0){
                    cJSON_Delete(main_object);
                    return;
                }
            }
            if (strcmp(actionCode->valuestring, "get") == 0){
                if (get_tuya(msg, main_object, actionCode) != 0){
                    cJSON_Delete(main_object);
                    return;
                }
            }
            tuyalink_thing_property_report(context, arguments.device_id, output);
            cJSON_Delete(main_object);
            break;
        default:
            break;
    }
}

int connect_init(tuya_mqtt_context_t *client, char *device_id, char *device_secret)
{   
    int ret = 0;
    ret = tuya_mqtt_init(client, &(const tuya_mqtt_config_t) {
        .host = "m2.tuyacn.com",
        .port = 8883,
        .cacert = (const unsigned char *)tuya_cacert_pem,
        .cacert_len = sizeof(tuya_cacert_pem),
        .device_id = device_id,
        .device_secret = device_secret,
        .keepalive = 60,
        .timeout_ms = 2000,
        .on_connected = on_connected,
        .on_disconnect = on_disconnect,
        .on_messages = on_messages
    });
    if (ret != 0){
        syslog(LOG_ERR, "Error trying to initialize tuya_mqtt [CONNECT_INIT]\n\n");
        return 5;
    }
    ret = tuya_mqtt_connect(client);
    if (ret != 0){
        syslog(LOG_ERR, "Error trying to connect to tuya_mqtt [CONNECT_INIT]\n\n");
        tuya_mqtt_deinit(client);
        return 6;
    }
    return 0;
}

void disconnect_deinit(tuya_mqtt_context_t *client)
{   
    tuya_mqtt_disconnect(client);
    tuya_mqtt_deinit(client);
}

void cjson_payload_string(char *buffer, cJSON *main)
{
    buffer = cJSON_PrintUnformatted(main);
    strcpy(output, buffer);
    free(buffer);
}

int devices_tuya()
{   
    cJSON *object = cJSON_CreateObject();
    if (object == NULL) 
        return -1;
    devices_info();
    char buffer[512];
    cJSON_AddStringToObject(object, "port_name", esp_devices.port_name);
    cJSON_AddStringToObject(object, "vid", esp_devices.vid);
    cJSON_AddStringToObject(object, "pid", esp_devices.pid);
    cjson_payload_string(buffer, object);
    cJSON_Delete(object );
    return 0;
}

void check_action_json(const tuyalink_message_t* msg, cJSON **main, cJSON **actionCode)
{
    *main = cJSON_Parse(msg->data_string);
    if (*main == NULL)
        return;
    *actionCode = cJSON_GetObjectItem(*main, "actionCode");
    if (*actionCode == NULL) {
        cJSON_Delete(*main);
        return;
    }
}

void generate_params(const tuyalink_message_t* msg, char *params, char *action, cJSON *main, cJSON *actionCode)
{   
    cJSON *input = cJSON_GetObjectItem(main, "inputParams");
    if ((strcmp(action, "on") == 0) || (strcmp(action, "off") == 0)){
        sprintf(params, "{\"port\":\"%s\", \"pin\":%d}", 
        input->child->valuestring, input->child->next->valueint);
    } 
    if (strcmp(action, "get") == 0){
        sprintf(params, "{\"port\":\"%s\", \"pin\":%d, \"sensor\":\"%s\",\"model\":\"%s\"}", 
            input->child->valuestring, input->child->next->valueint, 
                input->child->next->next->valuestring, input->child->next->next->next->valuestring);
    }  
}

int on_tuya(const tuyalink_message_t* msg, cJSON *main, cJSON *actionCode)
{
    cJSON *object = cJSON_CreateObject();
    if (object == NULL)
        return -1;
    char params[256] = "";
    char buffer[512];
    generate_params(msg, params, "on", main, actionCode);
    devices_on(params);
    cJSON_AddStringToObject(main, "response", output);
    cjson_payload_string(buffer, main);
    cJSON_Delete(object);
    return 0;
}

int off_tuya(const tuyalink_message_t* msg, cJSON *main, cJSON *actionCode)
{
    cJSON *object = cJSON_CreateObject();
    if (object == NULL)
        return -1;
    char params[256] = "";
    char buffer[512];
    generate_params(msg, params, "off", main, actionCode);
    devices_off(params);
    cJSON_AddStringToObject(main, "response", output);
    cjson_payload_string(buffer, main);
    cJSON_Delete(object);
    return 0;
}

int get_tuya(const tuyalink_message_t* msg, cJSON *main, cJSON *actionCode)
{
    cJSON *object = cJSON_CreateObject();
    if (object == NULL)
        return -1;
    char params[256] = "";
    char buffer[512];
    generate_params(msg, params, "get", main, actionCode);
    device_get(params);
    cJSON_AddStringToObject(main, "response", output);
    cjson_payload_string(buffer, main);
    cJSON_Delete(object);
    return 0;
}
