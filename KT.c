#include <iostream> 
using namespace std;

// thông tin ngày tháng năm
struct Ngay {
    int ngay, thang, nam;
};

// Khai báo SV
struct SinhVien {
    char maSV[8];      // Mã sv (7 ký tự và 1 ký tự null)
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
    Node* next;     //trỏ đến node kế tiếp
};

struct List {
    Node* head;  // trỏ đầu danh sách
};

//tạo danh sách rỗng
void khoiTao(List &l) {
    l.head = NULL;
}

//so sánh hai chuỗi
int soSanhChuoi(const char* s1, const char* s2) {
    int i = 0;
    // So sánh từng ký tự
    while (s1[i] != '\0' && s2[i] != '\0') {
        if (s1[i] != s2[i]) {
            return s1[i] - s2[i];  // return về hiệu nếu khác
        }
        i++;
    }
    return s1[i] - s2[i];  // So sánh độ dài
}

// Tạo node mới
Node* taoNode(SinhVien sv) {
    Node* p = new Node;
    p->data = sv;
    p->next = NULL;
    return p;
}

// Thêm sv vào danh sách (tăng dần)
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

// Nhập tt
SinhVien nhapSinhVien() {
    SinhVien sv;
    cout << "Nhap ma sinh vien: ";
    cin >> sv.maSV;
    cout << "Nhap ho ten: ";
    cin.ignore();  // Xóa bộ đệm 
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

// In tt
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

int main() {
    List l;
    khoiTao(l);  //tạo danh sách

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

    return 0;
}

