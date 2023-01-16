#pragma once

#include <exception>


namespace HLA
{
	// Something wrong with the dimensions of a matrix
	class DimensionError : public std::exception
	{
	public:
		DimensionError(const char* msg) : exception(msg) {}
		DimensionError() : exception("Dimension Error."){}
	};

	class NotImplemented : public std::exception
	{
	public:
		NotImplemented(const char* msg) : exception(msg) {}
		NotImplemented() : exception("Functionality not implemented.") {}
	};
}