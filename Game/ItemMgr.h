//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   ItemMgr.h
//!
//! @brief  ItemMgrクラスの宣言
//!
//! @date   2016.09.15
//!
//! @author Miyu Hara
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

/* 二重インクルードの防止 */
#pragma once


/* インクルードファイル */
#include "Item.h"
#include "Common.h"
#include "GamePlay.h"


/* クラスの宣言 */
class ItemMgr
{
public:
	ItemMgr(void);						// コンストラクタ

	void Init(void);														// 初期化
	void LoadGraphic(const char *file_name1, const char *file_name2);		// メモリに画像を読み込む
	void Update(const int time_limit);										// 更新
	void Draw(void);														// 描画

	void AllDelete(void);				// 全て消去
	void AllResetSpeed(void);			// 全ての速度をリセット

	Item m_item[MAX_ITEM] = {
		{ 33, 48, ITEM_X, ITEM_Y, 0.0f, 7.0f },
		{ 33, 48, ITEM_X, ITEM_Y, 0.0f, 7.0f },
		{ 33, 48, ITEM_X, ITEM_Y, 0.0f, 7.0f },
		{ 33, 48, ITEM_X, ITEM_Y, 0.0f, 7.0f } };		// アイテム(※一気に初期化したい・・・)

private:
	char stage[MAX_STAGE_FILESIZE];				// ステージデータ(※動的確保したい・・・)
	int pos_start = 0;							// スタート地点

	int grp_colditem_handle;					// グラフィックハンドル(冷たい)
	int grp_hotitem_handle;						// グラフィックハンドル(温かい)
};