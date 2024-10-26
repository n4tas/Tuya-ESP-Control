#pragma once
#include <libubus.h>
#include <blobmsg.h>
#include <blobmsg_json.h>
#include <syslog.h>
#include <signal.h>

extern char output[512];

struct esp_devices {
    char *port_name;
    char *vid;
    char *pid;
};

extern struct esp_devices esp_devices;
extern struct ubus_context* ctx; 
/**
 * Removes backslash character from string.
 */
void remove_backslash(char* str);

/**
 * Establishes ubus context connection.
 */
struct ubus_context* ubus_ctx();

/**
 * Invoke function for ESP Devices.
 */
int devices_info();
/**
 * Parses invoke, receives ``ubus ESP Device`` data.
 */
void invoke_devices(struct ubus_request *req, int type, struct blob_attr *msg);

/**
 * Parses invoke, receives ``ubus ESP on/off/get` data.
 */
void on_off_get_payload(struct ubus_request *req, int type, struct blob_attr *msg);

/**
 * Invoke function for ESP ON.
 */
int devices_on(char *params);

/**
 * Invoke function for ESP OFF.
 */
int devices_off(char *params);

/**
 * Invoke function for ESP GET.
 */
int device_get(char *params);

