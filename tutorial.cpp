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
// スタティック変数
//==================================================
namespace
{
int	s_nIdx;	// 背景の矩形のインデックス
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
		D3DXVECTOR3 size = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

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

}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void DrawTutorial(void)
{
}
