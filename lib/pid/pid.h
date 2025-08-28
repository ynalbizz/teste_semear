//include Guard

//includes
#include "pid_ctrl.h"
#include "esp_err.h"
#include "driver/gpio.h"
#include "driver/ledc.h"
#include "esp_log.h"

//Some Macros
#define MAX_IN 99999
#define MAX_OUT 99999

pid_ctrl_block_handle_t init_pid(int kp, int ki, int kd);