#include "encoder.h"

pcnt_unit_handle_t init_encoder(encoder_side_t cha_encoder){ 

    //allocate pcnt unit handle
    pcnt_unit_handle_t selected_encoder = NULL;

    //pcnt unit configuration
    //ESP_LOGI(TAG_ENCODER, "Install pcnt unit");
    pcnt_unit_config_t unit_config = {
        .high_limit = PCNT_HIGH_LIMIT,
        .low_limit = PCNT_LOW_LIMIT,
    };

    //unit "Creation"
    ESP_ERROR_CHECK(pcnt_new_unit(&unit_config, &selected_encoder));

    //glitch filter configuration
    //ESP_LOGI(TAG_ENCODER, "Set glitch filter");
    pcnt_glitch_filter_config_t filter_config = {
        .max_glitch_ns = 1000,
    };
    //Setting filter on unit
    ESP_ERROR_CHECK(pcnt_unit_set_glitch_filter(selected_encoder, &filter_config));

    //pcnt channel configuration
    //ESP_LOGI(TAG_ENCODER, "Install pcnt channels");
    pcnt_chan_config_t chan_a_config = {
        .edge_gpio_num = ENCODER_INPUT_A(cha_encoder),
        .level_gpio_num = ENCODER_INPUT_B(cha_encoder),
    };

    //allocate and assign pcnt channel handle
    pcnt_channel_handle_t pcnt_chan_a = NULL;
    ESP_ERROR_CHECK(pcnt_new_channel(selected_encoder, &chan_a_config, &pcnt_chan_a));

    //pcnt channel configuration(not used in this case)
    pcnt_chan_config_t chan_b_config = {
        .edge_gpio_num = ENCODER_INPUT_B(cha_encoder),
        .level_gpio_num = ENCODER_INPUT_A(cha_encoder),
    };

    //allocate and assign pcnt channel handle
    pcnt_channel_handle_t pcnt_chan_b = NULL;
    ESP_ERROR_CHECK(pcnt_new_channel(selected_encoder, &chan_b_config, &pcnt_chan_b));

    //set edge and level actions for pcnt channels
    //ESP_LOGI(TAG_ENCODER, "Set edge and level actions for pcnt channels");
    ESP_ERROR_CHECK(pcnt_channel_set_edge_action(pcnt_chan_a, PCNT_CHANNEL_EDGE_ACTION_DECREASE, PCNT_CHANNEL_EDGE_ACTION_INCREASE));
    ESP_ERROR_CHECK(pcnt_channel_set_level_action(pcnt_chan_a, PCNT_CHANNEL_LEVEL_ACTION_KEEP, PCNT_CHANNEL_LEVEL_ACTION_INVERSE));
    ESP_ERROR_CHECK(pcnt_channel_set_edge_action(pcnt_chan_b, PCNT_CHANNEL_EDGE_ACTION_INCREASE, PCNT_CHANNEL_EDGE_ACTION_DECREASE));
    ESP_ERROR_CHECK(pcnt_channel_set_level_action(pcnt_chan_b, PCNT_CHANNEL_LEVEL_ACTION_KEEP, PCNT_CHANNEL_LEVEL_ACTION_INVERSE));

    //enable, clear and start pcnt unit
    //ESP_LOGI(TAG_ENCODER, "Enable pcnt unit");
    ESP_ERROR_CHECK(pcnt_unit_enable(selected_encoder));
    
    //ESP_LOGI(TAG_ENCODER, "Clear pcnt unit");
    ESP_ERROR_CHECK(pcnt_unit_clear_count(selected_encoder));

    //ESP_LOGI(TAG_ENCODER, "Start pcnt unit");
    ESP_ERROR_CHECK(pcnt_unit_start(selected_encoder));

    //return the selected encoder unit handle
    return selected_encoder;
}

// Function to get the pulse count and reset it
float pulse_count(pcnt_unit_handle_t encoder){
    pcnt_unit_clear_count(encoder);
    vTaskDelay(100 / portTICK_PERIOD_MS); // Small delay to ensure accurate reading
    
    int pulse_count = 0;
    ESP_ERROR_CHECK(pcnt_unit_get_count(encoder, &pulse_count));
    ESP_LOGI("ENCODER", "Pulse count: %d", pulse_count);
    
    return pulse_count;
}