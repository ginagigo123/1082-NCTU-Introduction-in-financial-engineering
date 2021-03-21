#include<iostream>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<iomanip>
#include<algorithm>

using namespace std;

int main()
{
	float c[]={9702,-19700.0,10000}, x, Discount;
	float Low = 0, High = 0.5, Middle;
	int n;
	
	// n need to be 3
	cout<<"plz input  x(期初投入) , n(有幾期):";
	cin >> x >> n;
	
	cout<<" ----- 左邊逼近法(Low = 0 High =0.5) -----"<<endl;
	while(High - Low >= 0.0001)
	{
		Middle = (Low+High)/2;
		float value = 0;
		// value = 9702-19700/(1+IRR) +10000/(1+IRR)^2
		for(int i = 0 ; i < n ; i ++){
			Discount = 1;
			for(int j = 0 ; j < i ; j ++)
				Discount *= (1.0+Middle);
			value = value + c[i] / Discount;
		}
		value = value - x;
		if(value > 0)
			High = Middle;   // notice 如果從右邊逼近因為這邊是遞增 (隨著X的增加) 所以 High 要=Middle 
		else
			Low = Middle;
	}
	cout<<"Yield rate ="<<High<<"\n";
	
	
	Low = 0;
	cout<<" ----- 右邊逼近法(Low = 0 High = 0.0204468 第一解) -----"<<endl;
	while(High - Low >= 0.0001)
	{
		Middle = (Low+High)/2;
		float value = 0;
		// value = 9702-19700/(1+IRR) +10000/(1+IRR)^2
		for(int i = 0 ; i < n ; i ++){
			Discount = 1;
			for(int j = 0 ; j < i ; j ++)
				Discount *= (1.0+Middle);
			value = value + c[i] / Discount;
		}
		value = value - x;
		if(value > 0)
			Low = Middle;   // notice 如果從左邊逼近因為這邊是遞減 (隨著X增加) 所以 Low 要=Middle 
		else
			High = Middle;
	}
	cout<<"Yield rate ="<<High<<"\n";
	
	return 0;
}

