//**************************************************
// 
// Hackathon ( select.cpp )
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "main.h"
#include "input.h"
#include "select.h"
#include "fade.h"
#include "color.h"
#include "rectangle.h"
#include "utility.h"

#include <assert.h>

//==================================================
// ��`
//==================================================
namespace
{
const int	MAX_SELECT = 16;	// ���j���[�̍ő吔

/*�� �I���� ��*/
typedef struct
{
	D3DXVECTOR3	pos;		// �ʒu
	D3DXCOLOR	col;		// �F
	int			nIdx;		// ��`�̃C���f�b�N�X
	float		fWidth;		// ��
	float		fHeight;	// ����
}Option;

/*�� ���j���[ ��*/
typedef struct
{
	D3DXVECTOR3	pos;				// �ʒu
	Option		Option[MAX_OPTION];	// �I�����̏��
	int			nNumUse;			// �g�p��
	int			nIdx;				// ��`�̃C���f�b�N�X
	float		fWidth;				// ��
	float		fHeight;			// ����
	float		fInterval;			// �I�����̊Ԋu
	bool		bDraw;				// �`�悷�邩�ǂ���
	bool		bUse;				// �g�p���Ă��邩�ǂ���
}Select;
}// namespace�͂����܂�

//==================================================
// �X�^�e�B�b�N�ϐ�
//==================================================
namespace
{
Select	s_aSelect[MAX_SELECT];	// ���j���[�̏��
int		s_nIdxSelect;			// �I�΂�Ă��郁�j���[�̔ԍ�
}// namespace�͂����܂�

//--------------------------------------------------
// ������
//--------------------------------------------------
void InitSelect(void)
{
	s_nIdxSelect = 0;

	// �������̃N���A
	memset(s_aSelect, 0, sizeof(s_aSelect));
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void UninitSelect(void)
{
	for (int i = 0; i < MAX_SELECT; i++)
	{
		Select *pSelect = &s_aSelect[i];

		if (!pSelect->bUse)
		{// �g�p���Ă��Ȃ�
			continue;
		}

		/*�� �g�p���Ă��� ��*/

		for (int j = 0; j < pSelect->nNumUse; j++)
		{
			Option *pOption = &pSelect->Option[j];

			// �g���̂��~�߂�
			StopUseRectangle(pOption->nIdx);
		}
	}
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void UpdateSelect(void)
{
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void DrawSelect(void)
{
	/* ��`�ŕ`�悵�Ă܂� */
}

//--------------------------------------------------
// �ݒ�
//--------------------------------------------------
int SetSelect(const SelectArgument &menu)
{
	assert(menu.nNumUse >= 0 && menu.nNumUse < MAX_OPTION);
	
	for (int i = 0; i < MAX_SELECT; i++)
	{
		Select *pSelect = &s_aSelect[i];

		if (pSelect->bUse)
		{// �g�p���Ă���
			continue;
		}

		/*�� �g�p���Ă��Ȃ� ��*/

		float fPosX = menu.fLeft + ((menu.fRight - menu.fLeft) * 0.5f);
		float fPosY = menu.fTop + ((menu.fBottom - menu.fTop) * 0.5f);

		pSelect->pos = D3DXVECTOR3(fPosX, fPosY, 0.0f);
		pSelect->nNumUse = menu.nNumUse;
		pSelect->fWidth = menu.fRight - menu.fLeft;
		pSelect->fHeight = menu.fBottom - menu.fTop;
		pSelect->bDraw = true;
		pSelect->bUse = true;

		if (menu.bSort)
		{// �c
			pSelect->fInterval = pSelect->fHeight / (menu.nNumUse + 1);
		}
		else
		{// ��
			pSelect->fInterval = pSelect->fWidth / (menu.nNumUse + 1);
		}

		s_nIdxSelect = i;
	
		for (int j = 0; j < pSelect->nNumUse; j++)
		{
			Option *pOption = &pSelect->Option[j];

			if (menu.bSort)
			{// �c
				pOption->pos = D3DXVECTOR3(pSelect->pos.x, menu.fTop + (pSelect->fInterval * (j + 1)), 0.0f);
			}
			else
			{// ��
				pOption->pos = D3DXVECTOR3(menu.fLeft + (pSelect->fInterval * (j + 1)), pSelect->pos.y, 0.0f);
			}

			pOption->col = GetColor(COLOR_WHITE);
			pOption->fWidth = menu.fWidth;
			pOption->fHeight = menu.fHeight;

			// ��`�̐ݒ�
			pOption->nIdx = SetRectangle(menu.texture[j]);

			D3DXVECTOR3 size = D3DXVECTOR3(menu.fWidth, menu.fHeight, 0.0f);

			// ��`�̈ʒu�̐ݒ�
			SetPosRectangle(pOption->nIdx, pOption->pos, size);

			// ��`�̐F�̐ݒ�
			SetColorRectangle(pOption->nIdx, pOption->col);
		}

		return i;
	}

	assert(false);
	return -1;
}

//--------------------------------------------------
// ���Z�b�g
//--------------------------------------------------
void ResetSelect(int nIdx)
{
	assert(nIdx >= 0 && nIdx < MAX_SELECT);

	s_nIdxSelect = 0;
	
	Select *pSelect = &s_aSelect[nIdx];

	if (!pSelect->bUse)
	{// �g�p���Ă��Ȃ�
		return;
	}

	/*�� �g�p���Ă��� ��*/

	for (int i = 0; i < pSelect->nNumUse; i++)
	{
		Option *pOption = &pSelect->Option[i];

		// �g���̂��~�߂�
		StopUseRectangle(pOption->nIdx);
	}

	pSelect->bUse = false;
}

//--------------------------------------------------
// �`�悷�邩�ǂ���
//--------------------------------------------------
void SetDrawSelect(int nIdx, bool bDraw)
{
	assert(nIdx >= 0 && nIdx < MAX_SELECT);

	Select *pSelect = &s_aSelect[nIdx];

	if (!pSelect->bUse)
	{// �g�p���Ă��Ȃ�
		return;
	}

	/*�� �g�p���Ă��� ��*/

	for (int i = 0; i < pSelect->nNumUse; i++)
	{
		Option *pOption = &pSelect->Option[i];

		// ��`�̕`�悷�邩�ǂ���
		SetDrawRectangle(pOption->nIdx, bDraw);

		pOption->col = GetColor(COLOR_WHITE);
	}

	pSelect->bDraw = bDraw;
}
