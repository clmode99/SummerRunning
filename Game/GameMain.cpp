//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GameMain.cpp
//!
//! @brief  ゲーム全体関連のソースファイル
//!
//! @date   2016.08.07
//!
//! @author Miyu Hara
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

/* インクルードファイル */
#include "GameMain.h"
#include "GameLogo.h"
#include "GameTitle.h"
#include "GameCredit.h"
#include "GamePlay.h"
#include "Common.h"


/* グローバル変数の定義 */
static SCENE g_scene=PLAY;				// シーン情報
SCENE g_next_scene = g_scene;		// 次のシーン情報


/* 関数の定義 */
/* ----------------------------------------
関数名：InitializeGame
概要　：初期化処理
引数　：なし(void)
戻り値：なし(void)
---------------------------------------- */
void InitializeGame(void)
{
	InitCommon();
	SetMouseDispFlag(FALSE);
}

/* ----------------------------------------
関数名：UpdateGame
概要　：更新処理
引数　：なし(void)
戻り値：なし(void)
---------------------------------------- */
void UpdateGame(void)
{
	/* ローカル変数の初期化 */
	// シーン管理
	void(*p_update_scene[])(void) = { UpdateLogo,UpdateTitle,UpdateCredit,UpdatePlay };		// 更新のシーン管理
	

	/* 処理 */
	UpdateCommon();

	if (g_scene != g_next_scene)	// シーン切り替え調整
	{
		g_scene = g_next_scene;
	}

	p_update_scene[g_scene]();		// シーン管理


}

/* ----------------------------------------
関数名：RenderGame
概要　：描画処理
引数　：なし(void)
戻り値：なし(void)
---------------------------------------- */
void RenderGame(void)
{
	/* ローカル変数の初期化 */
	void(*p_render_scene[])(void) = { RenderLogo,RenderTitle,RenderCredit,RenderPlay };		// 描画のシーン管理
	

	/* 処理 */
	p_render_scene[g_scene]();		// シーン管理
}

/* ----------------------------------------
関数名：FinalizeGame
概要　：終了処理
引数　：なし(void)
戻り値：なし(void)
---------------------------------------- */
void FinalizeGame(void)
{
	;
}
