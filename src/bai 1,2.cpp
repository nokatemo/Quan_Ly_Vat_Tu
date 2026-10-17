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
	 
	 int max = 0;
	 for (int i = 0; i < 3 ; i++) {
	 	if (ds[i].gia > ds[max].gia) 
	 		max = i;
	  }
	   cout << " sach co gia cao nhat la :" << ds[max].ten << " | " << "so trang:" << ds[max].sotrang<<" | " << "gia:" << ds[max].gia << endl;
	   
	  return 0;	    
 }

