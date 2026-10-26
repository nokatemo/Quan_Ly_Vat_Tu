#include <bits/stdc++.h>
using namespace std;

struct Sv 
{
	string mssv;
	string ten;
};


int main()
{
	Sv sv1, sv2, sv3;
	
	ofstream fileOut("Dssv.txt", ios::out);
	if (!fileOut.is_open()) 
	{
		cout << "File khong the mo";
		return 0;
	}
	else
	{
		sv1.mssv = "SV01";
		sv1.ten = "Bui Vu Nguyen Khoa";
		sv2.mssv = "SV02";
		sv2.ten = "Ngo Minh Tien";
		sv3.mssv = "SV03";
		sv3.ten = "Tran Trung Nguyen";
		
		fileOut << sv1.mssv << "|" << sv1.ten << "\n";
		fileOut << sv2.mssv << "|" << sv2.ten << "\n";
		fileOut << sv3.mssv << "|" << sv3.ten << "\n";
	}
	fileOut.close();
	
	ifstream fileIn("Dssv.txt", ios::in);
	
	string ma, ten;

	while(getline(fileIn, ma, '|'))
	{
		getline(fileIn, ten, '\n');
		cout << "Ma Sinh Vien: " << ma << " " << "Ten: "<< ten <<  "\n";
	}
	
	
	fileIn.close();
	return 0;
	
	
	
}
