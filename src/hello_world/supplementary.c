#ifndef _SUPPLEMENTARYC_
#define _SUPPLEMENTARYC_
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
#include "sdcard.h"
#include "ff.h"
#include "plic.h"

uint16_t isinTable16[] =  {
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



 int sdcard_init(void)
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



 int fs_init(void)
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
#endif


