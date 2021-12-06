/*****************************************************************//**
 * @file main_video_test.cpp
 *
 * @brief Basic test of 4 basic i/o cores
 *
 * @author p chu
 * @version v1.0: initial release
 *********************************************************************/

//#define _DEBUG
#include "chu_init.h"
#include "gpio_cores.h"
#include "vga_core.h"
#include "sseg_core.h"
#include "ps2_core.h"

void test_start(GpoCore *led_p) {
   int i;

   for (i = 0; i < 20; i++) {
      led_p->write(0xff00);
      sleep_ms(50);
      led_p->write(0x0000);
      sleep_ms(50);
   }
}

/**
 * check bar generator core
 * @param bar_p pointer to Gpv instance
 */
void bar_check(GpvCore *bar_p) {
   bar_p->bypass(0);
   sleep_ms(3000);
}

/**
 * check color-to-grayscale core
 * @param gray_p pointer to Gpv instance
 */
void gray_check(GpvCore *gray_p) {
   gray_p->bypass(0);
   sleep_ms(3000);
   gray_p->bypass(1);
}

/**
 * check osd core
 * @param osd_p pointer to osd instance
 */
void osd_check(OsdCore *osd_p) {
   osd_p->set_color(0x0f0, 0x001); // dark gray/green
   osd_p->bypass(0);
   osd_p->clr_screen();
   for (int i = 0; i < 64; i++) {
      osd_p->wr_char(8 + i, 20, i);
      osd_p->wr_char(8 + i, 21, 64 + i, 1);
      sleep_ms(100);
   }
   sleep_ms(3000);
}

/**
 * test frame buffer core
 * @param frame_p pointer to frame buffer instance
 */
void frame_check(FrameCore *frame_p) {
   int x, y, color;

   frame_p->bypass(0);
   for (int i = 0; i < 10; i++) {
      //frame_p->clr_screen(0x008);  // dark green
      for (int j = 0; j < 20; j++) {
         x = rand() % 640;
         y = rand() % 480;
         color = rand() % 512;
         frame_p->plot_line(400, 200, x, y, color);
      }
      sleep_ms(300);
   }
   sleep_ms(3000);
}

/**
 * test ghost sprite
 * @param ghost_p pointer to mouse sprite instance
 */
void mouse_check(SpriteCore *mouse_p) {
   int x, y;

   mouse_p->bypass(0);
   // clear top and bottom lines
   for (int i = 0; i < 32; i++) {
      mouse_p->wr_mem(i, 0);
      mouse_p->wr_mem(31 * 32 + i, 0);
   }

   // slowly move mouse pointer
   x = 0;
   y = 0;
   for (int i = 0; i < 80; i++) {
      mouse_p->move_xy(x, y);
      sleep_ms(50);
      x = x + 4;
      y = y + 3;
   }
   sleep_ms(3000);
   // load top and bottom rows
   for (int i = 0; i < 32; i++) {
      sleep_ms(20);
      mouse_p->wr_mem(i, 0x00f);
      mouse_p->wr_mem(31 * 32 + i, 0xf00);
   }
   sleep_ms(3000);
}

void block2_check(SpriteCore *block2_p) {
   int x, y;

   block2_p->bypass(0);
   // clear top and bottom lines
   for (int i = 0; i < 32; i++) {
	  block2_p->wr_mem(i, 0);
	  block2_p->wr_mem(31 * 32 + i, 0);
   }

   // slowly move mouse pointer
   x = 50;
   y = 50;
   for (int i = 0; i < 80; i++) {
	  block2_p->move_xy(x, y);
      sleep_ms(50);
      x = x + 4;
      y = y + 3;
   }
   sleep_ms(3000);
   // load top and bottom rows
   for (int i = 0; i < 32; i++) {
      sleep_ms(20);
      block2_p->wr_mem(i, 0x00f);
      block2_p->wr_mem(31 * 32 + i, 0xf00);
   }
   sleep_ms(3000);
}

void block3_check(SpriteCore *block3_p) {
   int x, y;

   block3_p->bypass(0);
   // clear top and bottom lines
   for (int i = 0; i < 32; i++) {
	  block3_p->wr_mem(i, 0);
	  block3_p->wr_mem(31 * 32 + i, 0);
   }

   // slowly move mouse pointer
   x = 100;
   y = 100;
   for (int i = 0; i < 80; i++) {
	  block3_p->move_xy(x, y);
      sleep_ms(50);
      x = x + 4;
      y = y + 3;
   }
   sleep_ms(3000);
   // load top and bottom rows
   for (int i = 0; i < 32; i++) {
      sleep_ms(20);
      block3_p->wr_mem(i, 0x00f);
      block3_p->wr_mem(31 * 32 + i, 0xf00);
   }
   sleep_ms(3000);
}

/**
 * test ghost sprite
 * @param ghost_p pointer to ghost sprite instance
 */
void ghost_check(SpriteCore *ghost_p) {
   int x, y;

   // slowly move mouse pointer
   ghost_p->bypass(0);
   ghost_p->wr_ctrl(0x1c);  //animation; blue ghost
   x = 0;
   y = 100;
   for (int i = 0; i < 156; i++) {
      ghost_p->move_xy(x, y);
      sleep_ms(100);
      x = x + 4;
      if (i == 80) {
         // change to red ghost half way
         ghost_p->wr_ctrl(0x04);
      }
   }
   sleep_ms(3000);
}

/*frame_p->plot_line(x,y,x+96,y,rand()%512);
frame_p->plot_line(x,y+32,x+96,y+32,rand()%512);
frame_p->plot_line(x,y,x,y+32,rand()%512);
frame_p->plot_line(x+96,y,x+96,y+32,rand()%512);*/

void block3_check(SpriteCore *mouse_p, SpriteCore *block2_p, SpriteCore *block3_p, FrameCore *frame_p, Ps2Core *ps2_p, OsdCore *osd_p) {
	int x, y, x1, y1, x2, y2;
	int id;
	char ch;
	int thres_x;
	int thres_y;
	int thres_x1;
	int thres_y1;
	int lives = 3;
	int i = 0;
	id = ps2_p->init();
	uart.disp("\n\rPS2 device (1-keyboard / 2-mouse): ");
	uart.disp(id);
	uart.disp("\n\r");
	mouse_p->bypass(1);
	block2_p->bypass(1);
	block3_p->bypass(0);
	frame_p->bypass(0);

	x = 0;
	y = 448;
	x1 = 0;
	y1 = 384;
	bool input = true;
	while(input){
		for(i = 0; i < 160; i++)
		{
			 if(ps2_p->get_kb_ch(&ch))
			 {
				 if(ch == 80)
				 {
					 input = false;
					 break;
				 }
			 }
			 block3_p->move_xy(x, y);
			 sleep_ms(50);
			 if(i < 80)
			 {
				 x = x + 5;
			 }
			 if(i > 80)
			 {
				 x = x - 5;
			 }
		}
	}

	frame_p->drawRect(x, y, 96, 32, rand()%512);
	thres_x = x;
	thres_y = y;
	thres_x1 = x + 96;
	thres_y1 = y + 32;

	x = 0;
	y = 416;
	while(lives != 0 && y > 224)
	{
		input = true;
		while(input){
			for(i = 0; i < 160; i++)
			{
				 if(ps2_p->get_kb_ch(&ch))
				 {
					 if(ch == 80)
					 {
						 input = false;
						 break;
					 }
				 }
				 block3_p->move_xy(x, y);
				 block2_p->move_xy(x, y);
				 mouse_p->move_xy(x, y);
				 sleep_ms(50);
				 if(i < 80)
				 {
					 x = x + 5;
				 }
				 if(i > 80)
				 {
					 x = x - 5;
				 }
			}
		}

		if(i > 80)
		{
			if(thres_x - 32 < x && thres_x + 32 > x)
			{
				x = thres_x;
				if(lives == 3)
				{
					frame_p->drawRect(x, y, 96, 32, rand()%512);
				}
				else if(lives == 2)
				{
					frame_p->drawRect(x, y, 64, 32, rand()%512);
				}
				else if(lives == 1)
				{
					frame_p->drawRect(x, y, 32, 32, rand()%512);
				}
			}
			else
			{
				if(lives == 3){
					mouse_p->bypass(1);
					block2_p->bypass(0);
					block3_p->bypass(1);
					frame_p->drawRect(thres_x, y, 64, 32, rand()%512);
					lives = lives - 1;
				}
				else if(lives == 2){
					mouse_p->bypass(0);
					block2_p->bypass(1);
					block3_p->bypass(1);
					frame_p->drawRect(thres_x, y, 32, 32, rand()%512);
					lives = lives - 1;
				}
				else if(lives == 1){
					mouse_p->bypass(1);
					block2_p->bypass(1);
					block3_p->bypass(1);
					frame_p->clr_screen(0x008);
					lives = lives - 1;
				}
			}
		}
		else if(i < 80)
		{

			if(thres_x - 32 < x && thres_x + 32 > x)
			{
				x = thres_x;
				if(lives == 3)
				{
					frame_p->drawRect(x, y, 96, 32, rand()%512);
				}
				else if(lives == 2)
				{
					frame_p->drawRect(x, y, 64, 32, rand()%512);
				}
				else if(lives == 1)
				{
					frame_p->drawRect(x, y, 32, 32, rand()%512);
				}
			}
			else
			{
				if(lives == 3){
					mouse_p->bypass(1);
					block2_p->bypass(0);
					block3_p->bypass(1);
					thres_x = thres_x + 32;
					frame_p->drawRect(thres_x, y, 64, 32, rand()%512);
					lives = lives - 1;
				}
				else if(lives == 2){
					mouse_p->bypass(0);
					block2_p->bypass(1);
					block3_p->bypass(1);
					thres_x = thres_x + 32;
					frame_p->drawRect(thres_x, y, 32, 32, rand()%512);
					lives = lives - 1;
				}
				else if(lives == 1){
					mouse_p->bypass(1);
					block2_p->bypass(1);
					block3_p->bypass(1);
					frame_p->clr_screen(0x008);
					lives = lives - 1;
				}
			}
		}
		y = y - 32;
		x = 0;
	}

	if(lives != 0)
	{
		mouse_p->bypass(1);
		block2_p->bypass(1);
		block3_p->bypass(1);
		frame_p->clr_screen(0x008);
		osd_p->set_color(0x0f0, 0x001); // dark gray/green
		osd_p->bypass(0);
		osd_p->clr_screen();
	    osd_p->wr_char(8, 20, 87);
	    osd_p->wr_char(9, 20, 87);
	    osd_p->wr_char(10, 20, 87);
	    sleep_ms(100);
	}
	if(lives == 0){
		mouse_p->bypass(1);
		block2_p->bypass(1);
		block3_p->bypass(1);
		frame_p->clr_screen(0x008);
		osd_p->bypass(1);
	}


	/*x = 0;
	y = 384;
	input = true;
	while(input){
		for(i = 0; i < 160; i++)
		{
			 if(ps2_p->get_kb_ch(&ch))
			 {
				 if(ch == 80)
				 {
					 input = false;
					 break;
				 }
			 }
			 block3_p->move_xy(x, y);
			 block2_p->move_xy(x, y);
			 sleep_ms(50);
			 if(i < 80)
			 {
				 x = x + 5;
			 }
			 if(i > 80)
			 {
				 x = x - 5;
			 }
		}
	}*/


	/*x = 0;
	y = 448;
	x1 = 0;
	y1 = 416;
	x2 = 0;
	y2 = 384;
   for (int i = 0; i < 80; i++) {
	  block3_p->move_xy(x, y);
	  block2_p->move_xy(x1, y1);
	  mouse_p->move_xy(x2, y2);
	  sleep_ms(50);
	  x = x + 5;
	  x1 = x1 + 5;
	  x2 = x2 + 5;
   }
   frame_p->drawRect(x, y, 96, 32, rand()%512);
   frame_p->drawRect(x1, y1, 64, 32, rand()%512);
   y = 352;
   x = 0;
   y1 = 320;
   x1 = 0;
   for (int i = 0; i < 80; i++) {
   	  block3_p->move_xy(x, y);
   	  block2_p->move_xy(x1, y1);
   	  sleep_ms(50);
   	  x = x + 5;
   	  x1 = x1 + 5;
   	  //x2 = x2 + 5;
   }
   frame_p->drawRect(x2, y2, 32, 32, rand()%512);
   y2 = 288;
   x2 = 0;
   for (int i = 0; i < 80; i++) {
	  mouse_p->move_xy(x2, y2);
	  sleep_ms(50);
	  x = x + 5;
	  x1 = x1 + 5;
	  x2 = x2 + 5;
   }*/

}


// external core instantiation
GpoCore led(get_slot_addr(BRIDGE_BASE, S2_LED));
GpiCore sw(get_slot_addr(BRIDGE_BASE, S3_SW));
FrameCore frame(FRAME_BASE);
GpvCore bar(get_sprite_addr(BRIDGE_BASE, V7_BAR));
GpvCore gray(get_sprite_addr(BRIDGE_BASE, V6_GRAY));
SpriteCore ghost(get_sprite_addr(BRIDGE_BASE, V3_GHOST), 1024);
SpriteCore mouse(get_sprite_addr(BRIDGE_BASE, V1_MOUSE), 1024);
SpriteCore block2(get_sprite_addr(BRIDGE_BASE, V4_USER4), 1024);
SpriteCore block3(get_sprite_addr(BRIDGE_BASE, V5_USER5), 1024);
OsdCore osd(get_sprite_addr(BRIDGE_BASE, V2_OSD));
SsegCore sseg(get_slot_addr(BRIDGE_BASE, S8_SSEG));

Ps2Core ps2(get_slot_addr(BRIDGE_BASE, S11_PS2));

int main() {
   while (1) {
      test_start(&led);
      // bypass all cores
      frame.bypass(1);
      bar.bypass(1);
      gray.bypass(1);
      ghost.bypass(1);
      osd.bypass(1);
      mouse.bypass(1);
      block2.bypass(1);
      block3.bypass(1);
      sleep_ms(3000);

      // enable cores one by one
      //frame_check(&frame);
      //bar_check(&bar);
      //gray_check(&gray);
      //ghost_check(&ghost);
      //osd_check(&osd);
      //mouse_check(&mouse);
      //block2_check(&block2);
      block3_check(&mouse, &block2, &block3,&frame,&ps2,&osd);

      while (sw.read(0)) {
         // test composition with different overlays if sw(0) is 1
         //mouse.bypass(sw.read(1));
         osd.bypass(sw.read(2));
         //ghost.bypass(sw.read(3));
         gray.bypass(sw.read(6));
         bar.bypass(sw.read(7));
         frame.bypass(sw.read(8));
         // set osd background color to transparent
         osd.set_color(0x0f0, sw.read(9));
         // set color/animation of ghost sprite
         ghost.wr_ctrl(sw.read() >> 11);
      } //while
      //ps2_check(&ps2,&mouse);
   } // while
} //main
