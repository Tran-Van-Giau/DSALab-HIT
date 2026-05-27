#include <iostream>
#include <iomanip>
#include <string>
#include <chrono>

using namespace std;
using namespace chrono;

// ======================================================
// STRUCT CONTACT
// ======================================================

struct Contact {

    string name;
    string phone;
};

// ======================================================
// LINEAR SEARCH
// ======================================================

bool contains(string text, string keyword) {

    return text.find(keyword) != string::npos;
}

void linearSearch(Contact a[], int n, string keyword) {

    int steps = 0;
    bool found = false;

    auto start = high_resolution_clock::now();

    cout << "\nKet qua tim kiem:\n\n";

    for (int i = 0; i < n; i++) {

        steps++;

        if (contains(a[i].name, keyword)) {

            cout << i + 1 << ". "
                 << left << setw(25) << a[i].name
                 << " - "
                 << a[i].phone
                 << endl;

            found = true;
        }
    }

    auto stop = high_resolution_clock::now();

    auto duration =
        duration_cast<microseconds>(stop - start);

    if (!found) {

        cout << "Khong tim thay!\n";

        cout << "\nGoi y ten gan dung:\n";

        int count = 0;

        for (int i = 0; i < n && count < 3; i++) {

            if (a[i].name[0] == keyword[0]) {

                cout << "- " << a[i].name << endl;
                count++;
            }
        }
    }

    cout << "\nDa so sanh "
         << steps
         << "/"
         << n
         << " phan tu";

    cout << " — "
         << duration.count()
         << " microseconds\n";
}

// ======================================================
// BUBBLE SORT THEO PHONE
// ======================================================

void bubbleSort(Contact a[], int n) {

    for (int i = 0; i < n - 1; i++) {

        for (int j = n - 1; j > i; j--) {

            if (a[j].phone < a[j - 1].phone) {

                Contact temp = a[j];
                a[j] = a[j - 1];
                a[j - 1] = temp;
            }
        }
    }
}

// ======================================================
// BINARY SEARCH ITERATIVE
// ======================================================

int binarySearchIterative(
    Contact a[],
    int n,
    string phone,
    int& steps
) {

    int left = 0;
    int right = n - 1;

    while (left <= right) {

        steps++;

        int mid = (left + right) / 2;

        if (a[mid].phone == phone)
            return mid;

        if (a[mid].phone < phone)
            left = mid + 1;
        else
            right = mid - 1;
    }

    return -1;
}

// ======================================================
// BINARY SEARCH RECURSIVE
// ======================================================

int binarySearchRecursive(
    Contact a[],
    int left,
    int right,
    string phone,
    int& steps
) {

    if (left > right)
        return -1;

    steps++;

    int mid = (left + right) / 2;

    if (a[mid].phone == phone)
        return mid;

    if (a[mid].phone < phone) {

        return binarySearchRecursive(
            a,
            mid + 1,
            right,
            phone,
            steps
        );
    }

    return binarySearchRecursive(
        a,
        left,
        mid - 1,
        phone,
        steps
    );
}

// ======================================================
// XUAT DANH BA
// ======================================================

void printContacts(Contact a[], int n) {

    cout << "\n================ DANH BA ================\n";

    cout << left
         << setw(30) << "TEN"
         << "SO DIEN THOAI\n";

    cout << "=========================================\n";

    for (int i = 0; i < n; i++) {

        cout << left
             << setw(30)
             << a[i].name
             << a[i].phone
             << endl;
    }
}

// ======================================================
// SO SANH HIEU NANG
// ======================================================

void performanceTable() {

    cout << "\n========== BANG SO SANH ==========\n";

    cout << left
         << setw(15) << "N"
         << setw(20) << "Linear"
         << setw(20) << "Binary"
         << endl;

    cout << "==============================================\n";

    cout << setw(15) << "10,000"
         << setw(20) << "O(N)"
         << setw(20) << "O(log N)"
         << endl;

    cout << setw(15) << "100,000"
         << setw(20) << "O(N)"
         << setw(20) << "O(log N)"
         << endl;

    cout << setw(15) << "1,000,000"
         << setw(20) << "O(N)"
         << setw(20) << "O(log N)"
         << endl;
}

// ======================================================
// MAIN
// ======================================================

int main() {

    Contact contacts[] = {

        {"Nguyen Van Minh", "0901234567"},
        {"Tran Thi Minh Anh", "0912345678"},
        {"Le Minh Tuan", "0923456789"},
        {"Pham Gia Bao", "0934567890"},
        {"Vo Hoang Long", "0945678901"},
        {"Nguyen Minh Quan", "0956789012"},
        {"Tran Duc Huy", "0967890123"},
        {"Le Thi Lan", "0978901234"}
    };

    int n =
        sizeof(contacts) / sizeof(Contact);

    int choice;

    do {

        cout << "\n";
        cout << "======= SMART SEARCH ENGINE =======\n";
        cout << "1. Hien thi danh ba\n";
        cout << "2. Tim theo ten (Linear Search)\n";
        cout << "3. Tim theo SDT (Binary Iterative)\n";
        cout << "4. Tim theo SDT (Binary Recursive)\n";
        cout << "5. Bang so sanh hieu nang\n";
        cout << "0. Thoat\n";

        cout << "Chon: ";
        cin >> choice;

        switch (choice) {

        case 1: {

            printContacts(contacts, n);
            break;
        }

        case 2: {

            cin.ignore();

            string keyword;

            cout << "\nNhap ten can tim: ";
            getline(cin, keyword);

            linearSearch(
                contacts,
                n,
                keyword
            );

            break;
        }

        case 3: {

            bubbleSort(contacts, n);

            string phone;

            cout << "\nNhap SDT can tim: ";
            cin >> phone;

            int steps = 0;

            auto start =
                high_resolution_clock::now();

            int pos =
                binarySearchIterative(
                    contacts,
                    n,
                    phone,
                    steps
                );

            auto stop =
                high_resolution_clock::now();

            auto duration =
                duration_cast<microseconds>(
                    stop - start
                );

            if (pos == -1) {

                cout << "\nKhong tim thay!\n";
            }
            else {

                cout << "\nTim thay:\n";

                cout << contacts[pos].name
                     << " - "
                     << contacts[pos].phone
                     << endl;
            }

            cout << "\nDa so sanh "
                 << steps
                 << "/"
                 << n
                 << " phan tu";

            cout << " — "
                 << duration.count()
                 << " microseconds\n";

            break;
        }

        case 4: {

            bubbleSort(contacts, n);

            string phone;

            cout << "\nNhap SDT can tim: ";
            cin >> phone;

            int steps = 0;

            auto start =
                high_resolution_clock::now();

            int pos =
                binarySearchRecursive(
                    contacts,
                    0,
                    n - 1,
                    phone,
                    steps
                );

            auto stop =
                high_resolution_clock::now();

            auto duration =
                duration_cast<microseconds>(
                    stop - start
                );

            if (pos == -1) {

                cout << "\nKhong tim thay!\n";
            }
            else {

                cout << "\nTim thay:\n";

                cout << contacts[pos].name
                     << " - "
                     << contacts[pos].phone
                     << endl;
            }

            cout << "\nDa so sanh "
                 << steps
                 << "/"
                 << n
                 << " phan tu";

            cout << " — "
                 << duration.count()
                 << " microseconds\n";

            break;
        }

        case 5: {

            performanceTable();
            break;
        }

        case 0: {

            cout << "\nThoat chuong trinh!\n";
            break;
        }

        default:

            cout << "\nLua chon khong hop le!\n";
        }

    } while (choice != 0);

    return 0;
}
