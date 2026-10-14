#include <bits/stdc++.h>
using namespace std;

struct Sach {
	string ten;
	int Sotrang;
	double gia;
};

int main()
{
	Sach sach1;
	cout << "Nhap ten sach: ";
	getline(cin, sach1.ten);
	cout << "\n";
	
	cout << "Nhap so trang sach: ";
	cin >> sach1.Sotrang;
	cout << "\n";
	
	cout << "Nhap gia sach: ";
	cin>> sach1.gia;
	cout << "\n";
	
	cout << "Don gia trung binh tren moi trang la: " << sach1.gia/sach1.Sotrang;
	
	return 0;
}
