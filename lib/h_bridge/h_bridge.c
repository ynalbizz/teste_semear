#include "h_bridge.h"

void init_gpio(motor_side_t motor)
{
    if(motor == LEFT){
        gpio_set_direction(INPUT_LEFT_1, GPIO_MODE_OUTPUT);
        gpio_set_direction(INPUT_LEFT_2, GPIO_MODE_OUTPUT);
        gpio_set_direction(LEDC_OUTPUT_LEFT, GPIO_MODE_OUTPUT);
    }
    
    if(motor == RIGHT){
        gpio_set_direction(INPUT_RIGHT_1, GPIO_MODE_OUTPUT);
        gpio_set_direction(INPUT_RIGHT_2, GPIO_MODE_OUTPUT);
        gpio_set_direction(LEDC_OUTPUT_RIGHT, GPIO_MODE_OUTPUT);
        
    }
    gpio_set_direction(STANDBY, GPIO_MODE_OUTPUT);
    gpio_set_level(STANDBY, 1); // Enable the H-Bridge
}
void init_pwm(motor_side_t motor)
{
    /*Verificar Problemas De Redefinição em Caso de Modularização de Código
    "Se eu chamar essa função mais de uma vez, o que acontecer? ela vai ferrar com o timer?
    ... Valeria pena iniciar o Timer do PWM primerio dps os canais?"
    */ 

    // Configuração do timer do LEDC
    static ledc_timer_config_t ledc_timer = {
        .speed_mode = LEDC_MODE,
        .timer_num = LEDC_TIMER,
        .duty_resolution = LEDC_DUTY_RES,
        .freq_hz = LEDC_FREQ_HZ,
        .clk_cfg = LEDC_AUTO_CLK
    };
    ledc_timer_config(&ledc_timer);

    // Configuração dos canais do LEDC
    if(motor == LEFT){
        ledc_channel_config_t ledc_left_channel = {
            .speed_mode = LEDC_MODE,
            .channel = LEDC_CHANNEL_LEFT,
            .timer_sel = LEDC_TIMER,
            .intr_type = LEDC_INTR_DISABLE,
            .gpio_num = LEDC_OUTPUT_LEFT,
            .duty = 0,  // Set duty to 0%
            .hpoint = 0,
        };
        ledc_channel_config(&ledc_left_channel);
    }

    if(motor == RIGHT){
        // Canal para o motor direito
        ledc_channel_config_t ledc_right_channel = {
            .speed_mode = LEDC_MODE,
            .channel = LEDC_CHANNEL_RIGHT,
            .timer_sel = LEDC_TIMER,
            .intr_type = LEDC_INTR_DISABLE,
            .gpio_num = LEDC_OUTPUT_RIGHT,
            .duty = 0,  // Set duty to 0%
            .hpoint = 0
        };
        ledc_channel_config(&ledc_right_channel);
    }
}

void init_h_bridge(motor_side_t motor)
{
    init_gpio(motor);
    init_pwm(motor);
}

esp_err_t _set_forward(motor_side_t motor)
{
    // Definir pinos para direção 'forward'
    gpio_set_level(MOTOR_INPUT_1(motor), 1);
    gpio_set_level(MOTOR_INPUT_2(motor), 0);
    return ESP_OK;
}

esp_err_t _set_backward(motor_side_t motor)
{
    // Definir pinos para direção 'backward'
    gpio_set_level(MOTOR_INPUT_1(motor), 0);
    gpio_set_level(MOTOR_INPUT_2(motor), 1);
    return ESP_OK;
}


esp_err_t update_motor(motor_side_t motor, int u)
{

    if(u < 0) {
        _set_forward(motor);
    } else if (u > 0) {
        _set_backward(motor);
    }

    // Set PWM duty cycle
    ledc_set_duty(LEDC_MODE, MOTOR_CHANNEL(motor), abs(u));
    ledc_update_duty(LEDC_MODE, MOTOR_CHANNEL(motor));
    return ESP_OK;
}