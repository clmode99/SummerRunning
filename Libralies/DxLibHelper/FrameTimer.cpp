//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   FrameTimer.cpp
//!
//! @brief  �t���[���^�C�}�[�֘A�̃\�[�X�t�@�C��
//!
//! @date   2015/5/1
//!
//! @author ���� �W
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include <DxLib.h>




// �t�@�C���X�R�[�v�ϐ��̒�` ==============================================
static float f_frameDeltaTime = 0.0f;    //!< �t���[���̌o�ߎ���[s]
static float f_frameRate      = 0.0f;    //!< �t���[�����[�g[fps]




// �֐��̒�` ==============================================================

//----------------------------------------------------------------------
//! @brief �t���[���^�C�}�[�̍X�V
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void UpdateFrameTimer(void)
{
	static LONGLONG previousTime = 0;    // �O��̌v������
	static LONGLONG currentTime  = 0;    // ���݂̌v������
	static LONGLONG startTime    = 0;    // �t���[�����[�g�v���J�n����
	static int      frameCount   = 0;    // �t���[����


	// ���Ԃ̌v��
	previousTime = (currentTime != 0) ? currentTime : GetNowHiPerformanceCount();
	currentTime  = GetNowHiPerformanceCount();


	// �t���[���̌o�ߎ��Ԃ̍X�V
	f_frameDeltaTime = (float)(currentTime - previousTime) / 1000000;


	// 1�b���Ƀt���[�����[�g�̍X�V
	frameCount++;
	if ((currentTime - startTime) > 1000000)
	{
		f_frameRate = (float)(1000000 * frameCount) / (currentTime - startTime);
		startTime   = currentTime;
		frameCount  = 0;
	}
}



//------------------------------------------------------------------
//! @brief �t���[���̌o�ߎ��Ԃ̎擾
//!
//! @param[in] �Ȃ�
//!
//! @return �t���[���̌o�ߎ���[s]
//------------------------------------------------------------------
float GetFrameDeltaTime(void)
{
	return f_frameDeltaTime;
}



//------------------------------------------------------------------
//! @brief �t���[�����[�g�̎擾
//!
//! @param[in] �Ȃ�
//!
//! @return �t���[�����[�g[fps]
//------------------------------------------------------------------
float GetFrameRate(void)
{
	return f_frameRate;
}
