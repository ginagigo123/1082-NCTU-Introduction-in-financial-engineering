#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

/*
	content: dirty price & clean price
			 under actual/actual & 30/360
	author : 蔡怡君 0613413
*/

using namespace std;

//  m means Maturity s mean Settlement 
struct day
{
	int y,m,d;
}M,S;

// check 是否為閏年 
int is_leaf(int year)
{
	// leaf return 1 
	return (year%4 == 0 && year%100 != 0) || (year%400 == 0);
}

// return 月份的日子 
int month_day(int year,int month)
{
	if(month == 2)
		return 28 + is_leaf(year);
	else if( (month < 8 && month%2 == 1) || (month > 7 && month %2 == 0 ) )
		return 31;
	else
		return 30;
}

// day for Actual/Actual d1 for Maturity
float actual_day(struct day d1,struct day d2)
{
	int sum = d1.d;
	int year = d1.y, month = d1.m, day= d1.d;
	//cout<<year<<"/"<<month<<"/"<<day<<":"<<sum<<endl;
	
	// i controls year , j controls month 時間用倒敘的算回去 
	for(int i = year ; i >= d2.y ; i--){
		for(int j = month-1 ; j > 0 ; j--){
			// 如果同年同月要檢查 直接剪掉 
			if( i == d2.y && j == d2.m)
			{
				sum += month_day(i,j) - d2.d;
				//cout<<i<<"."<<j<<":"<<month_day(i,j)-d2.d<<endl;
				break;
			}
			sum += month_day(i,j);
			//cout<<i<<"."<<j<<":"<<month_day(i,j)<<endl; //using for debug
		}
		month = 13; // 因為j是從12開始 
	}
	return sum;
}

// day interest for 30/360
float thirty_day(struct day d1,struct day d2)
{
	int sum = 0;
	if(d1.d >= d2.d)
		sum += d1.d-d2.d;
	else{
		d1.m-=1;
		d1.d+=30;
		sum += d1.d-d2.d;
	}
	if(d1.m >= d2.m)
		sum += (d1.m-d2.m)*30;
	else{
		d1.y-=1;
		d1.m+=12;
		sum+= (d1.m-d2.m)*30;
	}
	sum += (d1.y-d2.y)*360;
	return sum;
}

float cal_price(float w,float n,float b_yield,float rate)
{
	int cash = 100*rate/2;
	float Discount = 1,Value=0;
	for(int i = 0 ; i <= n ; i++){
		Discount = pow(1+b_yield,-w-i);
		//for(float j = 0; j < i/2.0 ; j +=0.5)
			//Discount /= (1+b_yield);
		Value += cash*Discount;
	}
	Value += (100)*Discount;
	//cout<<n+1<<". Value: "<<Value<<endl; //using for debug
	return Value;
}

int main()
{
	// ---- input  // rate means Coupon rate
	float b_yield,rate;
	cout<<"Plz input Bond Maturity date (year/month/day):";
	cin>>M.y>>M.m>>M.d;
	cout<<"plz input settlement date (year/month/day):";
	cin>>S.y>>S.m>>S.d;
	cout<<"plz input the bond yield/coupon rate:";
	cin>>b_yield>>rate;
	
	// ---- 30/360
	cout<<"\n--- Using 30/360 --- \n";
	int total = thirty_day(M,S);
	cout<<"total day :" <<total<<endl;
	
	float w = (total%180)/180.0, n = total/180;
	cout<<"w :"<<w<<endl;
	float ac_interest = 100*rate/2*(1-w);
	float dirty = cal_price(w,n,b_yield/2,rate);
	
	cout<<"dirty price / clean price:\n";
	cout<<"$"<<dirty<<" / $"<<dirty-ac_interest<<"\n";
	
	// ----- Actual/Actual
	cout<<"\n--- Using Actual/Actual --- \n";
	total = actual_day(M,S);
	cout<<"total day :"<<total<<endl;
	
	w = (total%182)/184.0,n = total/182.0;
	cout<<"w :"<<w<<endl;
	ac_interest = 100*rate/2*(1-w);
	dirty = cal_price(w,n,b_yield/2,rate);
	
	cout<<"dirty price / clean price:\n";
	cout<<"$"<<dirty<<" / $"<<dirty-ac_interest<<"\n";
		
	// using for debug
	//cout<<"next payment/total day:"<<total%180<<"/"<<total<<endl;

	return 0;
}

