/* Copyright (c) [2020] juruoyun developer team
   Juruoyun basic lib is licensed under the Mulan PSL v1.
   You can use this software according to the terms and conditions of the Mulan PSL v1.
   You may obtain a copy of Mulan PSL v1 at:
      http://license.coscl.org.cn/MulanPSL
   THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR
   PURPOSE.
   See the Mulan PSL v1 for more details.*/
#include "jbl_base64.h"
#if JBL_BASE64_ENABLE==1
/*******************************************************************************************/
/*                            依赖jbl_ying jbl_exception                                   */
/*******************************************************************************************/
#include "jbl_exception.h"
#include "jbl_ying.h"
/*******************************************************************************************/
/*                            联动jbl_stream jbl_string                                    */
/*******************************************************************************************/
#include "jbl_string.h"
#include "jbl_stream.h"

/*******************************************************************************************/
/*                            全局变量定义                                                */
/*******************************************************************************************/
static const char ent[]= "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"; 
static const char det[]={-2,-2,-2,-2,-2,-2,-2,-2,-2,-1,-1,-2,-2,-1,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-1,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,62,-2,-2,-2,63,52,53,54,55,56,57,58,59,60,61,-2,-2,-2,-2,-2,-2,-2,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,-2,-2,-2,-2,-2,-2,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2};
#if JBL_STRING_ENABLE==1
/*******************************************************************************************/
/*                            以下函数实现字符串的base64编解码操作                      */
/*******************************************************************************************/
jbl_string * jbl_base64_encode(jbl_string *this,jbl_string *result)
{
	if(!this)jbl_exception("NULL POINTER");	
	jbl_string *thi=jbl_refer_pull_rdlock(this);		
	jbl_string_size_type i=0,len=jbl_string_get_length_force(thi);
	jbl_string *res;result=jbl_string_extend_to(result,len*4/3+4,1,&res);jbl_string_hash_clear(res);
	while(i+3<=len)
		jbl_string_add_char_force(res,ent[  jbl_string_get_force(thi,i  )      >>2]),
        jbl_string_add_char_force(res,ent[((jbl_string_get_force(thi,i  )&0x03)<<4)+(jbl_string_get_force(thi,i+1)>>4)]),
        jbl_string_add_char_force(res,ent[((jbl_string_get_force(thi,i+1)&0x0f)<<2)+(jbl_string_get_force(thi,i+2)>>6)]),
        jbl_string_add_char_force(res,ent[  jbl_string_get_force(thi,i+2)&0x3f]),
        i+=3;
	if(i<len)
	{
		jbl_string_add_char_force(res,ent[jbl_string_get_force(thi,i)>>2]);
		if((len-i)%3==1)
			jbl_string_add_char_force(res,ent[(jbl_string_get_force(thi,i)&0x03)<<4]),
            jbl_string_add_char_force(res,'='),
            jbl_string_add_char_force(res,'=');
		else if((len-i)%3==2)
			jbl_string_add_char_force(res,ent[((jbl_string_get_force(thi,i)&0x03)<<4)+(jbl_string_get_force(thi,i+1)>>4)]),
            jbl_string_add_char_force(res,ent[ (jbl_string_get_force(thi,i+1)&0x0f)<<2]),
            jbl_string_add_char_force(res,'=');
	}
    jbl_refer_pull_unwrlock(result);
    jbl_refer_pull_unrdlock(this);
	return result;
}
jbl_string * jbl_base64_decode(jbl_string *this,jbl_string *result)
{
	if(!this)jbl_exception("NULL POINTER");	
	jbl_string *thi=jbl_refer_pull_rdlock(this);		
	jbl_string_size_type i=0,len=jbl_string_get_length_force(thi);
	jbl_uint8 bin=0,ch;
	jbl_string *res;result=jbl_string_extend_to(result,len*3/4+3,1,&res);jbl_string_hash_clear(res);
	while(i<len)
	{
		ch=jbl_string_get_force(thi,i);
		if(ch=='=')
		{
			if(jbl_string_get_force(thi,i+1)!='='&&(i%4)==1)
            {
				jbl_string_clear(res);
                break;
            }
		}
		else if(det[ch]>=0)
        {
            ch=(jbl_uint8)det[ch];
            switch(i&3)
            {
                case 0:bin =(jbl_uint8)(ch<<2);break;
                case 1:bin|=ch>>4,jbl_string_add_char_force(res,bin),bin=(jbl_uint8)((ch&0x0f)<<4);break;
                case 2:bin|=ch>>2,jbl_string_add_char_force(res,bin),bin=(jbl_uint8)((ch&0x03)<<6);break;
                case 3:bin|=ch,jbl_string_add_char_force(res,bin);break;
            }
        }
		++i;
	}
    jbl_refer_pull_unwrlock(result);
    jbl_refer_pull_unrdlock(this);
	return result;
}
#endif
#if JBL_STREAM_ENABLE==1
/*******************************************************************************************/
/*                            以下函数实现stream的编解码操作                       */
/*******************************************************************************************/
static void __b64_seo(jbl_stream* thi,jbl_uint8 force)
{
	if(!thi)jbl_exception("NULL POINTER");	
	jbl_stream* nxt=jbl_refer_pull_wrlock(thi->nxt);
	if(nxt&&(!thi->stop)&&thi->buf)
	{
        jbl_stream_get_buf(thi,1);
        while(thi->buf->sta+3<=thi->buf->len)
        {
            jbl_stream_push_down(nxt,4);
            jbl_stream_move_unhandle_buf(nxt->buf);
            if(1==(thi->stop=nxt->stop))break;
            jbl_stream_push_char_force(nxt,ent[thi->buf->s[thi->buf->sta]>>2]);
            jbl_stream_push_char_force(nxt,ent[((thi->buf->s[thi->buf->sta]&0x03)<<4)+(thi->buf->s[thi->buf->sta+1]>>4)]);
            jbl_stream_push_char_force(nxt,ent[((thi->buf->s[thi->buf->sta+1]&0x0f)<<2)+(thi->buf->s[thi->buf->sta+2]>>6)]);
            jbl_stream_push_char_force(nxt,ent[thi->buf->s[thi->buf->sta+2]&0x3f]);
            thi->buf->sta+=3; 
        }
		if(force)
		{
            if(thi->buf->sta<thi->buf->len)
			{
                jbl_stream_push_down(nxt,4);
                jbl_stream_move_unhandle_buf(nxt->buf);
                if(1==(thi->stop=nxt->stop))goto exit;
                jbl_stream_push_char_force(nxt,ent[thi->buf->s[thi->buf->sta]>>2]);
                if((thi->buf->len-thi->buf->sta)%3==1)
                {
                    jbl_stream_push_char_force(nxt,ent[(thi->buf->s[thi->buf->sta]&0x03)<<4]);
                    jbl_stream_push_char_force(nxt,'=');
                    jbl_stream_push_char_force(nxt,'=');
                    thi->buf->sta+=1;
                }
                else if((thi->buf->len-thi->buf->sta)%3==2)
                {
                    jbl_stream_push_char_force(nxt,ent[((thi->buf->s[thi->buf->sta]&0x03)<<4)+(thi->buf->s[thi->buf->sta+1]>>4)]);
                    jbl_stream_push_char_force(nxt,ent[(thi->buf->s[thi->buf->sta+1]&0x0f)<<2]);                    
                    jbl_stream_push_char_force(nxt,'=');
                    thi->buf->sta+=2;
                }
            }
			nxt->op->op(nxt,force);
		}
	}
exit:;
    jbl_refer_pull_unwrlock(thi->nxt);
}
static void __b64_sdo(jbl_stream* thi,jbl_uint8 force)
{
	if(!thi)jbl_exception("NULL POINTER");	
	jbl_stream* nxt=jbl_refer_pull_wrlock(thi->nxt);
	if(nxt&&(!thi->stop)&&thi->buf)
	{
        jbl_stream_get_buf(thi,1);
        jbl_uint8 ch,bin=0;
		while(thi->buf->sta<thi->buf->len)
		{
            jbl_stream_push_down(nxt,3);
            jbl_stream_move_unhandle_buf(nxt->buf);
            if(1==(thi->stop=nxt->stop))break;
            ch=thi->buf->s[thi->buf->sta];
			if(ch=='=')
			{
				if(thi->buf->s[thi->buf->sta+1]!='='&&(thi->buf->sta%4)==1)
				{
					if(thi->buf->sta<thi->buf->len&&force)
                        jbl_exception("STREAM ERROR");
					goto exit;
				}
				++thi->buf->sta;
				continue;
			}
			if(det[ch]>=0)
            {
                ch=(jbl_uint8)det[ch];
                switch(thi->buf->sta&3)
                {
                    case 0:bin =(jbl_uint8)(ch<<2);break;
                    case 1:bin|=ch>>4;jbl_stream_push_char_force(nxt,bin),bin=(jbl_uint8)((ch&0x0f)<<4);break;
                    case 2:bin|=ch>>2;jbl_stream_push_char_force(nxt,bin),bin=(jbl_uint8)((ch&0x03)<<6);break;
                    case 3:bin|=ch   ;jbl_stream_push_char_force(nxt,bin);break;
                }
            }
			++thi->buf->sta;
		}
        nxt->op->op(nxt,force);
	}
exit:;
    jbl_refer_pull_unwrlock(thi->nxt);
}
jbl_stream_operators_new(jbl_stream_base64_encode_operators,__b64_seo,NULL,NULL,12,0);
jbl_stream_operators_new(jbl_stream_base64_decode_operators,__b64_sdo,NULL,NULL,16,0);
#endif
#endif
