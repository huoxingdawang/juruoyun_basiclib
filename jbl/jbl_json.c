/* Generated by re2c 1.3 on Tue Sep 15 18:31:38 2020 */
#line 1 "jbl/jbl_json.l"
/* Copyright (c) [2020] juruoyun developer team
   Juruoyun basic lib is licensed under the Mulan PSL v1.
   You can use this software according to the terms and conditions of the Mulan PSL v1.
   You may obtain a copy of Mulan PSL v1 at:
      http://license.coscl.org.cn/MulanPSL
   THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR
   PURPOSE.
   See the Mulan PSL v1 for more details.*/
#include "jbl_json.h"
#if JBL_JSON_ENABLE==1
#include "jbl_string.h"
#include "jbl_string_cc.h"
#include "jbl_stream.h"
#include "jbl_ll.h"
#include "jbl_ht.h"
#include "jbl_log.h"
#if JBL_JSON_DEBUG ==0
	#undef jbl_log
	#define jbl_log(x,...)
#endif
struct __jbl_json_decode_yy
{
	jbl_uint8		cond;
	jbl_uint8		state;
	jbl_uint8		ch;
	struct
	{
		jbl_int8	f:2;
		jbl_int8	type:4;	
	};
	unsigned char *	marker;
//	jbl_string    *	k;
	void          *	v;
	struct __jbl_json_decode_yy *pre;
	union
	{
		jbl_uint64	u;
		double		d;
	}tmp;
	jbl_string* htk;
	jbl_uint8	dl;
};
#define ARRAY	1
#define HTK		2
#define HTV		3
struct __jbl_json_decode_yy* __jbl_json_decode_yy_new()
{
	struct __jbl_json_decode_yy*yy=jbl_malloc(sizeof(struct __jbl_json_decode_yy));
	yy->cond	=0;
	yy->state	=0;		
	yy->ch		=0;
	yy->marker	=NULL;
	yy->v		=NULL;
	yy->pre		=NULL;
	yy->htk		=NULL;
	return yy;
	
}
struct __jbl_json_decode_yy* __jbl_json_decode_yy_free(struct __jbl_json_decode_yy* yy)
{
	if(!yy)return NULL;
	jbl_var_free(yy->v);
	jbl_string_free(yy->htk);
	__jbl_json_decode_yy_free(yy->pre);
	jbl_free(yy);
	return NULL;
}
#line 72 "jbl/jbl_json.c"
enum jbl_json_condition {
	jbl_json_condition_0,
	jbl_json_condition_start,
	jbl_json_condition_string,
	jbl_json_condition_string_turn,
	jbl_json_condition_string_u,
	jbl_json_condition_hex,
	jbl_json_condition_num,
	jbl_json_condition_flo,
	jbl_json_condition_e,
};
#line 69 "jbl/jbl_json.l"

//-1 完成
//-2致命错误
//-3更多输入
struct __jbl_json_decode_yy* __jbl_json_decode(struct __jbl_json_decode_yy* yy,unsigned char* in,unsigned char*YYLIMIT,jbl_string_size_type *start)
{
	jbl_string_size_type _=0;if(!start)start=&_;
start:;
#define upd *start=YYCURSOR-in	
	unsigned char	*	YYCURSOR=in+*start;
//
#line 96 "jbl/jbl_json.c"

	switch (yy->state) {
	default: goto yy0;
	case 0: goto yyFillLabel0;
	case 1: goto yyFillLabel1;
	case 2: goto yyFillLabel2;
	case 3: goto yyFillLabel3;
	case 4: goto yyFillLabel4;
	case 5: goto yyFillLabel5;
	case 6: goto yyFillLabel6;
	case 7: goto yyFillLabel7;
	}
yy0:
	switch (yy->cond) {
	case jbl_json_condition_0: goto yyc_0;
	case jbl_json_condition_start: goto yyc_start;
	case jbl_json_condition_string: goto yyc_string;
	case jbl_json_condition_string_turn: goto yyc_string_turn;
	case jbl_json_condition_string_u: goto yyc_string_u;
	case jbl_json_condition_hex: goto yyc_hex;
	case jbl_json_condition_num: goto yyc_num;
	case jbl_json_condition_flo: goto yyc_flo;
	case jbl_json_condition_e: goto yyc_e;
	}
/* *********************************** */
yyc_0:
	yy->cond = (jbl_json_condition_start);
	goto yyc_start;
/* *********************************** */
yyc_start:
	yy->state = (0);
	if ((YYLIMIT - YYCURSOR) < 5) {upd;return yy;}
yyFillLabel0:
	yy->ch = *(yy->marker = YYCURSOR);
	switch (yy->ch) {
	case 0x00:	goto yy7;
	case 0x01:
	case 0x02:
	case 0x03:
	case 0x04:
	case 0x05:
	case 0x06:
	case 0x07:
	case 0x08:
	case '\t':
	case '\n':
	case '\v':
	case '\f':
	case '\r':
	case 0x0E:
	case 0x0F:
	case 0x10:
	case 0x11:
	case 0x12:
	case 0x13:
	case 0x14:
	case 0x15:
	case 0x16:
	case 0x17:
	case 0x18:
	case 0x19:
	case 0x1A:
	case 0x1B:
	case 0x1C:
	case 0x1D:
	case 0x1E:
	case 0x1F:
	case ' ':	goto yy9;
	case '"':	goto yy11;
	case '+':	goto yy13;
	case ',':	goto yy15;
	case '-':	goto yy17;
	case '.':	goto yy19;
	case '0':	goto yy21;
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':	goto yy23;
	case ':':	goto yy24;
	case '[':	goto yy26;
	case ']':	goto yy28;
	case 'f':	goto yy30;
	case 'n':	goto yy32;
	case 't':	goto yy33;
	case '{':	goto yy34;
	case '}':	goto yy36;
	default:	goto yy6;
	}
yy6:
#line 104 "jbl/jbl_json.l"
	{																							;return yy;}
#line 193 "jbl/jbl_json.c"
yy7:
	++YYCURSOR;
#line 261 "jbl/jbl_json.l"
	{yy->cond=-1;return yy;}
#line 198 "jbl/jbl_json.c"
yy9:
	++YYCURSOR;
#line 94 "jbl/jbl_json.l"
	{upd																						;goto yyc_start;}
#line 203 "jbl/jbl_json.c"
yy11:
	++YYCURSOR;
	yy->cond = (jbl_json_condition_string);
#line 95 "jbl/jbl_json.l"
	{upd;yy->v=jbl_var_free(yy->v);yy->v=jbl_string_new(yy->v)									;goto yyc_string;}
#line 209 "jbl/jbl_json.c"
yy13:
	++YYCURSOR;
	yy->cond = (jbl_json_condition_num);
#line 99 "jbl/jbl_json.l"
	{upd;yy->v=jbl_var_free(yy->v);yy->tmp.u=0;yy->f=1											;goto yyc_num;}
#line 215 "jbl/jbl_json.c"
yy15:
	++YYCURSOR;
#line 219 "jbl/jbl_json.l"
	{
																	if(yy->type==ARRAY)
																	{
																		upd;
																		struct __jbl_json_decode_yy* yy2=yy->pre;
																		if(yy->v)
																			yy2->v=jbl_ll_add(yy2->v,yy->v);
																		else
																		{
																			jbl_log(UC"JSON decode error %s",in);
																			yy->cond=-2;
																			return yy;
																		}
																		yy->v=jbl_var_free(yy->v);
																		goto yyc_start;
																	}
																	else if(yy->type==HTV&&yy->htk)
																	{
																		upd;
																		struct __jbl_json_decode_yy* yy2=yy->pre;
																		if(yy->v)
																			yy2->v=jbl_ht_insert(yy2->v,yy->htk,yy->v);
																		else
																		{
																			jbl_log(UC"JSON decode error %s",in);
																			yy->cond=-2;
																			return yy;
																		}
																		yy->v=jbl_var_free(yy->v);
																		yy->htk=jbl_string_free(yy->htk);
																		yy->type=HTK;
																		goto yyc_start;																		
																	}
																	else
																	{
																		jbl_log(UC"JSON decode error %s",in);
																		yy->cond=-2;
																		return yy;
																	}
																}
#line 259 "jbl/jbl_json.c"
yy17:
	++YYCURSOR;
	yy->cond = (jbl_json_condition_num);
#line 98 "jbl/jbl_json.l"
	{upd;yy->v=jbl_var_free(yy->v);yy->tmp.u=0;yy->f=-1											;goto yyc_num;}
#line 265 "jbl/jbl_json.c"
yy19:
	++YYCURSOR;
	yy->cond = (jbl_json_condition_flo);
#line 100 "jbl/jbl_json.l"
	{upd;yy->v=jbl_var_free(yy->v);yy->f=1;yy->dl=0;											;goto yyc_flo;}
#line 271 "jbl/jbl_json.c"
yy21:
	yy->ch = *++YYCURSOR;
	switch (yy->ch) {
	case 'X':
	case 'x':	goto yy38;
	default:	goto yy22;
	}
yy22:
	yy->cond = (jbl_json_condition_num);
#line 97 "jbl/jbl_json.l"
	{upd;yy->v=jbl_var_free(yy->v);yy->tmp.u=*(YYCURSOR-1)-'0';yy->f=1							;goto yyc_num;}
#line 283 "jbl/jbl_json.c"
yy23:
	++YYCURSOR;
	goto yy22;
yy24:
	++YYCURSOR;
#line 203 "jbl/jbl_json.l"
	{
																	if(yy->type==HTK&&jbl_var_is(yy->v,jbl_string_operators))
																	{
																		upd;
																		yy->htk=(jbl_string*)yy->v;
																		yy->v=NULL;
																		yy->type=HTV;
																		goto start;
																	}
																	else
																	{
																		jbl_log(UC"JSON decode error %s",in);
																		yy->cond=-2;
																		return yy;
																	}
																}
#line 306 "jbl/jbl_json.c"
yy26:
	++YYCURSOR;
#line 149 "jbl/jbl_json.l"
	{
																	upd;yy->v=jbl_var_free(yy->v);yy->v=jbl_ll_new(yy->v);
																	struct __jbl_json_decode_yy* yy2=__jbl_json_decode_yy_new();
																	yy2->type=ARRAY;
																	yy2->pre=yy;
																	yy=yy2;
																	goto start;
																}
#line 318 "jbl/jbl_json.c"
yy28:
	++YYCURSOR;
#line 157 "jbl/jbl_json.l"
	{
																	if(yy->type==ARRAY)
																	{
																		upd;
																		struct __jbl_json_decode_yy* yy2=yy->pre;
																		if(yy->v)
																			yy2->v=jbl_ll_add(yy2->v,yy->v);
																		yy->pre=NULL;
																		yy=__jbl_json_decode_yy_free(yy);
																		yy=yy2;
																		goto start;
																	}
																	else
																	{
																		yy->cond=-2;
																		jbl_log(UC"JSON decode error %d %j %s",yy->type,yy->v,in);
																		return yy;
																	}
																}
#line 341 "jbl/jbl_json.c"
yy30:
	yy->ch = *++YYCURSOR;
	switch (yy->ch) {
	case 'a':	goto yy40;
	default:	goto yy31;
	}
yy31:
	YYCURSOR = yy->marker;
	goto yy6;
yy32:
	yy->ch = *++YYCURSOR;
	switch (yy->ch) {
	case 'u':	goto yy41;
	default:	goto yy31;
	}
yy33:
	yy->ch = *++YYCURSOR;
	switch (yy->ch) {
	case 'r':	goto yy42;
	default:	goto yy31;
	}
yy34:
	++YYCURSOR;
#line 176 "jbl/jbl_json.l"
	{
																	upd;yy->v=jbl_var_free(yy->v);yy->v=jbl_ht_new(yy->v);
																	struct __jbl_json_decode_yy* yy2=__jbl_json_decode_yy_new();
																	yy2->type=HTK;
																	yy2->pre=yy;
																	yy=yy2;
																	goto start;
																}
#line 374 "jbl/jbl_json.c"
yy36:
	++YYCURSOR;
#line 184 "jbl/jbl_json.l"
	{
																	if((yy->type==HTK&&!yy->htk)||(yy->type==HTV&&yy->v))
																	{
																		upd;
																		struct __jbl_json_decode_yy* yy2=yy->pre;
																		if(yy->v)
																			yy2->v=jbl_ht_insert(yy2->v,yy->htk,yy->v);
																		yy->pre=NULL;
																		yy=__jbl_json_decode_yy_free(yy);
																		yy=yy2;
																		goto start;																					
																	}
																	else
																	{
																		jbl_log(UC"JSON decode error %d %j %j %s",yy->type,yy->htk,yy->v,in);
																		yy->cond=-2;
																		return yy;
																	}
																}
#line 397 "jbl/jbl_json.c"
yy38:
	++YYCURSOR;
	yy->cond = (jbl_json_condition_hex);
#line 96 "jbl/jbl_json.l"
	{upd;yy->v=jbl_var_free(yy->v);yy->tmp.u=0													;goto yyc_hex;}
#line 403 "jbl/jbl_json.c"
yy40:
	yy->ch = *++YYCURSOR;
	switch (yy->ch) {
	case 'l':	goto yy43;
	default:	goto yy31;
	}
yy41:
	yy->ch = *++YYCURSOR;
	switch (yy->ch) {
	case 'l':	goto yy44;
	default:	goto yy31;
	}
yy42:
	yy->ch = *++YYCURSOR;
	switch (yy->ch) {
	case 'u':	goto yy45;
	default:	goto yy31;
	}
yy43:
	yy->ch = *++YYCURSOR;
	switch (yy->ch) {
	case 's':	goto yy46;
	default:	goto yy31;
	}
yy44:
	yy->ch = *++YYCURSOR;
	switch (yy->ch) {
	case 'l':	goto yy47;
	default:	goto yy31;
	}
yy45:
	yy->ch = *++YYCURSOR;
	switch (yy->ch) {
	case 'e':	goto yy49;
	default:	goto yy31;
	}
yy46:
	yy->ch = *++YYCURSOR;
	switch (yy->ch) {
	case 'e':	goto yy51;
	default:	goto yy31;
	}
yy47:
	++YYCURSOR;
#line 102 "jbl/jbl_json.l"
	{upd;yy->v=jbl_var_free(yy->v);yy->v=jbl_Vnull_new()										;goto yyc_start;}
#line 450 "jbl/jbl_json.c"
yy49:
	++YYCURSOR;
#line 101 "jbl/jbl_json.l"
	{upd;yy->v=jbl_var_free(yy->v);yy->v=jbl_Vtrue_new()										;goto yyc_start;}
#line 455 "jbl/jbl_json.c"
yy51:
	++YYCURSOR;
#line 103 "jbl/jbl_json.l"
	{upd;yy->v=jbl_var_free(yy->v);yy->v=jbl_Vfalse_new()										;goto yyc_start;}
#line 460 "jbl/jbl_json.c"
/* *********************************** */
yyc_string:
	yy->state = (1);
	if (YYLIMIT <= YYCURSOR) {upd;return yy;}
yyFillLabel1:
	yy->ch = *YYCURSOR;
	switch (yy->ch) {
	case 0x00:	goto yy56;
	case '"':	goto yy58;
	case '\\':	goto yy60;
	default:	goto yy55;
	}
yy55:
#line 109 "jbl/jbl_json.l"
	{upd;yy->v=jbl_string_add_char(yy->v,*YYCURSOR)			;++YYCURSOR;upd						;goto yyc_string;}
#line 476 "jbl/jbl_json.c"
yy56:
	++YYCURSOR;
#line 261 "jbl/jbl_json.l"
	{yy->cond=-1;return yy;}
#line 481 "jbl/jbl_json.c"
yy58:
	++YYCURSOR;
	yy->cond = (jbl_json_condition_start);
#line 108 "jbl/jbl_json.l"
	{upd																						;goto yyc_start;}
#line 487 "jbl/jbl_json.c"
yy60:
	++YYCURSOR;
	yy->cond = (jbl_json_condition_string_turn);
#line 110 "jbl/jbl_json.l"
	{upd																						;goto yyc_string_turn;}
#line 493 "jbl/jbl_json.c"
/* *********************************** */
yyc_string_turn:
	yy->state = (2);
	if (YYLIMIT <= YYCURSOR) {upd;return yy;}
yyFillLabel2:
	yy->ch = *YYCURSOR;
	switch (yy->ch) {
	case 0x00:	goto yy65;
	case '"':	goto yy67;
	case '\\':	goto yy69;
	case 'b':	goto yy71;
	case 'f':	goto yy73;
	case 'n':	goto yy75;
	case 'r':	goto yy77;
	case 't':	goto yy79;
	case 'u':	goto yy81;
	default:	goto yy64;
	}
yy64:
	yy->cond = (jbl_json_condition_string);
#line 119 "jbl/jbl_json.l"
	{upd;																						;goto yyc_string;}
#line 516 "jbl/jbl_json.c"
yy65:
	++YYCURSOR;
#line 261 "jbl/jbl_json.l"
	{yy->cond=-1;return yy;}
#line 521 "jbl/jbl_json.c"
yy67:
	++YYCURSOR;
	yy->cond = (jbl_json_condition_string);
#line 112 "jbl/jbl_json.l"
	{upd;yy->v=jbl_string_add_char(yy->v,'"')													;goto yyc_string;}
#line 527 "jbl/jbl_json.c"
yy69:
	++YYCURSOR;
	yy->cond = (jbl_json_condition_string);
#line 111 "jbl/jbl_json.l"
	{upd;yy->v=jbl_string_add_char(yy->v,'\\')													;goto yyc_string;}
#line 533 "jbl/jbl_json.c"
yy71:
	++YYCURSOR;
	yy->cond = (jbl_json_condition_string);
#line 113 "jbl/jbl_json.l"
	{upd;yy->v=jbl_string_add_char(yy->v,'\b')													;goto yyc_string;}
#line 539 "jbl/jbl_json.c"
yy73:
	++YYCURSOR;
	yy->cond = (jbl_json_condition_string);
#line 114 "jbl/jbl_json.l"
	{upd;yy->v=jbl_string_add_char(yy->v,'\f')													;goto yyc_string;}
#line 545 "jbl/jbl_json.c"
yy75:
	++YYCURSOR;
	yy->cond = (jbl_json_condition_string);
#line 115 "jbl/jbl_json.l"
	{upd;yy->v=jbl_string_add_char(yy->v,'\n')													;goto yyc_string;}
#line 551 "jbl/jbl_json.c"
yy77:
	++YYCURSOR;
	yy->cond = (jbl_json_condition_string);
#line 116 "jbl/jbl_json.l"
	{upd;yy->v=jbl_string_add_char(yy->v,'\r')													;goto yyc_string;}
#line 557 "jbl/jbl_json.c"
yy79:
	++YYCURSOR;
	yy->cond = (jbl_json_condition_string);
#line 117 "jbl/jbl_json.l"
	{upd;yy->v=jbl_string_add_char(yy->v,'\t')													;goto yyc_string;}
#line 563 "jbl/jbl_json.c"
yy81:
	++YYCURSOR;
	yy->cond = (jbl_json_condition_string_u);
#line 118 "jbl/jbl_json.l"
	{upd;yy->tmp.u=0																			;goto yyc_string_u;}
#line 569 "jbl/jbl_json.c"
/* *********************************** */
yyc_string_u:
	yy->state = (3);
	if (YYLIMIT <= YYCURSOR) {upd;return yy;}
yyFillLabel3:
	yy->ch = *YYCURSOR;
	switch (yy->ch) {
	case 0x00:	goto yy86;
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':	goto yy88;
	case 'A':
	case 'B':
	case 'C':
	case 'D':
	case 'E':
	case 'F':	goto yy90;
	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'e':
	case 'f':	goto yy92;
	default:	goto yy85;
	}
yy85:
	yy->cond = (jbl_json_condition_string);
#line 124 "jbl/jbl_json.l"
	{upd;yy->v=jbl_string_add_utf8_from_unicode(yy->v,yy->tmp.u)								;goto yyc_string;}
#line 606 "jbl/jbl_json.c"
yy86:
	++YYCURSOR;
#line 123 "jbl/jbl_json.l"
	{																							;return yy;}
#line 611 "jbl/jbl_json.c"
yy88:
	++YYCURSOR;
#line 120 "jbl/jbl_json.l"
	{upd;yy->tmp.u=(yy->tmp.u<<4)+*(YYCURSOR-1)-'0'												;goto yyc_string_u;}
#line 616 "jbl/jbl_json.c"
yy90:
	++YYCURSOR;
#line 122 "jbl/jbl_json.l"
	{upd;yy->tmp.u=(yy->tmp.u<<4)+*(YYCURSOR-1)-'A'+10											;goto yyc_string_u;}
#line 621 "jbl/jbl_json.c"
yy92:
	++YYCURSOR;
#line 121 "jbl/jbl_json.l"
	{upd;yy->tmp.u=(yy->tmp.u<<4)+*(YYCURSOR-1)-'a'+10											;goto yyc_string_u;}
#line 626 "jbl/jbl_json.c"
/* *********************************** */
yyc_hex:
	yy->state = (4);
	if (YYLIMIT <= YYCURSOR) {upd;return yy;}
yyFillLabel4:
	yy->ch = *YYCURSOR;
	switch (yy->ch) {
	case 0x00:	goto yy97;
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':	goto yy99;
	case 'A':
	case 'B':
	case 'C':
	case 'D':
	case 'E':
	case 'F':	goto yy101;
	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'e':
	case 'f':	goto yy103;
	default:	goto yy96;
	}
yy96:
	yy->cond = (jbl_json_condition_start);
#line 129 "jbl/jbl_json.l"
	{upd;yy->v=jbl_Vuint_set(yy->v,yy->tmp.u)													;goto yyc_start;}
#line 663 "jbl/jbl_json.c"
yy97:
	++YYCURSOR;
#line 130 "jbl/jbl_json.l"
	{   ;yy->v=jbl_Vuint_set(yy->v,yy->tmp.u)													;yy->cond=-1;return yy;}
#line 668 "jbl/jbl_json.c"
yy99:
	++YYCURSOR;
#line 126 "jbl/jbl_json.l"
	{upd;yy->tmp.u=(yy->tmp.u<<4)+*(YYCURSOR-1)-'0'												;goto yyc_hex;}
#line 673 "jbl/jbl_json.c"
yy101:
	++YYCURSOR;
#line 128 "jbl/jbl_json.l"
	{upd;yy->tmp.u=(yy->tmp.u<<4)+*(YYCURSOR-1)-'A'+10											;goto yyc_hex;}
#line 678 "jbl/jbl_json.c"
yy103:
	++YYCURSOR;
#line 127 "jbl/jbl_json.l"
	{upd;yy->tmp.u=(yy->tmp.u<<4)+*(YYCURSOR-1)-'a'+10											;goto yyc_hex;}
#line 683 "jbl/jbl_json.c"
/* *********************************** */
yyc_num:
	yy->state = (5);
	if (YYLIMIT <= YYCURSOR) {upd;return yy;}
yyFillLabel5:
	yy->ch = *YYCURSOR;
	switch (yy->ch) {
	case 0x00:	goto yy108;
	case '.':	goto yy110;
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':	goto yy112;
	case 'E':
	case 'e':	goto yy114;
	default:	goto yy107;
	}
yy107:
	yy->cond = (jbl_json_condition_start);
#line 133 "jbl/jbl_json.l"
	{upd;yy->v=((yy->f==1)?jbl_Vuint_set(yy->v,yy->tmp.u):jbl_Vint_set(yy->v,yy->tmp.u*-1))		;goto yyc_start;}
#line 711 "jbl/jbl_json.c"
yy108:
	++YYCURSOR;
#line 134 "jbl/jbl_json.l"
	{   ;yy->v=((yy->f==1)?jbl_Vuint_set(yy->v,yy->tmp.u):jbl_Vint_set(yy->v,yy->tmp.u*-1))		;yy->cond=-1;return yy;}
#line 716 "jbl/jbl_json.c"
yy110:
	++YYCURSOR;
	yy->cond = (jbl_json_condition_flo);
#line 135 "jbl/jbl_json.l"
	{upd;yy->v=jbl_var_free(yy->v);yy->dl=0														;goto yyc_flo;}
#line 722 "jbl/jbl_json.c"
yy112:
	++YYCURSOR;
#line 132 "jbl/jbl_json.l"
	{upd;yy->tmp.u=(yy->tmp.u<<3)+(yy->tmp.u<<1)+*(YYCURSOR-1)-'0'								;goto yyc_num;}
#line 727 "jbl/jbl_json.c"
yy114:
	++YYCURSOR;
	yy->cond = (jbl_json_condition_e);
#line 136 "jbl/jbl_json.l"
	{upd;yy->v=jbl_var_free(yy->v);yy->dl=0;yy->tmp.d=yy->tmp.u;yy->f=1;yy->dl=0				;goto yyc_e;}
#line 733 "jbl/jbl_json.c"
/* *********************************** */
yyc_flo:
	yy->state = (6);
	if (YYLIMIT <= YYCURSOR) {upd;return yy;}
yyFillLabel6:
	yy->ch = *YYCURSOR;
	switch (yy->ch) {
	case 0x00:	goto yy119;
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':	goto yy121;
	case 'E':
	case 'e':	goto yy123;
	default:	goto yy118;
	}
yy118:
	yy->cond = (jbl_json_condition_start);
#line 139 "jbl/jbl_json.l"
	{upd;yy->v=jbl_Vdouble_set(yy->v,yy->f*((double)yy->tmp.u)/jbl_pow(10,yy->dl))				;goto yyc_start;}
#line 760 "jbl/jbl_json.c"
yy119:
	++YYCURSOR;
#line 140 "jbl/jbl_json.l"
	{   ;yy->v=jbl_Vdouble_set(yy->v,yy->f*((double)yy->tmp.u)/jbl_pow(10,yy->dl))				;yy->cond=-1;pl();return yy;}
#line 765 "jbl/jbl_json.c"
yy121:
	++YYCURSOR;
#line 138 "jbl/jbl_json.l"
	{upd;yy->tmp.u=(yy->tmp.u<<3)+(yy->tmp.u<<1)+*(YYCURSOR-1)-'0';++yy->dl;					;goto yyc_flo;}
#line 770 "jbl/jbl_json.c"
yy123:
	++YYCURSOR;
	yy->cond = (jbl_json_condition_e);
#line 141 "jbl/jbl_json.l"
	{upd;yy->tmp.d=yy->f*((double)yy->tmp.u)/jbl_pow(10,yy->dl);yy->f=1;yy->dl=0				;goto yyc_e;}
#line 776 "jbl/jbl_json.c"
/* *********************************** */
yyc_e:
	yy->state = (7);
	if (YYLIMIT <= YYCURSOR) {upd;return yy;}
yyFillLabel7:
	yy->ch = *YYCURSOR;
	switch (yy->ch) {
	case 0x00:	goto yy128;
	case '+':	goto yy130;
	case '-':	goto yy132;
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':	goto yy134;
	default:	goto yy127;
	}
yy127:
	yy->cond = (jbl_json_condition_start);
#line 146 "jbl/jbl_json.l"
	{upd;yy->v=jbl_Vdouble_set(yy->v,yy->tmp.d*jbl_pow((yy->f==1)?10:0.1,yy->dl))				;goto yyc_start;}
#line 803 "jbl/jbl_json.c"
yy128:
	++YYCURSOR;
#line 147 "jbl/jbl_json.l"
	{   ;yy->v=jbl_Vdouble_set(yy->v,yy->tmp.d*jbl_pow((yy->f==1)?10:0.1,yy->dl))				;yy->cond=-1;return yy;}
#line 808 "jbl/jbl_json.c"
yy130:
	++YYCURSOR;
#line 144 "jbl/jbl_json.l"
	{upd;yy->f=1																				;goto yyc_e;}
#line 813 "jbl/jbl_json.c"
yy132:
	++YYCURSOR;
#line 143 "jbl/jbl_json.l"
	{upd;yy->f=-1																				;goto yyc_e;}
#line 818 "jbl/jbl_json.c"
yy134:
	++YYCURSOR;
#line 145 "jbl/jbl_json.l"
	{upd;yy->dl=(yy->dl<<3)+(yy->dl<<1)+*(YYCURSOR-1)-'0'										;goto yyc_e;}
#line 823 "jbl/jbl_json.c"
#line 262 "jbl/jbl_json.l"

	#undef YYCTYPE	


	return yy;
}
jbl_stream *jbl_json_decode_stream_new()
{
	struct __jbl_json_decode_yy* yy=__jbl_json_decode_yy_new();
	jbl_stream * this=jbl_stream_new(&jbl_json_decode_stream_operaters,yy,JBL_JSON_DECODE_STREAM_BUF_LENGTH+1,NULL,1);
	this->extra[0].p=yy;
	return this;
}
static void __jbl_json_decode_stream_usf(jbl_stream* this){this->size=JBL_JSON_DECODE_STREAM_BUF_LENGTH;}
static void __jbl_json_decode_stream_operater(jbl_stream* this,jbl_uint8 flags)
{
	if(!this)jbl_exception("NULL POINTER");	
	this=jbl_refer_pull(this);
//	jbl_stream* nxt=jbl_refer_pull(this->nxt);
	jbl_string_size_type i=0;
	if((!this->stop)&&this->en)
	{
		this->buf[this->en]=0;
		this->data=__jbl_json_decode(this->data,this->buf,this->buf+this->size,&i);
		if((((struct __jbl_json_decode_yy*)this->data)->cond==(jbl_uint8)-2))
		{
			jbl_log(UC"%v",((struct __jbl_json_decode_yy*)this->extra[0].p)->v);
			this->extra[0].p=__jbl_json_decode_yy_free((struct __jbl_json_decode_yy*)this->extra[0].p);
			this->extra[0].p=this->data=__jbl_json_decode_yy_new();
			this->stop=1;
			return;
		}
		if((((struct __jbl_json_decode_yy*)this->data)->cond==(jbl_uint8)-1)&&(this->extra[0].p==this->data)){this->stop=1;return;}
	}
	jbl_memory_copy(this->buf,this->buf+i,this->en-=i);
}
jbl_stream_operators_new(jbl_json_decode_stream_operaters,__jbl_json_decode_stream_operater,__jbl_json_decode_yy_free,__jbl_json_decode_stream_usf);
inline void * jbl_json_decode_stream_var(jbl_stream* this)
{
	this=jbl_refer_pull(this);
	return jbl_var_copy(((struct __jbl_json_decode_yy*)(this->extra[0].p))->v);
}


#endif
