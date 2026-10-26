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

struct vattu{
	string mavt;
	string tenvt;
	int soluong;
	double dongia;
};

struct nodebst{
	vattu data;
	nodebst* left;
	nodebst* right;
};

nodebst* create(vattu vt){
	nodebst* p = new nodebst;
	p->data = vt;
	p->left=nullptr;
	p->right=nullptr;
	
	return p;
}

void list(vattu vt){
	cout << "Ma vat tu: " << vt.mavt << '\n';
    cout << "Ten vat tu: " << vt.tenvt << '\n';
    cout << "So luong: " << vt.soluong << '\n';
    cout << "Don gia: " << vt.dongia << '\n';
    cout << "Thanh tien: " << vt.soluong * vt.dongia << '\n';
    cout << "-------------------------\n";
}

void inorder(nodebst* root){
	if (root!=nullptr){
		inorder(root->left);
		list(root->data);
		inorder(root->right);
	}
}

nodebst* search(nodebst* root, string ma){
	if (root==nullptr||root->data.mavt==ma) return root;
	else if (ma < root->data.mavt) return search(root->left,ma);
	return search(root->right, ma);
}
float value(nodebst* root){
	if (root==nullptr) return 0;
	return root->data.soluong * root->data.dongia + value(root->left) + value(root->right);
}


nodebst* insert(nodebst* root,vattu vt){
	if (root == nullptr) return create( vt);
	else if (vt.mavt < root->data.mavt) root->left = insert(root->left,vt);
	else if (vt.mavt > root->data.mavt) root->right = insert(root->right,vt);
	else cout<<"Ma vat da ton tai, khong the them"<<endl;
	return root;
}

void input(vattu &vt, int i){
	xoaManHinh();
	cout<<"===== Vat tu thu "<<i+1<<" ======"<<endl;
	cout<<"Ma vat tu: "; cin>> vt.mavt; 
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout<<"Ten vat tu: "; getline(cin,vt.tenvt);
	cout<<"So luong: "; cin>>vt.soluong;
	cout<<"Don gia: "; cin>>vt.dongia;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

}

void freeroot(nodebst* root){
	if (root!=nullptr){
		freeroot(root->left); freeroot(root->right);
		delete root;
	}
}


void quayLaiMenu() {
    cout << "\nNhan Enter de quay lai menu...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

int main(){
	
	int n;bool loi;
	do{
		xoaManHinh();
		cout<<"Vui long nhap so vat tu can them: ";
		cin>>n;
		loi=cin.fail();
		if (loi||n<=0){
			cout<<"So vat tu phai la so nguyen duong lon hon 0"<<endl<<
			"Vui long thu lai....";
			Sleep(3000);
		}
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	} while (loi||n<=0);
	nodebst* root = nullptr;
	for (int i=0;i<n;i++){
		vattu vt;
		
		input (vt, i);
		
		root = insert(root, vt);
	}
	
	int select;
	do{
		xoaManHinh();
		cout<<"===== Menu ====="<<endl;
		cout<<"1. Xuat danh sach vat tu"<<endl;
		cout<<"2. Tim kiem thong tin vat tu"<<endl;
		cout<<"3. Tinh tong tien ton kho"<<endl;
		cout<<"0. Thoat chuong trinh"<<endl;
		cout<<"================"<<endl;

		cout<<"Vui long chon tinh nang: ";
		cin>>select;
		loi=cin.fail();
		if (loi || select < 0 || select >= 4){
			cout<<"Vui long chon tu 0-3"<<endl<<
			"Vui long thu lai....";
			Sleep(3000);
		}
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		
		if (select == 1) {
            if (root == nullptr) {
                cout << "Danh sach rong!\n";
            } else {
                cout << "\n=== DANH SACH VAT TU ===\n";
                inorder(root);
            }
            quayLaiMenu();
        }
        
        else if (select == 2){
        	string ma;
        	cout<<"Nhap ma vat tu: "; cin>>ma;
        	nodebst* p = search(root,ma);
        	
        	if (p == nullptr) {
                cout << "Khong tim thay vat tu!\n";
            } else {
                cout << "\n=== THONG TIN VAT TU ===\n";
                list(p->data);
            }
            quayLaiMenu();
		}
		
		else if (select == 3) {
            cout << "Tong gia tri ton kho: "
                 << value(root) << '\n';
                  quayLaiMenu();
        }
	} while (select!=0);
	
	freeroot(root);
	
	
	
	
	return 0;
}