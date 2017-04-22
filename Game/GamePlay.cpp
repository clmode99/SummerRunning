//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GamePlay.cpp
//!
//! @brief  ゲームプレイ関連のソースファイル
//!
//! @date   2016.09.05
//!
//! @author Miyu Hara
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

/* インクルードファイル */
#include "GamePlay.h"
#include "Common.h"
#include "Sound.h"
#include "Balloon.h"
#include "ItemMgr.h"
#include "Face.h"
#include "Life.h"
#include "Object.h"
#include "Bg.h"
#include "Player.h"
#include "TimeLimit.h"


/* グローバルオブジェクト、グローバル変数の定義 */
// オブジェクト
static Player player(28, 36, PLAYER_X, SCREEN_HEIGHT, 0.0f, 0.0f, MAX_LIFE);	// プレイヤー
static ItemMgr food;															// 食べ物

// 装飾系
static Bg bg(SCROLL);														// 背景
static Face face(64, 64, FACE_X, FACE_Y, 0.0f, 0.0f);				// 顔グラ
static Balloon balloon(80, 48, BALLOON_X, BALLOON_Y, 0.0f, 0.0f);	// 吹き出し
static Life life(32, 32, LIFE_X, LIFE_Y, 0.0f, 0.0f);				// ライフ
static TimeLimit timelimit;											// 制限時間
static Bg explan1(BG_NORMAL);													// 説明１
static Bg explan2(BG_NORMAL);													// 説明２
static Bg clear(BG_NORMAL);													// ゲームクリア
static Bg over(BG_NORMAL);														// ゲームオーバー
static Object ice_resault(13, 20, 210, 335, 0.0f, 0.0f);			// クリア時のアイスアイコン
static Object oden_resault(13, 20, 310, 335, 0.0f, 0.0f);			// クリア時のおでんアイコン

// サウンド
static Sound play_bgm;			// メインＢＧＭ
static Sound sub_bgm;			// サブＢＧＭ
static Sound decision;			// 決定音
static Sound cursor_move;		// カーソル移動
static Sound ice_se;			// アイスを食べる音
static Sound oden_se;			// おでんを食べる音
static Sound clear_se;			// ゲームクリア
static Sound page;				// ページめくる音
static bool is_play_clear;		// 再生したかフラグ

// フォントハンドル
static int font_normal_handle = 0;					// ノーマル
static int font_arrow_handle = 0;					// 選択時の矢印
static int font_start_handle = 0;					// 「ＳＰＡＣＥキーでスタート！」の文字

// フラグ
static bool is_init = false;			// 初期化
static bool is_explan = false;			// 説明したか
static bool is_startline = false;		// スタートラインに立ったか
static bool is_fadeout = false;			// フェードアウトしてもいいか

// アイテムカウンタ
static int ice_cnt = 0;		// アイス食べた数
static int oden_cnt = 0;	// おでん食べた数

// その他
static int arrow_x = ARROW_LEFT;					// 選択時の矢印Ｘ座標
static PLAY_SCENE play_scene = PLAY_EXPLAN1;		// GamePlay内のシーン管理
static int fadein_opacity = 0;						// 不透明度
static bool is_fadeout_bgm = false;					// ＢＧＭがフェードアウトしてるか
extern SCENE g_next_scene;							// シーン情報


/* 関数の定義 */
/* ----------------------------------------
関数名：InitializePlay
概要　：ゲームプレイの初期化処理
引数　：なし(void)
戻り値：なし(void)
---------------------------------------- */
void InitializePlay(void)
{
	// 画像をメモリに読み込む (※グローバルだとコンストラクタで読み込もうとしたら失敗したため)
	player.LoadGraphic("Resources\\Images\\player_normal.png", "Resources\\Images\\player_left.png", "Resources\\Images\\player_right.png");
	food.LoadGraphic("Resources\\Images\\ice.png", "Resources\\Images\\oden.png");
	bg.LoadGraphic("Resources\\Images\\bg.png");
	face.LoadGraphic("Resources\\Images\\face_fine.png", "Resources\\Images\\face_caution.png", "Resources\\Images\\face_danger.png");
	balloon.LoadGraphic("Resources\\Images\\balloon_caution.png", "Resources\\Images\\balloon_danger.png");
	life.LoadGraphic("Resources\\Images\\life.png", "Resources\\Images\\life_damage.png");
	explan1.LoadGraphic("Resources\\Images\\explan1.png");
	explan2.LoadGraphic("Resources\\Images\\explan2.png");
	clear.LoadGraphic("Resources\\Images\\clear.png");
	over.LoadGraphic("Resources\\Images\\over.png");
	ice_resault.LoadGraphic("Resources\\Images\\ice_resault.png");
	oden_resault.LoadGraphic("Resources\\Images\\oden_resault.png");

	// フォントデータをメモリに読み込む
	timelimit.LoadFont("メイリオ");
	font_normal_handle = CreateFontToHandle("メイリオ", 20, 5, DX_FONTTYPE_ANTIALIASING);
	font_arrow_handle = CreateFontToHandle("メイリオ", 20, 9, DX_FONTTYPE_ANTIALIASING);
	font_start_handle = CreateFontToHandle("メイリオ", 26, 7, DX_FONTTYPE_ANTIALIASING);

	// サウンドをメモリに読み込む
	play_bgm.LoadSound("Resources\\Sounds\\play_bgm.mp3");
	sub_bgm.LoadSound("Resources\\Sounds\\summer_bgm.mp3");
	decision.LoadSound("Resources\\Sounds\\decision.mp3");
	cursor_move.LoadSound("Resources\\Sounds\\cursor.mp3");
	ice_se.LoadSound("Resources\\Sounds\\ice.mp3");
	oden_se.LoadSound("Resources\\Sounds\\oden.mp3");
	clear_se.LoadSound("Resources\\Sounds\\clear.mp3");
	page.LoadSound("Resources\\Sounds\\page.mp3");

	sub_bgm.ChangeVolume(65);		// サブＢＧＭは音量ひかえめ
}

/* ----------------------------------------
関数名：UpdatePlay
概要　：ゲームプレイの更新処理
引数　：なし(void)
戻り値：なし(void)
---------------------------------------- */
void UpdatePlay(void)
{
	/* 初期化 */
	if (is_init == false)
	{
		InitializePlay();
		food.Init();			// ステージファイル読み込むも含む

		is_init = true;
	}
	
	/* 処理 */
	switch (play_scene)
	{
	case PLAY_EXPLAN1:
		is_explan = true;
		play_bgm.Play(BGM);
		sub_bgm.Play(BGM);

		if (player.GetUpBorder() > PLAYER_Y)				// プレイヤーが下から出てくる(最初だけ)
		{
			player.Advance();
		}
		else if (PressKeyTrigger(PAD_INPUT_RIGHT) == true)	// 次の説明へ
		{
			play_scene = PLAY_EXPLAN2;
			page.Play(SE);
		}
		else												// 説明する１
		{
			is_startline = true;
			player.Animation(NORMAL);
		}
		break;

	case PLAY_EXPLAN2:
		if (PressKeyTrigger(PAD_INPUT_LEFT) == true)		// 前の説明に戻る
		{
			play_scene = PLAY_EXPLAN1;
			page.Play(SE);
		}
		else if (PressKeyTrigger(PAD_INPUT_10) == true)		// ゲームスタート！
		{
			is_explan = false;
			play_scene = PLAY_PLAY;
			decision.Play(SE);
			InitGameData();
		}
		else												// 説明する２
		{
			player.Animation(NORMAL);
		}
		break;

	case PLAY_PLAY:
		if (IsFinished() == false)
		{
			/* 更新 */
			timelimit.Update();
			bg.Update(timelimit.GetTimeLimit());
			food.Update(timelimit.GetTimeLimit());
			player.Update(timelimit.GetTimeLimit());
			face.Update(player.GetLife());
			balloon.Update(player.GetLife());

			/* 当たり判定(※関数化候補) */
			for (int i = 0; i < MAX_ITEM; i++)
			{
				if ((food.m_item[i].IsExistState() == true) && (food.m_item[i].IsFadeOut() == false))
				{
					if (CollisionObject(&player, &food.m_item[i]) == true)
					{
						// 回復するかダメージを受けるか(※関数化候補)
						switch (food.m_item[i].GetKind())
						{
						case COLD:
							player.Heal();
							ice_se.Play(SE);
							ice_cnt++;
							break;

						case HOT:
							player.Damage();
							oden_se.Play(SE);
							oden_cnt++;
							break;

						default:
							Error();
							break;
						}

						food.m_item[i].StartFadeout();
					}
				}
			}
		}
		else
		{
			if (timelimit.GetTimeLimit() <= 0)
			{
				play_scene = PLAY_CLEAR;
			}
			else
			{
				play_scene = PLAY_OVER;
			}
		}
		break;

	case PLAY_CLEAR:
		if (is_play_clear == false)		// 効果音なのに長いのでフラグ立てないとだめ・・・
		{
			play_bgm.Stop();
			sub_bgm.Stop();

			clear_se.Play(SE);
			is_play_clear = true;
		}

		// 決定時処理
		if (PressKeyTrigger(PAD_INPUT_10) == true)
		{
			InitGameData();
			ResetAllFlag();
			player.ResetPositionAll();
			decision.Play(SE);
			clear_se.Stop();
			WaitTimer(500);
			play_scene = PLAY_EXPLAN1;
			g_next_scene = TITLE;
		}

		// クリア演出(※関数化候補)
		if (player.GetDownBorder() > 0.0f)
		{
			player.Advance();
		}
		break;

	case PLAY_OVER:
		// 「リトライしますか？」
		if (PressKeyTrigger(PAD_INPUT_LEFT) == true)	// 「はい」
		{
			arrow_x = ARROW_LEFT;
			cursor_move.Play(SE);
		}
		if (PressKeyTrigger(PAD_INPUT_RIGHT) == true)	// 「いいえ」
		{
			arrow_x = ARROW_RIGHT;
			cursor_move.Play(SE);
		}

		// 決定時処理
		if (PressKeyTrigger(PAD_INPUT_10) == true)
		{
			if (arrow_x == ARROW_LEFT)				// リトライする
			{
				decision.Play(SE);
				InitGameData();
				play_scene = PLAY_PLAY;
			}
			else									// タイトルへ
			{
				decision.Play(SE);
				is_fadeout_bgm = true;
			}
		}
		break;

	default:
		Error();
		break;
	}

	// 音量フェードアウトしてタイトルへ
	if (is_fadeout_bgm == true)
	{
		static int bgm_volume = 100;		// BGMの音量
		
		bgm_volume -= 3;
		play_bgm.ChangeVolume(bgm_volume);

		if (bgm_volume <= 0)
		{
			is_fadeout_bgm = false;
			InitGameData();
			ResetAllFlag();
			player.ResetPositionAll();
			play_bgm.Stop();
			sub_bgm.Stop();
			arrow_x = ARROW_LEFT;			// カーソルを左に戻しておく
			bgm_volume = 100;
			play_bgm.ChangeVolume(100);
			WaitTimer(100);
			play_scene = PLAY_EXPLAN1;
			g_next_scene = TITLE;
		}
	}
}

/* ----------------------------------------
関数名：RenderPlay
概要　：ゲームプレイの描画処理
引数　：なし(void)
戻り値：なし(void)
---------------------------------------- */
void RenderPlay(void)
{
	/* 後ろ→前に描画する */
	bg.Draw();
	face.Draw();
	if (is_explan == false)					// 説明中は描画しない
	{
		balloon.Draw();
		food.Draw();
	}
	player.Draw();
	life.Draw(player.GetLife());

	if (player.GetLife() <= 3)				// 危険状態の時は少し赤くする
	{
		SetDrawBright(255, 240, 240);		// ほんのり赤い
	}
	else
	{
		SetDrawBright(255, 255, 255);		// 普通
	}

	/* 特定の場面のみ描画する */
	switch (play_scene)
	{
	case PLAY_EXPLAN1:
		if (is_startline == true)		// プレイヤーがスタートラインに立つまでは描画しない
		{
			// フェードイン処理
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadein_opacity);		// 不透明度設定
			fadein_opacity += 5;
			if (fadein_opacity > 255)
			{
				fadein_opacity = 255;
			}

			explan1.Draw();
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);					// もとに戻さないとおかしくなる
		}
		break;

	case PLAY_EXPLAN2:
		explan2.Draw();
		if ((GetPassageTime() / 500) % 2)			// ぺかぺか点滅させる
		{
			DrawFormatStringToHandle(185, 372, GetColor(0, 0, 0), font_start_handle, "ＳＰＡＣＥキーでスタート！");
		}
		break;

	case PLAY_PLAY:
		timelimit.Draw();
		break;

	case PLAY_CLEAR:
		SetDrawBright(255, 255, 255);			// 元に戻す

		clear.Draw();
		ice_resault.Draw();
		oden_resault.Draw();
		DrawFormatStringToHandle(105, 335, GetColor(0, 0, 0), font_normal_handle, "食べた数　　：%2d個、　：%2d個", ice_cnt, oden_cnt);
		DrawFormatStringToHandle(105, 365, GetColor(0, 0, 0), font_normal_handle, "ＳＰＡＣＥキーでタイトルへ");
		break;

	case PLAY_OVER:
		over.Draw();

		// ※関数化候補
		DrawFormatStringToHandle(105, 335, GetColor(0, 0, 0), font_normal_handle, "リトライしますか？");
		DrawFormatStringToHandle(153, 365, GetColor(0, 0, 0), font_normal_handle, "／");
		switch (arrow_x)
		{
		case ARROW_LEFT:
			DrawFormatStringToHandle(110, 365, GetColor(0, 0, 0), font_normal_handle, "はい");
			DrawFormatStringToHandle(177, 365, GetColor(100, 100, 100), font_normal_handle, "いいえ");
			break;

		case ARROW_RIGHT:
			DrawFormatStringToHandle(110, 365, GetColor(100, 100, 100), font_normal_handle, "はい");
			DrawFormatStringToHandle(177, 365, GetColor(0, 0, 0), font_normal_handle, "いいえ");
			break;

		default:
			Error();
			break;
		}
		//DrawFormatStringToHandle(arrow_x, 365, GetColor(0, 0, 0), font_arrow_handle, "→");
		break;
	}


	// ※デバッグ情報はここに
	//DrawFormatString(450, 25, GetColor(0, 0, 0), "プレイヤーのライフ：%d", player.GetLife());
}

/* ----------------------------------------
関数名：IsFiniehed
概要　：ゲームの終了判定
引数　：なし(void)
戻り値：終了(true)、続行(false)
---------------------------------------- */
bool IsFinished(void)
{
	if ((player.GetLife() > 0) && (timelimit.GetTimeLimit() > 0))
	{
		return false;
	}
	else
	{
		return true;
	}
}

/* ----------------------------------------
関数名：InitGameData
概要　：データをまとめて初期化
引数　：なし(void)
戻り値：なし(void)
---------------------------------------- */
void InitGameData(void)
{
	InitCommon();
	bg.ResetPosition();
	food.Init();
	player.ResetPositionX();
	player.ResetLife();
	balloon.Update(player.GetLife());		// プレイしてからタイトル戻ってまたスタートすると、一瞬だけふきだし出現するため
	timelimit.ResetTimeLimit();
	ice_cnt = 0;
	oden_cnt = 0;
	fadein_opacity = 0;
}

/* ----------------------------------------
関数名：ResetAllFlag
概要　：フラグをまとめてリセットする
引数　：なし(void)
戻り値：なし(void)
---------------------------------------- */
void ResetAllFlag(void)
{
	is_init = false;
	is_explan = false;
	is_startline = false;
	is_play_clear = false;
}