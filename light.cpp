//**************************************************
//
// Hackathon ( light.cpp )
// Author  : katsuki mizuki
//
//**************************************************

//==================================================
// インクルード
//==================================================
#include "main.h" 
#include "fade.h"
#include "input.h"
#include "select.h"
#include "mode.h"
#include "rectangle.h"
#include "light.h"
#include "color.h"
#include "sound.h"
#include "texture.h"

#include <assert.h>

//==================================================
// 定義
//==================================================
namespace
{
const int	MAX_LIGHT = 16;		// ライトの最大数
const float	LIGHT_SIZE = 50.0f;	// ライトのサイズ

typedef enum
{
	LIGHT_COLOR_RED = 0,	// 赤
	LIGHT_COLOR_GREEN,		// 緑
	LIGHT_COLOR_BLUE,		// 青
	LIGHT_COLOR_YELLOW,		// 黄色
	LIGHT_COLOR_MAX,
}LIGHT_COLOR;
}// namespaceはここまで

//==================================================
// スタティック変数
//==================================================
namespace
{
int		s_nLight;					// ライトの数
int		s_nSelect;					// 選ばれている
int		s_nIdxSelect;				// メニューの配列のインデックス
COLOR	s_aColor[LIGHT_COLOR_MAX];	// ライトの色
}// namespaceはここまで

//==================================================
// スタティック関数プロトタイプ宣言
//==================================================
namespace
{
}// namespaceはここまで

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void InitLight(void)
{
	s_aColor[LIGHT_COLOR_RED] = COLOR_RED;
	s_aColor[LIGHT_COLOR_GREEN] = COLOR_GREEN;
	s_aColor[LIGHT_COLOR_BLUE] = COLOR_BLUE;
	s_aColor[LIGHT_COLOR_YELLOW] = COLOR_YELLOW;

	s_nSelect = 0;
	s_nLight = 1;

	{// メニュー
		SelectArgument select;
		select.nNumUse = MAX_LIGHT;
		select.fLeft = 0.0f;
		select.fRight = SCREEN_WIDTH;
		select.fTop = SCREEN_HEIGHT * 0.25f;
		select.fBottom = SCREEN_HEIGHT * 0.75f;
		select.fWidth = LIGHT_SIZE;
		select.fHeight = LIGHT_SIZE;
		select.bSort = false;

		for (int i = 0; i < MAX_LIGHT; i++)
		{
			select.texture[i] = TEXTURE_NONE;
		}

		// セレクトの設定
		s_nIdxSelect = SetSelect(select);
	}
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void UninitLight(void)
{
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void UpdateLight(void)
{
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void DrawLight(void)
{
}

namespace
{

}// namespaceはここまで
