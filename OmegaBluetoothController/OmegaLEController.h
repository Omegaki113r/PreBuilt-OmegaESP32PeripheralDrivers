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
 * Last Modified: Monday, 3rd June 2024 12:35:05 pm
 * Modified By: Omegaki113r (omegaki113r@gmail.com)
 * -----
 * Copyright 2024 - 2024 0m3g4ki113r, Xtronic
 * -----
 * HISTORY:
 * Date      	By	Comments
 * ----------	---	---------------------------------------------------------
 *
 * 03-06-2024	0m3g4	added,
                              OmegaLEController_set_descriptor_name
                              OmegaLEController_remove_descriptor
                              OmegaLEController_set_characteristic_name
                              OmegaLEController_remove_characteristic
                              OmegaLEController_set_service_name
                              OmegaLEController_remove_service
                              OmegaLEController_set_profile_name
                              OmegaLEController_remove_profile
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

#define UUID2LIST(uuid)                                 \
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
          16 * CHAR2INT(uuid[0]) + CHAR2INT(uuid[1])

#define UUID128(name, ...) \
      uint8_t name[16] = {__VA_ARGS__};

#define INITIAL_BUFFER_LEN 5

      typedef enum
      {
            LE_SUCCESS,
            LE_INVALID_HANDLE,
            LE_FAILED,
      } LEControllerStatus;

      typedef enum
      {
            UUID16 = ESP_UUID_LEN_16,
            UUID32 = ESP_UUID_LEN_32,
            UUID128 = ESP_UUID_LEN_128,
      } UUIDLength;

      typedef enum
      {
            USER_RESPONSE,
            AUTO_RESPONSE,
      } AutoResponseStatus;

      typedef enum
      {
            NOTIFICATION_INDICATION_DISABLED,
            NOTIFICATION_ENABLED,
            INDICATION_ENABLED,
      } ResponseStatus;

      typedef enum
      {
            NO_PROPERTY,
            BROADCAST = ESP_GATT_CHAR_PROP_BIT_BROADCAST,
            READ = ESP_GATT_CHAR_PROP_BIT_READ,
            WRITE_WITHOUT_RESPONSE = ESP_GATT_CHAR_PROP_BIT_WRITE_NR,
            WRITE = ESP_GATT_CHAR_PROP_BIT_WRITE,
            NOTIFY = ESP_GATT_CHAR_PROP_BIT_NOTIFY,
            INDICATE = ESP_GATT_CHAR_PROP_BIT_INDICATE,
            AUTH = ESP_GATT_CHAR_PROP_BIT_AUTH,
            EXTENDED = ESP_GATT_CHAR_PROP_BIT_EXT_PROP,
      } CharacteristicProperty;

      typedef enum
      {
            NO_PERMISSION,
            READ_PERMISSION = ESP_GATT_PERM_READ,
            ENCRYPT_READ_PERMISSION = ESP_GATT_PERM_READ_ENCRYPTED,
            ENCRYPT_MITM_READ_PERMISSION = ESP_GATT_PERM_READ_ENC_MITM,
            WRITE_PERMISSION = ESP_GATT_PERM_WRITE,
            ENCRYPT_WRITE_PERMISSION = ESP_GATT_PERM_WRITE_ENCRYPTED,
            ENCRYPT_MITM_WRITE_PERMISSION = ESP_GATT_PERM_WRITE_ENC_MITM,
            SIGNED_WRITE_PERMISSION = ESP_GATT_PERM_WRITE_SIGNED,
            SIGNED_MITM_WRITE_PERMISSION = ESP_GATT_PERM_WRITE_SIGNED_MITM,
            AUTHORIZED_READ_PERMISSION = ESP_GATT_PERM_READ_AUTHORIZATION,
            AUTHORIZED_WRITE_PERMISSION = ESP_GATT_PERM_WRITE_AUTHORIZATION,
      } GATTPermission;

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

      typedef uint32_t ConnectedDeviceHandle;
      typedef uint32_t DescriptorHandle;
      typedef uint32_t CharacteristicHandle;
      typedef uint32_t ServiceHandle;
      typedef uint32_t ProfileHandle;

      typedef void (*disconnect_cb_t)(ConnectedDeviceHandle);
      typedef void (*connect_cb_t)(ConnectedDeviceHandle, ConnectionParameter_t *);
      typedef void (*read_cb_t)(CharacteristicHandle, uint8_t *, uint16_t *);
      typedef void (*write_cb_t)(CharacteristicHandle, uint8_t *, size_t);
      typedef void (*notification_state_change_cb_t)(CharacteristicHandle, ResponseStatus);

      LEControllerStatus OmegaLEController_add_gatts_profile(ProfileHandle in_profile);
      LEControllerStatus OmegaLEController_set_device_name(const char *in_device_name);
      LEControllerStatus OmegaLEController_change_advertising_device_name_state(bool in_enable_device_name);
      LEControllerStatus OmegaLEController_change_scan_response_device_name_state(bool in_enable_device_name);
      LEControllerStatus OmegaLEController_change_advertising_tx_power_state(bool in_enable_tx_power);
      LEControllerStatus OmegaLEController_change_scan_response_tx_power_state(bool in_enable_tx_power);
      LEControllerStatus OmegaLEController_change_advertising_service_data(const uint8_t *in_service_data_buffer, const uint16_t in_service_data_buffer_length);
      LEControllerStatus OmegaLEController_change_scan_response_service_data(const uint8_t *in_service_data_buffer, const uint16_t in_service_data_buffer_length);
      LEControllerStatus OmegaLEController_change_advertising_manufacturer_data(const uint8_t *in_manufacturer_data_buffer, const uint16_t in_manufacturer_data_buffer_length);
      LEControllerStatus OmegaLEController_change_scan_response_manufacturer_data(const uint8_t *in_manufacturer_data_buffer, const uint16_t in_manufacturer_data_buffer_length);
      LEControllerStatus OmegaLEController_set_advertising_service_uuid16(uint16_t in_service_uuid);
      LEControllerStatus OmegaLEController_set_advertising_service_uuid32(uint32_t in_service_uuid);
      LEControllerStatus OmegaLEController_set_advertising_service_uuid128(uint8_t in_service_uuid[UUID128]);
      LEControllerStatus OmegaLEController_change_advertising_service128bit_data(uint8_t in_service_uuid[UUID128], const uint8_t *in_service_data_buffer, const uint16_t in_service_data_buffer_length);
      LEControllerStatus OmegaLEController_change_manufacturer_data(const uint8_t *manufacturer_data, const size_t manufacturer_data_length);
      LEControllerStatus OmegaLEController_set_scan_response_service_uuid16(uint16_t in_service_uuid);
      LEControllerStatus OmegaLEController_set_scan_response_service_uuid32(uint32_t in_service_uuid);
      LEControllerStatus OmegaLEController_set_scan_response_service_uuid128(uint8_t in_service_uuid[UUID128]);
      LEControllerStatus OmegaLEController_start_advertising();
      LEControllerStatus OmegaLEController_stop_advertising();
      LEControllerStatus OmegaLEController_init_LE();
      LEControllerStatus OmegaLEController_get_bluetooth_mac_address(uint8_t in_mac_address[6]);
      LEControllerStatus OmegaLEController_set_disconnect_callback(disconnect_cb_t in_disconnect_cb);
      LEControllerStatus OmegaLEController_set_connect_callback(connect_cb_t in_connect_cb);
      LEControllerStatus OmegaLEController_set_read_callback(read_cb_t in_read_cb);
      LEControllerStatus OmegaLEController_set_write_callback(write_cb_t in_write_cb);
      LEControllerStatus OmegaLEController_set_notification_state_changed_callback(notification_state_change_cb_t in_notification_state_changed_cb);

      DescriptorHandle OmegaLEController_add_descriptor16(const CharacteristicHandle in_handle, uint16_t in_uuid);
      DescriptorHandle OmegaLEController_add_descriptor32(const CharacteristicHandle in_handle, uint32_t in_uuid);
      DescriptorHandle OmegaLEController_add_descriptor128(const CharacteristicHandle in_handle, uint8_t in_uuid[UUID128]);
      LEControllerStatus OmegaLEController_remove_descriptor(const DescriptorHandle in_handle);
      LEControllerStatus OmegaLEController_set_descriptor_name(const DescriptorHandle in_handle, const char in_descriptor_name[32]);
      LEControllerStatus OmegaLEController_set_descriptor_data(const DescriptorHandle in_handle, const uint8_t *in_data_buffer, size_t in_data_buffer_length);
      CharacteristicHandle OmegaLEController_add_characteristic16(const ServiceHandle in_handle, uint16_t in_uuid);
      CharacteristicHandle OmegaLEController_add_characteristic32(const ServiceHandle in_handle, uint32_t in_uuid);
      CharacteristicHandle OmegaLEController_add_characteristic128(const ServiceHandle in_handle, uint8_t in_uuid[UUID128]);
      LEControllerStatus OmegaLEController_remove_characteristic(const CharacteristicHandle in_handle);
      LEControllerStatus OmegaLEController_set_characteristic_name(const CharacteristicHandle in_handle, const char in_characteristic_name[32]);
      LEControllerStatus OmegaLEController_set_characteristic_data(const CharacteristicHandle in_handle, const uint8_t *in_data_buffer, size_t in_data_buffer_length);
      ServiceHandle OmegaLEController_add_service16(const ProfileHandle in_handle, uint16_t in_uuid);
      ServiceHandle OmegaLEController_add_service32(const ProfileHandle in_handle, uint32_t in_uuid);
      ServiceHandle OmegaLEController_add_service128(const ProfileHandle in_handle, uint8_t in_uuid[UUID128]);
      LEControllerStatus OmegaLEController_remove_service(const ServiceHandle in_handle);
      LEControllerStatus OmegaLEController_set_service_name(const ServiceHandle in_handle, const char in_service_name[32]);
      ProfileHandle OmegaLEController_add_profile();
      LEControllerStatus OmegaLEController_remove_profile(const ProfileHandle in_handle);
      LEControllerStatus OmegaLEController_set_profile_name(const ProfileHandle in_handle, const char in_profile_name[32]);
      LEControllerStatus OmegaLEController_set_characteristic_response_state(const CharacteristicHandle in_handle, AutoResponseStatus in_auto_response);
      LEControllerStatus OmegaLEController_set_characteristic_properties(const CharacteristicHandle in_handle, const CharacteristicProperty in_property);
      LEControllerStatus OmegaLEController_set_characteristic_permission(const CharacteristicHandle in_handle, const GATTPermission in_permission);

      LEControllerStatus OmegaLEController_send_notification(const ConnectedDeviceHandle in_device_handle, const CharacteristicHandle in_handle, uint8_t *in_data, size_t in_data_length);
      LEControllerStatus OmegaLEController_send_indication(const ConnectedDeviceHandle in_device_handle, const CharacteristicHandle in_handle, uint8_t *in_data, size_t in_data_length);

#endif

#ifdef __cplusplus
}
#endif

#endif