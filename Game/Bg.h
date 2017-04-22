//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Bg.h
//!
//! @brief  Bg�N���X�̐錾
//!
//! @date   2016.10.03
//!
//! @author Miyu Hara
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

/* ��d�C���N���[�h�̖h�~ */
#pragma once


/* �C���N���[�h�t�@�C�� */
#include "Object.h"


/* �񋓌^�̐錾 */
enum BG_TYPE
{
	BG_NORMAL,
	SCROLL
};


/* �N���X�̐錾 */
class Bg :public Object
{
public:
	Bg(BG_TYPE type);		// �R���X�g���N�^
	
	void Update(const int time_limit);		// �X�V
	void Draw(void);						// �`��

	void ResetPosition(void);		// ���W�����Z�b�g����
	void UpSpeed(void);				// ���x���グ��

private:
	BG_TYPE type;	// �X�N���[�����邩���Ȃ���
	int grp_y;		// ��ʏ�̉摜�x�P
	int grp_y2;		// ��ʏ�̉摜�x�Q
	int spd_y;		// �X�N���[�������鑬�x�x
	
	bool is_draw1;		// �摜�P��`�悷�邩
	bool is_draw2;		// �摜�Q��`�悷�邩
};