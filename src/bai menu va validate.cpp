#include<iostream>
#include<string>
#include<sstream>
#include<cstdlib>
#include<limits>
using namespace std;

int nhapsonguyen() {
	int so ;
	string nhap;
	
	while(true) {
		cout <<" nhap lua chon : ";
		if (!getline(cin, nhap)){
			return 0;
		}
		
		stringstream doc(nhap);
		char kytuthua;
		
	    if ((doc >> so) && !(doc >> kytuthua) && so >= 0 && so <=2) {
	    	return so;
		}
		cout << "nhap sai vui long nhap lai.....\n";
	}
} 


void xoakhoangtrangthua(string &s) {
	stringstream tach(s);
	string tu;
	string kqua;
	
	while(tach >> tu){
		if(!kqua.empty()) {
			kqua += " " ;
		}
		
		kqua+= tu;
		
	}
	s = kqua ;
}

bool NamNhuan(int nam) {
	if(nam % 400 == 0 || nam % 4 == 0 && nam % 100 != 0) {
	return true;
    }
    else {
    	return false;
	}
}

int tinhsongaytrongthang(int thang, int nam){
    int luungay;
    
    switch(thang){
    	case 1:
    	case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
        	 luungay = 31;
        	break;
    	case 4:
        case 6:
        case 9:
        case 11:
        	 luungay = 30;
        case 2:
			if (NamNhuan(nam)) {
				luungay = 29;
			}
            else {
            	luungay = 28;
			}
	}
	return luungay;
}

bool kiemtrangay (int ngay, int thang, int nam ) {
	if (nam < 0) {
		return false;
	}
	
	if (thang < 1, thang > 12 ) {
		return false;
	}
	
	if ( ngay < 1 || ngay > tinhsongaytrongthang(thang, nam) ) {
	return false;
    }
    
    return true;
}


 void hienMenu() {
 	system("cls") ;
 	cout << "\n  ====== Quan Ly Vat Tu ======\n";
 	cout << "  |1. Nhap vat tu            |\n";
 	cout << "  |2. In vat tu              |\n";
 	cout << "  |0. Thoat chuong trinh     |\n";
	cout << "  ============================\n";
 }
 
 int main (){
 	string s;
 	int ngay, thang, nam ;
 	
 	while (true) {
 		hienMenu();
 		
 		int luachon = nhapsonguyen();
 		
 		switch (luachon) {
 			case 1 : {
 				    system ("cls");
 				   do {
 				   	cout << "\n--- nhap vat tu---\n" ;
 				   	cout << " Nhap ten vat lieu: " ;
 				   	if (!getline (cin , s)) {
 				   		return 0;
						}
					 xoakhoangtrangthua(s) ;
					 
					 if (s.empty()){
					 	cout << " khong duoc de trong ...";
					 }
 				   	  
					} while(s.empty());
					system ("cls");
					cout << "\n--- nhap vat tu---\n" ;
					cout << "Nhap ten vat lieu: " << s << "\n" ;
					cout << "nhap ngay, thang, nam:";
					cin >> ngay ; cin >> thang ; cin >> nam;
					cin.ignore();
					if (kiemtrangay(ngay, thang, nam)){
						cout << "hop le..\n";
					}
					else {
						cout <<" khong hop le..\n";
					}
					
				break;
			 }
			 
		    case 2 : {
		    	if (s.empty()) {
		    		cout << "khong co ten nao duoc luu \n";
		    	}
		    	else {
		    		system("cls");
		    		if(kiemtrangay(ngay, thang, nam)){
		    		cout << "  ======================== Thong Tin ========================\n";
		    		cout << "  | Ten vat tu : " << s <<"                                 |\n";
		    		cout << "  | ngay thang nam: "<< ngay <<"/" << thang <<"/" << nam <<"|\n";
		    		cout << "  ===========================================================\n";
		        	}
		        	else {
		                  cout << "khong co ten nao duoc luu\n";
					}
				}
				break;
			}
			case 0:
			    return 0;
			    
			default : 
			      cout << " nhap sai vui long nhap lai";
				break;
		 }
		 
		 	cout << " nhan enter de ve menu...";
				string tam;
				if (!getline(cin, tam)) {

				return 0;
			}
	 } 
return 0;
 }
