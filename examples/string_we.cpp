#include "main.h"
using namespace std;
jry_bl_string a(jry_bl_string a){jry_bl_string b;b=a;return b;}
int main()
{
	jry_bl_string s1="juruoyun";
	jry_bl_string s2;
	for(int i=0;i<12;i++,(s1+=s1));
	for(int i=0;i<100000;i++)
	{
//爆内存
		s2=a(s1);
		s2.free();
//不爆
//		s2<<a(s1);
//		s2.free();	
	}
	return 0;
}