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
		cin>>s1;
		if(a==0)
		{
			cout<<"encode"<<endl;
			s1.to_json(s2);
		}
		else
		{
			cout<<"decode"<<endl;
			s2.from_json(s1);
		}
		cout<<s2<<endl<<endl<<endl;
	}
	return 0;
}