//**************************************************
//
// Hackathon ( title.cpp )
// Author  : katsuki mizuki
//
//**************************************************

//==================================================
// インクルード
//==================================================
#include "main.h" 
#include "fade.h"
#include "input.h"
#include "menu.h"
#include "mode.h"
#include "rectangle.h"
#include "title.h"
#include "color.h"
#include "sound.h"
#include "texture.h"
#include "cursor.h"
#include "gauge.h"
#include "utility.h"
#include "effect.h"
#include "bg.h"

#include <assert.h>

//==================================================
// 定義
//==================================================
namespace
{
const float	TITLE_WIDTH = 600.0f;	// タイトルの幅
const float	TITLE_HEIGHT = 600.0f;	// タイトルの高さ
const float	MENU_WIDTH = 300.0f;	// メニューの幅
const float	MENU_HEIGHT = 80.0f;	// メニューの高さ
const float	CURSOR_SIZE = 50.0f;	// カーソルのサイズ

typedef enum
{
	MENU_GAME = 0,	// ゲーム
	MENU_MAX
}MENU;
}// namespaceはここまで

//==================================================
// スタティック変数
//==================================================
namespace
{
int	s_nIdxBG;		// 背景の矩形のインデックス
int	s_nIdx;			// 矩形のインデックス
int	s_nSelectMenu;	// 選ばれているメニュー
int	s_nIdxMenu;		// メニューの配列のインデックス
int	s_nIdxCursor;	// カーソルの配列のインデックス
int	s_nGaugeIdxGray;	// ゲージのインデックスの保管
float s_fGaugeAlpha;	// 現在のゲージのアルファ値
int	s_nTime;		// タイム
}// namespaceはここまで

//==================================================
// スタティック関数プロトタイプ宣言
//==================================================
namespace
{
void Input(void);
}// namespaceはここまで

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void InitTitle(void)
{
	// サウンドの再生
	PlaySound(SOUND_LABEL_BGM_TITLE);

	s_nSelectMenu = 0;
	s_nTime = 0;
	s_fGaugeAlpha = 0.3f;

	// ゲージの設定(灰色)
	s_nGaugeIdxGray = SetGauge(D3DXVECTOR3(0.0f, SCREEN_HEIGHT * 0.5f, 0.0f), GetColor(COLOR_GRAY), SCREEN_WIDTH, SCREEN_HEIGHT, GAUGE_LEFT);
	// ゲージの色の設定(灰色)
	SetColorGauge(s_nGaugeIdxGray, D3DXCOLOR(GetColor(COLOR_GRAY).r, GetColor(COLOR_GRAY).g, GetColor(COLOR_GRAY).b, s_fGaugeAlpha));

	// 背景
	InitBG();

	// エフェクト
	InitEffect();

	{// ロゴ
		// 矩形の設定
		s_nIdx = SetRectangle(TEXTURE_TITLE_LOGO);

		D3DXVECTOR3 size = D3DXVECTOR3(TITLE_WIDTH, TITLE_HEIGHT, 0.0f);
		D3DXVECTOR3 pos = D3DXVECTOR3(SCREEN_WIDTH * 0.275f, SCREEN_HEIGHT * 0.5f, 0.0f);

		// 矩形の位置の設定
		SetPosRectangle(s_nIdx, pos, size);
	}

	{// メニュー
		// メニューの初期化
		InitMenu();

		MenuArgument menu;
		menu.nNumUse = MENU_MAX;
		menu.fLeft = SCREEN_WIDTH * 0.55f;
		menu.fRight = SCREEN_WIDTH * 0.95f;
		menu.fTop = 0.0f;
		menu.fBottom = SCREEN_HEIGHT;
		menu.fWidth = MENU_WIDTH;
		menu.fHeight = MENU_HEIGHT;
		menu.bSort = true;

		menu.texture[MENU_GAME] = TEXTURE_TITLE_UI;

		FrameArgument Frame;
		Frame.bUse = true;
		Frame.col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f);
		Frame.texture = TEXTURE_NONE;

		// メニューの設定
		s_nIdxMenu = SetMenu(menu, Frame);

		// 選択肢の色の設定
		SetColorOption(s_nIdxMenu, GetColor(COLOR_WHITE), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));

		// 選ばれていない選択肢の色の設定
		SetColorDefaultOption(s_nIdxMenu, GetColor(COLOR_WHITE));
	}

	{// カーソル
		// カーソル初期化
		InitCursor();

		CursorArgument cursor;
		cursor.nNumUse = MENU_MAX;
		cursor.fPosX = SCREEN_WIDTH * 0.65f;
		cursor.fTop = 0.0f;
		cursor.fBottom = SCREEN_HEIGHT;
		cursor.fWidth = CURSOR_SIZE;
		cursor.fHeight = CURSOR_SIZE;
		cursor.texture = TEXTURE_Cursor_Right;
		cursor.nSelect = s_nSelectMenu;
		cursor.bRotation = false;

		// カーソルの設定
		s_nIdxCursor = SetCursor(cursor);
	}
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void UninitTitle(void)
{
	//サウンド停止
	StopSound();

	// メニューの終了
	UninitMenu();

	// カーソルの終了
	UninitCursor();

	// エフェクト
	UninitEffect();

	// 背景
	UninitBG();

	// 使うのを止める
	StopUseRectangle(s_nIdxBG);
	StopUseRectangle(s_nIdx);
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void UpdateTitle(void)
{
	// 入力
	Input();

	// メニューの更新
	UpdateMenu();

	// カーソルの更新
	UpdateCursor();

	s_nTime++;

	float fCurve = CosCurve(s_nTime, 0.01f);
	s_fGaugeAlpha = Curve(fCurve, 0.3f, 0.6f);

	// ゲージの色の設定(灰色)
	SetColorGauge(s_nGaugeIdxGray, D3DXCOLOR(GetColor(COLOR_GRAY).r, GetColor(COLOR_GRAY).g, GetColor(COLOR_GRAY).b, s_fGaugeAlpha));

	// エフェクト
	UpdateEffect();

//	D3DXVECTOR3 pos(140.0f + FloatRandam(20.0f, -20.0f), 80.0f + FloatRandam(10.0f, -10.0f), 0.0f);
	{
		D3DXVECTOR3 pos(142.5f, 102.0f, 0.0f);
		D3DXCOLOR col = GetColor(COLOR_WHITE);

		col.b = 0.1f;

		if (s_nTime % 45 == 0)
		{
			SetEffect(pos, EFFECT_TYPE_003, col);
		}
	}

	{
		D3DXVECTOR3 pos(SCREEN_WIDTH * 0.4f + FloatRandam(100.0f, -100.0f), SCREEN_HEIGHT * 0.4f + FloatRandam(20.0f, -20.0f), 0.0f);
		D3DXCOLOR col = D3DXCOLOR(1.0f, 0.5f, 0.5f, 1.0f);

		col.b = 0.1f;

		if (s_nTime % 55 == 0)
		{
			SetEffect(pos, EFFECT_TYPE_003, col);
		}
	}

	{
		D3DXVECTOR3 pos(SCREEN_WIDTH * 0.15f + FloatRandam(100.0f, -100.0f), SCREEN_HEIGHT * 0.6f + FloatRandam(20.0f, -20.0f), 0.0f);
		D3DXCOLOR col = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);

		col.b = 0.1f;

		if (s_nTime % 35 == 0)
		{
			SetEffect(pos, EFFECT_TYPE_003, col);
		}
	}
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void DrawTitle(void)
{
	// 矩形の描画
	DrawRectangle();
}

namespace
{
//--------------------------------------------------
// 入力
//--------------------------------------------------
void Input(void)
{
	if (GetFade() != FADE_NONE)
	{// フェードしている
		return;
	}

	if (GetFunctionKeyTrigger(FUNCTION_KEY_DESISION))
	{//決定キー(ENTERキー)が押されたかどうか
		switch (s_nSelectMenu)
		{
		case MENU_GAME:	// ゲーム
			ChangeMode(MODE_GAME);
			break;

		default:
			assert(false);
			break;
		}

		// 選択肢の決定
		DecisionOption();

		// サウンドの再生
		PlaySound(SOUND_LABEL_SE_ENTER);
	}
}
}// namespaceはここまで
