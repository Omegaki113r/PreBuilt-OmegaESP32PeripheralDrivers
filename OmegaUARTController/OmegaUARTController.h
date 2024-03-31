/**
 * @file OmegaUARTController.h
 * @author Omegaki113r
 * @date Wednesday, 21st February 2024 4:43:55 pm
 * @copyright Copyright 2024 - 2024 0m3g4ki113r, Xtronic
 * */
/*
 * Project: OmegaESP32PeripheralDrivers
 * File Name: OmegaUARTController.h
 * File Created: Wednesday, 21st February 2024 4:43:55 pm
 * Author: Omegaki113r (omegaki113r@gmail.com)
 * -----
 * Last Modified: Saturday, 30th March 2024 3:22:07 pm
 * Modified By: 0m3g4ki113r (omegaki113r@gmail.com)
 * -----
 * Copyright 2024 - 2024 0m3g4ki113r, Xtronic
 * -----
 * HISTORY:
 * Date      	By	Comments
 * ----------	---	---------------------------------------------------------
 *
 * 30-03-2024	0m3g4	following functions were added,
 *                              OmegaUARTController_default_init
 *                              OmegaUARTController_set_data_received_callback
 *                      following data structures were added,
 *                              OmegaUARTDataReceivedCallback
 */

#ifndef __OMEGA_UART_CONTROLLER_H__
#define __OMEGA_UART_CONTROLLER_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include <driver/gpio.h>
#include <driver/uart.h>

    typedef enum
    {
        UARTCTRL_SUCCESS,
        UARTSYSCTRL_NOT_INIT,
        UARTCTRL_INVALID_PARAMETERS,
        UARTCTRL_FAILED,
    } UARTControllerStatus;

    /// @brief Abstracted enumaration of databits for ease of use
    typedef enum
    {
        /// @brief enumaration of 5 data bits
        DATA_BITS_5 = UART_DATA_5_BITS,
        /// @brief enumaration of 6 data bits
        DATA_BITS_6 = UART_DATA_6_BITS,
        /// @brief enumaration of 7 data bits
        DATA_BITS_7 = UART_DATA_7_BITS,
        /// @brief enumaration of 8 data bits
        DATA_BITS_8 = UART_DATA_8_BITS,
    } UART_Data_Bits;

    /// @brief Abstracted enumaration of parity modes for ease of use
    typedef enum
    {
        /// @brief enumaration of Disable parity on UART bus
        DISABLE = UART_PARITY_DISABLE,
        /// @brief enumaration of ODD parity on UART bus
        ODD = UART_PARITY_ODD,
        /// @brief enumaration of EVEN parity on UART bus
        EVEN = UART_PARITY_EVEN,
    } UART_Parity;

    /// @brief Abstracted enumaration of stop bits for ease of use
    typedef enum
    {
        /// @brief enumaration of 1 stop bits
        STOP_BITS_1 = UART_STOP_BITS_1,
        /// @brief enumaration of 1.5 stop bits
        STOP_BITS_1_5 = UART_STOP_BITS_1_5,
        /// @brief enumaration of 2 stop bits
        STOP_BITS_2 = UART_STOP_BITS_2,
    } UART_Stop_Bits;

    /// @brief OmegaUARTHandle that needs to be used to operate using UARTController
    typedef uint64_t OmegaUARTHandle;

    typedef void (*OmegaUARTDataReceivedCallback)(uint8_t *, size_t);

    /**
     * @brief initialize the UARTSystemController which is responsible for allocating and deallocating the each individual UART buses.
     *          This needs to be called before trying to initialize any UART buses
     */
    UARTControllerStatus OmegaUARTSystemController_init();
    /**
     * @brief deinitialize the UARTSystemController which is responsible for allocating and deallocating the each individual UART buses
     *          After this is called, no new UART buses can be initialized.
     */
    void OmegaUARTSystemController_deinit();
    /**
     * @brief initialize an UART bus with given parameters
     *
     * @param in_uart_port input parameter. UART bus that needs to be used for the operation
     * @param in_tx_pin input parameter. TX pin that will be used for the UART bus. Can be NULL
     * @param in_rx_pin input parameter. RX pin that will be used for the UART bus. can be NULL
     * @param in_baudrate input parameter. baudrate that will be used by the UART bus. Cannot be NULL
     * @param in_data_bits input parameter. number of data bits that will be used in the UART operations. Cannot be NULL
     * @param in_parity input parameter. number of parity bits that will be used in the UART operations. Cannot be NULL
     * @param in_stop_bits input parameter. number of stop bits that will be used in the UART operations. Cannot be NULL
     * @return OmegaUARTHandle Identifier for the initialized bus. If `OmegaUARTController_init()` was success returned `OmegaUARTHandle` will be greater than 0
     */
    OmegaUARTHandle OmegaUARTController_init(uart_port_t in_uart_port, gpio_num_t in_tx_pin, gpio_num_t in_rx_pin, uint32_t in_baudrate, UART_Data_Bits in_data_bits, UART_Parity in_parity, UART_Stop_Bits in_stop_bits);
    /**
     * @brief initialize an UART bus with default parameters.
     *  baud rate   => 115200
     *  data bits   => 8 bits
     *  parity      => no parity
     *  stop bits   => 1 stop bits
     *
     * @param in_uart_port input parameter. UART bus that needs to be used for the operation
     * @param in_tx_pin input parameter. TX pin that will be used for the UART bus. Can be NULL
     * @param in_rx_pin input parameter. RX pin that will be used for the UART bus. can be NULL
     * @return OmegaUARTHandle Identifier for the initialized bus. If `OmegaUARTController_init()` was success returned `OmegaUARTHandle` will be greater than 0
     */
    OmegaUARTHandle OmegaUARTController_default_init(uart_port_t in_uart_port, gpio_num_t in_tx_pin, gpio_num_t in_rx_pin);
    /**
     * @brief add a function callback for data received events for the specified UART bus handle
     *
     * @param in_handle input parameter. Handle that refers to a previously initialized UART bus using `OmegaUARTController_init()`
     * @param in_callback input parameter. add a callback to to application layer from the UART bus
     * @return UARTControllerStatus UARTCTRL_SUCCESS if `OmegaUARTController_set_data_received_callback()` operation was success
     */
    UARTControllerStatus OmegaUARTController_set_data_received_callback(OmegaUARTHandle in_handle, OmegaUARTDataReceivedCallback in_callback);
    /**
     * @brief start UART bus with the configurations
     *
     * @param in_handle input parameter. Handle that refers to a previously initialized UART bus using `OmegaUARTController_init()`
     * @return UARTControllerStatus UARTCTRL_SUCCESS if `OmegaUARTController_start()` operation was success
     */
    UARTControllerStatus OmegaUARTController_start(OmegaUARTHandle in_handle);
    /**
     * @brief deinitialize previously configured UART bus
     *
     * @param in_handle input parameter. Handle that refers to a previously initialized UART bus using `OmegaUARTController_init()`
     * @return UARTControllerStatus UARTCTRL_SUCCESS if `OmegaUARTController_deinit()` operation was success
     */
    UARTControllerStatus OmegaUARTController_deinit(OmegaUARTHandle in_handle);
    /**
     * @brief used to configure the `OmegaUARTController_t` with the UART bus that is going to be used
     *
     * @param in_handle input parameter. Handle that refers to a previously initialized UART bus using `OmegaUARTController_init()`
     * @param in_uart_port input parameter. UART bus that needs to be used for the operations
     * @return UARTControllerStatus UARTCTRL_SUCCESS if `OmegaUARTController_deinit()` operation was success
     */
    UARTControllerStatus OmegaUARTController_set_uart_port(OmegaUARTHandle in_handle, uart_port_t in_uart_port);
    /** @brief Blocking/Non-Blocking method depending on the timeout. used to write bytes onto UART bus.
     *
     * @param in_handle input parameter. Handle that refers to a previously initialized UART bus using `OmegaUARTController_init()`
     * @param in_buffer input parameter. bytes that needs to be sent through the UART bus. Cannot be NULL.
     * @param in_buffer_length input parameter. number of bytes that needs to be sent from the above input buffer. cannot be NULL, Negative or zero
     * @param in_blocking_ms input parameter. the number of miliseconds to block the function to complete it's execution
     * @return size_t number of bytes written. If the write operation succeeded. in_buffer_length and this return parameter needs to be the same
     */
    size_t OmegaUARTController_write(OmegaUARTHandle in_handle, uint8_t *in_buffer, size_t in_buffer_length, uint64_t in_blocking_ms);
    /** @brief Blocking/Non-Blocking method depending on the timeout. used to read bytes from UART bus.
     *
     * @param in_handle input parameter. Handle that refers to a previously initialized UART bus using `OmegaUARTController_init()`
     * @param in_buffer input parameter. bytes that needs to be sent through the UART bus. Cannot be NULL.
     * @param in_buffer_length input parameter. number of bytes that needs to be sent from the above input buffer. cannot be NULL, Negative or zero
     * @param in_blocking_ms input parameter. the number of miliseconds to block the function to complete it's execution
     * @return size_t number of bytes read. If the read operation succeeded. in_buffer_length and this return parameter needs to be the same
     */
    size_t OmegaUARTController_read(OmegaUARTHandle in_handle, uint8_t *out_buffer, size_t in_buffer_length, uint64_t in_blocking_ms);
#ifdef __cplusplus
}
#endif

#endif