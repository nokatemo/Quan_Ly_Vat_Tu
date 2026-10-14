#include <bits/stdc++.h>
using namespace std;

struct Sach {
	string ten;
	int Sotrang;
	double gia;
};

int main()
{
	Sach ds[3];
	for (int i = 0; i < 3; i++) 
	{
		cout << "Nhap ten sach " << i + 1 << ":";
		getline(cin, ds[i].ten);
		cout << "\n";
		
		cout << "Nhap so trang sach: ";
		cin >> ds[i].Sotrang;
		cin.ignore();
		cout << "\n";
		
		
		cout << "Nhap gia sach: ";
		cin>> ds[i].gia;
		cin.ignore();
		cout << "\n";
		
	}
	double ma = 0; int vitri = 0;
	for (int i = 0; i < 3; i++)
	{
		if (ds[i].gia >= ma)
		{
			ma = ds[i].gia;
			vitri = i;
		}
	}
	cout << "Thong tin cuon sach co gia cao nhat"; cout <<"\n\n";
	cout << "Ten cuon sach: " << ds[vitri].ten;
	cout <<"\n";
	cout <<"So trang sach: " << ds[vitri].Sotrang;
	cout <<"\n";
	cout <<"Gia cuon sach: " << ds[vitri].gia;
}
