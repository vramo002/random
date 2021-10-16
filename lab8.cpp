#include "chu_init.h"
#include "gpio_cores.h"
#include "xadc_core.h"


void chasing_leds(GpoCore *led_p, GpiCore *sw_p, XadcCore *adc_p, int n){
	int i, s, a;
	int temp;
	int j = n - 1;

	if(sw_p->read() & 0x0001){
			s = (adc_p->read_adc_in(0) * 500) + 50;
			if (temp != s){
				uart.disp("current speed: ");
				uart.disp(int(s));
				uart.disp("\n\r");
			}
			temp = s;
			for (i = 0; i < ((n*2) - 2); i++) {
				if (i >= n)
				{
					j = j - 1;
				}
				if(sw_p->read() & 0x0001){
					s = (adc_p->read_adc_in(0) * 500) + 50;
					if (temp != s){
						uart.disp("current speed: ");
						uart.disp(int(s));
						uart.disp("\n\r");
					}
					if(i < n)
					{
						a = i;
					}
					else
						a = j;
					led_p->write(1, a);
					sleep_ms(s);
					led_p->write(0, a);
					sleep_ms(s);
					temp = s;
				}
			}
		}
}

GpoCore led(get_slot_addr(BRIDGE_BASE, S2_LED));
GpiCore sw(get_slot_addr(BRIDGE_BASE, S3_SW));
XadcCore adc(get_slot_addr(BRIDGE_BASE, S5_XDAC));

int main() {
   while (1) {
	   chasing_leds(&led, &sw, &adc, 16);
   } //while
} //main

