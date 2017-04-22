//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Sound.cpp
//!
//! @brief  Sound�N���X�̒�`
//!
//! @date   2016.09.09
//!
//! @author Miyu Hara
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

/* �C���N���[�h�t�@�C�� */
#include "Sound.h"


/* �N���X�̒�` */
/* ----------------------------------------
�֐����FSound::Sound
�T�v�@�FSound�N���X�̃R���X�g���N�^
�����@�F�Ȃ�(void)
�߂�l�F�Ȃ�
---------------------------------------- */
Sound::Sound(void)
	:sound_handle(0),is_play(false)
{}

/* ----------------------------------------
�֐����FSound::LoadSound
�T�v�@�F�������ɃT�E���h��ǂݍ���
�����@�F�t�@�C����(const char*)
�߂�l�F�Ȃ�(void)
---------------------------------------- */
void Sound::LoadSound(const char *file_name)
{
	sound_handle = LoadSoundMem(file_name);
}

/* ----------------------------------------
�֐����FSound::Play
�T�v�@�F�Đ�����
�����@�F�Đ��^�C�v(PLAY_TYPE)
�߂�l�F�Ȃ�(void)
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
�֐����FSound::Stop
�T�v�@�F�Đ����Ă�T�E���h���~����
�����@�F�Ȃ�(void)
�߂�l�F�Ȃ�(void)
---------------------------------------- */
void Sound::Stop(void)
{
	is_play = false;
	StopSoundMem(sound_handle);
}

/* ----------------------------------------
�֐����FSound::ChangeVolume
�T�v�@�F���ʂ�ύX����
�����@�F�Ȃ�(void)
�߂�l�F�Ȃ�(void)
---------------------------------------- */
void Sound::ChangeVolume(const int volume)
{
	ChangeVolumeSoundMem(255 * volume / 100, sound_handle);
}