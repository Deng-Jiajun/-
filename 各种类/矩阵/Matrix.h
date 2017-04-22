#ifndef MATRIX_H
#define MATRIX_H
#include<iostream>
class Matrix//矩阵类
{
	friend Matrix multiplyMatrix(Matrix&, Matrix&);//实现矩阵的乘积
public:
	Matrix() = default;
	Matrix(int, int);
	Matrix(const Matrix&);
	Matrix& operator= (const Matrix&);
	int &element(int, int);//访问矩阵元素
	int element(int, int)const;//访问矩阵元素(为常量对象而提供)
	int row()const;//得到矩阵的行数
	int col()const;//得到矩阵的列数
	void display()const;//按row行col列显示矩阵元素
	Matrix transposeMatrix();//实现矩阵转置;
	//~Matrix() = default;
	~Matrix();
private:
	int *p_data_;//矩阵数据
	int row_, col_;//矩阵的行数和列数

};

Matrix::Matrix(int r, int c)
{
	if (r <= 0 || c <= 0)
	{
		std::cerr << "矩阵尺寸不合法!\n";
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
		std::cerr << "矩阵下标越界\n";
		exit(-1);
	}
	return *(p_data_ + i*col_ + j);
}

int Matrix::element(int i, int j)const
{
	if (i < 0 || i >= row_ || j < 0 || j >= col_)
	{
		std::cerr << "矩阵下标越界\n";
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
		std::cerr << "矩阵尺寸不匹配\n";
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
