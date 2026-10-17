#include<iostream>
#include<string>

using namespace std;

void thongtin(string*ten , double*diem, int n) {
	for (int i = 0 ; i < n; i++) {
	   cout << "nhap thong tin \n ";
	   cout << " hs thu:" << i + 1 << "\n";
	    cin.ignore();
	   getline (cin , ten[i]);
	   cin >> diem[i] ;
   } 
}


double diemtb (double*diem, int n) {
	double sum= 0;
	for ( int i = 0; i < n ; i++) {
       sum += diem[i] ;
	} return sum / n;
} 


int vtrimax (double*diem, int n) {
	int max = 0;
	for ( int i = 0; i < n; i ++){
		if (diem[i] > diem[max]) {
			 max = i;
		}		
	} return max;
} 

int main (){
	
	int n;
	cin >> n;
	string*tenhs = new string[n];
	double* diemhs = new double[n];
	
	thongtin (tenhs,diemhs, n);
	double tbdiem = diemtb (diemhs, n); 
	int vtmax = vtrimax ( diemhs, n) ;
	
	cout << "\n === thong tin ===\n";
	for (int i =0 ; i < n; i ++){
      cout << "hoc sinh thu :" << i + 1 <<"\n" ;
      cout << " ten: " << tenhs[i] <<"\n";
      cout << " diem: " << diemhs[i] << "\n";	
     }
     
     cout << " diem tb cua ca lop :" << tbdiem << "\n";
     cout << " hoc sinh co diem cao nhat la : " << tenhs[vtmax] << " | " << "co diem la: " << diemhs[vtmax];
     
     delete [] tenhs;
     delete [] diemhs;
     
      return 0;   
}

