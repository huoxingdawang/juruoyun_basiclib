#include "main.h"
using namespace std;
int main()
{
	jry_bl_string s1,s2,s3;
	int a;
	for(;;)
	{
		cin>>s1;
//		s2=jry_bl_md5(s1).get_string();cout<<s2<<endl;
		s3+=jry_bl_md5(s1).get_string(s2);cout<<s2<<endl<<s3<<endl;
		s2.free();s3.free();
	}	
    return 0;
}