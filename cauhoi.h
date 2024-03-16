#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

class CauhoiTN {
    private:
        string cauhoi;
        string dapanA;
        string dapanB;
        char dapandung;
    public:
        // Nhap cau hoi va dap an tu nguoi dung
        void nhap() {
            cin.ignore();
            cout << "Nhap noi dung cau hoi: ";
            getline(cin, cauhoi);

            cout << "Nhap noi dung dap an A: ";
            getline(cin, dapanA);

            cout << "Nhap noi dung dap an B: ";
            getline(cin, dapanB);

            do {
                cout << "Dap an dung (A or B): ";
                cin >> dapandung;
            } while (dapandung < 'A' || dapandung > 'B');
        }

        // Doc cau hoi tu file
        void docfile(ifstream& f) {
            if (!f.is_open()) {
                cout << "Khong the mo file" << endl;
                return;
            }

            getline(f, cauhoi);
            getline(f, dapanA);
            getline(f, dapanB);
            f >> dapandung;

            f.ignore();
        }

        // Ghi cau hoi vao file
        void ghifile(ofstream& f) {
            if (!f.is_open()) {
                cout << "Khong the mo file" << endl;
                return;
            }
            f << cauhoi << endl;
            f << dapanA << endl;
            f << dapanB << endl;
            f << dapandung << endl;
        }

        // Kiem tra
        bool kiemtra() {
            cout << cauhoi << endl;
            cout << "A. " << dapanA << endl;
            cout << "B. " << dapanB << endl;
            
            char cautraloi;
            cout << "Cau tra loi (A or B): ";
            cin >> cautraloi;
            if (cautraloi == 'a' || cautraloi == 'b') cautraloi -= 32;

            if (cautraloi == dapandung) {
                cout << "Dung" << endl;
                return true;
            }
            else cout << "Sai" << endl;
            return false;
        }

        // Xuat cau hoi ra man hinh
        void xuat() {
            cout << cauhoi << endl;
            cout << "A. " << dapanA << endl;
            cout << "B. " << dapanB << endl;
            cout << "Dap an dung: " << dapandung << endl;
        }

        friend bool giongnhau(CauhoiTN cau1, CauhoiTN cau2);        
};