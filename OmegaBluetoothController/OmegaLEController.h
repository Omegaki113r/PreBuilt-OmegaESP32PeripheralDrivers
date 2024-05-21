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
 * Last Modified: Wednesday, 22nd May 2024 1:28:52 am
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

      LESuccessStatus add_gatts_profile(ProfileHandle in_profile);
      LESuccessStatus set_device_name(const char *in_device_name);
      LESuccessStatus set_advertising_device_name(const char *in_device_name);
      LESuccessStatus disable_advertising_device_name(bool in_device_name_enabled);
      LESuccessStatus start_advertising();
      LESuccessStatus stop_advertising();
      LESuccessStatus init_LE();

      const DescriptorHandle add_descriptor16(CharacteristicHandle in_handle, uint16_t in_uuid);
      const DescriptorHandle add_descriptor32(CharacteristicHandle in_handle, uint32_t in_uuid);
      const DescriptorHandle add_descriptor128(CharacteristicHandle in_handle, uint8_t in_uuid[UUID128]);
      const CharacteristicHandle add_characteristic16(ServiceHandle in_handle, uint16_t in_uuid);
      const CharacteristicHandle add_characteristic32(ServiceHandle in_handle, uint32_t in_uuid);
      const CharacteristicHandle add_characteristic128(ServiceHandle in_handle, uint8_t in_uuid[UUID128]);
      const ServiceHandle add_service16(ProfileHandle in_handle, uint16_t in_uuid);
      const ServiceHandle add_service32(ProfileHandle in_handle, uint32_t in_uuid);
      const ServiceHandle add_service128(ProfileHandle in_handle, uint8_t in_uuid[UUID128]);
      const ProfileHandle add_profile();

#endif

#ifdef __cplusplus
}
#endif

#endif