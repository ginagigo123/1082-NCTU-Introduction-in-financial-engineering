#include<iostream>
#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#include<algorithm>

using namespace std;

int main()
{
	int n;
	float c, r, value = 0, Discount, duration = 0;
	cout<<"請輸入期數:";
	cin>>n;
	cout<<"請輸入債息(%):";
	cin>>c; 
	cout<<"請輸入利率:";
	cin>>r;
	for(int i = 1 ; i <= n ; i ++){
		Discount = pow(1+r,-i);
		duration += i*Discount*c*100;
		value += Discount*c*100;
		if( i == n){
			duration += n*100*Discount;
			value += 100*Discount;
		}
	}
	duration = duration / value;
	cout<<"\nDuration:"<<duration;
	
	return 0;
}

