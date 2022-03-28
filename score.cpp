//**************************************************
//
// Hackathon ( score.cpp )
// Author  : katsuki mizuki
//
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "main.h"
#include "score.h"
#include "rectangle.h"
#include "texture.h"
#include "number.h"
#include "color.h"
#include "mode.h"
#include "input.h"
#include "utility.h"

//==================================================
// ��`
//==================================================
namespace
{
const float	SCORE_WIDTH = 50.0f;	// �X�R�A�̕�
const float	SCORE_HEIGHT = 100.0f;	// �X�R�A�̍���
}// namespace�͂����܂�

//==================================================
// �X�^�e�B�b�N�ϐ�
//==================================================
namespace
{
int	s_nIdxScore;	// ���̔z��̃C���f�b�N�X
int	s_nScore;		// �X�R�A
}// namespace�͂����܂�

//--------------------------------------------------
// ������
//--------------------------------------------------
void InitScore(void)
{
	s_nScore = 0;
	s_nIdxScore = 0;

	D3DXVECTOR3 size = D3DXVECTOR3(SCORE_WIDTH, SCORE_HEIGHT, 0.0f);
	D3DXVECTOR3 pos = D3DXVECTOR3(SCREEN_WIDTH, SCORE_HEIGHT * 0.5f, 0.0f);

	// ���̐ݒ�
	s_nIdxScore = SetNumber(pos, size, GetColor(COLOR_WHITE), s_nScore, DigitNumber(s_nScore), false);

	// �X�R�A�̐ݒ�
	SetScore(0);
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void UninitScore(void)
{
	// �g���̂��~�߂�
	StopUseRectangle(s_nIdxScore);
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void UpdateScore(void)
{
	if (GetFunctionKeyTrigger(FUNCTION_KEY_DESISION))
	{//����L�[(ENTER�L�[)�������ꂽ���ǂ���
		// �X�R�A�̉��Z
		AddScore(100);
	}
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void DrawScore(void)
{
	/* ��`�ŕ`�悵�Ă܂� */
}

//--------------------------------------------------
// �ݒ�
//--------------------------------------------------
void SetScore(int nScore)
{
	s_nScore = nScore;

	// ���̕ύX
	s_nIdxScore = ChangeNumber(s_nIdxScore, s_nScore);
}

//--------------------------------------------------
// ���Z
// ����  : int nValue / ���Z����l
//--------------------------------------------------
void AddScore(int nValue)
{
	s_nScore += nValue;

	// ���̕ύX
	s_nIdxScore = ChangeNumber(s_nIdxScore, s_nScore);
}
