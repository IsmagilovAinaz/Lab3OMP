#include <iostream>
#include "Matrix.h"

Matrix::Matrix(int r, int c)
	: rows(r), colums(c)
{
	Create();
}

void Matrix::Create() {
	matrix = new int* [rows];
	for (int i = 0; i < rows; i++) {
		matrix[i] = new int[colums];
	}
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < colums; j++) {
			matrix[i][j] = 0;
		}
	}
}

int Matrix::Rrand(int min, int max) {
	return 1 + rand() % (max - min + 1) + min;
}

void Matrix::RandFill() {
	if (matrix != NULL) {
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < colums; j++) {
				matrix[i][j] = Rrand(-100, 100);
			}
		}
	}
	else {
		std::cout << "Matrix is empty" << std::endl;
	}
	
}

void Matrix::PrintArr() {
	if (matrix != NULL) {
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < colums; j++) {
				std::cout << matrix[i][j] << " ";
			}
			std::cout << std::endl;
		}
	}
	else {
		std::cout << "Matrix is empty" << std::endl;
	}
}

Matrix::~Matrix() {
	for (int i = 0; i < rows; i++) {
		delete[] matrix[i];
	}
	delete[] matrix;
}
