//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   ItemMgr.cpp
//!
//! @brief  ItemMgrクラスの定義
//!
//! @date   2016.09.15
//!
//! @author Miyu Hara
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

/* インクルードファイル */
#include "ItemMgr.h"
#include "Common.h"


/* クラスの定義 */
/* ------------------------------------------------------------------------------
関数名：ItemMgr::ItemMgr
概要　：ItemMgrクラスのコンストラクタ
引数　：なし(void)
戻り値：なし
------------------------------------------------------------------------------ */
ItemMgr::ItemMgr(void)
{
	LoadFile("stage.txt", stage);	// ステージデータを読み込む
}

/* ------------------------------------------------------------------------------
関数名：ItemMgr::ItemMgr
概要　：初期化する
引数　：なし(void)
戻り値：なし(void)
------------------------------------------------------------------------------ */
void ItemMgr::Init(void)
{
	pos_start = 0;	

	// データのスタート地点を求める
	int new_line = 0;					// 改行カウンタ。一時変数

	for (int i = 0; new_line < 4; i++)	//４回改行したところが初期スタート地点
	{
		pos_start++;
		if (stage[i] == '\n')
		{
			new_line++;
		}
	}

	AllDelete();
	AllResetSpeed();
}

/* ------------------------------------------------------------------------------
関数名：ItemMgr::LoadGraphic
概要　：メモリに指定された画像を読み込み、グラフィックハンドルメンバに代入する
引数　：ファイル名(const char*, const char*)
戻り値：なし(void)
------------------------------------------------------------------------------ */
void ItemMgr::LoadGraphic(const char *file_name1, const char *file_name2)
{
	grp_colditem_handle = LoadGraph(file_name1);
	grp_hotitem_handle = LoadGraph(file_name2);
	/*for (int i = 0; i < MAX_ITEM; i++)
	{
		m_item[i].LoadGraphic(file_name);
	}*/
}

/* ------------------------------------------------------------------------------
関数名：ItemMgr::Update
概要　：更新処理
引数　：制限時間(const int)
戻り値：なし(void)
------------------------------------------------------------------------------ */
void ItemMgr::Update(const int time_limit)
{
	/* ローカル変数の初期化 */
	int appearance_time = 0;		// 出現時間(秒)
	int appearance_lane = 0;		// 出現レーン(０～３）
	char item_type = '\0';			// アイテムの種類。ファイルから読み込んだやつを入れておく。一時変数
	KIND item_kind = NONE;			// アイテムの種類。関数に渡す用。一時変数
	int grp_item_handle = 0;		// アイテムのグラフィックハンドル。一時変数
	const int STAGE_WIDTH = 8;		// ステージデータの幅


	/* 指定した時間になったら、飲み物を作る */
	for (int i = 0; stage[pos_start + (STAGE_WIDTH * i)] != '\0'; i++)			// 行
	{
		for (int j = 0; stage[pos_start + (STAGE_WIDTH * i + j)] != '\n'; j++)	// 列
		{
			// 出現時間
			if (j == 0)			// １０の位
			{
				appearance_time = (ConvertNumCharToInt(stage[pos_start + (j + STAGE_WIDTH * i)])) * 10;
			}
			if (j == 1)			// １の位
			{
				appearance_time += ConvertNumCharToInt(stage[pos_start + (j + STAGE_WIDTH * i)]);
			}

			// 出現レーン
			if (j == 3)
			{
				appearance_lane = ConvertNumCharToInt(stage[pos_start + (j + STAGE_WIDTH * i)]);
			}

			// アイテムの種類
			if (j == 5)
			{
				item_type = stage[pos_start + (j + STAGE_WIDTH * i)];		// このほうがわかりやすい・・・？
				
				if (item_type == 'C')
				{
					item_kind = COLD;
					grp_item_handle = grp_colditem_handle;
				}
				if (item_type == 'H')
				{
					item_kind = HOT;
					grp_item_handle = grp_hotitem_handle;
				}
			}
		}

		if (time_limit == appearance_time)
		{
			if (m_item[appearance_lane].IsExistState() == false)
			{
				m_item[appearance_lane].Create(appearance_lane, grp_item_handle, item_kind);
				pos_start += STAGE_WIDTH;		// スタート地点を更新する
			}
		}
	}


	/* 存在してる飲み物の更新 */
	for (int i = 0; i < MAX_ITEM; i++)
	{
		if (m_item[i].IsExistState() == true)
		{
			if (time_limit < 10)
			{
				m_item[i].UpSpeed();
			}

			m_item[i].Update();
		}
	}
}

/* ------------------------------------------------------------------------------
関数名：ItemMgr::Draw
概要　：描画処理
引数　：なし(void)
戻り値：なし(void)
------------------------------------------------------------------------------ */
void ItemMgr::Draw(void)
{
	for (int i = 0; i < MAX_ITEM; i++)
	{
		if (m_item[i].IsExistState() == true)
		{
			m_item[i].Draw();
		}
	}
}

/* ------------------------------------------------------------------------------
関数名：ItemMgr::AllDelete
概要　：描画してるものを全て消す
引数　：なし(void)
戻り値：なし(void)
------------------------------------------------------------------------------ */
void ItemMgr::AllDelete(void)
{
	for (int i = 0; i < MAX_ITEM; i++)
	{
		if (m_item[i].IsExistState() == true)
		{
			m_item[i].Delete();
		}
	}
}

/* ------------------------------------------------------------------------------
関数名：ItemMgr::AllResetSpeed
概要　：速度を全てリセットする
引数　：なし(void)
戻り値：なし(void)
------------------------------------------------------------------------------ */
void ItemMgr::AllResetSpeed(void)
{
	for (int i = 0; i < MAX_ITEM; i++)
	{
		m_item[i].ResetSpeed();
	}
}