//**************************************************
//
// Hackathon ( player.cpp )
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
#include "answer.h"
#include "time.h"
#include "bg.h"

#include <assert.h>

//==================================================
// 定義
//==================================================
namespace
{
const int	MAX_TIME = 5;		// タイムの最大値
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
COLOR	s_aColor[LIGHT_COLOR_MAX];	// ライトの色
int		s_nPlayer;					// ライトの現在の数
int		s_nIdxSelect;				// メニューの配列のインデックス
int		s_nIdxColor[MAX_LIGHT];		// 色の番号
}// namespaceはここまで

 //==================================================
 // スタティック関数プロトタイプ宣言
 //==================================================
namespace
{
void ResetDrawPlayer(void);
}// namespaceはここまで

 //--------------------------------------------------
 // 初期化
 //--------------------------------------------------
void InitPlayer(void)
{
	s_aColor[LIGHT_COLOR_RED] = COLOR_RED;
	s_aColor[LIGHT_COLOR_GREEN] = COLOR_GREEN;
	s_aColor[LIGHT_COLOR_BLUE] = COLOR_BLUE;
	s_aColor[LIGHT_COLOR_YELLOW] = COLOR_YELLOW;

	s_nPlayer = 0;

	{// メニュー
		SelectArgument select;
		select.nNumUse = MAX_LIGHT;
		select.fLeft = 0.0f;
		select.fRight = SCREEN_WIDTH;
		select.fTop = SCREEN_HEIGHT * 0.5f;
		select.fBottom = SCREEN_HEIGHT * 0.5f;
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

	// 描画のリセット
	ResetDrawPlayer();

	// タイムの設定
	SetTime(MAX_TIME);
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void UninitPlayer(void)
{
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void UpdatePlayer(void)
{
	if (GetFade() != FADE_NONE)
	{
		return;
	}

	switch (GetGameState())
	{
	case GAMESTATE_RESET:	// リセット状態
		// 描画のリセット
		ResetDrawPlayer();

		// ゲーム状態の設定
		SetGameState(GAMESTATE_SAMPLE);
		break;

	case GAMESTATE_PLAYER:	// プレイヤー状態

		if (GetAnswer())
		{// 最大値
			return;
		}

		if (GetLightKeyTrigger(LIGHT_KEY_RED))
		{// 赤
			s_nIdxColor[s_nPlayer] = LIGHT_COLOR_RED;

			// セレクトの色の設定
			SetColorSelect(s_nIdxSelect, s_nPlayer, s_aColor[s_nIdxColor[s_nPlayer]]);

			// セレクトの描画するかどうか
			SetDrawSelect(s_nIdxSelect, s_nPlayer, true);

			// ライトの描画設定
			SetDrawLight(s_nPlayer);

			// 答え合わせ
			SetAnswer(s_nPlayer);

			// タイムの設定
			SetTime(MAX_TIME);

			// 矩形の色の設定
			SetColorRectangle(GetBG(), GetColor(COLOR_RED));

			s_nPlayer++;

			// エフェクトの設定
			SetEffect(GetPosSelect(s_nIdxSelect, s_nPlayer - 1), EFFECT_TYPE_000, GetColSelect(s_nIdxSelect, s_nPlayer - 1));
		}
		else if (GetLightKeyTrigger(LIGHT_KEY_GREEN))
		{// 緑
			s_nIdxColor[s_nPlayer] = LIGHT_COLOR_GREEN;

			// セレクトの色の設定
			SetColorSelect(s_nIdxSelect, s_nPlayer, s_aColor[s_nIdxColor[s_nPlayer]]);

			// セレクトの描画するかどうか
			SetDrawSelect(s_nIdxSelect, s_nPlayer, true);

			// ライトの描画設定
			SetDrawLight(s_nPlayer);

			// 答え合わせ
			SetAnswer(s_nPlayer);

			// タイムの設定
			SetTime(MAX_TIME);

			// 矩形の色の設定
			SetColorRectangle(GetBG(), GetColor(COLOR_GREEN));

			s_nPlayer++;

			// エフェクトの設定
			SetEffect(GetPosSelect(s_nIdxSelect, s_nPlayer - 1), EFFECT_TYPE_000, GetColSelect(s_nIdxSelect, s_nPlayer - 1));
		}
		else if (GetLightKeyTrigger(LIGHT_KEY_BLUE))
		{// 青
			s_nIdxColor[s_nPlayer] = LIGHT_COLOR_BLUE;

			// セレクトの色の設定
			SetColorSelect(s_nIdxSelect, s_nPlayer, s_aColor[s_nIdxColor[s_nPlayer]]);

			// セレクトの描画するかどうか
			SetDrawSelect(s_nIdxSelect, s_nPlayer, true);

			// ライトの描画設定
			SetDrawLight(s_nPlayer);

			// 答え合わせ
			SetAnswer(s_nPlayer);

			// タイムの設定
			SetTime(MAX_TIME);

			// 矩形の色の設定
			SetColorRectangle(GetBG(), GetColor(COLOR_BLUE));

			s_nPlayer++;

			// エフェクトの設定
			SetEffect(GetPosSelect(s_nIdxSelect, s_nPlayer - 1), EFFECT_TYPE_000, GetColSelect(s_nIdxSelect, s_nPlayer - 1));
		}
		else if (GetLightKeyTrigger(LIGHT_KEY_YELLOW))
		{// 黄色
			s_nIdxColor[s_nPlayer] = LIGHT_COLOR_YELLOW;

			// セレクトの色の設定
			SetColorSelect(s_nIdxSelect, s_nPlayer, s_aColor[s_nIdxColor[s_nPlayer]]);

			// セレクトの描画するかどうか
			SetDrawSelect(s_nIdxSelect, s_nPlayer, true);

			// ライトの描画設定
			SetDrawLight(s_nPlayer);
		
			// 答え合わせ
			SetAnswer(s_nPlayer);

			// タイムの設定
			SetTime(MAX_TIME);

			// 矩形の色の設定
			SetColorRectangle(GetBG(), GetColor(COLOR_YELLOW));

			s_nPlayer++;

			// エフェクトの設定
			SetEffect(GetPosSelect(s_nIdxSelect, s_nPlayer - 1), EFFECT_TYPE_000, GetColSelect(s_nIdxSelect, s_nPlayer - 1));
		}
		break;

	case GAMESTATE_SAMPLE:	// 見本状態
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
void DrawPlayer(void)
{
}

//--------------------------------------------------
// 取得
//--------------------------------------------------
int GetPlayer(void)
{
	return s_nPlayer;
}

//--------------------------------------------------
// 色の取得
//--------------------------------------------------
int GetColorPlayer(int nNowLight)
{
	assert(nNowLight >= 0 && nNowLight < MAX_LIGHT);

	return s_nIdxColor[nNowLight];
}

namespace
{
//--------------------------------------------------
// 描画のリセット
//--------------------------------------------------
void ResetDrawPlayer(void)
{
	for (int i = 0; i < MAX_LIGHT; i++)
	{
		// セレクトの描画するかどうか
		SetDrawSelect(s_nIdxSelect, i, false);
	}

	s_nPlayer = 0;
}
}// namespaceはここまで