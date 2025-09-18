#include "pid.h"

pid_ctrl_block_handle_t init_pid(motor_side_t motor){

    pid_ctrl_parameter_t pid_param = {
        .kp = kp(motor),
        .ki = ki(motor),
        .kd = kd(motor),
        .max_output = max_output(motor),
        .min_output = min_output(motor),
        .max_integral = max_integral(motor),
        .min_integral = min_integral(motor),
        .cal_type = PID_CAL_TYPE_INCREMENTAL,
    };

    pid_ctrl_config_t pid_config = {
        .init_param = pid_param
    };

    pid_ctrl_block_handle_t pid;

    ESP_ERROR_CHECK(pid_new_control_block(&pid_config, &pid)); //cria bloco pid e faz o update dos valores do pid_param
    
    return pid;
}
void limite_PWM(int *val){
    if(*val > 1023) *val = 1023;
    if(*val < -1023) *val = -1023;
}

esp_err_t pid_apply(pid_ctrl_block_handle_t pid, float setpoint, pcnt_unit_handle_t encoder, int *output){
    float pid_output = 0.0f;
    //float measurement = pulse_count(encoder)*KC; //leitura do encoder
    //float erro = setpoint - measurement; //calculo do erro
    float erro = setpoint/KC_TESTE - pulse_count(encoder); //calculo do erro
    
    ESP_ERROR_CHECK(pid_compute(pid, erro, &pid_output)); //calculo do pid
    //ESP_LOGI("DEBUGING","PID_OUT:  %f ",pid_output);
    *output += (int)pid_output; //conversao do output do pid para int
    limite_PWM(output); //limita o valor do pwm
    return ESP_OK;
}

