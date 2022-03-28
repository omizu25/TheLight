//**************************************************
//
// Hackathon ( time.cpp )
// Author  : katsuki mizuki
//
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "main.h"
#include "time.h"
#include "rectangle.h"
#include "texture.h"
#include "number.h"
#include "color.h"

//==================================================
// ��`
//==================================================
namespace
{
const int	ONE_SECOND = 60;		// 1�b
const float	TIME_WIDTH = 100.0f;	// �^�C���̕�
const float	TIME_HEIGHT = 200.0f;	// �^�C���̍���
}// namespace�͂����܂�

//==================================================
// �X�^�e�B�b�N�ϐ�
//==================================================
namespace
{
int	s_nIdxTime;	// ���̔z��̃C���f�b�N�X
int	s_nTime;	// �^�C��
int	s_nSecond;	// 1�b���v��
}// namespace�͂����܂�

 //--------------------------------------------------
 // ������
 //--------------------------------------------------
void InitTime(void)
{
	s_nTime = 0;
	s_nSecond = 0;
	s_nIdxTime = 0;

	D3DXVECTOR3 size = D3DXVECTOR3(TIME_WIDTH, TIME_HEIGHT, 0.0f);
	D3DXVECTOR3 pos = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, TIME_HEIGHT * 0.5f, 0.0f);

	// ���̐ݒ�
	s_nIdxTime = SetNumber(pos, size, GetColor(COLOR_WHITE), s_nTime, 5);
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void UninitTime(void)
{
	// �g���̂��~�߂�
	StopUseRectangle(s_nIdxTime);
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void UpdateTime(void)
{
	s_nSecond++;

	if ((s_nSecond % ONE_SECOND) == 0)
	{// 1�b����
		// ���Z
		AddTime(1);
	}
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void DrawTime(void)
{
	/* ��`�ŕ`�悵�Ă܂� */
}

//--------------------------------------------------
// �ݒ�
//--------------------------------------------------
void SetTime(int nTime)
{
	s_nTime = nTime;
	s_nSecond = 0;

	// ���̕ύX
	s_nIdxTime = ChangeNumber(s_nIdxTime, s_nTime);
}

//--------------------------------------------------
// ���Z
// ����  : int nValue / ���Z����l
//--------------------------------------------------
void AddTime(int nValue)
{
	s_nTime += nValue;

	// ���̕ύX
	s_nIdxTime = ChangeNumber(s_nIdxTime, s_nTime);
}
