#include <iostream>
#include <string>
#include <limits>
using namespace std;

// 1. Ham nhap thong tin hoc sinh

void nhapThongTin(string ten[], double diem[], int N) {
    for (int i = 0; i < N; i++) {
        system("cls");

        cout << "Nhap ten hoc sinh so " << i + 1 << ": ";
        getline(cin, ten[i]);

        while (true) {
            cout << "Nhap diem hoc sinh so " << i + 1
                 << " (0 - 10): ";

            if (!(cin >> diem[i])) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                 system("cls");
                cout << "Vui long nhap mot so!\n";
                continue;
            }

            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (diem[i] >= 0 && diem[i] <= 10) {
                break;
            }

            cout << "Diem khong hop le! Nhap lai.\n";
        }
    }
}


// 2. Ham tinh diem trung binh
double tinhTrungBinh(const double diem[], int N) {
    // TODO: Tinh tong va tra ve trung binh
    double tong=0,tb;
    for (int i=0; i<N; i++){
        tong+=diem[i];
    }
    tb = tong/N;

    return tb;
}

// 3. Ham tim vi tri diem cao nhat
int timMax(const double diem[], int N) {
    int vtmax=0;
    for (int i=1; i < N; i++){
        if (diem[i] >diem[vtmax]) vtmax = i;
    }
    return vtmax;
}

int main() {
    int N;
    do{
        system("cls");
        cout<<"Nhap so luong hoc sinh (> 0): ";
        cin>>N;
        cin.ignore(10000, '\n');
    }  while(N<=0);
    string *ten=new string[N];
    double *diem=new double[N];
    nhapThongTin(ten,diem, N);
    double tb = tinhTrungBinh(diem,N); 
    int vtmax = timMax(diem,N);
    cout<<"Danh sach hoc sinh: ";
    for (int i=0; i<N; i++){
        cout<<ten[i]<<": "<<diem[i]<<endl;
    }
    cout<<"Diem trung binh cua lop: "<< tb<<endl;
    cout<<"Ban "<<ten[vtmax]<< " co diem cao nhat la "<<diem[vtmax]<<" diem";
    delete[] ten;
    delete[] diem;
    return 0;
}
