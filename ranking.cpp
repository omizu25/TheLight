//**************************************************
//
// Hackathon ( ranking.cpp )
// Author  : katsuki mizuki
//
//**************************************************

//==================================================
// インクルード
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
// 定義
//==================================================
namespace
{
const int	MAX_RANKING = 5;						// ランキングの最大数
const int	MAX_DIGIT = 8;							// 最大桁数
const float	RANKING_WIDTH = 50.0f;					// ランキングの幅
const float	RANKING_HEIGHT = 100.0f;				// ランキングの高さ
const char *TEXT_NAME = "data/TEXT/Ranking.txt";	// テキスト名

typedef struct
{
	D3DXVECTOR3	pos;	// 位置
	int			nIdx;	// 矩形のインデックス
	int			nScore;	// スコア
}Ranking;

}// namespaceはここまで

//==================================================
// スタティック変数
//==================================================
namespace
{
Ranking	s_aRanking[MAX_RANKING];	// ランキングの情報
}// namespaceはここまで

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void InitRanking(void)
{
	D3DXVECTOR3 size = D3DXVECTOR3(RANKING_WIDTH, RANKING_HEIGHT, 0.0f);

	for (int i = 0; i < MAX_RANKING; i++)
	{
		Ranking *pRanking = &s_aRanking[i];

		pRanking->pos = D3DXVECTOR3(RANKING_WIDTH * MAX_DIGIT, (RANKING_HEIGHT * i) + RANKING_HEIGHT * 0.5f, 0.0f);

		// 数の設定
		pRanking->nIdx = SetNumber(pRanking->pos, size, GetColor(COLOR_WHITE), pRanking->nScore, MAX_DIGIT, true);
	}
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void UninitRanking(void)
{
	for (int i = 0; i < MAX_RANKING; i++)
	{
		Ranking *pRanking = &s_aRanking[i];

		// 使うのを止める
		StopUseRectangle(pRanking->nIdx);
	}
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void UpdateRanking(void)
{
	if (GetFunctionKeyTrigger(FUNCTION_KEY_DESISION))
	{//決定キー(ENTERキー)が押されたかどうか
		// ランキングの設定
		SetRanking();
	}
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void DrawRanking(void)
{
	/* 矩形で描画してます */
}

//--------------------------------------------------
// 設定
//--------------------------------------------------
void SetRanking(void)
{
	int aSave[MAX_RANKING + 1];
	
	for (int i = 0; i < MAX_RANKING; i++)
	{
		Ranking *pRanking = &s_aRanking[i];

		aSave[i] = pRanking->nScore;
	}

	// スコアの取得
	aSave[MAX_RANKING] = GetScore();

	for (int i = 0; i < MAX_RANKING; i++)
	{
		int nMax = aSave[i];

		for (int j = i + 1; j < MAX_RANKING + 1; j++)
		{
			if (nMax < aSave[j])
			{//相手が大きかったら交代
				nMax = aSave[j];
			}
		}

		for (int j = i + 1; j < MAX_RANKING + 1; j++)
		{
			if (nMax == aSave[j])
			{//最大値を探して交代
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

		// 数の変更
		pRanking->nIdx = ChangeNumber(pRanking->nIdx, pRanking->nScore);
	}
}

//--------------------------------------------------
// ロード
//--------------------------------------------------
void LoadRanking(void)
{
	FILE *pFile = NULL;	// ファイルポインタを宣言

	// ファイルを開く
	pFile = fopen(TEXT_NAME, "r");

	if (pFile != NULL)
	{// ファイルが開いた場合
		for (int i = 0; i < MAX_RANKING; i++)
		{
			Ranking *pRanking = &s_aRanking[i];

			fscanf(pFile, "%d", &pRanking->nScore);
		}

		// ファイルを閉じる
		fclose(pFile);
	}
	else
	{// ファイルが開かない場合
		assert(false);

		for (int i = 0; i < MAX_RANKING; i++)
		{
			Ranking *pRanking = &s_aRanking[i];

			pRanking->nScore = 0;
		}
	}
}

//--------------------------------------------------
// セーブ
//--------------------------------------------------
void SaveRanking(void)
{
	FILE *pFile = NULL;	// ファイルポインタを宣言

	// ファイルを開く
	pFile = fopen(TEXT_NAME, "w");

	if (pFile != NULL)
	{// ファイルが開いた場合

		for (int i = 0; i < MAX_RANKING; i++)
		{
			Ranking *pRanking = &s_aRanking[i];

			fprintf(pFile, "%d\n\n", pRanking->nScore);
		}

		// ファイルを閉じる
		fclose(pFile);
	}
	else
	{// ファイルが開かない場合
		assert(false);
	}
}