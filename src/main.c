//Librarys to use GPIO(General Purpose Input Output) on ESP32 [From Espressif Framework]
#include <math.h>
#include "pid.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

//Main function
void app_main() {
    //Initialize H-Bridge
    //init_h_bridge();
    

int meta, b = 0;
srandom(1234);
meta = (int)random();
int erro =(meta - b);
printf("Random: %d\n", meta);

//Initialize PID with Kp, Ki, Kd
pid_ctrl_block_handle_t pid = init_pid(1.0, 0.1, 0.01);

while (1)
{
    //Function to compute PID
    float output;
    pid_compute(pid, erro, &output);
    printf("Output: %f\n", output);


    vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

