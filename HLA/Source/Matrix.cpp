#include <cmath>

#include "Matrix.h"
#include "Common.h"
#include "MatrixExceptions.h"

namespace HLA
{
	bool Matrix::Internal_VerifySize(size_t nm, Size sz)
	{
		if (nm == sz.c * sz.r) return true;
		return false;
	}

	Matrix::Matrix(const std::initializer_list<double>& init, Size sz): m_Elements(init), m_Size(sz)
	{
		if (!Internal_VerifySize(init.size(), m_Size))
			throw DimensionError("Size Error");
	}

	Matrix::Matrix(const std::vector<double>& init, Size sz) : m_Elements(init), m_Size(sz)
	{
		if (!Internal_VerifySize(init.size(), m_Size))
			throw DimensionError("Size Error");
	}

	Matrix::Matrix(const Matrix& other) = default;

	Matrix& Matrix::operator=(const Matrix& other) = default;

	Matrix::Matrix(Matrix&&) noexcept = default;

	Matrix& Matrix::operator=(Matrix&&) noexcept = default;

	Matrix::~Matrix() = default;

	Matrix Matrix::Transpose()
	{
		std::vector<double> init;
		init.reserve(m_Size.c * m_Size.r);

		std::vector<std::vector<double>> columns;
		columns.resize(m_Size.c);

		// fill rows and columns
		for (size_t y = 0; y < m_Size.r; ++y)
		{
			for (size_t x = 0; x < m_Size.c; ++x)
			{
				columns.at(x).push_back(m_Elements[(m_Size.c * y) + x]);
			}
		}

		for (const auto& col: columns)
		{
			for (double d : col)
			{
				init.push_back(d);
			}
		}
		return Matrix{ init, {m_Size.c, m_Size.r} };
	}

	double Matrix::Trace()
	{
		double traceSum = 0;
		const size_t maxIdx = std::min(m_Size.c, m_Size.r);
		for (size_t i = 0; i < maxIdx; ++i)
		{
			traceSum += this->operator()(i, i);
		}
		return traceSum;
	}

	double Matrix::Determinant()
	{
		if (!IsSquare(*this))
			throw DimensionError("Matrix must be a square matrix");

		if (m_Size.r == 2)	// 2x2
		{
			return this->operator()(0, 0) * this->operator()(1, 1) - this->operator()(1, 0) * this->operator()(0, 1);
		}

		else if (m_Size.r == 3)
		{
			return +this->operator()(0, 0) * (this->operator()(1, 1) * this->operator()(2, 2) - this->operator()(2, 1) * this->operator()(1, 2))
				- this->operator()(1, 0) * (this->operator()(0, 1) * this->operator()(2, 2) - this->operator()(2, 1) * this->operator()(0, 2))
				+ this->operator()(2, 0) * (this->operator()(0, 1) * this->operator()(1, 2) - this->operator()(1, 1) * this->operator()(0, 2));

		}

		else
		{
			// TODO: 4x4 Matrix
			throw NotImplemented();
		}

	}

	double Matrix::Norm(const unsigned short p)
	{
		switch (p)
		{
		case 1:
			{
				double maxSum = 0;
				double rowSum = 0;


				// The following is for column-wise

				//for (size_t y = 0; y < m_Size.r; ++y)
				//{
				//	rowSum = 0;	// reset row sum per row iteration
				//	for (size_t x = 0; x < m_Size.c; ++x)
				//	{
				//		rowSum += std::abs(this->operator()(x, y));
				//	}
				//	maxSum = std::max(maxSum, rowSum);
				//}

				const Matrix transposedMatrix = this->Transpose();

				for (size_t y = 0; y < transposedMatrix.m_Size.r; ++y)
				{
					rowSum = 0;	// reset row sum per row iteration
					for (size_t x = 0; x < transposedMatrix.m_Size.c; ++x)
					{
						rowSum += std::abs(transposedMatrix(x, y));
					}
					maxSum = std::max(maxSum, rowSum);
				}

				return maxSum;
			}

		case 2:
			{
				double sum = 0;
				for (const double d : m_Elements)
				{
					sum += std::pow(d, 2);
				}
				return sqrt(sum);
			}

		default:
			throw NotImplemented("Unsupported Norm Type.");
		}
	}

	bool Matrix::IsVector()
	{
		if (m_Size.c == 1 || m_Size.r == 1) return true;
		return false;
	}

	Matrix Matrix::Inverse()
	{
		const double oDetScalar = 1.0 / this->Determinant();

		if (m_Size.r == 2)	// 2x2
		{
			return Matrix { {+this->operator()(1,1) * oDetScalar,
					-this->operator()(0,1) * oDetScalar,
					-this->operator()(1,0) * oDetScalar,
					+this->operator()(0,0) * oDetScalar}, {2, 2} };
		}

		else if (m_Size.r == 3)
		{
			Matrix returnMatrix = Zero(3, 3);
			returnMatrix(0,0) = +(this->operator()(1,1) * this->operator()(2,2) - this->operator()(2,1) * this->operator()(1,2)) * oDetScalar;
			returnMatrix(1,0) = -(this->operator()(1,0) * this->operator()(2,2) - this->operator()(2,0) * this->operator()(1,2)) * oDetScalar;
			returnMatrix(2,0) = +(this->operator()(1,0) * this->operator()(2,1) - this->operator()(2,0) * this->operator()(1,1)) * oDetScalar;
			returnMatrix(0,1) = -(this->operator()(0,1) * this->operator()(2,2) - this->operator()(2,1) * this->operator()(0,2)) * oDetScalar;
			returnMatrix(1,1) = +(this->operator()(0,0) * this->operator()(2,2) - this->operator()(2,0) * this->operator()(0,2)) * oDetScalar;
			returnMatrix(2,1) = -(this->operator()(0,0) * this->operator()(2,1) - this->operator()(2,0) * this->operator()(0,1)) * oDetScalar;
			returnMatrix(0,2) = +(this->operator()(0,1) * this->operator()(1,2) - this->operator()(1,1) * this->operator()(0,2)) * oDetScalar;
			returnMatrix(1,2) = -(this->operator()(0,0) * this->operator()(1,2) - this->operator()(1,0) * this->operator()(0,2)) * oDetScalar;
			returnMatrix(2,2) = +(this->operator()(0,0) * this->operator()(1,1) - this->operator()(1,0) * this->operator()(0,1)) * oDetScalar;
			return returnMatrix;
		}

		else
		{
			// TODO: 4x4 Matrix
			throw NotImplemented();
		}
	}

	Size Matrix::Shape() const
	{
		return m_Size;
	}

	Matrix Matrix::operator+(const Matrix& other)
	{
		// check compatibility
		if ((m_Size.c != other.m_Size.c) || (m_Size.r != other.m_Size.r))
			throw DimensionError("Incompatible matrices, cannot be Added.");

		Matrix returnMat = *this;	// copy current matrix

		for (size_t y = 0; y < m_Size.r; ++y)
		{
			for (size_t x = 0; x < m_Size.c; ++x)
			{
				returnMat.m_Elements[(m_Size.c * y) + x] += other.m_Elements[(m_Size.c * y) + x];
			}
		}
		return returnMat;
	}

	Matrix Matrix::operator-(const Matrix& other)
	{
		// check compatibility
		if ((m_Size.c != other.m_Size.c) || (m_Size.r != other.m_Size.r))
			throw DimensionError("Incompatible matrices, cannot be Subtracted.");

		Matrix returnMat = *this;	// copy current matrix

		for (size_t y = 0; y < m_Size.r; ++y)
		{
			for (size_t x = 0; x < m_Size.c; ++x)
			{
				returnMat.m_Elements[(m_Size.c * y) + x] -= other.m_Elements[(m_Size.c * y) + x];
			}
		}
		return returnMat;
	}

	Matrix Matrix::operator*(const Matrix& other)
	{
		// check compatibility
		if (m_Size.c != other.m_Size.r)
			throw DimensionError("Incompatible matrices, cannot be multiplied.");

		std::vector<std::vector<double>> rows;
		std::vector<std::vector<double>> columns;
		rows.resize(m_Size.r);
		columns.resize(other.m_Size.c);

		// fill rows and columns
		for (size_t y = 0; y < m_Size.r; ++y)
		{
			std::vector<double> row;
			for (size_t x = 0; x < m_Size.c; ++x)
			{
				row.push_back(m_Elements[(m_Size.c * y) + x]);
				//row.at(x) = m_Elements[(m_Size.c * y) + x];
			}
			rows.at(y) = row;
		}

		for (size_t y = 0; y < other.m_Size.r; ++y)
		{
			for (size_t x = 0; x < other.m_Size.c; ++x)
			{
				columns.at(x).push_back(other.m_Elements[(other.m_Size.c * y) + x]);
			}
		}



		Matrix returnMatrix = Zero(m_Size.r, other.m_Size.c);

		for (size_t y = 0; y < m_Size.r; ++y)	// iterate through rows
		{
			for (size_t x = 0; x < other.m_Size.c; ++x)	// iterate through columns within the row
			{
				returnMatrix(x, y) = Dot(rows.at(y), columns.at(x));
			}
		}
		return returnMatrix;
	}

	inline double& Matrix::operator()(size_t x, size_t y)
	{
		return m_Elements[(m_Size.c * y) + x];
	}

	inline double Matrix::operator()(size_t x, size_t y) const
	{
		return m_Elements[(m_Size.c * y) + x];
	}

	Matrix::operator std::vector<double>()
	{
		if (this->IsVector())
		{
			return m_Elements;
		}
		throw DimensionError("Not a vector.");
	}

	std::string Matrix::PrintFormat()
	{
		std::string retString;
		for (size_t y = 0; y < m_Size.r; ++y)
		{
			for (size_t x = 0; x < m_Size.c; ++x)
			{
				retString += std::to_string(m_Elements[(m_Size.c * y) + x]) + (x == m_Size.c - 1? "":" ");
			}
			retString += '\n';
		}
		return retString;
	}
}
