#include <stdio.h>
#include <stdbool.h>

#define P 5 // 进程数
#define R 3 // 资源种类数

// 打印矩阵
void printMatrix(int matrix[P][R], const char *name) {
    printf("%s:\n", name);
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

// 安全性检查
bool isSafe(int processes[], int avail[], int max[][R], int allot[][R]) {
    int need[P][R];
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            need[i][j] = max[i][j] - allot[i][j];
        }
    }

    bool finish[P] = {0};
    int work[R];
    for (int i = 0; i < R; i++) {
        work[i] = avail[i];
    }

    while (true) {
        bool found = false;
        for (int p = 0; p < P; p++) {
            if (!finish[p]) {
                int j;
                for (j = 0; j < R; j++) {
                    if (need[p][j] > work[j]) {
                        break;
                    }
                }
                if (j == R) {
                    for (int k = 0; k < R; k++) {
                        work[k] += allot[p][k];
                    }
                    finish[p] = true;
                    found = true;
                }
            }
        }
        if (!found) {
            break;
        }
    }

    for (int i = 0; i < P; i++) {
        if (!finish[i]) {
            return false;
        }
    }
    return true;
}

int main() {
    int processes[] = {0, 1, 2, 3, 4};

    int avail[] = {3, 3, 2};

    int max[P][R] = {
        {7, 5, 3},
        {3, 2, 2},
        {9, 0, 2},
        {2, 2, 2},
        {4, 3, 3}
    };

    int allot[P][R] = {
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 2},
        {2, 1, 1},
        {0, 0, 2}
    };

    printMatrix(max, "Max");
    printMatrix(allot, "Allocation");

    if (isSafe(processes, avail, max, allot)) {
        printf("System is in a safe state.\n");
    } else {
        printf("System is not in a safe state.\n");
    }

    return 0;
}
