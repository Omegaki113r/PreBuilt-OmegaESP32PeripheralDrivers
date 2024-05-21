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
 * Last Modified: Tuesday, 21st May 2024 3:27:23 pm
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
#include "esp_gatts_api.h"

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
      } LESuccessStatus;

      typedef uint64_t DescriptorHandle;
      typedef uint64_t CharacteristicHandle;
      typedef uint64_t ServiceHandle;
      typedef uint64_t ProfileHandle;

      typedef struct
      {
            uint16_t _descriptor_handle;
            DescriptorHandle m_descriptor_handle;
            UUIDLength len;
            union
            {
                  uint16_t uuid16;
                  uint32_t uuid32;
                  uint8_t uuid128[UUID128];
            } uuid;
      } Descriptor_t;
      typedef struct
      {
            uint16_t _characteristic_handle;
            CharacteristicHandle m_characteristic_handle;
            UUIDLength len;
            union
            {
                  uint16_t uuid16;
                  uint32_t uuid32;
                  uint8_t uuid128[UUID128];
            } uuid;
            uint32_t m_idx;
            uint32_t m_descriptor_buffer_size;
            Descriptor_t *m_descriptors;
      } Characteristic_t;
      typedef struct
      {
            uint16_t _service_handle;
            ServiceHandle m_service_handle;
            UUIDLength len;
            union
            {
                  uint16_t uuid16;
                  uint32_t uuid32;
                  uint8_t uuid128[UUID128];
            } uuid;
            uint32_t m_idx;
            uint32_t m_characteristic_buffer_size;
            Characteristic_t *m_characteristics;
      } Service_t;
      typedef struct
      {
            ProfileHandle m_profile_handle;
            uint32_t m_idx;
            uint32_t m_service_buffer_size;
            Service_t *m_services;
      } Profile_t;
      typedef struct
      {
            uint32_t m_idx;
            uint32_t m_profile_buffer_size;
            Profile_t *m_profiles;
      } BLEApplication_t;

      ProfileHandle init_profile();
      LESuccessStatus init_service16(ProfileHandle in_profile_handle, uint16_t in_uuid);
      LESuccessStatus init_service32(ProfileHandle in_profile_handle, uint32_t in_uuid);
      LESuccessStatus init_service128(ProfileHandle in_profile_handle, uint8_t in_uuid[UUID128]);
      LESuccessStatus deinit_profile(ProfileHandle in_handle);

      LESuccessStatus add_gatts_profile(Profile_t *in_profile);
      LESuccessStatus set_device_name(const char *in_device_name);
      LESuccessStatus set_advertising_device_name(const char *in_device_name);
      LESuccessStatus disable_advertising_device_name(bool in_device_name_enabled);
      LESuccessStatus start_advertising();
      LESuccessStatus stop_advertising();
      LESuccessStatus init_LE();

#endif

#ifdef __cplusplus
}
#endif

#endif