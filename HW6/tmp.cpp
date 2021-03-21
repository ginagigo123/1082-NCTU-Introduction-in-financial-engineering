#include<iostream>
#include<stdlib.h>
#include<math.h>

using namespace std;

double price(int C,int N,double YS,double *y){
 double p = 0;
 for(int i=0;i<N;i++)
  p+= (C*1.0)/(pow(1+YS+y[N-1],i+1));
 p+= 100.0/(pow(1+YS+y[N-1],N));
 return p;
}

double priceZ(int C,int N,double SS,double *z){
 double p = 0;
 for(int i=0;i<N;i++)
  p+= (C*1.0)/(pow(1+SS+z[i],i+1));
 p+= 100.0/(pow(1+SS+z[N-1],N));
 return p;
}

double staticSpread(int C,int N,double *z,double bondPrice){
 double up=1,low=0;
 
 //å‹˜æ ¹ 
 while((up-low)>0.00001){
  double mid = (up+low)/2;
  double p = priceZ(C,N,mid,z)-bondPrice;
  double upP = priceZ(C,N,up,z)-bondPrice;
  double lowP = priceZ(C,N,low,z)-bondPrice;
  printf("%f\t%f\t%f\n",p,upP,lowP);
  if(p==0.0) {cout<<"mid";return mid;}
  if(upP==0.0) {cout<<"up";return up;}
  if(lowP==0.0) {cout<<"low"; return low;}
  if(p*upP<0.0)
   low = mid;
  else if(p*lowP<0.0)
   up = mid;
   cout<<"up:"<<up<<" low:"<<low<<" re"<<abs(up-low)<<endl;
 }
 return low;
}

int main()
{
 int N,C;
 double YS,*y,*z;
 
 //Input
 cout<<"¿é¤J¶Å®§¯: ";
 cin>>C;
 cout<<"¿é¤J…¥yield spread(in %): ";
 cin>>YS;
 YS/=100; 
 cout<<"¿é¤J´Á¼Æ : ";
 cin>>N;
 cout<<"¿é¤J "<<N<<"´Á yield rate(in %): ";
 y = new double[N];
 z = new double[N];
 for(int i=0;i<N;i++){
  cin>>y[i];
  y[i]/=100;
 }
 
 //Compute bond price
 double P = price(C,N,YS,y);
 printf("Bond price is %f\n",P);
 
 //compute zero-rate
 z[0] = y[0];
 cout<<"Z["<<0<<"] = "<<z[0]<<endl;
 for(int i=1;i<N;i++){
  double cSum = 0;
  double Ptmp = price(C,i+1,0,y);
  for(int j=0;j<i;j++)
   cSum += (C*1.0)/(pow(1+z[j],j+1));
  double tmp = (C+100.0)/(Ptmp-cSum);
  z[i] = pow(tmp,1.0/(i+1))-1;
  cout<<"Z["<<i<<"] = "<<z[i]<<endl;
 }
 
 //Find static spread
 double SS = staticSpread(C,N,z,P);
 cout<<"Static Spread is "<<SS<<endl;
 
 return 0;
}
