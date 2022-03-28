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
	MENU_TUTORIAL,	// チュートリアル
	MENU_TEST_1,
	MENU_TEST_2,
	MENU_TEST_3,
	MENU_TEST_4,
	MENU_TEST_5,
	MENU_TEST_6,
	MENU_TEST_7,
	MENU_TEST_8,
	MENU_MAX
}MENU;
}// namespaceはここまで

//==================================================
// スタティック変数
//==================================================
namespace
{
int		s_nIdxBG;		// 背景の矩形のインデックス
int		s_nIdx;			// 矩形のインデックス
int		s_nSelectMenu;	// 選ばれているメニュー
int		s_nIdxUseMenu;	// 使っているメニューの番号
int		s_nIdxCursor;	// カーソルの配列のインデックス
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
	//PlaySound(SOUND_LABEL_TITLE2);

	s_nSelectMenu = 0;

	{// 背景
		// 矩形の設定
		s_nIdxBG = SetRectangle(TEXTURE_NONE);

		D3DXVECTOR3 size = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
		D3DXVECTOR3 pos = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f);

		// 矩形の位置の設定
		SetPosRectangle(s_nIdxBG, pos, size);
	}

	{// ロゴ
		// 矩形の設定
		s_nIdx = SetRectangle(TEXTURE_NONE);

		D3DXVECTOR3 size = D3DXVECTOR3(TITLE_WIDTH, TITLE_HEIGHT, 0.0f);
		D3DXVECTOR3 pos = D3DXVECTOR3(SCREEN_WIDTH * 0.25f, SCREEN_HEIGHT * 0.5f, 0.0f);

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

		menu.texture[MENU_GAME] = TEXTURE_NONE;
		menu.texture[MENU_TUTORIAL] = TEXTURE_NONE;
		menu.texture[MENU_TEST_1] = TEXTURE_NONE;
		menu.texture[MENU_TEST_2] = TEXTURE_NONE;
		menu.texture[MENU_TEST_3] = TEXTURE_NONE;
		menu.texture[MENU_TEST_4] = TEXTURE_NONE;
		menu.texture[MENU_TEST_5] = TEXTURE_NONE;
		menu.texture[MENU_TEST_6] = TEXTURE_NONE;
		menu.texture[MENU_TEST_7] = TEXTURE_NONE;
		menu.texture[MENU_TEST_8] = TEXTURE_NONE;

		FrameArgument Frame;
		Frame.bUse = true;
		Frame.col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f);
		Frame.texture = TEXTURE_NONE;

		// メニューの設定
		s_nIdxUseMenu = SetMenu(menu, Frame);
	}

	{// カーソル
		// カーソル初期化
		InitCursor();

		CursorArgument cursor;
		cursor.nNumUse = MENU_MAX;
		cursor.fPosX = SCREEN_WIDTH * 0.595f;
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

	if (GetKeyboardTrigger(DIK_W) || GetJoypadTrigger(JOYKEY_UP,0) || 
		GetJoypadStickTrigger(JOYKEY_LEFT_STICK, JOYKEY_CROSS_UP,0))
	{// Wキーが押されたかどうか
		// 選択肢の色の初期化
		InitColorOption();

		s_nSelectMenu = ((s_nSelectMenu - 1) + MENU_MAX) % MENU_MAX;

		// 選択肢の変更
		ChangeOption(s_nSelectMenu);

		// カーソルの位置の変更
		ChangePosCursor(s_nIdxCursor, s_nSelectMenu);

		// サウンドの再生
		PlaySound(SOUND_LABEL_SE_SELECT);
	}
	else if (GetKeyboardTrigger(DIK_S) || GetJoypadTrigger(JOYKEY_DOWN,0) || 
		GetJoypadStickTrigger(JOYKEY_LEFT_STICK, JOYKEY_CROSS_DOWN,0))
	{// Sキーが押されたかどうか
		// 選択肢の色の初期化
		InitColorOption();

		s_nSelectMenu = ((s_nSelectMenu + 1) + MENU_MAX) % MENU_MAX;

		// 選択肢の変更
		ChangeOption(s_nSelectMenu);

		// カーソルの位置の変更
		ChangePosCursor(s_nIdxCursor, s_nSelectMenu);

		// サウンドの再生
		PlaySound(SOUND_LABEL_SE_SELECT);
	}

	if (GetKeyboardTrigger(DIK_RETURN) || GetJoypadTrigger(JOYKEY_START,0) ||
		GetJoypadTrigger(JOYKEY_A,0) || GetJoypadTrigger(JOYKEY_B,0))
	{//決定キー(ENTERキー)が押されたかどうか
		switch (s_nSelectMenu)
		{
		case MENU_GAME:	// ゲーム
			ChangeMode(MODE_GAME);
			break;

		case MENU_TUTORIAL:	// チュートリアル
			ChangeMode(MODE_TUTORIAL);
			break;

		case MENU_TEST_1:
		case MENU_TEST_2:
		case MENU_TEST_3:
		case MENU_TEST_4:
		case MENU_TEST_5:
		case MENU_TEST_6:
		case MENU_TEST_7:
		case MENU_TEST_8:
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
