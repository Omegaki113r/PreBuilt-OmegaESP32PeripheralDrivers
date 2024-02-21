#ifndef __OMEGA_I2C_CONTROLLER_H__
#define __OMEGA_I2C_CONTROLLER_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <driver/gpio.h>
#include <driver/i2c.h>

    typedef struct
    {
        i2c_port_t _m_i2c_port;
        i2c_mode_t _m_i2c_mode;
        gpio_num_t _m_scl_pin;
        gpio_num_t _m_sda_pin;
        uint32_t _m_clock;
        i2c_config_t _m_i2c_config;
        SemaphoreHandle_t _m_i2c_semaphore_handle;
    } OmegaI2CController_t;

    void OmegaI2CController_reset_module(OmegaI2CController_t *);
    void OmegaI2CController_set_i2c_port(OmegaI2CController_t *, i2c_port_t);
    void OmegaI2CController_set_i2c_mode(OmegaI2CController_t *, i2c_mode_t);
    void OmegaI2CController_set_i2c_pins(OmegaI2CController_t *, gpio_num_t, gpio_num_t);
    void OmegaI2CController_set_i2c_clock_speed_hz(OmegaI2CController_t *, uint32_t);
    void OmegaI2CController_start(OmegaI2CController_t *);
    void OmegaI2CController_write_register(OmegaI2CController_t *, uint8_t, uint8_t, uint8_t *, size_t);
    void OmegaI2CController_read_register(OmegaI2CController_t *, uint8_t, uint8_t, uint8_t *, size_t);

    void OmegaI2CController_scan_i2c_bus(OmegaI2CController_t *);

#ifdef __cplusplus
}
#endif

#endif