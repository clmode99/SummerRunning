//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Object.h
//!
//! @brief  Objectクラスの宣言
//!
//! @date   2016.08.12
//!
//! @author Miyu Hara
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

/* 二重インクルードの防止 */
#pragma once


/* クラスの宣言 */
class Object
{
public:
	Object();													// コンストラクタ(引数なし。全部0で初期化。※デフォルト引数0にすればこれいらないかな・・・)
	Object(int w, int h, float px, float py, float sx, float sy);	// コンストラクタ(引数あり)

	void LoadGraphic(const char *file_name);	// メモリに画像を読み込む
	virtual void Update();				// 更新
	virtual void Draw();					// 描画

	// 座標取得系
	float GetLeftBorder() const;		// 左端
	float GetRightBorder() const;		// 右端
	float GetUpBorder() const;			// 上端
	float GetDownBorder() const;		// 下端

protected:
	int grp_handle;		// グラフィックハンドル
	int grp_width;		// 画像の幅
	int grp_height;		// 画像の高さ
	float pos_x;		// 座標Ｘ
	float pos_y;		// 座標Ｙ
	float spd_x;		// 速度Ｘ
	float spd_y;		// 速度Ｙ
};