//**************************************************
//
// Hackathon ( player.cpp )
// Author  : katsuki mizuki
//
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "main.h" 
#include "fade.h"
#include "input.h"
#include "select.h"
#include "mode.h"
#include "rectangle.h"
#include "light.h"
#include "color.h"
#include "sound.h"
#include "texture.h"
#include "utility.h"
#include "game.h"
#include "effect.h"
#include "player.h"

#include <assert.h>

//==================================================
// ��`
//==================================================
namespace
{
const int	MAX_LIGHT = 16;		// ���C�g�̍ő吔
const float	LIGHT_SIZE = 50.0f;	// ���C�g�̃T�C�Y

typedef enum
{
	LIGHT_COLOR_RED = 0,	// ��
	LIGHT_COLOR_GREEN,		// ��
	LIGHT_COLOR_BLUE,		// ��
	LIGHT_COLOR_YELLOW,		// ���F
	LIGHT_COLOR_MAX,
}LIGHT_COLOR;
}// namespace�͂����܂�

 //==================================================
 // �X�^�e�B�b�N�ϐ�
 //==================================================
namespace
{
int		s_nPlayer;					// ���C�g�̌��݂̐�
int		s_nIdxSelect;				// ���j���[�̔z��̃C���f�b�N�X
int		s_nTime;					// �^�C��
int		s_nIdxColor[MAX_LIGHT];		// �F�̔ԍ�
COLOR	s_aColor[LIGHT_COLOR_MAX];	// ���C�g�̐F
}// namespace�͂����܂�

 //==================================================
 // �X�^�e�B�b�N�֐��v���g�^�C�v�錾
 //==================================================
namespace
{
void ResetDrawPlayer(void);
}// namespace�͂����܂�

 //--------------------------------------------------
 // ������
 //--------------------------------------------------
void InitPlayer(void)
{
	s_aColor[LIGHT_COLOR_RED] = COLOR_RED;
	s_aColor[LIGHT_COLOR_GREEN] = COLOR_GREEN;
	s_aColor[LIGHT_COLOR_BLUE] = COLOR_BLUE;
	s_aColor[LIGHT_COLOR_YELLOW] = COLOR_YELLOW;

	s_nPlayer = 0;

	{// ���j���[
		SelectArgument select;
		select.nNumUse = MAX_LIGHT;
		select.fLeft = 0.0f;
		select.fRight = SCREEN_WIDTH;
		select.fTop = SCREEN_HEIGHT * 0.5f;
		select.fBottom = SCREEN_HEIGHT * 0.5f;
		select.fWidth = LIGHT_SIZE;
		select.fHeight = LIGHT_SIZE;
		select.bSort = false;

		for (int i = 0; i < MAX_LIGHT; i++)
		{
			select.texture[i] = TEXTURE_effect_000;
		}

		// �Z���N�g�̐ݒ�
		s_nIdxSelect = SetSelect(select);
	}

	// �`��̃��Z�b�g
	//ResetDrawPlayer();
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void UninitPlayer(void)
{
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void UpdatePlayer(void)
{
	switch (GetGameState())
	{
	case GAMESTATE_RESET:	// ���Z�b�g���
		s_nPlayer = 0;

		for (int i = 0; i < MAX_LIGHT; i++)
		{
			// �Z���N�g�̐F�̐ݒ�
			SetColorSelect(s_nIdxSelect, i, s_aColor[IntRandam(LIGHT_COLOR_MAX, 0)]);
		}

		// �`��̃��Z�b�g
		ResetDrawPlayer();

		break;

	case GAMESTATE_SAMPLE:	// ���{���
	case GAMESTATE_NONE:	// �������Ă��Ȃ����
	case GAMESTATE_START:	// �J�n���
	case GAMESTATE_ANSWER:	// �������킹���
	case GAMESTATE_PLAYER:	// �v���C���[���
		break;

	default:
		assert(false);
		break;
	}


}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void DrawPlayer(void)
{
}

namespace
{
//--------------------------------------------------
// �`��̃��Z�b�g
//--------------------------------------------------
void ResetDrawPlayer(void)
{
	for (int i = 0; i < MAX_LIGHT; i++)
	{
		// �Z���N�g�̕`�悷�邩�ǂ���
		SetDrawSelect(s_nIdxSelect, i, false);
	}
}
}// namespace�͂����܂�