//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Life.h
//!
//! @brief  Lifeクラスの宣言
//!
//! @date   2016.08.19
//!
//! @author Miyu Hara
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

/* 二重インクルードの防止 */
#pragma once


/* インクルードファイル */
#include "Object.h"


/* クラスの宣言 */
class Life :public Object
{
public:
	Life(int w, int h, float px, float py, float sx, float sy);				// コンストラクタ
	
	void LoadGraphic(const char *file_name1, const char *file_name2);		// メモリに画像を読み込む
	void Draw(const int player_life);										// 描画

private:
	int grp_damage_handle;			// グラフィックハンドル(ダメージ時)
};