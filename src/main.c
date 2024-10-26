#include <signal.h>
#include "tuya.h"
#include "utilities.h"

int main(int argc, char **argv) {
    tuya_mqtt_context_t client_instance;
    tuya_mqtt_context_t *client = &client_instance;
    set_signal_context(client);   
    signal(SIGINT, handle_signal);
    signal(SIGCONT, handle_signal);
    signal(SIGSEGV, handle_signal);
    signal(SIGTERM, handle_signal);
    signal(SIGCHLD, handle_signal);
    signal(SIGHUP, handle_signal);
    uloop_init();
    ctx = ubus_ctx();
    if (ctx == NULL)
        return -1;
    if (load_arguments(argc, argv) != 0){
        ubus_free(ctx);
        return -1;
    }
    if (connect_init(client, arguments.device_id, arguments.device_secret) != 0){
        ubus_free(ctx);
        return 1;
    }                                           
    for (;;){   
        if (tuya_mqtt_loop(client) != 0)
            break;
    }
    disconnect_deinit(client);
    ubus_free(ctx);
    uloop_done();
    return 0;
}
