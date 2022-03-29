//**************************************************
//
// Hackathon ( tutorial.cpp )
// Author  : katsuki mizuki
//
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "main.h"
#include "tutorial.h"
#include "rectangle.h"
#include "texture.h"
#include "input.h"
#include "mode.h"
#include "game.h"

//==================================================
// ��`
//==================================================
namespace
{
const int	MAX_TIME = 120;		// �^�C���̍ő�l
}// namespace�͂����܂�

//==================================================
// �X�^�e�B�b�N�ϐ�
//==================================================
namespace
{
int	s_nIdx;		// �w�i�̋�`�̃C���f�b�N�X
int	s_nTime;	// �^�C��
}// namespace�͂����܂�

 //--------------------------------------------------
 // ������
 //--------------------------------------------------
void InitTutorial(void)
{
	{// �w�i
		// ��`�̐ݒ�
		s_nIdx = SetRectangle(TEXTURE_TITLE_GamePopup);

		D3DXVECTOR3 pos = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f);
		D3DXVECTOR3 size = D3DXVECTOR3(SCREEN_WIDTH * 0.8f, SCREEN_HEIGHT * 0.8f, 0.0f);

		// ��`�̈ʒu�̐ݒ�
		SetPosRectangle(s_nIdx, pos, size);
	}
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void UninitTutorial(void)
{
	// �g���̂��~�߂�
	StopUseRectangle(s_nIdx);
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void UpdateTutorial(void)
{
	if (GetGameState() != GAMESTATE_START)
	{
		return;
	}
	s_nTime++;

	if (s_nTime >= MAX_TIME)
	{
		// ��`�̕`�悷�邩�ǂ���
		SetDrawRectangle(s_nIdx, false);

		// �Q�[����Ԃ̐ݒ�
		SetGameState(GAMESTATE_SAMPLE);
	}
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void DrawTutorial(void)
{
}
