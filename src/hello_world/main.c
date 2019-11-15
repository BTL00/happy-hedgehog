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

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "i2s.h"
#include "sysctl.h"
#include "fpioa.h"
#include "uarths.h"
#include "mic_array_leds.h"
#include "gpiohs.h"
#include "bsp.h"
#include "dmac.h"
#include "fpioa.h"
#include "sdcard.h"
#include "ff.h"
#include "plic.h"
#include "movement.h" //my file
#include "supplementary.h" //my file


#define FRAME_LEN   32768
#define PI 3.14159265



uint32_t rx_buf[262144];
int16_t file_buf[262144];



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

  fpioa_set_function(1, FUNC_GPIOHS1);
  fpioa_set_function(2, FUNC_GPIOHS2);
  fpioa_set_function(3, FUNC_GPIOHS3);
  fpioa_set_function(4, FUNC_GPIOHS4);


     // SD CARD INIT for maix bit
  fpioa_set_function(27, FUNC_SPI0_SCLK);
  fpioa_set_function(26, FUNC_SPI0_D1);
  fpioa_set_function(28, FUNC_SPI0_D0);
  fpioa_set_function(29, FUNC_GPIOHS7);
  gpiohs_set_drive_mode(29, GPIO_DM_OUTPUT);


  fpioa_set_function(12, FUNC_GPIOHS10);
  gpiohs_set_drive_mode(10, GPIO_DM_OUTPUT);

  fpioa_set_function(13, FUNC_GPIOHS9);
  gpiohs_set_drive_mode(9, GPIO_DM_OUTPUT);

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

    prepare_gpio_for_tb6612();




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

    // initialize all 4 I2S channels, stereo -> 8 microphones
    i2s_init(I2S_DEVICE_0, I2S_RECEIVER, 0xFF);

    // configure the 4 I2S channels
    i2s_rx_channel_config(I2S_DEVICE_0, I2S_CHANNEL_0, RESOLUTION_16_BIT, SCLK_CYCLES_32, TRIGGER_LEVEL_4, STANDARD_MODE);
    i2s_rx_channel_config(I2S_DEVICE_0, I2S_CHANNEL_1, RESOLUTION_16_BIT, SCLK_CYCLES_32, TRIGGER_LEVEL_4, STANDARD_MODE);
    i2s_rx_channel_config(I2S_DEVICE_0, I2S_CHANNEL_2, RESOLUTION_16_BIT, SCLK_CYCLES_32, TRIGGER_LEVEL_4, STANDARD_MODE);
    i2s_rx_channel_config(I2S_DEVICE_0, I2S_CHANNEL_3, RESOLUTION_16_BIT, SCLK_CYCLES_32, TRIGGER_LEVEL_4, STANDARD_MODE);

    i2s_set_sample_rate(I2S_DEVICE_0, 44100);







    // some variables for taking averages
    int32_t av[8]; 
    int num_averages = 50;
    float if_samples;
    float x,y = 0; //angle

    // inverse, float of the number of samples taken
    if_samples = 1./(float)(num_averages * FRAME_LEN);


 /* */



    gpiohs_set_pin(10, GPIO_PV_LOW); 
    gpiohs_set_pin(9, GPIO_PV_LOW);



    FIL  file_channel_0;

    FRESULT ret = FR_OK;
    const char *path_0 = "file_channel_0.txt";
    uint32_t v_ret_len = 0;

    sleep(2); //wait before starting work



    ret = f_open(&file_channel_0, path_0,  FA_CREATE_ALWAYS | FA_WRITE | FA_READ);
    if (ret != FR_OK) {
      printf("File opening error\n");
      while(1) {};
    }else{
      printf("File sucessfully opened\n");
    }

    while (1)
    {
        // set averages to zero to start
      for (int i=0; i<8; i++) av[i] = 0;





        // for take num_averages samples (of FRAME_LEN samples each)
         for (int a=0; a<num_averages; a++) {
             // read the samples of the 8 mics from the rx_buffer

             for (int f=0; f<FRAME_LEN; f++) {
                 for (int i=0; i<8; i++) {
                     av[i] += abs(rx_buf[8*f+i] >> 16);
                 }


             }
         }

     gpiohs_set_pin(9, GPIO_PV_LOW);

     i2s_receive_data_dma(I2S_DEVICE_0, &rx_buf[0], FRAME_LEN * 8, DMAC_CHANNEL1);

     gpiohs_set_pin(9, GPIO_PV_HIGH);

     for (uint32_t i = 0; i < FRAME_LEN * 8; i++)
     {
                    file_buf[i] = (int16_t) (rx_buf[i] >> 16); //converts 32 bit integers with 0x0000 at the end to 16 bit
                  }


                  gpiohs_set_pin(10, GPIO_PV_LOW);



                   // for (int buff_counter = 0 )
                  ret = f_write(&file_channel_0,  (void *) file_buf, sizeof(file_buf), &v_ret_len);
                  f_sync(&file_channel_0);
                  if(ret != FR_OK)
                  {
                    printf("Write %s err[%d]\n", path_0, ret);
                    while(1) {};
                  }
                  else
                  {
                    printf("Write %d bytes to %s ok\n", v_ret_len, path_0);
                  }

                  
                  //}
                  gpiohs_set_pin(10, GPIO_PV_HIGH);



                    // correct for the number of samples taken
                  for (int i=0; i<8; i++) {
                    av[i] = (int) ((float)av[i]*if_samples);
                    if (av[i]>512) av[i]=512;
                  }








       /* if only noise is present (a low central microphone output), set all array mic averages to 0.
        else subract the central microphone output from the other array mics, and make sure that their 
        value is between 0 and 255.*/
                  if (av[1] > 10) {
                    for (int i=2; i<8; i++) {
                      av[i] -= av[1]/2;
                      if (av[i]<0) av[i] = 0;
                      if (av[i]>512) av[i]=512;
                    }
                  } else {
                    for (int i=2; i<8; i++) av[i] = 0;
                  }








                x = av[3] * icos(0.0-90.) + av[4] * icos(60.-90.) + av[5] * icos(120-90.) + av[6] * icos(180-90)  + av[7] * icos(240-90) + av[2] * icos(300-90);
                y = av[3] * isin(0.0-90.) + av[4] * isin(60.-90.) + av[5] * isin(120-90.) + av[6] * isin(180-90)  + av[7] * isin(240-90) + av[2] * isin(300-90);


                if( x > 0 && ( y > -10 || y < 10) ) {
                  move_forward();
                }else if( x < -10 && ( y > -10 || y < 10) ) {
                  move_backward();
                }else if( x > 0 && y > 0 ) {
                  turn_right();
                }else if(x > 0 && y < 0) {
                  turn_left();
                }else if(x < 0 && y > 0) {
                  turn_right();

                }else if(x < 0 && y < 0) {
                  turn_left();

                }else {
                  stop();
                }


         printf("mB=%d\tmC=%d\tm1=%d\tm2=%d\tm3=%d\tm4=%d\tm5=%d\tm6=%d\n\r", av[0], av[1], av[2], av[3], av[4], av[5], av[6], av[7]);



            // set the LEDs to white with brightness according to their average microphone output
            // set_light(8, av[2], av[2], av[2]);
            // set_light(10, av[3], av[3], av[3]);
            // set_light(6, av[4], av[4], av[4]);
            // set_light(4, av[5], av[5], av[5]);
            // set_light(0, av[6], av[6], av[6]);
            // set_light(2, av[7], av[7], av[7]);
            // write_pixels();
              }
              f_close(&file_channel_0);

              return 0;
            }
