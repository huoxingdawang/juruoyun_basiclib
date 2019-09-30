/* Copyright (c) [2019] juruoyun developer team
	 Juruoyun basic lib is licensed under the Mulan PSL v1.
	 You can use this software according to the terms and conditions of the Mulan PSL v1.
	 You may obtain a copy of Mulan PSL v1 at:
			http://license.coscl.org.cn/MulanPSL
	 THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR
	 IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR
	 PURPOSE.
	 See the Mulan PSL v1 for more details.*/
#include "jry_bl_md5.h"
const unsigned char jry_bl_md5::padding[64]={0x80};
jry_bl_md5::jry_bl_md5(jry_bl_string& message)
{
	finished=false;
	count[0]=count[1]=0;
	state[0]=0x67452301;
	state[1]=0xefcdab89;
	state[2]=0x98badcfe;
	state[3]=0x10325476;	
	init((const unsigned char*)message.get_s(),message.get_length());
}
void jry_bl_md5::init(const unsigned char* input, JRY_BL_STRING_SIZE_TYPE len)
{
	register unsigned int i,index,partlen;
	finished=false;
	index=(unsigned int)((count[0]>>3)&0x3f);
	if ((count[0]+=((unsigned int)len<<3))<((unsigned int)len<<3))
		++count[1];
	count[1]+=((unsigned int)len>>29);
	partlen=64-index;
	if (len>=partlen)
	{
		memcpy(&buffer[index],input,partlen);
		transform(buffer);
		for(i=partlen;i+63<len;i+=64)
			transform(&input[i]);
		index = 0;
	}
	else
		i = 0;
	memcpy(&buffer[index],&input[i],len-i);
}
void jry_bl_md5::transform(const unsigned char block[64])
{
	register unsigned int a=state[0],b=state[1],c=state[2],d=state[3],x[16];
	decode(block,x,64);
	JRY_BL_MD5_FF(a,b,c,d,x[ 0], 7,0xd76aa478);
	JRY_BL_MD5_FF(d,a,b,c,x[ 1],12,0xe8c7b756);
	JRY_BL_MD5_FF(c,d,a,b,x[ 2],17,0x242070db);
	JRY_BL_MD5_FF(b,c,d,a,x[ 3],22,0xc1bdceee);
	JRY_BL_MD5_FF(a,b,c,d,x[ 4], 7,0xf57c0faf);
	JRY_BL_MD5_FF(d,a,b,c,x[ 5],12,0x4787c62a);
	JRY_BL_MD5_FF(c,d,a,b,x[ 6],17,0xa8304613);
	JRY_BL_MD5_FF(b,c,d,a,x[ 7],22,0xfd469501);
	JRY_BL_MD5_FF(a,b,c,d,x[ 8], 7,0x698098d8);
	JRY_BL_MD5_FF(d,a,b,c,x[ 9],12,0x8b44f7af);
	JRY_BL_MD5_FF(c,d,a,b,x[10],17,0xffff5bb1);
	JRY_BL_MD5_FF(b,c,d,a,x[11],22,0x895cd7be);
	JRY_BL_MD5_FF(a,b,c,d,x[12], 7,0x6b901122);
	JRY_BL_MD5_FF(d,a,b,c,x[13],12,0xfd987193);
	JRY_BL_MD5_FF(c,d,a,b,x[14],17,0xa679438e);
	JRY_BL_MD5_FF(b,c,d,a,x[15],22,0x49b40821);
	JRY_BL_MD5_GG(a,b,c,d,x[ 1], 5,0xf61e2562);
	JRY_BL_MD5_GG(d,a,b,c,x[ 6], 9,0xc040b340);
	JRY_BL_MD5_GG(c,d,a,b,x[11],14,0x265e5a51);
	JRY_BL_MD5_GG(b,c,d,a,x[ 0],20,0xe9b6c7aa);
	JRY_BL_MD5_GG(a,b,c,d,x[ 5], 5,0xd62f105d);
	JRY_BL_MD5_GG(d,a,b,c,x[10], 9,0x02441453);
	JRY_BL_MD5_GG(c,d,a,b,x[15],14,0xd8a1e681);
	JRY_BL_MD5_GG(b,c,d,a,x[ 4],20,0xe7d3fbc8);
	JRY_BL_MD5_GG(a,b,c,d,x[ 9], 5,0x21e1cde6);
	JRY_BL_MD5_GG(d,a,b,c,x[14], 9,0xc33707d6);
	JRY_BL_MD5_GG(c,d,a,b,x[ 3],14,0xf4d50d87);
	JRY_BL_MD5_GG(b,c,d,a,x[ 8],20,0x455a14ed);
	JRY_BL_MD5_GG(a,b,c,d,x[13], 5,0xa9e3e905);
	JRY_BL_MD5_GG(d,a,b,c,x[ 2], 9,0xfcefa3f8);
	JRY_BL_MD5_GG(c,d,a,b,x[ 7],14,0x676f02d9);
	JRY_BL_MD5_GG(b,c,d,a,x[12],20,0x8d2a4c8a);
	JRY_BL_MD5_HH(a,b,c,d,x[ 5], 4,0xfffa3942);
	JRY_BL_MD5_HH(d,a,b,c,x[ 8],11,0x8771f681);
	JRY_BL_MD5_HH(c,d,a,b,x[11],16,0x6d9d6122);
	JRY_BL_MD5_HH(b,c,d,a,x[14],23,0xfde5380c);
	JRY_BL_MD5_HH(a,b,c,d,x[ 1], 4,0xa4beea44);
	JRY_BL_MD5_HH(d,a,b,c,x[ 4],11,0x4bdecfa9);
	JRY_BL_MD5_HH(c,d,a,b,x[ 7],16,0xf6bb4b60);
	JRY_BL_MD5_HH(b,c,d,a,x[10],23,0xbebfbc70);
	JRY_BL_MD5_HH(a,b,c,d,x[13], 4,0x289b7ec6);
	JRY_BL_MD5_HH(d,a,b,c,x[ 0],11,0xeaa127fa);
	JRY_BL_MD5_HH(c,d,a,b,x[ 3],16,0xd4ef3085);
	JRY_BL_MD5_HH(b,c,d,a,x[ 6],23,0x04881d05);
	JRY_BL_MD5_HH(a,b,c,d,x[ 9], 4,0xd9d4d039);
	JRY_BL_MD5_HH(d,a,b,c,x[12],11,0xe6db99e5);
	JRY_BL_MD5_HH(c,d,a,b,x[15],16,0x1fa27cf8);
	JRY_BL_MD5_HH(b,c,d,a,x[ 2],23,0xc4ac5665);
	JRY_BL_MD5_II(a,b,c,d,x[ 0], 6,0xf4292244);
	JRY_BL_MD5_II(d,a,b,c,x[ 7],10,0x432aff97);
	JRY_BL_MD5_II(c,d,a,b,x[14],15,0xab9423a7);
	JRY_BL_MD5_II(b,c,d,a,x[ 5],21,0xfc93a039);
	JRY_BL_MD5_II(a,b,c,d,x[12], 6,0x655b59c3);
	JRY_BL_MD5_II(d,a,b,c,x[ 3],10,0x8f0ccc92);
	JRY_BL_MD5_II(c,d,a,b,x[10],15,0xffeff47d);
	JRY_BL_MD5_II(b,c,d,a,x[ 1],21,0x85845dd1);
	JRY_BL_MD5_II(a,b,c,d,x[ 8], 6,0x6fa87e4f);
	JRY_BL_MD5_II(d,a,b,c,x[15],10,0xfe2ce6e0);
	JRY_BL_MD5_II(c,d,a,b,x[ 6],15,0xa3014314);
	JRY_BL_MD5_II(b,c,d,a,x[13],21,0x4e0811a1);
	JRY_BL_MD5_II(a,b,c,d,x[ 4], 6,0xf7537e82);
	JRY_BL_MD5_II(d,a,b,c,x[11],10,0xbd3af235);
	JRY_BL_MD5_II(c,d,a,b,x[ 2],15,0x2ad7d2bb);
	JRY_BL_MD5_II(b,c,d,a,x[ 9],21,0xeb86d391);
	state[0]+=a;state[1]+=b;state[2]+=c;state[3]+=d;
}
void jry_bl_md5::decode(const unsigned char* input, unsigned int* output, JRY_BL_STRING_SIZE_TYPE length)
{
	for(JRY_BL_STRING_SIZE_TYPE i=0,j=0;j<length;++i,j+=4)
		output[i]=((unsigned int)input[j])|(((unsigned int)input[j+1])<<8)|(((unsigned int)input[j+2])<<16)|(((unsigned int)input[j+3])<<24);
}
void jry_bl_md5::encode(const unsigned int* input,unsigned char* output,JRY_BL_STRING_SIZE_TYPE length)
{
	for(JRY_BL_STRING_SIZE_TYPE i=0,j=0;j<length;++i,j+=4)
		output[j]=(unsigned char)(input[i]&0xff),output[j+1]=(unsigned char)((input[i]>>8)&0xff),output[j+2]=(unsigned char)((input[i]>>16)&0xff),output[j+3]=(unsigned char)((input[i]>>24)&0xff);
}
const unsigned char* jry_bl_md5::get_digest()
{
	if (!finished)
	{
		finished=true;
		register unsigned char bits[8];
		register unsigned int  oldstate[4],oldcount[2],index,padlen;
		memcpy(oldstate,state,16);
		memcpy(oldcount,count,8);
		encode(count,bits,8);
		index=(unsigned int)((count[0]>>3)&0x3f);
		padlen=(index<56)?(56-index):(120-index);
		init(padding,padlen);
		init(bits,8);
		encode(state,digest,16);
		memcpy(state,oldstate,16);
		memcpy(count,oldcount,8);
	}
	return digest;
}
jry_bl_string jry_bl_md5::get_string()
{
	register const unsigned char* digestt=get_digest();
	jry_bl_string str;
	str.extend(16<<1);
	for (JRY_BL_STRING_SIZE_TYPE i=0;i<16;++i)
		str+=jry_bl_md5_hex_humbers[digestt[i]/16],str+=jry_bl_md5_hex_humbers[digestt[i]%16];
	return str;
}