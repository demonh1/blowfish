#ifndef COMMON_H
#define COMMON_H

#include "types.h"


typedef struct  {
	u32 pbox[18];
	u32 sbox[4][256];
} blowfish_context_t;

union aword
{
	u32 word;
	struct
	{
		u8 byte3;
		u8 byte2;
		u8 byte1;
		u8 byte0;
	} w;
};


#define BF_F(s,x) ((( s[0][x.w.byte3] + s[1][x.w.byte2]) ^ s[2][x.w.byte1]) + s[3][x.w.byte0])
#define ROUND(a,b,s,p) (a.word ^= BF_F(s,b) ^ p)
#define BF_ENCRYPT(xl,xr,s,p)	ROUND(xl,xr,s,p[1]);\
								ROUND(xr,xl,s,p[2]);\
								ROUND(xl,xr,s,p[3]);\
								ROUND(xr,xl,s,p[4]);\
								ROUND(xl,xr,s,p[5]);\
								ROUND(xr,xl,s,p[6]);\
								ROUND(xl,xr,s,p[7]);\
								ROUND(xr,xl,s,p[8]);\
								ROUND(xl,xr,s,p[9]);\
								ROUND(xr,xl,s,p[10]);\
								ROUND(xl,xr,s,p[11]);\
								ROUND(xr,xl,s,p[12]);\
								ROUND(xl,xr,s,p[13]);\
								ROUND(xr,xl,s,p[14]);\
								ROUND(xl,xr,s,p[15]);\
								ROUND(xr,xl,s,p[16]);

#define BF_DECRYPT(xl,xr,s,p)	ROUND(xl,xr,s,p[16]);\
								ROUND(xr,xl,s,p[15]);\
								ROUND(xl,xr,s,p[14]);\
								ROUND(xr,xl,s,p[13]);\
								ROUND(xl,xr,s,p[12]);\
								ROUND(xr,xl,s,p[11]);\
								ROUND(xl,xr,s,p[10]);\
								ROUND(xr,xl,s,p[9]);\
								ROUND(xl,xr,s,p[8]);\
								ROUND(xr,xl,s,p[7]);\
								ROUND(xl,xr,s,p[6]);\
								ROUND(xr,xl,s,p[5]);\
								ROUND(xl,xr,s,p[4]);\
								ROUND(xr,xl,s,p[3]);\
								ROUND(xl,xr,s,p[2]);\
								ROUND(xr,xl,s,p[1]);





#endif