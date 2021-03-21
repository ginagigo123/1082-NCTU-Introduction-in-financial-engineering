#include<iostream>
#include <cmath>
#include<iomanip>
#include <cstdlib>

#define cost 1
#define N 16
using namespace std;

/*
	author : 蔡怡君 0613413 
	content : theroem about arbitrage
				Final project of financial engineering
*/
int gcd(int x,int y)
{
	if(x!=0&&y!=0)
		return gcd((x>=y)?x%y:x,(x<y)?y%x:y);
	else
		return(x!=0)?x:y;
} 

// ---------------
void theorem2_call (double o[][5],int length) {
	// call 
	for (int i = 0 ; i < length -1 ; i ++ ){
		for (int j = i+1 ; j < length ; j ++) {
			// 後面(X高 X2) - 前面(X低 X1)
			if(o[j][1] - o [i][2] > 2 * cost) {
				cout << "---------------arbitrage with Theorem 2 (call)---------------:" << endl
				<< "Buy 1 call option X=" << o[i][0] << " cost:" << o[i][2]
				<< "& write 1 call option X=" << o[j][0] <<" gain:" << o[j][1] << endl
				<< "( c2>c1 , c: call price; X: strike price)"<<endl
				<< "期末 : if St<=X1, the profit is c2-c1-2(transaction cost) ="<<o[j][1]-o[i][2]-2<<endl
				<< "期末 : if X1<St<X2, the profit is c2-c1+St-X1-2(transaction cost) ="<<o[j][1]-o[i][2]<<"+St-"<<o[i][0]-2<<endl
				<< "期末 : if St>=X2, the profit is c2-c1+X2-X1-2(transaction cost) ="<<o[j][1]-o[i][2]+o[j][0]-o[i][0]-2<<endl<<endl;
			}
		}
	}
}

void theorem2_put ( double o[][5], int length) {
	//Theorem2-put
	for (int i = 0 ; i < length -1 ; i ++ ){
		for (int j = i+1 ; j < length ; j ++) {
			// 後面(X低 X2) - 前面(X高 X1)
			if(o[i][3] - o [j][4] > 2 * cost && o[i][3]!=-1 && o[j][4]!=-1 ) {
				cout << "---------------arbitrage with Theorem 2 (put)---------------:" << endl
				<< "write 1 put option X=" << o[i][0] << " gain:" << o[i][3]
				<< "& buy 1 put option X=" << o[j][0] <<" cost:" << o[j][4] << endl
				<< "( p2>p1 , c: call price; X: strike price)" << endl
				<< "期末 : if St<=X1, the profit is p1-p2+X2-X1-2(transaction cost) =" << o[i][3]-o[j][4]+o[j][0]-o[i][0]-2 << endl
				<< "期末 : if X1<St<X2, the profit is p1-p2+X2-St-2(transaction cost) =" << o[i][3]-o[j][4]+o[j][0] <<" -St-2"<< endl
				<< "期末 : if St>=X2, the profit is p1-p2-2(transaction cost) =" << o[i][3]-o[j][4]-2 << endl << endl;
			}
		}
	}
}

int main()
{
	// strike price 買權(買/賣) 賣權(買/賣) 
	// -1 means 沒有這個東西！ 
	double option[N][5]={{6900, 820, 835, 8.6, 9.1},
						  {7000, 690, 740, 12, 12.5},
					  	  {7100, 630, 645, 17, 18},
						  {7200, 540, 550, 26, 27},
					      {7300, 445, 470, 38.5, 39.5},
					      {7400, 372, 397, 55, 56},
					      {7500, 304, 307, 78, 79},
					      {7600, 231, 235, 109, 110},
				       	  {7700, 173, 174, 148, 149},
					      {7800, 120, 121, 195, 196},
					      {7900, 79 ,  81, 250, 258},
					      {8000, 48.5, 49, 323, 332},
					      {8200, 15.5,16.5, 493, 505},
					      {8400, 4.1,  4.2,-1,-1},
						  {8600,   1,   2, 825, 855},
						  {8800, 0.6, 2.9,-1,-1}
						  };
			
	double Tstock[3]; // 0不用 
	double future[3];
	double r=0.01844, t = 1.0/12;

	
	// bid 買價 => 對於要賣的人 / ask 賣價 => 對於要買的人 
	cout<< "Please input the bid price and ask price of TAIEX : ";
	cin >> Tstock[1] >> Tstock[2];
	cout << "Please input the bid price and ask price of Future : ";
	cin >> future[1] >> future[2];
	
	// Theorem2-call
	theorem2_call(option,N);
	// Theorem2-put
	theorem2_put(option,N);
	
	// Theorem3-call
	for (int i = 0 ; i < N ; i ++) {
		// call worth more than stock 買台指賣call 
		if (option[i][1] - Tstock[2] > 2 * cost)
			cout << "---------------arbitrage with Theorem 3 (call)---------------:" << endl
				<< "Long the taiex and short the call with strike price X=" << option[i][0] << endl
				<< "期初 : gain c-S0-2(transaction cost) =" << option[i][1]-Tstock[2]-2 << endl
				<< "期末 : if the St>X, the profit is X =" << option[i][0] << endl
				<< "期末 :, if the St<X, the profit is St =" << "St" << endl << endl;
	}
	
	//Theorem3-put
	for (int i = 0 ; i < N ; i ++) {
		// put > PV of the strike price
		if (option[i][3] == -1) continue;
		if (option[i][3] - option[i][0] * exp(-r*t) > 1 * cost)
			cout<<"---------------arbitrage with Theorem 3 (put)---------------:"<<endl
				<<"Write the put with the strike price X=" << option[i][0] << " and save the PV of strike price"<<endl
				<<"期初 : gain p-PV(X)-1(transaction cost) =" << option[i][3]-option[i][0]*exp(-r*t)-1 <<endl
				<<"期末 : if the St>X, the profit is X =" << option[i][0] <<endl
				<<"期末 : if the St<X, the profit is St =" << "+St" << endl << endl;
	}
	
	//Theorem4 (call)
	for (int i = 0 ; i < N ; i ++) {
		int value = Tstock[1] - option[i][0]*exp(-r*t), result;
		(value > 0) ? result = value : result = 0;
		// call < intrinsic value => arbitrage 
		if ( result - option[i][2] > 2 * cost) {
			cout <<"---------------arbitrage with Theorem 4 (call)---------------:" << endl
				<< "Buying call costs "<< option[i][2] << " and saving costs PV(" << option[i][0] << ") = option[i][0]*exp(-r*t)" << endl
				<< "Selling the taiex(Spot,S) gets " << Tstock[1] << endl
				<< "期初 : gain S0-c-PV(X)-2 =" << Tstock[1]-option[i][2]-option[i][0]*exp(-r*t)-2<<endl
				<< "期末 : if St>X, the profit is 0" << endl
				<< "期末 : if St<X, the profit is X-St =" << option[i][0] <<"-St"<<endl<<endl;
		}
	}
	
	//Theorem6 (put)
	for (int i = 0 ; i < N ; i ++) {
		// value >= Max(PV(x)-S,0)
		int value = option[i][0] * exp(-r*t) - Tstock[2], result;
		(value > 0) ? result = value : result = 0;
		if (option[i][4] == -1) continue;
		if (result - option[i][4] > 2 * cost) {
			cout << "---------------arbitrage with Theorem 6 (put)---------------:" << endl
				<< "Buying put costs " << option[i][4] << " and borrowing gets PV(" << option[i][0] << ") = option[i][0]*exp(-r*t)" <<endl
				<< "Buying the taiex costs " << Tstock[2] << endl 
				<< "期初 : gain (negative) -p-S0-2+PV(X) =" << -option[i][4] - Tstock[2] - 2 + option[i][0] * exp(-r*t) << endl
				<< "期末 : if St>X, the profit is -X+St =" << -option[i][0] << "+St" << endl
				<< "期末 : if St<X, the profit is X-St+St-X =0" << endl << endl;
		}
	}
	//Theorem8
	// i for X1 , j for X2 , k for X3
	for (int i = 0 ; i < N-2 ; i ++ ) {
		for (int j = i + 1 ; j < N-1 ; j ++ ) {
			for (int k = j + 1 ; k < N ; k ++ ) {
				// omega = (X3-X2)/(X3-X1)
				double omega = ( option[k][0] - option[j][0]) / (option[k][0] - option[i][0]);
				// 因為交易不能買分數的 所以要找整數 
				omega = omega * 1000000;
				int m = 1000000;
				int g = gcd (omega,m); // 取兩者的最小公因數 
				// 去約分 算最小的 
				omega = omega / g;
				m = m / g;
				// write C2 , buy omega C1 , buy (1-omega) C3
				// call
				if ( m * option[j][1] - omega * option[i][2] - (m-omega) * option[k][2] > 3 * cost ) {
					cout << "---------------arbitrage with Theorem 8 (call)---------------:" << endl
						<< "Selling " << m << " units of strike price X=" << option[j][0] << " get " << m*option[j][1] << endl
						<< "Buying " << omega << " units of strike price X=" << option[i][0] << " cost " << omega*option[i][2] << endl 
						<< "buying " << (m-omega)<<" units of strike price X=" << option[k][2] << " cost " << (m-omega)*option[k][2] << endl 
						<< "期初 : gain m*c2-omega*c1-(m-omega)c3-3 =" << m*option[j][0] - omega*option[i][2] -(m-omega)*option[k][2]-3 << endl
						<< " ordering：X3 > X2 > X1 :" << endl 
						<< "期末 : if St<X1, the profit is 0"<<endl
						<< "期末 : if X1<St<X2, the profit is w(St-X1)"<< endl
						<< "期末 : if X2<St<X3, the profit is w(St-X1)-m*(X2-St)"<<endl
						<< "期末 : if St>X3, the profit is 0"<<endl<<endl;
				}
				// put
				if(option[j][3] == -1 || option[i][4] == -1 || option[k][4] == -1) continue;
				if( m * option[j][3] - omega * option[i][4] - (m-omega) * option[k][4] > 3 * cost) {
					cout<< "---------------arbitrage with Theorem 8 (put)---------------:" << endl
						<< "Selling " << m << " units of strike price X=" << option[j][0] << " get " << m*option[j][3] << endl 
						<< "Buying " << omega << " units of strike price X=" << option[i][0] << " cost " << omega*option[i][4] << endl 
						<< "buying " << (m-omega) << " units of strike price X=" << option[k][0] << " cost "<< (m-omega)*option[k][2] << endl 
						<< "期初 : gain m*p2-omega*p1-(m-omega)p3-3 =" << m * option[j][3] - omega * option[i][4] - (m-omega) * option[k][4] - 3 <<endl
						<< "期末 : if St<X1, the profit is 0"<< endl
						<< "期末 : if X1<St<X2, the profit is w(St-X1)" << endl
						<< "期末 : if X2<St<X3, the profit is (m-omega)(X3-St)" << endl
						<< "期末 : if St>X3, the profit is 0" << endl << endl;
				}
			}
		}
	}
	
	//Theorem9-2
	for (int i = 0 ; i < N ; i ++) {
		if(option[i][4] == -1) continue;
		if ( (option[i][4]-option[i][1]) - (future[2]-option[i][0]) * exp(-r*t) > 3 * cost){
			cout << "---------------arbitrage with Theorem 9-2-1---------------:" << endl
				<< "Selling call gets " << option[i][1] << endl
				<< "Buying put costs " << option[i][4] << endl
				<< "Buying futures costs " << future[2] << endl
				<< "The profit is " << (option[i][4]-option[i][1])-(future[2]-option[i][0])*exp(-r*t)-3 << endl << endl;
		}
	}
	
	for ( int i = 0 ; i < N ; i ++) {
		if(option[i][3] == -1 )	continue;
		if ( (future[1]-option[i][0]) * exp(-r*t) - (option[i][3]-option[i][2]) > 3 *cost ){
			cout << "---------------arbitrage with Theorem 9-2-2---------------:" << endl
				<< "Buying call costs" << option[i][2] << endl
				<< "Selling put gets" << option[i][3] << endl
				<< "Selling futures gets" << future[1] << endl
				<< "The profit is " << (future[1]-option[i][0]) * exp(-r*t) - (option[i][3]-option[i][2]) - 3 << endl << endl;
		}	
	}
	return 0;
} 
