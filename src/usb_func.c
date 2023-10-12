
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
	}
	tud_cdc_n_write_str(0, str);
}

//--------------------------------------------------------------------+
// Device callbacks
//--------------------------------------------------------------------+

// // Invoked when device is mounted
// void tud_mount_cb(void) {
// }

// // Invoked when device is unmounted
// void tud_umount_cb(void) {
// }

// // Invoked when usb bus is suspended
// // remote_wakeup_en : if host allow us  to perform remote wakeup
// // Within 7ms, device must draw an average of current less than 2.5 mA from bus
// void tud_suspend_cb(bool remote_wakeup_en) {
// 	(void)remote_wakeup_en;
// }

// // Invoked when usb bus is resumed
// void tud_resume_cb(void) {
// 	//   blink_interval_ms = tud_mounted() ? BLINK_MOUNTED : BLINK_NOT_MOUNTED;
// }

// //--------------------------------------------------------------------+
// // USB HID
// //--------------------------------------------------------------------+

// // Invoked when received GET_REPORT control request
// // Application must fill buffer report's content and return its length.
// // Return zero will cause the stack to STALL request
// uint16_t tud_hid_get_report_cb(uint8_t itf, uint8_t report_id, hid_report_type_t report_type, uint8_t* buffer, uint16_t reqlen) {
// 	// TODO not Implemented
// 	(void)itf;
// 	(void)report_id;
// 	(void)report_type;
// 	(void)buffer;
// 	(void)reqlen;

// 	return 0;
// }

// // Invoked when received SET_REPORT control request or
// // received data on OUT endpoint ( Report ID = 0, Type = 0 )
// void tud_hid_set_report_cb(uint8_t itf, uint8_t report_id, hid_report_type_t report_type, uint8_t const* buffer, uint16_t bufsize) {
// 	// This example doesn't use multiple report and report ID
// 	(void)itf;
// 	(void)report_id;
// 	(void)report_type;

// 	// echo back anything we received from host
// 	tud_hid_report(0, buffer, bufsize);
// }
