#include <iostream>
#include <string>
using namespace std;

struct Sach {
	string ten;
	int sotrang;
	double gia;
	
};

int timmax(Sach x[]){
	int max=0;
	for (int i=1;i<3;i++){
		if (x[max].gia<x[i].gia) max=i;
	}
	
	return max;
}


int main(){
	Sach ds[3];
	
	for (int i=0; i<3;i++){
		if (i!=0) cout<<endl;
		cout<< "Nhap ten sach "<<i+1<<" : ";
		getline(cin,ds[i].ten);
		
		cout<<"Nhap so trang cua sach "<<i+1<<" : ";
		cin>>ds[i].sotrang;
		
		cout<<"Nhap gia tien cua sach "<<i+1<<" : ";
		cin>>ds[i].gia;
		cin.ignore();
	}
	int max=timmax(ds);
	cout<<"Sach thu "<<max+1<<" co gia tien cao nhat";
	return 0;
	
}