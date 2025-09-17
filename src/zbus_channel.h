

typedef enum {
    SENSOR_TYPE_TEMPERATURE,
    SENSOR_TYPE_PRESSURE,
    SENSOR_TYPE_HUMIDITY,
    SENSOR_TYPE_ACCELERATION,
    SENSOR_TYPE_GYROSCOPE,
} sensor_type_t;

struct sensor_msg_t {
    float data;
    sensor_type_t sensor_type;
    int channel;
};