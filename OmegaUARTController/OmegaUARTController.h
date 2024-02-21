#ifndef __OMEGA_UART_CONTROLLER_H__
#define __OMEGA_UART_CONTROLLER_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <driver/gpio.h>
#include <driver/uart.h>

    typedef enum
    {
        DISABLE = UART_PARITY_DISABLE,
        ODD = UART_PARITY_ODD,
        EVEN = UART_PARITY_EVEN,
    } UART_Parity;

    typedef enum
    {
        STOP_BITS_1 = UART_STOP_BITS_1,
        STOP_BITS_1_5 = UART_STOP_BITS_1_5,
        STOP_BITS_2 = UART_STOP_BITS_2,
    } UART_Stop_Bits;

    typedef struct
    {
        uart_port_t _m_uart_port;
        gpio_num_t _m_tx_pin;
        gpio_num_t _m_rx_pin;
        uint32_t _m_baudrate;
        UART_Parity _m_parity;
        UART_Stop_Bits _m_uart_stop_bits;
        uint64_t _m_timeout_ms;
        uart_config_t _m_uart_config;
        QueueHandle_t _m_uart_queue_handle;
        SemaphoreHandle_t _m_uart_semaphore_handle;
    } OmegaUARTController_t;

    void OmegaUARTController_reset_module(OmegaUARTController_t *);
    void OmegaUARTController_set_uart_port(OmegaUARTController_t *, uart_port_t);
    void OmegaUARTController_set_uart_pins(OmegaUARTController_t *, gpio_num_t, gpio_num_t);
    void OmegaUARTController_set_uart_baudrate(OmegaUARTController_t *, uint32_t);
    void OmegaUARTController_set_uart_parity(OmegaUARTController_t *, UART_Parity);
    void OmegaUARTController_set_uart_stop_bits(OmegaUARTController_t *, UART_Stop_Bits);
    void OmegaUARTController_reconfigure_baudrate(OmegaUARTController_t *, uint32_t, UART_Parity,UART_Stop_Bits);
    void OmegaUARTController_reconfigure_baudrate_only(OmegaUARTController_t *, uint32_t);
    void OmegaUARTController_start(OmegaUARTController_t *);
    size_t OmegaUARTController_polling_write(OmegaUARTController_t *, uint8_t *, size_t);
    size_t OmegaUARTController_polling_read(OmegaUARTController_t *, uint8_t *, size_t);
    void OmegaUARTController_flush_rx(OmegaUARTController_t *);
    void OmegaUARTController_flush_tx(OmegaUARTController_t *);

#ifdef __cplusplus
}
#endif

#endif