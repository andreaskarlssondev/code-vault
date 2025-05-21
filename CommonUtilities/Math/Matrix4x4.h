#pragma once

#include "Vector4.h"

#include <initializer_list>
#include <algorithm>
#include <assert.h>

namespace CommonUtilities
{
	template <class T>
	class Matrix4x4
	{
		public:
			// Create the identity matrix.
			Matrix4x4<T>();

			// Creaste matris from array
			Matrix4x4<T>(const T (&aDataArray)[4][4]);

			// Creaste matris from initilizer list
			Matrix4x4<T>(const std::initializer_list<T>& someValues);

			// Copy Constructor
			Matrix4x4<T>(const Matrix4x4<T>& aMatrix);

			// Allocation
			Matrix4x4<T>& operator=(const Matrix4x4<T>& aMatrix);

			// () operator for accessing element (row, column) for read/write or read, respectively.
			T& operator()(const int aRow, const int aColumn);
			const T& operator()(const int aRow, const int aColumn) const;

			// Static functions for creating rotation metrices around X.
			static Matrix4x4<T> CreateRotationAroundX(T aAngleInRadians);
			// Static functions for creating rotation metrices around Y.
			static Matrix4x4<T> CreateRotationAroundY(T aAngleInRadians);
			// Static functions for creating rotation metrices around Z.
			static Matrix4x4<T> CreateRotationAroundZ(T aAngleInRadians);

			// Static function for creating a transpose of matrix.
			static Matrix4x4<T> Transpose(const Matrix4x4<T>& aMatrixToTranspose);

			// Assumes aTransform is made up of nothing but roration and translation.
			static Matrix4x4<T> GetFastInverse(const Matrix4x4<T>& aTransform);

		private:
			T myData[4][4];
	};

	template<class T>
	inline Matrix4x4<T>::Matrix4x4(): 
		myData {
			{1, 0, 0, 0},
			{0, 1, 0, 0},
			{0, 0, 1, 0},
			{0, 0, 0, 1}
		}
	{}

	template<class T>
	inline Matrix4x4<T>::Matrix4x4(const T(&aDataArray)[4][4]): myData(aDataArray)
	{}

	template<class T>
	inline Matrix4x4<T>::Matrix4x4(const std::initializer_list<T>& someValues)
	{
		assert(someValues.size() < 17);
		std::copy(someValues.begin(), someValues.begin() + someValues.size(), &myData[0][0]);
		for (size_t row = someValues.size() / 4; row < 4; ++row)
		{
			for (size_t column = someValues.size() % 4; column < 4; ++column)
			{
				myData[row][column] = T();
			}
		}
	}

	template<class T>
	inline Matrix4x4<T>::Matrix4x4(const Matrix4x4<T>& aMatrix)
	{
		std::copy(&aMatrix.myData[0][0], &aMatrix.myData[0][0] + 4 * 4, &myData[0][0]);
	}

	template<class T>
	inline Matrix4x4<T>& Matrix4x4<T>::operator=(const Matrix4x4<T>& aMatrix)
	{
		if (this == &aMatrix)
		{
			return *this;
		}

		std::copy(&aMatrix.myData[0][0], &aMatrix.myData[0][0] + 4 * 4, &myData[0][0]);

		return *this;
	}

	template<class T>
	inline T& Matrix4x4<T>::operator()(const int aRow, const int aColumn)
	{
		assert((aRow > 0 && aColumn > 0) && L"Index to low");
		assert((5 > aRow && 5 > aColumn) && L"Index to high");
		return myData[aRow - 1][aColumn - 1];
	}

	template<class T>
	inline const T& Matrix4x4<T>::operator()(const int aRow, const int aColumn) const
	{
		assert((aRow > 0 && aColumn > 0) && L"Index to low");
		assert((5 > aRow && 5 > aColumn) && L"Index to high");
		return myData[aRow - 1][aColumn - 1];
	}

	// Add two matrix and return result.
	template <class T> Matrix4x4<T> operator+(const Matrix4x4<T>& aMatrix, const Matrix4x4<T>& aSecondMatrix)
	{
		return
		{	
			aMatrix(1, 1) + aSecondMatrix(1, 1), aMatrix(1, 2) + aSecondMatrix(1, 2), aMatrix(1, 3) + aSecondMatrix(1, 3), aMatrix(1, 4) + aSecondMatrix(1, 4),
			aMatrix(2, 1) + aSecondMatrix(2, 1), aMatrix(2, 2) + aSecondMatrix(2, 2), aMatrix(2, 3) + aSecondMatrix(2, 3), aMatrix(2, 4) + aSecondMatrix(2, 4),
			aMatrix(3, 1) + aSecondMatrix(3, 1), aMatrix(3, 2) + aSecondMatrix(3, 2), aMatrix(3, 3) + aSecondMatrix(3, 3), aMatrix(3, 4) + aSecondMatrix(3, 4),
			aMatrix(4, 1) + aSecondMatrix(4, 1), aMatrix(4, 2) + aSecondMatrix(4, 2), aMatrix(4, 3) + aSecondMatrix(4, 3), aMatrix(4, 4) + aSecondMatrix(4, 4),
		};
	}

	// Subract a matrix from the first one return the result.
	template <class T> Matrix4x4<T> operator-(const Matrix4x4<T>& aMatrix, const Matrix4x4<T>& aSecondMatrix)
	{
		return
		{
			aMatrix(1, 1) - aSecondMatrix(1, 1), aMatrix(1, 2) - aSecondMatrix(1, 2), aMatrix(1, 3) - aSecondMatrix(1, 3), aMatrix(1, 4) - aSecondMatrix(1, 4),
			aMatrix(2, 1) - aSecondMatrix(2, 1), aMatrix(2, 2) - aSecondMatrix(2, 2), aMatrix(2, 3) - aSecondMatrix(2, 3), aMatrix(2, 4) - aSecondMatrix(2, 4),
			aMatrix(3, 1) - aSecondMatrix(3, 1), aMatrix(3, 2) - aSecondMatrix(3, 2), aMatrix(3, 3) - aSecondMatrix(3, 3), aMatrix(3, 4) - aSecondMatrix(3, 4),
			aMatrix(4, 1) - aSecondMatrix(4, 1), aMatrix(4, 2) - aSecondMatrix(4, 2), aMatrix(4, 3) - aSecondMatrix(4, 3), aMatrix(4, 4) - aSecondMatrix(4, 4),
		};
	}

	// Multiply two matrixes and return the result.
	template <class T> Matrix4x4<T> operator*(const Matrix4x4<T>& aMatrix, const Matrix4x4<T>& aSecondMatrix)
	{
		return
		{
			aMatrix(1, 1) * aSecondMatrix(1, 1) + aMatrix(1, 2) * aSecondMatrix(2, 1) + aMatrix(1, 3) * aSecondMatrix(3, 1) + aMatrix(1, 4) * aSecondMatrix(4, 1),
			aMatrix(1, 1) * aSecondMatrix(1, 2) + aMatrix(1, 2) * aSecondMatrix(2, 2) + aMatrix(1, 3) * aSecondMatrix(3, 2) + aMatrix(1, 4) * aSecondMatrix(4, 2),
			aMatrix(1, 1) * aSecondMatrix(1, 3) + aMatrix(1, 2) * aSecondMatrix(2, 3) + aMatrix(1, 3) * aSecondMatrix(3, 3) + aMatrix(1, 4) * aSecondMatrix(4, 3),
			aMatrix(1, 1) * aSecondMatrix(1, 4) + aMatrix(1, 2) * aSecondMatrix(2, 4) + aMatrix(1, 3) * aSecondMatrix(3, 4) + aMatrix(1, 4) * aSecondMatrix(4, 4),
	
			aMatrix(2, 1) * aSecondMatrix(1, 1) + aMatrix(2, 2) * aSecondMatrix(2, 1) + aMatrix(2, 3) * aSecondMatrix(3, 1) + aMatrix(2, 4) * aSecondMatrix(4, 1),
			aMatrix(2, 1) * aSecondMatrix(1, 2) + aMatrix(2, 2) * aSecondMatrix(2, 2) + aMatrix(2, 3) * aSecondMatrix(3, 2) + aMatrix(2, 4) * aSecondMatrix(4, 2),
			aMatrix(2, 1) * aSecondMatrix(1, 3) + aMatrix(2, 2) * aSecondMatrix(2, 3) + aMatrix(2, 3) * aSecondMatrix(3, 3) + aMatrix(2, 4) * aSecondMatrix(4, 3),
			aMatrix(2, 1) * aSecondMatrix(1, 4) + aMatrix(2, 2) * aSecondMatrix(2, 4) + aMatrix(2, 3) * aSecondMatrix(3, 4) + aMatrix(2, 4) * aSecondMatrix(4, 4),

			aMatrix(3, 1) * aSecondMatrix(1, 1) + aMatrix(3, 2) * aSecondMatrix(2, 1) + aMatrix(3, 3) * aSecondMatrix(3, 1) + aMatrix(3, 4) * aSecondMatrix(4, 1),
			aMatrix(3, 1) * aSecondMatrix(1, 2) + aMatrix(3, 2) * aSecondMatrix(2, 2) + aMatrix(3, 3) * aSecondMatrix(3, 2) + aMatrix(3, 4) * aSecondMatrix(4, 2),
			aMatrix(3, 1) * aSecondMatrix(1, 3) + aMatrix(3, 2) * aSecondMatrix(2, 3) + aMatrix(3, 3) * aSecondMatrix(3, 3) + aMatrix(3, 4) * aSecondMatrix(4, 3),
			aMatrix(3, 1) * aSecondMatrix(1, 4) + aMatrix(3, 2) * aSecondMatrix(2, 4) + aMatrix(3, 3) * aSecondMatrix(3, 4) + aMatrix(3, 4) * aSecondMatrix(4, 4),

			aMatrix(4, 1) * aSecondMatrix(1, 1) + aMatrix(4, 2) * aSecondMatrix(2, 1) + aMatrix(4, 3) * aSecondMatrix(3, 1) + aMatrix(4, 4) * aSecondMatrix(4, 1),
			aMatrix(4, 1) * aSecondMatrix(1, 2) + aMatrix(4, 2) * aSecondMatrix(2, 2) + aMatrix(4, 3) * aSecondMatrix(3, 2) + aMatrix(4, 4) * aSecondMatrix(4, 2),
			aMatrix(4, 1) * aSecondMatrix(1, 3) + aMatrix(4, 2) * aSecondMatrix(2, 3) + aMatrix(4, 3) * aSecondMatrix(3, 3) + aMatrix(4, 4) * aSecondMatrix(4, 3),
			aMatrix(4, 1) * aSecondMatrix(1, 4) + aMatrix(4, 2) * aSecondMatrix(2, 4) + aMatrix(4, 3) * aSecondMatrix(3, 4) + aMatrix(4, 4) * aSecondMatrix(4, 4),
		};
	}

	// Multiply with a Vector4.
	template <class T> Vector4<T> operator*(const Vector4<T>& aVector, const Matrix4x4<T>& aMatrix)
	{
		return
		{
			aVector.x * aMatrix(1,1) + aVector.y * aMatrix(2,1) + aVector.z * aMatrix(3,1) + aVector.w * aMatrix(4,1),
			aVector.x * aMatrix(1,2) + aVector.y * aMatrix(2,2) + aVector.z * aMatrix(3,2) + aVector.w * aMatrix(4,2),
			aVector.x * aMatrix(1,3) + aVector.y * aMatrix(2,3) + aVector.z * aMatrix(3,3) + aVector.w * aMatrix(4,3),
			aVector.x * aMatrix(1,4) + aVector.y * aMatrix(2,4) + aVector.z * aMatrix(3,4) + aVector.w * aMatrix(4,4),
		};
	}

	// Add a matrix on this.
	template <class T> void operator+=(Matrix4x4<T>& aMatrix, const Matrix4x4<T>& aSecondMatrix)
	{
		for (int row = 1; row < 5; ++row)
		{
			for (int column = 1; column < 5; ++column)
			{
				aMatrix(row, column) += aSecondMatrix(row, column);
			}
		}
	}

	// Subract a matric from this.
	template <class T> void operator-=(Matrix4x4<T>& aMatrix, const Matrix4x4<T>& aSecondMatrix)
	{
		for (int row = 1; row < 5; ++row)
		{
			for (int column = 1; column < 5; ++column)
			{
				aMatrix(row, column) -= aSecondMatrix(row, column);
			}
		}
	}

	// Multiply a matrix with this.
	template <class T> void operator*=(Matrix4x4<T>& aMatrix, const Matrix4x4<T>& aSecondMatrix)
	{
		aMatrix = aMatrix * aSecondMatrix;
	}

	// Comparison two matrixes.
	template <class T> bool operator==(const Matrix4x4<T> aMatrix, const Matrix4x4<T> aSecondMatrix)
	{
		for (int row = 1; row < 5; ++row)
		{
			for (int column = 1; column < 5; ++column)
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
	inline Matrix4x4<T> CommonUtilities::Matrix4x4<T>::CreateRotationAroundX(T aAngleInRadians)
	{
		return
		{
			1, 0, 0, 0 ,
			0, cos(aAngleInRadians), sin(aAngleInRadians), 0 ,
			0, -sin(aAngleInRadians), cos(aAngleInRadians), 0 ,
			0, 0, 0, 1 
		};
	}

	template<class T>
	inline Matrix4x4<T> CommonUtilities::Matrix4x4<T>::CreateRotationAroundY(T aAngleInRadians)
	{ 
		return
		{
			cos(aAngleInRadians), 0, -sin(aAngleInRadians), 0,
			0, 1, 0, 0,
			sin(aAngleInRadians), 0, cos(aAngleInRadians) , 0,
			0, 0, 0, 1
		};
	}

	template<class T>
	inline Matrix4x4<T> CommonUtilities::Matrix4x4<T>::CreateRotationAroundZ(T aAngleInRadians)
	{
		return
		{
			cos(aAngleInRadians), sin(aAngleInRadians), 0, 0,
			-sin(aAngleInRadians), cos(aAngleInRadians), 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
		};
	}

	template<class T>
	inline Matrix4x4<T> CommonUtilities::Matrix4x4<T>::Transpose(const Matrix4x4<T>& aMatrixToTranspose)
	{
		return 
		{
			 aMatrixToTranspose(1, 1), aMatrixToTranspose(2, 1), aMatrixToTranspose(3, 1), aMatrixToTranspose(4, 1),
			 aMatrixToTranspose(1, 2), aMatrixToTranspose(2, 2), aMatrixToTranspose(3, 2), aMatrixToTranspose(4, 2),
			 aMatrixToTranspose(1, 3), aMatrixToTranspose(2, 3), aMatrixToTranspose(3, 3), aMatrixToTranspose(4, 3),
			 aMatrixToTranspose(1, 4), aMatrixToTranspose(2, 4), aMatrixToTranspose(3, 4), aMatrixToTranspose(4, 4),
		};
	}

	template<class T>
	inline Matrix4x4<T> Matrix4x4<T>::GetFastInverse(const Matrix4x4<T>& aTransform)
	{
		// Split them
		// Transpose them
		// Add them togeter in a return

		Matrix4x4<T> rotationTransformation;
		for (int row = 1; row < 4; ++row)
		{
			for (int column = 1; column < 4; ++column)
			{
				rotationTransformation(row, column) = aTransform(row, column);
			}
		}

		Matrix4x4<T> translationTransformation;
		for (int column = 1; column < 4; ++column)
		{
			translationTransformation(4, column) = -aTransform(4, column);
		}
		translationTransformation(4, 4) = aTransform(4, 4);

		return translationTransformation * Transpose(rotationTransformation) ;
	}

}