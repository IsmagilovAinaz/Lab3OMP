#pragma once
class Matrix
{
private:
	int rows;
	int colums;
	int** matrix;

public:
	Matrix(int r, int c);
	int Rrand(int min, int max);
	void RandFill();
	void PrintArr();
	void Create();
	~Matrix();
};

