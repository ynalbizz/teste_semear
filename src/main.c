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
    init_h_bridge(LEFT);
    init_h_bridge(RIGHT);
    //Initialize Encoder
    pcnt_unit_handle_t pcnt = init_encoder(ENC_LEFT);
    //Initialize PID
    pid_ctrl_block_handle_t pid = init_pid(LEFT);
    int output = 0;
    //Main loop
    while (1)
    {
        //ESP_LOGI("MAIN", "Output: %d", output);
        //Apply PID control
        //pid_apply(pid,6.283185, pcnt, &output);
        //Set motor speed
        //update_motor(LEFT, output);
        update_motor(LEFT, 256);
        //Log output
        //update_motor(LEFT,1023);
        //pulse_count(pcnt);
        // Parte da comunicação ta feita (Tanto o .h quanto o .c) so n implementei aqui :P
    }
    
}

