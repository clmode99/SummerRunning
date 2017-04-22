//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Common.cpp
//!
//! @brief  共通して使うものの定義
//!
//! @date   2016.08.31
//!
//! @author Miyu Hara
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

/* インクルードファイル */
#include "Common.h"
#include "Object.h"
#include <fstream>	// ifstream


/* グローバル変数の定義 */
// キー情報
static int g_key_code;		// キー情報
static int g_key_code_old;	// １フレーム前のキー情報

// 時間
static int g_time_ms;			// ゲーム開始時から経過した時間(ミリ秒)
static int g_now_time_ms;		// 今の時間(ミリ秒)。一時変数
static int g_start_time_ms;		// InitCommon()時の時間(ミリ秒)。一時変数


/* 関数の定義 */
/* ----------------------------------------
関数名：InitCommon
概要　：初期化する
引数　：なし(void)
戻り値：なし(void)
---------------------------------------- */
void InitCommon(void)
{
	g_time_ms = 0;
	g_start_time_ms = GetNowCount();	// 時間を取得
}

/* ----------------------------------------
関数名：UpdateCommon
概要　：更新する
引数　：なし(void)
戻り値：なし(void)
---------------------------------------- */
void UpdateCommon(void)
{
	// キー情報の更新
	g_key_code_old = g_key_code;
	g_key_code = GetJoypadInputState(DX_INPUT_KEY);

	// 時間の更新
	g_now_time_ms = GetNowCount();
	g_time_ms = g_now_time_ms - g_start_time_ms;
}

/* ----------------------------------------------------------------------
関数名：PressKeyTrigger
概要　：キー処理(トリガー)
引数　：トリガー判定したいキー(GetJoypad～のマスク)
戻り値：押されてる(true)、押されてない or 同じキー押しっぱなし(false)
---------------------------------------------------------------------- */
bool PressKeyTrigger(const int direction)
{
	if ((g_key_code & direction) && (g_key_code != g_key_code_old))
	{
		return true;
	}
	else
	{
		return false;
	}
}

/* ----------------------------------------------------------------------
関数名：GetPassageTime
概要　：初期化してからの経過時間(ミリ秒)を取得する
引数　：void(なし)
戻り値：経過時間(int)
---------------------------------------------------------------------- */
int GetPassageTime(void)
{
	return g_time_ms;
}

/* ----------------------------------------------------------------------
関数名：CollisionObject
概要　：Object型のオブジェクト同士の当たり判定
引数　：当たり判定したいオブジェクト(const Object*, const Object*)
戻り値：当たってる(true)、当たってない(false)
---------------------------------------------------------------------- */
bool CollisionObject(const Object *object1, const Object *object2)
{
	if ((object1->GetLeftBorder() <= object2->GetRightBorder()) &&
		(object1->GetRightBorder() >= object2->GetLeftBorder()) &&
		(object1->GetUpBorder() <= object2->GetDownBorder()) &&
		(object1->GetDownBorder() >= object2->GetUpBorder()))
	{
		return true;
	}
	else
	{
		return false;
	}
}

/* -------------------------------------------------------------------------------------
関数名：LoadFile
概要　：ファイルを読み込み、指定した文字列に代入する
引数　：読み込むファイル名(const char*)、書き込む文字列(char*)
戻り値：なし(void)
※参考書籍：「ゲームプログラマになる前に覚えておきたい技術」p.20～p.21
------------------------------------------------------------------------------------- */
void LoadFile(const char *file_name, char *data)
{
	/* ローカル変数、オブジェクトの初期化 */
	ifstream input_file(file_name, ifstream::binary);	// ファイル処理のためのオブジェクト？
	int file_size = 0;									// ファイルサイズ


	// ファイルサイズ取得
	input_file.seekg(0, ifstream::end);
	file_size = static_cast<int>(input_file.tellg());	// 最後の位置＝ファイルサイズ
	
	// ※デバッグ処理(最終的には消すこと)--------------------------------------
	// 読み込んだファイルサイズがファイル最大値を超えたときはエラー
	if (file_size > MAX_STAGE_FILESIZE)
	{
		Error();
	}
	// ------------------------------------------------------------------------


	// ファイルを読み込む
	char *file_image = new char[file_size];		// ファイルの中身(この位置じゃないと動的確保できない)
	input_file.seekg(0, ifstream::beg);
	input_file.read(file_image, file_size);

	CopyString(data, file_image);

	delete[] file_image;	// newしたらdeleteする
}

/* -------------------------------------------------------------------------------------
関数名：CopyString
概要　：ある文字列に指定した文字列をコピーする。strcpyと同じ機能
引数　：コピー先の文字列(char[])、コピー元の文字列(const char[])
戻り値：なし(void)
------------------------------------------------------------------------------------- */
void CopyString(char copy_1[], const char copy_2[])
{
	for (int i = 0; copy_2[i] != '\0'; i++)
	{
		copy_1[i] = copy_2[i];
	}
}

/* -------------------------------------------------------------------------------------
関数名：GetStringLength
概要　：文字列の長さを取得する。strlenと同じ機能
引数　：長さを取得したい文字列(const char[])
戻り値：長さ(int)
------------------------------------------------------------------------------------- */
int GetStringLength(const char string[])
{
	/* ローカル変数の初期化 */
	int  length = 0;			// 文字列の長さ


	for (int i = 0; string[i] != '\0'; i++)		// iとlengthがほぼ一緒だけど、見やすさ重視で
	{
		length++;
	}

	return length;
}

/* -------------------------------------------------------------------------------------
関数名：ConvertNumCharToInt
概要　：数字→数値(整数)に変換する
引数　：数字(const char)
戻り値：数値(int)
------------------------------------------------------------------------------------- */
int ConvertNumCharToInt(const char c)
{
	return static_cast<int>(c - 48);	// '0' = 48だから
}

/* -------------------------------------------------------------------------------------
関数名：CutDecimalPoint
概要　：特定の小数第何位未満を切り捨てる
引数　：変換したい数値(const float)、特定の小数点第何位(const int)
戻り値：数値(float)
------------------------------------------------------------------------------------- */
float CutDecimalPoint(const float data, const int place)
{
	/* ローカル変数の初期化 */
	int temp = 1;
	int temp_data = 0;

	// 特定の第何位のところまでを整数にする
	for (int i = 1; i <= place; i++)
	{
		temp *= 10;
	}
	temp_data = static_cast<int>(data * temp);

	// 整数を実数に戻す。1.0fかけることで実数に変換してる
	return static_cast<float>(temp_data / (temp*1.0f));
}

/* ----------------------------------------------------------------------
関数名：Error
概要　：エラー時はここに飛んでくる
引数　：なし(void)
戻り値：なし(void)
---------------------------------------------------------------------- */
void Error(void)
{
	WaitKey();
}