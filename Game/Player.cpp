//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Player.cpp
//!
//! @brief  Playerクラスの定義
//!
//! @date   2016.08.12
//!
//! @author Miyu Hara
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

/* インクルードファイル */
#include "Player.h"
#include "GamePlay.h"
#include "Common.h"


/* クラスの定義 */
/* ----------------------------------------
関数名：Player::Player
概要　：Playerクラスのコンストラクタ
引数　：Objectクラスのメンバ、ライフ(int)
戻り値：なし
---------------------------------------- */
Player::Player(int w, int h, float px, float py, float sx, float sy, int l)
	: Object(w, h, px, py, sx, sy), life(l)
{}

/* ------------------------------------------------------------------------------
関数名：Player::LoadGraph
概要　：メモリに指定された画像を読み込み、グラフィックハンドルメンバに代入する
引数　：ファイル名(char*)
戻り値：なし(void)
------------------------------------------------------------------------------ */
void Player::LoadGraphic(const char *file_name1, const char *file_name2, const char *file_name3)
{
	grp_normal_handle = LoadGraph(file_name1);		// 正面
	grp_left_handle = LoadGraph(file_name2);		// 左
	grp_right_handle = LoadGraph(file_name3);		// 右
}

/* ----------------------------------------
関数名：Player::Update
概要　：更新する
引数　：制限時間(const int)
戻り値：なし(void)
---------------------------------------- */
void Player::Update(const int time_limit)
{
	// ↓※処理はそれぞれ関数化してもいいかな↓

	/* 移動処理 */
	if (PressKeyTrigger(PAD_INPUT_LEFT) == true)
	{
		if (pos_x > (7 * CHIP_SIZE))		// 左ボーダーライン(※定数)
		{
			pos_x -= (float)8 * CHIP_SIZE;
		}
	}
	if (PressKeyTrigger(PAD_INPUT_RIGHT) == true)
	{
		if (pos_x < (31 * CHIP_SIZE))		// 右ボーダーライン(※定数)
		{
			pos_x += (float)8 * CHIP_SIZE;
		}
	}

	/* ライフ処理 */
	now_time = GetPassageTime() / 1000;
	if (now_time != old_time)
	{
		life--;
		old_time = now_time;
	}

	/* アニメーション処理 */
	if (time_limit < 10)			// 10秒切ったら速くなる
	{
		Animation(FAST);
	}
	else							// ふつー
	{
		Animation(NORMAL);
	}
}

/* ----------------------------------------
関数名：Player::Draw
概要　：描画する
引数　：なし(void)
戻り値：なし(void)
---------------------------------------- */
void Player::Draw(void)
{
	if (is_damage == true)
	{
		SetDrawBlendMode(DX_BLENDMODE_ADD, 127);		// 白っぽい表現
		is_damage = false;
	}

	DrawGraph(static_cast<int>(pos_x), static_cast<int>(pos_y), grp_handle, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);		// 元に戻す
}

/* ----------------------------------------
関数名：Player::GetLife
概要　：ライフを取得する
引数　：なし(void)
戻り値：ライフ(int)
---------------------------------------- */
int Player::GetLife(void)
{
	return life;
}

/* ----------------------------------------
関数名：Player::Heal
概要　：ライフを回復する
引数　：なし(void)
戻り値：なし(void)
---------------------------------------- */
void Player::Heal(void)
{
	life += 2;	// 回復

	// 最大値以上は回復しない処理
	if (life > MAX_LIFE)
	{
		life = MAX_LIFE;
	}
}

/* ----------------------------------------
関数名：Player::Damage
概要　：ライフにダメージを与える
引数　：なし(void)
戻り値：なし(void)
---------------------------------------- */
void Player::Damage(void)
{
	is_damage = true;

	life -= 1;					// ダメージ

	// ０だったらこれ以上は下がらない
	if (life < 0)
	{
		life = 0;
	}
}

/* ----------------------------------------
関数名：Player::ResetLife
概要　：ライフをリセットする
引数　：なし(void)
戻り値：なし(void)
---------------------------------------- */
void Player::ResetLife(void)
{
	life = MAX_LIFE + 1;	// ＋１は調整
}


/* ----------------------------------------
関数名：Player::Advance
概要　：前に進む
引数　：なし(void)
戻り値：なし(void)
---------------------------------------- */
void Player::Advance(void)
{
	pos_y -= 5.0f;
	Animation(FAST);
}

/* ----------------------------------------
関数名：Player::Animation
概要　：動きをつける
引数　：アニメーションの種類(ANIMATION_SPEED)
戻り値：なし(void)
---------------------------------------- */
void Player::Animation(ANIMATION_SPEED speed)
{
	/* ローカル変数の初期化 */
	int animation_time = 0;		// どれくらいのタイミングで動くか


	/* 種類によって動くタイミングが変わる処理 */
	switch (speed)
	{
	case NORMAL:
		animation_time = (GetPassageTime() / 125) % 4;		// 125ミリ秒ごとにアニメーション
		break;

	case FAST:
		animation_time = (GetPassageTime() / 100) % 4;		// 100ミリ秒ごとにアニメーション
		break;

	default:												// ここにくるのはおかしい
		Error();
		break;
	}

	/* アニメーション処理 */
	switch (animation_time)
	{
	case NORMAL0: case NORMAL1:				//正面
		grp_handle = grp_normal_handle;
		break;

	case LEFT:								// 左
		grp_handle = grp_left_handle;
		break;

	case RIGHT:								// 右
		grp_handle = grp_right_handle;
		break;

	default:								// ここにくるのはおかしい
		Error();
		break;
	}
}

/* ----------------------------------------
関数名：Player::ResetPositionX
概要　：Ｘ座標を初期状態に戻す
引数　：なし(void)
戻り値：なし(void)
---------------------------------------- */
void Player::ResetPositionX(void)
{
	pos_x = PLAYER_X;
}

/* ----------------------------------------
関数名：Player::ResetPositionY
概要　：Ｙ座標を初期状態に戻す
引数　：なし(void)
戻り値：なし(void)
---------------------------------------- */
void Player::ResetPositionY(void)
{
	pos_y = SCREEN_HEIGHT;
}

/* ----------------------------------------
関数名：Player::ResetPositionAll
概要　：ＸＹ座標を初期状態に戻す
引数　：なし(void)
戻り値：なし(void)
---------------------------------------- */
void Player::ResetPositionAll(void)
{
	ResetPositionX();
	ResetPositionY();
}
