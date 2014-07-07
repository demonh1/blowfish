#include "bf.h"

void encryptBlock(blowfish_context_t* ctx, u32* xl, u32* xr) 
{
	aword  Xl, Xr;
	Xl.word = *xl;
	Xr.word = *xr;

	 Xl.word ^= ctx->pbox[0];
	 
	BF_ENCRYPT(Xr,Xl,ctx->sbox,ctx->pbox);	
	 

	 Xr.word ^= ctx->pbox[17];

	 *xr = Xl.word;
	 *xl = Xr.word;
}

void decryptBlock(blowfish_context_t* ctx, u32 *xl, u32 *xr)
{
	aword  Xl, Xr;
	Xl.word = *xl;
	Xr.word = *xr;

   Xl.word ^= ctx->pbox[17];
   
   BF_DECRYPT(Xr,Xl,ctx->sbox,ctx->pbox);
  
   Xr.word ^= ctx->pbox[0];

   *xl = Xr.word;
   *xr = Xl.word;
}


void blowfishInit(blowfish_context_t* ctx, u8* key, u32 keybytes) 
{

  u32  datal = 0;
  u32  datar = 0;
  aword temp;

  memcpy(ctx->pbox, P, sizeof(P));
  memcpy(ctx->sbox, S, sizeof(S));

  u16 j = 0;
  for (u16 i = 0; i < 7; ++i)
  {
	temp.w.byte0 = key[j];
    temp.w.byte1 = key[(j+1)%keybytes];
	temp.w.byte2 = key[(j+2)%keybytes];
    temp.w.byte3 = key[(j+3)%keybytes];

	switch (i)
	{
		case 0:
		ctx->pbox[0]  = ctx->pbox[0] ^ temp.word;
		ctx->pbox[7]  = ctx->pbox[7] ^ temp.word;
		ctx->pbox[14] = ctx->pbox[14] ^ temp.word;
		break;

		case 1:
		ctx->pbox[1]  = ctx->pbox[1] ^ temp.word;
		ctx->pbox[8]  = ctx->pbox[8] ^ temp.word;
		ctx->pbox[15] = ctx->pbox[15] ^ temp.word;
		break;

		case 2:
		ctx->pbox[2]  = ctx->pbox[2] ^ temp.word;
		ctx->pbox[9]  = ctx->pbox[9] ^ temp.word;
		ctx->pbox[16] = ctx->pbox[16] ^ temp.word;
		break;

		case 3:
		ctx->pbox[3]   = ctx->pbox[3] ^ temp.word;
		ctx->pbox[10]  = ctx->pbox[10] ^ temp.word;
		ctx->pbox[17]  = ctx->pbox[17] ^ temp.word;
		break;

		case 4:
		ctx->pbox[4]   = ctx->pbox[4] ^ temp.word;
		ctx->pbox[11]  = ctx->pbox[11] ^ temp.word;
		break;

		case 5:
		ctx->pbox[5]   = ctx->pbox[5] ^ temp.word;
		ctx->pbox[12]  = ctx->pbox[12] ^ temp.word;
		break;

		case 6:
		ctx->pbox[6]   = ctx->pbox[6] ^ temp.word;
		ctx->pbox[13]  = ctx->pbox[13] ^ temp.word;
		break;
	}

	j = (j + 4) % keybytes;
  }

	for (u16 i = 0; i < 18; i += 2)
	{
		
		encryptBlock(ctx,&datal, &datar);

		ctx->pbox[i] = datal;
		ctx->pbox[i + 1] = datar;
	}

  for (size_t i = 0; i < 4; ++i)
  {
	for (j = 0; j < 256; j += 2)
	{
	  
		encryptBlock(ctx,&datal, &datar);

	  ctx->sbox[i][j] = datal;
	  ctx->sbox[i][j + 1] = datar;
    }
  }

}