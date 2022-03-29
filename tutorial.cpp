//**************************************************
//
// Hackathon ( tutorial.cpp )
// Author  : katsuki mizuki
//
//**************************************************

//==================================================
// インクルード
//==================================================
#include "main.h"
#include "tutorial.h"
#include "rectangle.h"
#include "texture.h"
#include "input.h"
#include "mode.h"
#include "game.h"

//==================================================
// 定義
//==================================================
namespace
{
const int	MAX_TIME = 120;		// タイムの最大値
}// namespaceはここまで

//==================================================
// スタティック変数
//==================================================
namespace
{
int	s_nIdx;		// 背景の矩形のインデックス
int	s_nTime;	// タイム
}// namespaceはここまで

 //--------------------------------------------------
 // 初期化
 //--------------------------------------------------
void InitTutorial(void)
{
	{// 背景
		// 矩形の設定
		s_nIdx = SetRectangle(TEXTURE_TITLE_GamePopup);

		D3DXVECTOR3 pos = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f);
		D3DXVECTOR3 size = D3DXVECTOR3(SCREEN_WIDTH * 0.8f, SCREEN_HEIGHT * 0.8f, 0.0f);

		// 矩形の位置の設定
		SetPosRectangle(s_nIdx, pos, size);
	}
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void UninitTutorial(void)
{
	// 使うのを止める
	StopUseRectangle(s_nIdx);
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void UpdateTutorial(void)
{
	if (GetGameState() != GAMESTATE_START)
	{
		return;
	}
	s_nTime++;

	if (s_nTime >= MAX_TIME)
	{
		// 矩形の描画するかどうか
		SetDrawRectangle(s_nIdx, false);

		// ゲーム状態の設定
		SetGameState(GAMESTATE_SAMPLE);
	}
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void DrawTutorial(void)
{
}
