#ifndef BF_H
#define BF_H

#include "common.h"
#include "tabl.h"
#include <cstring>


void encryptBlock(blowfish_context_t* ctx, u32 *xl, u32 *xr);
void decryptBlock(blowfish_context_t* ctx, u32 *xl, u32 *xr);
void blowfishInit(blowfish_context_t* ctx, u8* key, u32 keybytes);

#endif