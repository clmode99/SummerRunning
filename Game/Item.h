//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Item.h
//!
//! @brief  Item�N���X�̐錾
//!
//! @date   2016.09.15
//!
//! @author Miyu Hara
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

/* ��d�C���N���[�h�̖h�~ */
#pragma once


/* �C���N���[�h�t�@�C�� */
#include "Object.h"


/* �񋓌^�̐錾 */
enum KIND
{
	COLD,
	HOT,
	NONE		// �������p
};


/* �N���X�̐錾 */
class Item :public Object
{
public:
	Item(int w, int h, float px, float py, float sx, float sy);		// �R���X�g���N�^
	
	void Update(void);			// �X�V
	void Draw(void);			// �`��

	void Create(const int lane, const int grp_handle,const KIND kind);	// ���
	void Delete(void);													// ����

	void UpSpeed(void);				// ���x���グ��
	void ResetSpeed(void);			// ���x�����Z�b�g����

	bool IsExistState(void);		// ���݂��邩
	KIND GetKind(void);				// ��ނ��擾����

	bool IsFadeOut(void);			// �t�F�[�h�A�E�g���Ă邩
	void StartFadeout(void);		// �t�F�[�h�A�E�g�J�n (���֐����ɃZ���X���Ȃ��E�E�E�j

private:
	bool exist_state;			// ���݂��邩
	KIND kind;					// ���

	bool is_fadeout;						// �t�F�[�h�A�E�g�t���O
	int opacity;							// �摜�̕s�����x(�O�`�Q�T�T)�B�O�������A�Q�T�T�����S�s����
	static const int MAX_OPACITY = 255;		// �s�����x�̍ő�l�B�ÓI�ɂ��邱�ƂŃC���X�^���X�������ĂȂ��Ă��g����悤�ɂ���
};