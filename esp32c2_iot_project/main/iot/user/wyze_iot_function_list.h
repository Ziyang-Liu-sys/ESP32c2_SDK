#ifndef WYZE_IOT_FUNCTION_LIST_H
#define WYZE_IOT_FUNCTION_LIST_H
#ifdef __cplusplus
extern "C" {
#endif
#include "wyze_iot3_0_callback.h"
#include "wyze-iot/wyze-iot-base.h"
#include "wyze-iot/wyze-iot-v3.h"
wyze_iot_function_list func_list[] = {
    /*Property*/
    {"undefined_command", WYZE_IOT_UNDEFINED_CMD, {.func_undefined_ptr = WYZE_iot3_0_undefined_command_callback}, WYZE_IOT_FUNC_LIST_PARAM_NONE},
#if 0
    {"floodlight::on", WYZE_IOT_SET_PROPERTY_CMD, {.func_int_ptr = WYZE_iot3_0_device_floodlight_on_callback}, WYZE_IOT_FUNC_LIST_PARAM_INT},
    {"airconditioner::on", WYZE_IOT_SET_PROPERTY_CMD, {.func_string_ptr = WYZE_iot3_0_device_airconditioner_callback}, WYZE_IOT_FUNC_LIST_PARAM_CHAR},
    {"purifier::on", WYZE_IOT_SET_PROPERTY_CMD, {.func_double_ptr = WYZE_iot3_0_device_purifier_callback}, WYZE_IOT_FUNC_LIST_PARAM_DOUBLE},
    {"camera::resolution", WYZE_IOT_GET_PROPERTY_CMD, {.func_get_info_ptr = WYZE_iot3_0_get_cam_resolution_callback}, WYZE_IOT_FUNC_LIST_PARAM_CHAR},
    {"iot-device::iot-power", WYZE_IOT_GET_PROPERTY_CMD,{.func_get_info_ptr = WYZE_iot3_0_get_iot_device_power_callback}, WYZE_IOT_FUNC_LIST_PARAM_BOOL},
    {"camera::temperature", WYZE_IOT_GET_PROPERTY_CMD, {.func_get_info_ptr = WYZE_iot3_0_get_cam_temp_callback}, WYZE_IOT_FUNC_LIST_PARAM_DOUBLE},
    {"iot-device::submit-log", WYZE_IOT_ACTION_TYPE_CMD, {.func_action_ptr = WYZE_iot3_0_run_action_submit_log}, WYZE_IOT_FUNC_LIST_PARAM_ACTION},
    {"lock::get-one-time-code", WYZE_IOT_ACTION_TYPE_CMD, {.func_action_ptr = WYZE_iot3_0_sync_action_get_one_time_code}, WYZE_IOT_FUNC_LIST_PARAM_ACTION},
    {"lock::add-one-time-code", WYZE_IOT_ACTION_TYPE_CMD, {.func_action_ptr = WYZE_iot3_0_sync_action_add_one_time_code}, WYZE_IOT_FUNC_LIST_PARAM_ACTION},
    {"lock::schedule-lock-time", WYZE_IOT_SET_PROPERTY_CMD, {.func_string_ptr = WYZE_iot3_0_schedule_lock_time_callback}, WYZE_IOT_FUNC_LIST_PARAM_CHAR},
    {"lock::schedule-lock-mode", WYZE_IOT_SET_PROPERTY_CMD, {.func_bool_ptr = WYZE_iot3_0_schedule_lock_mode_callback}, WYZE_IOT_FUNC_LIST_PARAM_BOOL},
    {"iot-device::upgrade-2", WYZE_IOT_ACTION_TYPE_CMD, {.func_action_ptr = WYZE_iot3_0_upgrade}, WYZE_IOT_FUNC_LIST_PARAM_ACTION},
#endif
#if 1//模块间调用 keep_alive 使用
    {"iot-device::log-level", WYZE_IOT_SET_PROPERTY_CMD, {.func_int_ptr = WYZE_iot3_0_set_log_level_callback}, WYZE_IOT_FUNC_LIST_PARAM_INT},
    {"iot-device::wakeup", WYZE_IOT_ACTION_TYPE_CMD, {.func_action_ptr = WYZE_iot3_0_run_action_wakeup_callback}, WYZE_IOT_FUNC_LIST_PARAM_ACTION},
    {"iot-device::server-migration", WYZE_IOT_ACTION_TYPE_CMD, {.func_action_ptr = WYZE_iot3_0_run_action_server_migration}, WYZE_IOT_FUNC_LIST_PARAM_ACTION},
#endif //end keep_alive
};

#ifdef __cplusplus
}
#endif
#endif