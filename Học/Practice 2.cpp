#include <iostream>
#include <string>
using namespace std;

struct Sach {
	string ten;
	int sotrang;
	double gia;
	
};

double thanhtien(const int x,double y){
	double tb;
	tb=y/x;
	return tb;
}

int main(){
	Sach sach1;
	cout<<"Nhap ten sach: ";
	getline(cin,sach1.ten);
	cout<<"Nhap so trang: ";
	cin>>sach1.sotrang;
	cout<<"Nhap gia tien: ";
	cin>>sach1.gia;
	double tb=thanhtien(sach1.sotrang,sach1.gia);
	cout<<"Gia trung binh moi trang: "<< tb;
	
	return 0;
	
}