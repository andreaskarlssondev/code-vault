#pragma once

#include "Matrix4x4.h"
#include "Vector3.h"

#include <initializer_list>
#include <algorithm>
#include <assert.h>


namespace CommonUtilities
{
	template <class T>
	class Matrix3x3
	{
		public:
			// Create the identity matrix.
			Matrix3x3<T>();

			// Creaste matris from array
			Matrix3x3<T>(T (&aDataArray)[3][3]);

			// Creaste matris from initilizer list
			Matrix3x3<T>(const std::initializer_list<T>& someValues);

			// Copy Constructor
			Matrix3x3<T>(const Matrix3x3<T>& aMatrix);

			// Copies the top left 3x3 part of the Matrix4x4
			Matrix3x3<T>(const Matrix4x4<T>& aMatrix);

			// Allocation
			Matrix3x3<T>& operator=(const Matrix3x3<T>& aMatrix);

			// () operator for accessing element (row, column) for read/write or read, respectively.
			T& operator()(const int aRow, const int aColumn);
			const T& operator()(const int aRow, const int aColumn) const;

			const T Determinant() const;

			// Static functions for creating rotation metrices.
			static Matrix3x3<T> CreateRotationAroundX(T aAngleInRadians);
			static Matrix3x3<T> CreateRotationAroundY(T aAngleInRadians);
			static Matrix3x3<T> CreateRotationAroundZ(T aAngleInRadians);

			// Static function for creating a transpose of matrix.
			static Matrix3x3<T> Transpose(const Matrix3x3<T>& aMatrixToTranspose);

		private:
			T myData[3][3];

	};

	template<class T>
	inline Matrix3x3<T>::Matrix3x3():
		myData {
			{1, 0, 0},
			{0, 1, 0},
			{0, 0, 1}
		}
	{}


	template<class T>
	inline Matrix3x3<T>::Matrix3x3(T(&aDataArray)[3][3]): myData(aDataArray)
	{}

	template<class T>
	inline Matrix3x3<T>::Matrix3x3(const std::initializer_list<T>& someValues)
	{
		assert(someValues.size() < 10);
		std::copy(someValues.begin(), someValues.begin() + someValues.size(), &myData[0][0]);
		for (size_t row = someValues.size() / 3; row < 3; ++row)
		{
			for (size_t column = someValues.size() % 3; column < 3; ++column)
			{
				myData[row][column] = T();
			}
		}
	}


	template<class T>
	inline Matrix3x3<T>::Matrix3x3(const Matrix3x3<T>& aMatrix)
	{
		std::copy(&aMatrix.myData[0][0], &aMatrix.myData[0][0] + 3 * 3, &myData[0][0]);
	}

	template<class T>
	inline Matrix3x3<T>::Matrix3x3(const Matrix4x4<T>& aMatrix)
	{
		for (int row = 0; row < 3; ++row)
		{
			for (int column = 0; column < 3;)
			{
				myData[row][column] = aMatrix(row + 1, ++column);
			}
		}
	}

	template<class T>
	inline Matrix3x3<T>& Matrix3x3<T>::operator=(const Matrix3x3<T>& aMatrix)
	{
		if (this == &aMatrix)
		{
			return *this;
		}

		std::copy(&aMatrix.myData[0][0], &aMatrix.myData[0][0] + 3 * 3, &myData[0][0]);

		return *this;
	}

	template<class T>
	inline T& Matrix3x3<T>::operator()(const int aRow, const int aColumn)
	{
		assert((aRow > 0 && aColumn > 0) && L"Index to low");
		assert((4 > aRow && 4 > aColumn) && L"Index to high");
		return myData[aRow - 1][aColumn - 1];
	}

	template<class T>
	inline const T& Matrix3x3<T>::operator()(const int aRow, const int aColumn) const
	{
		assert((aRow > 0 && aColumn > 0) && L"Index to low");
		assert((4 > aRow && 4 > aColumn) && L"Index to high");
		return myData[aRow - 1][aColumn - 1];
	}

	template<class T>
	inline const T Matrix3x3<T>::Determinant() const
	{
		return myData[0][0] * myData[1][1] * myData[2][2]
			+ myData[0][1] * myData[1][2] * myData[2][0]
			+ myData[0][2] * myData[1][0] * myData[2][1]
			- myData[0][2] * myData[1][1] * myData[2][1]
			- myData[0][1] * myData[1][0] * myData[2][2]
			- myData[0][0] * myData[1][2] * myData[2][1];
	}

	// Add two matrix and return result.
	template <class T> 
	Matrix3x3<T> operator+(const Matrix3x3<T>& aMatrix, const Matrix3x3<T>& aSecondMatrix)
	{
		return
		{
			aMatrix(1, 1) + aSecondMatrix(1, 1), aMatrix(1, 2) + aSecondMatrix(1, 2), aMatrix(1, 3) + aSecondMatrix(1, 3),
			aMatrix(2, 1) + aSecondMatrix(2, 1), aMatrix(2, 2) + aSecondMatrix(2, 2), aMatrix(2, 3) + aSecondMatrix(2, 3),
			aMatrix(3, 1) + aSecondMatrix(3, 1), aMatrix(3, 2) + aSecondMatrix(3, 2), aMatrix(3, 3) + aSecondMatrix(3, 3),
		};
	}

	// Subract a matrix from the first one return the result.
	template <class T> 
	Matrix3x3<T> operator-(const Matrix3x3<T>& aMatrix, const Matrix3x3<T>& aSecondMatrix)
	{
		return
		{
			aMatrix(1, 1) - aSecondMatrix(1, 1), aMatrix(1, 2) - aSecondMatrix(1, 2), aMatrix(1, 3) - aSecondMatrix(1, 3),
			aMatrix(2, 1) - aSecondMatrix(2, 1), aMatrix(2, 2) - aSecondMatrix(2, 2), aMatrix(2, 3) - aSecondMatrix(2, 3),
			aMatrix(3, 1) - aSecondMatrix(3, 1), aMatrix(3, 2) - aSecondMatrix(3, 2), aMatrix(3, 3) - aSecondMatrix(3, 3),
		};
	}

	// Multiply two matrixes and return the result.
	template <class T> 
	Matrix3x3<T> operator*(const Matrix3x3<T>& aMatrix, const Matrix3x3<T>& aSecondMatrix)
	{
		return
		{
			aMatrix(1, 1) * aSecondMatrix(1, 1) + aMatrix(1, 2) * aSecondMatrix(2, 1) + aMatrix(1, 3) * aSecondMatrix(3, 1),
			aMatrix(1, 1) * aSecondMatrix(1, 2) + aMatrix(1, 2) * aSecondMatrix(2, 2) + aMatrix(1, 3) * aSecondMatrix(3, 2),
			aMatrix(1, 1) * aSecondMatrix(1, 3) + aMatrix(1, 2) * aSecondMatrix(2, 3) + aMatrix(1, 3) * aSecondMatrix(3, 3),
			
			aMatrix(2, 1) * aSecondMatrix(1, 1) + aMatrix(2, 2) * aSecondMatrix(2, 1) + aMatrix(2, 3) * aSecondMatrix(3, 1),
			aMatrix(2, 1) * aSecondMatrix(1, 2) + aMatrix(2, 2) * aSecondMatrix(2, 2) + aMatrix(2, 3) * aSecondMatrix(3, 2),
			aMatrix(2, 1) * aSecondMatrix(1, 3) + aMatrix(2, 2) * aSecondMatrix(2, 3) + aMatrix(2, 3) * aSecondMatrix(3, 3),

			aMatrix(3, 1) * aSecondMatrix(1, 1) + aMatrix(3, 2) * aSecondMatrix(2, 1) + aMatrix(3, 3) * aSecondMatrix(3, 1),
			aMatrix(3, 1) * aSecondMatrix(1, 2) + aMatrix(3, 2) * aSecondMatrix(2, 2) + aMatrix(3, 3) * aSecondMatrix(3, 2),
			aMatrix(3, 1) * aSecondMatrix(1, 3) + aMatrix(3, 2) * aSecondMatrix(2, 3) + aMatrix(3, 3) * aSecondMatrix(3, 3),
		};
	}

	// Multiply with a Vector3.
	template <class T> 
	Vector3<T> operator*(const Vector3<T>& aVector, const Matrix3x3<T>& aMatrix)
	{
		return
		{
			aVector.x * aMatrix(1,1) + aVector.y * aMatrix(2,1) + aVector.z * aMatrix(3,1),
			aVector.x * aMatrix(1,2) + aVector.y * aMatrix(2,2) + aVector.z * aMatrix(3,2),
			aVector.x * aMatrix(1,3) + aVector.y * aMatrix(2,3) + aVector.z * aMatrix(3,3),
		};
	}

	// Setting aMatrix to (aMatrix + aSecondMatrix)
	template <class T> 
	void operator+=(Matrix3x3<T>& aMatrix, const Matrix3x3<T>& aSecondMatrix)
	{
		for (int row = 1; row < 4; ++row)
		{
			for (int column = 1; column < 4; ++column)
			{
				aMatrix(row, column) += aSecondMatrix(row, column);
			}
		}
	}

	// Setting aMatrix to (aMatrix - aSecondMatrix)
	template <class T> 
	void operator-=(Matrix3x3<T>& aMatrix, const Matrix3x3<T>& aSecondMatrix)
	{
		for (int row = 1; row < 4; ++row)
		{
			for (int column = 1; column < 4; ++column)
			{
				aMatrix(row, column) -= aSecondMatrix(row, column);
			}
		}
	}

	// Setting aMatrix to (aMatrix * aSecondMatrix)
	template <class T>
	void operator*=(Matrix3x3<T>& aMatrix, const Matrix3x3<T>& aSecondMatrix)
	{
		aMatrix = aMatrix * aSecondMatrix;
	}

	// Comparison two matrixes.
	template <class T>
	bool operator==(const Matrix3x3<T>& aMatrix, const Matrix3x3<T>& aSecondMatrix)
	{
		for (int row = 1; row < 4; ++row)
		{
			for (int column = 1; column < 4; ++column)
			{
				if (aMatrix(row, column) != aSecondMatrix(row, column))
				{
					return false;
				}
			}
		}
		return true;
	}


	template<class T>
	inline Matrix3x3<T> Matrix3x3<T>::CreateRotationAroundX(T aAngleInRadians)
	{
		return
		{
			1, 0, 0,
			0, cos(aAngleInRadians), sin(aAngleInRadians),
			0, -sin(aAngleInRadians), cos(aAngleInRadians),
		};
	}

	template<class T>
	inline Matrix3x3<T> Matrix3x3<T>::CreateRotationAroundY(T aAngleInRadians)
	{
		return
		{
			cos(aAngleInRadians), 0, -sin(aAngleInRadians),
			0, 1, 0,
			sin(aAngleInRadians), 0, cos(aAngleInRadians),
		};
	}

	template<class T>
	inline Matrix3x3<T> Matrix3x3<T>::CreateRotationAroundZ(T aAngleInRadians)
	{
		return
		{
			cos(aAngleInRadians), sin(aAngleInRadians), 0,
			-sin(aAngleInRadians), cos(aAngleInRadians), 0,
			0, 0, 1,
		};
	}

	template<class T>
	inline Matrix3x3<T> Matrix3x3<T>::Transpose(const Matrix3x3<T>& aMatrixToTranspose)
	{
		return 
		{
			 aMatrixToTranspose(1, 1), aMatrixToTranspose(2, 1), aMatrixToTranspose(3, 1),
			 aMatrixToTranspose(1, 2), aMatrixToTranspose(2, 2), aMatrixToTranspose(3, 2),
			 aMatrixToTranspose(1, 3), aMatrixToTranspose(2, 3), aMatrixToTranspose(3, 3),
		};
	}
}
