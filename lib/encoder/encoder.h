//include guard
#ifndef ENCODER_H
#define ENCODER_H
//includes
#include "driver/pulse_cnt.h"
#include "esp_err.h"
#include "driver/gpio.h"
#include "driver/ledc.h"
#include "esp_log.h"

/* PCNT Limits */
#define PCNT_HIGH_LIMIT 1500
#define PCNT_LOW_LIMIT  -1500

/* Right encoder defines */
#define CHA_ENCODER_1R 18
#define CHA_ENCODER_2R 19

/* Left encoder defines */
#define CHA_ENCODER_1L 4
#define CHA_ENCODER_2L 14


/* Enum */
typedef enum {
ENC_LEFT = 0,
ENC_RIGHT = 1
} encoder_side_t;


/* Macro functions */

#define ENCODER_INPUT_A(NUM) NUM == (ENC_RIGHT) ? CHA_ENCODER_1R : CHA_ENCODER_1L
#define ENCODER_INPUT_B(NUM) NUM == (ENC_RIGHT) ? CHA_ENCODER_2R : CHA_ENCODER_2L

//Function prototypes
pcnt_unit_handle_t init_encoder(encoder_side_t cha_encoder);
float pulse_count(pcnt_unit_handle_t encoder);

// Tag for logging
const char *TAG_ENCODER = "Encoder";


#endif // ENCODER_H