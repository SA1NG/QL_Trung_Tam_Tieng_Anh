#include<iostream>
#include<string.h>
#include<string>
using namespace std;
#define MaxBh 50

/* CÁC C?U TRÚC S? D?NG */
// Thông Tin Cá Nhân
struct ThongTinCaNhan;
// Gi?ng Viên
struct GiangVien;
// H?c Viên
struct HocVien;
// Khóa H?c
struct KhoaHoc;
// Bu?i H?c
struct BuoiHoc;
// H?c Viên C?a Khóa H?c
struct HocVien_KH;
// Khóa H?c C?a H?c Viên
struct KhoaHoc_HV;

/* Các Nút */
// Nút Gi?ng Viên
typedef GiangVien* N_GiangVien;
// Nút H?c Viên
typedef HocVien* N_HocVien;
// Nút Khóa H?c
typedef KhoaHoc* N_KhoaHoc;
// Nút Bu?i H?c
typedef BuoiHoc* N_BuoiHoc;
// Nút H?c Viên C?a Khóa H?c;
typedef HocVien_KH* N_HocVien_KH;
// Nút Khóa H?c C?a H?c Viên;
typedef KhoaHoc_HV* N_KhoaHoc_HV;

/* Các Danh Sách S? D?ng */
// Danh Sách Gi?ng Viên
typedef N_GiangVien DS_GiangVien;
// Danh Sách H?c Viên
typedef N_HocVien DS_HocVien;
// Danh Sách Khóa H?c
typedef N_KhoaHoc DS_KhoaHoc;
// Danh Sách Bu?i H?c
typedef N_BuoiHoc DS_BuoiHoc;
// Danh Sách H?c Viên C?a Khóa H?c
typedef N_HocVien_KH DS_HocVien_KH;
// Danh Sách Khóa H?c C?a H?c Viên
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

// Ki?m Tra N?m Nhu?n
bool NamNhuan(short Nam) {
    return (Nam % 4 == 0 && Nam % 100 != 0) || (Nam % 400 == 0);
}
// S? Ngày Trong Thang
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
// Tính Th? Trong Tu?n
short TinhThu(short Ngay, short Thang, short Nam) {
    // Cong Thuc Zeller Congruence
    if (Thang < 3) {
        Thang += 12;
        Nam -= 1;
    }
    short thu = (Ngay + (13 * (Thang + 1)) / 5 + (Nam % 100) + (Nam % 100) / 4 + (Nam / 100) / 4 + 5 * (Nam / 100)) % 7;
    return thu / 7;
}
// Kh?i T?o Danh Sách Bu?i H?c
void initBH(DS_BuoiHoc& DSBH) {
    DSBH = NULL;
}
// Thêm Nút Bu?i H?c Vào Danh Sách
bool insertBH(DS_BuoiHoc& DSBH, short Kip, short Ngay, short Thang, short Nam, short Buoi_so, short Phong_hoc) {
    // T?o Ra M?t Bu?i H?c
    N_BuoiHoc newBh = new BuoiHoc;
    newBh->kip = Kip;
    newBh->ngay = Ngay;
    newBh->thang = Thang;
    newBh->nam = Nam;
    newBh->buoi_so = Buoi_so;
    newBh->trang_thai = 0;
    newBh->phong_hoc = Phong_hoc;
    newBh->Next = NULL;
    // Thêm Bu?i H?c Vào Danh Sách
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
// T?o Danh Sách Bu?i H?c T? ??ng
void TaoDanhSachBuoiHoc(DS_BuoiHoc& DSBH, short So_buoi, short Tan_suat) { // Tan Suat Nho Nhat La 7
    N_BuoiHoc P = DSBH;
    N_BuoiHoc R = DSBH;
    while (R->Next != NULL) R = R->Next;
    for (int i = Tan_suat + 1; i < So_buoi; i++) {
        // T?o Ra M?t Bu?i H?c
        N_BuoiHoc newBh = new BuoiHoc;
        newBh->buoi_so = i;
        newBh->kip = P->kip;
        newBh->phong_hoc = P->phong_hoc;
        newBh->trang_thai = 0;
        newBh->Next = NULL;
        // T?o l?ch h?c
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

/* Các Hàm C?a Thông Tin Cá Nhân */

// Kh?i T?o Thông Tin Cá Nhân M?i
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

/* Các Hàm C?a Gi?ng Viên */

// Kh?i T?o Danh Sách Gi?ng Viên
void initGV(DS_GiangVien& DSGV) {
    DSGV = NULL;
}
// Thêm Gi?ng Viên Vào ??u Danh Sách
void insertGV(DS_GiangVien& DSGV, ThongTinCaNhan Tt_gv, int Luong) {
    // T?o Ra Nút Gi?ng Viên M?i
    N_GiangVien newGv = new GiangVien;
    newGv->tt_gv = Tt_gv;
    newGv->tt_gv.nghe_nghiep = "Giang Vien Toiec";
    newGv->luong = Luong;
    newGv->Next = NULL;
    // Thêm Nút Vào Danh Sách
    newGv->Next = DSGV;
    DSGV = newGv;
}
// Tìm Ki?m Gi?ng Viên
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
// Xóa 1 Gi?ng Viên
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
// Xóa Danh Sách Khóa H?c
void deleteDSDSGV(DS_GiangVien& DSGV) {
    while (DSGV != NULL) {
        N_GiangVien P = DSGV;
        DSGV = P->Next;
        delete P;
    }
}
// Tính S? L??ng Gi?ng Viên
short SoLuongGV(DS_GiangVien DSGV) {
    if (DSGV == NULL) return 0;
    return 1 + SoLuongGV(DSGV->Next);
}
// Thay ??i Thông Tin Gi?ng Viên
// Tính L??ng
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

/* Các Hàm C?a H?c Viên */

// Kh?i T?o Danh Sách H?c Viên
void initHocVien(DS_HocVien& DSHV) {
    DSHV = NULL;
}
// Thêm H?c Viên Vào Danh Sách
void insertHV(DS_HocVien& DSHV, ThongTinCaNhan Tt_hv) {
    // T?o Ra Nút H?c Viên M?i
    N_HocVien newHv = new HocVien;
    newHv->tt_hv = Tt_hv;
    newHv->Ds_kh_hv = NULL;
    newHv->Next = NULL;
    // Thêm Nút Vào Danh SáchSách
    newHv->Next = DSHV;
    DSHV = newHv;
}
// Tìm Ki?m H?c Viên
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
// Xóa 1 H?c Viên
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
// Tính Toán S? L??ng H?c Viên
int SoLuongHV(DS_HocVien DSHV) {
    if (DSHV == NULL) return 0;
    return 1 + SoLuongHV(DSHV->Next);
}
// Thay ??i Thông Tin H?c Viên
// Thêm Khóa H?c Vào Danh Sách Khóa H?c C?a H?c Viên
void insertKHtoHV(DS_KhoaHoc_HV& DSKHHV, int Ma_so) {
    N_KhoaHoc_HV newKhHv = new KhoaHoc_HV;
    newKhHv->ma_so = Ma_so;
    newKhHv->ket_qua = 0;
    newKhHv->Next = NULL;

    newKhHv->Next = DSKHHV;
    DSKHHV = newKhHv;
}
// Xóa Khóa H?c C?a H?c Viên
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

/* Các Hàm C?a Khóa H?c */

// Kh?i T?o Danh Sách Khóa H?c
void initKhoaHoc(DS_KhoaHoc& DSKH) {
    DSKH = NULL;
}
// Thêm M?t Khóa H?c Vào Danh Sách
void insertKh(DS_KhoaHoc& DSKH, short Ma_so, string Ten, int Gia_tien, short So_buoi, short Muc_tieu, string Gioi_thieu, N_GiangVien Gvkh, DS_BuoiHoc Dsbh, DS_HocVien_KH Dshvkh) {
    // T?o Nút Khóa H?c M?i
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
// Tìm Ki?m Khóa H?c
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
// Xóa Khóa H?c
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
// Thay ??i Thông Tin Khóa H?c
// Thêm Gi?ng Viên Cho Khóa h?c
void insertGVtoKH(N_KhoaHoc& Kh, N_GiangVien& Gv) {
    Kh->Gv_kh = Gv;
}
// Thêm H?c Viên Vào Danh Sách Khóa H?c
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
// Xóa H?c Viên Kh?i Khóa H?c
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
// Tính Toán S? L??ng H?c Viên Khóa 
int SoLuongHVKH(DS_HocVien_KH DSHV) {
    if (DSHV == NULL) return 0;
    return 1 + SoLuongHVKH(DSHV->Next);
}

//ham hien thi trung tam
void HienThiTrungTam() {
    cout << "\n========== TRUNG TÂM TI?NG ANH TOEIC ==========\n";
    cout << "DANH SÁCH PHÒNG H?C:\n";
    cout << "- T?ng 2: 201 202 203 204\n";
    cout << "- T?ng 3: 301 302 303 304\n";
    cout << "- T?ng 4: 401 402 403 404\n\n";
    cout << "DANH SÁCH KÍP H?C:\n";
    cout << "- Kíp 1: 8h - 10h\n";
    cout << "- Kíp 2: 13h - 15h\n";
    cout << "- Kíp 3: 15h - 17h\n";
    cout << "- Kíp 4: 17h - 19h\n";
    cout << "- Kíp 5: 19h - 21h\n";
    cout << "==============================================\n";
    cout << "Nh?n phím b?t k? ?? quay l?i menu chính...\n";
    cin.ignore();
    cin.get();
    system("cls");
}
void MenuHocVien(DS_HocVien& DSHV);
void MenuGiangVien(DS_GiangVien& DSGV);
void MenuKhoaHoc(DS_KhoaHoc& DSKH, DS_GiangVien& DSGV);
void MenuThongKe(DS_HocVien DSHV, DS_GiangVien DSGV, DS_KhoaHoc DSKH);

//cau truc menu chinh
void MenuChinh(DS_HocVien& DSHV, DS_GiangVien& DSGV, DS_KhoaHoc& DSKH) {
    int choice;
    do {
        cout << "\n========== MENU CHÍNH ==========\n";
        cout << "1. H?c viên\n";
        cout << "2. Gi?ng viên\n";
        cout << "3. Khóa h?c\n";
        cout << "4. Th?ng kê\n";
        cout << "5. Hi?n th? thông tin trung tâm\n";
        cout << "6. Thoát\n";
        cout << "L?a ch?n c?a b?n: ";
        cin >> choice;
        system("cls");

        switch (choice) {
        case 1: MenuHocVien(DSHV); break;
        case 2: MenuGiangVien(DSGV); break;
        case 3: MenuKhoaHoc(DSKH, DSGV); break;
        case 4: MenuThongKe(DSHV, DSGV, DSKH); break;
        case 5: HienThiTrungTam(); break;
        case 6: cout << "Thoát ch??ng trình...\n"; break;
        default: cout << "L?a ch?n không h?p l?!\n";
        }
    } while (choice != 6);
}



//cau truc menu hoc vien
void MenuHocVien(DS_HocVien& DSHV) {
    int choice;
    do {
        cout << "\n=== MENU H?C VIÊN ===\n";
        cout << "1. Hi?n th? danh sách h?c viên\n";
        cout << "2. Thêm h?c viên\n";
        cout << "3. Xóa h?c viên\n";
        cout << "4. Hi?n th? thông tin h?c viên\n";
        cout << "5. Quay l?i\n";
        cout << "L?a ch?n c?a b?n: ";
        cin >> choice;
        system("cls");

        switch (choice) {
        case 1: {
            N_HocVien P = DSHV;
            while (P != NULL) {
                cout << "Mã s?: " << P->tt_hv.ma_so << ", Tên: " << P->tt_hv.ten << endl;
                P = P->Next;
            }
            system("pause");
            system("cls");
            break;
        }
        case 2: {
            ThongTinCaNhan tt;
            cout << "Nh?p mã s?: "; cin >> tt.ma_so;
            cin.ignore();
            cout << "Nh?p tên: ";
            getline(cin, tt.ten);
            cout << "Nh?p tu?i: "; cin >> tt.tuoi;
            cin.ignore();
            cout << "Nh?p CCCD: ";
            getline(cin, tt.cccd);
            cout << "Nh?p S?T: ";
            getline(cin, tt.sdt);
            cout << "Nh?p trình ??: ";
            getline(cin, tt.trinh_do);
            insertHV(DSHV, tt);
            system("cls");
            break;

        }
        case 3: {
            int ma;
            cout << "Nh?p mã s? h?c viên c?n xóa: "; cin >> ma;
            N_HocVien hv = findHVbyMaSo(DSHV, ma);
            if (deleteHV(DSHV, hv))
                cout << "Xóa h?c viên thành công!\n";
            else
                cout << "Không tìm th?y h?c viên!\n";
            system("cls");
            break;
        }
        case 4: {
            int ma;
            cout << "Nh?p mã s? h?c viên c?n tìm: "; cin >> ma;
            N_HocVien hv = findHVbyMaSo(DSHV, ma);
            if (hv != NULL)
                cout << "Mã s?: " << hv->tt_hv.ma_so << ", Tên: " << hv->tt_hv.ten << endl;
            else
                cout << "Không tìm th?y h?c viên!\n";
            system("cls");
            break;
        }
        case 5: return;
            system("cls");
        default: cout << "L?a ch?n không h?p l?!\n";
            system("cls");
        }
    } while (choice != 5);
}
//cau truc menu giang vien
void MenuGiangVien(DS_GiangVien& DSGV) {
    int choice;
    do {
        cout << "\n=== MENU GI?NG VIÊN ===\n";
        cout << "1. Hi?n th? danh sách gi?ng viên\n";
        cout << "2. Thêm gi?ng viên\n";
        cout << "3. Xóa gi?ng viên\n";
        cout << "4. Hi?n th? thông tin gi?ng viên\n";
        cout << "5. Quay l?i\n";
        cout << "L?a ch?n c?a b?n: ";
        cin >> choice;
        system("cls");
        switch (choice) {
        case 1: {
            N_GiangVien P = DSGV;
            while (P != NULL) {
                cout << "Mã s?: " << P->tt_gv.ma_so << ", Tên: " << P->tt_gv.ten << endl;
                P = P->Next;
            }
            system("pause");
            system("cls");
            break;
        }
        case 2: {
            ThongTinCaNhan tt;
            int luong;
            cout << "Nh?p mã s?: "; cin >> tt.ma_so;
            cin.ignore();
            cout << "Nh?p tên: "; getline(cin, tt.ten);
            cout << "Nh?p tu?i: "; cin >> tt.tuoi;
            cin.ignore();
            cout << "Nh?p CCCD: "; getline(cin, tt.cccd);
            cout << "Nh?p S?T: "; getline(cin, tt.sdt);
            cout << "Nh?p l??ng: "; cin >> luong;
            insertGV(DSGV, tt, luong);
            system("cls");
            break;
        }
        case 3: {
            int ma;
            cout << "Nh?p mã s? gi?ng viên c?n xóa: "; cin >> ma;
            N_GiangVien gv = findGVbyMaSo(DSGV, ma);
            if (deleteGV(DSGV, gv))
                cout << "Xóa gi?ng viên thành công!\n";
            else
                cout << "Không tìm th?y gi?ng viên!\n";
            system("cls");
            break;
        }
        case 4: {
            int ma;
            cout << "Nh?p mã s? gi?ng viên c?n tìm: "; cin >> ma;
            N_GiangVien gv = findGVbyMaSo(DSGV, ma);
            if (gv != NULL)
                cout << "Mã s?: " << gv->tt_gv.ma_so << ", Tên: " << gv->tt_gv.ten << endl;
            else
                cout << "Không tìm th?y gi?ng viên!\n";
            system("cls");
            break;
        }
        case 5: return;
            system("cls");
        default: cout << "L?a ch?n không h?p l?!\n";
            system("cls");
        }
    } while (choice != 5);
}
//cau truc menu khoa hoc
void MenuKhoaHoc(DS_KhoaHoc& DSKH, DS_GiangVien& DSGV) {
    int choice;
    do {
        cout << "\n=== MENU KHÓA H?C ===\n";
        cout << "1. Hi?n th? danh sách khóa h?c\n";
        cout << "2. Thêm khóa h?c\n";
        cout << "3. Xóa khóa h?c\n";
        cout << "4. Tìm ki?m khóa h?c\n";
        cout << "5. Quay l?i\n";
        cout << "L?a ch?n c?a b?n: ";
        cin >> choice;
        system("cls");

        switch (choice) {
        case 1: {
            N_KhoaHoc P = DSKH;
            while (P != NULL) {
                cout << "Mã khóa h?c: " << P->ma_so << ", Tên: " << P->ten << endl;
                P = P->Next;
            }
            system("pause");
            system("cls");
            break;
        }
        case 2: {
            short ma_so, so_buoi, muc_tieu;
            string ten, gioi_thieu;
            int gia_tien;
            short ma_gv; // Mã s? gi?ng viên
            N_GiangVien gv = NULL;

            cout << "Nh?p mã s? khóa h?c: ";
            cin >> ma_so;
            cin.ignore();

            cout << "Nh?p tên khóa h?c: ";
            getline(cin, ten);

            cout << "Nh?p giá ti?n: ";
            cin >> gia_tien;

            cout << "Nh?p s? bu?i h?c: ";
            cin >> so_buoi;

            cout << "Nh?p m?c tiêu: ";
            cin >> muc_tieu;
            cin.ignore();

            cout << "Nh?p gi?i thi?u khóa h?c: ";
            getline(cin, gioi_thieu);

            // Tìm gi?ng viên theo mã s?
            cout << "Nh?p mã s? gi?ng viên ph? trách: ";
            cin >> ma_gv;
            gv = findGVbyMaSo(DSGV, ma_gv);
            if (gv == NULL) {
                cout << "Không tìm th?y gi?ng viên có mã s? này! Khóa h?c s? không có gi?ng viên ph? trách.\n";
            }

            // Kh?i t?o danh sách bu?i h?c và h?c viên khóa h?c
            DS_BuoiHoc dsbh;
            DS_HocVien_KH dshvkh;
            initBH(dsbh); // Kh?i t?o danh sách bu?i h?c tr?ng
            dshvkh = NULL; // Danh sách h?c viên tr?ng

            // Thêm khóa h?c vào danh sách
            insertKh(DSKH, ma_so, ten, gia_tien, so_buoi, muc_tieu, gioi_thieu, gv, dsbh, dshvkh);
            cout << "Thêm khóa h?c thành công!\n";
            system("cls");
        }
        case 3: {
            short ma;
            cout << "Nh?p mã khóa h?c c?n xóa: "; cin >> ma;
            N_KhoaHoc kh = findKHbyMaSo(DSKH, ma);
            if (deleteKh(DSKH, kh))
                cout << "Xóa khóa h?c thành công!\n";
            else
                cout << "Không tìm th?y khóa h?c!\n";
            system("cls");
            break;
        }
        case 4: {
            short ma;
            cout << "Nh?p mã khóa h?c c?n tìm: "; cin >> ma;
            N_KhoaHoc kh = findKHbyMaSo(DSKH, ma);
            if (kh != NULL)
                cout << "Tên khóa h?c: " << kh->ten << endl;
            else
                cout << "Không tìm th?y khóa h?c!\n";
            system("cls");
            break;
        }
        case 5: return;
            system("cls");
        default: cout << "L?a ch?n không h?p l?!\n";
            system("cls");
        }
    } while (choice != 5);
}
//cau truc menu thong ke
void MenuThongKe(DS_HocVien DSHV, DS_GiangVien DSGV, DS_KhoaHoc DSKH) {
    int choice;
    do {
        cout << "\n=== MENU TH?NG KÊ ===\n";
        cout << "1. Hi?n th? t?ng quan\n";
        cout << "2. Hi?n th? doanh thu hàng tháng\n";
        cout << "3. Quay l?i\n";
        cout << "L?a ch?n c?a b?n: ";
        cin >> choice;
        system("cls");

        switch (choice) {
        case 1: {
            // Th?ng kê t?ng quan
            int soHocVien = SoLuongHV(DSHV);
            int soGiangVien = SoLuongGV(DSGV);
            int soKhoaHoc = 0;
            N_KhoaHoc P = DSKH;
            while (P != NULL) {
                soKhoaHoc++;
                P = P->Next;
            }

            cout << "\n===== T?NG QUAN =====\n";
            cout << "T?ng s? h?c viên: " << soHocVien << endl;
            cout << "T?ng s? gi?ng viên: " << soGiangVien << endl;
            cout << "T?ng s? khóa h?c: " << soKhoaHoc << endl;
            cout << "======================\n";
            system("pause");
            system("cls");
            break;
        }
        case 2: {
            // Th?ng kê doanh thu
            int doanhThu = 0;
            N_KhoaHoc P = DSKH;
            while (P != NULL) {
                if (P->trang_thai == true) { // Ch? tính các khóa h?c ?ã hoàn thành
                    doanhThu += P->gia_tien * SoLuongHVKH(P->Ds_hv_kh);
                }
                P = P->Next;
            }

            cout << "\n===== DOANH THU HÀNG THÁNG =====\n";
            cout << "T?ng doanh thu t? các khóa h?c hoàn thành: " << doanhThu << " VND\n";
            cout << "=================================\n";
            system("pause");
            system("cls");
            break;
        }
        case 3: return;
            system("cls");
        default:
            cout << "L?a ch?n không h?p l?!\n";
            system("cls");
        }
    } while (choice != 3);
}
/* Gi?i phóng b? nh? an toàn */
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

    MenuChinh(DSHV, DSGV, DSKH);
    // Gi?i phóng b? nh? tr??c khi k?t thúc ch??ng trình
    GiaiPhongBoNho(DSHV, DSGV, DSKH);
    return 0;
}
