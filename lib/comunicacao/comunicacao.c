#include "cominicacao.h"


void init_com(){
    //Instalando O Driver UART
    QueueHandle_t queue_handle;
    ESP_ERROR_CHECK(uart_driver_install(PORT_NUM,BUFFER_SIZE,BUFFER_SIZE,10,&queue_handle,0));
    
    //configurando Parametros da Comunicação UART
    uart_config_t uart_config = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE
    };
    ESP_ERROR_CHECK(uart_param_config(PORT_NUM, &uart_config));

    //Setando os pinos da comunicação
    ESP_ERROR_CHECK(uart_set_pin(PORT_NUM,TX_PIN,RX_PIN,UART_PIN_NO_CHANGE,UART_PIN_NO_CHANGE));
}

void send_data(char* string){
uart_write_bytes(PORT_NUM, string, strlen(string));
}

// Read data from UART.
void read_data(){
    // Read data from UART.
    uint8_t data[BUFFER_SIZE];
    int len = 0;
    len = uart_read_bytes(PORT_NUM, data, BUFFER_SIZE-1, 100 / portTICK_PERIOD_MS);
    if (len > 0) {
        data[len] = '\0';  // Garante que o buffer de dados seja uma string válida
        // Converte os dados para string e separa em dois valores
        char *token = strtok((char *)data, ",");  // Primeiro valor antes da vírgula
        if (token != NULL) {
           float motor_1 = atof(token);  // Converte para float
        }

        token = strtok(NULL, ",");  // Segundo valor depois da vírgula
        if (token != NULL) {
           float motor_2 = atof(token);  // Converte para float
        }
    }
}