
include(${CMAKE_CURRENT_LIST_DIR}/../../../../lib/darkstar_file_paths.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/../../../../third-party/third-party.cmake)
idf_component_register(SRCS ${DARKSTAR_SOURCES} ${THIRD_PARTY_SOURCES}
                      INCLUDE_DIRS ${DARKSTAR_PUBLIC_INCLUDE_DIRS} ${DARKSTAR_PRIVATE_INCLUDE_DIRS} ${THIRD_PARTY_INCLUDE_DIRS}
                      REQUIRES esp_timer mbedtls)
idf_component_get_property(target iot_v3 COMPONENT_LIB)
target_compile_definitions(${target} PRIVATE DWYZE_ARCH=2 DWYZE_ENABLE_LWIP=1)