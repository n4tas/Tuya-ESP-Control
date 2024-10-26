#include "ubus.h"

char output[512];
struct ubus_context* ctx = NULL; 
struct esp_devices esp_devices = { 0 };

enum {
    DEVICES,
    SYSTEM_MAX
};

enum {
    PORT_NAME,
    VID,
    PID,
    DEVICES_MAX
};

static const struct blobmsg_policy system_policy[SYSTEM_MAX] = {
	[DEVICES] { .name = "devices", .type = BLOBMSG_TYPE_ARRAY }
};

static const struct blobmsg_policy devices_policy[DEVICES_MAX] = {
	[PORT_NAME] = { .name = "port_name", .type = BLOBMSG_TYPE_STRING },
    [VID] = {.name = "vid", .type = BLOBMSG_TYPE_STRING },
    [PID] = { .name = "pid", .type = BLOBMSG_TYPE_STRING }
};

struct ubus_context* ubus_ctx()
{   
    ctx = ubus_connect(NULL);
	if (!ctx) {
		syslog(LOG_ERR, "Ubus failed to connect\n");
        return NULL;
	}
    return ctx;
}

int devices_on(char *params)
{   
    uint32_t id = 0;
    if (ubus_lookup_id(ctx, "esp", &id)) {
        return -1;
    }
    struct blob_buf b = {0};
    blob_buf_init(&b, 0);
    if (!blobmsg_add_json_from_string(&b, params)) {
        blob_buf_free(&b);
        return -1;
    } 
    if (ubus_invoke(ctx, id, "on", b.head, on_off_get_payload, output, 5000)){
        blob_buf_free(&b);
        return -1;
    }
    blob_buf_free(&b);
    return 0;
}

int devices_off(char *params)
{   
    uint32_t id = 0;
    if (ubus_lookup_id(ctx, "esp", &id)) {
        return -1;
    }
    struct blob_buf b = {0};
    blob_buf_init(&b, 0);
    if (!blobmsg_add_json_from_string(&b, params)) {
        blob_buf_free(&b);
        return -1;
    }
    if (ubus_invoke(ctx, id, "off", b.head, on_off_get_payload, output, 5000)){
        blob_buf_free(&b);
        return -1;
    }
    blob_buf_free(&b);
    return 0;
}

void remove_backslash(char* str) 
{
    char *read = str, *write = str;
    while (*read) {
        *write = *read++;
        write += (*write != '\\');
    }
    *write = '\0';
}

void on_off_get_payload(struct ubus_request *req, int type, struct blob_attr *msg)
{   
    char *buffer = blobmsg_format_json(msg, true);
    remove_backslash(buffer);
    strcpy(output, buffer);
    free(buffer);
}

int devices_info()
{   
    uint32_t id = 0;
    if (ubus_lookup_id(ctx, "esp", &id)){
        return -1;
    }
    if (ubus_invoke(ctx, id, "devices", NULL, invoke_devices, &esp_devices, 3000) != 0){
        return -1;
    }
	return 0;
}

void invoke_devices(struct ubus_request *req, int type, struct blob_attr *msg)
{   
    struct blob_attr *tb[SYSTEM_MAX];
    struct blob_attr *cur;
    int rem;
    blobmsg_parse(system_policy, SYSTEM_MAX, tb, blob_data(msg),
        blob_len(msg));
    if (!tb[DEVICES])
        return;
    blobmsg_for_each_attr(cur, tb[DEVICES], rem) {
        struct blob_attr *devices[DEVICES_MAX];
        blobmsg_parse(devices_policy, DEVICES_MAX, devices, blobmsg_data(cur), blobmsg_data_len(cur));
        esp_devices.port_name = blobmsg_get_string(devices[PORT_NAME]);
        esp_devices.vid = blobmsg_get_string(devices[VID]);
        esp_devices.pid = blobmsg_get_string(devices[PID]);
    }
}

int device_get(char *params)
{   
    uint32_t id = 0;
    if (ubus_lookup_id(ctx, "esp", &id)) {
        return -1;
    }
    struct blob_buf b = {0};
    blob_buf_init(&b, 0);
    if (!blobmsg_add_json_from_string(&b, params)) {
        blob_buf_free(&b);
        return -1;
    }
    if (ubus_invoke(ctx, id, "get", b.head, on_off_get_payload, output, 8000)){
        blob_buf_free(&b);
        return -1;
    }
    blob_buf_free(&b);
    return 0;
}
