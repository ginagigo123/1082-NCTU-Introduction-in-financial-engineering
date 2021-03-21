#include<iostream>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<iomanip>
#include<algorithm>

using namespace std;

float f(float c[],int n,float r)
{
	float result = 0.0;
	// result = 9702-19700/(1+IRR) +10000/(1+IRR)^2
	for(int i = 0 ;i <= n ; i ++){
		float Discount = 1.0;
		for(int j = 0 ; j < i ; j ++)
			Discount = Discount / (1.0+r);
		result = result + c[i] * Discount;
	}
	return result;
} 

float f_df(float c[],int n,float r)
{
	float result = 0.0;
	// result = -1*(-19700)/(1+IRR)^2 -2*10000/(1+IRR)^3
	for(int i = 0 ; i <= n ; i ++){
		float Discount = 1.0;
		for(int j = 0 ; j < i+1 ; j++)  // i+1 important 
			Discount = Discount / (1.0+r);
		result = result - i * c[i] * Discount;
	}
	return result;
}
int main()
{
	float c[]={9702.0,-19700.0,10000.0}, x , value=1 , dvalue;
	int n;
	cout<<"plz input n(有幾期):";
	// need to input 2
	cin >> n;	

	// right
	cout<<"--- use cost of capital rate:1.0去趨近 ---\n";
	float ans = 1.0;
	while(value >= 0.00001) 
	{
		value = f(c,n,ans);
		dvalue = f_df(c,n,ans);
		// x = x - f/f'
		ans = ans - value/dvalue;
	}
	cout<<"Yield rate ="<<ans<<endl;
	
	// left
	cout<<"--- if cost of capital rate:0.0去趨近 ---\n";
	ans = 0;
	value = 1;
	while(value >= 0.00001)  
	{
		value = f(c,n,ans);
		dvalue = f_df(c,n,ans);
		ans = ans - value/dvalue;
	}
	cout<<"Yield rate ="<<ans;
	return 0;
}

