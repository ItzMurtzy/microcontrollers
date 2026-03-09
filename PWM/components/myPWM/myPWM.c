#include <stdio.h>
#include "myPWM.h"
#include "driver/ledc.h"

static ledc_timer_config_t timer;
static ledc_channel_config_t channel;

void pwm_init(int gpio, int freq, int duty)
{
   
        timer.speed_mode = LEDC_HIGH_SPEED_MODE,
        timer.timer_num = LEDC_TIMER_0,
        timer.duty_resolution = LEDC_TIMER_10_BIT,
        timer.freq_hz = 5000,
        timer.clk_cfg = LEDC_AUTO_CLK,


    ledc_timer_config(&timer);

        channel.gpio_num = gpio,
        channel.speed_mode = LEDC_HIGH_SPEED_MODE,
        channel.channel = LEDC_CHANNEL_0,
        channel.timer_sel = LEDC_TIMER_0,
        channel.duty = duty,
        channel.hpoint = 0,

    ledc_channel_config(&channel);
}

void pwm_set_duty(int duty)
{
    ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0, duty);
    ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0);
}

void pwm_set_freq(int freq)
{
    timer.freq_hz = freq;
    ledc_timer_config(&timer);
}
