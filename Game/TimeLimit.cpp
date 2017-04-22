//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   TimeLimit.cpp
//!
//! @brief  TimeLimitクラスの定義
//!
//! @date   2016.09.02
//!
//! @author Miyu Hara
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

/* インクルードファイル */
#include "TimeLimit.h"
#include "Common.h"
#include "GamePlay.h"


/* クラスの定義 */
/* ----------------------------------------
関数名：TimeLimit::TimeLimit
概要　：TimeLimitクラスのコンストラクタ
引数　：なし(void)
戻り値：なし
---------------------------------------- */
TimeLimit::TimeLimit(void)
	:time_limit(MAX_TIME_LIMIT), font_handle(0)
{}

/* ----------------------------------------
関数名：TimeLimit::LoadFont
概要　：フォントデータをメモリに読み込む
引数　：フォント名(const char*)
戻り値：なし(void)
---------------------------------------- */
void TimeLimit::LoadFont(const char *font_name)
{
	font_handle = CreateFontToHandle(font_name, 23, 5, DX_FONTTYPE_ANTIALIASING);
}

/* ----------------------------------------
関数名：TimeLimit::Update
概要　：更新処理
引数　：なし(void)
戻り値：なし(void)
---------------------------------------- */
void TimeLimit::Update(void)
{
	time_limit = MAX_TIME_LIMIT - (GetPassageTime() / 1000);
}

/* ----------------------------------------
関数名：TimeLimit::Draw
概要　：描画処理
引数　：なし(void)
戻り値：なし(void)
---------------------------------------- */
void TimeLimit::Draw(void)
{
	if (time_limit <= 5)
	{
		DrawFormatStringToHandle(595, 10, GetColor(255, 0, 0), font_handle, "%02d", time_limit);
	}
	else
	{
		DrawFormatStringToHandle(595, 10, GetColor(0, 0, 0), font_handle, "%02d", time_limit);
	}
}

/* ----------------------------------------
関数名：TimeLimit::GetTimeLimit
概要　：制限時間を取得する
引数　：なし(void)
戻り値：制限時間(int)
---------------------------------------- */
int TimeLimit::GetTimeLimit(void)
{
	return time_limit;
}

/* ----------------------------------------
関数名：TimeLimit::ResetTimeLimit
概要　：制限時間をリセットする
引数　：なし(void)
戻り値：なし(void)
---------------------------------------- */
void TimeLimit::ResetTimeLimit(void)
{
	time_limit = MAX_TIME_LIMIT;
}
