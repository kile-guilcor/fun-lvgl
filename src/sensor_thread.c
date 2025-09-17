#include "zbus_channel.h"
#include <zephyr/kernel.h>
#include <zephyr/zbus/zbus.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(sensor_thread, LOG_LEVEL_INF);

ZBUS_CHAN_DECLARE(sensor_chan);

static const char* get_sensor_type_name(sensor_type_t type) {
    switch (type) {
        case SENSOR_TYPE_TEMPERATURE: return "Temperature";
        case SENSOR_TYPE_PRESSURE: return "Pressure";
        case SENSOR_TYPE_HUMIDITY: return "Humidity";
        case SENSOR_TYPE_ACCELERATION: return "Acceleration";
        case SENSOR_TYPE_GYROSCOPE: return "Gyroscope";
        default: return "Unknown";
    }
}

static void generate_sensor_data(struct sensor_msg_t *msg, int iteration) {
    // Cycle through sensor types       
    msg->sensor_type = (sensor_type_t)(iteration % 5);
    msg->channel = iteration % 3; // Assume 3 channels per sensor type

    // Generate dummy data based on sensor type
    switch (msg->sensor_type) {
        case SENSOR_TYPE_TEMPERATURE:
            msg->data = 20.0f + (iteration % 10); // 20.0 to 29.0
            break;
        case SENSOR_TYPE_PRESSURE:
            msg->data = 1000.0f + (iteration % 50); // 1000.0 to 1049.0
            break;
        case SENSOR_TYPE_HUMIDITY:
            msg->data = 30.0f + (iteration % 70); // 30.0 to 99.0
            break;
        case SENSOR_TYPE_ACCELERATION:
            msg->data = (float)(iteration % 16) - 8.0f; // -8.0 to +7.0
            break;
        case SENSOR_TYPE_GYROSCOPE:
            msg->data = (float)(iteration % 360); // 0 to 359 degrees
            break;
        default:
            msg->data = 0.0f;
            break;
    }
}

void sensor_publisher_thread(void *arg1, void *arg2, void *arg3) {
    ARG_UNUSED(arg1);
    ARG_UNUSED(arg2);
    ARG_UNUSED(arg3);
    
    struct sensor_msg_t msg;
    int iteration = 0;
    int ret;
    
    LOG_INF("Sensor publisher thread started");
    
    while (1) {
        generate_sensor_data(&msg, iteration);
        
        // Publish the message via Zbus
        ret = zbus_chan_pub(&sensor_chan, &msg, K_MSEC(100));
        if (ret < 0) {
            LOG_ERR("Failed to publish sensor message: %d", ret);
        } else {
            LOG_INF("Published: %s sensor, channel %d, data: %.2f",
                    get_sensor_type_name(msg.sensor_type),
                    msg.channel,
                    (double)msg.data);
        }
        
        iteration++;
        
        k_sleep(K_SECONDS(2));
    }
}

K_THREAD_DEFINE(sensor_publisher_thread_id, 512, sensor_publisher_thread, NULL, NULL, NULL, 3, 0, 0);
