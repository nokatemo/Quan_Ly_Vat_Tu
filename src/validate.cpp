#include "validate.h"


#include<iostream> 
#include<string> // nhap chuoi
#include<sstream> 
#include<cctype> 
#include <conio.h>   // _getch()
#include <stdexcept> // out_of_range
#include <cstddef>   // size_t
using namespace std;

// chuan hoa ten
void chuanhoaten(string& str) {
	while (!str.empty() && str.front() == ' '){
		 str.erase(0, 1) ;
	}
	
	while (!str.empty() && str.back() ==' '){
		str.pop_back();
	}
	for (size_t i = 1 ; i < str.size() ; i++ ) {
	 if (str [ i -1] == ' ' && str[i] == ' ' ) {
			str.erase(i,1);
		i-- ;
		}
		
	}
   for (size_t i =0; i < str.size(); i++ ) {
   	unsigned char c = static_cast < unsigned char > (str [i]) ;
   	if ( i == 0 || str [i - 1] == ' ') {
   		str [i] = static_cast <char> (toupper(c));
	   }
	else {
		str [i] = static_cast <char> (tolower(c)) ;
	}
   }
}
   
// tinh nam nhuan
bool namnhuan (int nam){
	if ((nam % 400 == 0) || ( nam % 4 == 0 && nam % 100 != 0)){
	return true ;
}
   else {
   	return false ;
   }
}

// tinh ngay trong thang , nam
int kiemtrangay(int thang,int nam){
	int luungay;
	switch(thang) {
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
			luungay = 31;
			break ;
		case 4:
		case 6:
	    case 9:
	    case 11:
	    	luungay = 30;
	    	break;
	    case 2: {
	    	if(namnhuan(nam)) {
	    		luungay = 29;
			}
	    	else {
	    		luungay = 28;
			}
			break;
		}
		default : 
		return 0;
	}
	return luungay;
}

// kiem tra ngay thang nam hop le
bool ngayhople (int ngay , int thang, int nam) {
	if ( nam < 1900) {
		return false ;
	}
	if (thang < 1 || thang > 12) {
		return false ;
	}
	
	if (ngay < 1 || ngay > kiemtrangay (thang , nam) ) {
		return false ;
	}
	return true;
}


 // di voi chuan hoa ten () (chan so khi nhap )
bool conso (const string& ten) {
	for ( size_t i = 0 ; i < ten.size() ; i++) {
	 if(ten[i] >= '0' && ten [i] <= '9') {
	 	return true ;
	  }
	}
	return false;
}

// nhap ma
string NhapMaID(size_t maxlen) {
	int result; // chuoi ban dau rong
	
	while (true) {
		int c = _getch(); // cho bam 1 phim
		// mui ten , f1..
		if (c == 0 || c == 224) {
			_getch();
			continue;
		}
		//space
		if (c == ' ') {
			continue;
		}
		 // enter
		if (c == 13) {
			break;
		}
		//backspace;
		if (c == 8) {
			if (!result.empty()) {
				result.pop_back();
				cout << "\b \b"  << flush;
			}
			continue;
		}
		// ngoai khoang 33 - 126 ko nhan;
		if ( c < 33 || c > 126 ) {
			continue;
		}
		// toi maxlen thi dung.
		if (size.result >= maxlen) {
			continue;
		}
		// chuyen thanh chu hoa
		char upper = static_cast <char>(toupper(static_cost<unsigned char>(c)));
		
		result+=upper;
		
		cout << upper << flush;	
	} 	
	return result;
} 

// nhap so nguyen
int nhapsonguyen() {
	string s;
	while (true) {
		int c = _getch();
		if (c == 0 || c == 224) {
		   _getch();
		   continue;
		}
		
		if (c == 8){
		  if(!s.empty()) {
		  	s.pop_back();
		  	cout << "\b \b" <<flush;
        }
        continue;
	 }
		if (c == 13) {
			if (s.empty() || s == " "){
				continue;
		}
			try {
				int n = stoi (s);
				cout <<"\n";
				return n;
			}
			catch(const out_of_range&){
				cout << "\n so vuot pham vi. nhap lai: " << flush;
				s.clear();
			}
			continue;
		}
		if (  (c >= '0' && c <= '9' )||( c == '-' && s.empty())) {
			char kytu = static_cast<char>(c);
			s +=kytu;
			cout << kytu << flush; 
		}
   }
}

 \\ nhap so thuc.
 void nhapsothuc () {
 	string s;
 	while (true) {
 		char c = _getcha();
 		
 		if  (c == 0 || c == 224) {
 			_getch();
 			continue;
		 }
		 
		 if  (c == 8) {
		 	if (!s.empty) {
		 		s.pop_back();
		 		cout << "\b \b" << flush;
			 }
			 continue;
		 }
		 
		 if (c == 13) {
		   if (s.empty() || c == ' ' ) {
		   	continue;
		   }
		   
		   try {
		   	  double n = stoi(t);
		   	  cout << "\n";
		   	  return n;
		   }
		   
		   catch (const out_of_range&) {
		   	cout << "\n so vuot pham vi. nhap lai: " << flush;
		   	s.clear();
		   }
		   continue;
		 }
		 
		 if ( (c == '0' && c == '9') || (c == '-' && s.empty()) || (c == '.' && s.find('.') == string::npos)) {
		 	char kytu = static_cast <char> (c);
		 	s += kytu;
		 	cout << kytu << flush; \\ flush lu du lieu va in ra man hing cung dong
		 }	 
	 }
 }

