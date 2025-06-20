#ifndef WYZE_IOT3_0_CALLBACK_H
#define WYZE_IOT3_0_CALLBACK_H
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#include "wyze-iot/wyze-iot-base.h"
#include "wyze-iot/wyze-iot-v3.h"
#include "wyze-iot/wyze-keep-alive.h"

typedef struct user_struct {
    void* iot_handler;
    void* user_ptr;
} user_struct_t;
int32_t WYZE_iot3_0_undefined_command_callback(const char* key,
                                              void*       user_ptr,
                                              const char* topic,
                                              size_t       topic_len,
                                              const char*   payload,
                                              size_t       payload_len);

int WYZE_iot3_0_device_floodlight_on_callback(const char* deviceID,
                                              const char* deviceModel,
                                              void*       user_ptr,
                                              int         payload_in,
                                              void*       payload_out);
int WYZE_iot3_0_device_airconditioner_callback(const char* deviceID,
                                               const char* deviceModel,
                                               void*       user_ptr,
                                               char*       payload_in,
                                               void*       payload_out);
int WYZE_iot3_0_device_purifier_callback(const char* deviceID,
                                         const char* deviceModel,
                                         void*       user_ptr,
                                         double      payload_in,
                                         void*       payload_out);
int32_t WYZE_iot3_0_run_action_wakeup_callback(const char* deviceID,
                                           const char* deviceModel,
                                           void*       user_ptr,
                                           uint16_t    tid,
                                           uint64_t    ts,
                                           const char*       params,
                                           size_t         len);

int WYZE_iot3_0_get_cam_resolution_callback(const char* deviceID,
                                            const char* deviceModel,
                                            void*       user_ptr,
                                            void*       payload_out);
int WYZE_iot3_0_get_iot_device_power_callback(const char* deviceID,
                                              const char* deviceModel,
                                              void*       user_ptr,
                                              void*       payload_out);
int WYZE_iot3_0_get_cam_temp_callback(const char* deviceID,
                                      const char* deviceModel,
                                      void*       user_ptr,
                                      void*       payload_out);
int WYZE_iot3_0_log_level_callback(const char* deviceID,
                                   const char* deviceModel,
                                   int         payload_in,
                                   void*       payload_out);

int32_t WYZE_iot3_0_set_log_level_callback(const char* deviceID,
                                       const char* deviceModel,
                                       void*       user_ptr,
                                       int         payload_in,
                                       void*       payload_out);

int32_t WYZE_wakeUp_Callback(long rtc_uid, const char* rtc_token);

int32_t WYZE_iot3_0_run_action_server_migration(const char* deviceID,
                                            const char* deviceModel,
                                            void*       user_ptr,
                                            uint16_t    tid,
                                            uint64_t    ts,
                                            const char*       params,
                                            size_t         len);
int WYZE_iot3_0_run_action_submit_log(const char* deviceID,
                                      const char* deviceModel,
                                      void*       user_ptr,
                                      uint16_t    tid,
                                      uint64_t    ts,
                                      char*       params,
                                      int         len);

int WYZE_iot3_0_sync_action_get_one_time_code(const char* deviceID,
                                              const char* deviceModel,
                                              void*       user_ptr,
                                              uint16_t    tid,
                                              uint64_t    ts,
                                              char*       params,
                                              int         len);

int WYZE_iot3_0_sync_action_add_one_time_code(const char* deviceID,
                                              const char* deviceModel,
                                              void*       user_ptr,
                                              uint16_t    tid,
                                              uint64_t    ts,
                                              char*       params,
                                              int         len);

#ifdef __cplusplus
}
#endif
#endif