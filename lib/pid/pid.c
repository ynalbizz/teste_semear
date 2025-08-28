#include "pid.h"

pid_ctrl_block_handle_t init_pid(int kp, int ki, int kd){
    pid_ctrl_config_t pid_config = {
        .init_param = {
            .kp = kp,
            .ki = ki,
            .kd = kd,
            .max_output = MAX_OUT,
            .min_output = -MAX_OUT,
            .max_integral = MAX_IN,
            .min_integral = -MAX_IN,
            .cal_type = PID_CAL_TYPE_POSITIONAL,
        }
    };
    pid_ctrl_block_handle_t pid = NULL;

    if (pid_new_control_block(&pid_config, &pid) != ESP_OK) {
        ESP_LOGE("PID", "Failed to create PID control block");
        return NULL;
    }
    
    return pid;
}   