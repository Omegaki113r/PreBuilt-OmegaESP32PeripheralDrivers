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
 * Last Modified: Friday, 17th May 2024 10:04:44 pm
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
        /// @brief Indicates the system to use default clock source for the I2C peripheral
        DEFAULT = I2C_CLK_SRC_DEFAULT,
#if CONFIG_IDF_TARGET_ESP32
        /// @brief Indicates the system to use APB clock as the source for the I2C peripheral
        APB = I2C_CLK_SRC_APB,
#endif
#if CONFIG_IDF_TARGET_ESP32S3
        /// @brief Indicates the system to use XTAL as the source for the I2C peripheral
        XTAL = I2C_CLK_SRC_XTAL,
        /// @brief Indicates the system to use Fast Realtime clock as the source for the I2C peripheral
        RC_FAST = I2C_CLK_SRC_RC_FAST,
#endif
    } I2C_ClockSources;

    /// @brief Handle that will be used to operate the driver on master mode
    typedef uint64_t OmegaI2CMasterHandle;
    /// @brief Handle that will be used to operate the driver on slave mode
    typedef uint64_t OmegaI2CSlaveHandle;
    /// @brief Handle that will be used to operate the device
    typedef uint64_t OmegaI2CSlaveDeviceHandle;

    /**
     * @brief Initialize I2C Master bus for a specific I2C port and scl and sda gpio combination. This API will be removed in the future
     *
     * @param in_i2c_port input parameter of type `i2c_port_t`. I2C port that needs to be used for this master bus. -1 will result in system will automatically selecting the i2c port
     * @param in_scl_pin input parameter of type `gpio_num_t`. gpio that will be used as the SCL signal line of the I2C bus. should be within GPIO_NUM_0 and GPIO_NUM_MAX
     * @param in_sda_pin input parameter of type `gpio_num_t`. gpio that will be used as the SDA signal line of the I2C bus. should be within GPIO_NUM_0 and GPIO_NUM_MAX
     * @return OmegaI2CMasterHandle Reference for the I2C master bus that was initialized. non zero value if the API executed successfully zero otherwise
     */
    OmegaI2CMasterHandle OmegaI2CMasterController_init(i2c_port_t in_i2c_port, gpio_num_t in_scl_pin, gpio_num_t in_sda_pin);
    /**
     * @brief Deallocate all memories and resources attached to the specified I2C master bus
     *
     * @param in_handle input parameter of type `OmegaI2CMasterHandle`. This needs to be previously initialized
     * @return I2CControllerStatus I2CCTRL_INVALID_PARAMETERS if in_handle is not a valid argument (Not initialized or 0). I2CCTRL_FAILED if `i2c_del_master_bus` failed or removing I2CMasterbus erase failed. I2CCTRL_SUCCESS otherwise
     */
    I2CControllerStatus OmegaI2CMasterController_deinit(OmegaI2CMasterHandle in_handle);
    /**
     * @brief Scan all the devices attached to the master bus
     *
     * @param in_handle input parameter of type `OmegaI2CMasterHandle`. This needs to be previously initialized
     * @param in_indefinite input parameter of type `bool`. This indicates the API to run the scan indefinitely.
     * @param out_scanned_devices output parameter of type `uint8_t*`. This will be used to store all the I2C slave devices found in the master bus
     * @param out_scanned_device_count output parameter of type `uint8_t*`. This will be used to store the number of slave devices found on the I2C master bus
     * @return I2CControllerStatus I2CCTRL_INVALID_PARAMETERS if in_handle is not initialized, invalid or out_scanned_devices argument is NULL. I2CCTRL_SUCCESS otherwise
     */
    I2CControllerStatus OmegaI2CMasterController_scan_i2c_bus(OmegaI2CMasterHandle in_handle, bool in_indefinite, uint8_t *out_scanned_devices, uint8_t *out_scanned_device_count);
    /**
     * @brief Used to add a slave device to the I2C master bus that was previously initialized.
     *
     * @param in_handle input parameter of type `OmegaI2CMasterHandle`. This needs to be previously initialized
     * @param in_device_address input parameter of type `uint8_t`. Address of the slave device that needs to be added to the master bus
     * @param in_clock_speed input parameter of type `uint32_t`. SCL clock speed that the slave device will be running
     * @return OmegaI2CSlaveDeviceHandle Reference for the slave device that was added to the master bus. non zero value if the API executed successfully zero otherwise
     */
    OmegaI2CSlaveDeviceHandle OmegaI2CMasterController_add_device(OmegaI2CMasterHandle in_handle, uint8_t in_device_address, uint32_t in_clock_speed);
    /**
     * @brief Used to remove a slave device from I2C master bus.
     *
     * @param in_handle input parameter of type `OmegaI2CSlaveDeviceHandle`. This needs to be previously added to a master bus
     * @return I2CControllerStatus I2CCTRL_INVALID_PARAMETERS if in_handle was not initialized or not a valid handle. I2CCTRL_FAILED if `i2c_master_bus_rm_device` failed or failed to freeup the allocated resources for the slave device. I2CCTRL_SUCCESS otherwise
     */
    I2CControllerStatus OmegaI2CMasterController_remove_device(OmegaI2CSlaveDeviceHandle in_handle);
    /**
     * @brief Used to read a single byte from I2C slave device
     *
     * @param in_handle input parameter of type `OmegaI2CSlaveDeviceHandle`. Reference to a slave device handle that was previously added to a master I2C bus
     * @param out_data output parameter of type `uint8_t*`. This will be used to store the byte read from the slave device
     * @param in_timeout_ms input parameter of type `uint32_t`. This is the timeout in miliseconds that the I2C peripheral will wait for the data
     * @return I2CControllerStatus I2CCTRL_INVALID_PARAMETERS if in_handle is not initialized, not valid or out_data is NULL. I2CCTRL_FAILED if timeout occured. I2CCTRL_SUCCESS otherwise
     */
    I2CControllerStatus OmegaI2CMasterController_read_byte(OmegaI2CSlaveDeviceHandle in_handle, uint8_t *out_data, uint32_t in_timeout_ms);
    /**
     * @brief Used to write a single byte to I2C slave device
     *
     * @param in_handle input parameter of type `OmegaI2CSlaveDeviceHandle`. Reference to a slave device handle that was previously added to a master I2C bus
     * @param in_data input parameter of type `uint8_t`. This is the byte that will be written to the slave device
     * @param in_timeout_ms input parameter of type `uint32_t`. This is the timeout in miliseconds that the I2C peripheral will wait for the completion of data write operation
     * @return I2CControllerStatus I2CCTRL_INVALID_PARAMETERS if in_handle is not initialized, not valid. I2CCTRL_FAILED if timeout occured. I2CCTRL_SUCCESS otherwise
     */
    I2CControllerStatus OmegaI2CMasterController_write_byte(OmegaI2CSlaveDeviceHandle in_handle, uint8_t in_data, uint32_t in_timeout_ms);
    /**
     * @brief Used to read from I2C slave device address
     *
     * @param in_handle input parameter of type `OmegaI2CSlaveDeviceHandle`. Reference to a slave device handle that was previously added to a master I2C bus
     * @param in_register input parameter of type `uint8_t`. Reference to the register address of the slave device that needs to be read.
     * @param out_register_data output parameter of type `uint8_t*`. This will be used to store the bytes read from the slave device
     * @param in_read_length input parameter of type `size_t`. This is the amount of bytes that will be read from the slave device
     * @param in_timeout_ms input parameter of type `uint32_t`. This is the timeout in miliseconds that the I2C peripheral will wait for the data
     * @return I2CControllerStatus I2CControllerStatus I2CCTRL_INVALID_PARAMETERS if in_handle is not initialized, not valid or out_register_data is NULL. I2CCTRL_FAILED if timeout occured. I2CCTRL_SUCCESS otherwise
     */
    I2CControllerStatus OmegaI2CMasterController_read_register(OmegaI2CMasterHandle in_handle, uint8_t in_register, uint8_t *out_register_data, size_t in_read_length, uint32_t in_timeout_ms);
    /**
     * @brief Used to write to I2C slave device address
     *
     * @param in_handle input parameter of type `OmegaI2CSlaveDeviceHandle`. Reference to a slave device handle that was previously added to a master I2C bus
     * @param in_register input parameter of type `uint8_t`. Reference to the register address of the slave device that needs to be read.
     * @param in_register_data input parameter of type `uint8_t*`. These are the bytes that will be written to the slave device
     * @param in_write_length input parameter of type `size_t`. This is the amount of bytes that will be write to the slave device
     * @param in_timeout_ms input parameter of type `uint32_t`. This is the timeout in miliseconds that the I2C peripheral will wait for the data to be transmitted
     * @return I2CControllerStatus I2CControllerStatus I2CCTRL_INVALID_PARAMETERS if in_handle is not initialized, not validL. I2CCTRL_FAILED if timeout occured. I2CCTRL_SUCCESS otherwise
     */
    I2CControllerStatus OmegaI2CMasterController_write_register(OmegaI2CMasterHandle in_handle, uint8_t in_register, uint8_t *in_register_data, size_t in_write_length, uint32_t in_timeout_ms);
#ifdef __cplusplus
}
#endif

#endif