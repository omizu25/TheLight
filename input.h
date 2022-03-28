//=============================================================================
//
// ���͏��� [input.h]
// Author1 : KOZUNA HIROHITO
//
//=============================================================================

#ifndef _INPUT_H_		//���̃}�N����`������Ȃ�������
#define _INPUT_H_		//2�d�C���N���[�h�h�~�̃}�N����`

//----------------------------------------------------------------------------
//���C�u�����[�t�@�C���̃����N
//----------------------------------------------------------------------------

#pragma comment(lib,"dinput8.lib")//���͏����ɕK�v(�L�[�{�[�h)
#pragma comment(lib,"xinput.lib")//���͏����ɕK�v�i�W���C�p�b�g�j

//----------------------------------------------------------------------------
//�C���N���[�h�t�@�C��
//----------------------------------------------------------------------------

#include "main.h"

//----------------------------------------------------------------------------
//�񋓌^
//----------------------------------------------------------------------------

//�L�[���(�W���C�p�b�h)
typedef enum
{
	JOYKEY_UP = 0,				//�\���{�^����
	JOYKEY_DOWN,				//�\���{�^����
	JOYKEY_LEFT,				//�\���{�^����
	JOYKEY_RIGHT,				//�\���{�^���E
	JOYKEY_START,				//�X�^�[�g�{�^��
	JOYKEY_BACK,				//�o�b�N�{�^��
	JOYKEY_LEFT_THUMB,			//���X�e�B�b�N������
	JOYKEY_RIGHT_THUMB,			//�E�X�e�B�b�N������
	JOYKEY_LEFT_SHOULDER,		//L�P�{�^��
	JOYKEY_RIGHT_SHOULDER,		//R�P�{�^��
	JOYKEY_LEFT_TRIGGER,		//L�Q�g���K�[
	JOYKEY_RIGHT_TRIGGER,		//R�Q�g���K�[
	JOYKEY_A,					//A�{�^��
	JOYKEY_B,					//B�{�^��
	JOYKEY_X,					//X�{�^��
	JOYKEY_Y,					//Y�{�^��
	JOYKEY_MAX
}JOYKEY;

//�L�[���(8�����X�e�B�b�N)
typedef enum
{
	JOYKEY_CROSS_UP = 0,					//��
	JOYKEY_CROSS_UP_RIGHT,					//�E��
	JOYKEY_CROSS_RIGHT,						//�E
	JOYKEY_CROSS_DOWN_RIGHT,				//�E��
	JOYKEY_CROSS_DOWN,						//��
	JOYKEY_CROSS_DOWN_LEFT,					//����
	JOYKEY_CROSS_LEFT,						//��
	JOYKEY_CROSS_UP_LEFT,					//����
	JOYKEY_CROSS_MAX
}JOYKEY_CROSS;

//�X�e�B�b�N����(�W���C�p�b�h)
typedef enum
{
	JOYKEY_RIGHT_STICK = 0,
	JOYKEY_LEFT_STICK,
	JOYKEY_RIGHT_LEFT_MAX
}JOYKEY_RIGHT_LEFT;

//----------------------------------------------------------------------------
//�v���g�^�C�v�錾
//----------------------------------------------------------------------------

//���͏����̃v���g�^�C�v�錾

HRESULT InitInput(HINSTANCE hInstance, HWND hWnd);		//���͏����S���̏�����
void UninitInput(void);									//���͏����S���̏I������
void UpdateInput(void);									//���͏����S���̍X�V����

														//�v���g�^�C�v�錾�L�[�{�[�h
bool GetKeyboardPress(int nKey);						//�L�[�{�[�h�v���X����
bool GetKeyboardTrigger(int nKey);						//�L�[�{�[�h�g���K�[����
bool GetKeyboardAllPress(void);							//�L�[�{�[�h�S�L�[�v���X����
bool GetKeyboardAllTrigger(void);						//�L�[�{�[�h�S�L�[�g���K�[����

														//�v���g�^�C�v�錾�W���C�p�b�g
bool GetJoypadPress(JOYKEY Key, int nPlayer);													//�W���C�p�b�h�v���X����
bool GetJoypadTrigger(JOYKEY Key, int nPlayer);													//�W���C�p�b�h�g���K�[����
D3DXVECTOR3 GetJoypadStick(JOYKEY_RIGHT_LEFT RightLeft, int nPlayer);							//�W���C�p�b�h�X�e�B�b�N����
int GetJoypadTriggerPedal(JOYKEY Key, int nPlayer);												//�W���C�p�b�h�g���K�[�y�_������
bool GetJoypadStickPress(JOYKEY_RIGHT_LEFT RightLeft, JOYKEY_CROSS Key, int nPlayer);			//�W���C�p�b�h�X�e�B�b�N�v���X�W����
bool GetJoypadStickTrigger(JOYKEY_RIGHT_LEFT RightLeft, JOYKEY_CROSS Key, int nPlayer);			//�W���C�p�b�h�X�e�B�b�N�g���K�[�W����			
bool GetJoypadStickAllTrigger(JOYKEY_RIGHT_LEFT RightLeft, JOYKEY_CROSS Key);					//�W���C�p�b�h�X�e�B�b�N�g���K�[�W�����̑S�v���C���[�̑Ώ�
bool GetJoypadAllTrigger(JOYKEY Key);															//�W���C�p�b�h�g���K�[�̑S�v���C���[�̑Ώ�
#endif