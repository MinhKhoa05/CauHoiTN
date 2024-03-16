#include "cauhoi.h"
/* ----- Dinh nghia ham ----- */
char Menu(string dethi);
void OpenFile(ifstream& f);
void FileNew(ofstream& f);
void NewQuestion(ofstream& f);
void ListQuestions();
void SaveAs(ofstream& f);
void TakeTheExam();
void CapNhatMangDong(CauhoiTN cau);

CauhoiTN* cauhoi = nullptr;
int soCau = 0;
int diem = 0;
string dethi = "DeMoi.TTN";

int main() {
    cout << "-------------------- CHUONG TRINH TAO DE THI TRAC NGHIEM --------------------" << endl;
    
    ifstream fin;
    ofstream fout;

    bool running = true;
    while (running) {
        fin.open(dethi);
        switch(Menu(dethi)) {
            case '1':
                fin.close(); // Dong file cu truoc khi mo file
                OpenFile(fin);
                break;

            case '2':
                FileNew(fout);
                break;

            case '3':
                NewQuestion(fout);
                break;

            case '4':
                ListQuestions();
                break;
            
            case '5':
                fin.close();
                SaveAs(fout);
                break;

            case '6':
                TakeTheExam();
                break;
            
            case '7':
                running = false;
                break;
        }
    }
    fin.close();
    return 0;
}

/* ----- Menu ----- */
char Menu(string dethi) {
    char choice;
    cout << "\n------- " << dethi << " --------" << endl;
    cout << "1. Mo de thi (Open File)" << endl;
    cout << "2. Tao de thi moi (File New)" << endl;
    cout << "3. Cau hoi moi (New Question)" << endl;
    cout << "4. Danh sach cau hoi (List Questions)" << endl;
    cout << "5. Luu lai de thi (Save As)." << endl;
    cout << "6. Lam kiem tra (Take The Exam)" << endl;
    cout << "7. Roi khoi chuong trinh (Exit)" << endl;
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
    return chuyenVietThuong(cau1.cauhoi) == chuyenVietThuong(cau2.cauhoi) 
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

/* ----- Nhap du lieu de thi ----- */
void OpenFile(ifstream& f) {
    string filename;
    cout << "Nhap ten file: ";
    cin >> filename;

    filename += ".TTN";
    f.open(filename);

    if (!f.good()) {
        cout << "Khong ton tai file " << filename << endl;
        return;
    }
    
    while (!f.eof()) {
        CauhoiTN cauhoi_moi;
        cauhoi_moi.docfile(f);
        CapNhatMangDong(cauhoi_moi);
    }
    dethi = filename;
    f.close();
    // Tru so cau di 1 vi dong cuoi la dong trong
    if (soCau > 0) soCau--;
}

/* ----- Cap nhat mang dong ----- */
void CapNhatMangDong(CauhoiTN cau) {
    soCau ++;
    CauhoiTN* cauhoi_moi = new CauhoiTN[soCau];
    
    for (int i = 0; i < soCau - 1; i++) {
        cauhoi_moi[i] = cauhoi[i];
    }

    cauhoi_moi[soCau - 1] = cau;
    delete[] cauhoi;
    cauhoi = cauhoi_moi;
}

/* ----- Tao de thi moi ----- */
void FileNew(ofstream& f) {
    cout << "Nhap ten file: ";
    cin >> dethi;
    dethi += ".TTN";
    f.open(dethi);

    // Reset du lieu dang duoc luu trong cac bien
    delete[] cauhoi;
    f << "";
    soCau = 0;

    cout << "Ban da tao mot de thi moi co ten " << dethi << endl;
    f.close();
}

void NewQuestion(ofstream& f) {
    f.open(dethi, ios::app);
    CauhoiTN cauhoi_moi;

    cauhoi_moi.nhap();    
    if (check(cauhoi_moi)) return;

    cauhoi_moi.ghifile(f);

    CapNhatMangDong(cauhoi_moi);
    f.close();
}

void ListQuestions() {
    cout << "\n---------- " << dethi << " ----------" << endl;
    for (int i = 0; i < soCau; i++) {
        cout << "----------" << endl;
        cout << "Cau " << i + 1 << ": ";
        cauhoi[i].xuat();
        cout << endl;
    }
}

void SaveAs(ofstream& f) {
    cout << "Nhap ten file: ";
    cin >> dethi;
    dethi += ".TTN";
    f.open(dethi);
    for (int i = 0; i < soCau; i++) {
        cauhoi[i].ghifile(f);
    }
    cout << "Da luu cau hoi vao file " << dethi << endl;
    f.close();
}

void TakeTheExam() {
    cout << "----------- KIEM TRA ----------" << endl;
    for (int i = 0; i < soCau; i++) {
        cout << "Cau " << i + 1 << ": ";
        if(cauhoi[i].kiemtra()) diem ++;
        cout << "----------" << endl;
    }
    cout << "Diem so: " << diem << "/" << soCau << endl;
}