//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Sound.h
//!
//! @brief  Soundクラスの宣言
//!
//! @date   2016.09.09
//!
//! @author Miyu Hara
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

/* 二重インクルードの防止 */
#pragma once


/* 列挙型の宣言 */
enum PLAY_TYPE		// 再生タイプ
{
	BGM,
	SE
};


/* クラスの宣言 */
class Sound
{
public:
	Sound(void);		// コンストラクタ

	void LoadSound(const char *file_name);		// メモリにサウンドを読み込む
	void Play(PLAY_TYPE type);					// 再生
	void Stop(void);							// 停止

	void ChangeVolume(const int volume);		// 音量変更

private:
	int sound_handle;		// サウンドハンドル
	bool is_play;			// 再生フラグ
};