#include <iostream>
#include <cstdlib>
using namespace std;

int* NomerMatrNul(int** m, int r, int c, int& cnt) {
    cnt = 0;
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (m[i][j] == 0) {
                cnt++;
                break;
            }
        }
    }
    if (cnt == 0) return 0;

    int* rows = (int*)malloc(cnt * sizeof(int));
    int idx = 0;

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (m[i][j] == 0) {
                rows[idx++] = i;
                break;
            }
        }
    }
    return rows;
}

int main() {
    setlocale(LC_ALL, "");

    int A, B, C, D, r = 2, c = 2;

    cout << "Vvedite elementi matrici 2x2:\n";

    int** m = (int**)malloc(2 * sizeof(int*));
    for (int i = 0; i < 2; i++)
        m[i] = (int*)malloc(2 * sizeof(int));

    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            cin >> m[i][j];

    do {
        cout << "Vvedite A (strook sverhu): ";
        cin >> A;
    } while (A < 0);

    do {
        cout << "Vvedite B (stolbcov sleva): ";
        cin >> B;
    } while (B < 0);

    cout << "Vvedite C i D: ";
    cin >> C >> D;

    for (int i = 0; i < r; i++) {
        m[i] = (int*)realloc(m[i], (c + B) * sizeof(int));
        for (int j = c - 1; j >= 0; j--)
            m[i][j + B] = m[i][j];
    }
    c += B;

    m = (int**)realloc(m, (r + A) * sizeof(int*));
    for (int i = r - 1; i >= 0; i--)
        m[i + A] = m[i];
    for (int i = 0; i < A; i++)
        m[i] = (int*)malloc(c * sizeof(int));
    r += A;

    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++)
            m[i][j] = i * C + j * D;

    cout << "\nRezultat:\n";
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++)
            cout << m[i][j] << " ";
        cout << endl;
    }

    int zcnt;
    int* zrows = NomerMatrNul(m, r, c, zcnt);

    if (zcnt > 0) {
        int ni = 0;
        for (int i = 0; i < r; i++) {
            bool found = false;
            for (int j = 0; j < zcnt; j++) {
                if (i == zrows[j]) {
                    found = true;
                    break;
                }
            }

            if (!found) {
                if (ni != i) {
                    for (int j = 0; j < c; j++)
                        m[ni][j] = m[i][j];
                }
                ni++;
            }
        }

        for (int i = r - zcnt; i < r; i++)
            free(m[i]);

        r -= zcnt;
        m = (int**)realloc(m, r * sizeof(int*));
        free(zrows);

        cout << "\nPosle udalenia:\n";
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++)
                cout << m[i][j] << " ";
            cout << endl;
        }
    }
    else {
        cout << "\nNet nulei\n";
    }

    for (int i = 0; i < r; i++)
        free(m[i]);
    free(m);

    int n1, n2;
    cout << "\nVvedite dva chisla: ";
    cin >> n1 >> n2;

    int* ptr1 = new int(n1);
    int* ptr2 = new int(n2);

    *ptr1 *= 2;

    int temp = *ptr1;
    *ptr1 = *ptr2;
    *ptr2 = temp;

    n1 = *ptr1;
    n2 = *ptr2;

    cout << "Itog: " << n1 << " " << n2 << endl;

    delete ptr1;
    delete ptr2;

    return 0;
}
