#include<iostream>
#include<string>
using namespace std;

struct sach {
	string ten;
	int sotrang;
	double gia;
};

int main (){
  sach ds[3];
	 for (int i = 0; i < 3; i ++){
	 	getline (cin, ds[i].ten);
	 	cin >> ds[i].sotrang;
	 	cin >> ds[i].gia;
	 	cin.ignore();
	 }
  sach* pDs[3];
     for (int i = 0; i < 3; i ++){
     	pDs[i] = &ds[i];
	 }
	 
	 
     for (int i = 0; i < 2 ; i ++){
     	for (int j = i + 1; j < 3 ; j ++ ){
     		if ( pDs[i]->gia > pDs[j]->gia){
     	    sach* temp = pDs[i];
     	    pDs[i]= pDs[j] ;
     	    pDs[j] = temp ;
        	}
		 }
	 }
	 
	cout << " /n ---ds da sx--- /n " ;
	 for (int i = 0 ; i < 3; i++){
	    cout << " ten sach : " << pDs[i]->ten << "\n";
	    cout << " so trang : " << pDs[i]->sotrang << "\n";
	    cout << " gia :" << pDs[i]->gia <<"\n";
	 }
     
     	cout << " /n ---ds goc--- /n " ;
	 for (int i = 0 ; i < 3; i++){
	    cout << " ten sach : "<< ds[i].ten << "\n";
	    cout << " so trang : "<< ds[i].sotrang << "\n";
	    cout << " gia :" << ds[i].gia <<"\n";
	}
     return 0;
 }

