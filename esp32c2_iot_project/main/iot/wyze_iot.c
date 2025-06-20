#include "wyze-iot/wyze-iot-v3.h"
#include "wyze_iot_function_list.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include <string.h>

#include "wyze_iot3_0_callback.h"
#include <time.h>

static int flag = 0;
static void* global_iot_handler = NULL;
struct user_struct user;
SemaphoreHandle_t IOT3_0_MUTEX;

struct user_struct *user_ptr = NULL;
#define FIRMWARE_VERSION "1.0.0.0"
#define HARDWARE_VERSION "3.0.0.0"

// 用户需要实现，此函数名字的实现。
#define user_define_message                                                           \
    "{\"cmd\":\"update_state\",\"ts\":1732871002000,\"tid\":191,\"props\":{"   \
    "\"lock::beep-volume\":60,\"lock::alarm-volume\":60}}"
int32_t WYZE_wakeUp_Callback(long rtc_uid, const char* rtc_token) {
    printf("  User's wake-up callback function !!!  \r\n");
    printf("*****rtc_uid = %ld rtc_token = %s\r\n", rtc_uid, rtc_token);
#if 0
    wyze_iot_user_defined_message_send(global_iot_handler,
                                           "wyze/WZ_DEV/WZ_DEV_000000000003/state",
                                           strlen("wyze/WZ_DEV/WZ_DEV_000000000003/state"),
                                           user_define_message,
                                           strlen(user_define_message),
                                           1);
    wyze_iot_logger_level_upload(global_iot_handler,
                                 "WZ_DEV",
                                 "WZ_DEV_000000000003",
                                 WYZE_LOGGER_INFO);

    wyze_iot_logger_upload(global_iot_handler,
                           "WZ_DEV",
                           "WZ_DEV_000000000003",
                           WYZE_LOGGER_CRITICAL,
                           "xsf xsf",
                           strlen("xsf xsf"));

    wyze_iot3_0_update_battery_level(global_iot_handler,
                                         "WZ_DEV",
                                         "WZ_DEV_000000000003",
                                         50);
    wyze_iot3_0_update_lock_event(global_iot_handler,
                                      "WZ_DEV",
                                      "WZ_DEV_000000000003",
                                      1,
                                      "xsf_test");
    wyze_iot3_0_report_metrics(global_iot_handler,
                                     "WZ_DEV",
                                     "WZ_DEV_000000000003",
                                     2,
                                     "metrics str");
#endif
#if 1
    int32_t pub_id;
    pub_id = wyze_iot_wakeup_ack(((struct user_struct*)user_ptr)->iot_handler,
                                 1,
                                 2,
                                 3,
                                 4,
                                 -99);
    printf("*******2**** %s  %ld\n", __func__, pub_id);
    // pub_id = wyze_iot_firmware_version_upload(
    //     ((struct user_struct*)user_ptr)->iot_handler,
    //     "1.0.0",
    //     strlen("1.0.0"),
    //     "2.0.0",
    //     strlen("2.0.0"));
    // printf("******3***** %s  %ld\n", __func__, pub_id);

    wyze_iot_device_state_t device_state = {0};
    device_state.device_state            = WYZE_IOT_DEVICE_STATE_AWAKE;
    device_state.wakeup_reason           = WYZE_IOT_DEVICE_ERROR;
    pub_id                               = wyze_iot_device_state_upload(
        ((struct user_struct*)user_ptr)->iot_handler,
        &device_state);
    printf("*****4****** %s  %ld\n", __func__, pub_id);

    pub_id = wyze_iot_keep_alive_logger_level_upload(
        ((struct user_struct*)user_ptr)->iot_handler);
    printf("******5***** %s  %ld\n", __func__, pub_id);

    pub_id = wyze_iot_update_battery_level(
        ((struct user_struct*)user_ptr)->iot_handler,
        20);
    printf("******6***** %s  %ld\n", __func__, pub_id);

    pub_id = wyze_iot_battery_power_source(
        ((struct user_struct*)user_ptr)->iot_handler,
        WYZE_BATTERY_POWER_SOURCE_AC_MODE);

    printf("******7***** %s  %ld\n", __func__, pub_id);
    pub_id = wyze_iot_battery_low_battery(
        ((struct user_struct*)user_ptr)->iot_handler);
    printf("*****8****** %s  %ld\n", __func__, pub_id);

    pub_id = wyze_iot_wifi_signal_strength(
        ((struct user_struct*)user_ptr)->iot_handler,
        -90);
    printf("******9***** %s  %ld\n", __func__, pub_id);

#if 1  /// 日志上报有限制    1.log 等级限制  2. qos 0限制
    wyze_iot_device_log_upload(
        ((struct user_struct*)user_ptr)->iot_handler,
        WYZE_LOGGER_INFO,
        1,
        2000,
        0,
        "info",
        strlen("info"),
        "test module",
        strlen("test module"));

    wyze_iot_device_log_upload(
        ((struct user_struct*)user_ptr)->iot_handler,
        WYZE_LOGGER_CRITICAL,
        1,
        2000,
        0,
        "critical",
        strlen("critical"),
        "test module",
        strlen("test module"));
#endif

#endif
#if 0
    device_state.device_state = WYZE_IOT_DEVICE_STATE_SLEEP;
    device_state.awake_time   = 10;
    pub_id                    = wyze_iot_device_state_upload(
        ((struct user_struct*)user_ptr)->iot_handler,
        &device_state);
    printf("*****12****** %s  %d\n", __func__, pub_id);

    wyze_iot_message_struct_t metrics_struct[4] = {0};
        {
            metrics_struct[0].props      = "date";
            metrics_struct[0].props_mode = WYZE_IOT_PARAM_INT;
            metrics_struct[0].value      = (int64_t)1645111657;

            metrics_struct[1].props      = "offline_times";
            metrics_struct[1].props_mode = WYZE_IOT_PARAM_INT;
            metrics_struct[1].value      = 1;

            metrics_struct[2].props      = "offline_duration";
            metrics_struct[2].props_mode = WYZE_IOT_PARAM_INT;
            metrics_struct[2].value      = 30;

            metrics_struct[3].props      = "reboot_times";
            metrics_struct[3].props_mode = WYZE_IOT_PARAM_INT;
            metrics_struct[3].value      = 1;

        }

    wyze_iot_daily_metric(global_iot_handler,
                              metrics_struct,
                              4);

    wyze_iot_ring_doorbell(global_iot_handler);
#endif
    return 0;
}

// note: 使用不同的设备进行测试
static void WYZE_state_Callback(int32_t state, void* data, void *user_ptr) {
    (void)data;
    //printf("received state = %d\r\n", state);
    if ((state == WYZE_IOT_CLOSE)) {
        //low_power_exit(0);
        //printf("************************************* exit tickless \r\n");
    }

    if ((state == WYZE_IOT_DISCONNECTED)) {
        printf("************************************* iot disconnected\r\n");
    }

    if (state == WYZE_IOT_CONNECTED) {
        wyze_iot_subscribe_keepalive_topic(global_iot_handler, "WZ_DEV", "WZ_DEV_000000000003");
        //wyze_iot_subscription_user_defined(global_iot_handler,
        //                                   "wyze/WZ_DEV/WZ_DEV_000000000003/keep-alive",
        //                                   strlen("wyze/WZ_DEV/WZ_DEV_000000000003/keep-alive"));
        //wyze_iot_subscribe_iot_v3_topic(global_iot_handler, "WZ_DEV", "WZ_DEV_000000000003");
#if 0
        wyze_iot_firmware_version_upload(global_iot_handler,
                                         FIRMWARE_VERSION,
                                         strlen(FIRMWARE_VERSION),
                                         HARDWARE_VERSION,
                                         strlen(HARDWARE_VERSION));
#endif
#if 0
        low_power_enter(LOW_POWER_LEVEL);
        printf("************************************* enter tickless mode\r\n");
#endif
    }
    if (state == WYZE_IOT_DELAYING) {
        //uint32_t delay_time = (uint32_t)data;
        //printf("************************************* iot delay %d\r\n",
        //       delay_time);
        //printf("************************************* enter iot lowpower\r\n");
        //low_power_enter(LOW_POWER_LEVEL);
    }
    
    if (state == WYZE_IOT_EXIT_DELAY) {
        //printf("************************************* exit iot lowpower\r\n");
        //low_power_exit(0);
    }
    return;
}

static void t_pfn_stdout(char c, void* param) {
    printf("%c", c);
    (void)param;
}

#define INIT_STACK_SIZE (2048)
#define INIT_TASK_PRIORITY (16)

/**
 * @brief Retrieves the current timestamp in milliseconds since the system started.
 * 
 * This function calculates the timestamp based on the FreeRTOS tick count
 * and the tick period in milliseconds.
 * 
 * @return uint64_t The timestamp in milliseconds.
 */
uint64_t get_timestamp(void) {
    TickType_t xTickCount;
    xTickCount = xTaskGetTickCount();

    return (uint64_t)xTickCount * portTICK_PERIOD_MS;
}

void get_local_time(void)
{
    uint64_t timestamp_ms = 1633072800123;
       // 转换为秒级时间戳
    time_t timestamp_sec = timestamp_ms / 1000;

    // 获取 UTC 时间
    struct tm *utc_time = localtime(&timestamp_sec);

    // 格式化为可读的字符串
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S UTC", utc_time);

    printf("UTC time: %s\r\n", buffer);
#if 0
    int day_of_week = utc_time->tm_wday;  // 获取星期几
    // 将数字转换为星期几的字符串
    const char *days_of_week[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
    printf("%s.\n", days_of_week[day_of_week]);
#endif
}

uint32_t get_random_cb(void) {
    // 生成一个随机数
    int random_num = rand();
    // 将随机数转换为uint32_t类型
    uint32_t random_uint32 = (uint32_t)random_num;
    return random_uint32;
}
void iot_event_handler(wyze_iot_event_result_t result, void *user_ptr) {
    (void)user_ptr;
#if 1
    printf("********iot_event_handler****** %d, %d\r\n", result.message_id,
        result.result_code);
#endif
}

void low_power_test(void);
void destroy_iot(void)
{
    flag = 1;
}
void iot_set_network_state(uint8_t state)
{
    if(state){
        printf("************set iot network state on\r\n");
        wyze_iot_set_network_state(global_iot_handler, WYZE_IOT_NETWORK_STATE_ON);
    }else{
        printf("************set iot network state off\r\n");
        wyze_iot_set_network_state(global_iot_handler, WYZE_IOT_NETWORK_STATE_OFF);
    }
}
void connection_manager_static_ip_bk_callback(const char *array_str, size_t len)
{
    printf("connection manager backup ip\r\n");
    printf("%.*s\r\n", (int)len, array_str);
}

WYZE_TM local_time(void) {
    WYZE_TM tm;

    tm.tm_sec   = 0;
    tm.tm_min   = 0;
    tm.tm_hour  = 10;
    tm.tm_mday  = 20;
    tm.tm_mon   = 3;
    tm.tm_year  = 2025 - 1970;
    tm.tm_wday  = 5;
    tm.tm_yday  = 100;
    tm.tm_isdst = 0;
    return tm;
}

int wyze_iot() {
#if 1
    flag = 0;
    //    IOT3_0_MUTEX = xSemaphoreCreateMutex();
    wyze_iot_params params = WYZE_IOT_PARAMS_INIT;
    params.device_params.device_id = "WZ_DEV_000000000003";
    params.device_params.client_id = "WZ_DEV_000000000003";
    params.device_params.device_model = "WZ_DEV";
    //params.device_params.auth_key = "12345678123456781234567812345678";
    params.device_params.auth_key         = "4009a3a7151f4837b23bf28d77d8c497";
    params.device_params.firmware_version = FIRMWARE_VERSION;
    params.device_params.hardware_version = HARDWARE_VERSION;
    params.config_params.keep_alive_interval_default = 30;
    params.config_params.keep_alive_interval_timeout = 15;
    params.user_params.iot_state_callback = WYZE_state_Callback;
    params.user_params.current_time_ms_callback = get_timestamp;
    params.user_params.get_random_cb_callback = get_random_cb;
    params.user_params.iot_event_handler_callback = iot_event_handler;
    params.user_params.log_level = WYZE_IOT_LOG_LEVEL_INFO;
    params.user_params.log_callback = t_pfn_stdout;
    params.user_params.is_crypto_data = false;
#if 1
    params.user_params.message_callback = wyze_iot_router;
    params.user_params.function_list              = (void*)func_list;
    params.user_params.function_list_num =
        sizeof(func_list) / sizeof(wyze_iot_function_list);
#endif
    params.user_params.cm_bk_ip_callback = connection_manager_static_ip_bk_callback;
    //params.user_params.backup_cm_ip        = "[\"54.245.3.89\",\"34.218.106.9\"]";
    params.user_params.upgrade_testcode = "Official Version";
    params.user_params.local_time_ms_callback   = local_time;
    params.user_params.server_ver = WYZE_IOT_SERVER_BETA_VER;
    struct user_struct user;
    user_ptr = &user;
    void* iot_handler = wyze_iot_single_create(&params, &user);
    user.iot_handler = iot_handler;
    global_iot_handler = iot_handler;
    wyze_iot_set_network_state(iot_handler, WYZE_IOT_NETWORK_STATE_ON);
    //printf("heap free space size: %d bytes\r\n", xPortGetFreeHeapSize());
    while (1) {
        wyze_iot_poll(iot_handler);

        if(flag == 1){
            flag = 0;
            printf("***************break\r\n");
            break;
        }
    }
    wyze_iot_destroy(iot_handler);
    iot_handler = NULL;
#endif
    return 0;
}
