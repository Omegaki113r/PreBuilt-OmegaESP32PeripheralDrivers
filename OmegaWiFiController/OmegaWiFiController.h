#ifndef __OMEGA_WIFI_CONTROLLER_H__
#define __OMEGA_WIFI_CONTROLLER_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <esp_log.h>
#include <esp_wifi.h>

#define WIFI_CONTROLLER_TAG "[OMEGA_WIFI_LOG]"

typedef struct
{
    wifi_init_config_t m_wifi_init_config;
    wifi_config_t m_sta_config;
    wifi_config_t m_ap_config;
    esp_event_handler_t m_callback;
    uint8_t m_sta_max_retry_count;
    uint8_t m_sta_retry_count;
} OmegaWiFiController_t;

void OmegaWiFiController_reset_module(OmegaWiFiController_t *);
void OmegaWiFiController_set_sta_provisioning(OmegaWiFiController_t *, const char *, const char *);
void OmegaWiFiController_set_ap_provisioning(OmegaWiFiController_t *, const char *, const char *);
void OmegaWiFiController_set_callback(OmegaWiFiController_t *, esp_event_handler_t);
void OmegaWiFiController_initialize(OmegaWiFiController_t *);

void _OmegaWiFiController_callback(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data);

#ifdef __cplusplus
}
#endif

#endif