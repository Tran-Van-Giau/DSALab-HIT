#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

// =====================================================
// STRUCT SINH VIEN
// =====================================================

struct SinhVien {
    string ten;
    string mssv;
    float diem;
};

// =====================================================
// CLASS QUAN LY SINH VIEN
// =====================================================

class StudentManager {

private:

    SinhVien* ds;
    int size;
    int capacity;

public:

    // Constructor
    StudentManager() {

        capacity = 2;
        size = 0;

        ds = new SinhVien[capacity];
    }

    // Destructor
    ~StudentManager() {

        delete[] ds;
    }

    // =====================================================
    // RESIZE MANG
    // =====================================================

    void resize() {

        capacity *= 2;

        SinhVien* temp = new SinhVien[capacity];

        for (int i = 0; i < size; i++) {
            temp[i] = ds[i];
        }

        delete[] ds;

        ds = temp;
    }

    // =====================================================
    // THEM SINH VIEN
    // =====================================================

    void themSinhVien() {

        if (size == capacity) {
            resize();
        }

        cin.ignore();

        cout << "\nNhap ten: ";
        getline(cin, ds[size].ten);

        cout << "Nhap MSSV: ";
        getline(cin, ds[size].mssv);

        cout << "Nhap diem: ";
        cin >> ds[size].diem;

        size++;

        cout << "\nThem sinh vien thanh cong!\n";
    }

    // =====================================================
    // XUAT DANH SACH
    // =====================================================

    void xuatDanhSach() {

        if (size == 0) {

            cout << "\nDanh sach rong!\n";
            return;
        }

        cout << "\n=====================================================\n";

        cout << left
             << setw(25) << "TEN"
             << setw(20) << "MSSV"
             << setw(10) << "DIEM"
             << endl;

        cout << "=====================================================\n";

        for (int i = 0; i < size; i++) {

            cout << left
                 << setw(25) << ds[i].ten
                 << setw(20) << ds[i].mssv
                 << setw(10) << ds[i].diem
                 << endl;
        }
    }

    // =====================================================
    // TIM MSSV
    // =====================================================

    int timTheoMSSV(string mssv) {

        for (int i = 0; i < size; i++) {

            if (ds[i].mssv == mssv) {
                return i;
            }
        }

        return -1;
    }

    // =====================================================
    // TIM THEO TEN
    // =====================================================

    void timTheoTen(string ten) {

        bool found = false;

        for (int i = 0; i < size; i++) {

            if (ds[i].ten == ten) {

                cout << "\nTim thay:\n";

                cout << ds[i].ten
                     << " | "
                     << ds[i].mssv
                     << " | "
                     << ds[i].diem
                     << endl;

                found = true;
            }
        }

        if (!found) {
            cout << "\nKhong tim thay!\n";
        }
    }

    // =====================================================
    // XOA SINH VIEN
    // =====================================================

    void xoaSinhVien() {

        cin.ignore();

        string mssv;

        cout << "\nNhap MSSV can xoa: ";
        getline(cin, mssv);

        int vt = timTheoMSSV(mssv);

        if (vt == -1) {

            cout << "\nKhong tim thay sinh vien!\n";
            return;
        }

        for (int i = vt; i < size - 1; i++) {
            ds[i] = ds[i + 1];
        }

        size--;

        cout << "\nDa xoa sinh vien!\n";
    }

    // =====================================================
    // SUA SINH VIEN
    // =====================================================

    void suaSinhVien() {

        cin.ignore();

        string mssv;

        cout << "\nNhap MSSV can sua: ";
        getline(cin, mssv);

        int vt = timTheoMSSV(mssv);

        if (vt == -1) {

            cout << "\nKhong tim thay!\n";
            return;
        }

        cout << "\nNhap ten moi: ";
        getline(cin, ds[vt].ten);

        cout << "Nhap diem moi: ";
        cin >> ds[vt].diem;

        cout << "\nCap nhat thanh cong!\n";
    }

    // =====================================================
    // SAP XEP THEO DIEM (BUBBLE SORT)
    // =====================================================

    void sapXepTheoDiem() {

        for (int i = 0; i < size - 1; i++) {

            for (int j = size - 1; j > i; j--) {

                if (ds[j].diem > ds[j - 1].diem) {

                    SinhVien temp = ds[j];
                    ds[j] = ds[j - 1];
                    ds[j - 1] = temp;
                }
            }
        }

        cout << "\nDa sap xep theo diem!\n";
    }

    // =====================================================
    // THONG KE
    // =====================================================

    void thongKe() {

        if (size == 0) {

            cout << "\nDanh sach rong!\n";
            return;
        }

        float tong = 0;
        float max = ds[0].diem;
        float min = ds[0].diem;

        for (int i = 0; i < size; i++) {

            tong += ds[i].diem;

            if (ds[i].diem > max)
                max = ds[i].diem;

            if (ds[i].diem < min)
                min = ds[i].diem;
        }

        cout << "\n========== THONG KE ==========\n";

        cout << "Diem cao nhat : " << max << endl;
        cout << "Diem thap nhat: " << min << endl;
        cout << "Diem trung binh: "
             << tong / size << endl;
    }

    // =====================================================
    // XEP HANG
    // =====================================================

    void xepHang() {

        cout << "\n========== XEP HANG ==========\n";

        for (int i = 0; i < size; i++) {

            cout << i + 1 << ". "
                 << ds[i].ten
                 << " - "
                 << ds[i].diem
                 << endl;
        }
    }

    // =====================================================
    // XUAT FILE
    // =====================================================

    void xuatFile() {

        ofstream file("diem_sinhvien.txt");

        if (!file) {

            cout << "\nKhong mo duoc file!\n";
            return;
        }

        file << left
             << setw(25) << "TEN"
             << setw(20) << "MSSV"
             << setw(10) << "DIEM"
             << endl;

        for (int i = 0; i < size; i++) {

            file << left
                 << setw(25) << ds[i].ten
                 << setw(20) << ds[i].mssv
                 << setw(10) << ds[i].diem
                 << endl;
        }

        file.close();

        cout << "\nDa xuat file diem_sinhvien.txt\n";
    }
};

// =====================================================
// MAIN
// =====================================================

int main() {

    StudentManager sm;

    int chon;

    do {

        cout << "\n";
        cout << "=== QUAN LY DIEM SINH VIEN ===\n";
        cout << "1. Them sinh vien\n";
        cout << "2. Xoa sinh vien\n";
        cout << "3. Tim kiem theo ten\n";
        cout << "4. Sap xep theo diem\n";
        cout << "5. Xep hang lop\n";
        cout << "6. Thong ke\n";
        cout << "7. Xuat danh sach\n";
        cout << "8. Xuat file\n";
        cout << "9. Sua sinh vien\n";
        cout << "0. Thoat\n";

        cout << "Chon: ";
        cin >> chon;

        switch (chon) {

        case 1:
            sm.themSinhVien();
            break;

        case 2:
            sm.xoaSinhVien();
            break;

        case 3: {

            cin.ignore();

            string ten;

            cout << "\nNhap ten can tim: ";
            getline(cin, ten);

            sm.timTheoTen(ten);

            break;
        }

        case 4:
            sm.sapXepTheoDiem();
            break;

        case 5:
            sm.xepHang();
            break;

        case 6:
            sm.thongKe();
            break;

        case 7:
            sm.xuatDanhSach();
            break;

        case 8:
            sm.xuatFile();
            break;

        case 9:
            sm.suaSinhVien();
            break;

        case 0:
            cout << "\nThoat chuong trinh!\n";
            break;

        default:
            cout << "\nLua chon khong hop le!\n";
        }

    } while (chon != 0);

    return 0;
}
