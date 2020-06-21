#include "stdio.h"
#include "string.h"
#include "stdlib.h"
typedef char				jbl_int8;
typedef unsigned char		jbl_uint8;
typedef short				jbl_int16;
typedef unsigned short		jbl_uint16;
typedef int					jbl_int32;
typedef unsigned int		jbl_uint32;
typedef long long			jbl_int64;
typedef unsigned long long	jbl_uint64;
//手动添加以下映射
//unicode	gb2312
//0x00A3	0xA1EA	￡
//0x00B4	0xA1E4	′
#include "table.c"
typedef struct 
{
	jbl_uint16 a;
	jbl_uint16 b;
}datttt;
int cmp(const void *a,const void *b)
{
	jbl_uint16 aa=((datttt*)a)->a;	
	jbl_uint16 bb=((datttt*)b)->a;	
	return aa==bb?0:aa>bb?1:-1;
}
#define encode "0x%04X,0x%04X,"
void main()
{
	jbl_uint32 utg_len=(const jbl_uint32)((sizeof utg)>>2)-1;//unicode 和 gb2312各占两个字节
	jbl_uint32 gtu_len=(const jbl_uint32)((sizeof gtu)>>2)-1;//unicode 和 gb2312各占两个字节
		
	
	qsort(utg,utg_len,4,cmp);
	qsort(gtu,gtu_len,4,cmp);
	FILE *fp=fopen("data.c","wb");
	fprintf(fp,"/* Copyright (c) [2020] juruoyun developer team\n"
"   Juruoyun basic lib is licensed under the Mulan PSL v1.\n"
"   You can use this software according to the terms and conditions of the Mulan PSL v1.\n"
"   You may obtain a copy of Mulan PSL v1 at:\n"
"      http://license.coscl.org.cn/MulanPSL\n"
"   THIS SOFTWARE IS PROVIDED ON AN \"AS IS\" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR\n"
"   IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR\n"
"   PURPOSE.\n"
"   See the Mulan PSL v1 for more details.*/\n");
	fprintf(fp,"static const jbl_uint16 __jbl_string_utg_table[]={");
	for(jbl_uint32 i=0;i<utg_len+1;(i%8)?0:fprintf(fp,"\n\t"),fprintf(fp,encode,utg[i<<1],utg[(i<<1)+1]),++i);
	fprintf(fp,"\n};\n");
	fprintf(fp,"static const jbl_uint16 __jbl_string_gtu_table[]={");
	for(jbl_uint32 i=0;i<gtu_len+1;(i%8)?0:fprintf(fp,"\n\t"),fprintf(fp,encode,gtu[i<<1],gtu[(i<<1)+1]),++i);
	fprintf(fp,"\n};\n");
	fclose(fp);	
	fp=fopen("table.c","wb");
	fprintf(fp,"jbl_uint16 utg[]={");
	for(jbl_uint32 i=0;i<utg_len+1;(i%8)?0:fprintf(fp,"\n\t"),fprintf(fp,encode,utg[i<<1],utg[(i<<1)+1]),++i);
	fprintf(fp,"\n};\n");
	fprintf(fp,"jbl_uint16 gtu[]={");
	for(jbl_uint32 i=0;i<gtu_len+1;(i%8)?0:fprintf(fp,"\n\t"),fprintf(fp,encode,gtu[i<<1],gtu[(i<<1)+1]),++i);
	fprintf(fp,"\n};\n");
	fclose(fp);
		
	fp=fopen("jbl_string_code_change_gb2312_utf8_table.bin","wb");
	fwrite(utg,sizeof utg,1,fp);
	fwrite(gtu,sizeof gtu,1,fp);
	fclose(fp);
	
	
	
	
}