#include "bf.h"

#include <iostream>

#ifdef WIN32
#include <windows.h>
#endif

#ifdef _UNIX
#include <time.h>
#endif

//---------------- globals ---------------------
struct _byte
{
	u8 seven;
	u8 six;
	u8 five;
	u8 four;
	u8 three;
	u8 two;
	u8 one;
	u8 zero;
};

union word
{
	u64 w;
	_byte b;
};


u32 getTickCount() {
#ifdef WIN32
	return GetTickCount();
#else
	struct timespec now;
	if (clock_gettime(CLOCK_MONOTONIC, &now))
		return 0;
	return now.tv_sec * 1000 + now.tv_nsec / 1000000;
#endif
}
//-------------------------------------

int main () {

	blowfish_context_t c;
	word key;
	key.w = 0x5ECB72D0600000;

	u32 L = 0x8B069CE0;    //     Plain text
	u32 R = 0xC50D4976;    //     Plain text

	u32 l = 0x3CC9C7B4;   //     Cipher text
	u32 r = 0xD9638201;   //     Cipher text

	u64 i = key.w;

	u32 len = 7;


	u32 start = getTickCount();


	while( i < 0xFFFFFFFFFFFFFFFF )
	{
		u8 bkey[7] = {
			key.b.one,
			key.b.two,
			key.b.three,
			key.b.four,
			key.b.five,
			key.b.six,
			key.b.seven };

			blowfishInit(&c,bkey,len);
			decryptBlock(&c,&l,&r);

			if (l == L && r == R) 
			{
				u32 stop = getTickCount();
				u32 end = stop - start;
				std::cout << "Time: " << end  << " ms\n";
				std::cout << "Key: " << std::hex << i << "\n";
				break;

			}

			else 
			{
				l = 0x3CC9C7B4;   
				r = 0xD9638201;  

				key.w++;
				i++;
			}
	}



}
