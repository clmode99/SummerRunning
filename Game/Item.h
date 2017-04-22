//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Item.h
//!
//! @brief  Itemクラスの宣言
//!
//! @date   2016.09.15
//!
//! @author Miyu Hara
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

/* 二重インクルードの防止 */
#pragma once


/* インクルードファイル */
#include "Object.h"


/* 列挙型の宣言 */
enum KIND
{
	COLD,
	HOT,
	NONE		// 初期化用
};


/* クラスの宣言 */
class Item :public Object
{
public:
	Item(int w, int h, float px, float py, float sx, float sy);		// コンストラクタ
	
	void Update(void);			// 更新
	void Draw(void);			// 描画

	void Create(const int lane, const int grp_handle,const KIND kind);	// 作る
	void Delete(void);													// 消す

	void UpSpeed(void);				// 速度を上げる
	void ResetSpeed(void);			// 速度をリセットする

	bool IsExistState(void);		// 存在するか
	KIND GetKind(void);				// 種類を取得する

	bool IsFadeOut(void);			// フェードアウトしてるか
	void StartFadeout(void);		// フェードアウト開始 (※関数名にセンスがない・・・）

private:
	bool exist_state;			// 存在するか
	KIND kind;					// 種類

	bool is_fadeout;						// フェードアウトフラグ
	int opacity;							// 画像の不透明度(０～２５５)。０＝透明、２５５＝完全不透明
	static const int MAX_OPACITY = 255;		// 不透明度の最大値。静的にすることでインスタンス生成してなくても使えるようにする
};