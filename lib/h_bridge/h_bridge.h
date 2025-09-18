//include guard
#ifndef H_BRIDGE_H
#define H_BRIDGE_H

//includes
#include "esp_err.h"
#include "driver/gpio.h"
#include "driver/ledc.h"
#include "esp_log.h"

// GPIOs of h-bridge for left motor
#define INPUT_RIGHT_1   GPIO_NUM_15
#define INPUT_RIGHT_2   GPIO_NUM_13
#define INPUT_LEFT_1    GPIO_NUM_25
#define INPUT_LEFT_2    GPIO_NUM_33
#define STANDBY        GPIO_NUM_32

// GPIOs for PWM outputs
#define LEDC_OUTPUT_RIGHT   GPIO_NUM_27
#define LEDC_OUTPUT_LEFT    GPIO_NUM_26

//Some Ledc definitions
#define LEDC_CHANNEL_LEFT   LEDC_CHANNEL_0
#define LEDC_CHANNEL_RIGHT  LEDC_CHANNEL_1
#define LEDC_TIMER          LEDC_TIMER_0
#define LEDC_MODE           LEDC_LOW_SPEED_MODE
#define LEDC_DUTY_RES      LEDC_TIMER_8_BIT // Set duty resolution to 8 bits
#define LEDC_FREQ_HZ       500                // Frequency in Hertz.

//Enum for motor side
typedef enum {
    LEFT,
    RIGHT
} motor_side_t;


/* Macro functions */
#define MOTOR_INPUT_1(MOTOR) ((MOTOR) == (LEFT) ? INPUT_LEFT_1 : INPUT_RIGHT_1)
#define MOTOR_INPUT_2(MOTOR) ((MOTOR) == (LEFT) ? INPUT_LEFT_2 : INPUT_RIGHT_2)
#define MOTOR_CHANNEL(MOTOR) ((MOTOR) == (LEFT) ? LEDC_CHANNEL_LEFT : LEDC_CHANNEL_RIGHT)

//Function prototypes
void init_h_bridge(void);
void init_gpio(motor_side_t motor);
void init_pwm(void);
esp_err_t _set_forward(motor_side_t motor);
esp_err_t _set_backward(motor_side_t motor);
esp_err_t set_speed(motor_side_t motor, uint8_t speed);
esp_err_t update_motor(motor_side_t motor, int u);

#endif // H_BRIDGE_H