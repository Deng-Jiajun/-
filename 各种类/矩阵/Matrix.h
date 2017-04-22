#ifndef MATRIX_H
#define MATRIX_H
#include<iostream>
class Matrix//������
{
	friend Matrix multiplyMatrix(Matrix&, Matrix&);//ʵ�־���ĳ˻�
public:
	Matrix() = default;
	Matrix(int, int);
	Matrix(const Matrix&);
	Matrix& operator= (const Matrix&);
	int &element(int, int);//���ʾ���Ԫ��
	int element(int, int)const;//���ʾ���Ԫ��(Ϊ����������ṩ)
	int row()const;//�õ����������
	int col()const;//�õ����������
	void display()const;//��row��col����ʾ����Ԫ��
	Matrix transposeMatrix();//ʵ�־���ת��;
	//~Matrix() = default;
	~Matrix();
private:
	int *p_data_;//��������
	int row_, col_;//���������������

};

Matrix::Matrix(int r, int c)
{
	if (r <= 0 || c <= 0)
	{
		std::cerr << "����ߴ粻�Ϸ�!\n";
		exit(-1);
	}
	row_ = r; col_ = c;
	p_data_ = new int[row_*col_];
}

Matrix::Matrix(const Matrix &copy):row_(copy.row()),col_(copy.col()),p_data_(new int[copy.row()*copy.col()])
{
	for (int i = 0; i != copy.row(); ++i)
	{
		for (int j = 0; j != copy.col(); ++j)
		{
			element(i, j) = copy.element(i,j);
		}
	}
}

Matrix& Matrix::operator= (const Matrix &rhd)
{
	delete []p_data_;
	row_ = rhd.row();
	col_ = rhd.col();
	p_data_ = new int[rhd.row()*rhd.col()];

	for (int i = 0; i != rhd.row(); ++i)
	{
		for (int j = 0; j != rhd.col(); ++j)
		{
			element(i, j) = rhd.element(i, j);
		}
	}
	return *this;
}
Matrix::~Matrix()
{
	delete []p_data_;
}

int& Matrix::element(int i, int j)
{
	if (i < 0 || i >= row_ || j < 0 || j >= col_)
	{
		std::cerr << "�����±�Խ��\n";
		exit(-1);
	}
	return *(p_data_ + i*col_ + j);
}

int Matrix::element(int i, int j)const
{
	if (i < 0 || i >= row_ || j < 0 || j >= col_)
	{
		std::cerr << "�����±�Խ��\n";
		exit(-1);
	}
	return *(p_data_ + i*col_ + j);
}
int Matrix::row()const
{
	return row_;
}

int Matrix::col()const
{
	return col_;
}
void Matrix::display()const
{
	int *p = p_data_;
	for (int i = 0; i < row_; ++i)
	{
		for (int j = 0; j < col_; ++j)
		{
			std::cout << *p++ << ' ';
		}
		std::cout << std::endl;
	}
}
Matrix Matrix::transposeMatrix()
{
	Matrix copy(col(), row());
	for (int i = 0; i != copy.row(); ++i)
	{
		for (int j = 0; j != copy.col(); ++j)
		{
			copy.element(i, j) = element(j, i);
		}
	}
	return copy;
}
Matrix multiplyMatrix(Matrix &lhd, Matrix &rhd)
{
	if (lhd.col() != rhd.row() || lhd.row() != rhd.col())
	{
		std::cerr << "����ߴ粻ƥ��\n";
		exit(-1);
	}
	Matrix result(lhd.row(), lhd.row());
	for (int i = 0; i != result.row(); ++i)
	{
		for (int j = 0; j != result.row(); ++j)
		{
			result.element(i, j) = 0;
			for (int k = 0; k != lhd.col(); ++k)
				result.element(i, j) += lhd.element(i, k)*rhd.element(k, j);
		}
	}
	return result;
}

#endif // !MATRIX_H
