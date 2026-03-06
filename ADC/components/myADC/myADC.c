#include <stdlib.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/adc.h"
#include "esp_adc_cal.h"

#include "myADC.h"

static esp_adc_cal_characteristics_t *adc_chars;
static adc1_channel_t active_channel;

void adc_component_init(adc1_channel_t channel)
{
    active_channel = channel;

    adc1_config_width(ADC_WIDTH_BIT_12);
    adc1_config_channel_atten(active_channel, ADC_ATTEN_DB_12);

    adc_chars = calloc(1, sizeof(esp_adc_cal_characteristics_t));

    esp_adc_cal_characterize(
        ADC_UNIT_1,
        ADC_ATTEN_DB_12,
        ADC_WIDTH_BIT_12,
        1100,
        adc_chars
    );
}

int adc_component_read_mv(void)
{
    int raw = adc1_get_raw(active_channel);
    return esp_adc_cal_raw_to_voltage(raw, adc_chars);
}
