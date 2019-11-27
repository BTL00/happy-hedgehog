/* made by GitJer, based on work by Canaan */

/* Copyright 2018 Canaan Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

//#define SDCARD_RECORD
//#define DISP_LEDS


#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "i2s.h"
#include "sysctl.h"
#include "fpioa.h"
#include "uarths.h"
#include "gpiohs.h"
#include "bsp.h"
#include "dmac.h"
#include "fpioa.h"
#include "plic.h"
#include "movement.h" //my file
#include "supplementary.h" //my file

#ifdef SDCARD_RECORD

#include "mic_array_leds.h"
#include "sdcard.h"
#include "ff.h"
#else
#include "lcd.h"
#include "nt35310.h"
#include "board_config.h"

#endif

char disp_line[4][32];
char direction = 'S';


#define FRAME_LEN   4096
#define BUFFER_LEN 32768
#define PI 3.14159265

double sum_of_rms = 0;

uint32_t rx_buf_0[32768];
uint32_t rx_buf_1[32768];




void io_mux_init(){   // assign functions to pins

    // first the four I2S channels for I2S device 0
  fpioa_set_function(20, FUNC_I2S0_IN_D0);
  fpioa_set_function(21, FUNC_I2S0_IN_D1);
  fpioa_set_function(22, FUNC_I2S0_IN_D2);
  fpioa_set_function(23, FUNC_I2S0_IN_D3);
    // the left/right clock
  fpioa_set_function(19, FUNC_I2S0_WS);
    // the data clock
  fpioa_set_function(18, FUNC_I2S0_SCLK);

  fpioa_set_function(6, FUNC_GPIOHS3);
  fpioa_set_function(7, FUNC_GPIOHS4);
  fpioa_set_function(8, FUNC_GPIOHS5);
  fpioa_set_function(9, FUNC_GPIOHS6);


     // SD CARD INIT for maix bit
  #ifdef SDCARD_RECORD
    fpioa_set_function(27, FUNC_SPI0_SCLK);
    fpioa_set_function(26, FUNC_SPI0_D1);
    fpioa_set_function(28, FUNC_SPI0_D0);
    fpioa_set_function(29, FUNC_GPIOHS7);
    gpiohs_set_drive_mode(29, GPIO_DM_OUTPUT);
  #else
    fpioa_set_function(38, FUNC_GPIOHS0 + DCX_GPIONUM);
    fpioa_set_function(36, FUNC_SPI0_SS3);
    fpioa_set_function(39, FUNC_SPI0_SCLK);
    sysctl_set_spi0_dvp_data(1);

  #endif

  fpioa_set_function(12, FUNC_GPIOHS10);
  gpiohs_set_drive_mode(10, GPIO_DM_OUTPUT);

  fpioa_set_function(13, FUNC_GPIOHS9);
  gpiohs_set_drive_mode(9, GPIO_DM_OUTPUT);

}
void drawline(int x0, int y0, int x1, int y1, uint32_t color)
{
    int dx, dy, p, x, y;
 
  dx=x1-x0;
  dy=y1-y0;
 
  x=x0;
  y=y0;
 
  p=2*dy-dx;
 
  while(x<x1)
  {
    if(p>=0)
    {
      lcd_draw_point(x,y,color);
      y=y+1;
      p=p+2*dy-2*dx;
    }
    else
    {
      lcd_draw_point(x,y,color);
      p=p+2*dy;
    }
    x=x+1;
  }
}

double absd(double d) {
if(d > 0.) return d;
else return -d;

}


void drawcircle(int x0, int y0, int radius, uint32_t color)
{
    int x = radius;
    int y = 0;
    int err = 0;
 
    while (x >= y)
    {
  lcd_draw_point(x0 + x, y0 + y, color);
  lcd_draw_point(x0 + y, y0 + x, color);
  lcd_draw_point(x0 - y, y0 + x, color);
  lcd_draw_point(x0 - x, y0 + y, color);
  lcd_draw_point(x0 - x, y0 - y, color);
  lcd_draw_point(x0 - y, y0 - x, color);
  lcd_draw_point(x0 + y, y0 - x, color);
  lcd_draw_point(x0 + x, y0 - y, color);
 
  if (err <= 0)
  {
      y += 1;
      err += 2*y + 1;
  }
 
  if (err > 0)
  {
      x -= 1;
      err -= 2*x + 1;
  }
    }
}


float rmsValue(uint32_t arr[], uint32_t n, uint32_t nth) 
{ 
    uint32_t square = 0; 
    uint32_t buff = 0;
    float mean = 0.0, root = 0.0; 
  
    // Calculate square. 
    for (int i = nth; i < n; i+=8) { 
      buff = arr[i] / 0xFFFF;
        square += buff * buff;
    } 
  
    // Calculate Mean. 
    mean = (square / (float)(n)); 
  
    // Calculate Root. 
    root = sqrt(mean); 
  
    return root; 
} 



bool buffer_0_to_be_saved = 0;
bool buffer_1_to_be_saved = 0;

bool buffer_0_saving = 0;
bool buffer_1_saving = 0;

int buffer_last_used = 0;







int core1_function(void * ctx) {
    #ifdef SDCARD_RECORD

    FIL  file_channel_0;

    FRESULT ret = FR_OK;
    const char *path_0 = "file_channel_0.txt";
    uint32_t v_ret_len = 0;

    ret = f_open(&file_channel_0, path_0,  FA_CREATE_ALWAYS | FA_WRITE | FA_READ);
    if (ret != FR_OK) {
      printf("File opening error\n");
      while(1) {};
    }else{
      printf("File sucessfully opened\n");
    }
    int save_counter = 0;


    while(1) {


                  if(buffer_0_to_be_saved) {
                    printf("saving buffer 0\n");
                   buffer_0_saving = 1; 
                                                                            gpiohs_set_pin(10, GPIO_PV_LOW);

                   ret = f_write(&file_channel_0,  (void *) rx_buf_0, sizeof(rx_buf_0), &v_ret_len);
                  if(save_counter % 32  == 0) {
                    f_sync(&file_channel_0);
                  }
                  save_counter++;
                   buffer_0_saving = 0;
                   buffer_0_to_be_saved = 0; 
                                     gpiohs_set_pin(10, GPIO_PV_HIGH);

                  }else if(buffer_1_to_be_saved) {
                                        printf("saving buffer 1\n");

                   buffer_1_saving = 1; 
                    gpiohs_set_pin(10, GPIO_PV_LOW);

                  ret = f_write(&file_channel_0,  (void *) rx_buf_1, sizeof(rx_buf_1), &v_ret_len);
                  if(save_counter % 32  == 0) {
                    f_sync(&file_channel_0);
                  }
                  save_counter++;
                   buffer_1_saving = 0;
                   buffer_1_to_be_saved = 0; 
                                                        gpiohs_set_pin(10, GPIO_PV_HIGH);

                  }else{
                                        f_sync(&file_channel_0);

                  }



    }
                  f_close(&file_channel_0);
    #endif

return 0;

}



int main(void)
{
    sysctl_pll_set_freq(SYSCTL_PLL0, 800000000UL);
    sysctl_pll_set_freq(SYSCTL_PLL1, 160000000UL);
    sysctl_pll_set_freq(SYSCTL_PLL2, 45158400UL); //has to be compatible with 44100
    uarths_init();
    io_mux_init();



    dmac_init();
    plic_init();
    sysctl_enable_irq();



    /* Prepare GPIO for TB6612 */

    // prepare_gpio_for_tb6612();

    #ifdef SDCARD_RECORD


        if(sdcard_init())
        {
          printf("SD card err\n");
          return -1;
        }

        if(fs_init())
        {
          printf("FAT32 err\n");
          return -1;
        }

    // initialize the LEDs, and set them initially to off
    init_mic_array_lights();
    printf("Lights initilized\n");
    for (int l=0; l<12; l++) set_light(l, 0, 0, 0);

    #else
    sysctl_set_power_mode(SYSCTL_POWER_BANK6, SYSCTL_POWER_V18);
    sysctl_set_power_mode(SYSCTL_POWER_BANK7, SYSCTL_POWER_V18);
        sleep(1);
        lcd_init();
            lcd_set_direction(DIR_XY_LRDU);

        sleep(1);
        lcd_clear(BLACK);
        sleep(1);
        lcd_draw_string(16, 16, "Display initialized", BLUE);

    #endif



    // initialize all 4 I2S channels, stereo -> 8 microphones
    i2s_init(I2S_DEVICE_0, I2S_RECEIVER, 0xFF);

    // configure the 4 I2S channels
    i2s_rx_channel_config(I2S_DEVICE_0, I2S_CHANNEL_0, RESOLUTION_16_BIT, SCLK_CYCLES_32, TRIGGER_LEVEL_4, STANDARD_MODE);
    i2s_rx_channel_config(I2S_DEVICE_0, I2S_CHANNEL_1, RESOLUTION_16_BIT, SCLK_CYCLES_32, TRIGGER_LEVEL_4, STANDARD_MODE);
    i2s_rx_channel_config(I2S_DEVICE_0, I2S_CHANNEL_2, RESOLUTION_16_BIT, SCLK_CYCLES_32, TRIGGER_LEVEL_4, STANDARD_MODE);
    i2s_rx_channel_config(I2S_DEVICE_0, I2S_CHANNEL_3, RESOLUTION_16_BIT, SCLK_CYCLES_32, TRIGGER_LEVEL_4, STANDARD_MODE);

    i2s_set_sample_rate(I2S_DEVICE_0, 44100);







    // some variables for taking averages
    float av[8]; 
    // int num_averages = 50;
    // float if_samples;
    float x,y,angle; //angle

    // inverse, float of the number of samples taken
    // if_samples = 1./(float)(num_averages * FRAME_LEN);


 /* */






    gpiohs_set_pin(10, GPIO_PV_LOW); 
    gpiohs_set_pin(9, GPIO_PV_LOW);




    // uint32_t a;
    // int32_t b;
    // int16_t c;

    sleep(2); //wait before starting work

    register_core1(core1_function, NULL);




    while (1)
    {


        // set averages to zero to start
      for (int i=0; i<8; i++) av[i] = 0;


        // for take num_averages samples (of FRAME_LEN samples each)
    //     for (int a=0; a<num_averages; a++) {
             // read the samples of the 8 mics from the rx_buffer

      //       for (int f=0; f<FRAME_LEN; f++) {



    #ifdef SDCARD_RECORD



                 for (int i=0; i<8; i++) {
                  if(buffer_last_used == 0) {
                                         av[i] += rmsValue(rx_buf_0, FRAME_LEN * 8, i);
                  }else if (buffer_last_used == 1){
                                         av[i] += rmsValue(rx_buf_1, FRAME_LEN * 8, i);

                  }
                 }


      //       }
      //   }


    while(buffer_0_to_be_saved == 1 && buffer_1_to_be_saved == 1) {
          gpiohs_set_pin(10, GPIO_PV_LOW); 
          gpiohs_set_pin(9, GPIO_PV_LOW);
          msleep(1);
    }

    gpiohs_set_pin(10, GPIO_PV_HIGH); 


    gpiohs_set_pin(9, GPIO_PV_LOW);
   
   // stop();
   
     if(!buffer_0_saving && !buffer_0_to_be_saved) {
            i2s_receive_data_dma(I2S_DEVICE_0, &rx_buf_0[0], FRAME_LEN * 8, DMAC_CHANNEL1);
            buffer_last_used = 0;
            buffer_0_to_be_saved = 1;
     }else if(!buffer_1_saving && !buffer_1_to_be_saved){
            i2s_receive_data_dma(I2S_DEVICE_0, &rx_buf_1[0], FRAME_LEN * 8, DMAC_CHANNEL1);
            buffer_last_used = 1;
            buffer_1_to_be_saved = 1;
     }

     gpiohs_set_pin(9, GPIO_PV_HIGH);

#else
            sum_of_rms = 0;
            for (int i=0; i<8; i++) {
                   av[i] += rmsValue(rx_buf_0, FRAME_LEN * 8, i);
                    sum_of_rms +=av[i];
                 }



    gpiohs_set_pin(10, GPIO_PV_HIGH); 
    gpiohs_set_pin(9, GPIO_PV_LOW);
   
   // stop();
   
            i2s_receive_data_dma(I2S_DEVICE_0, &rx_buf_0[0], FRAME_LEN * 8, DMAC_CHANNEL1);

     gpiohs_set_pin(9, GPIO_PV_HIGH);



     #endif


                x = av[3] * icos(0.0-90.) + av[4] * icos(60.-90.) + av[5] * icos(120-90.) + av[6] * icos(180-90)  + av[7] * icos(240-90) + av[2] * icos(300-90);
                y = av[3] * isin(0.0-90.) + av[4] * isin(60.-90.) + av[5] * isin(120-90.) + av[6] * isin(180-90)  + av[7] * isin(240-90) + av[2] * isin(300-90);

                angle = atan2(y,x);


                sprintf(disp_line[0], "x: %.3lf, y: %.3lf", x, y );
                 sprintf(disp_line[1], "a: %.3lf, r: %.3lf", angle, sum_of_rms );

                lcd_clear(BLACK);
                lcd_draw_string(16,16,disp_line[0], RED);
                lcd_draw_string(16,32,disp_line[1], RED);



                drawcircle(121,160, 5, RED);

                drawcircle(121+y*3,160+x*3, sum_of_rms/20, BLUE);




                if( angle >= 2.4f ) {
                  move_forward();
                                  lcd_draw_string(16,64,"F", RED);

                //  printf("F1 %f\n\r", angle);
                }
                 else if( angle <= -2.4f ) {
                  move_forward();
                                                    lcd_draw_string(16,64,"F", RED);

                //  printf("F2 %f\n\r", angle);
                }else if( (angle > -0.5f && angle < 0.0f)  || (angle < 0.5f && angle > 0.0f) ) {
                //  printf("B %f\n\r", angle);
                                                    lcd_draw_string(16,64,"B", RED);

                  move_backward();
                }else if( angle > 0.0f && angle < 2.4f) {
                 // printf("R %f\n\r", angle);
                                                    lcd_draw_string(16,64,"R", RED);

                 turn_right();
                }else if( angle < 0.0f  && angle > -2.4f) {
                // printf("L %f\n\r", angle);
                                                    lcd_draw_string(16,64,"L", RED);

                  turn_left();
                }else {
                 // printf("S %f\n\r", angle);
                                                    lcd_draw_string(16,64,"S", YELLOW);

                  stop();
                }








            // set the LEDs to white with brightness according to their average microphone output
            #ifdef DISP_LEDS
             set_light(8, av[2], av[2], av[2]);
             set_light(10, av[3], av[3], av[3]);
             set_light(6, av[4], av[4], av[4]);
             set_light(4, av[5], av[5], av[5]);
             set_light(0, av[6], av[6], av[6]);
             set_light(2, av[7], av[7], av[7]);
             write_pixels();
             #endif
              }

              return 0;
            }
