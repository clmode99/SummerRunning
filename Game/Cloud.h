//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Cloud.h
//!
//! @brief  Cloudクラスの宣言
//!
//! @date   2016.09.09
//!
//! @author Miyu Hara
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

/* 二重インクルードの防止 */
#pragma once


/* インクルードファイル */
#include "Object.h"


/* クラスの宣言 */
class Cloud :public Object
{
public:
	Cloud(int w, int h, float px, float py, float sx, float sy);		// コンストラクタ
	
	void Update(void);			// 更新
};