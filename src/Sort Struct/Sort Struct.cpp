#include <iostream>
#include <string>
#include <windows.h>
#include <limits>
using namespace std;

void xoaManHinh() {
   		HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    	CONSOLE_SCREEN_BUFFER_INFO csbi;
    	DWORD written;

    	GetConsoleScreenBufferInfo(h, &csbi);

    	DWORD size = csbi.dwSize.X * csbi.dwSize.Y;
    	COORD topLeft = {0, 0};

    	FillConsoleOutputCharacter(h, ' ', size, topLeft, &written);
    	FillConsoleOutputAttribute(h, csbi.wAttributes, size, topLeft, &written);
    	SetConsoleCursorPosition(h, topLeft);
}

struct SinhVien{
	char MASV[11];
	string HO,TEN;
	float DTB;
};

void xuatDS(SinhVien *ds[], int n){
	cout<<"==== Danh sach sinh vien ===="<<endl;
	for (int i=0; i<n; i++){

		cout<<"\nMASV: "<< ds[i]->MASV<<endl;
		cout<<"HO: "<< ds[i]->HO<<endl;
		cout<<"TEN: "<< ds[i]->TEN<<endl;
		cout<<"DTB: "<< ds[i]->DTB<<endl;
	}
}

void swapSinhVien (SinhVien *&a, SinhVien *&b ){
	SinhVien *temp = a;
	a=b;
	b=temp;
}

void sortTheoTen(SinhVien *ds[], int n){
	for (int i=0;i<n-1;i++){
		for (int j=0;j<n-i-1;j++){
			if (ds[j]->TEN>ds[j+1]->TEN ||ds[j]->TEN==ds[j+1]->TEN && ds[j]->HO>ds[j+1]->HO ) 
			swapSinhVien(ds[j],ds[j+1]);
		}
	}
}

void MaxDTB(SinhVien *ds[], int n){
	float Max=ds[0]->DTB;
	cout<<"==== Danh sach sinh vien co diem cao nhat ===="<<endl;
	for (int i=0;i<n;i++){
		if (Max<ds[i]->DTB) Max=ds[i]->DTB;
		
	}
	
	for (int i=0;i<n;i++){

		if (Max==ds[i]->DTB) {
			cout<<"\nMASV: "<< ds[i]->MASV<<endl;
			cout<<"HO: "<< ds[i]->HO<<endl;
			cout<<"TEN: "<< ds[i]->TEN<<endl;
			cout<<"DTB: "<< ds[i]->DTB<<endl;
		}
		
	}
}

int main(){
	int n;
	bool loi;
	
	do{
		xoaManHinh();
		
		cout<<"Vui long nhap n (n>0): ";
		cin>> n;
		loi=cin.fail();
		if (loi) cin.clear();
		if (loi || n<=0){
			cout<<"n phai la so nguyen duong lon hon 0!";
			cout<<endl<<"Vui long thu lai...\n";
			Sleep(3000);
        	FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
		}		
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	} while (loi || n<=0);
	
	SinhVien **ds = new SinhVien*[n];
	for (int i=0;i<n;i++){
		ds[i]= new SinhVien;
	}
	
	for (int i=0;i<n;i++){
		xoaManHinh();
		
		
		cout<<"Nhap thong tin sinh vien "<<i+1<<endl;
		cout<<"MASV: ";
		cin>>ds[i]->MASV;
		cin.ignore();
		
		
		cout<<"HO: ";
		cin>>ds[i]->HO;
		cin.ignore();
		
		cout<<"TEN: ";
		cin>>ds[i]->TEN;
		cin.ignore();
	
		
		do{
				cout<<"DTB: ";
			    cin>>ds[i]->DTB;
			    
			    loi=cin.fail();
				if (loi) cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
			 		if (loi || ds[i]->DTB < 0||ds[i]->DTB>10) {
			 			cout << "\033[J";
        				cout << "DTB phai la so thuc lon hon 0 va nho hon 10!\n";
        				Sleep(3000);
        				FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
        				cout << "\033[2A\033[J";
    			}
    					xoaManHinh();
		}while ( loi || ds[i]->DTB < 0||ds[i]->DTB > 10);
	}
	
	
	sortTheoTen(ds,n)
	xuatDS(ds,n);
	MaxDTB(ds,n);
	
	
	
	for (int i=0;i<n;i++){
		delete ds[i];
	}
	

	
	delete [] ds;
	
	return 0;
}



