#ifndef __OMEGA_SPI_CONTROLLER_H__
#define __OMEGA_SPI_CONTROLLER_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>

#include <esp_log.h>
#include <driver/gpio.h>
#include <driver/spi_master.h>

    typedef struct
    {
        spi_device_handle_t _m_spi_device_handle;
        spi_host_device_t _m_spi_host_device;
        spi_bus_config_t _m_spi_bus_config;
        spi_device_interface_config_t _m_spi_device_interface_config;
        gpio_num_t _m_miso_pin;
        gpio_num_t _m_mosi_pin;
        gpio_num_t _m_sclk_pin;
        gpio_num_t _m_cs_pin;
        int _m_clock_speed_hz;
        uint8_t _m_spi_mode;
        transaction_cb_t _m_pre_transaction_cb;
        transaction_cb_t _m_post_transaction_cb;
        SemaphoreHandle_t _m_spi_semaphore_handle;
    } OmegaSPIController_t;
    void OmegaSPIController_reset_module(OmegaSPIController_t *);
    void OmegaSPIController_set_spi_port(OmegaSPIController_t *, spi_host_device_t);
    void OmegaSPIController_set_spi_mode(OmegaSPIController_t *, uint8_t);
    void OmegaSPIController_set_spi_pins(OmegaSPIController_t *, gpio_num_t, gpio_num_t, gpio_num_t, gpio_num_t);
    void OmegaSPIController_set_spi_clock_speed_hz(OmegaSPIController_t *, uint32_t);
    void OmegaSPIController_initialize(OmegaSPIController_t *);
    void OmegaSPIController_spi_write_byte(OmegaSPIController_t *, uint8_t *, size_t);
    void OmegaSPIController_spi_read_byte(OmegaSPIController_t *, uint8_t *, uint8_t *, size_t);
    uint8_t OmegaSPIController_spi_transfer(OmegaSPIController_t *, uint8_t);
    void OmegaSPIController_write(OmegaSPIController_t *, uint8_t *, size_t);
    void OmegaSPIController_read(OmegaSPIController_t *, uint8_t *, size_t);

    void _OmegaSPIController_pre_transfer_callback(spi_transaction_t *);
    void _OmegaSPIController_post_transfer_callback(spi_transaction_t *);

#ifdef __cplusplus
}
#endif

#endif