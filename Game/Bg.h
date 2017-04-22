//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Bg.h
//!
//! @brief  Bgクラスの宣言
//!
//! @date   2016.10.03
//!
//! @author Miyu Hara
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

/* 二重インクルードの防止 */
#pragma once


/* インクルードファイル */
#include "Object.h"


/* 列挙型の宣言 */
enum BG_TYPE
{
	BG_NORMAL,
	SCROLL
};


/* クラスの宣言 */
class Bg :public Object
{
public:
	Bg(BG_TYPE type);		// コンストラクタ
	
	void Update(const int time_limit);		// 更新
	void Draw(void);						// 描画

	void ResetPosition(void);		// 座標をリセットする
	void UpSpeed(void);				// 速度を上げる

private:
	BG_TYPE type;	// スクロールするかしないか
	int grp_y;		// 画面上の画像Ｙ１
	int grp_y2;		// 画面上の画像Ｙ２
	int spd_y;		// スクロールさせる速度Ｙ
	
	bool is_draw1;		// 画像１を描画するか
	bool is_draw2;		// 画像２を描画するか
};