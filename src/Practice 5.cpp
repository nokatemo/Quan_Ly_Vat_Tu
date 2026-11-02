	#include <iostream>
	#include <string>
	#include <limits>
	#include <windows.h>
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
	
	struct Sach{
		string ten;
		double gia;
		int page;
	};
	int main(){
		bool loi;
		int n;
		do{
			
			xoaManHinh();
			cout<<"Nhap n (n>0): ";
			cin>>n;
			loi=cin.fail();
			if (loi) cin.clear();
			 	if (loi || n <= 0) {
        			cout << "n phai la so nguyen duong lon hon 0!\n";
        			Sleep(3000);
        			FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
    			}
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}while ( loi || n<=0);
		
		Sach **ds = new Sach*[n]; 
		for (int i=0; i<n;i++){
			xoaManHinh();

			ds[i]=new Sach;
			cout<<"Nhap thong tin sach "<<i+1<<":"<<endl<<
			"Ten: ";
			getline(cin,ds[i]->ten);
			
			do{
				cout<<"So trang: ";
			    cin>>ds[i]->page;
			    
			    loi=cin.fail();
				if (loi) cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
			 		if (loi || n <= 0) {
			 			cout << "\033[J";
        				cout << "So trang phai la so nguyen duong lon hon 0!\n";
        				Sleep(3000);
        				FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
        				cout << "\033[2A\033[J";
    			}
			}while ( loi || n<=0);
			
			do{

				cout<<"Gia: ";
			cin>>ds[i]->gia;
			    loi=cin.fail();
				if (loi) cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
			 		if (loi || n <= 0) {
        				cout << "So tien phai la so thuc duong lon hon 0!\n";
        				Sleep(3000);
        				FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
        				cout << "\033[2A\033[J";
    			}
			}while ( loi || n<=0);
		
		}
		xoaManHinh();
		cout<<"==== Danh sach cac sach ===="<<endl;
		for (int i=0; i<n;i++){
			if (i>=1) cout<<endl;
			cout<<"Sach "<<ds[i]->ten<<": "<<endl;
			cout<<"Page: "<<ds[i]->gia<<endl;
			cout<<"Gia: "<<ds[i]->page<<endl;
			                 
		}
	}
		