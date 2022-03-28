//**************************************************
//
// Hackathon ( ranking.cpp )
// Author  : katsuki mizuki
//
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "main.h"
#include "ranking.h"
#include "rectangle.h"
#include "texture.h"
#include "number.h"
#include "color.h"
#include "mode.h"
#include "input.h"
#include "utility.h"
#include "score.h"

#include <stdio.h>
#include <assert.h>

//==================================================
// ��`
//==================================================
namespace
{
const int	MAX_RANKING = 5;						// �����L���O�̍ő吔
const int	MAX_DIGIT = 8;							// �ő包��
const float	RANKING_WIDTH = 50.0f;					// �����L���O�̕�
const float	RANKING_HEIGHT = 100.0f;				// �����L���O�̍���
const char *TEXT_NAME = "data/TEXT/Ranking.txt";	// �e�L�X�g��

typedef struct
{
	D3DXVECTOR3	pos;	// �ʒu
	int			nIdx;	// ��`�̃C���f�b�N�X
	int			nScore;	// �X�R�A
}Ranking;

}// namespace�͂����܂�

//==================================================
// �X�^�e�B�b�N�ϐ�
//==================================================
namespace
{
Ranking	s_aRanking[MAX_RANKING];	// �����L���O�̏��
}// namespace�͂����܂�

//--------------------------------------------------
// ������
//--------------------------------------------------
void InitRanking(void)
{
	D3DXVECTOR3 size = D3DXVECTOR3(RANKING_WIDTH, RANKING_HEIGHT, 0.0f);

	for (int i = 0; i < MAX_RANKING; i++)
	{
		Ranking *pRanking = &s_aRanking[i];

		pRanking->pos = D3DXVECTOR3(RANKING_WIDTH * MAX_DIGIT, (RANKING_HEIGHT * i) + RANKING_HEIGHT * 0.5f, 0.0f);

		// ���̐ݒ�
		pRanking->nIdx = SetNumber(pRanking->pos, size, GetColor(COLOR_WHITE), pRanking->nScore, MAX_DIGIT, true);
	}
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void UninitRanking(void)
{
	for (int i = 0; i < MAX_RANKING; i++)
	{
		Ranking *pRanking = &s_aRanking[i];

		// �g���̂��~�߂�
		StopUseRectangle(pRanking->nIdx);
	}
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void UpdateRanking(void)
{
	if (GetFunctionKeyTrigger(FUNCTION_KEY_DESISION))
	{//����L�[(ENTER�L�[)�������ꂽ���ǂ���
		// �����L���O�̐ݒ�
		SetRanking();
	}
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void DrawRanking(void)
{
	/* ��`�ŕ`�悵�Ă܂� */
}

//--------------------------------------------------
// �ݒ�
//--------------------------------------------------
void SetRanking(void)
{
	int aSave[MAX_RANKING + 1];
	
	for (int i = 0; i < MAX_RANKING; i++)
	{
		Ranking *pRanking = &s_aRanking[i];

		aSave[i] = pRanking->nScore;
	}

	// �X�R�A�̎擾
	aSave[MAX_RANKING] = GetScore();

	for (int i = 0; i < MAX_RANKING; i++)
	{
		int nMax = aSave[i];

		for (int j = i + 1; j < MAX_RANKING + 1; j++)
		{
			if (nMax < aSave[j])
			{//���肪�傫����������
				nMax = aSave[j];
			}
		}

		for (int j = i + 1; j < MAX_RANKING + 1; j++)
		{
			if (nMax == aSave[j])
			{//�ő�l��T���Č��
				aSave[j] = aSave[i];
				aSave[i] = nMax;
				break;
			}
		}
	}

	for (int i = 0; i < MAX_RANKING; i++)
	{
		Ranking *pRanking = &s_aRanking[i];

		pRanking->nScore = aSave[i];

		// ���̕ύX
		pRanking->nIdx = ChangeNumber(pRanking->nIdx, pRanking->nScore);
	}
}

//--------------------------------------------------
// ���[�h
//--------------------------------------------------
void LoadRanking(void)
{
	FILE *pFile = NULL;	// �t�@�C���|�C���^��錾

	// �t�@�C�����J��
	pFile = fopen(TEXT_NAME, "r");

	if (pFile != NULL)
	{// �t�@�C�����J�����ꍇ
		for (int i = 0; i < MAX_RANKING; i++)
		{
			Ranking *pRanking = &s_aRanking[i];

			fscanf(pFile, "%d", &pRanking->nScore);
		}

		// �t�@�C�������
		fclose(pFile);
	}
	else
	{// �t�@�C�����J���Ȃ��ꍇ
		assert(false);

		for (int i = 0; i < MAX_RANKING; i++)
		{
			Ranking *pRanking = &s_aRanking[i];

			pRanking->nScore = 0;
		}
	}
}

//--------------------------------------------------
// �Z�[�u
//--------------------------------------------------
void SaveRanking(void)
{
	FILE *pFile = NULL;	// �t�@�C���|�C���^��錾

	// �t�@�C�����J��
	pFile = fopen(TEXT_NAME, "w");

	if (pFile != NULL)
	{// �t�@�C�����J�����ꍇ

		for (int i = 0; i < MAX_RANKING; i++)
		{
			Ranking *pRanking = &s_aRanking[i];

			fprintf(pFile, "%d\n\n", pRanking->nScore);
		}

		// �t�@�C�������
		fclose(pFile);
	}
	else
	{// �t�@�C�����J���Ȃ��ꍇ
		assert(false);
	}
}