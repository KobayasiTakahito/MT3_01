#include <Novice.h>
#include <math.h>

const char kWindowTitle[] = "LD2A_05_コバヤシ_タカヒト_タイトル";

struct Vector3 {
	float x, y, z;
};
//加算
Vector3 Add(const Vector3& v1, const Vector3& v2){
	Vector3 result;
	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;
	return result;
}
//減算
Vector3 Subtract(const Vector3& v1, const Vector3& v2) {
	Vector3 result;
	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;
	return result;
}
//スカラー値
Vector3 Multiply(float scalar, const Vector3& v2) {
	Vector3 result;
	result.x = scalar * v2.x;
	result.y = scalar * v2.y;
	result.z = scalar * v2.z;
	return result;
}
//内積
float Dot(const Vector3& v1, const Vector3& v2) {
	float result;
	result = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	return result;
}
//長さ（ノルム）
float Length(const Vector3& v) {
	float result;
	result = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
	return result;
}
//正規化
Vector3 Normalize(const Vector3& v) {
	Vector3 result; 
	float length = Length(v);
	if (length != 0) {
		result.x = v.x / length;
		result.y = v.y / length;
		result.z = v.z / length;
	}
	return result;

}

static const int kColumnWidth = 60;
void vectorScreenprintf(int x, int y, const Vector3& vector, const char* label) {
	Novice::ScreenPrintf(x, y, "%.02f", vector.x);
	Novice::ScreenPrintf(x +kColumnWidth, y, "%.02f", vector.y);
	Novice::ScreenPrintf(x +kColumnWidth * 2, y, "%.02f", vector.z);
	Novice::ScreenPrintf(x + kColumnWidth * 3, y, "%s", label);
}

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	Vector3 v1{ 1.0f,3.0f,-5.0f };
	Vector3 v2{ 4.0f,-1.0f,2.0f };
	float k = { 4.0f };



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
		Vector3 resultAdd = Add(v1, v2);
		Vector3 resultSubtract = Subtract(v1, v2);
		Vector3 resultMultiply = Multiply(k, v1);
		float resultDot = Dot(v1, v2);
		float resultLength = Length(v1);
		Vector3 resultNormalize = Normalize(v2);


		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		vectorScreenprintf(0, 0, resultAdd, "  : Add");
		vectorScreenprintf(0, 60, resultSubtract, "  : Sub");
		vectorScreenprintf(0, 120, resultMultiply, "  : Multi");
		Novice::ScreenPrintf(0, 180, "%.02f  : Dot", resultDot);
		Novice::ScreenPrintf(0, 240, "%.02f  : Length", resultLength);
		vectorScreenprintf(0, 300, resultNormalize, "  : Normalize");

	



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
