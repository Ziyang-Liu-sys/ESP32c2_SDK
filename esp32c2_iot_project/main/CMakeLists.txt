

idf_component_register(SRCS "station_example_main.c" "ping/ping.c" "iot/wyze_iot.c" "iot/user/wyze_iot3_0_callback.c"
                    PRIV_REQUIRES esp_wifi nvs_flash fatfs lwip esp_timer mbedtls json console iot_v3
                    INCLUDE_DIRS "." "ping" "iot" "iot/user" )


