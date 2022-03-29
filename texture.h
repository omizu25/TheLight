//**************************************************
// 
// Hackathon ( texture.h )
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _TEXTURE_H_	//このマクロ定義がされてなかったら
#define _TEXTURE_H_	//２重インクルード防止のマクロ定義

//==================================================
// 列挙型
//==================================================
typedef enum
{
	TEXTURE_Cursor_Right = 0,	// カーソル
	TEXTURE_Number_004,			// 数
	TEXTURE_TITLE_LOGO,			// タイトルロゴ	
	TEXTURE_TITLE_UI,
	TEXTURE_BG_0,					// 背景
	TEXTURE_BG_1,			// 背景
	TEXTURE_BG_2,						// 背景
	TEXTURE_BG,						// 背景
	TEXTURE_effect_000,
	TEXTURE_effect_001,
	TEXTURE_effect_002,
	TEXTURE_Number_Neon,		// ナンバー画像(ネオン)
	TEXTURE_Method,
	TEXTURE_MAX,
	TEXTURE_NONE,			// 使用しない
}TEXTURE;

//==================================================
// プロトタイプ宣言
//==================================================
//--------------------------------------------------
// 読み込み
//--------------------------------------------------
void LoadTexture(void);

//--------------------------------------------------
// 終了
//--------------------------------------------------
void UninitTexture(void);

//--------------------------------------------------
// 取得
// 引数  : TEXTURE texture / 列挙型 種類
// 返値  : LPDIRECT3DTEXTURE9 / テクスチャ
//--------------------------------------------------
LPDIRECT3DTEXTURE9 GetTexture(TEXTURE texture);

#endif // !_TEXTURE_H_
