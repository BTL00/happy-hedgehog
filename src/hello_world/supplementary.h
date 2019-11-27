#ifndef _SUPPLEMENTARYH_
#define _SUPPLEMENTARYH_

#ifdef __cplusplus
extern "C" {
#endif

float isin(long x);
float icos(long x);
 int sdcard_init(void);
 int fs_init(void);
 uint16_t hsvTorgb565(uint16_t h, uint8_t s, uint8_t v);

#ifdef __cplusplus
}
#endif


#endif
