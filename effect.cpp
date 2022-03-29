//=========================================
// 
// �p�[�e�B�N���̏���
// Author YudaKaito
// 
//=========================================

//-----------------------------------------
// include
//-----------------------------------------
#include "main.h"
#include "effect.h"
#include "rectangle.h"
#include "color.h"
#include "utility.h"
#include <assert.h>

//-----------------------------------------
// ��`
//-----------------------------------------
namespace
{
const int MAX_EFFECT = 512;	// �p�[�e�B�N���̍ő吔

//-----------------------------------------
// �p�[�e�B�N���\����
//-----------------------------------------
typedef struct
{
	D3DXVECTOR3 pos;	// �ʒu
	D3DXVECTOR3 move;	// �ړ���
	D3DXVECTOR3 rot;	// �p�x
	D3DXCOLOR col;		// �F
	float fRaduus;		// ���a
	int nMaxLife;		// �ő����
	int nLife;			// ����
	int nIdx;			// RectAngel
	EFFECT_TYPE type;	// �p�[�e�B�N���̎��
	bool bUse;			// �g�p���Ă��邩�ǂ���e
}Effect;

}


//-----------------------------------------
// �ÓI�ϐ�
//-----------------------------------------
namespace
{
Effect s_aEffect[MAX_EFFECT];
}

//=========================================
// �p�[�e�B�N���̏���������
//=========================================
void InitEffect(void)
{
	ZeroMemory(s_aEffect, sizeof(s_aEffect));

	for (int i = 0; i < MAX_EFFECT; i++)
	{
		Effect *pEffect = &s_aEffect[i];

		// ��`�̐ݒ�
		pEffect->nIdx = SetRectangle(TEXTURE_NONE);

		// ��`��`�悷�邩�ǂ���
		SetDrawRectangle(pEffect->nIdx, false);
	}
}

//=========================================
// �p�[�e�B�N���̏I������
//=========================================
void UninitEffect(void)
{
	for (int i = 0; i < MAX_EFFECT; i++)
	{
		Effect *pEffect = &s_aEffect[i];

		if (!pEffect->bUse)
		{// �g�p���Ă��Ȃ�
			continue;
		}

		/*�� �g�p���Ă��� ��*/

		// �g���̂��~�߂�
		StopUseRectangle(pEffect->nIdx);
	}
}

//=========================================
// �p�[�e�B�N���̍X�V����
//=========================================
void UpdateEffect(void)
{
	Effect *pEffect;

	for (int i = 0; i < MAX_EFFECT; i++)
	{
		pEffect = s_aEffect + i;

		if (!pEffect->bUse)
		{	// �p�[�e�B�N�����g�p����Ă��Ȃ�
			continue;
		}

		// �p�[�e�B�N�����g�p����Ă���
		// �ʒu�̍X�V
		pEffect->pos += pEffect->move;

		switch (pEffect->type)
		{
		case EFFECT_TYPE_000:
			pEffect->nLife--;											// �̗͂̍X�V
			pEffect->col.a -= (float)1.0f / pEffect->nMaxLife;			// �����x�̍X�V
			pEffect->fRaduus += 8.5f;	// ���a�̊g��
			if (pEffect->nLife <= 0)
			{
				pEffect->bUse = false;
			}
			break;
		case EFFECT_TYPE_001:		// �v���C���[�̈ړ�
			pEffect->nLife--;											// �̗͂̍X�V
			pEffect->col.a -= (float)1.0f / pEffect->nMaxLife;			// �����x�̍X�V
			pEffect->fRaduus += 8.5f;	// ���a�̊g��
			if (pEffect->nLife <= 0)
			{
				pEffect->bUse = false;
			}
			break;
		//case EFFECT_TYPE_PLAYER_AIR:			// �v���C���[�̋󒆋O��
		//	pEffect->nLife--;
		//	pEffect->col.a -= (float)0.5f / pEffect->nMaxLife;
		//	if (pEffect->nLife <= 0)
		//	{
		//		pEffect->bUse = false;
		//	}
		//	break;
		//case EFFECT_TYPE_PLAYER_DEATH:
		//	break;
		//case EFFECT_TYPE_SPLITBALL_ATTACK:
		//	pEffect->fRaduus -= 2.0f;
		//	if (pEffect->fRaduus <= 0.0f)
		//	{
		//		pEffect->bUse = false;
		//	}
		//	break;
		//case EFFECT_TYPE_BALL_HOMING00_ATTACK:	// �Â��Ǐ]������~�̍U�� 
		//									// �̗͂̍X�V
		//	pEffect->nLife--;
		//	if (pEffect->nLife <= 0)
		//	{
		//		pEffect->bUse = false;
		//	}
		//	// �����x�̍X�V
		//	pEffect->col.g -= (float)1 / pEffect->nMaxLife;
		//	pEffect->col.a -= (float)0.5f / pEffect->nMaxLife;
		//	break;
		//case EFFECT_TYPE_BALL_HOMING01_ATTACK:	// �Ǐ]������~�̍U�� 
		//									// �̗͂̍X�V
		//	pEffect->nLife--;
		//	if (pEffect->nLife <= 0)
		//	{
		//		pEffect->bUse = false;
		//	}
		//	// �����x�̍X�V
		//	pEffect->col.g -= (float)1 / pEffect->nMaxLife;
		//	pEffect->col.r -= (float)1 / pEffect->nMaxLife;
		//	pEffect->col.a -= (float)0.5f / pEffect->nMaxLife;
		//	break;
		//case EFFECT_TYPE_GOSTRAIGHT_DIE:	// ���i���钷���`���S��
		//	pEffect->fRaduus -= 0.15f;
		//	if (pEffect->fRaduus <= 0.0f)
		//	{
		//		pEffect->bUse = false;
		//	}
		//	break;
		//case EFFECT_TYPE_BALL_HOMING00_DIE:		// �Â��Ǐ]������~�̎��S��
		//	pEffect->col.a -= (float)0.5f / pEffect->nMaxLife;
		//	pEffect->fRaduus -= 0.05f;
		//	if (pEffect->fRaduus <= 0.0f)
		//	{
		//		pEffect->bUse = false;
		//	}
		//	break;
		//case EFFECT_TYPE_BALL_HOMING01_DIE:		// �Ǐ]������~�̎��S��
		//	pEffect->col.a -= (float)0.5f / pEffect->nMaxLife;
		//	pEffect->fRaduus -= 0.05f;
		//	if (pEffect->fRaduus <= 0.0f)
		//	{
		//		pEffect->bUse = false;
		//	}
		//	break;
		//case EFFECT_TYPE_SERECT_DECISION:		// ���莞��������p�[�e�B�N��
		//	pEffect->col.a -= (float)1.0f / pEffect->nMaxLife;			// �����x�̍X�V
		//	if (pEffect->col.a <= 0.0f)
		//	{
		//		pEffect->bUse = false;
		//	}
		//	break;
		default:
			break;
		}

		if (!pEffect->bUse)
		{	// �p�[�e�B�N�����g�p����Ă��Ȃ�
			// ��`��`�悷�邩�ǂ���
			SetDrawRectangle(pEffect->nIdx, false);
		}

		// ��`�̈ʒu�̐ݒ�
		SetPosRectangle(pEffect->nIdx, pEffect->pos, D3DXVECTOR3(pEffect->fRaduus, pEffect->fRaduus, 0.0f));

		// ��`�̐F�̐ݒ�
		SetColorRectangle(pEffect->nIdx, pEffect->col);
	}
}

//=========================================
// �p�[�e�B�N���̕`�揈��
//=========================================
void DrawEffect(void)
{
}

//=========================================
// �p�[�e�B�N���̐ݒ菈��
//=========================================
void SetEffect(D3DXVECTOR3 pos, EFFECT_TYPE type, D3DXCOLOR col)
{
	Effect *pEffect;

	for (int i = 0; i < MAX_EFFECT; i++)
	{
		pEffect = &(s_aEffect[i]);

		if (pEffect->bUse)
		{// �p�[�e�B�N�����g�p����Ă�
			continue;
		}

		pEffect->bUse = true;
		pEffect->type = type;
		pEffect->col = col;

		switch (type)
		{
		case EFFECT_TYPE_000:	// �v���C���[�̃W�����v�p�[�e�B�N��
			// ��`�̃e�N�X�`���̕ύX
			SetAddRectangle(pEffect->nIdx, true);
			ChangeTextureRectangle(pEffect->nIdx, TEXTURE_effect_000);
			pEffect->pos = pos;
			pEffect->col.a = 0.75f;
			pEffect->fRaduus = 20.0f;
			pEffect->nMaxLife = 60;
			pEffect->nLife = pEffect->nMaxLife;
			SetEffect(pEffect->pos,EFFECT_TYPE_001,GetColor(COLOR_WHITE));
			break;
		case  EFFECT_TYPE_001:		// �v���C���[�̈ړ�
			// ��`�̃e�N�X�`���̕ύX
			SetAddRectangle(pEffect->nIdx, true);
			ChangeTextureRectangle(pEffect->nIdx, TEXTURE_effect_001);
			pEffect->pos = pos;
			pEffect->col.a = 0.75f;
			pEffect->fRaduus = 10.0f;
			pEffect->nMaxLife = 60;
			pEffect->nLife = pEffect->nMaxLife;
			break;
		default:
			assert(false);
			break;
		}

		// ��`��`�悷�邩�ǂ���
		SetDrawRectangle(pEffect->nIdx, true);

		// ��`�̈ʒu�̐ݒ�
		D3DXVECTOR3 size = D3DXVECTOR3(pEffect->fRaduus, pEffect->fRaduus, 0.0f);
		SetPosRectangle(pEffect->nIdx, pEffect->pos, size);

		// ��`�̐F�̐ݒ�
		SetColorRectangle(pEffect->nIdx, pEffect->col);

		break;
	}
}
