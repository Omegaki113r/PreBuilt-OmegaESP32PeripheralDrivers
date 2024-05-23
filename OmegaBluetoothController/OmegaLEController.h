/**
 * @file OmegaLEController.h
 * @author Omegaki113r
 * @date Saturday, 18th May 2024 10:28:57 pm
 * @copyright Copyright 2024 - 2024 0m3g4ki113r, Xtronic
 * */
/*
 * Project: OmegaESP32PeripheralDrivers
 * File Name: OmegaLEController.h
 * File Created: Saturday, 18th May 2024 10:28:57 pm
 * Author: Omegaki113r (omegaki113r@gmail.com)
 * -----
 * Last Modified: Friday, 24th May 2024 2:31:41 am
 * Modified By: Omegaki113r (omegaki113r@gmail.com)
 * -----
 * Copyright 2024 - 2024 0m3g4ki113r, Xtronic
 * -----
 * HISTORY:
 * Date      	By	Comments
 * ----------	---	---------------------------------------------------------
 */
#ifndef __OMEGA_LE_CONTROLLER_H__
#define __OMEGA_LE_CONTROLLER_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdio.h>
#include <stdlib.h>

#include <sdkconfig.h>

#ifdef CONFIG_BT_ENABLED

#include "esp_bt.h"
#include "esp_bt_defs.h"
#include "esp_bt_main.h"
#include "esp_gap_ble_api.h"
#include "esp_gatt_common_api.h"
#include "esp_gattc_api.h"
#include "esp_gatts_api.h"

#define CHAR2INT(x) (('0' <= x && x <= '9') ? (x - '0') : (('a' <= x && x <= 'f') ? (10 + (x - 'a')) : (('A' <= x && x <= 'F') ? (10 + (x - 'A')) : (0))))

#define UUID2ARRAY(uuid)                                      \
      (uint8_t[])                                             \
      {                                                       \
            16 * CHAR2INT(uuid[34]) + CHAR2INT(uuid[35]),     \
                16 * CHAR2INT(uuid[32]) + CHAR2INT(uuid[33]), \
                16 * CHAR2INT(uuid[30]) + CHAR2INT(uuid[31]), \
                16 * CHAR2INT(uuid[28]) + CHAR2INT(uuid[29]), \
                16 * CHAR2INT(uuid[26]) + CHAR2INT(uuid[27]), \
                16 * CHAR2INT(uuid[24]) + CHAR2INT(uuid[25]), \
                16 * CHAR2INT(uuid[21]) + CHAR2INT(uuid[22]), \
                16 * CHAR2INT(uuid[19]) + CHAR2INT(uuid[20]), \
                16 * CHAR2INT(uuid[16]) + CHAR2INT(uuid[17]), \
                16 * CHAR2INT(uuid[14]) + CHAR2INT(uuid[15]), \
                16 * CHAR2INT(uuid[11]) + CHAR2INT(uuid[12]), \
                16 * CHAR2INT(uuid[9]) + CHAR2INT(uuid[10]),  \
                16 * CHAR2INT(uuid[6]) + CHAR2INT(uuid[7]),   \
                16 * CHAR2INT(uuid[4]) + CHAR2INT(uuid[5]),   \
                16 * CHAR2INT(uuid[2]) + CHAR2INT(uuid[3]),   \
                16 * CHAR2INT(uuid[0]) + CHAR2INT(uuid[1]),   \
      }

#define INITIAL_BUFFER_LEN 5

      typedef enum
      {
            UUID16 = ESP_UUID_LEN_16,
            UUID32 = ESP_UUID_LEN_32,
            UUID128 = ESP_UUID_LEN_128,
      } UUIDLength;

      typedef enum
      {
            LE_SUCCESS,
            LE_FAILED,
      } LEControllerStatus;

      /// @brief Connection update parameters
      typedef struct
      {
            /// @brief Bluetooth device address
            esp_bd_addr_t bda;
            /// @brief Min connection interval [interval = min_int*1.25ms]
            uint16_t min_int;
            /// @brief Max connection interval [interval = max_int*1.25ms]
            uint16_t max_int;
            /// @brief Slave latency for the connection in number of connection events. Range: 0x0000 to 0x01F3
            uint16_t latency;
            /**
             * @brief Supervision timeout for the LE Link.
             *          Range: 0x000A to 0x0C80.
             *          Mandatory Range: 0x000A to 0x0C80 Time = N * 10 msec
             *          Time Range: 100 msec to 32 seconds
             */
            uint16_t timeout;
      } ConnectionParameter_t;

      typedef uint64_t DescriptorHandle;
      typedef uint64_t CharacteristicHandle;
      typedef uint64_t ServiceHandle;
      typedef uint64_t ProfileHandle;

      typedef void (*disconnect_cb_t)(void);
      typedef void (*connect_cb_t)(ConnectionParameter_t *);
      typedef void (*read_cb_t)(CharacteristicHandle, uint8_t *, size_t);
      typedef void (*write_cb_t)(CharacteristicHandle, uint8_t *, size_t);

      LEControllerStatus OmegaLEController_add_gatts_profile(ProfileHandle in_profile);
      LEControllerStatus OmegaLEController_set_device_name(const char *in_device_name);
      LEControllerStatus OmegaLEController_set_advertising_device_name(const char *in_device_name);
      LEControllerStatus OmegaLEController_disable_advertising_device_name(bool in_device_name_enabled);
      LEControllerStatus OmegaLEController_start_advertising();
      LEControllerStatus OmegaLEController_stop_advertising();
      LEControllerStatus OmegaLEController_init_LE();
      LEControllerStatus OmegaLEController_set_disconnect_callback(disconnect_cb_t in_disconnect_cb);
      LEControllerStatus OmegaLEController_set_connect_callback(connect_cb_t in_connect_cb);
      LEControllerStatus OmegaLEController_set_read_callback(read_cb_t in_read_cb);
      LEControllerStatus OmegaLEController_set_write_callback(write_cb_t in_write_cb);

      DescriptorHandle OmegaLEController_add_descriptor16(const CharacteristicHandle in_handle, uint16_t in_uuid);
      DescriptorHandle OmegaLEController_add_descriptor32(const CharacteristicHandle in_handle, uint32_t in_uuid);
      DescriptorHandle OmegaLEController_add_descriptor128(const CharacteristicHandle in_handle, uint8_t in_uuid[UUID128]);
      CharacteristicHandle OmegaLEController_add_characteristic16(const ServiceHandle in_handle, uint16_t in_uuid);
      CharacteristicHandle OmegaLEController_add_characteristic32(const ServiceHandle in_handle, uint32_t in_uuid);
      CharacteristicHandle OmegaLEController_add_characteristic128(const ServiceHandle in_handle, uint8_t in_uuid[UUID128]);
      ServiceHandle OmegaLEController_add_service16(const ProfileHandle in_handle, uint16_t in_uuid);
      ServiceHandle OmegaLEController_add_service32(const ProfileHandle in_handle, uint32_t in_uuid);
      ServiceHandle OmegaLEController_add_service128(const ProfileHandle in_handle, uint8_t in_uuid[UUID128]);
      ProfileHandle OmegaLEController_add_profile();

#endif

#ifdef __cplusplus
}
#endif

#endif