//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GamePlay.h
//!
//! @brief  ゲームプレイ関連のヘッダファイル
//!
//! @date   2016.09.05
//!
//! @author Miyu Hara
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

/* 二重インクルードの防止 */
#pragma once


/* インクルードファイル */
#include "Common.h"


/* マクロの定義 */
// マップ関係
#define PLAYER_X (CHIP_SIZE * 15)		// プレイヤーのＸ座標の初期値
#define PLAYER_Y (CHIP_SIZE * 26)		// プレイヤーのＹ座標の初期値
#define LIFE_X (2 * (CHIP_SIZE * 2))	// ライフのＸ座標
#define LIFE_Y (1 * (CHIP_SIZE * 2))	// ライフのＹ座標
#define FACE_X (CHIP_SIZE)				// 顔グラのＸ座標
#define FACE_Y (CHIP_SIZE)				// 顔グラのＹ座標
#define BALLOON_X (CHIP_SIZE - 8.0f)		// 吹き出しのＸ座標
#define BALLOON_Y (CHIP_SIZE * 5)		// 吹き出しのＹ座標
#define ITEM0_X (CHIP_SIZE * 7)			// レーン０のＸ座標
#define ITEM1_X (CHIP_SIZE * 15)		// レーン１のＸ座標
#define ITEM2_X (CHIP_SIZE * 23)		// レーン２のＸ座標
#define ITEM3_X (CHIP_SIZE * 31)		// レーン３のＸ座標
#define ITEM_X (0.0f)					// アイテムのＸ座標の初期値
#define ITEM_Y (0.0f)					// アイテムのＹ座標の初期値

// プレイヤー情報
#define MAX_LIFE (10)		//ライフの最大値

// アイテム情報
#define MAX_ITEM (4)		// アイテムの最大数

// 選択情報
#define ARROW_LEFT  (103)	// 左のＸ座標
#define ARROW_RIGHT (203)	// 右のＸ座標

// その他
#define MAX_TIME_LIMIT (30)			// 制限時間


/* 列挙型の定義 */
enum PLAY_SCENE
{
	PLAY_EXPLAN1,		// 説明１
	PLAY_EXPLAN2,		// 説明２
	PLAY_PLAY,			// プレイ(メイン)。名前おかしい・・・
	PLAY_CLEAR,			// ゲームクリア
	PLAY_OVER			// ゲームオーバー
};


/* 関数のプロトタイプ宣言 */
void InitializePlay(void);			// ゲームプレイの初期化処理
void UpdatePlay(void);				// ゲームプレイの更新処理
void RenderPlay(void);				// ゲームプレイの描画処理
void FinalizePlay(void);			// ゲームプレイの終了処理

bool IsFinished(void);				// ゲームの終了判定
void InitGameData(void);			// データをまとめて初期化
void ResetAllFlag(void);			// フラグを全部リセットする