#include <iostream>
using namespace std;

// Mảng chi tiết 8 nước đi của quân mã
int row[] = {2, 1, -1, -2, -2, -1, 1, 2};
int col[] = {1, 2, 2, 1, -1, -2, -2, -1};

// Hàm kiểm tra nước đi hợp lệ trên bàn cờ
bool isValid(int x, int y, int N) {
    return (x >= 0 && y >= 0 && x < N && y < N);
}

// Hàm quay lui thực hiện tìm tất cả các hành trình của quân mã
void knightTour(int **visited, int x_current, int y_current, int count, int N, int &totalSolutions) {
    // Đánh dấu ô hiện tại đã được ghé thăm
    visited[x_current][y_current] = count;
    count++;

    // Nếu tất cả các ô đã được ghé thăm, in hành trình
    if (count == N * N + 1) {
        totalSolutions++;
        cout << "Hanh trinh " << totalSolutions << ":\n";
        // In bàn cờ theo chiều từ dưới lên trên và từ trái sang phải
        for (int i = 0; i < N; i++) {  // Duyệt từ dòng dưới cùng lên trên
            for (int j = 0; j < N; j++) {
                cout << visited[i][j] << " ";  // Các ô được in từ trái sang phải
            }
            cout << endl;
        }
        cout << endl;

        // Quay lui trước khi trả về
        visited[x_current][y_current] = 0;
        return;
    }

    // Duyệt các nước đi
    for (int t = 0; t < 8; t++) {
        int newX = x_current + row[t];
        int newY = y_current + col[t];

        // Nếu vị trí mới hợp lệ và chưa ghé thăm
        if (isValid(newX, newY, N) && visited[newX][newY] == 0) {
            knightTour(visited, newX, newY, count, N, totalSolutions);
        }
    }

    // Quay lui: Nếu không có hành trình hợp lệ, đánh dấu lại ô hiện tại là chưa ghé thăm
    visited[x_current][y_current] = 0;
}

int main() {
    int N;
    cout << "Nhap kich thuoc ban co N: ";
    cin >> N;

    int startX, startY;
    cout << "Nhap toa do bat dau cua quan ma (x y): ";
    cin >> startX >> startY;

    // Điều chỉnh tọa độ sao cho (1,1) là góc dưới bên trái
    startX = N - startX;  // Dòng tăng từ dưới lên
    startY = startY - 1;  // Cột tăng từ trái sang phải

    // Kiểm tra vị trí bắt đầu có hợp lệ không
    if (!isValid(startX, startY, N)) {
        cout << "Toa do khong hop le! Vui long chay lai chuong trinh va nhap toa do hop le." << endl;
        return 1;
    }

    // Cấp phát mảng 2 chiều động cho bàn cờ
    int **visited = new int *[N];
    for (int i = 0; i < N; i++) {
        visited[i] = new int[N];
        for (int j = 0; j < N; j++) {
            visited[i][j] = 0;  // Khởi tạo tất cả các ô là chưa ghé thăm
        }
    }

    int count = 1;  // Số lượng ô đã ghé thăm
    int totalSolutions = 0;

    // Bắt đầu từ vị trí xuất phát do người dùng nhập
    knightTour(visited, startX, startY, count, N, totalSolutions);

    // In ra tổng số hành trình hợp lệ
    if (totalSolutions == 0) {
        cout << "Khong tim thay hanh trinh hop le." << endl;
    } else {
        cout << "Tong so hanh trinh hop le: " << totalSolutions << endl;
    }

    // Giải phóng bộ nhớ
    for (int i = 0; i < N; i++) {
        delete[] visited[i];
    }
    delete[] visited;

    return 0;
}
