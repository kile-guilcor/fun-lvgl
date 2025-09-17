#include <zephyr/zbus/zbus.h>
#include "zbus_channel.h"

ZBUS_CHAN_DEFINE(sensor_chan,
        struct sensor_msg_t,
        NULL,
        NULL,
        ZBUS_OBSERVERS_EMPTY,
        ZBUS_MSG_INIT({0})
);