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

//==================================================
// �X�^�e�B�b�N�ϐ�
//==================================================
namespace
{
int	s_nIdx;	// �w�i�̋�`�̃C���f�b�N�X
}// namespace�͂����܂�

 //--------------------------------------------------
 // ������
 //--------------------------------------------------
void InitTutorial(void)
{
	{// �w�i
	 // ��`�̐ݒ�
		s_nIdx = SetRectangle(TEXTURE_NONE);

		D3DXVECTOR3 pos = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f);
		D3DXVECTOR3 size = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

		// ��`�̈ʒu�̐ݒ�
		SetPosRectangle(s_nIdx, pos, size);

		// ��`�̐F�̐ݒ�
		SetColorRectangle(s_nIdx, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
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
	if (GetFunctionKeyTrigger(FUNCTION_KEY_DESISION))
	{//����L�[(ENTER�L�[)�������ꂽ���ǂ���
		// ���[�h�̕ύX
		ChangeMode(MODE_TITLE);
	}
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void DrawTutorial(void)
{
	// ��`�̕`��
	DrawRectangle();
}
