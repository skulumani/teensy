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
typedef struct _AHRS_IMUMeasurement {
    float accel_meas[3];
    float accel_bias[3];
    float gyro_meas[3];
    float gyro_bias[3];
    float mag_meas[3];
    float mag_bias[3];
    float temp_meas;
} AHRS_IMUMeasurement;

typedef struct _AHRS_SensorMeasurement {
    float meas[3];
    float bias[3];
} AHRS_SensorMeasurement;


/* Initializer values for message structs */
#define AHRS_SensorMeasurement_init_default      {{0, 0, 0}, {0, 0, 0}}
#define AHRS_IMUMeasurement_init_default         {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, 0}
#define AHRS_SensorMeasurement_init_zero         {{0, 0, 0}, {0, 0, 0}}
#define AHRS_IMUMeasurement_init_zero            {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, 0}

/* Field tags (for use in manual encoding/decoding) */
#define AHRS_IMUMeasurement_accel_meas_tag       1
#define AHRS_IMUMeasurement_accel_bias_tag       2
#define AHRS_IMUMeasurement_gyro_meas_tag        3
#define AHRS_IMUMeasurement_gyro_bias_tag        4
#define AHRS_IMUMeasurement_mag_meas_tag         5
#define AHRS_IMUMeasurement_mag_bias_tag         6
#define AHRS_IMUMeasurement_temp_meas_tag        7
#define AHRS_SensorMeasurement_meas_tag          1
#define AHRS_SensorMeasurement_bias_tag          2

/* Struct field encoding specification for nanopb */
#define AHRS_SensorMeasurement_FIELDLIST(X, a) \
X(a, STATIC,   FIXARRAY, FLOAT,    meas,              1) \
X(a, STATIC,   FIXARRAY, FLOAT,    bias,              2)
#define AHRS_SensorMeasurement_CALLBACK NULL
#define AHRS_SensorMeasurement_DEFAULT NULL

#define AHRS_IMUMeasurement_FIELDLIST(X, a) \
X(a, STATIC,   FIXARRAY, FLOAT,    accel_meas,        1) \
X(a, STATIC,   FIXARRAY, FLOAT,    accel_bias,        2) \
X(a, STATIC,   FIXARRAY, FLOAT,    gyro_meas,         3) \
X(a, STATIC,   FIXARRAY, FLOAT,    gyro_bias,         4) \
X(a, STATIC,   FIXARRAY, FLOAT,    mag_meas,          5) \
X(a, STATIC,   FIXARRAY, FLOAT,    mag_bias,          6) \
X(a, STATIC,   SINGULAR, FLOAT,    temp_meas,         7)
#define AHRS_IMUMeasurement_CALLBACK NULL
#define AHRS_IMUMeasurement_DEFAULT NULL

extern const pb_msgdesc_t AHRS_SensorMeasurement_msg;
extern const pb_msgdesc_t AHRS_IMUMeasurement_msg;

/* Defines for backwards compatibility with code written before nanopb-0.4.0 */
#define AHRS_SensorMeasurement_fields &AHRS_SensorMeasurement_msg
#define AHRS_IMUMeasurement_fields &AHRS_IMUMeasurement_msg

/* Maximum encoded size of messages (where known) */
#define AHRS_SensorMeasurement_size              30
#define AHRS_IMUMeasurement_size                 95

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
