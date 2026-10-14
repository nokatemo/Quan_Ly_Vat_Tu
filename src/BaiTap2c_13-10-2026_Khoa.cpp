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
	
	Sach* pds[3];
	for (int i = 0; i < 3; i++) pds[i] = &ds[i];
	
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3 - i - 1; j++)
		{
			if (pds[j]->gia > pds[j+1]->gia) 
			{
				swap(pds[j], pds[j+1]);
			}
		}
	}
	
	cout<< "Sap xep mang con tro theo thu tu gia tang dan";
	for (int i = 0; i < 3; i++)
	{
	
		cout << "\n";
		cout << pds[i]->ten; 
		cout <<"\n";
		cout <<"\n";
	}
	
	cout << "Thu tu goc cua mang ds";
	for (int i = 0; i < 3; i++)
	{
		
		cout <<"\n";
		cout << ds[i].ten;
		cout <<"\n";
	}
}
