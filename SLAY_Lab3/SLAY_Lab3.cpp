#include <iostream>
#include <omp.h>
#include "Matrix.h"
#include <chrono>
using namespace std;

bool CheckInput() {
    return false;
}

int EnterNumOfUnknown() {
    int nX = 0;
    do {
        cout << "Enter the Number of unknown quantities in the system: ";
        cin >> nX;
        if (cin.fail() || nX <= 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Incorrect input!" << endl;
        }
    } while (nX <= 0);
    return nX;
}

int SelectOption() {
    int opt = 0;
    cout << "Select options:" <<endl;
    cout << "1) Autofill" << endl;
    cout << "2) Enter manually" << endl;
    do {
        cin >> opt;
        if (cin.fail() || (opt != 1 && opt != 2)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Incorrect input!" << endl;
        }
    } while (opt != 1 && opt != 2);
    return opt;
}

int Rrand(int min, int max) {
    return 1 + rand() % (max - min + 1) + min;
}

double** CreateMatrix(int rows, int colums) {
    double** arr = new double* [rows];
    for (int i = 0; i < rows; i++) {
        arr[i] = new double[colums];
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < colums; j++) {
            arr[i][j] = 0;
        }
    }
    return arr;
}

double** MatrixFill(double** arr, int rows, int colums) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < colums; j++) {
            arr[i][j] = Rrand(-100, 100);
        }
    }
    return arr;
}

double* ArrFill(double* arr, int len) {
    for (int i = 0; i < len; i++) {
        arr[i] = Rrand(-100, 100);
    }
    return arr;
}

double* ArrFillZeros(double* arr, int len) {
    for (int i = 0; i < len; i++) {
        arr[i] = 0;
    }
    return arr;
}

double** EnterMatrix(double** arr, int rows, int colums) {
    cout << "Fill the coefficient matrix" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < colums; j++) {
            cout << "A[" << i << "]" << "[" << j << "] = ";
            cin >> arr[i][j];
        }
    }
    return arr;
}

double* EnterArr(double* arr, int n) {
    cout << "Fill the matrix of Y" << endl;
    for (int i = 0; i < n; i++) {
        cout << "B[" << i << "] = ";
        cin >> arr[i];
    }
    return arr;
}

void PrintMatrix(double** matrix, int rows, int colums) {
    if (matrix != NULL) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < colums; j++) {
                cout << matrix[i][j] << " ";
            }
            cout << endl;
        }
    }
    else {
        cout << "Matrix is empty" << endl;
    }
}

void PrintArr(double* arr, int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

double* GaussOMP(double**A, double* Y, int n) {
    auto begin = std::chrono::steady_clock::now();
    double* X = new double[n];
#pragma omp parallel

    for (int k = 0; k < n; k++)
    {
#pragma omp for
        for(int j = k+1; j < n; j++){
            double m = A[j][k] / A[k][k];
            for (int i = k; i < n; i++) {
                A[j][i] = A[j][i] - m * A[k][i];
            }
            Y[j] = Y[j] - m * Y[k];
        }
    }

    //double sum;
//#pragma omp parallel
    
    for (int k = n - 1; k >= 0; k--) {
        //sum = 0;
//#pragma omp barrier

//#pragma omp for reduction(+:sum)
        X[k] = Y[k];
        for (int i = k + 1; i < n; i++) {
            //sum += A[k][i] * X[i];
            X[k] = X[k] - A[k][i] * X[i];

        }
//#pragma omp single
       //X[k] = (Y[k] - sum) / A[k][k];
        X[k] = X[k] / A[k][k];
    }
    auto end = std::chrono::steady_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    std::cout << "fuction time: " << elapsed_ms.count() << " ms\n";
    return X;
}

double* Gauss(double** A, double* Y, int n) {
    auto begin = std::chrono::steady_clock::now();
    double* X = new double[n];
        for (int k = 0; k < n; k++)
        {
            for (int j = k + 1; j < n; j++) {
                double m = A[j][k] / A[k][k];
                for (int i = k; i < n; i++) {
                    A[j][i] = A[j][i] - m * A[k][i];
                }
                Y[j] = Y[j] - m * Y[k];
            }
        }
    for (int k = n - 1; k >= 0; k--) {
        X[k] = Y[k];
        for (int i = k + 1; i < n; i++) {
            X[k] = X[k] - A[k][i] * X[i];

        }
        X[k] = X[k] / A[k][k];
    }
    auto end = std::chrono::steady_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    std::cout << "fuction time: " << elapsed_ms.count() << " ms\n";
    return X;
}

int main()
{
    int nX;
    nX = EnterNumOfUnknown();

    double** A = CreateMatrix(nX, nX);
    for (int i = 0; i < nX; i++) {
        A[i] = new double[nX];
    }
    for (int i = 0; i < nX; i++) {
        for (int j = 0; j < nX; j++) {
            A[i][j] = 0;
        }
    }
    double* X = new double[nX];
    double* Y = new double[nX];

    int opt;
    opt = SelectOption();
    switch (opt)
    {
    case 1:
        A = MatrixFill(A, nX, nX);
        //cout << "Matrix A:" << endl;
        //PrintMatrix(A, nX, nX);
        Y = ArrFill(Y, nX);
        //cout << "Matrix Y:" << endl;
        //PrintArr(Y, nX);
        X = GaussOMP(A, Y, nX);
        PrintArr(X, nX);
        cout << "-------------------------" << endl;
        //X = Gauss(A, Y, nX);
        //PrintArr(X, nX);
        break;
    case 2:
        A = EnterMatrix(A, nX, nX);
        Y = EnterArr(Y, nX);
        X = GaussOMP(A, Y, nX);
        PrintArr(X, nX);

        break;
    default:
        break;
    }
    for (int i = 0; i < nX; i++) {
        delete[] A[i];
    }
    delete[] A;
    delete[] X;
    delete[] Y;
}

