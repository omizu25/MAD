//**************************************************
//
// FPD���� ( number.h )
// Author  : katsuki mizuki
//
//**************************************************
#ifndef _NUMBER_H_	//���̃}�N����`������ĂȂ�������
#define _NUMBER_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �v���g�^�C�v�錾
//==================================================
//--------------------------------------------------
// ������
//--------------------------------------------------
void InitNumber(void);

//--------------------------------------------------
// �I��
//--------------------------------------------------
void UninitNumber(void);

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void UpdateNumber(void);

//--------------------------------------------------
// �`��
//--------------------------------------------------
void DrawNumber(void);

//--------------------------------------------------
// �ݒ�
// ����1  : D3DXVECTOR3 pos / ���S�̈ʒu
// ����2  : D3DXVECTOR3 size / �T�C�Y
// ����3  : D3DXCOLOR col / �F
// ����4  : int nNumber / ��
// ����5  : int nDigit / ����
// �Ԓl  : int / �z��̃C���f�b�N�X
//--------------------------------------------------
int SetNumber(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size, const D3DXCOLOR &col, int nNumber);

//--------------------------------------------------
// �ύX
// ����1  : int nIdx / �z��̃C���f�b�N�X
// ����2  : int nNumber / ��
//--------------------------------------------------
void ChangeNumber(int nIdx, int nNumber);

//--------------------------------------------------
// �g���̂��~�߂�
// ����  : int nIdx / �C���f�b�N�X
//--------------------------------------------------
void StopUseNumber(int nIdx);

//--------------------------------------------------
// ����
// ����  : int nNumber / ��
// �Ԓl  : int / ����
//--------------------------------------------------
int DigitNumber(int nNumber);

#endif // !_NUMBER_H_