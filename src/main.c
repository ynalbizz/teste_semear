//Librarys to use GPIO(General Purpose Input Output) on ESP32 [From Espressif Framework]
#include <math.h>
#include "pid.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"

// Add function prototype if not present in pid.h
#include "freertos/task.h"
#include "h_bridge.h"
#include "encoder.h"

//Main function
void app_main() {
    //Initialize H-Bridge
    init_h_bridge();
    //Initialize Encoder
    pcnt_unit_handle_t pcnt = init_encoder(ENC_LEFT);
    //Initialize PID
    pid_ctrl_block_handle_t pid = init_pid(LEFT);
    int output = 0;
    //Main loop
    while (1)
    {
        //Apply PID control
        pid_apply(pid, 25.0f, pcnt, &output);
        //Set motor speed
        update_motor(LEFT, output);
        //Log output
        ESP_LOGI("MAIN", "Output: %d", output);
    }
    
}

