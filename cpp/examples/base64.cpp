#include "main.h"
using namespace std;
int main()
{
	jry_bl_string s1,s2;
	int a;
	for(;;)
	{
		cout<<"input 0 or 1,0 means encode,1 means decode;"<<endl;
		cin>>a;getchar();
		if(a==0)
			cout<<"encode"<<endl;
		else
			cout<<"decode"<<endl;
		cin>>s1;
		if(a==0)
			jry_bl_base64_encode(s2,s1);
		else
			jry_bl_base64_decode(s2,s1);
		cout<<s2<<endl<<endl<<endl;
		s1.clear();s2.clear();
	}	
    return 0;
}