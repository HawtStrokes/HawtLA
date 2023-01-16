#pragma once
#include <vector>
#include <initializer_list>
#include <string>

namespace HLA
{
	struct Size
	{
		size_t r, c;
	};

	class Matrix
	{
	private:
		std::vector<double> m_Elements;
		Size m_Size;

	private:
		static bool Internal_VerifySize(size_t nm, Size sz);

	public:
		Matrix(const std::initializer_list<double>& init, Size sz);
		Matrix(const std::vector<double>& init, Size sz);

		// Copies
		Matrix(const Matrix&);
		Matrix& operator=(const Matrix&);

		// Move
		Matrix(Matrix&&) noexcept;
		Matrix& operator=(Matrix&&) noexcept;

		~Matrix();

	public:
		Matrix Transpose();

		double Trace();
		double Determinant();
		//double Cofactor();
		//double Minor();
		double Norm(const unsigned short p);

		bool IsVector();

		// Matrix Adj();
		Matrix Inverse();

		[[nodiscard]] Size Shape() const;

		Matrix operator+(const Matrix&);	
		Matrix operator-(const Matrix&);
		Matrix operator*(const Matrix&);
		double& operator()(size_t x, size_t y);
		double operator()(size_t x, size_t y) const;
		explicit operator std::vector<double>();

		std::string PrintFormat();
	};
}