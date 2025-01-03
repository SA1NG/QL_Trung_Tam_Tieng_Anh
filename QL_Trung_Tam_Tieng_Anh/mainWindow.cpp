#include<iostream>
#include<string.h>
using namespace std;
#define MaxBh 50

/* CÁC CẤU TRÚC SỬ DỤNG */
// Thông Tin Cá Nhân
struct ThongTinCaNhan;
// Giảng Viên
struct GiangVien;
// Học Viên
struct HocVien;
// Khóa Học
struct KhoaHoc;
// Buổi Học
struct BuoiHoc;
// Học Viên Của Khóa Học
struct HocVien_KH;
// Khóa Học Của Học Viên
struct KhoaHoc_HV;

/* Các Nút */
// Nút Giảng Viên
typedef GiangVien* N_GiangVien;
// Nút Học Viên
typedef HocVien* N_HocVien;
// Nút Khóa Học
typedef KhoaHoc* N_KhoaHoc;
// Nút Buổi Học
typedef BuoiHoc* N_BuoiHoc;
// Nút Học Viên Của Khóa Học;
typedef HocVien_KH* N_HocVien_KH;
// Nút Khóa Học Của Học Viên;
typedef KhoaHoc_HV* N_KhoaHoc_HV;

/* Các Danh Sách Sử Dụng */
// Danh Sách Giảng Viên
typedef N_GiangVien DS_GiangVien;
// Danh Sách Học Viên
typedef N_HocVien DS_HocVien;
// Danh Sách Khóa Học
typedef N_KhoaHoc DS_KhoaHoc;
// Danh Sách Buổi Học
typedef N_BuoiHoc DS_BuoiHoc;
// Danh Sách Học Viên Của Khóa Học
typedef N_HocVien_KH DS_HocVien_KH;
// Danh Sách Khóa Học Của Học Viên
typedef N_KhoaHoc_HV DS_KhoaHoc_HV;

struct ThongTinCaNhan {
    short ma_so;
    string ten;
    short tuoi;
    string cccd;
    string sdt;
    string nghe_nghiep;
    string trinh_do;
};

struct GiangVien {
    ThongTinCaNhan tt_gv;
    int luong;

    GiangVien* Next;
};

struct HocVien {
    ThongTinCaNhan tt_hv;
    DS_KhoaHoc_HV Ds_kh_hv;

    HocVien* Next;
};

struct KhoaHoc {
    short ma_so;
    string ten;
    int gia_tien;
    short so_buoi;
    short muc_tieu;
    bool trang_thai;
    string gioi_thieu;
    N_GiangVien Gv_kh;
    DS_BuoiHoc Ds_bh;
    DS_HocVien_KH Ds_hv_kh;

    KhoaHoc* Next;
};

struct BuoiHoc {
    short kip;
    short ngay, thang, nam;
    short buoi_so;
    short phong_hoc;
    bool trang_thai;

    BuoiHoc* Next;
};

struct HocVien_KH {
    short ma_so;
    bool diem_danh[MaxBh];
    HocVien_KH* Next;
};

struct KhoaHoc_HV {
    short ma_so;
    short ket_qua;
    KhoaHoc_HV* Next;
};


/* Cac Ham Cua Buoi Hoc*/

// Kiểm Tra Năm Nhuận
bool NamNhuan(short Nam) {
    return (Nam % 4 == 0 && Nam % 100 != 0) || (Nam % 400 == 0);
}
// Số Ngày Trong Thang
short SoNgay(short Thang, short Nam) {
    switch (Thang) {
    case 1: case 3: case 5: case 7: case 8: case 10: case 12:
        return 31;
    case 4: case 6: case 9: case 11:
        return 30;
    case 2:
        return NamNhuan(Nam) ? 29 : 28;
    default: return 0;
    }
}
// Tính Thứ Trong Tuần
short TinhThu(short Ngay, short Thang, short Nam) {
    // Cong Thuc Zeller Congruence
    if (Thang < 3) {
        Thang += 12;
        Nam -= 1;
    }
    short thu = (Ngay + (13 * (Thang + 1)) / 5 + (Nam % 100) + (Nam % 100) / 4 + (Nam / 100) / 4 + 5 * (Nam / 100)) % 7;
    return thu / 7;
}
// Khởi Tạo Danh Sách Buổi Học
void initBH(DS_BuoiHoc& DSBH) {
    DSBH = NULL;
}
// Thêm Nút Buổi Học Vào Danh Sách
bool insertBH(DS_BuoiHoc& DSBH, short Kip, short Ngay, short Thang, short Nam, short Buoi_so, short Phong_hoc) {
    // Tạo Ra Một Buổi Học
    N_BuoiHoc newBh = new BuoiHoc;
    newBh->kip = Kip;
    newBh->ngay = Ngay;
    newBh->thang = Thang;
    newBh->nam = Nam;
    newBh->buoi_so = Buoi_so;
    newBh->trang_thai = 0;
    newBh->phong_hoc = Phong_hoc;
    newBh->Next = NULL;
    // Thêm Buổi Học Vào Danh Sách
    if (DSBH == NULL) {
        DSBH = newBh;
    }
    else {
        N_BuoiHoc P = DSBH;
        while (P->Next != NULL) P = P->Next;
        P->Next = newBh;
    }
    return true;
}
// Tạo Danh Sách Buổi Học Tự Động
void TaoDanhSachBuoiHoc(DS_BuoiHoc& DSBH, short So_buoi, short Tan_suat) { // Tan Suat Nho Nhat La 7
    N_BuoiHoc P = DSBH;
    N_BuoiHoc R = DSBH;
    while (R->Next != NULL) R = R->Next;
    for (int i = Tan_suat + 1; i < So_buoi; i++) {
        // Tạo Ra Một Buổi Học
        N_BuoiHoc newBh = new BuoiHoc;
        newBh->buoi_so = i;
        newBh->kip = P->kip;
        newBh->phong_hoc = P->phong_hoc;
        newBh->trang_thai = 0;
        newBh->Next = NULL;
        // Tạo lịch học
        short So_ngay = SoNgay(R->thang, R->nam);
        if (R->ngay + Tan_suat <= So_ngay) {
            newBh->ngay = R->ngay + Tan_suat;
            newBh->thang = R->thang;
            newBh->nam = R->nam;
        }
        else {
            newBh->ngay = R->ngay + Tan_suat - So_ngay;
            newBh->thang = R->thang + 1;
            if (newBh->thang > 12) {
                newBh->thang = 1;
                newBh->nam = R->nam + 1;
            }
            else newBh->nam = R->nam;
        }
        R->Next = newBh;
        R = R->Next;
        P = P->Next;
    }
}

/* Các Hàm Của Thông Tin Cá Nhân */

// Khởi Tạo Thông Tin Cá Nhân Mới
ThongTinCaNhan InitTTCN(int Ma_so, string Ten, int Tuoi, int Cccd, string Sdt, string trinh_do) {
    ThongTinCaNhan tt_cn;
    tt_cn.ma_so = Ma_so;
    tt_cn.ten = Ten;
    tt_cn.tuoi = Tuoi;
    tt_cn.cccd = Cccd;
    tt_cn.sdt = Sdt;
    tt_cn.trinh_do = trinh_do;
    tt_cn.nghe_nghiep = "";
    return tt_cn;
}

/* Các Hàm Của Giảng Viên */

// Khởi Tạo Danh Sách Giảng Viên
void initGV(DS_GiangVien& DSGV) {
    DSGV = NULL;
}
// Thêm Giảng Viên Vào Đầu Danh Sách
void insertGV(DS_GiangVien& DSGV, ThongTinCaNhan Tt_gv, int Luong) {
    // Tạo Ra Nút Giảng Viên Mới
    N_GiangVien newGv = new GiangVien;
    newGv->tt_gv = Tt_gv;
    newGv->tt_gv.nghe_nghiep = "Giang Vien Toiec";
    newGv->luong = Luong;
    newGv->Next = NULL;
    // Thêm Nút Vào Danh Sách
    newGv->Next = DSGV;
    DSGV = newGv;
}
// Tìm Kiếm Giảng Viên
N_GiangVien findGVbyMaSo(DS_GiangVien& DSGV, int MaSo) {
    if (DSGV == NULL) return NULL;
    N_GiangVien P = DSGV;
    while (P != NULL) {
        if (MaSo != P->tt_gv.ma_so) {
            P = P->Next;
        }
        else break;
    }
    return P;
}
// Xóa 1 Giảng Viên
bool deleteGV(DS_GiangVien& DSGV, N_GiangVien Gv) {
    if (DSGV == NULL || Gv == NULL) return false;
    if (DSGV == Gv && Gv->Next == NULL) {
        DSGV = NULL;
        delete Gv;
        return true;
    }

    if (DSGV == Gv) {
        DSGV = Gv->Next;
        delete Gv;
        return true;
    }

    N_GiangVien P = DSGV;
    while (P->Next != NULL && P->Next != Gv) {
        P = P->Next;
    }
    if (P->Next == Gv) {
        P->Next = Gv->Next;
        delete Gv;
        return true;
    }
    return false;
}
// Xóa Danh Sách Khóa Học
void deleteDSDSGV(DS_GiangVien& DSGV) {
    while (DSGV != NULL) {
        N_GiangVien P = DSGV;
        DSGV = P->Next;
        delete P;
    }
}
// Tính Số Lượng Giảng Viên
short SoLuongGV(DS_GiangVien DSGV) {
    if (DSGV == NULL) return 0;
    return 1 + SoLuongGV(DSGV->Next);
}
// Thay Đổi Thông Tin Giảng Viên
// Tính Lương
int TinhLuongGV(N_GiangVien Gv, DS_KhoaHoc DSKH, short Thang, short Nam) {
    N_KhoaHoc P = DSKH;
    int so_buoi_day = 0;
    while (P != NULL) {
        if (Gv->tt_gv.ma_so == DSKH->Gv_kh->tt_gv.ma_so && DSKH->trang_thai == 1) {
            N_BuoiHoc R = new BuoiHoc;
            while (R != NULL) {
                if (R->nam == Nam && R->thang == Thang) {
                    if (R->trang_thai == 1) so_buoi_day++;
                }
                R = R->Next;
            }
        }
        P = P->Next;
    }
    return Gv->luong * so_buoi_day;
}

/* Các Hàm Của Học Viên */

// Khởi Tạo Danh Sách Học Viên
void initHocVien(DS_HocVien& DSHV) {
    DSHV = NULL;
}
// Thêm Học Viên Vào Danh Sách
void insertHV(DS_HocVien& DSHV, ThongTinCaNhan Tt_hv) {
    // Tạo Ra Nút Học Viên Mới
    N_HocVien newHv = new HocVien;
    newHv->tt_hv = Tt_hv;
    newHv->Ds_kh_hv = NULL;
    newHv->Next = NULL;
    // Thêm Nút Vào Danh SáchSách
    newHv->Next = DSHV;
    DSHV = newHv;
}
// Tìm Kiếm Học Viên
N_HocVien findHVbyMaSo(DS_HocVien& DSHV, int MaSo) {
    if (DSHV == NULL) return NULL;
    N_HocVien P = DSHV;
    while (P != NULL) {
        if (MaSo != P->tt_hv.ma_so) {
            P = P->Next;
        }
        else break;
    }
    return P;
}
// Xóa 1 Học Viên
bool deleteHV(DS_HocVien& DSHV, N_HocVien Hv) {
    if (DSHV == NULL || Hv == NULL) return false;
    if (DSHV == Hv && Hv->Next == NULL) {
        DSHV = NULL;
        delete Hv;
        return true;
    }

    if (DSHV == Hv) {
        DSHV = Hv->Next;
        delete Hv;
        return true;
    }

    N_HocVien P = DSHV;
    while (P->Next != NULL && P->Next != Hv) {
        P = P->Next;
    }
    if (P->Next == Hv) {
        P->Next = Hv->Next;
        delete Hv;
        return true;
    }
    return false;
}
// Tính Toán Số Lượng Học Viên
int SoLuongHV(DS_HocVien DSHV) {
    if (DSHV == NULL) return 0;
    return 1 + SoLuongHV(DSHV->Next);
}
// Thay Đổi Thông Tin Học Viên
// Thêm Khóa Học Vào Danh Sách Khóa Học Của Học Viên
void insertKHtoHV(DS_KhoaHoc_HV& DSKHHV, int Ma_so) {
    N_KhoaHoc_HV newKhHv = new KhoaHoc_HV;
    newKhHv->ma_so = Ma_so;
    newKhHv->ket_qua = 0;
    newKhHv->Next = NULL;

    newKhHv->Next = DSKHHV;
    DSKHHV = newKhHv;
}
// Xóa Khóa Học Của Học Viên
bool deleteKhHv(DS_KhoaHoc_HV& DSKHHV, N_KhoaHoc_HV& HvKh) {
    if (DSKHHV == NULL || HvKh == NULL) return false;
    if (DSKHHV == HvKh && HvKh->Next == NULL) {
        DSKHHV = NULL;
        delete HvKh;
        return true;
    }

    if (DSKHHV == HvKh) {
        DSKHHV = HvKh->Next;
        delete HvKh;
        return true;
    }

    N_KhoaHoc_HV P = DSKHHV;
    while (P->Next != NULL && P->Next != HvKh) {
        P = P->Next;
    }
    if (P->Next == HvKh) {
        P->Next = HvKh->Next;
        delete HvKh;
        return true;
    }
    return false;
}

/* Các Hàm Của Khóa Học */

// Khởi Tạo Danh Sách Khóa Học
void initKhoaHoc(DS_KhoaHoc& DSKH) {
    DSKH = NULL;
}
// Thêm Một Khóa Học Vào Danh Sách
void insertKh(DS_KhoaHoc& DSKH, short Ma_so, string Ten, int Gia_tien, short So_buoi, short Muc_tieu, string Gioi_thieu, N_GiangVien Gvkh, DS_BuoiHoc Dsbh, DS_HocVien_KH Dshvkh) {
    // Tạo Nút Khóa Học Mới
    N_KhoaHoc newKh = new KhoaHoc;
    newKh->ma_so = Ma_so;
    newKh->ten = Ten;
    newKh->gia_tien = Gia_tien;
    newKh->so_buoi = So_buoi;
    newKh->muc_tieu = Muc_tieu;
    newKh->trang_thai = 0;
    newKh->gioi_thieu = Gioi_thieu;
    newKh->Gv_kh = Gvkh;
    newKh->Ds_bh = Dsbh;
    newKh->Ds_hv_kh = Dshvkh;
    newKh->Next = NULL;

    // Thêm Nút Vào Danh Sách
    newKh->Next = DSKH;
    DSKH = newKh;
}
// Tìm Kiếm Khóa Học
N_KhoaHoc findKHbyMaSo(DS_KhoaHoc& DSKH, short Ma_so) {
    if (DSKH == NULL) return NULL;
    N_KhoaHoc P = DSKH;
    while (P != NULL) {
        if (Ma_so != P->ma_so) {
            P = P->Next;
        }
        else break;
    }
    return P;
}
// Xóa Khóa Học
bool deleteKh(DS_KhoaHoc& DSKH, N_KhoaHoc Kh) {
    if (DSKH == NULL || Kh == NULL) return false;
    if (DSKH == Kh && Kh->Next == NULL) {
        DSKH = NULL;
        delete Kh;
        return true;
    }

    if (DSKH == Kh) {
        DSKH = Kh->Next;
        delete Kh;
        return true;
    }

    N_KhoaHoc P = DSKH;
    while (P->Next != NULL && P->Next != Kh) {
        P = P->Next;
    }
    if (P->Next == Kh) {
        P->Next = Kh->Next;
        delete Kh;
        return true;
    }
    return false;
}
// Thay Đổi Thông Tin Khóa Học
// Thêm Giảng Viên Cho Khóa học
void insertGVtoKH(N_KhoaHoc& Kh, N_GiangVien& Gv) {
    Kh->Gv_kh = Gv;
}
// Thêm Học Viên Vào Danh Sách Khóa Học
void insertHVtoKH(N_KhoaHoc& Kh, int Ma_so) {
    N_HocVien_KH newHvKh = new HocVien_KH;
    newHvKh->ma_so = Ma_so;
    for (int i = 0; i < Kh->so_buoi; i++) {
        newHvKh->diem_danh[i] = true;
    }
    newHvKh->Next = NULL;
    //Thêm nút vào danh sách
    newHvKh->Next = Kh->Ds_hv_kh;
    Kh->Ds_hv_kh = newHvKh;
}
// Xóa Học Viên Khỏi Khóa Học
bool deleteHvKh(DS_HocVien_KH& DS_Hv_Kh, N_HocVien_KH HvKh) {
    if (DS_Hv_Kh == NULL || HvKh == NULL) return false;
    if (DS_Hv_Kh == NULL && HvKh->Next == NULL) {
        DS_Hv_Kh = NULL;
        delete HvKh;
        return true;
    }

    if (DS_Hv_Kh == HvKh) {
        DS_Hv_Kh = HvKh->Next;
        delete HvKh;
        return true;
    }

    N_HocVien_KH P = DS_Hv_Kh;
    while (P->Next != NULL && P->Next != HvKh) {
        P = P->Next;
    }
    if (P->Next == HvKh) {
        P->Next = HvKh->Next;
        delete HvKh;
        return true;
    }
    return false;
}
//ham hien thi trung tamtam
void HienThiTrungTam() {
    cout << "\n========== TRUNG TÂM TIẾNG ANH TOEIC ==========\n";
    cout << "DANH SÁCH PHÒNG HỌC:\n";
    cout << "- Tầng 2: 201 202 203 204\n";
    cout << "- Tầng 3: 301 302 303 304\n";
    cout << "- Tầng 4: 401 402 403 404\n\n";
    cout << "DANH SÁCH KÍP HỌC:\n";
    cout << "- Kíp 1: 8h - 10h\n";
    cout << "- Kíp 2: 13h - 15h\n";
    cout << "- Kíp 3: 15h - 17h\n";
    cout << "- Kíp 4: 17h - 19h\n";
    cout << "- Kíp 5: 19h - 21h\n";
    cout << "==============================================\n";
    cout << "Nhấn phím bất kỳ để quay lại menu chính...\n";
    cin.ignore();
    cin.get();
}
void MenuHocVien(DS_HocVien& DSHV);
//cau truc menu chinh
void MenuChinh() {
    int choice;
    do {
        cout << "\n========== MENU CHÍNH ==========\n";
        cout << "1. Học viên\n";
        cout << "2. Giảng viên\n";
        cout << "3. Khóa học\n";
        cout << "4. Thống kê\n";
        cout << "5. Hiển thị thông tin trung tâm\n";
        cout << "6. Thoát\n";
        cout << "Lựa chọn của bạn: ";
        cin >> choice;

        switch (choice) {
        case 1: MenuHocVien(); break;
        case 2: MenuGiangVien(); break;
        case 3: MenuKhoaHoc(); break;
        case 4: MenuThongKe(); break;
        case 5: HienThiTrungTam(); break;
        case 6: cout << "Thoát chương trình...\n"; break;
        default: cout << "Lựa chọn không hợp lệ!\n";
        }
    } while (choice != 6);
}
//cau truc menu hoc vien
void MenuHocVien(DS_HocVien& DSHV) {
    int choice;
    do {
        cout << "\n=== MENU HỌC VIÊN ===\n";
        cout << "1. Hiển thị danh sách học viên\n";
        cout << "2. Thêm học viên\n";
        cout << "3. Xóa học viên\n";
        cout << "4. Hiển thị thông tin học viên\n";
        cout << "5. Quay lại\n";
        cout << "Lựa chọn của bạn: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            N_HocVien P = DSHV;
            while (P != NULL) {
                cout << "Mã số: " << P->tt_hv.ma_so << ", Tên: " << P->tt_hv.ten << endl;
                P = P->Next;
            }
            break;
        }
        case 2: {
            ThongTinCaNhan tt;
            cout << "Nhập mã số: "; cin >> tt.ma_so;
            cin.ignore();
            cout << "Nhập tên: "; getline(cin, tt.ten);
            cout << "Nhập tuổi: "; cin >> tt.tuoi;
            cin.ignore();
            cout << "Nhập CCCD: "; getline(cin, tt.cccd);
            cout << "Nhập SĐT: "; getline(cin, tt.sdt);
            cout << "Nhập trình độ: "; getline(cin, tt.trinh_do);
            insertHV(DSHV, tt);
            break;
        }
        case 3: {
            int ma;
            cout << "Nhập mã số học viên cần xóa: "; cin >> ma;
            N_HocVien hv = findHVbyMaSo(DSHV, ma);
            if (deleteHV(DSHV, hv))
                cout << "Xóa học viên thành công!\n";
            else
                cout << "Không tìm thấy học viên!\n";
            break;
        }
        case 4: {
            int ma;
            cout << "Nhập mã số học viên cần tìm: "; cin >> ma;
            N_HocVien hv = findHVbyMaSo(DSHV, ma);
            if (hv != NULL)
                cout << "Mã số: " << hv->tt_hv.ma_so << ", Tên: " << hv->tt_hv.ten << endl;
            else
                cout << "Không tìm thấy học viên!\n";
            break;
        }
        case 5: return;
        default: cout << "Lựa chọn không hợp lệ!\n";
        }
    } while (choice != 5);
}
//cau truc menu giang vien
void MenuGiangVien(DS_GiangVien& DSGV) {
    int choice;
    do {
        cout << "\n=== MENU GIẢNG VIÊN ===\n";
        cout << "1. Hiển thị danh sách giảng viên\n";
        cout << "2. Thêm giảng viên\n";
        cout << "3. Xóa giảng viên\n";
        cout << "4. Hiển thị thông tin giảng viên\n";
        cout << "5. Quay lại\n";
        cout << "Lựa chọn của bạn: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            N_GiangVien P = DSGV;
            while (P != NULL) {
                cout << "Mã số: " << P->tt_gv.ma_so << ", Tên: " << P->tt_gv.ten << endl;
                P = P->Next;
            }
            break;
        }
        case 2: {
            ThongTinCaNhan tt;
            int luong;
            cout << "Nhập mã số: "; cin >> tt.ma_so;
            cin.ignore();
            cout << "Nhập tên: "; getline(cin, tt.ten);
            cout << "Nhập tuổi: "; cin >> tt.tuoi;
            cin.ignore();
            cout << "Nhập CCCD: "; getline(cin, tt.cccd);
            cout << "Nhập SĐT: "; getline(cin, tt.sdt);
            cout << "Nhập lương: "; cin >> luong;
            insertGV(DSGV, tt, luong);
            break;
        }
        case 3: {
            int ma;
            cout << "Nhập mã số giảng viên cần xóa: "; cin >> ma;
            N_GiangVien gv = findGVbyMaSo(DSGV, ma);
            if (deleteGV(DSGV, gv))
                cout << "Xóa giảng viên thành công!\n";
            else
                cout << "Không tìm thấy giảng viên!\n";
            break;
        }
        case 4: {
            int ma;
            cout << "Nhập mã số giảng viên cần tìm: "; cin >> ma;
            N_GiangVien gv = findGVbyMaSo(DSGV, ma);
            if (gv != NULL)
                cout << "Mã số: " << gv->tt_gv.ma_so << ", Tên: " << gv->tt_gv.ten << endl;
            else
                cout << "Không tìm thấy giảng viên!\n";
            break;
        }
        case 5: return;
        default: cout << "Lựa chọn không hợp lệ!\n";
        }
    } while (choice != 5);
}
//cau truc menu khoa hoc
void MenuKhoaHoc(DS_KhoaHoc& DSKH, DS_GiangVien& DSGV) {
    int choice;
    do {
        cout << "\n=== MENU KHÓA HỌC ===\n";
        cout << "1. Hiển thị danh sách khóa học\n";
        cout << "2. Thêm khóa học\n";
        cout << "3. Xóa khóa học\n";
        cout << "4. Tìm kiếm khóa học\n";
        cout << "5. Quay lại\n";
        cout << "Lựa chọn của bạn: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            N_KhoaHoc P = DSKH;
            while (P != NULL) {
                cout << "Mã khóa học: " << P->ma_so << ", Tên: " << P->ten << endl;
                P = P->Next;
            }
            break;
        }
        case 2: {
            short ma_so, so_buoi, muc_tieu;
            string ten, gioi_thieu;
            int gia_tien;
            short ma_gv; // Mã số giảng viên
            N_GiangVien gv = NULL;

            cout << "Nhập mã số khóa học: ";
            cin >> ma_so;
            cin.ignore();

            cout << "Nhập tên khóa học: ";
            getline(cin, ten);

            cout << "Nhập giá tiền: ";
            cin >> gia_tien;

            cout << "Nhập số buổi học: ";
            cin >> so_buoi;

            cout << "Nhập mục tiêu: ";
            cin >> muc_tieu;
            cin.ignore();

            cout << "Nhập giới thiệu khóa học: ";
            getline(cin, gioi_thieu);

            // Tìm giảng viên theo mã số
            cout << "Nhập mã số giảng viên phụ trách: ";
            cin >> ma_gv;
            gv = findGVbyMaSo(DSGV, ma_gv);
            if (gv == NULL) {
                cout << "Không tìm thấy giảng viên có mã số này! Khóa học sẽ không có giảng viên phụ trách.\n";
            }

            // Khởi tạo danh sách buổi học và học viên khóa học
            DS_BuoiHoc dsbh;
            DS_HocVien_KH dshvkh;
            initBH(dsbh); // Khởi tạo danh sách buổi học trống
            dshvkh = NULL; // Danh sách học viên trống

            // Thêm khóa học vào danh sách
            insertKh(DSKH, ma_so, ten, gia_tien, so_buoi, muc_tieu, gioi_thieu, gv, dsbh, dshvkh);
            cout << "Thêm khóa học thành công!\n";
        }
        case 3: {
            short ma;
            cout << "Nhập mã khóa học cần xóa: "; cin >> ma;
            N_KhoaHoc kh = findKHbyMaSo(DSKH, ma);
            if (deleteKh(DSKH, kh))
                cout << "Xóa khóa học thành công!\n";
            else
                cout << "Không tìm thấy khóa học!\n";
            break;
        }
        case 4: {
            short ma;
            cout << "Nhập mã khóa học cần tìm: "; cin >> ma;
            N_KhoaHoc kh = findKHbyMaSo(DSKH, ma);
            if (kh != NULL)
                cout << "Tên khóa học: " << kh->ten << endl;
            else
                cout << "Không tìm thấy khóa học!\n";
            break;
        }
        case 5: return;
        default: cout << "Lựa chọn không hợp lệ!\n";
        }
    } while (choice != 5);
}
//cau truc menu thong ke
void MenuThongKe(DS_HocVien DSHV, DS_GiangVien DSGV, DS_KhoaHoc DSKH) {
    int choice;
    do {
        cout << "\n=== MENU THỐNG KÊ ===\n";
        cout << "1. Hiển thị tổng quan\n";
        cout << "2. Hiển thị doanh thu hàng tháng\n";
        cout << "3. Quay lại\n";
        cout << "Lựa chọn của bạn: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            // Thống kê tổng quan
            int soHocVien = SoLuongHV(DSHV);
            int soGiangVien = SoLuongGV(DSGV);
            int soKhoaHoc = 0;
            N_KhoaHoc P = DSKH;
            while (P != NULL) {
                soKhoaHoc++;
                P = P->Next;
            }

            cout << "\n===== TỔNG QUAN =====\n";
            cout << "Tổng số học viên: " << soHocVien << endl;
            cout << "Tổng số giảng viên: " << soGiangVien << endl;
            cout << "Tổng số khóa học: " << soKhoaHoc << endl;
            cout << "======================\n";
            break;
        }
        case 2: {
            // Thống kê doanh thu
            int doanhThu = 0;
            N_KhoaHoc P = DSKH;
            while (P != NULL) {
                if (P->trang_thai == true) { // Chỉ tính các khóa học đã hoàn thành
                    doanhThu += P->gia_tien * SoLuongHV(P->Ds_hv_kh);
                }
                P = P->Next;
            }

            cout << "\n===== DOANH THU HÀNG THÁNG =====\n";
            cout << "Tổng doanh thu từ các khóa học hoàn thành: " << doanhThu << " VND\n";
            cout << "=================================\n";
            break;
        }
        case 3: return;
        default:
            cout << "Lựa chọn không hợp lệ!\n";
        }
    } while (choice != 3);
}
/* Giải phóng bộ nhớ an toàn */
void GiaiPhongBoNho(DS_HocVien& DSHV, DS_GiangVien& DSGV, DS_KhoaHoc& DSKH) {
    deleteDSDSGV(DSGV);
    while (DSHV != NULL) {
        N_HocVien temp = DSHV;
        DSHV = DSHV->Next;
        delete temp;
    }
    while (DSKH != NULL) {
        N_KhoaHoc temp = DSKH;
        DSKH = DSKH->Next;
        delete temp;
    }
}
// Ham Main
int main() {
    DS_HocVien DSHV;
    DS_GiangVien DSGV;
    DS_KhoaHoc DSKH;

    initHocVien(DSHV);
    initGV(DSGV);
    initKhoaHoc(DSKH);

    MenuChinh();
    // Giải phóng bộ nhớ trước khi kết thúc chương trình
    GiaiPhongBoNho(DSHV, DSGV, DSKH);
    return 0;
}
