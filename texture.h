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
	TEXTURE_Number_0To9 = 0,	// 数字
	TEXTURE_Cursor_Right,		// 右カーソル
	TEXTURE_Cursor_Left,		// 左カーソル
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
