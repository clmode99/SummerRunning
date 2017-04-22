//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GameCredit.cpp
//!
//! @brief  ゲームクレジット関連のソースファイル
//!
//! @date   2016.09.09
//!
//! @author Miyu Hara
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

/* インクルードファイル */
#include "GameCredit.h"
#include "Common.h"
#include "Bg.h"
#include "Sound.h"


/* グローバル変数の定義 */
static Bg credit(BG_NORMAL);				// クレジット
static Sound page;				// ページめくる音

// その他
static bool is_init = false;		// 初期化
extern SCENE g_next_scene;			// シーン情報


/* 関数の定義 */
/* ----------------------------------------
関数名：UpdateCredit
概要　：ゲームクレジットの更新処理
引数　：なし(void)
戻り値：なし(void)
---------------------------------------- */
void UpdateCredit(void)
{
	/* 初期化 */
	if (is_init == false)
	{
		// 画像をメモリに読み込む
		credit.LoadGraphic("Resources\\Images\\credit.png");

		// サウンドをメモリに読み込む
		page.LoadSound("Resources\\Sounds\\page.mp3");

		is_init = true;
	}

	// タイトルへ戻る
	if (PressKeyTrigger(PAD_INPUT_10) == true)
	{
		g_next_scene = TITLE;
		page.Play(SE);
	}

}

/* ----------------------------------------
関数名：RenderCredit
概要　：ゲームクレジットの描画処理
引数　：なし(void)
戻り値：なし(void)
---------------------------------------- */
void RenderCredit(void)
{
	credit.Draw();
}
