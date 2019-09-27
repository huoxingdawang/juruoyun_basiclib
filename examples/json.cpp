#include "main.h"
using namespace std;
int main()
{
	jry_bl_string s1,s2;
	int a;
	cin>>a;getchar();
	if(a==0)
	{
		cout<<"encode"<<endl;
		for(;;)
		{
			cin>>s1;
			s2<<s1.to_json();
			cout<<s2<<endl;
		}
	}
	else
	{
		cout<<"decode"<<endl;
		for(;;)
		{
			cin>>s1;
			s2.from_json(s1);
			cout<<s2<<endl;
		}
	}	
	return 0;
}