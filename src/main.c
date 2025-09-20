//Librarys to use GPIO(General Purpose Input Output) on ESP32 [From Espressif Framework]
#include <math.h>
#include "pid.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"


// Add function prototype if not present in pid.h
#include "freertos/task.h"
#include "h_bridge.h"
#include "encoder.h"
#include "cominicacao.h"

//Estrutura com os Parametros que a Thread PID usa
struct{
    pid_ctrl_block_handle_t pid;
    pcnt_unit_handle_t pcnt;
    float target;
    motor_side_t side;
}typedef pidTask_params;

static pidTask_params L_pid_task_params;

//Define a Thread do PID
void pid_task(void *pVparams){
    while (1)
    {
        pidTask_params *params = (pidTask_params*)pVparams;
        
        static int output = 0;
        pid_apply(params->pid,params->target, params->pcnt, &output);
        update_motor(params->side, output);
        
    }
}

//Main function
void app_main() {
    init_com();
    //Initialize H-Bridge
    init_h_bridge(LEFT);
    init_h_bridge(RIGHT);
    //Initialize Encoder
    pcnt_unit_handle_t pcnt = init_encoder(ENC_LEFT);
    //Initialize PID
    pid_ctrl_block_handle_t pid = init_pid(LEFT);
    //Main loop
    L_pid_task_params.pid = pid;
    L_pid_task_params.pcnt = pcnt;
    L_pid_task_params.target = 0;
    L_pid_task_params.side = LEFT;

    //Inicia a Thread do PID
    xTaskCreate(
        pid_task,
        "PID Control Task",
        4096,
        &L_pid_task_params,
        10,
        NULL
    );

    char data[1024];
    while(1){
        //Recebe Novo target(Float) da serial e atualiza o target no pid
        read_data(data);
        L_pid_task_params.target = atof(data);
        ESP_LOGI("Target","%.3f",L_pid_task_params.target);
        vTaskDelay(500/portTICK_PERIOD_MS);
    }
}

