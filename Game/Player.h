//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Player.h
//!
//! @brief  Playerクラスの宣言
//!
//! @date   2016.08.12
//!
//! @author Miyu Hara
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

/* 二重インクルードの防止 */
#pragma once


/* インクルードファイル */
#include "Object.h"


/*　列挙型の宣言*/
enum ANIMATION_SPEED
{
	NORMAL,		// ふつー
	FAST		// はやい
};

enum ANIMATION_KIND
{
	NORMAL0,	// ノーマル０。同じだけど中身は違う
	LEFT,		// 左
	NORMAL1,	// ノーマル１。同じだけど中身は違う
	RIGHT,		// 右
};

/* クラスの宣言 */
class Player:public Object
{
public:
	Player(int w, int h, float px, float py, float sx, float sy, int l);		// コンストラクタ
	
	void LoadGraphic(const char *file_name1, const char *file_name2, const char *file_name3);	// メモリに画像を読み込む
	void Update(const int time_limit);															// 更新
	void Draw(void);																			// 描画

	int GetLife(void);		// ライフを取得する
	void Heal(void);		// ライフを回復する
	void Damage(void);		// ライフにダメージを与える
	void ResetLife(void);	// ライフをリセットする

	void Advance(void);							// 前に進む
	void Animation(ANIMATION_SPEED speed);		// 動きをつける
	
	void ResetPositionX(void);		// Ｘ座標を初期状態に戻す
	void ResetPositionY(void);		// Ｙ座標を初期状態に戻す
	void ResetPositionAll(void);	// ＸＹ座標を初期状態に戻す

private:
	
	int life;				// ライフ

	int now_time;			// 今の時間(秒)。一時変数
	int old_time;			// １秒前の時間(秒）。一時変数

	int grp_normal_handle;	// グラフィックハンドル（正面）
	int grp_left_handle;	// グラフィックハンドル（左）
	int grp_right_handle;	// グラフィックハンドル（右）

	bool is_damage;			// ダメージを受けたか
};