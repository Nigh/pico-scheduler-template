
#include "tusb.h"
#include "tusb_config.h"

#include "string.h"

void cdc_task(void) {
	uint8_t itf;
	for(itf = 0; itf < CFG_TUD_CDC; itf++) {
		if(tud_cdc_n_available(itf)) {
			uint8_t buf[64];
			uint32_t count = tud_cdc_n_read(itf, buf, sizeof(buf));
		}
	}
}

static void serial_write(uint8_t itf, uint8_t buf[], uint32_t count) {
	if(tud_cdc_n_write_available(itf) < count) {
		tud_cdc_n_write_flush(itf);
	}
	tud_cdc_n_write(itf, buf, count);
}

void cdc_log_print(char* str) {
	uint16_t len = strlen(str);
	if(tud_cdc_n_write_available(0) < len) {
		tud_cdc_n_write_flush(0);
		tud_cdc_n_write_str(0, "@");
	}
	tud_cdc_n_write_str(0, str);
}

void cdc_data_write(uint8_t buf[], uint32_t count) {
	serial_write(1, buf, count);
}
