#include "zbus_channel.h"
#include <zephyr/zbus/zbus.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(display_thread, LOG_LEVEL_INF);

ZBUS_CHAN_DECLARE(sensor_chan);

// Define a subscriber observer
ZBUS_SUBSCRIBER_DEFINE(sensor_data_subscriber, 4);

// Add the subscriber to the sensor channel
ZBUS_CHAN_ADD_OBS(sensor_chan, sensor_data_subscriber, 0);

void subscriber_task(void)
{
    const struct zbus_channel *chan;

    while (1) {
        if (!zbus_sub_wait(&sensor_data_subscriber, &chan, K_FOREVER)) {
            if (chan == &sensor_chan) {
                struct sensor_msg_t sensor_msg;
                if (zbus_chan_read(chan, &sensor_msg, K_MSEC(100)) == 0) {
                    LOG_INF("From subscriber -> Sensor type=%d, channel=%d, data=%.2f",
                            sensor_msg.sensor_type, sensor_msg.channel, (double)sensor_msg.data);
                }
            }
        }
    }
}

K_THREAD_DEFINE(subscriber_task_id, 512, subscriber_task, NULL, NULL, NULL, 3, 0, 0);