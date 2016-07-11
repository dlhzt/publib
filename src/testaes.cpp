#include <stdexcept>
#include <stdio.h>
#include "aes.hpp"

using namespace std;

#define LEN 16

int main(int argc, char* argv[])
{
	if(argc<4)
	{
		printf("Usage: %s [ e | d | f | F ] <password> <texts/filename>\n", argv[0]); 
		printf("Option 'e' and 'd' denotes encrpytion/decrpytion.\n");
		printf("Optino 'f' and 'F' for file encrpytion/decrpytion.\n");
		return 0;
	}
	
	AES crpty;
	char key[LEN*2], raw[LEN+1], sec[LEN+1], dec[LEN+1];
	
	try
	{
        memset(key, '\0', LEN+1);
        memset(raw, '\0', LEN+1);
        memset(sec, '\0', LEN+1);
        memset(dec, '\0', LEN+1);

		while(strlen(key) < LEN)
			strcat(key, argv[2]);
		
		crpty.MakeKey(key);
		int t;
		
		switch(argv[1][0])
		{
		case 'e':
			strncpy(raw, argv[3], LEN);
			crpty.Encrypt(raw, sec, LEN);
			printf("Raw texts: [%s]\n", raw);
			printf("Encryption: [");
			for(int i=0;i<LEN;i++)
			{
				printf("%02x", (unsigned char)sec[i]);
			}
			printf("]\n");;
			break;
		case 'd':
			int i;
			char hexstr[1024];
			strcpy(hexstr, argv[3]);
			char *phead;
			char tmp[8];
			phead = hexstr;
			for(i=0; i<LEN; i++)
			{
				strncpy(tmp, phead, 2);
				t = strtol(tmp, NULL, 16);
				raw[i] = t;
				phead += 2;
			}
			crpty.Decrypt(raw, dec, LEN);
			printf("Encrpytion: [");
			for(i=0;i<LEN;i++)
			{
				printf("%02x", (unsigned char)raw[i]);
			}
			printf("]\n");
			printf("Decrpytion: [%s]\n", dec);
			break;
		case 'f':
			crpty.Encrypt(argv[3], "encrypt");
			break;
		case 'F':
			crpty.Decrypt(argv[3], "decrypt");
			break;
		default:
			break;
		}
	}
	catch(exception& ex)
	{
		printf("%s\n", ex.what());;
	}
	
	return 0;
}
