/* Automatically generated nanopb header */
/* Generated by nanopb-0.4.1 */

#ifndef PB_AHRS_AHRS_PB_H_INCLUDED
#define PB_AHRS_AHRS_PB_H_INCLUDED
#include <pb.h>

#if PB_PROTO_HEADER_VERSION != 40
#error Regenerate this file with the current version of nanopb generator.
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* Struct definitions */
typedef struct _AHRS_SensorBias {
    float x;
    float y;
    float z;
} AHRS_SensorBias;

typedef struct _AHRS_SensorMeasurement {
    float x;
    float y;
    float z;
} AHRS_SensorMeasurement;

typedef struct _AHRS_IMUMeasurement {
    bool has_accel;
    AHRS_SensorMeasurement accel;
    bool has_gyro;
    AHRS_SensorMeasurement gyro;
    bool has_mag;
    AHRS_SensorMeasurement mag;
    bool has_accel_bias;
    AHRS_SensorBias accel_bias;
    bool has_gyro_bias;
    AHRS_SensorBias gyro_bias;
    bool has_mag_bias;
    AHRS_SensorBias mag_bias;
    float temp;
    int32_t dt;
} AHRS_IMUMeasurement;


/* Initializer values for message structs */
#define AHRS_SensorMeasurement_init_default      {0, 0, 0}
#define AHRS_SensorBias_init_default             {0, 0, 0}
#define AHRS_IMUMeasurement_init_default         {false, AHRS_SensorMeasurement_init_default, false, AHRS_SensorMeasurement_init_default, false, AHRS_SensorMeasurement_init_default, false, AHRS_SensorBias_init_default, false, AHRS_SensorBias_init_default, false, AHRS_SensorBias_init_default, 0, 0}
#define AHRS_SensorMeasurement_init_zero         {0, 0, 0}
#define AHRS_SensorBias_init_zero                {0, 0, 0}
#define AHRS_IMUMeasurement_init_zero            {false, AHRS_SensorMeasurement_init_zero, false, AHRS_SensorMeasurement_init_zero, false, AHRS_SensorMeasurement_init_zero, false, AHRS_SensorBias_init_zero, false, AHRS_SensorBias_init_zero, false, AHRS_SensorBias_init_zero, 0, 0}

/* Field tags (for use in manual encoding/decoding) */
#define AHRS_SensorBias_x_tag                    1
#define AHRS_SensorBias_y_tag                    2
#define AHRS_SensorBias_z_tag                    3
#define AHRS_SensorMeasurement_x_tag             1
#define AHRS_SensorMeasurement_y_tag             2
#define AHRS_SensorMeasurement_z_tag             3
#define AHRS_IMUMeasurement_accel_tag            1
#define AHRS_IMUMeasurement_gyro_tag             2
#define AHRS_IMUMeasurement_mag_tag              3
#define AHRS_IMUMeasurement_accel_bias_tag       4
#define AHRS_IMUMeasurement_gyro_bias_tag        5
#define AHRS_IMUMeasurement_mag_bias_tag         6
#define AHRS_IMUMeasurement_temp_tag             7
#define AHRS_IMUMeasurement_dt_tag               8

/* Struct field encoding specification for nanopb */
#define AHRS_SensorMeasurement_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, FLOAT,    x,                 1) \
X(a, STATIC,   SINGULAR, FLOAT,    y,                 2) \
X(a, STATIC,   SINGULAR, FLOAT,    z,                 3)
#define AHRS_SensorMeasurement_CALLBACK NULL
#define AHRS_SensorMeasurement_DEFAULT NULL

#define AHRS_SensorBias_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, FLOAT,    x,                 1) \
X(a, STATIC,   SINGULAR, FLOAT,    y,                 2) \
X(a, STATIC,   SINGULAR, FLOAT,    z,                 3)
#define AHRS_SensorBias_CALLBACK NULL
#define AHRS_SensorBias_DEFAULT NULL

#define AHRS_IMUMeasurement_FIELDLIST(X, a) \
X(a, STATIC,   OPTIONAL, MESSAGE,  accel,             1) \
X(a, STATIC,   OPTIONAL, MESSAGE,  gyro,              2) \
X(a, STATIC,   OPTIONAL, MESSAGE,  mag,               3) \
X(a, STATIC,   OPTIONAL, MESSAGE,  accel_bias,        4) \
X(a, STATIC,   OPTIONAL, MESSAGE,  gyro_bias,         5) \
X(a, STATIC,   OPTIONAL, MESSAGE,  mag_bias,          6) \
X(a, STATIC,   SINGULAR, FLOAT,    temp,              7) \
X(a, STATIC,   SINGULAR, INT32,    dt,                8)
#define AHRS_IMUMeasurement_CALLBACK NULL
#define AHRS_IMUMeasurement_DEFAULT NULL
#define AHRS_IMUMeasurement_accel_MSGTYPE AHRS_SensorMeasurement
#define AHRS_IMUMeasurement_gyro_MSGTYPE AHRS_SensorMeasurement
#define AHRS_IMUMeasurement_mag_MSGTYPE AHRS_SensorMeasurement
#define AHRS_IMUMeasurement_accel_bias_MSGTYPE AHRS_SensorBias
#define AHRS_IMUMeasurement_gyro_bias_MSGTYPE AHRS_SensorBias
#define AHRS_IMUMeasurement_mag_bias_MSGTYPE AHRS_SensorBias

extern const pb_msgdesc_t AHRS_SensorMeasurement_msg;
extern const pb_msgdesc_t AHRS_SensorBias_msg;
extern const pb_msgdesc_t AHRS_IMUMeasurement_msg;

/* Defines for backwards compatibility with code written before nanopb-0.4.0 */
#define AHRS_SensorMeasurement_fields &AHRS_SensorMeasurement_msg
#define AHRS_SensorBias_fields &AHRS_SensorBias_msg
#define AHRS_IMUMeasurement_fields &AHRS_IMUMeasurement_msg

/* Maximum encoded size of messages (where known) */
#define AHRS_SensorMeasurement_size              15
#define AHRS_SensorBias_size                     15
#define AHRS_IMUMeasurement_size                 118

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
