#include <iostream>
using namespace std;

// Thông tin ngày tháng năm
struct Ngay {
    int ngay, thang, nam;
};

// Khai báo sinh viên
struct SinhVien {
    char maSV[8];      // Mã sinh viên (7 ký tự và 1 ký tự null)
    char hoTen[50];   
    int gioiTinh;       // Giới tính (0: Nữ, 1: Nam)
    Ngay ngaySinh;      
    char diaChi[100];   
    char lop[12];      
    char khoa[7];       
};

// Khai báo Node và danh sách liên kết
struct Node {
    SinhVien data;  
    Node* next;     // Trỏ đến node kế tiếp
};

struct List {
    Node* head;  // Trỏ đầu danh sách
};

// Tạo danh sách rỗng
void khoiTao(List &l) {
    l.head = NULL;
}

// So sánh hai chuỗi
int soSanhChuoi(const char* s1, const char* s2) {
    int i = 0;
    while (s1[i] != '\0' && s2[i] != '\0') {
        if (s1[i] != s2[i]) {
            return s1[i] - s2[i];  // Return về hiệu nếu khác
        }
        i++;
    }
    return s1[i] - s2[i];
}

// Tạo node mới
Node* taoNode(SinhVien sv) {
    Node* p = new Node;
    p->data = sv;
    p->next = NULL;
    return p;
}

// Thêm sinh viên vào danh sách theo thứ tự mã sinh viên (tăng dần)
void themSinhVien(List &l, SinhVien sv) {
    Node* p = taoNode(sv);

    if (l.head == NULL || soSanhChuoi(l.head->data.maSV, sv.maSV) > 0) {
        p->next = l.head;
        l.head = p;
    } else {
        Node* q = l.head;
        while (q->next != NULL && soSanhChuoi(q->next->data.maSV, sv.maSV) < 0) {
            q = q->next;
        }
        p->next = q->next;
        q->next = p;
    }
}

// Nhập thông tin sinh viên
SinhVien nhapSinhVien() {
    SinhVien sv;
    cout << "Nhap ma sinh vien: ";
    cin >> sv.maSV;
    cout << "Nhap ho ten: ";
    cin.ignore();  
    cin.getline(sv.hoTen, 50);
    cout << "Nhap gioi tinh (0: Nu, 1: Nam): ";
    cin >> sv.gioiTinh;
    cout << "Nhap ngay sinh (ngay thang nam): ";
    cin >> sv.ngaySinh.ngay >> sv.ngaySinh.thang >> sv.ngaySinh.nam;
    cout << "Nhap dia chi: ";
    cin.ignore();
    cin.getline(sv.diaChi, 100);
    cout << "Nhap lop: ";
    cin >> sv.lop;
    cout << "Nhap khoa: ";
    cin >> sv.khoa;
    return sv;
}

// In danh sách sinh viên
void inDanhSach(List l) {
    Node* p = l.head;
    while (p != NULL) {
        cout << "Ma SV: " << p->data.maSV << endl;
        cout << "Ho ten: " << p->data.hoTen << endl;
        cout << "Gioi tinh: " << (p->data.gioiTinh ? "Nam" : "Nu") << endl;
        cout << "Ngay sinh: " << p->data.ngaySinh.ngay << "/"
             << p->data.ngaySinh.thang << "/" << p->data.ngaySinh.nam << endl;
        cout << "Dia chi: " << p->data.diaChi << endl;
        cout << "Lop: " << p->data.lop << endl;
        cout << "Khoa: " << p->data.khoa << endl;
        cout << "------------------------------" << endl;
        p = p->next;
    }
}

// kiểm tra và in các sinh viên có cùng ngày sinh
void inSinhVienCungNgaySinh(List l) {
    bool found = false;
    Node* p = l.head;

    while (p != NULL) {
        bool coSinhVienTrung = false;
        Node* q = p->next;

        while (q != NULL) {
            if (p->data.ngaySinh.ngay == q->data.ngaySinh.ngay &&
                p->data.ngaySinh.thang == q->data.ngaySinh.thang &&
                p->data.ngaySinh.nam == q->data.ngaySinh.nam) {
                
                if (!coSinhVienTrung) {
                    cout << "Sinh vien co ngay sinh " << p->data.ngaySinh.ngay << "/"
                         << p->data.ngaySinh.thang << "/" << p->data.ngaySinh.nam << ":\n";
                    cout << "Ma SV: " << p->data.maSV << ", Ho ten: " << p->data.hoTen << endl;
                    coSinhVienTrung = true;
                    found = true;
                }
                cout << "Ma SV: " << q->data.maSV << ", Ho ten: " << q->data.hoTen << endl;
            }
            q = q->next;
        }
        
        if (coSinhVienTrung) {
            cout << "------------------------------" << endl;
        }
        p = p->next;
    }

    if (!found) {
        cout << "Khong tim thay sinh vien cung ngay sinh.\n";
    }
}

// xóa sinh viên có cùng ngày sinh
void xoaSinhVienCungNgaySinh(List &l) {
    Node* p = l.head;
    Node* truoc = NULL;

    while (p != NULL) {
        Node* q = p->next;
        bool coSinhVienTrung = false;

        while (q != NULL) {
            if (p->data.ngaySinh.ngay == q->data.ngaySinh.ngay &&
                p->data.ngaySinh.thang == q->data.ngaySinh.thang &&
                p->data.ngaySinh.nam == q->data.ngaySinh.nam) {
                
                coSinhVienTrung = true;
                break;
            }
            q = q->next;
        }

        if (coSinhVienTrung) {
            if (truoc == NULL) {
                l.head = p->next;
            } else {
                truoc->next = p->next;
            }
            delete p;
            if (truoc == NULL) p = l.head;
            else p = truoc->next;
        } else {
            truoc = p;
            p = p->next;
        }
    }
}

int main() {
    List l;
    khoiTao(l);

    int n;
    cout << "Nhap so luong sinh vien: ";
    cin >> n;

    for (int i = 0; i < n; ++i) {
        cout << "\nNhap thong tin sinh vien thu " << i + 1 << ":\n";
        SinhVien sv = nhapSinhVien();
        themSinhVien(l, sv);
    }

    cout << "\nDanh sach sinh vien:\n";
    inDanhSach(l);

    cout << "\nCac sinh vien co cung ngay sinh:\n";
    inSinhVienCungNgaySinh(l);

    xoaSinhVienCungNgaySinh(l);
    cout << "\nDanh sach sinh vien sau khi loai bo sinh vien co ngay sinh trung lap:\n";
    inDanhSach(l);

    return 0;
}
