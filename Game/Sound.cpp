//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Sound.cpp
//!
//! @brief  Soundクラスの定義
//!
//! @date   2016.09.09
//!
//! @author Miyu Hara
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

/* インクルードファイル */
#include "Sound.h"


/* クラスの定義 */
/* ----------------------------------------
関数名：Sound::Sound
概要　：Soundクラスのコンストラクタ
引数　：なし(void)
戻り値：なし
---------------------------------------- */
Sound::Sound(void)
	:sound_handle(0),is_play(false)
{}

/* ----------------------------------------
関数名：Sound::LoadSound
概要　：メモリにサウンドを読み込む
引数　：ファイル名(const char*)
戻り値：なし(void)
---------------------------------------- */
void Sound::LoadSound(const char *file_name)
{
	sound_handle = LoadSoundMem(file_name);
}

/* ----------------------------------------
関数名：Sound::Play
概要　：再生する
引数　：再生タイプ(PLAY_TYPE)
戻り値：なし(void)
---------------------------------------- */
void Sound::Play(PLAY_TYPE type)
{
	if (is_play == false)
	{
		if (type == BGM)
		{
			PlaySoundMem(sound_handle, DX_PLAYTYPE_LOOP);
			is_play = true;
		}
		if (type == SE)
		{
			PlaySoundMem(sound_handle, DX_PLAYTYPE_BACK);
		}
		
	}
}

/* ----------------------------------------
関数名：Sound::Stop
概要　：再生してるサウンドを停止する
引数　：なし(void)
戻り値：なし(void)
---------------------------------------- */
void Sound::Stop(void)
{
	is_play = false;
	StopSoundMem(sound_handle);
}

/* ----------------------------------------
関数名：Sound::ChangeVolume
概要　：音量を変更する
引数　：なし(void)
戻り値：なし(void)
---------------------------------------- */
void Sound::ChangeVolume(const int volume)
{
	ChangeVolumeSoundMem(255 * volume / 100, sound_handle);
}