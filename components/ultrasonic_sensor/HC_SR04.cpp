#include "HC_SR04.h"
extern "C"
{
#include "driver/pcnt.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp32/rom/ets_sys.h"
#include "esp_clk.h"
}
#define clockCyclesPerMicrosecond() (esp_clk_cpu_freq() / 1000000L)
#define clockCyclesToMicroseconds(a) ((a) / clockCyclesPerMicrosecond())

HC_SR04::HC_SR04()
{
}
HC_SR04::~HC_SR04()
{
}
HC_SR04::HC_SR04(gpio_num_t triggerPin_e, gpio_num_t echoPin_e)
{
    this->m_echo_e = echoPin_e;
    this->m_trigger_e = triggerPin_e;
    this->m_distance = 0;
}

void HC_SR04::startReadingDistance()
{

    gpio_set_direction(m_trigger_e, GPIO_MODE_OUTPUT);
    gpio_set_direction(m_echo_e, GPIO_MODE_INPUT);
    gpio_set_level(m_trigger_e, 0);
    ets_delay_us(2);
    gpio_set_level(m_trigger_e, 1);
    ets_delay_us(10);
    gpio_set_level(m_trigger_e, 0);
    ets_delay_us(2);

    float timer = 0;
    GetEcho(timer);
    this->m_distance = (timer/2)/29.1;
  
}

void HC_SR04::GetEcho(float &timer)
{
    while(gpio_get_level(m_echo_e) == 0)
    {}
    const uint32_t start_cycle_count = xthal_get_ccount();
    while (gpio_get_level(m_echo_e) == 1)
    {}
    timer = xthal_get_ccount()-start_cycle_count;
    timer = clockCyclesToMicroseconds(timer);
}
