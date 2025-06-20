在develop分支下 有个esp32c2文件夹放到第三方库的cmake文件夹下即可
另外lib/util/util.c 下的wyze_number_to_str函数需要做如下更改
void wyze_number_to_str(char* dest, int length, uint32_t number) {
#if WYZE_ARCH == WYZE_ARCH_UNIX && defined(__APPLE__)
    snprintf(dest, length, "%" PRIu64, number);
#elif (WYZE_ARCH == WYZE_ARCH_FREERTOS) || (WYZE_ARCH == WYZE_ARCH_ESP32)
    snprintf(dest, length, "%ld", number);  // MCU :lld, x86:ld
    printf("*******************%ld",number);
    // snprintf(dest, length, "%"PRIu64, number);
#else
    snprintf(dest, length, "%" PRIu64, number);
#endif
}
