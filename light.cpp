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
#include "utility.h"
#include "game.h"
#include "effect.h"
#include "player.h"

#include <assert.h>

//==================================================
// 定義
//==================================================
namespace
{
const int	MAX_LIGHT = 16;		// ライトの最大数
const int	REPEAT_TIME = 30;	// タイムの繰り返し
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
int		s_nNowLight;				// ライトの現在数
int		s_nMaxLight;				// ライトの最大数
int		s_nIdxSelect;				// メニューの配列のインデックス
int		s_nTime;					// タイム
int		s_nIdxColor[MAX_LIGHT];		// 色の番号
COLOR	s_aColor[LIGHT_COLOR_MAX];	// ライトの色
}// namespaceはここまで

//==================================================
// スタティック関数プロトタイプ宣言
//==================================================
namespace
{
void ResetDrawLight(void);
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

	s_nNowLight = 0;
	s_nMaxLight = 1;

	{// メニュー
		SelectArgument select;
		select.nNumUse = MAX_LIGHT;
		select.fLeft = 0.0f;
		select.fRight = SCREEN_WIDTH;
		select.fTop = SCREEN_HEIGHT * 0.35f;
		select.fBottom = SCREEN_HEIGHT * 0.35f;
		select.fWidth = LIGHT_SIZE;
		select.fHeight = LIGHT_SIZE;
		select.bSort = false;

		for (int i = 0; i < MAX_LIGHT; i++)
		{
			select.texture[i] = TEXTURE_effect_000;
		}

		// セレクトの設定
		s_nIdxSelect = SetSelect(select);
	}


	for (int i = 0; i < MAX_LIGHT; i++)
	{
		s_nIdxColor[i] = IntRandam(LIGHT_COLOR_MAX, 0);

		// セレクトの色の設定
		SetColorSelect(s_nIdxSelect, i, s_aColor[s_nIdxColor[i]]);
	}

	// 応急処置
	s_nIdxColor[0] = IntRandam(LIGHT_COLOR_MAX, 0);

	// セレクトの色の設定
	SetColorSelect(s_nIdxSelect, 0, s_aColor[s_nIdxColor[0]]);

	// 描画のリセット
	//ResetDrawLight();
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
	switch (GetGameState())
	{
	case GAMESTATE_SAMPLE:	// 見本状態
		s_nTime++;

		if (s_nTime % REPEAT_TIME != 0)
		{
			return;
		}

		if (s_nNowLight < s_nMaxLight)
		{
			s_nNowLight++;
			
			// エフェクトの設定
			SetEffect(GetPosSelect(s_nIdxSelect, s_nNowLight - 1), EFFECT_TYPE_000, GetColSelect(s_nIdxSelect, s_nNowLight - 1));
			
			// 描画のリセット
			ResetDrawLight();
		}
		else
		{// 増え切った
			for (int i = 0; i < MAX_LIGHT; i++)
			{
				// セレクトの描画するかどうか
				SetDrawSelect(s_nIdxSelect, i, false);
			}

			// ゲーム状態の設定
			SetGameState(GAMESTATE_PLAYER);
		}
		break;

	case GAMESTATE_RESET:	// リセット状態
		s_nNowLight = 0;
		s_nMaxLight++;
		s_nTime = 0;

		for (int i = 0; i < MAX_LIGHT; i++)
		{
			s_nIdxColor[i] = IntRandam(LIGHT_COLOR_MAX, 0);

			// セレクトの色の設定
			SetColorSelect(s_nIdxSelect, i, s_aColor[s_nIdxColor[i]]);
		}

		// 描画のリセット
		ResetDrawLight();

		break;

	case GAMESTATE_PLAYER:	// プレイヤー状態
	case GAMESTATE_NONE:	// 何もしていない状態
	case GAMESTATE_START:	// 開始状態
		break;

	default:
		assert(false);
		break;
	}

	
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void DrawLight(void)
{
}

//--------------------------------------------------
// 取得
//--------------------------------------------------
int GetLight(void)
{
	return s_nMaxLight;
}

//--------------------------------------------------
// 色の取得
//--------------------------------------------------
int GetColorLight(int nNowLight)
{
	assert(nNowLight >= 0 && nNowLight < MAX_LIGHT);

	return s_nIdxColor[nNowLight];
}

//--------------------------------------------------
// 描画の設定
//--------------------------------------------------
void SetDrawLight(int nNowLight)
{
	// セレクトの描画するかどうか
	SetDrawSelect(s_nIdxSelect, nNowLight, true);

	// エフェクトの設定
	SetEffect(GetPosSelect(s_nIdxSelect, nNowLight), EFFECT_TYPE_000, GetColSelect(s_nIdxSelect, nNowLight));
}

namespace
{
//--------------------------------------------------
// 描画のリセット
//--------------------------------------------------
void ResetDrawLight(void)
{
	for (int i = 0; i < MAX_LIGHT; i++)
	{
		// セレクトの描画するかどうか
		SetDrawSelect(s_nIdxSelect, i, false);
	}

	for (int i = 0; i < s_nNowLight; i++)
	{
		// セレクトの描画するかどうか
		SetDrawSelect(s_nIdxSelect, i, true);
	}
}
}// namespaceはここまで
