#include <Novice.h>
#include <cmath>
#include<cassert>

const char kWindowTitle[] = "LD2A_05_コバヤシ_タカヒト_タイトル";

struct Vector3 {
	float x, y, z;
};

struct Matrix4x4
{
	float m[4][4];
};
//Matrix4x4 積
Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 result;
	float term = 0.0f;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			term = 0;
			for (int k = 0; k < 4; k++) {
				term = term + m1.m[i][k] * m2.m[k][j];
				result.m[i][j] = term;
			}
		}
	}
	return result;
}

//並行移動行列
Matrix4x4 MakeTranslateMatrix(const Vector3& translate) {
	Matrix4x4 result;
	result.m[0][0] = 1.0f;
	result.m[0][1] = 0.0f;
	result.m[0][2] = 0.0f;
	result.m[0][3] = 0.0f;

	result.m[1][0] = 0.0f;
	result.m[1][1] = 1.0f;
	result.m[1][2] = 0.0f;
	result.m[1][3] = 0.0f;

	result.m[2][0] = 0.0f;
	result.m[2][1] = 0.0f;
	result.m[2][2] = 1.0f;
	result.m[2][3] = 0.0f;

	result.m[3][0] = translate.x;
	result.m[3][1] = translate.y;
	result.m[3][2] = translate.z;
	result.m[3][3] = 1.0f;
	return result;

}
Matrix4x4 MakeScaleMatrix(const Vector3& scale)
{
	Matrix4x4 result;
	result.m[0][0] = scale.x;
	result.m[0][1] = 0.0f;
	result.m[0][2] = 0.0f;
	result.m[0][3] = 0.0f;

	result.m[1][0] = 0.0f;
	result.m[1][1] = scale.y;
	result.m[1][2] = 0.0f;
	result.m[1][3] = 0.0f;

	result.m[2][0] = 0.0f;
	result.m[2][1] = 0.0f;
	result.m[2][2] = scale.z;
	result.m[2][3] = 0.0f;

	result.m[3][0] = 0.0f;
	result.m[3][1] = 0.0f;
	result.m[3][2] = 0.0f;
	result.m[3][3] = 1.0f;
	return result;
}

Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix) {
	Vector3 result;
	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + vector.z * matrix.m[2][0] + 1.0f * matrix.m[3][0];
	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + vector.z * matrix.m[2][1] + 1.0f * matrix.m[3][1];
	result.z = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + vector.z * matrix.m[2][2] + 1.0f * matrix.m[3][2];
	float w = vector.x * matrix.m[0][3] + vector.y * matrix.m[1][3] + vector.z * matrix.m[2][3] + 1.0f * matrix.m[3][3];
	assert(w != 0.0f);
	result.x /= w;
	result.y /= w;
	result.z /= w;
	return result;
}

//軸周りの回転行列
Matrix4x4 MakeRotateZMatrix(float radion) {
	Matrix4x4 result;
	result.m[0][0] = cosf(radion);
	result.m[0][1] = sinf(radion);
	result.m[0][2] = 0.0f;
	result.m[0][3] = 0.0f;

	result.m[1][0] = - sinf(radion);
	result.m[1][1] = cosf(radion);
	result.m[1][2] = 0.0f;
	result.m[1][3] = 0.0f;

	result.m[2][0] = 0.0f;
	result.m[2][1] = 0.0f;
	result.m[2][2] = 1.0f;
	result.m[2][3] = 0.0f;

	result.m[3][0] = 0;
	result.m[3][1] = 0;
	result.m[3][2] = 0;
	result.m[3][3] = 1.0f;
	return result;

}
Matrix4x4 MakeRotateXMatrix(float radion) {
	Matrix4x4 result;
	result.m[0][0] = 1.0f;
	result.m[0][1] = 0.0f;
	result.m[0][2] = 0.0f;
	result.m[0][3] = 0.0f;

	result.m[1][0] = 0.0f;
	result.m[1][1] = cosf(radion);
	result.m[1][2] = sinf(radion);
	result.m[1][3] = 0.0f;

	result.m[2][0] = 0.0f;
	result.m[2][1] = - sinf(radion);
	result.m[2][2] = cosf(radion);
	result.m[2][3] = 0.0f;

	result.m[3][0] = 0;
	result.m[3][1] = 0;
	result.m[3][2] = 0;
	result.m[3][3] = 1.0f;
	return result;

}
Matrix4x4 MakeRotateYMatrix(float radion) {
	Matrix4x4 result;
	result.m[0][0] = cosf(radion);
	result.m[0][1] = 0.0f;
	result.m[0][2] = - sinf(radion);
	result.m[0][3] = 0.0f;

	result.m[1][0] = 0.0f;
	result.m[1][1] = 1.0f;
	result.m[1][2] = 0.0f;
	result.m[1][3] = 0.0f;

	result.m[2][0] = sinf(radion);
	result.m[2][1] = 0.0f;
	result.m[2][2] = cosf(radion);
	result.m[2][3] = 0.0f;

	result.m[3][0] = 0;
	result.m[3][1] = 0;
	result.m[3][2] = 0;
	result.m[3][3] = 1.0f;
	return result;

}
//アフィン変換
Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate ) {
	Matrix4x4 rotateXMatrix = MakeRotateXMatrix(rotate.x);
	Matrix4x4 rotateYMatrix = MakeRotateYMatrix(rotate.y);
	Matrix4x4 rotateZMatrix = MakeRotateZMatrix(rotate.z);
	Matrix4x4 rotateXYZMatrix = Multiply(rotateXMatrix, (Multiply(rotateYMatrix, rotateZMatrix)));

	Matrix4x4 result;
	result.m[0][0] = rotateXYZMatrix.m[0][0] * scale.x;
	result.m[0][1] = rotateXYZMatrix.m[0][1] * scale.x;
	result.m[0][2] = rotateXYZMatrix.m[0][2] * scale.x;
	result.m[0][3] = 0.0f;

	result.m[1][0] = rotateXYZMatrix.m[1][0] * scale.y;
	result.m[1][1] = rotateXYZMatrix.m[1][1] * scale.y;
	result.m[1][2] = rotateXYZMatrix.m[1][2] * scale.y;
	result.m[1][3] = 0.0f;

	result.m[2][0] = rotateXYZMatrix.m[2][0] * scale.z;
	result.m[2][1] = rotateXYZMatrix.m[2][1] * scale.z;
	result.m[2][2] = rotateXYZMatrix.m[2][2] * scale.z;
	result.m[2][3] = 0.0f;

	result.m[3][0] = translate.x;
	result.m[3][1] = translate.y;
	result.m[3][2] = translate.z;
	result.m[3][3] = 1.0f;
	return result;

	
}

static int kRowHeight = 20;
static int kColumnWidth = 60;

void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix,const char* label) {
	for (int row = 0; row < 4; ++row) {
		for (int colmun = 0; colmun < 4; ++colmun) {
			Novice::ScreenPrintf(x + colmun * kColumnWidth, y + row * kRowHeight, "%6.02f", matrix.m[row][colmun], label);
		}
	}
}
void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label) {
	Novice::ScreenPrintf(x, y, "%.02f", vector.x,label);
	Novice::ScreenPrintf(x + kColumnWidth, y, "%.02f", vector.y, label);
	Novice::ScreenPrintf(x + kColumnWidth * 2, y, "%.02f", vector.z, label);
	Novice::ScreenPrintf(x + kColumnWidth * 3, y, "%s", label);
}

float Cotangent(float b, float a) {
	return (b / tanf(a));
}

//透投影行列
Matrix4x4 MakeperspectiveFovMatrix(float fovY, float aspectRatio, float neatClip, float farClip) {
	Matrix4x4 result;
	result.m[0][0] = Cotangent((1 / aspectRatio), (fovY/2));
	result.m[0][1] = 0.0f;
	result.m[0][2] = 0.0f;
	result.m[0][3] = 0.0f;

	result.m[1][0] = 0.0f;
	result.m[1][1] = Cotangent(1,fovY/2);
	result.m[1][2] = 0.0f;
	result.m[1][3] = 0.0f;

	result.m[2][0] = 0.0f;
	result.m[2][1] = 0.0f;
	result.m[2][2] = farClip / (farClip - neatClip);
	result.m[2][3] = 1.0f;

	result.m[3][0] = 0.0f;
	result.m[3][1] = 0.0f;
	result.m[3][2] = (neatClip * farClip) / (neatClip - farClip);
	result.m[3][3] = 0.0f;
	return result;
}
//正射投影行列
Matrix4x4 MakeOrthographhicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip) {
	assert(left != right);
	assert(top != bottom);
	Matrix4x4 result;
	result.m[0][0] = 2.0f / (right - left);
	result.m[0][1] = 0.0f;
	result.m[0][2] = 0.0f;
	result.m[0][3] = 0.0f;

	result.m[1][0] = 0.0f;
	result.m[1][1] = 2.0f / (top - bottom);
	result.m[1][2] = 0.0f;
	result.m[1][3] = 0.0f;

	result.m[2][0] = 0.0f;
	result.m[2][1] = 0.0f;
	result.m[2][2] = 1.0f / (farClip - nearClip);
	result.m[2][3] = 0.0f;

	result.m[3][0] = (left + right) / (left - right);
	result.m[3][1] = (top + bottom) / (bottom - top);
	result.m[3][2] = 1.0f / (farClip - nearClip);
	result.m[3][3] = 1.0f;
	return result;
}

//ビューポート変換行列
Matrix4x4 MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth) {
	Matrix4x4 result;
	result.m[0][0] = width / 2;
	result.m[0][1] = 0.0f;
	result.m[0][2] = 0.0f;
	result.m[0][3] = 0.0f;

	result.m[1][0] = 0.0f;
	result.m[1][1] = -(height / 2);
	result.m[1][2] = 0.0f;
	result.m[1][3] = 0.0f;

	result.m[2][0] = 0.0f;
	result.m[2][1] = 0.0f;
	result.m[2][2] = maxDepth - minDepth;
	result.m[0][3] = 0.0f;

	result.m[3][0] = left + (width / 2);
	result.m[3][1] = top + (height / 2);
	result.m[3][2] = minDepth;
	result.m[3][3] = 1.0f;
	return result;
}

Vector3 Cross(const Vector3& v1, const Vector3& v2) {
	Vector3 v3;
	v3.x = (v1.y * v2.z - v1.z * v2.y);
	v3.y = (v1.z * v2.x - v1.x * v2.z);
	v3.z = (v1.x * v2.y - v1.y * v2.x);
	return v3;

}
//４　逆行列
Matrix4x4 Inverse(const Matrix4x4& m) {
	Matrix4x4 result;
	float determinant =
		m.m[0][0] * m.m[1][1] * m.m[2][2] * m.m[3][3]
		+ m.m[0][0] * m.m[1][2] * m.m[2][3] * m.m[3][1]
		+ m.m[0][0] * m.m[1][3] * m.m[2][1] * m.m[3][2]
		- m.m[0][0] * m.m[1][3] * m.m[2][2] * m.m[3][1]
		- m.m[0][0] * m.m[1][2] * m.m[2][1] * m.m[3][3]
		- m.m[0][0] * m.m[1][1] * m.m[2][3] * m.m[3][2]
		- m.m[0][1] * m.m[1][0] * m.m[2][2] * m.m[3][3]
		- m.m[0][2] * m.m[1][0] * m.m[2][3] * m.m[3][1]
		- m.m[0][3] * m.m[1][0] * m.m[2][1] * m.m[3][2]
		+ m.m[0][3] * m.m[1][0] * m.m[2][2] * m.m[3][1]
		+ m.m[0][2] * m.m[1][0] * m.m[2][1] * m.m[3][3]
		+ m.m[0][1] * m.m[1][0] * m.m[2][3] * m.m[3][2]
		+ m.m[0][1] * m.m[1][2] * m.m[2][0] * m.m[3][3]
		+ m.m[0][2] * m.m[1][3] * m.m[2][0] * m.m[3][1]
		+ m.m[0][3] * m.m[1][1] * m.m[2][0] * m.m[3][2]
		- m.m[0][3] * m.m[1][2] * m.m[2][0] * m.m[3][1]
		- m.m[0][2] * m.m[1][1] * m.m[2][0] * m.m[3][3]
		- m.m[0][1] * m.m[1][3] * m.m[2][0] * m.m[3][2]
		- m.m[0][1] * m.m[1][2] * m.m[2][3] * m.m[3][0]
		- m.m[0][2] * m.m[1][3] * m.m[2][1] * m.m[3][0]
		- m.m[0][3] * m.m[1][1] * m.m[2][2] * m.m[3][0]
		+ m.m[0][3] * m.m[1][2] * m.m[2][1] * m.m[3][0]
		+ m.m[0][2] * m.m[1][1] * m.m[2][3] * m.m[3][0]
		+ m.m[0][1] * m.m[1][3] * m.m[2][2] * m.m[3][0];
	assert(determinant != 0.0f);
	float determinantRecp = 0.0f;
	determinantRecp = 1.0f / determinant;

	result.m[0][0] =
		(m.m[1][1] * m.m[2][2] * m.m[3][3]
			+ m.m[1][2] * m.m[2][3] * m.m[3][1]
			+ m.m[1][3] * m.m[2][1] * m.m[3][2]
			- m.m[1][3] * m.m[2][2] * m.m[3][1]
			- m.m[1][2] * m.m[2][1] * m.m[3][3]
			- m.m[1][1] * m.m[2][3] * m.m[3][2]
			) / determinant;

	result.m[0][1] =
		(-m.m[0][1] * m.m[2][2] * m.m[3][3]
			- m.m[0][2] * m.m[2][3] * m.m[3][1]
			- m.m[0][3] * m.m[2][1] * m.m[3][2]
			+ m.m[0][3] * m.m[2][2] * m.m[3][1]
			+ m.m[0][2] * m.m[2][1] * m.m[3][3]
			+ m.m[0][1] * m.m[2][3] * m.m[3][2]
			) / determinant;

	result.m[0][2] =
		(m.m[0][1] * m.m[1][2] * m.m[3][3]
			+ m.m[0][2] * m.m[1][3] * m.m[3][1]
			+ m.m[0][3] * m.m[1][1] * m.m[3][2]
			- m.m[0][3] * m.m[1][2] * m.m[3][1]
			- m.m[0][2] * m.m[1][1] * m.m[3][3]
			- m.m[0][1] * m.m[1][3] * m.m[3][2]
			) / determinant;

	result.m[0][3] =
		(-m.m[0][1] * m.m[1][2] * m.m[2][3]
			- m.m[0][2] * m.m[1][3] * m.m[2][1]
			- m.m[0][3] * m.m[1][1] * m.m[2][2]
			+ m.m[0][3] * m.m[1][2] * m.m[2][1]
			+ m.m[0][2] * m.m[1][1] * m.m[2][3]
			+ m.m[0][1] * m.m[1][3] * m.m[2][2]
			) / determinant;



	result.m[1][0] =
		(-m.m[1][0] * m.m[2][2] * m.m[3][3]
			- m.m[1][2] * m.m[2][3] * m.m[3][0]
			- m.m[1][3] * m.m[2][0] * m.m[3][2]
			+ m.m[1][3] * m.m[2][2] * m.m[3][0]
			+ m.m[1][2] * m.m[2][0] * m.m[3][3]
			+ m.m[1][0] * m.m[2][3] * m.m[3][2]
			) / determinant;

	result.m[1][1] =
		(m.m[0][0] * m.m[2][2] * m.m[3][3]
			+ m.m[0][2] * m.m[2][3] * m.m[3][0]
			+ m.m[0][3] * m.m[2][0] * m.m[3][2]
			- m.m[0][3] * m.m[2][2] * m.m[3][0]
			- m.m[0][2] * m.m[2][0] * m.m[3][3]
			- m.m[0][0] * m.m[2][3] * m.m[3][2]
			) / determinant;

	result.m[1][2] =
		(-m.m[0][0] * m.m[1][2] * m.m[3][3]
			- m.m[0][2] * m.m[1][3] * m.m[3][0]
			- m.m[0][3] * m.m[1][0] * m.m[3][2]
			+ m.m[0][3] * m.m[1][2] * m.m[3][0]
			+ m.m[0][2] * m.m[1][0] * m.m[3][3]
			+ m.m[0][0] * m.m[1][3] * m.m[3][2]
			) / determinant;

	result.m[1][3] =
		(m.m[0][0] * m.m[1][2] * m.m[2][3]
			+ m.m[0][2] * m.m[1][3] * m.m[2][0]
			+ m.m[0][3] * m.m[1][0] * m.m[2][2]
			- m.m[0][3] * m.m[1][2] * m.m[2][0]
			- m.m[0][2] * m.m[1][0] * m.m[2][3]
			- m.m[0][0] * m.m[1][3] * m.m[2][2]
			) / determinant;



	result.m[2][0] =
		(m.m[1][0] * m.m[2][1] * m.m[3][3]
			+ m.m[1][1] * m.m[2][3] * m.m[3][0]
			+ m.m[1][3] * m.m[2][0] * m.m[3][1]
			- m.m[1][3] * m.m[2][1] * m.m[3][0]
			- m.m[1][1] * m.m[2][0] * m.m[3][3]
			- m.m[1][0] * m.m[2][3] * m.m[3][1]
			) / determinant;

	result.m[2][1] =
		(-m.m[0][0] * m.m[2][1] * m.m[3][3]
			- m.m[0][1] * m.m[2][3] * m.m[3][0]
			- m.m[0][3] * m.m[2][0] * m.m[3][1]
			+ m.m[0][3] * m.m[2][1] * m.m[3][0]
			+ m.m[0][1] * m.m[2][0] * m.m[3][3]
			+ m.m[0][0] * m.m[2][3] * m.m[3][1]
			) / determinant;

	result.m[2][2] =
		(m.m[0][0] * m.m[1][1] * m.m[3][3]
			+ m.m[0][1] * m.m[1][3] * m.m[3][0]
			+ m.m[0][3] * m.m[1][0] * m.m[3][1]
			- m.m[0][3] * m.m[1][1] * m.m[3][0]
			- m.m[0][1] * m.m[1][0] * m.m[3][3]
			- m.m[0][0] * m.m[1][3] * m.m[3][1]
			) / determinant;

	result.m[2][3] =
		(-m.m[0][0] * m.m[1][1] * m.m[2][3]
			- m.m[0][1] * m.m[1][3] * m.m[2][0]
			- m.m[0][3] * m.m[1][0] * m.m[2][1]
			+ m.m[0][3] * m.m[1][1] * m.m[2][0]
			+ m.m[0][1] * m.m[1][0] * m.m[2][3]
			+ m.m[0][0] * m.m[1][3] * m.m[2][1]
			) / determinant;



	result.m[3][0] =
		(-m.m[1][0] * m.m[2][1] * m.m[3][2]
			- m.m[1][1] * m.m[2][2] * m.m[3][0]
			- m.m[1][2] * m.m[2][0] * m.m[3][1]
			+ m.m[1][2] * m.m[2][1] * m.m[3][0]
			+ m.m[1][1] * m.m[2][0] * m.m[3][2]
			+ m.m[1][0] * m.m[2][2] * m.m[3][1]
			) / determinant;

	result.m[3][1] =
		(m.m[0][0] * m.m[2][1] * m.m[3][2]
			+ m.m[0][1] * m.m[2][2] * m.m[3][0]
			+ m.m[0][2] * m.m[2][0] * m.m[3][1]
			- m.m[0][2] * m.m[2][1] * m.m[3][0]
			- m.m[0][1] * m.m[2][0] * m.m[3][2]
			- m.m[0][0] * m.m[2][2] * m.m[3][1]
			) / determinant;


	result.m[3][2] =
		(-m.m[0][0] * m.m[1][1] * m.m[3][2]
			- m.m[0][1] * m.m[1][2] * m.m[3][0]
			- m.m[0][2] * m.m[1][0] * m.m[3][1]
			+ m.m[0][2] * m.m[1][1] * m.m[3][0]
			+ m.m[0][1] * m.m[1][0] * m.m[3][2]
			+ m.m[0][0] * m.m[1][2] * m.m[3][1]
			) / determinant;

	result.m[3][3] =
		(m.m[0][0] * m.m[1][1] * m.m[2][2]
			+ m.m[0][1] * m.m[1][2] * m.m[2][0]
			+ m.m[0][2] * m.m[1][0] * m.m[2][1]
			- m.m[0][2] * m.m[1][1] * m.m[2][0]
			- m.m[0][1] * m.m[1][0] * m.m[2][2]
			- m.m[0][0] * m.m[1][2] * m.m[2][1]
			) / determinant;
	return result;
}

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	Vector3 v1{ 1.2f,-3.9f,2.5f };
	Vector3 v2{ 2.8f,0.4f,-1.3f };
	Vector3 rotate{};
	Vector3 translate{};
	Vector3 cameraPosition{0.0f,0.0f,-10.0f };
	const int kWindowWidth = 1280;
	const int kWindowHeight = 720;

	Vector3 kLocalVertices[3];
	kLocalVertices[0] = { 0.0f,0.0f,0.0f };
	kLocalVertices[1] = { 1.0f,-1.0f,0.0f };
	kLocalVertices[2] = { -1.0f,-1.0f,0.0f };
	
	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///
		if (keys[DIK_A]) {
			translate.x -= 0.1f;
		}
		if (keys[DIK_D]) {
			translate.x += 0.1f;
		}
		if (keys[DIK_S]) {
			translate.z -= 0.1f;
		}
		if (keys[DIK_W]) {
			translate.z += 0.1f;
		}

		if (keys[DIK_RIGHTARROW]) {
			rotate.y += 0.1f;
		}
		if (keys[DIK_LEFTARROW]) {
			rotate.y -= 0.1f;
		}

		Matrix4x4 worldMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, rotate, translate);
		Matrix4x4 cameraMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, cameraPosition);
		Matrix4x4 viewMatrix = Inverse(cameraMatrix);
		Matrix4x4 projectionMatrix = MakeperspectiveFovMatrix(0.45f, float(kWindowWidth) / float(kWindowHeight), 0.1f, 100.0f);
		Matrix4x4 worldViewProjectionMatrix = Multiply(worldMatrix, Multiply(viewMatrix, projectionMatrix));
		Matrix4x4 viewportMatrix = MakeViewportMatrix(0, 0, float(kWindowWidth) , float(kWindowHeight), 0.0f, 1.0f);
		Vector3 screenVertices[3];
		for (uint32_t i = 0; i < 3; i++) {
			Vector3 ndcVertex = Transform(kLocalVertices[i], worldViewProjectionMatrix);
			screenVertices[i] = Transform(ndcVertex, viewportMatrix);
		}

		Vector3 cross = Cross(v1,v2);
		///
		/// ↑更新処理ここまで
		///
		
		///
		/// ↓描画処理ここから
		///
		Novice::DrawTriangle(
			int(screenVertices[0].x), int(screenVertices[0].y), int(screenVertices[1].x), int(screenVertices[1].y),
			int(screenVertices[2].x), int(screenVertices[2].y), RED, kFillModeSolid
		);
		VectorScreenPrintf(0, 0, cross, "Cross");
		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
