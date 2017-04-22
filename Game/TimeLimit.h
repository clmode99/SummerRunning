//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   TimeLimit.h
//!
//! @brief  TimeLimitクラスの宣言
//!
//! @date   2016.09.02
//!
//! @author Miyu Hara
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

/* 二重インクルードの防止 */
#pragma once


/* クラスの宣言 */
class TimeLimit
{
public:
	TimeLimit(void);		// コンストラクタ
	
	void LoadFont(const char *font_name);	// フォントを読み込む

	void Update(void);		// 更新
	void Draw(void);		// 描画

	int GetTimeLimit(void);		// 制限時間を取得する
	void ResetTimeLimit(void);	// 制限時間をリセットする
	
private:
	int time_limit;		// 制限時間
	int font_handle;	// フォントハンドル
};