#include <iostream>
#include <string>

using namespace std;

// ==========================================
// 1. ĐỊNH NGHĨA ĐỐI TƯỢNG VÉ XEM PHIM
// ==========================================
class VeXemPhim {
private:
    string tenPhim;
    int soGhe;
    double giaVe;
public:
    // Constructor mặc định (Bắt buộc phải có để khởi tạo mảng trong Pilha)
    VeXemPhim() {
        tenPhim = "";
        soGhe = 0;
        giaVe = 0.0;
    }

    VeXemPhim(string phim, int ghe, double gia) {
        tenPhim = phim;
        soGhe = ghe;
        giaVe = gia;
    }

    void hienThiThongTin() {
        cout << "Phim: " << tenPhim << " | Ghe so: " << soGhe << " | Gia: " << giaVe << " VND" << endl;
    }
};

// ==========================================
// 2. CLASS PILHA (Giữ nguyên cấu trúc của bạn)
// ==========================================
template <typename Tipo>
class Pilha {
private:
    Tipo* v;
    unsigned tamanho;
    int topo;
public:
    Pilha(unsigned tam) {
        tamanho = tam;
        v = new Tipo[tamanho];
        topo = -1;
    }

    ~Pilha() {
        delete[] v;
    }

    void empilhaContainer(Tipo x) {
        if (!pilhacheia()) {
            topo++;
            v[topo] = x;
        }
        else {
            cout << "Loi: Danh sach da day!" << endl;
        }
    }

    Tipo desempilha() {
        Tipo temp = v[topo];
        topo--;
        return temp;
    }

    Tipo elementodotopo() {
        return v[topo];
    }

    bool pilhacheia() {
        return topo == (int)tamanho - 1;
    }

    bool pilhavazia() {
        return topo == -1;
    }

    int getTopo() { // Sửa lại thành int vì topo khởi tạo là -1
        return topo;
    }

    unsigned getTamanho() {
        return tamanho;
    }

    Tipo getValor(unsigned posicao) {
        return v[posicao];
    }
};

// ==========================================
// 3. CHƯƠNG TRÌNH CHÍNH (QUẢN LÝ RẠP CHIẾU PHIM)
// ==========================================
int main() {
    // Khởi tạo một ngăn xếp quản lý tối đa 5 vé được bán ra
    Pilha<VeXemPhim> heThongVe(5);
    int luaChon;

    do {
        cout << "\n--- HE THONG QUAN LY RAP CHIEU PHIM ---" << endl;
        cout << "1. Ban ve moi (Empilha)" << endl;
        cout << "2. Hoan ve vua ban gan nhat (Desempilha - Undo)" << endl;
        cout << "3. Xem ve vua ban gan nhat (Elementodotopo)" << endl;
        cout << "4. Xem toan bo danh sach ve da ban" << endl;
        cout << "0. Thoat" << endl;
        cout << "Nhap lua chon cua ban: ";
        cin >> luaChon;

        switch (luaChon) {
        case 1: {
            if (heThongVe.pilhacheia()) {
                cout << "==> He thong het cho chua ve (Ghe da day)!" << endl;
            }
            else {
                string tenPhim;
                int soGhe;
                double giaVe;

                cin.ignore(); // Xóa bộ nhớ đệm
                cout << "Nhap ten phim: ";
                getline(cin, tenPhim);
                cout << "Nhap so ghe: ";
                cin >> soGhe;
                cout << "Nhap gia ve: ";
                cin >> giaVe;

                VeXemPhim veMoi(tenPhim, soGhe, giaVe);
                heThongVe.empilhaContainer(veMoi);
                cout << "==> Da ban ve thanh cong!" << endl;
            }
            break;
        }
        case 2: {
            if (heThongVe.pilhavazia()) {
                cout << "==> Chua co ve nao duoc ban de hoan!" << endl;
            }
            else {
                // Lấy vé ở đỉnh ngăn xếp ra (vé bán muộn nhất)
                VeXemPhim veHoan = heThongVe.desempilha();
                cout << "==> Da hoan thanh cong ve vua ban:" << endl;
                veHoan.hienThiThongTin();
            }
            break;
        }
        case 3: {
            if (heThongVe.pilhavazia()) {
                cout << "==> Chua co ve nao duoc ban!" << endl;
            }
            else {
                cout << "==> Ve vua ban gan nhat la:" << endl;
                heThongVe.elementodotopo().hienThiThongTin();
            }
            break;
        }
        case 4: {
            if (heThongVe.pilhavazia()) {
                cout << "==> Danh sach trong!" << endl;
            }
            else {
                cout << "=== DANH SACH VE DA BAN (Tu cu nhat den moi nhat) ===" << endl;
                for (int i = 0; i <= heThongVe.getTopo(); i++) {
                    cout << "[" << i << "] ";
                    heThongVe.getValor(i).hienThiThongTin();
                }
            }
            break;
        }
        case 0:
            cout << "Tam biet!" << endl;
            break;
        default:
            cout << "Lua chon khong hop le!" << endl;
        }
    } while (luaChon != 0);

    return 0;
}
