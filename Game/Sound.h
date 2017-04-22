//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Sound.h
//!
//! @brief  Sound�N���X�̐錾
//!
//! @date   2016.09.09
//!
//! @author Miyu Hara
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

/* ��d�C���N���[�h�̖h�~ */
#pragma once


/* �񋓌^�̐錾 */
enum PLAY_TYPE		// �Đ��^�C�v
{
	BGM,
	SE
};


/* �N���X�̐錾 */
class Sound
{
public:
	Sound(void);		// �R���X�g���N�^

	void LoadSound(const char *file_name);		// �������ɃT�E���h��ǂݍ���
	void Play(PLAY_TYPE type);					// �Đ�
	void Stop(void);							// ��~

	void ChangeVolume(const int volume);		// ���ʕύX

private:
	int sound_handle;		// �T�E���h�n���h��
	bool is_play;			// �Đ��t���O
};