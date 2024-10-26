#ifndef UTILS_H
#define UTILS_H
#include "tuya.h"
#include <argp.h>
#include <signal.h>
#include <string.h>

struct arguments {
    char device_secret[25];
    char product_id[25];
    char device_id[25];
    int daemon;
};
typedef struct {
    struct tuya_mqtt_context *client;
} signal_context_t;

signal_context_t* get_signal_context();

void set_signal_context(struct tuya_mqtt_context *client);

extern struct arguments arguments;

__attribute__((unused))static struct argp_option options[] = {
    {"device_secret", 'S', "DEVICE_SECRET", 0, "Direct passing of \"Device Secret\".", 0},
    {"product_id", 'P', "PRODUCT_ID", 0, "Direct passing of \"Product ID\"", 0},
    {"device_id", 'D', "DEVICE_ID", 0, "Direct passing \"Device ID\"", 0},
	{"daemon", 'd', 0, OPTION_ARG_OPTIONAL, "Direct passing \"Daemon\"", 0},
    {"help", 'h', 0, OPTION_ARG_OPTIONAL, "Args information", -1},
    {"usage", 'u', 0, OPTION_ARG_OPTIONAL, "Show usage", 0},
    {0}
};

error_t parse_opt(int key, char *arg, struct argp_state *state);

int load_arguments(int argc, char **argv);

void str_to_hex(int decimal, char *buffer);

void handle_signal(int sig);

#endif