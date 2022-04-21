#include <Arduino.h>
#include "GpioManager.h"

#define uS_TO_S_FACTOR 1000000
#define TIME_TO_SLEEP  5

GpioManager::GpioManager()
{

}

void GpioManager::start_esp_sleep()
{
    esp_sleep_enable_timer_wakeup( TIME_TO_SLEEP * uS_TO_S_FACTOR );
    esp_sleep_enable_ext0_wakeup( GPIO_NUM_10, HIGH );

    Serial.flush();
    esp_light_sleep_start();
}