#ifndef _CDC_H_
#define _CDC_H_
#include <stdint.h>

void cdc_task(void);
void cdc_log_print(char* str);
void cdc_data_write(uint8_t buf[], uint32_t count);

#endif
