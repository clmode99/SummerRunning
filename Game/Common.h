//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Common.h
//!
//! @brief  共通して使うもの
//!
//! @date   2016.08.19
//!
//! @author Miyu Hara
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

/* 二重インクルードの防止 */
#pragma once


/* インクルードファイル */
#include "Object.h"


/* マクロの定義 */
// ゲーム画面
#define SCREEN_WIDTH  (640)		// 画面の幅
#define SCREEN_HEIGHT (480)		// 画面の高さ

#define CHIP_SIZE     (16)		// マップチップの大きさ

#define MAX_STAGE_FILESIZE (500)		// ステージファイル最大値(※ここに置くのは不適切な気がするし、動的確保したい・・・)


/* 列挙型の定義 */
enum SCENE
{
	LOGO,
	TITLE,
	CREDIT,
	PLAY,
};


/* 関数のプロトタイプ宣言 */
void InitCommon(void);						// 初期化
void UpdateCommon(void);					// 更新

// ライブラリ(？)関数
//	キー処理系
bool PressKeyTrigger(const int direction);					// キー処理(トリガー)

//	時間
int GetPassageTime(void);									// 初期化してからの経過時間(ミリ秒)を取得する

//	当たり判定
bool CollisionObject(const Object *object1, const Object *object2);		// Object型同士の当たり判定

//	ファイル処理
void LoadFile(const char *file_name, char *data);			// ファイルを読み込み、指定した文字列に代入する

//	文字列処理
void CopyString(char copy_1[], const char copy_2[]);		// 文字列をコピーする
int GetStringLength(const char string[]);					// 文字列の長さを取得する
int ConvertNumCharToInt(const char c);						// 数字→数値に変換する

// 数値変換処理
float CutDecimalPoint(const float data, const int place);	// 特定の小数点第何位未満を切り捨てる

//	エラー
void Error(void);			// エラー検出