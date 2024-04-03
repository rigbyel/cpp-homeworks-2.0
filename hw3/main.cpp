#include "Matrix.h"
#include <iostream>

Matrix findShiftMatrix(const Matrix& dot1, const Matrix& dot2) {
    if (dot1.m_col != dot2.m_col || dot1.n_row != dot2.n_row) {
        std::cerr << "wrong dimensions" << std::endl;
    }

    int m = dot1.m_col;
    Matrix shiftMatrix = Matrix(m, m);

    int i;
    for (i = 0; i < m; i++) {
        shiftMatrix.change(i, i, 1);
    }

    for (i = 0; i < m -1; i++) {
        double diff = dot2.data[0][i] - dot1.data[0][i];
        shiftMatrix.change(m-1, i, diff);
    }

    return shiftMatrix;
}

Matrix prepareDot(int n, double* arr) {
    double dotArr[n+1];
    for (int i = 0; i < n; i++) {
        dotArr[i] = arr[i];
    }

    dotArr[n] = 1;
    return Matrix(1, n+1, dotArr);
}

int main(int argc, char* argv[]){
    int n = 6;
    double firstArr[6] = {1., 2., -9., 0.3, 10., 15};
    double secondArr[6] = {1, -1, 1, -1, 1, -1};

    Matrix dot1 = prepareDot(n, firstArr);
    Matrix dot2 = prepareDot(n, secondArr);

    std::cout << "Точка 1: " << std::endl;
    for (int i = 0; i < n; i++) {
        std::cout << firstArr[i] << " ";
    }

    std::cout << std::endl;

    std::cout << "Точка 2: " << std::endl;
    for (int i = 0; i < n; i++) {
        std::cout << secondArr[i] << " ";
    }

    std::cout << std::endl << std::endl;

    Matrix shift = findShiftMatrix(dot1, dot2);
    std::cout << "Матрица переноса: " << std::endl;
    shift.print_m();
    std::cout << std::endl;

    Matrix res = dot1*shift;
    std::cout << "Результат умножения точки 1 на матрицу переноса: " << std::endl;
    for (int i = 0; i < n; i++) {
        std::cout << res.data[0][i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
