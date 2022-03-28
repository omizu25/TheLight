//**************************************************
//
// Hackathon ( score.cpp )
// Author  : katsuki mizuki
//
//**************************************************

//==================================================
// インクルード
//==================================================
#include "main.h"
#include "score.h"
#include "rectangle.h"
#include "texture.h"
#include "number.h"
#include "color.h"
#include "mode.h"
#include "input.h"
#include "utility.h"

//==================================================
// 定義
//==================================================
namespace
{
const float	SCORE_WIDTH = 50.0f;	// スコアの幅
const float	SCORE_HEIGHT = 100.0f;	// スコアの高さ
}// namespaceはここまで

//==================================================
// スタティック変数
//==================================================
namespace
{
int	s_nIdxScore;	// 数の配列のインデックス
int	s_nScore;		// スコア
}// namespaceはここまで

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void InitScore(void)
{
	s_nScore = 0;
	s_nIdxScore = 0;

	D3DXVECTOR3 size = D3DXVECTOR3(SCORE_WIDTH, SCORE_HEIGHT, 0.0f);
	D3DXVECTOR3 pos = D3DXVECTOR3(SCREEN_WIDTH, SCORE_HEIGHT * 0.5f, 0.0f);

	// 数の設定
	s_nIdxScore = SetNumber(pos, size, GetColor(COLOR_WHITE), s_nScore, DigitNumber(s_nScore), false);

	// スコアの設定
	SetScore(0);
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void UninitScore(void)
{
	// 使うのを止める
	StopUseRectangle(s_nIdxScore);
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void UpdateScore(void)
{
	if (GetFunctionKeyTrigger(FUNCTION_KEY_DESISION))
	{//決定キー(ENTERキー)が押されたかどうか
		// スコアの加算
		AddScore(100);
	}
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void DrawScore(void)
{
	/* 矩形で描画してます */
}

//--------------------------------------------------
// 設定
//--------------------------------------------------
void SetScore(int nScore)
{
	s_nScore = nScore;

	// 数の変更
	s_nIdxScore = ChangeNumber(s_nIdxScore, s_nScore);
}

//--------------------------------------------------
// 加算
// 引数  : int nValue / 加算する値
//--------------------------------------------------
void AddScore(int nValue)
{
	s_nScore += nValue;

	// 数の変更
	s_nIdxScore = ChangeNumber(s_nIdxScore, s_nScore);
}
