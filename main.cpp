#include "cauhoi.h"
/* ----- Dinh nghia ham ----- */
char Menu(string dethi);
void OpenFile(ifstream& f);
void themCauHoi(ofstream& f);

CauhoiTN* cauhoi = nullptr;
int soCau = 0;
int diem = 0;
int main() {
    cout << "-------------------- CHUONG TRINH TAO DE THI TRAC NGHIEM --------------------" << endl;
    
    ifstream fin;
    ofstream fout;

    string dethi = "DeMoi.TTN";
    string temp;

    fin.open(dethi);
    bool running = true;
    while (running) {
        switch(Menu(dethi)) {
            case '1':
                cout << "Nhap ten file: ";
                cin >> temp;
                temp += ".TTN";
                fin.close();
                fin.open(temp);
                if (!fin.good()) {
                    cout << "Khong ton tai file " << temp << endl;
                } else {
                    OpenFile(fin);
                    dethi = temp;
                    fin.close();
                }
                break;

            case '2':
                cout << "Nhap ten file: ";
                cin >> dethi;
                dethi += ".TTN";
                fout.open(dethi);
                fout << "";
                delete[] cauhoi;
                soCau = 0;
                cout << "Ban da tao mot de thi moi co ten " << dethi << endl;
                fout.close();
                break;

            case '3':
                fout.open(dethi, ios::app);
                if (!fout.is_open()) {
                    cout << "Khong the mo tep";
                    break;
                }
                themCauHoi(fout);
                fout.close();
                break;

            case '4':
                cout << "\n---------- " << dethi << " ----------" << endl;
                for (int i = 0; i < soCau; i++) {
                    cout << "----------" << endl;
                    cout << "Cau " << i + 1 << ": ";
                    cauhoi[i].xuat();
                    cout << endl;
                }
                break;
            
            case '5':
                cout << "Nhap ten file: ";
                cin >> temp;
                fout.open(temp + ".TTN");
                for (int i = 0; i < soCau; i++) {
                    cauhoi[i].ghifile(fout);
                }
                cout << "Da luu cau hoi vao file " << temp + ".TTN" << endl;
                fout.close();
                break;

            case '6':
                cout << "----------- BAI KIEM TRA ----------" << endl;
                for (int i = 0; i < soCau; i++) {
                    cout << "----------" << endl;
                    cout << "Cau " << i + 1 << ": ";
                    if(cauhoi[i].kiemtra()) {
                        diem ++;
                    }
                }
                cout << "Diem so: " << diem << "/" << soCau << endl;
                break;
            
            case '7':
                running = false;
                break;
        }
    }
    fin.close();
    return 0;
}

/* ----- Nhap du lieu de thi ----- */
void OpenFile(ifstream& f) {
    while (!f.eof()) {
        CauhoiTN temp;
        temp.docfile(f);
        soCau++;

        CauhoiTN* newCauhoi = new CauhoiTN[soCau];
        for (int i = 0; i < soCau - 1; i++) {
            newCauhoi[i] = cauhoi[i];
        }
        newCauhoi[soCau - 1] = temp;
        delete[] cauhoi;
        cauhoi = newCauhoi;
    }
    if (soCau > 0) soCau--;
}

/* ----- Menu ----- */
char Menu(string dethi) {
    char choice;
    cout << "\n------- " << dethi << " --------" << endl;
    cout << "1. Mo de thi khac da co (FILE OPEN)." << endl;
    cout << "2. Tao de thi moi (FILE NEW). " << endl;
    cout << "3. Them cau hoi. " << endl;
    cout << "4. Danh sach cau hoi." << endl;
    cout << "5. Luu lai de thi (SAVE AS)." << endl;
    cout << "6. Bat dau thi." << endl;
    cout << "7. Roi khoi chuong trinh. " << endl;
    cout << "Nhap lua chon: ";
    cin >> choice;

    while (choice < '1' || choice > '7') {
        cout << "Khong co lua chon " << choice << ". Hay chon lai: ";
        cin >> choice;
    }
    return choice;
}

/* ----- Chuyen chuoi ve viet thuong ----- */
string chuyenVietThuong(string str) {
    transform(str.begin(), str.end(), str.begin(), :: tolower);
    return str;
}
/* ----- Kiem tra noi dung co giong nhau khong ----- */
bool giongnhau(CauhoiTN cau1, CauhoiTN cau2) {
    return
        chuyenVietThuong(cau1.cauhoi) == chuyenVietThuong(cau2.cauhoi) 
        && chuyenVietThuong(cau1.dapanA) == chuyenVietThuong(cau2.dapanA)
        && chuyenVietThuong(cau1.dapanB) == chuyenVietThuong(cau2.dapanB);
}
/* ----- Kiem tra cau hoi ----- */
bool check(CauhoiTN temp) {
    for (int i = 0; i < soCau; i++) {
        if (giongnhau(temp, cauhoi[i])) {
            cout << "Cau hoi vua nhap trung voi cau " << i + 1 << endl;
            return true;
        }
    }
    return false;
}

void themCauHoi(ofstream& f) {
    CauhoiTN temp;

    temp.nhap();    
    if (check(temp)) return;

    temp.ghifile(f);
    soCau++;
    CauhoiTN* newCauhoi = new CauhoiTN[soCau];
    for (int i = 0; i < soCau - 1; i++) {
        newCauhoi[i] = cauhoi[i];
    }
    newCauhoi[soCau - 1] = temp;

    delete[] cauhoi;
    cauhoi = newCauhoi;
}
