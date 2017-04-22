//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GameTitle.cpp
//!
//! @brief  ゲームタイトル関連のソースファイル
//!
//! @date   2016.09.09
//!
//! @author Miyu Hara
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

/* インクルードファイル */
#include "GameTitle.h"
#include "Common.h"
#include "Sound.h"
#include "Bg.h"
#include "Cloud.h"


/* グローバル変数、オブジェクトの定義 */
static Bg bg(BG_NORMAL);																		// 背景
static Object title_logo(448, 64, CHIP_SIZE * 11, CHIP_SIZE * 2, 0.0f, 0.0f);		// タイトルロゴ
static Cloud cloud[MAX_CLOUD] = {
	{160,96,CHIP_SIZE * 16,CHIP_SIZE * 4,1.0f,0.0f},
	{160,96,640,CHIP_SIZE * 4,1.0f,0.0f} };				// 雲(※余力あればMgr)

// サウンド
static Sound title_bgm;				// タイトルＢＧＭ
static Sound decision;				// 決定音
static Sound cursor_move;			// カーソル移動
static Sound page;					// ページめくる音

// フォントハンドル
static int font_normal_handle = 0;			// ノーマル
static int font_arrow_handle = 0;			// 矢印

// その他
static int arrow_y = START_Y;		// 矢印のＹ座標
static bool is_init = false;		// 初期化
static int brightness = 0;			// 輝度(０～２５５)
static bool is_fadeout = false;		// フェードアウトするか
extern SCENE g_next_scene;			// シーン情報


/* 関数の定義 */
/* ----------------------------------------
関数名：UpdateTitle
概要　：ゲームタイトルの更新処理
引数　：なし(void)
戻り値：なし(void)
---------------------------------------- */
void UpdateTitle(void)
{
	/* 初期化 */
	if (is_init == false)
	{
		// 画像をメモリに読み込む
		bg.LoadGraphic("Resources\\Images\\title.png");
		title_logo.LoadGraphic("Resources\\Images\\title_logo.png");
		for (int i = 0; i < MAX_CLOUD; i++)
		{
			cloud[i].LoadGraphic("Resources\\Images\\cloud.png");
		}

		// フォントデータをメモリに読み込む
		font_normal_handle = CreateFontToHandle("メイリオ", 20, 5, DX_FONTTYPE_ANTIALIASING);
		font_arrow_handle = CreateFontToHandle("メイリオ", 20, 9, DX_FONTTYPE_ANTIALIASING);

		// サウンドをメモリに読み込む
		title_bgm.LoadSound("Resources\\Sounds\\title.mp3");
		decision.LoadSound("Resources\\Sounds\\decision.mp3");
		cursor_move.LoadSound("Resources\\Sounds\\cursor.mp3");
		page.LoadSound("Resources\\Sounds\\page.mp3");

		is_init = true;
	}

	/* 更新処理 */
	else
	{
		// 雲
		for (int i = 0; i < MAX_CLOUD; i++)
		{
			cloud[i].Update();
		}

		// 選択
		if (PressKeyTrigger(PAD_INPUT_UP) == true)
		{
			if (arrow_y != 305)
			{
				arrow_y -= 30;
				cursor_move.Play(SE);
			}
		}
		if (PressKeyTrigger(PAD_INPUT_DOWN) == true)
		{
			if (arrow_y != 365)
			{
				arrow_y += 30;
				cursor_move.Play(SE);
			}
		}
		// 決定
		if (PressKeyTrigger(PAD_INPUT_10) == true)
		{
			switch (arrow_y)
			{
			case START_Y:
				is_fadeout = true;
				decision.Play(SE);
				break;

			case CREDIT_Y:
				g_next_scene = CREDIT;
				page.Play(SE);
				break;

			case EXIT_Y:
				DxLib_End();
				exit(1);
				break;

			default:
				Error();
			}
		}

		if (is_fadeout == true)		// 画面を音をフェードアウトっぽくしてみる
		{
			static int bgm_volume = 100;			// ＢＧＭの音量(０～１００)
			
			// ＢＧＭがぶちっと切れるのが気にいらないので、音量変化でフェードアウト
			bgm_volume -= 2;
			title_bgm.ChangeVolume(bgm_volume);

			brightness -= 10;		// これは画面のフェードアウト

			if (bgm_volume <= 0)
			{
				is_fadeout = false;
				WaitTimer(100);
				title_bgm.Stop();
				title_bgm.ChangeVolume(100);
				bgm_volume = 100;
				g_next_scene = PLAY;
			}
		}
		else
		{
			brightness += 20;		// フェードインぽくしてみる
			if (brightness > 255)
			{
				brightness = 255;
			}
		}
	}

	if (g_next_scene != PLAY)		// ゲームプレイのほうに移ったら再生しないようにする
	{
		title_bgm.Play(BGM);
	}
}

/* ----------------------------------------
関数名：RenderTitle
概要　：ゲームタイトルの描画処理
引数　：なし(void)
戻り値：なし(void)
---------------------------------------- */
void RenderTitle(void)
{
	SetDrawBright(brightness, brightness, brightness);

	/* 後ろ→前へ描画する */
	bg.Draw();

	// ※関数化候補
	switch (arrow_y)
	{
	case START_Y:
		DrawFormatStringToHandle(242, START_Y, GetColor(0, 0, 0), font_normal_handle, "　 ＳＴＡＲＴ");
		DrawFormatStringToHandle(232, CREDIT_Y, GetColor(100, 100, 100), font_normal_handle, "　 ＣＲＥＤＩＴ");
		DrawFormatStringToHandle(252, EXIT_Y, GetColor(100, 100, 100), font_normal_handle, "　 ＥＸＩＴ");
		break;

	case CREDIT_Y:
		DrawFormatStringToHandle(242, START_Y, GetColor(100, 100, 100), font_normal_handle, "　 ＳＴＡＲＴ");
		DrawFormatStringToHandle(232, CREDIT_Y, GetColor(0, 0, 0), font_normal_handle, "　 ＣＲＥＤＩＴ");
		DrawFormatStringToHandle(252, EXIT_Y, GetColor(100, 100, 100), font_normal_handle, "　 ＥＸＩＴ");
		break;

	case EXIT_Y:
		DrawFormatStringToHandle(242, START_Y, GetColor(100, 100, 100), font_normal_handle, "　 ＳＴＡＲＴ");
		DrawFormatStringToHandle(232, CREDIT_Y, GetColor(100, 100, 100), font_normal_handle, "　 ＣＲＥＤＩＴ");
		DrawFormatStringToHandle(252, EXIT_Y, GetColor(0, 0, 0), font_normal_handle, "　 ＥＸＩＴ");
		break;

	default:
		Error();
		break;
	}
	//DrawFormatStringToHandle(242, arrow_y, GetColor(0, 0, 0), font_arrow_handle, "→");

	for (int i = 0; i < MAX_CLOUD; i++)
	{
		cloud[i].Draw();
	}
	title_logo.Draw();
}
