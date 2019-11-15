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



#define FRAME_LEN   32768
#define PI 3.14159265



uint16_t isinTable16[] = {
  0, 1144, 2287, 3430, 4571, 5712, 6850, 7987, 9121, 10252, 11380,
  12505, 13625, 14742, 15854, 16962, 18064, 19161, 20251, 21336, 22414,
  23486, 24550, 25607, 26655, 27696, 28729, 29752, 30767, 31772, 32768,

  33753, 34728, 35693, 36647, 37589, 38521, 39440, 40347, 41243, 42125,
  42995, 43851, 44695, 45524, 46340, 47142, 47929, 48702, 49460, 50203,
  50930, 51642, 52339, 53019, 53683, 54331, 54962, 55577, 56174, 56755,

  57318, 57864, 58392, 58902, 59395, 59869, 60325, 60763, 61182, 61583,
  61965, 62327, 62671, 62996, 63302, 63588, 63855, 64103, 64331, 64539,
  64728, 64897, 65047, 65176, 65286, 65375, 65445, 65495, 65525, 65535,
};






float isin(long x)
{
  bool pos = true;
  if (x < 0)
  {
    x = -x;
    pos = !pos;
  }
  if (x >= 360) x %= 360;
  if (x > 180)
  {
    x -= 180;
    pos = !pos;
  }
  if (x > 90) x = 180 - x;

  if (pos) return (float)isinTable16[x] / 65535.0 ;
  return - (float)isinTable16[x] / 65535.0 ;
}
/* szybszy cosinus*/
float icos(long x)
{
  return isin(x + 90);
}






uint32_t rx_buf[262144];
int16_t file_buf[262144];

/* microphones on the array (silk screen readable, flex flat cable behind mic 4 and LED 6):

       5
   2       6
       C
   1       3
       4

   microphone on the MAIX GO board: B

   Note, two microphones are the left/right half of a stereo I2S channel. 
   On a single I2S channel the left/right are placed alternating in memory
   Also note that when using DMA all 8 mics are placed after each other: B, C, 1, 2, 3, 4, 5, 6

   microphone on MAIX GO board: pin 20, FUNC_I2S0_IN_D0 (even bytes)
   microphone C on mic array: pin 20, FUNC_I2S0_IN_D0 (odd bytes)
   microphone 1 on mic array: pin 21, FUNC_I2S0_IN_D1 (even bytes)
   microphone 2 on mic array: pin 21, FUNC_I2S0_IN_D1 (odd bytes)
   microphone 3 on mic array: pin 22, FUNC_I2S0_IN_D2 (even bytes)
   microphone 4 on mic array: pin 22, FUNC_I2S0_IN_D2 (odd bytes)
   microphone 5 on mic array: pin 23, FUNC_I2S0_IN_D3 (even bytes)
   microphone 6 on mic array: pin 23, FUNC_I2S0_IN_D3 (odd bytes)

   The top LED is number 0, counting clock-wise
   microphone 1 is at LED 8
   microphone 2 is at LED 10
   microphone 3 is at LED 4
   microphone 4 is at LED 6
   microphone 5 is at LED 0
   microphone 6 is at LED 2
*/

void io_mux_init(){
    // assign functions to pins

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


   // fpioa_set_function(29, FUNC_SPI0_SS0);



}





struct soundhdr {
  char  riff[4];        /* "RIFF"                                  */
  long  flength;        /* file length in bytes                    */
  char  wave[4];        /* "WAVE"                                  */
  char  fmt[4];         /* "fmt "                                  */
  long  chunk_size;     /* size of FMT chunk in bytes (usually 16) */
  short format_tag;     /* 1=PCM, 257=Mu-Law, 258=A-Law, 259=ADPCM */
  short num_chans;      /* 1=mono, 2=stereo                        */
  long  srate;          /* Sampling rate in samples per second     */
  long  bytes_per_sec;  /* bytes per second = srate*bytes_per_samp */
  short bytes_per_samp; /* 2=16-bit mono, 4=16-bit stereo          */
  short bits_per_samp;  /* Number of bits per sample               */
  char  data[4];        /* "data"                                  */
  long  dlength;        /* data length in bytes (filelength - 44)  */
} wavh;

// ......




static int sdcard_init(void)
{
    uint8_t status;

    printf("/******************sdcard test*****************/\n");
    status = sd_init();
    printf("sd init %d\n", status);
    if (status != 0)
    {
          printf("card info status %d\n", status);

        return status;
    }

    printf("card info status %d\n", status);
    printf("CardCapacity:%ld\n", cardinfo.CardCapacity);
    printf("CardBlockSize:%d\n", cardinfo.CardBlockSize);
    return 0;
}



static int fs_init(void)
{
    static FATFS sdcard_fs;
    FRESULT status;
    DIR dj;
    FILINFO fno;

    printf("/********************fs test*******************/\n");
    status = f_mount(&sdcard_fs, _T("0:"), 1);
    printf("mount sdcard:%d\n", status);
    if (status != FR_OK)
        return status;

    printf("printf filename\n");
    status = f_findfirst(&dj, &fno, _T("0:"), _T("*"));
    while (status == FR_OK && fno.fname[0]) {
        if (fno.fattrib & AM_DIR)
            printf("dir:%s\n", fno.fname);
        else
            printf("file:%s\n", fno.fname);
        status = f_findnext(&dj, &fno);
    }
    f_closedir(&dj);
    return 0;
}



void move_forward() {
     gpiohs_set_pin(1, GPIO_PV_HIGH);
     gpiohs_set_pin(2, GPIO_PV_LOW);
     gpiohs_set_pin(3, GPIO_PV_LOW);
     gpiohs_set_pin(4, GPIO_PV_HIGH);

}

void move_backward() {

     gpiohs_set_pin(1, GPIO_PV_LOW);
     gpiohs_set_pin(2, GPIO_PV_HIGH);
     gpiohs_set_pin(3, GPIO_PV_HIGH);
     gpiohs_set_pin(4, GPIO_PV_LOW);

}

void turn_right() {
     gpiohs_set_pin(1, GPIO_PV_HIGH);
     gpiohs_set_pin(2, GPIO_PV_LOW);
     gpiohs_set_pin(3, GPIO_PV_LOW);
     gpiohs_set_pin(4, GPIO_PV_LOW);


}


void turn_left() {
     gpiohs_set_pin(1, GPIO_PV_LOW);
     gpiohs_set_pin(2, GPIO_PV_LOW);
     gpiohs_set_pin(3, GPIO_PV_LOW);
     gpiohs_set_pin(4, GPIO_PV_HIGH);

}
void stop() {
     gpiohs_set_pin(1, GPIO_PV_HIGH);
     gpiohs_set_pin(2, GPIO_PV_HIGH);
     gpiohs_set_pin(3, GPIO_PV_HIGH);
     gpiohs_set_pin(4, GPIO_PV_HIGH);

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

     gpiohs_set_drive_mode(1, GPIO_DM_OUTPUT);
     gpiohs_set_drive_mode(2, GPIO_DM_OUTPUT);
     gpiohs_set_drive_mode(3, GPIO_DM_OUTPUT);
     gpiohs_set_drive_mode(4, GPIO_DM_OUTPUT);

     gpiohs_set_pin(1, GPIO_PV_LOW);
     gpiohs_set_pin(2, GPIO_PV_LOW);
     gpiohs_set_pin(3, GPIO_PV_LOW);
     gpiohs_set_pin(4, GPIO_PV_LOW);

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

    sleep(2);



               ret = f_open(&file_channel_0, path_0,  FA_CREATE_ALWAYS | FA_WRITE | FA_READ);
              if (ret != FR_OK) {
                    printf("File opening error\n");
                    while(1) {};
                   }else{
                    printf("File sucessfully opened\n");
                   }

                    ret = f_write(&file_channel_0,  (void *) bomba_header, sizeof(bomba_header), &v_ret_len);
                    f_sync(&file_channel_0);

    while (1)
    {
        // set averages to zero to start
        for (int i=0; i<8; i++) av[i] = 0;
            // read the data 
            




        // for take num_averages samples (of FRAME_LEN samples each)
        // for (int a=0; a<num_averages; a++) {
        //     // read the samples of the 8 mics from the rx_buffer

        //     for (int f=0; f<FRAME_LEN; f++) {
        //         for (int i=0; i<8; i++) {
        //             av[i] += abs(rx_buf[8*f+i]);
        //         }


        //     }
        // }

                  gpiohs_set_pin(9, GPIO_PV_LOW);

                  i2s_receive_data_dma(I2S_DEVICE_0, &rx_buf[0], FRAME_LEN * 8, DMAC_CHANNEL1);

                   gpiohs_set_pin(9, GPIO_PV_HIGH);

                   for (int i = 0; i < FRAME_LEN * 8; ++i)
                   {
                    file_buf[i] = (int16_t) (rx_buf[i] >> 16);
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


      //   printf("mB=%d\tmC=%d\tm1=%d\tm2=%d\tm3=%d\tm4=%d\tm5=%d\tm6=%d\t\tx=%f,\ty=%f\tangle=%f\n\r", av[0], av[1], av[2], av[3], av[4], av[5], av[6], av[7], x, y, angle / PI * 180);



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
