//**************************************************
//
// FPG���� ( score.h )
// Author  : katsuki mizuki
//
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "main.h"
#include "score.h"
#include "player.h"
#include "number.h"
#include "color.h"
#include "rule.h"
#include "mode.h"

#include <assert.h>

//==================================================
// ��`
//==================================================
namespace
{
const float	NUMBER_WIDTH = 40.0f;	// ���̕�
const float	NUMBER_HEIGHT = 60.0f;	// ���̍���
}// namespace�͂����܂�

//==================================================
// �X�^�e�B�b�N�ϐ�
//==================================================
namespace
{
int	nSet[MAXPLAYER];		// �Z�b�g��
int nPoint[MAXPLAYER];		// �|�C���g��
int nSetIdx[MAXPLAYER];		// �Z�b�g���̒l�̃C���f�b�N�X
int nPointIdx[MAXPLAYER];	// �|�C���g���̒l�̃C���f�b�N�X
}// namespace�͂����܂�

//--------------------------------------------------
// ������
//--------------------------------------------------
void InitScore(void)
{
	D3DXVECTOR3 size = D3DXVECTOR3(NUMBER_WIDTH, NUMBER_HEIGHT, 0.0f);

	for (int nPlayerNo = 0; nPlayerNo < MAXPLAYER; nPlayerNo++)
	{
		nSet[nPlayerNo] = 0;

		D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, NUMBER_HEIGHT, 0.0f);

		switch (nPlayerNo)
		{
		case 0:
			pos.x = SCREEN_WIDTH * 0.2f;
			break;

		case 1:
			pos.x = SCREEN_WIDTH * 0.8f;
			break;

		default:
			assert(false);
			break;
		}

		// ���̐ݒ�
		nSetIdx[nPlayerNo] = SetNumber(pos, size, GetColor(COLOR_BLUE), nSet[nPlayerNo]);
	}

	for (int nPlayerNo = 0; nPlayerNo < MAXPLAYER; nPlayerNo++)
	{
		nPoint[nPlayerNo] = 0;

		D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, NUMBER_HEIGHT, 0.0f);

		switch (nPlayerNo)
		{
		case 0:
			pos.x = SCREEN_WIDTH * 0.3f;
			break;

		case 1:
			pos.x = SCREEN_WIDTH * 0.7f;
			break;

		default:
			assert(false);
			break;
		}

		// ���̐ݒ�
		nPointIdx[nPlayerNo] = SetNumber(pos, size, GetColor(COLOR_RED), nPoint[nPlayerNo]);
	}
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void UninitScore(void)
{
	for (int nPlayerNo = 0; nPlayerNo < MAXPLAYER; nPlayerNo++)
	{
		// �����g���̂��~�߂�
		StopUseNumber(nSetIdx[nPlayerNo]);
		StopUseNumber(nPointIdx[nPlayerNo]);
	}
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void UpdateScore(void)
{
	for (int nPlayerNo = 0; nPlayerNo < MAXPLAYER; nPlayerNo++)
	{
		//if (nPoint[nPlayerNo] >= GetPointRule())
		//{// �|�C���g�����w��̒l���z����
		//	// �|�C���g����0�ɂ���
		//	ZeroPointScore(nPlayerNo);
		//
		//	// �Z�b�g���̉��Z
		//	AddSetScore(nPlayerNo, 1);
		//}

		//if (nSet[nPlayerNo] >= GetSetRule())
		//{// �Z�b�g�����w��̒l���z����
		//	// �Z�b�g����0�ɂ���
		//	ZeroSetScore(nPlayerNo);
		//
		//	// ���[�h�̕ύX
		//	ChangeMode(MODE_TITLE);
		//}

		if (nPoint[nPlayerNo] >= 6)
		{// �|�C���g�����w��̒l���z����
			// �|�C���g����0�ɂ���
			ZeroPointScore(nPlayerNo);

			// �Z�b�g���̉��Z
			AddSetScore(nPlayerNo, 1);
		}

		if (nSet[nPlayerNo] >= 2)
		{// �Z�b�g�����w��̒l���z����
			// �Z�b�g����0�ɂ���
			ZeroSetScore(nPlayerNo);

			// ���[�h�̕ύX
			ChangeMode(MODE_TITLE);
		}
	}
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void DrawScore(void)
{

}

//--------------------------------------------------
// �Z�b�g����0�ɂ���
//--------------------------------------------------
void ZeroSetScore(int nPlayerNo)
{
	assert(nPlayerNo >= 0 && nPlayerNo < MAXPLAYER);

	nSet[nPlayerNo] = 0;

	// ���̕ύX
	ChangeNumber(nSetIdx[nPlayerNo], nSet[nPlayerNo]);
}

//--------------------------------------------------
// �|�C���g����0�ɂ���
//--------------------------------------------------
void ZeroPointScore(int nPlayerNo)
{
	assert(nPlayerNo >= 0 && nPlayerNo < MAXPLAYER);

	nPoint[nPlayerNo] = 0;

	// ���̕ύX
	ChangeNumber(nPointIdx[nPlayerNo], nPoint[nPlayerNo]);
}

//--------------------------------------------------
// �Z�b�g�������Z
//--------------------------------------------------
void AddSetScore(int nPlayerNo, int nValue)
{
	assert(nPlayerNo >= 0 && nPlayerNo < MAXPLAYER);

	nSet[nPlayerNo] += nValue;

	// ���̕ύX
	ChangeNumber(nSetIdx[nPlayerNo], nSet[nPlayerNo]);
}

//--------------------------------------------------
// �|�C���g�������Z
//--------------------------------------------------
void AddPointScore(int nPlayerNo, int nValue)
{
	assert(nPlayerNo >= 0 && nPlayerNo < MAXPLAYER);

	nPoint[nPlayerNo] += nValue;

	// ���̕ύX
	ChangeNumber(nPointIdx[nPlayerNo], nPoint[nPlayerNo]);
}

//--------------------------------------------------
// �Z�b�g���̎擾
//--------------------------------------------------
int GetSetScore(int nPlayerNo)
{
	assert(nPlayerNo >= 0 && nPlayerNo < MAXPLAYER);

	return nSet[nPlayerNo];
}

//--------------------------------------------------
// �|�C���g���̎擾
//--------------------------------------------------
int GetPointScore(int nPlayerNo)
{
	assert(nPlayerNo >= 0 && nPlayerNo < MAXPLAYER);

	return nPoint[nPlayerNo];
}