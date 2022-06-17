#include <kernel/kernel.h>
#include <libc/libc.h>

#include "cpu.h"

static uint8_t _reg_century = 0;
static bool_t  _update_flag();

void rtc_init() {
    idt_register_entry(RTC_IRQ_VECT, rtc_irq);
}

void rtc_read(datetime_t* dt) {
    while (_update_flag());

    dt->year   = port_byte_in(PORT_RTC_YEAR) +
                 (_reg_century != 0 ? port_byte_in(_reg_century) : 20) * 10;
    dt->month  = port_byte_in(PORT_RTC_MONTH);
    dt->day    = port_byte_in(PORT_RTC_DAY);
    dt->hour   = port_byte_in(PORT_RTC_HOUR);
    dt->minute = port_byte_in(PORT_RTC_MINUTE);
    dt->second = port_byte_in(PORT_RTC_SECOND);
}

void rtc_inc(datetime_t* dt) {
    dt->second++;

    if (dt->second == 60) {
        dt->second = 0;
        dt->minute++;
    }
    else
        return;

    if (dt->minute == 60) {
        dt->minute = 0;
        dt->hour++;
    }
    else
        return;
    
    if (dt->hour == 24) {
        dt->hour = 0;
        dt->day++;
    }

    if (
        (dt->month == 2 && dt->day == (dt->year % 4 ? 29 : 30)) ||
        (dt->month != 2 && dt->day == (dt->month % 2 ? 32 : 31))
    ) {
        dt->day = 1;
        dt->month++;
    }

    if (dt->month == 13) {
        dt->month = 1;
        dt->year++;
    }
}

void rtc_irq_handler() {
    if (k_dt.year == 0)
        rtc_read(&k_dt);
    else
        rtc_inc(&k_dt);

    pic_send_eoi(0x20 - RTC_IRQ_VECT);
}

static bool_t _update_flag() {
    port_byte_out(PORT_CMOS_CTRL, 0xA);
    return port_byte_in(PORT_CMOS_DATA);
}