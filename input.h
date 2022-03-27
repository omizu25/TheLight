//==================================================
//
// Hackathon ( input.h )
// Author1  : KOZUNA HIROHITO
// Author2  : ISOE JUKIA
// Author3  : KATSUKI MIZUKI
//
//==================================================
#ifndef _INPUT_H_		// ���̃}�N����`������Ȃ�������
#define _INPUT_H_		// 2�d�C���N���[�h�h�~�̃}�N����`

//--------------------------------------------------
// ���C�u�����̃����N 
//--------------------------------------------------
#pragma comment(lib,"dinput8.lib")		// ���͏����ɕK�v (�L�[�{�[�h)
#pragma comment(lib,"xinput.lib")		// ���͏����ɕK�v�i�W���C�p�b�g�j

//--------------------------------------------------
// �C���N���[�h
//--------------------------------------------------
#include "main.h"

//--------------------------------------------------
// �񋓌^���`
//--------------------------------------------------

/*�� �L�[���(�W���C�p�b�h) ��*/

typedef enum
{
	JOYKEY_UP = 0,			// �\���{�^����
	JOYKEY_DOWN,			// �\���{�^����
	JOYKEY_LEFT,			// �\���{�^����
	JOYKEY_RIGHT,			// �\���{�^���E
	JOYKEY_START,			// �X�^�[�g�{�^��
	JOYKEY_BACK,			// �o�b�N�{�^��
	JOYKEY_LEFT_THUMB,		// ���X�e�B�b�N������
	JOYKEY_RIGHT_THUMB,		// �E�X�e�B�b�N������
	JOYKEY_LEFT_SHOULDER,	// L�P�{�^��
	JOYKEY_RIGHT_SHOULDER,	// R�P�{�^��
	JOYKEY_LEFT_TRIGGER,	// L�Q�g���K�[
	JOYKEY_RIGHT_TRIGGER,	// R�Q�g���K�[
	JOYKEY_A,				// A�{�^��
	JOYKEY_B,				// B�{�^��
	JOYKEY_X,				// X�{�^��
	JOYKEY_Y,				// Y�{�^��
	JOYKEY_LEFT_STICK,		// ���X�e�B�b�N
	JOYKEY_RIGHT_STICK,		// �E�X�e�B�b�N
	JOYKEY_MAX,
}JOYKEY;

/*�� �L�[���(�}�E�X) ��*/

typedef enum
{
	MOUSE_INPUT_LEFT,	// �}�E�X���{�^��
	MOUSE_INPUT_RIGHT,	// �}�E�X�E�{�^��
	MOUSE_INPUT_MIDDLE,	// �}�E�X�����{�^��
	MOUSE_INPUT_4,		// �}�E�X�{�^��4
	MOUSE_INPUT_5,		// �}�E�X�{�^��5
	MOUSE_INPUT_6,		// �}�E�X�{�^��6
	MOUSE_INPUT_7,		// �}�E�X�{�^��7
	MOUSE_INPUT_8,		// �}�E�X�{�^��8
	MOUSE_MAX
}MOUSE;

//--------------------------------------------------
// �v���g�^�C�v�錾
//--------------------------------------------------

/*�� ���͏����̃v���g�^�C�v�錾 ��*/

HRESULT InitInput(HINSTANCE hInstance, HWND hWnd);	// ���͏����S���̏�����
void UninitInput(void);								// ���͏����S���̏I������
void UpdateInput(void);								// ���͏����S���̍X�V����
int GetMaxInput(void);								// ���͏����̃v���C���[�����擾

/*�� �v���g�^�C�v�錾 (�L�[�{�[�h) ��*/

bool GetKeyboardAllPress(void);		// �L�[�{�[�h�̑S�L�[�v���X����
bool GetKeyboardPress(int nKey);	// �L�[�{�[�h�̃v���X����
bool GetKeyboardAllTrigger(void);	// �L�[�{�[�h�̑S�L�[�g���K�[����
bool GetKeyboardTrigger(int nKey);	// �L�[�{�[�h�̃g���K�[����
bool GetKeyboardAllRelease(void);	// �L�[�{�[�h�̑S�����[�X����
bool GetKeyboardRelease(int nKey);	// �L�[�{�[�h�̃����[�X����

/*�� �v���g�^�C�v�錾(�W���C�p�b�h) ��*/

bool GetJoypadAllPress(void);											// �W���C�p�b�h�v���X����(�L�[�w��Ȃ�)
bool GetJoypadPress(JOYKEY Key);										// �W���C�p�b�h�v���X����(�v���C���[�w��Ȃ�)
bool GetJoypadIdxPress(JOYKEY Key, int nPlayer);						// �W���C�p�b�h�̃v���X����(�v���C���[�w�肠��)
bool GetJoypadAllTrigger(void);											// �W���C�p�b�h�g���K�[����(�L�[�w��Ȃ�)
bool GetJoypadTrigger(JOYKEY Key);										// �W���C�p�b�h�g���K�[����(�v���C���[�w��Ȃ�)
bool GetJoypadIdxTrigger(JOYKEY Key, int nPlayer);						// �W���C�p�b�h�̃g���K�[����(�v���C���[�w�肠��)
D3DXVECTOR3 GetJoypadStick(JOYKEY Key, int nPlayer);					// �W���C�p�b�h�̃X�e�B�b�N����
int GetJoypadTriggerPedal(JOYKEY Key, int nPlayer);						// �W���C�p�b�h�̃g���K�[�y�_������
void JoypadVibration(int nTime, WORD nStrength, int nPlayer);			// �W���C�p�b�h�̐U������
bool IsJoyPadUse(int nPlayer);											// �W���C�p�b�h�̎g�p��
bool GetJoypadStickTrigger(JOYKEY Stick, JOYKEY Key);					// �W���C�p�b�h�̃X�e�B�b�N�̃g���K�[����(�v���C���[�w��Ȃ�)
bool GetJoypadIdxStickTrigger(JOYKEY Stick, JOYKEY Key, int nPlayer);	// �W���C�p�b�h�̃X�e�B�b�N�̃g���K�[����(�v���C���[�w�肠��)

/*�� �v���g�^�C�v�錾(�}�E�X) ��*/

bool GetMousePress(MOUSE mouse);	// �}�E�X�̃v���X����
bool GetMouseTrigger(MOUSE mouse);	// �}�E�X�̃g���K�[����
D3DXVECTOR3 GetMouse(void);			// �}�E�X�̉�ʓ��̈ʒu
int GetMouseWheel(void);			// �}�E�X�̃z�C�[���̓�������

#endif // !_INPUT_H_
