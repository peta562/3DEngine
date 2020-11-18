#pragma once
#include <memory>
#include "Vector3D.h"

class Matrix4x4
{
public:
	Matrix4x4() 
	{

	}

	void setIdentity()
	{
		::memset(matrix, 0, sizeof(float) * 16);
		matrix[0][0] = 1;
		matrix[1][1] = 1;
		matrix[2][2] = 1;
		matrix[3][3] = 1;
	}

	void setTranslation(const Vector3D& translation)
	{
		setIdentity();
		matrix[3][0] = translation.x;
		matrix[3][1] = translation.y;
		matrix[3][2] = translation.z;
	}

	void setScale(const Vector3D& scale)
	{
		setIdentity();
		matrix[0][0] = scale.x;
		matrix[1][1] = scale.y;
		matrix[2][2] = scale.z;
	}

	void setRotationX(float x)
	{
		matrix[1][1] = cos(x);
		matrix[2][2] = cos(x);
		matrix[2][1] = -sin(x);
		matrix[1][2] = sin(x);
	}

	void setRotationY(float y)
	{
		matrix[0][0] = cos(y);
		matrix[2][2] = cos(y);
		matrix[2][0] = sin(y);
		matrix[0][2] = -sin(y);
	}

	void setRotationZ(float z)
	{
		matrix[0][0] = cos(z);
		matrix[1][1] = cos(z);
		matrix[1][0] = -sin(z);
		matrix[0][1] = sin(z);
	}

	void operator *=(const Matrix4x4& mat)
	{
		Matrix4x4 out;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				out.matrix[i][j] = matrix[i][0] * mat.matrix[0][j] +
					matrix[i][1] * mat.matrix[1][j] +
					matrix[i][2] * mat.matrix[2][j] +
					matrix[i][3] * mat.matrix[3][j];

			}
		}
		::memcpy(matrix, out.matrix, sizeof(float) * 16);
	}
	void setOrtho(float width, float height, float near_plane, float far_plane)
	{
		setIdentity();
		matrix[0][0] = 2.0f / width;
		matrix[1][1] = 2.0f / height;
		matrix[2][2] = 1.0f / (far_plane - near_plane);
		matrix[3][2] = -(near_plane / ( far_plane - near_plane));
	}

	~Matrix4x4()
	{

	}

public:
	float matrix[4][4];
};
