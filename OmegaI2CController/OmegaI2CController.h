/**
 * @file OmegaI2CController.h
 * @author Omegaki113r
 * @date Monday, 13th May 2024 4:07:25 pm
 * @copyright Copyright 2024 - 2024 0m3g4ki113r, Xtronic
 * */
/*
 * Project: OmegaESP32PeripheralDrivers
 * File Name: OmegaI2CController.h
 * File Created: Monday, 13th May 2024 4:07:25 pm
 * Author: Omegaki113r (omegaki113r@gmail.com)
 * -----
 * Last Modified: Wednesday, 15th May 2024 3:02:13 am
 * Modified By: Omegaki113r (omegaki113r@gmail.com)
 * -----
 * Copyright 2024 - 2024 0m3g4ki113r, Xtronic
 * -----
 * HISTORY:
 * Date      	By	Comments
 * ----------	---	---------------------------------------------------------
 *
 * 13-05-2024	0m3g4	Started writing proper code and documentation
 */

#ifndef __OMEGA_I2C_CONTROLLER_H__
#define __OMEGA_I2C_CONTROLLER_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <driver/gpio.h>
#include <driver/i2c_master.h>

    /// @brief Enumaration for indicating status of the API that was being called
    typedef enum
    {
        /// @brief Indicates that the called API executed successfully
        I2CCTRL_SUCCESS,
        /// @brief Indicates that the API call cannot be executed due to I2C Controller system is not initialzed
        I2CSYSCTRL_NOT_INIT,
        /// @brief Indicates that the parameters that was used in the API was invalid
        I2CCTRL_INVALID_PARAMETERS,
        /// @brief Indicates that the API execution failed due to unknown reason
        I2CCTRL_FAILED,
    } I2CControllerStatus;

    /// @brief Abstracted enumaration of the clock sources available for the i2c driver to use
    typedef enum
    {
        DEFAULT = I2C_CLK_SRC_DEFAULT,
        XTAL = I2C_CLK_SRC_XTAL,
        RC_FAST = I2C_CLK_SRC_RC_FAST,
    } I2C_ClockSources;

    /// @brief Handle that will be used to operate the driver on master mode
    typedef uint64_t OmegaI2CMasterHandle;
    /// @brief Handle that will be used to operate the driver on slave mode
    typedef uint64_t OmegaI2CSlaveHandle;

    OmegaI2CMasterHandle OmegaI2CMasterController_init(i2c_port_t, gpio_num_t, gpio_num_t);
    I2CControllerStatus OmegaI2CMasterController_deinit(OmegaI2CMasterHandle);
    I2CControllerStatus OmegaI2CMasterController_scan_i2c_bus(OmegaI2CMasterHandle, bool);
    I2CControllerStatus OmegaI2CMasterController_add_device(OmegaI2CMasterHandle, uint8_t, uint32_t);
    I2CControllerStatus OmegaI2CMasterController_read_register(OmegaI2CMasterHandle, uint8_t, uint8_t *, uint8_t, uint32_t);
    // I2CControllerStatus OmegaI2CController_set_i2c_port(OmegaI2CMasterHandle, i2c_port_t);
    // I2CControllerStatus OmegaI2CController_set_i2c_mode(OmegaI2CMasterHandle, i2c_mode_t);
    // I2CControllerStatus OmegaI2CController_set_i2c_pins(OmegaI2CMasterHandle, gpio_num_t, gpio_num_t);
    // I2CControllerStatus OmegaI2CController_set_i2c_clock_speed_hz(OmegaI2CMasterHandle, uint32_t);
    // I2CControllerStatus OmegaI2CController_start(OmegaI2CMasterHandle);
    // I2CControllerStatus OmegaI2CController_write_register(OmegaI2CMasterHandle, uint8_t, uint8_t, uint8_t *, size_t);
    // I2CControllerStatus OmegaI2CController_read_register(OmegaI2CMasterHandle, uint8_t, uint8_t, uint8_t *, size_t);

#ifdef __cplusplus
}
#endif

#endif