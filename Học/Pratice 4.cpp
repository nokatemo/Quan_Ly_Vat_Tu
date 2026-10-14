#include <iostream>
#include <string>
using namespace std;

struct Sach {
	string ten;
	int sotrang;
	double gia;
	
};

void Selection(Sach *x[]){
	for (int i=0; i<2; i++){
		int min=i;
		for (int j=i+1;j<3;j++){
			if (x[j]->gia<x[min]->gia) min=j;
		}
		swap(x[i],x[min]);
	}
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
	
	Sach *pDs[3];
	for (int i=0; i<3;i++){
		pDs[i]=&ds[i];
	}
	
	

	return 0;
	
}