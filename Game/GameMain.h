//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GameMain.h
//!
//! @brief  ゲーム全体関連のヘッダファイル
//!
//! @date   2016.08.05
//!
//! @author Miyu Hara
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

/* 二重インクルードの防止 */
#pragma once


/* マクロの定義 */
// ゲームタイトル
#define GAME_TITLE "SUMMER RUNNING"


/* 関数のプロトタイプ宣言 */
void InitializeGame(void);	// 初期化処理
void UpdateGame(void);		// 更新処理
void RenderGame(void);		// 描画処理
void FinalizeGame(void);	// 終了処理
