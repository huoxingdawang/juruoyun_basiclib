#include "main.h"
using namespace std;
void print(unsigned char* state)
{
	for(int i=0;i<16;i++)
		printf("%s%X ",state[i]>15 ? "" : "0",state[i]);
	printf("\n");
}

int main()
{
	unsigned char out[16]; 
	unsigned char inp[]={0x32,0x43,0xf6,0xa8,0x88,0x5a,0x30,0x8d,0x31,0x31,0x98,0xa2,0xe0,0x37,0x07,0x34};
	unsigned char key[]={0x2b,0x7e,0x15,0x16,0x28,0xae,0xd2,0xa6,0xab,0xf7,0x15,0x88,0x09,0xcf,0x4f,0x3c};
	printf("Origin:\n");
	print(inp);	
	jry_bl_aes aes(key);
	aes.encode(inp,out);
	printf("After encode:\n");
	print(out);	
	aes.decode(out);
	printf("After decode:\n");
	print(out);
	
	jry_bl_string a="juruoyunjuruoyunjuruoyunjuruoyunjuruoyunjuruoyunjuruoyun",b;
	printf("Origin:\n");
	cout<<a<<endl;
	b<<aes.encode(a);
	printf("After encode:\n");
	for(int j=0; j<32; j++)printf("%X ",(unsigned char)b[j]);	
	printf("\nAfter decode:\n");
	b<<aes.decode(b);
	cout<<b;

	
}
