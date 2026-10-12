#include <iostream>
#include <string>
#include <iomanip>
using namespace std;
int N;

void Nhap (string ten[] ,double diemso[])
{
	for (int i = 0; i < N; i++)
	{
		getline(cin, ten[i]);
		cin >> diemso[i];
		cin.ignore();
	}
}

double dtbinh(string ten[],double diemso[])
{
	double dtb = 0; int cnt = 0; double tong = 0;
	for (int i = 0; i < N; i++)
	{
			 tong += diemso[i];
		   	 cnt++; 
	}	
	return	dtb = tong / cnt;
}

int Maxi(double diemso[])
{
	int mi = -1000, vitri;
	for (int i = 0; i < N; i++)
	{
		if (mi <= diemso[i]) 
		{
			mi = diemso[i];
		    vitri = i;
		}
	}
	return vitri;
}

int main()
{
	cin >> N;
	cin.ignore();
	string *ten = new string[N];
	double *diemso = new double[N];
	Nhap (ten, diemso);
	
	for (int i = 0; i < N; i++)
	{
		cout << "Hoc sinh: " << i + 1 << ", Ten: " << ten[i] << ", Diem So: " << diemso[i];
		cout <<"\n\n";
	}
	cout << "Diem Trung Binh Cua Ca Lop La: " << fixed << setprecision(2) << dtbinh(ten, diemso); 
	cout << "\n";
	cout << "Vi tri cua nguoi co so diem cao nhat la: " << Maxi(diemso) + 1 << ", ten la: " << ten[Maxi(diemso)];
	cout << "\n";
	
	delete[] ten;
	delete[] diemso;
	
	return 0;
}
