#include <bits/stdc++.h>
using namespace std;

int n;

struct Sach {
	string ten;
	int Sotrang;
	double gia;
};

int main()
{
	cout <<"Nhap so sach: ";
	cin >> n;
	cin.ignore();
	
	Sach** ds = new Sach*[n];
	
	for (int i = 0; i < n; i++) 
	{
		ds[i] = new Sach;
		
		cout << "Nhap ten sach " << i + 1 << ":";
		getline(cin, ds[i]->ten);
		cout << "\n";
		
		cout << "Nhap so trang sach: ";
		cin >> ds[i]->Sotrang;
		cin.ignore();
		cout << "\n";
		
		
		cout << "Nhap gia sach: ";
		cin>> ds[i]->gia;
		cin.ignore();
		cout << "\n";
	}
	
	for (int i = 0; i < n; i++)
	{
		cout << "Ten sach " << i + 1 << " la: " << ds[i]->ten; cout <<"\n";
		cout << "So trang sach " << i + 1 << " la: " << ds[i]->Sotrang; cout <<"\n";
		cout << "Gia sach " << i + 1 << " la: " << ds[i]->gia; cout <<"\n";
	}
	
	for (int i = 0; i < n; i++) delete ds[i];
	 delete[] ds;
}
