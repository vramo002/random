/*****************************************************************//**
 * @file main_sampler_test.cpp
 *
 * @brief Basic test of nexys4 ddr mmio cores
 *
 * @author p chu
 * @version v1.0: initial release
 *********************************************************************/

// #define _DEBUG
#include "chu_init.h"
#include "gpio_cores.h"
#include "xadc_core.h"
#include "sseg_core.h"
#include "spi_core.h"
#include "i2c_core.h"
#include "ps2_core.h"
#include "ddfs_core.h"
#include "adsr_core.h"

void spectrum_display(PwmCore *pwm_p, XadcCore *adc_p, SsegCore *sseg_p, GpiCore *sw_p) {
  double bright, duty;

  pwm_p->set_freq(50);
  //display number by breaking it apart
  int num = adc_p->read_adc_in(0) * 1000; //convert to from dec to whole number
  int tenths = num/100;
  num = num%100;
  int hundredths = num/10;
  int thousandths = num%10;
  for (int i = 0; i < 8; i++) {
        sseg_p->write_1ptn(0xff, i);
     }
  sseg_p->set_dp(0x08); //display decimal point
  //each number display
  sseg_p->write_1ptn(sseg_p->h2s(tenths), 2);
  sseg_p->write_1ptn(sseg_p->h2s(hundredths), 1);
  sseg_p->write_1ptn(sseg_p->h2s(thousandths), 0);
  //0.001v - 0.166v
  if(adc_p->read_adc_in(0) < 0.167){
	  	  //convert 0.001v - 0.166v to 1 - 99 range to determine the brightness
		  bright = (((adc_p->read_adc_in(0) - 0.001) * (99 - 1))/(0.166 - 0.001)) + 1;
		  duty = bright / 100.0;
		  //set each rgb on both leds
		  if(sw_p->read() & 0x0001 && sw_p->read() & 0x0002)
		  {
			  pwm_p->set_duty(0, 0);
			  pwm_p->set_duty(duty, 1);
			  pwm_p->set_duty(.99, 2);
			  pwm_p->set_duty(0, 3);
			  pwm_p->set_duty(duty, 4);
			  pwm_p->set_duty(.99, 5);
		  }
		  else if(sw_p->read() & 0x0002)
		  {
			  pwm_p->set_duty(0, 0);
			  pwm_p->set_duty(0, 1);
			  pwm_p->set_duty(0, 2);
			  pwm_p->set_duty(0, 3);
			  pwm_p->set_duty(duty, 4);
			  pwm_p->set_duty(.99, 5);
		  }
		  else if(sw_p->read() & 0x0001)
		  {
			  pwm_p->set_duty(0, 0);
			  pwm_p->set_duty(duty, 1);
			  pwm_p->set_duty(.99, 2);
			  pwm_p->set_duty(0, 3);
			  pwm_p->set_duty(0, 4);
			  pwm_p->set_duty(0, 5);
		  }
		  else
		  {
			  pwm_p->set_duty(0, 0);
			  pwm_p->set_duty(duty, 1);
			  pwm_p->set_duty(.99, 2);
			  pwm_p->set_duty(0, 3);
			  pwm_p->set_duty(duty, 4);
			  pwm_p->set_duty(.99, 5);
		  }

		  /*pwm_p->set_duty(0, 0);
		  pwm_p->set_duty(duty, 1);
		  pwm_p->set_duty(.99, 2);
		  pwm_p->set_duty(0, 3);
		  pwm_p->set_duty(duty, 4);
		  pwm_p->set_duty(.99, 5);*/
		  sleep_ms(100);
  }
  //0.167v - 0.333v
  else if(adc_p->read_adc_in(0) >= 0.167 && adc_p->read_adc_in(0) < 0.334){
	  	  //convert 0.167v - 0.333v to 1 - 99 range to determine the brightness
  		  bright = (((adc_p->read_adc_in(0) - 0.167) * (1 - 99))/(0.333 - 0.167)) + 99;
  		  duty = bright / 100.0;
  		  //set each rgb on both leds
  		if(sw_p->read() & 0x0001 && sw_p->read() & 0x0002)
  		{
			pwm_p->set_duty(0, 0);
			pwm_p->set_duty(.99, 1);
			pwm_p->set_duty(duty, 2);
			pwm_p->set_duty(0, 3);
			pwm_p->set_duty(.99, 4);
			pwm_p->set_duty(duty, 5);
  		}
  		else if(sw_p->read() & 0x0002)
		{
			pwm_p->set_duty(0, 0);
			pwm_p->set_duty(0, 1);
			pwm_p->set_duty(0, 2);
			pwm_p->set_duty(0, 3);
			pwm_p->set_duty(.99, 4);
			pwm_p->set_duty(duty, 5);
		}
  		else if(sw_p->read() & 0x0001)
		{
			pwm_p->set_duty(0, 0);
			pwm_p->set_duty(.99, 1);
			pwm_p->set_duty(duty, 2);
			pwm_p->set_duty(0, 3);
			pwm_p->set_duty(0, 4);
			pwm_p->set_duty(0, 5);
		}
  		else
  		{
			pwm_p->set_duty(0, 0);
			pwm_p->set_duty(.99, 1);
			pwm_p->set_duty(duty, 2);
			pwm_p->set_duty(0, 3);
			pwm_p->set_duty(.99, 4);
			pwm_p->set_duty(duty, 5);
  		}
  		  sleep_ms(100);
  }
  //0.334v - 0.499
  else if(adc_p->read_adc_in(0) >= 0.334 && adc_p->read_adc_in(0) < 0.5){
	  	  //convert 0.334v - 0.499 to 1 - 99 range to determine the brightness
		  bright = (((adc_p->read_adc_in(0) - 0.334) * (99 - 1))/(0.499 - 0.334)) + 1;
		  duty = bright / 100.0;
		  //set each rgb on both leds
		  if(sw_p->read() & 0x0001 && sw_p->read() & 0x0002)
		  {
			  pwm_p->set_duty(duty, 0);
			  pwm_p->set_duty(.99, 1);
			  pwm_p->set_duty(0, 2);
			  pwm_p->set_duty(duty, 3);
			  pwm_p->set_duty(.99, 4);
			  pwm_p->set_duty(0, 5);
		  }
		  else if(sw_p->read() & 0x0002)
		  {
			  pwm_p->set_duty(0, 0);
			  pwm_p->set_duty(0, 1);
			  pwm_p->set_duty(0, 2);
			  pwm_p->set_duty(duty, 3);
			  pwm_p->set_duty(.99, 4);
			  pwm_p->set_duty(0, 5);
		  }
		  else if(sw_p->read() & 0x0001)
		  {
			  pwm_p->set_duty(duty, 0);
			  pwm_p->set_duty(.99, 1);
			  pwm_p->set_duty(0, 2);
			  pwm_p->set_duty(0, 3);
			  pwm_p->set_duty(0, 4);
			  pwm_p->set_duty(0, 5);
		  }
		  else
		  {
			  pwm_p->set_duty(duty, 0);
			  pwm_p->set_duty(.99, 1);
			  pwm_p->set_duty(0, 2);
			  pwm_p->set_duty(duty, 3);
			  pwm_p->set_duty(.99, 4);
			  pwm_p->set_duty(0, 5);
		   }
		  sleep_ms(100);
  }
  //0.5v - 0.666v
  else if(adc_p->read_adc_in(0) >= 0.5 && adc_p->read_adc_in(0) < 0.667){
	  	  //convert 0.5v - 0.666v to 1 - 99 range to determine the brightness
		  bright = (((adc_p->read_adc_in(0) - 0.5) * (1 - 99))/(0.666 -  0.5)) + 99;
		  duty = bright / 100.0;
		  //set each rgb on both leds
		  if(sw_p->read() & 0x0001 && sw_p->read() & 0x0002)
		  {
			  pwm_p->set_duty(.99, 0);
			  pwm_p->set_duty(duty, 1);
			  pwm_p->set_duty(0, 2);
			  pwm_p->set_duty(.99, 3);
			  pwm_p->set_duty(duty, 4);
			  pwm_p->set_duty(0, 5);
		  }
		  else if(sw_p->read() & 0x0002)
		  {
			  pwm_p->set_duty(0, 0);
			  pwm_p->set_duty(0, 1);
			  pwm_p->set_duty(0, 2);
			  pwm_p->set_duty(.99, 3);
			  pwm_p->set_duty(duty, 4);
			  pwm_p->set_duty(0, 5);
		  }
		  else if(sw_p->read() & 0x0001)
		  {
			  pwm_p->set_duty(.99, 0);
			  pwm_p->set_duty(duty, 1);
			  pwm_p->set_duty(0, 2);
			  pwm_p->set_duty(0, 3);
			  pwm_p->set_duty(0, 4);
			  pwm_p->set_duty(0, 5);
		  }
		  else
		  {
			  pwm_p->set_duty(.99, 0);
			  pwm_p->set_duty(duty, 1);
			  pwm_p->set_duty(0, 2);
			  pwm_p->set_duty(.99, 3);
			  pwm_p->set_duty(duty, 4);
			  pwm_p->set_duty(0, 5);
		  }


		  sleep_ms(100);
  }
  //0.667v - 0.833v
  else if(adc_p->read_adc_in(0) >= 0.667 && adc_p->read_adc_in(0) < 0.834){
	  	  //convert 0.667v - 0.833v to 1 - 99 range to determine the brightness
  		  bright = (((adc_p->read_adc_in(0) - 0.667) * (99 - 1))/(0.834 - 0.667)) + 1;
  		  duty = bright / 100.0;
  		  //set each rgb on both leds
		  if(sw_p->read() & 0x0001 && sw_p->read() & 0x0002)
		  {
	  		  pwm_p->set_duty(.99, 0);
	  		  pwm_p->set_duty(0, 1);
	  		  pwm_p->set_duty(duty, 2);
	  		  pwm_p->set_duty(.99, 3);
			  pwm_p->set_duty(0, 4);
			  pwm_p->set_duty(duty, 5);
		  }
		  else if(sw_p->read() & 0x0002)
		  {
	  		  pwm_p->set_duty(0, 0);
	  		  pwm_p->set_duty(0, 1);
	  		  pwm_p->set_duty(0, 2);
	  		  pwm_p->set_duty(.99, 3);
			  pwm_p->set_duty(0, 4);
			  pwm_p->set_duty(duty, 5);
		  }
		  else if(sw_p->read() & 0x0001)
		  {
	  		  pwm_p->set_duty(.99, 0);
	  		  pwm_p->set_duty(0, 1);
	  		  pwm_p->set_duty(duty, 2);
	  		  pwm_p->set_duty(0, 3);
			  pwm_p->set_duty(0, 4);
			  pwm_p->set_duty(0, 5);
		  }
		  else
		  {
	  		  pwm_p->set_duty(.99, 0);
	  		  pwm_p->set_duty(0, 1);
	  		  pwm_p->set_duty(duty, 2);
	  		  pwm_p->set_duty(.99, 3);
			  pwm_p->set_duty(0, 4);
			  pwm_p->set_duty(duty, 5);
		  }

  		  sleep_ms(100);
  }
  //0.834v - 1v
  else if(adc_p->read_adc_in(0) >= 0.834 && adc_p->read_adc_in(0) <= 1){
	  	  //convert 0.834v - 1v to 1 - 99 range to determine the brightness
		  bright = (((adc_p->read_adc_in(0) - 0.834) * (1 - 99))/(1 -  0.834)) + 99;
		  duty = bright / 100.0;
		  //set each rgb on both leds
		  if(sw_p->read() & 0x0001 && sw_p->read() & 0x0002)
		  {
			  pwm_p->set_duty(duty, 0);
			  pwm_p->set_duty(0, 1);
			  pwm_p->set_duty(.99, 2);
			  pwm_p->set_duty(duty, 3);
			  pwm_p->set_duty(0, 4);
			  pwm_p->set_duty(.99, 5);
		  }
		  else if(sw_p->read() & 0x0002)
		  {
			  pwm_p->set_duty(0, 0);
			  pwm_p->set_duty(0, 1);
			  pwm_p->set_duty(0, 2);
			  pwm_p->set_duty(duty, 3);
			  pwm_p->set_duty(0, 4);
			  pwm_p->set_duty(.99, 5);
		  }
		  else if(sw_p->read() & 0x0001)
		  {
			  pwm_p->set_duty(duty, 0);
			  pwm_p->set_duty(0, 1);
			  pwm_p->set_duty(.99, 2);
			  pwm_p->set_duty(0, 3);
			  pwm_p->set_duty(0, 4);
			  pwm_p->set_duty(0, 5);
		  }
		  else
		  {
			  pwm_p->set_duty(duty, 0);
			  pwm_p->set_duty(0, 1);
			  pwm_p->set_duty(.99, 2);
			  pwm_p->set_duty(duty, 3);
			  pwm_p->set_duty(0, 4);
			  pwm_p->set_duty(.99, 5);
		  }

		  sleep_ms(100);
  }
}

void gsensor_check(SpiCore *spi_p, GpoCore *led_p) {
   const uint8_t RD_CMD = 0x0b;
   const uint8_t PART_ID_REG = 0x02;
   const uint8_t DATA_REG = 0x08;
   const float raw_max = 127.0 / 2.0;  //128 max 8-bit reading for +/-2g

   int8_t xraw, yraw, zraw;
   float x, y, z;
   int id;

   spi_p->set_dc(0);
   spi_p->set_res(1);
   spi_p->set_vccen(0);
   spi_p->set_pmoden(1);
   sleep_ms(20);
   spi_p->set_res(0);
   sleep_us(3);
   spi_p->set_res(1);
   sleep_us(3);
   //for(;;);

   spi_p->set_freq(400000);
   spi_p->set_mode(1, 1);
   // check part id
   spi_p->assert_ss(0);    // activate
   spi_p->transfer(0xFD);  // for read operation
   spi_p->transfer(0x12);
   spi_p->transfer(0xAE);
   spi_p->transfer(0xA0);
   spi_p->transfer(0x72);
   /*spi_p->transfer(PART_ID_REG);  // part id address
   id = (int) spi_p->transfer(0x00);
   spi_p->deassert_ss(0);
   uart.disp("read ADXL362 id (should be 0xf2): ");
   uart.disp(id, 16);
   uart.disp("\n\r");*/

}

GpoCore led(get_slot_addr(BRIDGE_BASE, S2_LED));
GpiCore sw(get_slot_addr(BRIDGE_BASE, S3_SW));
XadcCore adc(get_slot_addr(BRIDGE_BASE, S5_XDAC));
PwmCore pwm(get_slot_addr(BRIDGE_BASE, S6_PWM));
SsegCore sseg(get_slot_addr(BRIDGE_BASE, S8_SSEG));
SpiCore spi(get_slot_addr(BRIDGE_BASE, S9_SPI));

int main() {
   //uint8_t id, ;

   while (1) {
	   //gsensor_check(&spi, &led);
	   spectrum_display(&pwm, &adc, &sseg, &sw);
   } //while
} //main
