#ifndef _HC_SR04_
#define _HC_SR04_
extern "C"{
#include "driver/gpio.h"
}
class HC_SR04 
{


    public:
    HC_SR04();
    HC_SR04(gpio_num_t triggerPin_e, gpio_num_t echoPin_e);
    ~HC_SR04();
    void startReadingDistance();
    float getDistance()
    {
        return m_distance;
    }

    private:
    gpio_num_t m_trigger_e;
    gpio_num_t m_echo_e;
    float m_distance; 
    void GetEcho(float& timer);
    //void WaitForPinState_v(gpio_num_t echoPin_e);




};

#endif // _HC_SR04_