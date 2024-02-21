#ifndef __OMEGA_ADC_CONTROLLER_H__
#define __OMEGA_ADC_CONTROLLER_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>

#include <driver/gpio.h>
#include <driver/adc.h>
#include <esp_adc_cal.h>

    typedef enum
    {
        ADC_1 = 1,
        ADC_2
    } OmegaADCController_adc_port_t;

    typedef struct
    {
        OmegaADCController_adc_port_t _m_adc_port;
        adc_channel_t _m_adc_channel;
        adc_bits_width_t _m_adc_width;
        uint16_t _m_adc_reference_voltage;
        adc_atten_t _m_adc_atten;
        esp_adc_cal_characteristics_t *_m_adc_chars;
        esp_adc_cal_value_t _m_adc_calibration_value;
        SemaphoreHandle_t _m_adc_semaphore_handle;
    } OmegaADCController_t;

    void OmegaADCController_reset_module(OmegaADCController_t *);
    void OmegaADCController_set_adc_port(OmegaADCController_t *, OmegaADCController_adc_port_t);
    void OmegaADCController_set_adc_channel(OmegaADCController_t *, adc_channel_t);
    void OmegaADCController_set_adc_width(OmegaADCController_t *, adc_bits_width_t);
    void OmegaADCController_set_adc_reference_voltage(OmegaADCController_t *, uint16_t);
    void OmegaADCController_set_adc_channel_attenuation(OmegaADCController_t *, adc_atten_t);
    void OmegaADCController_set_adc_initialize(OmegaADCController_t *);
    void OmegaADCController_get_adc_reading_voltage(OmegaADCController_t *, uint16_t *, uint16_t *);
#ifdef __cplusplus
}
#endif

#endif