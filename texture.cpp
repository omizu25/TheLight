//**************************************************
// 
// Hackathon ( texture.cpp )
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "main.h"
#include "texture.h"

#include <assert.h>

//==================================================
// �萔
//==================================================
namespace
{
const char *s_FileName[] =
{// �e�N�X�`���̃p�X
	"data/TEXTURE/Cursor_Right.png",	// �J�[�\��
	"data/TEXTURE/Number_004.png",		// ��
};
}// namespace�͂����܂�

static_assert(sizeof(s_FileName) / sizeof(s_FileName[0]) == TEXTURE_MAX, "aho");

//==================================================
// �X�^�e�B�b�N�ϐ�
//==================================================
namespace
{
LPDIRECT3DTEXTURE9 s_pTexture[TEXTURE_MAX];
}// namespace�͂����܂�

//--------------------------------------------------
// �ǂݍ���
//--------------------------------------------------
void LoadTexture(void)
{
	// �f�o�C�X�ւ̃|�C���^�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int i = 0; i < TEXTURE_MAX; ++i)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,
			s_FileName[i],
			&s_pTexture[i]);
	}
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void UninitTexture(void)
{
	for (int i = 0; i < TEXTURE_MAX; ++i)
	{
		if (s_pTexture[i] != NULL)
		{// �e�N�X�`���̉��
			s_pTexture[i]->Release();
			s_pTexture[i] = NULL;
		}
	}
}

//--------------------------------------------------
// �擾
//--------------------------------------------------
LPDIRECT3DTEXTURE9 GetTexture(TEXTURE texture)
{
	if (texture == TEXTURE_NONE)
	{// �e�N�X�`�����g�p���Ȃ�
		return NULL;
	}

	assert(texture >= 0 && texture < TEXTURE_MAX);

	return s_pTexture[texture];
}
