#include <iostream>

int main() {
    
    const int N = 7;
    int x[N];

    std::cout << "Vvedite " << N << " chisel  massiva crat 5:\n";
    for(int i = 0; i < N; ++i) {
        std::cin >> x[i];
    }

  
    int all_crat5 = 1; 
    for(int i = 0; i < N; ++i) {
        if(x[i] % 5 != 0) {
            all_crat5 = 0;
        }
    }

    
    if(all_crat5 == 1) {
        for(int i = 0; i < N - 1; ++i) {
            for(int j = i + 1; j < N; ++j) {
                if(x[i] > x[j]) {
                    int tmp = x[i];
                    x[i] = x[j];
                    x[j] = tmp;
                }
            }
        }
    }

    std::cout << "Massiv posle proverki i sortirovki:\n";
    for(int i = 0; i < N; ++i) {
        std::cout << x[i] << " ";
    }
    std::cout << std::endl;

    
    const int strok = 3;
    const int stolb = 4;
    int matrix[strok][stolb];

    std::cout << "Vvedite 12 chisel(Matrix):\n";
    for(int i = 0; i < strok; ++i) {
        for(int j = 0; j < stolb; ++j) {
            std::cin >> matrix[i][j];
        }
    }

    
    int max_сol_otric = 0;
    int max_col_indx = 0;
    for(int j = 0; j < stolb; ++j) {
        int cnt = 0;
        for(int i = 0; i < strok; ++i) {
            if(matrix[i][j] < 0) {
                ++cnt;
            }
        }
        if(cnt > max_сol_otric) {
            max_сol_otric = cnt;
            max_col_indx = j;
        }
    }

    
    for(int i = 0; i < strok; ++i) {
        matrix[i][max_col_indx] = -1;
    }

    std::cout << "Matrix posle zamene:\n";
    for(int i = 0; i < strok; ++i) {
        for(int j = 0; j < stolb; ++j) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
