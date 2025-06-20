#include "wyze_iot3_0_callback.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include "cJSON.h"

int32_t WYZE_iot3_0_undefined_command_callback(const char* key,
                                              void*       user_ptr,
                                              const char* topic,
                                              size_t       topic_len,
                                              const char*   payload,
                                              size_t       payload_len) {
    (void)user_ptr;
    printf("undefined command key %s\r\n", key);
    printf("topic %.*s\r\n", topic_len, topic);
    printf("payload %.*s\r\n", payload_len, payload);
    return 0;
} 

int WYZE_iot3_0_log_level_callback(const char* deviceID,
                                   const char* deviceModel,
                                   int         payload_in,
                                   void*       payload_out) {
    if (deviceID != NULL && deviceModel) {
        printf("%s %s\r\n", deviceID, deviceModel);
    }

    *((int*)(payload_out)) = payload_in + 1;

    return 0;
}

int WYZE_iot3_0_device_floodlight_on_callback(const char* deviceID,
                                              const char* deviceModel,
                                              void*       user_ptr,
                                              int         payload_in,
                                              void*       payload_out) {
    printf("flood on\r\n");
    if (deviceID != NULL && deviceModel != NULL) {
        printf("%s %s\r\n", deviceID, deviceModel);
    }
    (void)user_ptr;
    *((int*)(payload_out)) = payload_in + 1;
    return 0;
}

int WYZE_iot3_0_device_airconditioner_callback(const char* deviceID,
                                               const char* deviceModel,
                                               void*       user_ptr,
                                               char*       payload_in,
                                               void*       payload_out) {
    if (deviceID != NULL && deviceModel != NULL) {
        printf("%s %s\r\n", deviceID, deviceModel);
    }
    printf("airconditioner on\r\n");
    (void)payload_in;
    (void)user_ptr;
    char* str                      = "airconditioner test";
    *((unsigned long*)payload_out) = (unsigned long)str;
    return 0;
}

int WYZE_iot3_0_device_purifier_callback(const char* deviceID,
                                         const char* deviceModel,
                                         void*       user_ptr,
                                         double      payload_in,
                                         void*       payload_out) {
    if (deviceID != NULL && deviceModel != NULL) {
        printf("%s %s\r\n", deviceID, deviceModel);
    }

    printf("airconditioner on\r\n");
    (void)user_ptr;
    *((double*)(payload_out)) = payload_in + 1;

    return 0;
}

int32_t WYZE_iot3_0_run_action_wakeup_callback(const char* deviceID,
                                           const char* deviceModel,
                                           void*       user_ptr,
                                           uint16_t    tid,
                                           uint64_t    ts,
                                           const char*       params,
                                           size_t         len) {
    int         ret  = 0;
    cJSON* json = NULL;
    printf("WYZE_iot3_0_run_action_wakeup_callback\r\n");
    if (deviceID != NULL && deviceModel != NULL) {
        printf("%s %s\r\n", deviceID, deviceModel);
    }

    (void)user_ptr;
    printf("tid %d ts %lld\n", tid, ts);
    printf("%s %d\n", params, len);
    // user_struct_t* ptr = user_ptr;
    char *buffer = malloc(len + 1);
    memset(buffer, 0x0, len + 1);
    memcpy(buffer, params, len);

    do {
        //json = cJSON_ParseWithLength(params, len);
        json = cJSON_Parse(buffer);

        if (json == NULL) {
            ret = -1;
            break;
        }

        cJSON* json_uid = cJSON_GetObjectItem(json, "rtc_uid");
        if (json_uid == NULL) {
            ret = -2;
            break;
        }
        printf("rtc uid %d\n", json_uid->valueint);

        cJSON* json_token = cJSON_GetObjectItem(json, "rtc_token");
        if (json_uid == NULL) {
            ret = -3;
            break;
        }
        printf("rtc token %s\n", json_token->valuestring);

        WYZE_wakeUp_Callback(json_uid->valueint, json_token->valuestring);
    } while (false);

    if (json != NULL) {
        cJSON_Delete(json);
    }
    if(buffer != NULL)
        free(buffer);

    return ret;
}

int WYZE_iot3_0_get_cam_resolution_callback(const char* deviceID,
                                            const char* deviceModel,
                                            void*       user_ptr,
                                            void*       payload_out) {
    char* str = "hello";
    if (deviceID != NULL && deviceModel != NULL) {
        printf("%s %s\r\n", deviceID, deviceModel);
    }
    (void)user_ptr;

    *((unsigned long*)payload_out) = (unsigned long)str;
    return 0;
}

int WYZE_iot3_0_get_iot_device_power_callback(const char* deviceID,
                                              const char* deviceModel,
                                              void*       user_ptr,
                                              void*       payload_out) {
    if (deviceID != NULL && deviceModel != NULL) {
        printf("%s %s\r\n", deviceID, deviceModel);
    }

    (void)user_ptr;
    *((uint8_t*)payload_out) = true;
    return 0;
}

int WYZE_iot3_0_get_cam_temp_callback(const char* deviceID,
                                      const char* deviceModel,
                                      void*       user_ptr,
                                      void*       payload_out) {
    if (deviceID != NULL && deviceModel != NULL) {
        printf("%s %s\r\n", deviceID, deviceModel);
    }

    (void)user_ptr;

    *((double*)payload_out) = (double)37.2;
    return 0;
}

int32_t WYZE_iot3_0_set_log_level_callback(const char* deviceID,
                                       const char* deviceModel,
                                       void*       user_ptr,
                                       int         payload_in,
                                       void*       payload_out) {
    // wyze_keep_alive_set_log_level(
    //     ((struct user_struct*)user_ptr)->iot3_0_handler,
    //     (uint8_t)payload_in);
    wyze_keep_alive_set_log_level(((struct user_struct*)user_ptr)->iot_handler,
                                  (uint8_t)payload_in);
    printf("iot device log level\r\n");
    if (deviceID != NULL && deviceModel != NULL) {
        printf("%s %s\r\n", deviceID, deviceModel);
    }

    *((int*)payload_out) = (int)payload_in;

    (void)user_ptr;
    // printf("set log level %d\n", payload_in);
    return 0;
}

int32_t WYZE_iot3_0_run_action_server_migration(const char* deviceID,
                                            const char* deviceModel,
                                            void*       user_ptr,
                                            uint16_t    tid,
                                            uint64_t    ts,
                                            const char*       params,
                                            size_t         len) {
    user_struct_t* ptr = user_ptr;
    if (deviceID != NULL && deviceModel != NULL) {
        printf("%s %s\r\n", deviceID, deviceModel);
    }
    printf("tid %d ts %lld\n", tid, ts);
    printf("%s %d\n", params, len);

    printf("WYZE_iot3_0_const run_action_server_migration\n");
    wyze_iot_server_migration(ptr->iot_handler);
    return 0;
}

int WYZE_iot3_0_run_action_submit_log(const char* deviceID,
                                      const char* deviceModel,
                                      void*       user_ptr,
                                      uint16_t    tid,
                                      uint64_t    ts,
                                      char*       params,
                                      int         len) {
    printf("WYZE_iot3_0_run_action_submit_log\n");
    if (deviceID != NULL && deviceModel != NULL) {
        printf("%s %s\r\n", deviceID, deviceModel);
    }
    (void)user_ptr;
    printf("tid %d ts %lld\n", tid, ts);
    printf("%s %d\n", params, len);

    printf("%s\n", params);
    return 0;
}

uint64_t get_timestamp(void);
uint64_t wyze_iot3_0_system_ms_time(void) {
    return get_timestamp();
}

int WYZE_iot3_0_sync_action_get_one_time_code(const char* deviceID,
                                              const char* deviceModel,
                                              void*       user_ptr,
                                              uint16_t    tid,
                                              uint64_t    ts,
                                              char*       params,
                                              int         len) {
    int ret = 0;
    printf("WYZE_iot3_0_sync_action_get_one_time_code\n");
    if (deviceID != NULL && deviceModel != NULL) {
        printf("%s %s\r\n", deviceID, deviceModel);
    }
    (void)user_ptr;
    (void)len;
    (void)params;
    printf("tid %d ts %lld\n", tid, ts);
    /* report one time code */
    /* create sync action ack */
    /* 创建一个空的 JSON 对象 */
    cJSON* json_ack_message = cJSON_CreateObject();
    if (json_ack_message == NULL) return -1;
    cJSON_AddStringToObject(json_ack_message, "cmd", "run_action_ack");

    cJSON_AddStringToObject(json_ack_message,
                                 "action",
                                 "lock::get-one-time-code");
    cJSON_AddNumberToObject(json_ack_message,
                                 "ts",
                                 wyze_iot3_0_system_ms_time());
    cJSON_AddNumberToObject(json_ack_message, "tid", tid);

    cJSON* json_params_object = cJSON_CreateObject();
    if (json_params_object != NULL) {
        cJSON_AddStringToObject(json_params_object,
                                     "code",
                                     "1234567");  // input you password
        cJSON_AddNumberToObject(json_params_object,
                                     "expiration_time",
                                     100000);
        cJSON_AddItemToObject(json_ack_message,
                                   "params",
                                   json_params_object);
    }
    cJSON_AddNumberToObject(json_ack_message,
                                 "result",
                                 1);  // result 1:succeed 0:failed
    char*          ack_string = cJSON_PrintUnformatted(json_ack_message);
    user_struct_t* user       = user_ptr;
    ret                       = wyze_iot_sync_action_ack_send(user->iot_handler,
                                        deviceModel,
                                        deviceID,
                                        ack_string,
                                        strlen(ack_string));

    free(ack_string);
    cJSON_Delete(json_ack_message);
    return ret;
}

int WYZE_iot3_0_sync_action_add_one_time_code(const char* deviceID,
                                              const char* deviceModel,
                                              void*       user_ptr,
                                              uint16_t    tid,
                                              uint64_t    ts,
                                              char*       params,
                                              int         len) {
    int ret = 0;
    printf("WYZE_iot3_0_sync_action_add_one_time_code\n");
    if (deviceID != NULL && deviceModel != NULL) {
        printf("%s %s\r\n", deviceID, deviceModel);
    }
    (void)user_ptr;
    (void)len;
    (void)params;
    printf("tid %d ts %lld\n", tid, ts);
    /* report one time code */
    /* create sync action ack */
    /* 创建一个空的 JSON 对象 */
    cJSON* json_ack_message = cJSON_CreateObject();
    if (json_ack_message == NULL) return -1;
    cJSON_AddStringToObject(json_ack_message, "cmd", "run_action_ack");

    cJSON_AddStringToObject(json_ack_message,
                                 "action",
                                 "lock::add-one-time-code");
    cJSON_AddNumberToObject(json_ack_message,
                                 "ts",
                                 wyze_iot3_0_system_ms_time());
    cJSON_AddNumberToObject(json_ack_message, "tid", tid);

    cJSON* json_params_object = cJSON_CreateObject();
    if (json_params_object != NULL) {
        cJSON_AddNumberToObject(json_params_object, "receive_ts", ts);
        cJSON_AddItemToObject(json_ack_message,
                                   "params",
                                   json_params_object);
    }
    cJSON_AddNumberToObject(json_ack_message,
                                 "result",
                                 1);  // result 1:succeed 0:failed
    char* ack_string = cJSON_PrintUnformatted(json_ack_message);

    user_struct_t* user = user_ptr;
    ret                 = wyze_iot_sync_action_ack_send(user->iot_handler,
                                        deviceModel,
                                        deviceID,
                                        ack_string,
                                        strlen(ack_string));

    free(ack_string);
    cJSON_Delete(json_ack_message);
    return ret;
}