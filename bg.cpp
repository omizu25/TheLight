//**************************************************
//
// Hackathon ( bg.cpp )
// Author  : katsuki mizuki
//
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "main.h"
#include "bg.h"
#include "rectangle.h"
#include "input.h"
#include "color.h"
#include "texture.h"

//==================================================
// �X�^�e�B�b�N�ϐ�
//==================================================
namespace
{
int	s_nIdxBG[3];	// �w�i�̋�`�̃C���f�b�N�X
}// namespace�͂����܂�

//--------------------------------------------------
// ������
//--------------------------------------------------
void InitBG(void)
{
	// ��`�̐ݒ�
	s_nIdxBG[0] = SetRectangle(TEXTURE_BG_2);

	D3DXVECTOR3 pos = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f);
	D3DXVECTOR3 size = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	// ��`�̈ʒu�̐ݒ�
	SetPosRectangle(s_nIdxBG[0], pos, size);

	// ��`�̐F�̐ݒ�
	SetColorRectangle(s_nIdxBG[0], D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	// ��`�̐ݒ�
	s_nIdxBG[1] = SetRectangle(TEXTURE_BG_1);

	pos = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f);
	size = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	// ��`�̈ʒu�̐ݒ�
	SetPosRectangle(s_nIdxBG[1], pos, size);

	// ��`�̐F�̐ݒ�
	SetColorRectangle(s_nIdxBG[1], D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	// ��`�̐ݒ�
	s_nIdxBG[2] = SetRectangle(TEXTURE_BG_0);

	pos = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f);
	size = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	// ��`�̈ʒu�̐ݒ�
	SetPosRectangle(s_nIdxBG[2], pos, size);

	// ��`�̐F�̐ݒ�
	SetColorRectangle(s_nIdxBG[2], D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void UninitBG(void)
{
	for (int i = 0; i < 3; i++)
	{
		// �g���̂��~�߂�
		StopUseRectangle(s_nIdxBG[i]);
	}
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void UpdateBG(void)
{
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void DrawBG(void)
{
	/* ��`�ŕ`�悵�Ă܂� */
}
