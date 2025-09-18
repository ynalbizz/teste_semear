//include Guard
#ifndef PID_H
#define PID_H

//includes
#include "pid_ctrl.h"
#include "encoder.h"
#include "h_bridge.h"
#include "esp_err.h"
#include "pid_ctrl.h"
#include "esp_err.h"
#include "driver/gpio.h"
#include "driver/ledc.h"
#include "esp_log.h"

//Some Macros
#define KC (3.141592653*2*(1000/DELAY))/1321//constant to convert pulse count to cm (depends on the wheel and encoder)
#define KC_TESTE 0.0475638

#define KP_R 1 
#define KI_R 0
#define KD_R 0
#define MAX_OUTPUT_R 1023 
#define MIN_OUTPUT_R -1023 
#define MAX_INTEGRAL_R 100000  //limita a range da soma dos erros (só importa se usar PID_CAL_TYPE_POSITIONAL)
#define MIN_INTEGRAL_R 0

#define KP_L 0.5
#define KI_L 0
#define KD_L 0
#define MAX_OUTPUT_L 1023
#define MIN_OUTPUT_L -1023
#define MAX_INTEGRAL_L 100000 
#define MIN_INTEGRAL_L 0

#define kp(SIDE) (SIDE == RIGHT)? KP_R : KP_L
#define ki(SIDE) (SIDE == RIGHT)? KI_R : KI_L
#define kd(SIDE) (SIDE == RIGHT)? KD_R : KD_L
#define max_output(SIDE) (SIDE == RIGHT)? MAX_OUTPUT_R : MAX_OUTPUT_L
#define min_output(SIDE) (SIDE == RIGHT)? MIN_OUTPUT_R : MIN_OUTPUT_L
#define max_integral(SIDE) (SIDE == RIGHT)? MAX_INTEGRAL_R : MAX_INTEGRAL_L
#define min_integral(SIDE) (SIDE == RIGHT)? MIN_INTEGRAL_R : MIN_INTEGRAL_L

pid_ctrl_block_handle_t init_pid(motor_side_t motor);
esp_err_t pid_apply(pid_ctrl_block_handle_t pid, float setpoint, pcnt_unit_handle_t pcnt, int *output);





#endif //PID_H