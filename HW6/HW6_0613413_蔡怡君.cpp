#include<iostream>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<algorithm>

using namespace std;

/*
	author : 蔡怡君 Gina
	ID : 0613413
	content : compute  zero rate,static spread By
			given yield spread / yield rate / Coupon.
*/

float Z[100],R[100],C;

// using for Newton
float f(int n,float r,float Bond)
{
	float result = 0.0;
	for(int i = 1 ;i <= n ; i ++){
		float Discount = pow(1.0 + Z[i] + r ,-i);
		result = result + C * Discount;
		if(i == n)
			result += 100*Discount;
	}
	result = result - Bond;
	return result;
} 

// using for Newton 
float f_df(int n,float r)
{
	float result = 0.0;
	for(int i = 1 ; i <= n ; i ++){
		float Discount = pow(1.0+ Z[i] + r ,-i-1);
		result = result - i * C * Discount;
		if(i == n)
			result += (-n) * 100 * Discount;
	}
	return result;
}

// using for Newton to compute the "static spread" 
float find_static(int n,float Bond)
{
	// right
	float value = 1.0,dvalue;
	cout<<"--- use cost of capital rate:0.0去趨近 ---\n";
	float ans = 0.0;
	while(value >= 0.00001)  
	{
		value = f(n,ans,Bond);
		dvalue = f_df(n,ans);
		// x = x - f/f'
		ans = ans - value/dvalue;
		//cout<<"ans="<<ans<<endl;
	}
	cout<<"static spread ="<<ans<<endl;
	return ans;
}

// using for yield rate
// calculate the bond price
float Bond_Price(int n,float R[],float S)
{
	float sum = 0;
	for(int i = 1 ; i <= n ; i ++){
		// the main differnet : yield => R[n]
		float Discount = pow(1+R[n]+S,-i);
		sum += C*Discount;
		if(i == n)
			sum += 100*Discount;
	} 
	return sum;
}

// using for Zero rate
float Bond_Price(int n,float s)
{
	float sum = 0;
	for(int i = 1 ; i <= n ; i ++){
		// the main differnet : zero rate => Z[i]
		float Discount = pow(1+Z[i]+s,-i);
		sum += C * Discount;
		if(i == n)
			sum += 100*Discount;
	}
	return sum;
}

// Given yield to find zero rate
void fill_zero(int n,float R[])
{
	Z[1] = R[1];
	float *price = new float [n];
	for(int i = 2 ; i <= n ; i++){
		float result, deduce = 0;
		price[i] = Bond_Price(i,R,0);
		for(int j = 1 ; j < i ; j ++)
			deduce += C * pow(1+Z[j],-j);
		// means (c+F) / ( Pi - c/(1+S(1)) - c/(1+S(2))^2 .... so on)
		result = (C+100.0) / (price[i]-deduce);
		Z[i] = pow(result,1.0/i) - 1;
	}
}

int main()
{
	int n;
	float S,s,Bond; // s using for static spread
	cout<<"Plz input 期數(n)  yield spread(S) 票息(C):";
	cin >> n >>S >>C;
	for(int i = 1 ; i <= n ; i ++){
		cout<<i<<".每期報酬率(R) "<<endl;
		cin>> R[i] ;
	}
	
	// find zero rate & print it out
	fill_zero(n,R);
	cout<<"zero rate :";
	for(int i = 1 ; i <= n ; i ++)
		cout<<Z[i]<<" ";
	
	// compute the bond price 
	Bond = Bond_Price(n,R,S);
	cout<<"\n(Yield Spread)Bond Price:"<<Bond<<endl;
	
	// find static spread and compute the result
	s = find_static(n,Bond);
	cout<<"(static Spread)Bond Price:"<<Bond_Price(n,s)<<endl;
	
	
	return 0;
}

/* using for debug
//cout<<"deduce:"<<deduce<<endl;
//cout<<"Price:"<<price[i]<<endl;
//cout<<"result:"<<result<<endl;
//cout<<"pow:"<<pow(result,1.0/i)<<endl;
*/
