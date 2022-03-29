//**************************************************
//
// Hackathon ( light.cpp )
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
#include "effect.h"

#include <assert.h>

//==================================================
// ��`
//==================================================
namespace
{
const int	MAX_LIGHT = 16;		// ���C�g�̍ő吔
const int	REPEAT_TIME = 60;	// �^�C���̌J��Ԃ�
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
int		s_nLight;					// ���C�g�̐�
int		s_nSelect;					// �I�΂�Ă���
int		s_nIdxSelect;				// ���j���[�̔z��̃C���f�b�N�X
int		s_nTime;					// �^�C��
COLOR	s_aColor[LIGHT_COLOR_MAX];	// ���C�g�̐F
}// namespace�͂����܂�

//==================================================
// �X�^�e�B�b�N�֐��v���g�^�C�v�錾
//==================================================
namespace
{
void ResetDrawLight(void);
}// namespace�͂����܂�

//--------------------------------------------------
// ������
//--------------------------------------------------
void InitLight(void)
{
	s_aColor[LIGHT_COLOR_RED] = COLOR_RED;
	s_aColor[LIGHT_COLOR_GREEN] = COLOR_GREEN;
	s_aColor[LIGHT_COLOR_BLUE] = COLOR_BLUE;
	s_aColor[LIGHT_COLOR_YELLOW] = COLOR_YELLOW;

	s_nSelect = 0;
	s_nLight = 0;

	{// ���j���[
		SelectArgument select;
		select.nNumUse = MAX_LIGHT;
		select.fLeft = 0.0f;
		select.fRight = SCREEN_WIDTH;
		select.fTop = SCREEN_HEIGHT * 0.25f;
		select.fBottom = SCREEN_HEIGHT * 0.75f;
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

	for (int i = 0; i < MAX_LIGHT; i++)
	{
		// �Z���N�g�̐F�̐ݒ�
		SetColorSelect(s_nIdxSelect, i, s_aColor[IntRandam(LIGHT_COLOR_MAX, 0)]);
	}

	// �`��̃��Z�b�g
	ResetDrawLight();
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void UninitLight(void)
{
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void UpdateLight(void)
{
	s_nTime++;

	if (s_nTime % REPEAT_TIME == 0)
	{
		if (s_nLight < MAX_LIGHT)
		{
			SetEffect(GetPosSelect(s_nIdxSelect, s_nLight), EFFECT_TYPE_000, D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.0f));
			s_nLight++;
		}

		// �`��̃��Z�b�g
		ResetDrawLight();
	}
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void DrawLight(void)
{
}

namespace
{
//--------------------------------------------------
// �`��̃��Z�b�g
//--------------------------------------------------
void ResetDrawLight(void)
{
	for (int i = 0; i < MAX_LIGHT; i++)
	{
		// �Z���N�g�̕`�悷�邩�ǂ���
		SetDrawSelect(s_nIdxSelect, i, false);
	}

	for (int i = 0; i < s_nLight; i++)
	{
		// �Z���N�g�̕`�悷�邩�ǂ���
		SetDrawSelect(s_nIdxSelect, i, true);
	}
}
}// namespace�͂����܂�
