//**************************************************
//
// Hackathon ( bg.cpp )
// Author  : katsuki mizuki
//
//**************************************************

//==================================================
// インクルード
//==================================================
#include "main.h"
#include "bg.h"
#include "rectangle.h"
#include "input.h"
#include "color.h"
#include "texture.h"

//==================================================
// スタティック変数
//==================================================
namespace
{
int	s_nIdxBG[3];	// 背景の矩形のインデックス
}// namespaceはここまで

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void InitBG(void)
{
	// 矩形の設定
	s_nIdxBG[0] = SetRectangle(TEXTURE_BG_2);

	D3DXVECTOR3 pos = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f);
	D3DXVECTOR3 size = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	// 矩形の位置の設定
	SetPosRectangle(s_nIdxBG[0], pos, size);

	// 矩形の色の設定
	SetColorRectangle(s_nIdxBG[0], D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	// 矩形の設定
	s_nIdxBG[1] = SetRectangle(TEXTURE_BG_1);

	pos = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f);
	size = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	// 矩形の位置の設定
	SetPosRectangle(s_nIdxBG[1], pos, size);

	// 矩形の色の設定
	SetColorRectangle(s_nIdxBG[1], D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	// 矩形の設定
	s_nIdxBG[2] = SetRectangle(TEXTURE_BG_0);

	pos = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f);
	size = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	// 矩形の位置の設定
	SetPosRectangle(s_nIdxBG[2], pos, size);

	// 矩形の色の設定
	SetColorRectangle(s_nIdxBG[2], D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void UninitBG(void)
{
	for (int i = 0; i < 3; i++)
	{
		// 使うのを止める
		StopUseRectangle(s_nIdxBG[i]);
	}
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void UpdateBG(void)
{
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void DrawBG(void)
{
	/* 矩形で描画してます */
}
