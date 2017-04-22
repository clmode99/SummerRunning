//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GameLogo.cpp
//!
//! @brief  ゲームロゴ関連のソースファイル
//!
//! @date   2016.09.10
//!
//! @author Miyu Hara
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

/* インクルードファイル */
#include "GameLogo.h"
#include "Common.h"
#include "Bg.h"


/* グローバル変数の定義 */
static Bg logo(BG_NORMAL);						// ロゴ
static bool is_init = false;		// 初期化
extern SCENE g_next_scene;			// シーン管理


/* ※↓前回のシューティングのロゴ部分丸ごとコピペなので、整理したい↓*/

/* 関数の定義 */
/* ----------------------------------------
関数名：UpdateLogo
概要　：ゲームロゴの更新処理
引数　：なし(void)
戻り値：なし(void)
---------------------------------------- */
void UpdateLogo(void)
{
	/* ローカル変数の初期化 */
	static int start_time_ms = 0, now_time_ms = 0;	// 時間関係。ミリ秒単位
	static int brightness = 0;						// 描画輝度
	static int revised_brightness = 0;				// 描画輝度の調整値
	static int cnt_frame = 0;						// 1フレームごとにインクリメント
	static int press_key_time_ms = 0;				// キーを押された瞬間の時間
	static int press_key_brightness = 0;			// キーを押された瞬間の描画輝度
	static bool is_press_key = false;				// キーを押されたか
	static bool is_normal_fadeout = false;			// 通常フェードアウト時か


	/* 初期化 */
	if (is_init == false)
	{
		// 繰り返し使うローカル変数
		start_time_ms = GetNowCount();

		// 画像をメモリに読み込む
		logo.LoadGraphic("Resources\\Images\\my_logo.png");

		is_init = true;
	}

	// 時間取得
	now_time_ms = GetNowCount() - start_time_ms;

	// 通常フェードアウト
	if (is_press_key == false)
	{
		revised_brightness = (int)(MAX_BRIGHTNESS / 60);

		switch (now_time_ms / 1000)
		{
			// フェードイン
		case 0:
			brightness = cnt_frame * revised_brightness;
			break;

			// 維持
		case 1:
		case 2:
			brightness = MAX_BRIGHTNESS;
			break;

			// フェードアウト
		case 3:
		case 4:
			// 最初だけ初期化
			if (is_normal_fadeout == false)
			{
				cnt_frame = 0;
				is_normal_fadeout = true;
			}
			brightness = MAX_BRIGHTNESS - (cnt_frame * revised_brightness);
			break;

		default:
			DrawString(0, 20, "エラー", GetColor(255, 0, 0));
			break;
		}

		// キー判定
		if (CheckHitKeyAll())
		{
			// 強制フェードアウトの初期化
			press_key_time_ms = now_time_ms;
			press_key_brightness = brightness;
			cnt_frame = 0;
			is_press_key = true;
		}
	}
	// 強制フェードアウト
	else
	{
		revised_brightness = (int)press_key_brightness / 40;	// 40が調整値として丁度よかった

		// キーを押されたときから1秒以内ならフェードアウト
		if ((now_time_ms >= press_key_time_ms) && (now_time_ms <= (press_key_time_ms + 1000)))
		{
			brightness = press_key_brightness - (cnt_frame * revised_brightness);
		}
	}

	SetDrawBright(brightness, brightness, brightness);

	cnt_frame++;

	// タイトルへ
	// 通常時：5秒経過、強制時：フェードアウトした時間から0.5秒経過
	if ((now_time_ms >= (5 * 1000)) || ((is_press_key == true) && (now_time_ms >= (press_key_time_ms + 1500))))
	{
		g_next_scene = TITLE;
	}

}

/* ----------------------------------------
関数名：RenderLogo
概要　：ゲームロゴの描画処理
引数　：なし(void)
戻り値：なし(void)
---------------------------------------- */
void RenderLogo(void)
{
	if (g_next_scene == LOGO)
	{
		logo.Draw();
	}
	else
	{
		SetDrawBright(MAX_BRIGHTNESS, MAX_BRIGHTNESS, MAX_BRIGHTNESS);		// 戻しておく
	}
}
