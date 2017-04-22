//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Face.h
//!
//! @brief  Faceクラスの宣言
//!
//! @date   2016.09.05
//!
//! @author Miyu Hara
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

/* 二重インクルードの防止 */
#pragma once


/* インクルードファイル */
#include "Object.h"


/* クラスの宣言 */
class Face :public Object
{
public:
	Face(int w, int h, float px, float py, float sx, float sy);			// コンストラクタ
	
	void LoadGraphic(const char *file_name1, const char *file_name2, const char *fine_name3);		// メモリに画像を読み込む
	void Update(const int player_life);										// 更新

private:
	int grp_fine_handle;		// グラフィックハンドル（ノーマル）
	int grp_caution_handle;		// グラフィックハンドル（注意）
	int grp_danger_handle;		// グラフィックハンドル（危険）
};