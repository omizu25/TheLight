//==================================================
// 
// Hackathon ( input.h )
// Author1  : KOZUNA HIROHITO
// Author2  : ISOE JUKIA
// Author3  : KATSUKI MIZUKI
// 
//==================================================

//--------------------------------------------------
// �C���N���[�h
//--------------------------------------------------
#include "input.h"

#include <assert.h>

//--------------------------------------------------
// �}�N����`
//--------------------------------------------------
#define NUM_KEY_MAX		(256)	// �L�[�̍ő吔�i�L�[�{�[�h�j
#define MOUSE_KEY_MAX	(8)		// �L�[�̍ő吔�i�}�E�X�j
#define PLAYER_MAX		(4)		// �v���C���[�̍ő�l��
#define DIRECTION_MAX	(4)		// �����̍ő吔
#define STICK_MAX		(2)		// �X�e�B�b�N�̍ő吔

//--------------------------------------------------
// �X�^�e�B�b�N�ϐ�
//--------------------------------------------------

/*�� �L�[�{�[�h ��*/

static LPDIRECTINPUT8		s_pInput = NULL;								// DirectInput�I�u�W�F�N�g�ւ̃|�C���^
static LPDIRECTINPUTDEVICE8	s_pDevKeyboard = NULL;							// ���̓f�o�C�X(�L�[�{�[�h)�ւ̃|�C���^
static BYTE					s_aKeyState[NUM_KEY_MAX];						// �L�[�{�[�h�̃v���X���
static BYTE					s_aKeyStateTrigger[NUM_KEY_MAX];				// �L�[�{�[�h�̃g���K�[���
static BYTE					s_aKeyStateRelease[NUM_KEY_MAX];				// �L�[�{�[�h�̃����[�X���

/*�� �W���C�p�b�h ��*/

static XINPUT_STATE			s_JoyKeyState[PLAYER_MAX];						// �W���C�p�b�h�̃v���X���
static XINPUT_STATE			s_JoyKeyStateTrigger[PLAYER_MAX];				// �W���C�p�b�h�̃g���K�[���
static D3DXVECTOR3			s_JoyStickPos[PLAYER_MAX];						// �W���C�X�e�B�b�N�̌X��
static XINPUT_VIBRATION		s_JoyMoter[PLAYER_MAX];							// �W���C�p�b�h�̃��[�^�[
static int					s_nTime[PLAYER_MAX];							// �U����������
static WORD					s_nStrength[PLAYER_MAX];						// �U���̋��� (0 - 65535)
static bool					s_bUseJoyPad[PLAYER_MAX];						// �W���C�p�b�h���g�p���Ă邩
static bool					s_bStick[PLAYER_MAX][STICK_MAX][DIRECTION_MAX];	// �X�e�B�b�N�̃g���K�[���
static bool					s_bLean[PLAYER_MAX][STICK_MAX][DIRECTION_MAX];	// �X�e�B�b�N���X�������ǂ���

/*�� �}�E�X ��*/

static LPDIRECTINPUT8		s_pMouseInput = NULL;							// Directinut�I�u�W�F�N�g�ւ̃|�C���^
static LPDIRECTINPUTDEVICE8	s_pDevMouse = NULL;								// ���͂Ńp�X�ւ̃|�C���^
static DIMOUSESTATE2		s_aKeyStateMouse;								// �}�E�X�̃v���X����
static DIMOUSESTATE2		s_aKeyStatetriggerMouse;						// �}�E�X�̃g���K�[����
static POINT				s_MousePos;										// �}�E�X�̃J�[�\���p
static HWND					s_hMouseWnd;									// �E�B���h�E�n���h��

//--------------------------------------------------
// �v���g�^�C�v�錾
//--------------------------------------------------

/*�� �L�[�{�[�h ��*/

static HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd);			// ������
static void UninitKeyboard(void);										// �I������
static void UpdateKeyboard(void);										// �X�V����

/*�� �W���C�p�b�h ��*/

static HRESULT InitJoypad(void);										// ������
static void UninitJoypad(void);											// �I������
static void UpdateJoypad(void);											// �X�V����
static void UpdateStickTrigger(JOYKEY Stick, JOYKEY Key, int nPlayer);	// �X�e�B�b�N�̃g���K�[�̍X�V

/*�� �}�E�X ��*/

static HRESULT InitMouse(HINSTANCE hlnstance, HWND hWnd);				// ������
static void UninitMouse(void);											// �I������
static void UpdateMouse(void);											// �X�V����

//**************************************************
// ���͏����S��
//**************************************************

//--------------------------------------------------
// ���͏����S���̏�����
//--------------------------------------------------
HRESULT InitInput(HINSTANCE hInstance, HWND hWnd)
{
	// �L�[�{�[�h�̏���������
	if (FAILED(InitKeyboard(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	// �}�E�X�̏���������
	if (FAILED(InitMouse(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	// �W���C�p�b�h������
	InitJoypad();

	return S_OK;
}

//--------------------------------------------------
// ���͏����S���̏I������
//--------------------------------------------------
void UninitInput(void)
{
	// �L�[�{�[�h�̏I������
	UninitKeyboard();

	// �}�E�X�̏I������
	UninitMouse();

	// �W���C�p�b�h�I������
	UninitJoypad();
}

//--------------------------------------------------
// ���͏����S���̍X�V����
//--------------------------------------------------
void UpdateInput(void)
{
	// �L�[�{�[�h�̍X�V����
	UpdateKeyboard();

	// �}�E�X�̍X�V����
	UpdateMouse();

	// �W���C�p�b�h�X�V����
	UpdateJoypad();
}

//--------------------------------------------------
// ���͏����̃v���C���[�����擾
//--------------------------------------------------
int GetMaxInput(void)
{
	return PLAYER_MAX;
}

//**************************************************
// �L�[�{�[�h�̓��͏���
//**************************************************

//--------------------------------------------------
// �L�[�{�[�h�̏���������
//--------------------------------------------------
static HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd)
{
	// DirectInput�I�u�W�F�N�g�̐���
	if (FAILED(DirectInput8Create(hInstance,DIRECTINPUT_VERSION,
		IID_IDirectInput8,(void**)&s_pInput,NULL)))
	{
		return E_FAIL;
	}

	// ���̓f�o�C�X�i�L�[�{�[�h�j�̐���
	if (FAILED(s_pInput->CreateDevice(GUID_SysKeyboard,&s_pDevKeyboard,NULL)))
	{
		return E_FAIL;
	}

	// �f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(s_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	// �������[�h��ݒ�
	if (FAILED(s_pDevKeyboard->SetCooperativeLevel(hWnd,
		(DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	// �L�[�{�[�h�ւ̃A�N�Z�X�����l��
	s_pDevKeyboard->Acquire();

	return S_OK;
}

//--------------------------------------------------
// �L�[�{�[�h�̏I������
//--------------------------------------------------
static void UninitKeyboard(void)
{
	// ���̓f�o�C�X�i�L�[�{�[�h�j�̕���
	if (s_pDevKeyboard != NULL)
	{
		s_pDevKeyboard->Unacquire();		// �L�[�{�[�h�ւ̃A�N�Z�X�������
		s_pDevKeyboard->Release();
		s_pDevKeyboard = NULL;
	}

	// DirectInput�I�u�W�F�N�g�̔j��
	if (s_pInput != NULL)
	{
		s_pInput->Release();
		s_pInput = NULL;
	}
}

//--------------------------------------------------
// �L�[�{�[�h�̍X�V����
//--------------------------------------------------
static void UpdateKeyboard(void)
{
	BYTE aKeyState[NUM_KEY_MAX];		// �L�[�{�[�h�̓��͏��

	// ���̓f�o�C�X����f�[�^���擾
	if (SUCCEEDED(s_pDevKeyboard->GetDeviceState(sizeof(aKeyState),&aKeyState[0])))
	{
		for (int nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			s_aKeyStateTrigger[nCntKey] = ~s_aKeyState[nCntKey] & aKeyState[nCntKey];		// �L�[�{�[�h�̃g���K�[����ۑ�
			s_aKeyStateRelease[nCntKey] = s_aKeyState[nCntKey] & ~aKeyState[nCntKey];		// �L�[�{�[�h�̃����[�X����ۑ�
			s_aKeyState[nCntKey] = aKeyState[nCntKey];										// �L�[�{�[�h�̃v���X����ۑ�
		}
	}
	else
	{
		s_pDevKeyboard->Acquire();			// �L�[�{�[�h�ւ̃A�N�Z�X�����l��
	}

}

//--------------------------------------------------
// �L�[�{�[�h�̃v���X�����擾
//--------------------------------------------------
bool GetKeyboardPress(int nKey)
{
	return (s_aKeyState[nKey] & 0x80) != 0;
}

//--------------------------------------------------
// �L�[�{�[�h�̃g���K�[�����擾
//--------------------------------------------------
bool GetKeyboardTrigger(int nKey)
{
	return (s_aKeyStateTrigger[nKey] & 0x80) != 0;
}

//--------------------------------------------------
// �L�[�{�[�h�̃����[�X�����擾
//--------------------------------------------------
bool GetKeyboardRelease(int nKey)
{
	return (s_aKeyStateRelease[nKey] & 0x80) != 0;
}

//--------------------------------------------------
// �L�[�{�[�h�̑S�L�[�v���X�����擾
//--------------------------------------------------
bool GetKeyboardAllPress(void)
{
	for (int nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
	{
		if (GetKeyboardPress(nCntKey))
		{
			return true;
		}
	}

	return false;
}

//--------------------------------------------------
// �L�[�{�[�h�̑S�L�[�g���K�[�����擾
//--------------------------------------------------
bool GetKeyboardAllTrigger(void)
{
	for (int nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
	{
		if (GetKeyboardTrigger(nCntKey))
		{
			return true;
		}
	}

	return false;
}

//--------------------------------------------------
// �L�[�{�[�h�̑S�L�[�����[�X�����擾
//--------------------------------------------------
bool GetKeyboardAllRelease(void)
{
	for (int nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
	{
		if (GetKeyboardRelease(nCntKey))
		{
			return true;
		}
	}

	return false;
}

//**************************************************
// �W���C�p�b�h�̓��͏���
//**************************************************

//--------------------------------------------------
// �W���C�p�b�h�̏�����
//--------------------------------------------------
static HRESULT InitJoypad(void)
{
	// XInput�̃X�e�[�g��ݒ�i�L���ɂ���j
	XInputEnable(true);

	for (int nCnt = 0; nCnt < PLAYER_MAX; nCnt++)
	{
		// �������[�̃N���A
		memset(&s_JoyKeyState[nCnt], 0, sizeof(XINPUT_STATE));
		memset(&s_JoyKeyStateTrigger[nCnt], 0, sizeof(XINPUT_STATE));

		// �W���C�p�b�h�̐U������̂O�N���A
		ZeroMemory(&s_JoyMoter[nCnt], sizeof(XINPUT_VIBRATION));

		// �U������p�̏�����
		s_nStrength[nCnt] = 0;
		s_nTime[nCnt] = 0;
	}

	return S_OK;
}

//--------------------------------------------------
// �W���C�p�b�h�̏I��
//--------------------------------------------------
static void UninitJoypad(void)
{
	// XInput�̃X�e�[�g��ݒ�i�����ɂ���j
	XInputEnable(false);
}

//--------------------------------------------------
// �W���C�p�b�h�̍X�V
//--------------------------------------------------
static void UpdateJoypad(void)
{
	XINPUT_STATE JoyKeyState[PLAYER_MAX];		// �W���C�p�b�h���͏��

	for (int nCnt = 0; nCnt < PLAYER_MAX; nCnt++)
	{
		// �W���C�p�b�h�̏�Ԃ��擾
		if (XInputGetState(nCnt, &JoyKeyState[nCnt]) == ERROR_SUCCESS)
		{
			// �g���K�[����ۑ�
			s_JoyKeyStateTrigger[nCnt].Gamepad.wButtons = ~s_JoyKeyState[nCnt].Gamepad.wButtons & JoyKeyState[nCnt].Gamepad.wButtons;

			// �v���X����ۑ�
			s_JoyKeyState[nCnt] = JoyKeyState[nCnt];

			// �X�e�B�b�N�̃g���K�[�̍X�V
			UpdateStickTrigger(JOYKEY_LEFT_STICK, JOYKEY_UP, nCnt);
			UpdateStickTrigger(JOYKEY_LEFT_STICK, JOYKEY_DOWN, nCnt);
			UpdateStickTrigger(JOYKEY_LEFT_STICK, JOYKEY_LEFT, nCnt);
			UpdateStickTrigger(JOYKEY_LEFT_STICK, JOYKEY_RIGHT, nCnt);
			UpdateStickTrigger(JOYKEY_RIGHT_STICK, JOYKEY_UP, nCnt);
			UpdateStickTrigger(JOYKEY_RIGHT_STICK, JOYKEY_DOWN, nCnt);
			UpdateStickTrigger(JOYKEY_RIGHT_STICK, JOYKEY_LEFT, nCnt);
			UpdateStickTrigger(JOYKEY_RIGHT_STICK, JOYKEY_RIGHT, nCnt);

			s_bUseJoyPad[nCnt] = true; // �g�p�󋵂̍X�V
		}
		else
		{
			s_bUseJoyPad[nCnt] = false;	// �g�p�󋵂̍X�V
		}

		// �W���C�p�b�h�̐U��
		s_JoyMoter[nCnt].wLeftMotorSpeed = s_nStrength[nCnt];
		s_JoyMoter[nCnt].wRightMotorSpeed = s_nStrength[nCnt];
		XInputSetState(nCnt, &s_JoyMoter[nCnt]);

		if (s_nTime[nCnt] > 0)
		{
			s_nTime[nCnt]--;
		}
		else
		{
			s_nStrength[nCnt] = 0;
			s_nTime[nCnt] = 0;
		}
	}
}

//--------------------------------------------------
// �X�e�B�b�N�̃g���K�[�̍X�V
//--------------------------------------------------
static void UpdateStickTrigger(JOYKEY Stick, JOYKEY Key, int nPlayer)
{
	D3DXVECTOR3 stick = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	float fDeadZone = 0.0f;
	int nStick = 0;

	switch (Stick)
	{// �X�e�B�b�N�̎��
	case JOYKEY_LEFT_STICK:
		stick = D3DXVECTOR3((float)(s_JoyKeyState[nPlayer].Gamepad.sThumbLX), (float)(-s_JoyKeyState[nPlayer].Gamepad.sThumbLY), 0.0f);
		fDeadZone = XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;
		nStick = 0;
		break;

	case JOYKEY_RIGHT_STICK:
		stick = D3DXVECTOR3((float)(s_JoyKeyState[nPlayer].Gamepad.sThumbRX), (float)(-s_JoyKeyState[nPlayer].Gamepad.sThumbRY), 0.0f);
		fDeadZone = XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE;
		nStick = 1;
		break;

	default:
		assert(false);
		break;
	}

	switch (Key)
	{// �X�������
	case JOYKEY_UP:		// ��
		if (s_bLean[nPlayer][nStick][0])
		{// �X����
			s_bStick[nPlayer][nStick][0] = true;
			s_bLean[nPlayer][nStick][0] = false;
		}
		else
		{// �X���ĂȂ�
			if (stick.y >= -fDeadZone)
			{// �X���ĂȂ�
				s_bStick[nPlayer][nStick][0] = false;
			}
		}
		break;

	case JOYKEY_DOWN:	// ��
		if (s_bLean[nPlayer][nStick][1])
		{// �X����
			s_bStick[nPlayer][nStick][1] = true;
			s_bLean[nPlayer][nStick][1] = false;
		}
		else
		{// �X���ĂȂ�
			if (stick.y <= fDeadZone)
			{// �X���ĂȂ�
				s_bStick[nPlayer][nStick][1] = false;
			}
		}
		break;

	case JOYKEY_LEFT:	// ��
		if (s_bLean[nPlayer][nStick][2])
		{// �X����
			s_bStick[nPlayer][nStick][2] = true;
			s_bLean[nPlayer][nStick][2] = false;
		}
		else
		{// �X���ĂȂ�
			if (stick.x >= -fDeadZone)
			{// �X���ĂȂ�
				s_bStick[nPlayer][nStick][2] = false;
			}
		}
		break;

	case JOYKEY_RIGHT:	// �E
		if (s_bLean[nPlayer][nStick][3])
		{// �X����
			s_bStick[nPlayer][nStick][3] = true;
			s_bLean[nPlayer][nStick][3] = false;
		}
		else
		{// �X���ĂȂ�
			if (stick.x <= fDeadZone)
			{// �X���ĂȂ�
				s_bStick[nPlayer][nStick][3] = false;
			}
		}
		break;

	default:
		assert(false);
		break;
	}
}

//--------------------------------------------------
// �W���C�p�b�h�̃v���X����(�v���C���[�w�肠��)
//--------------------------------------------------
bool GetJoypadIdxPress(JOYKEY Key, int nPlayer)
{
	return (s_JoyKeyState[nPlayer].Gamepad.wButtons & (0x01 << Key)) != 0;
}

//--------------------------------------------------
// �W���C�p�b�h�̃g���K�[����(�v���C���[�w�肠��)
//--------------------------------------------------
bool GetJoypadIdxTrigger(JOYKEY Key, int nPlayer)
{
	return (s_JoyKeyStateTrigger[nPlayer].Gamepad.wButtons & (0x01 << Key)) != 0;
}

//--------------------------------------------------
// �W���C�p�b�h�̃v���X����(�v���C���[�w��Ȃ�)
//--------------------------------------------------
bool GetJoypadPress(JOYKEY Key)
{
	for (int nPlayer = 0; nPlayer < PLAYER_MAX; nPlayer++)
	{
		if (GetJoypadIdxPress(Key, nPlayer))
		{
			return true;
		}
	}
	return false;
}

//--------------------------------------------------
// �W���C�p�b�h�̃v���X����(�v���C���[�w��Ȃ�)
//--------------------------------------------------
bool GetJoypadTrigger(JOYKEY Key)
{
	for (int nPlayer = 0; nPlayer < PLAYER_MAX; nPlayer++)
	{
		if (GetJoypadIdxTrigger((JOYKEY)Key, nPlayer))
		{
			return true;
		}
	}
	return false;
}

//--------------------------------------------------
// �W���C�p�b�h�̑S�L�[�v���X����
//--------------------------------------------------
bool GetJoypadAllPress(void)
{
	for (int nPlayer = 0; nPlayer < PLAYER_MAX; nPlayer++)
	{
		for (int nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			if (GetJoypadIdxPress((JOYKEY)nCntKey, nPlayer))
			{
				return true;
			}
		}
	}
	return false;
}

//--------------------------------------------------
// �W���C�p�b�h�̑S�L�[�g���K�[����
//--------------------------------------------------
bool GetJoypadAllTrigger(void)
{
	for (int nPlayer = 0; nPlayer < PLAYER_MAX; nPlayer++)
	{
		for (int nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			if (GetJoypadIdxTrigger((JOYKEY)nCntKey, nPlayer))
			{
				return true;
			}
		}
	}
	return false;
}


//--------------------------------------------------
// �W���C�p�b�g�i�X�e�B�b�N�v���X�j����
//--------------------------------------------------
D3DXVECTOR3 GetJoypadStick(JOYKEY Key, int nPlayer)
{
	switch (Key)
	{
	case JOYKEY_LEFT_STICK:
		s_JoyStickPos[nPlayer] = D3DXVECTOR3(s_JoyKeyState[nPlayer].Gamepad.sThumbLX / 32767.0f, - s_JoyKeyState[nPlayer].Gamepad.sThumbLY / 32767.0f, 0.0f);
		break;
	case JOYKEY_RIGHT_STICK:
		s_JoyStickPos[nPlayer] = D3DXVECTOR3(s_JoyKeyState[nPlayer].Gamepad.sThumbRX / 32767.0f, - s_JoyKeyState[nPlayer].Gamepad.sThumbRY / 32767.0f, 0.0f);
		break;
	}

	return s_JoyStickPos[nPlayer];
}

//--------------------------------------------------
// �W���C�p�b�g�i�g���K�[�y�_���j����
//--------------------------------------------------
int GetJoypadTriggerPedal(JOYKEY Key, int nPlayer)
{
	int nJoypadTriggerPedal = 0;

	switch (Key)
	{
	case JOYKEY_LEFT_TRIGGER:
		nJoypadTriggerPedal = s_JoyKeyState[nPlayer].Gamepad.bLeftTrigger;
		break;
	case JOYKEY_RIGHT_TRIGGER:
		nJoypadTriggerPedal = s_JoyKeyState[nPlayer].Gamepad.bRightTrigger;
		break;
	}
	
	return nJoypadTriggerPedal;
}

//--------------------------------------------------
// �R���g���[���[�̐U������
//--------------------------------------------------
void JoypadVibration(int nTime, WORD nStrength, int nPlayer)
{
	s_nTime[nPlayer] = nTime;				// �U����������
	s_nStrength[nPlayer] = nStrength;		// �U���̋���
}

//--------------------------------------------------
// �W���C�p�b�h�̎g�p����Ă��邩�Ԃ�����
//--------------------------------------------------
bool IsJoyPadUse(int nPlayer)
{
	return s_bUseJoyPad[nPlayer];
}

//--------------------------------------------------
// �W���C�p�b�h�̃X�e�B�b�N�̃g���K�[����(�v���C���[�w��Ȃ�)
//--------------------------------------------------
bool GetJoypadStickTrigger(JOYKEY Stick, JOYKEY Key)
{
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		if (GetJoypadIdxStickTrigger(Stick, Key, i))
		{// �N�����w��̃X�e�B�b�N���w��̕����ɓ|����
			return true;
		}
	}

	return false;
}

//--------------------------------------------------
// �W���C�p�b�h�̃X�e�B�b�N�̃g���K�[����(�v���C���[�w�肠��)
//--------------------------------------------------
bool GetJoypadIdxStickTrigger(JOYKEY Stick, JOYKEY Key, int nPlayer)
{
	D3DXVECTOR3 stick = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	float fDeadZone = 0.0f;
	int nStick = 0;

	switch (Stick)
	{// �X�e�B�b�N�̎��
	case JOYKEY_LEFT_STICK:
		stick = D3DXVECTOR3((float)(s_JoyKeyState[nPlayer].Gamepad.sThumbLX), (float)(-s_JoyKeyState[nPlayer].Gamepad.sThumbLY), 0.0f);
		fDeadZone = XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;
		nStick = 0;
		break;

	case JOYKEY_RIGHT_STICK:
		stick = D3DXVECTOR3((float)(s_JoyKeyState[nPlayer].Gamepad.sThumbRX), (float)(-s_JoyKeyState[nPlayer].Gamepad.sThumbRY), 0.0f);
		fDeadZone = XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE;
		nStick = 1;
		break;

	default:
		assert(false);
		break;
	}

	switch (Key)
	{// �X�������
	case JOYKEY_UP:		// ��
		if (!s_bStick[nPlayer][nStick][0])
		{// ���X�e�B�b�N���X���ĂȂ�
			if (stick.y < -fDeadZone)
			{// ���X�e�B�b�N���X����
				s_bLean[nPlayer][nStick][0] = true;
				return true;
			}
		}
		break;

	case JOYKEY_DOWN:	// ��
		if (!s_bStick[nPlayer][nStick][1])
		{// ���X�e�B�b�N���X���ĂȂ�
			if (stick.y > fDeadZone)
			{// ���X�e�B�b�N���X����
				s_bLean[nPlayer][nStick][1] = true;
				return true;
			}
		}
		break;

	case JOYKEY_LEFT:	// ��
		if (!s_bStick[nPlayer][nStick][2])
		{// ���X�e�B�b�N���X���ĂȂ�
			if (stick.x < -fDeadZone)
			{// ���X�e�B�b�N���X����
				s_bLean[nPlayer][nStick][2] = true;
				return true;
			}
		}
		break;

	case JOYKEY_RIGHT:	// �E
		if (!s_bStick[nPlayer][nStick][3])
		{// ���X�e�B�b�N���X���ĂȂ�
			if (stick.x > fDeadZone)
			{// ���X�e�B�b�N���X����
				s_bLean[nPlayer][nStick][3] = true;
				return true;
			}
		}
		break;

	default:
		assert(false);
		break;
	}

	return false;
}

//**************************************************
// �}�E�X�̓��͏���
//**************************************************

//--------------------------------------------------
// �}�E�X�̏�����
//--------------------------------------------------
static HRESULT InitMouse(HINSTANCE hInstance, HWND hWnd)
{
	// DirectInput�I�u�W�F�N�g�̐���
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION,
		IID_IDirectInput8, (void**)&s_pMouseInput, NULL)))
	{
		return E_FAIL;
	}

	// ���̓f�o�C�X�i�}�E�X�j�̐���
	if (FAILED(s_pMouseInput->CreateDevice(GUID_SysMouse, &s_pDevMouse, NULL)))
	{
		return E_FAIL;
	}

	// �f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(s_pDevMouse->SetDataFormat(&c_dfDIMouse2)))
	{
		return E_FAIL;
	}

	// �������[�h��ݒ�
	if (FAILED(s_pDevMouse->SetCooperativeLevel(hWnd,
		(DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	//�E�B���h�E�n���h���̕ۊ�
	s_hMouseWnd = hWnd;

	// �L�[�{�[�h�ւ̃A�N�Z�X�����l��
	s_pDevMouse->Acquire();

	return S_OK;
}

//--------------------------------------------------
// �}�E�X�̏I������
//--------------------------------------------------
static void UninitMouse(void)
{
	if (s_pDevMouse != NULL)
	{
		s_pDevMouse->Unacquire();
		s_pDevMouse = NULL;
	}
}

//--------------------------------------------------
// �}�E�X�̍X�V����
//--------------------------------------------------
static void UpdateMouse(void)
{
	DIMOUSESTATE2 aKeyState;	// �}�E�X�̓��͏��

	// ���̓f�o�C�X����f�[�^���擾
	if (SUCCEEDED(s_pDevMouse->GetDeviceState(sizeof(aKeyState), &aKeyState)))
	{
		for (int nCntKey = 0; nCntKey < MOUSE_KEY_MAX; nCntKey++)
		{
			// �}�E�X�̃g���K�[����ۑ�
			s_aKeyStatetriggerMouse.rgbButtons[nCntKey] = ~s_aKeyStateMouse.rgbButtons[nCntKey] & aKeyState.rgbButtons[nCntKey];
		}

		// �}�E�X�̃v���X����ۑ�
		s_aKeyStateMouse = aKeyState;
	}
	else
	{
		s_pDevMouse->Acquire();		// �}�E�X�ւ̃A�N�Z�X�����l��
	}
}

//--------------------------------------------------
// �}�E�X�̃v���X����
//--------------------------------------------------
bool GetMousePress(MOUSE mouse)
{
	return (s_aKeyStateMouse.rgbButtons[mouse] & 0x80) != 0;

}

//--------------------------------------------------
// �}�E�X�̃g���K�[����
//--------------------------------------------------
bool GetMouseTrigger(MOUSE mouse)
{
	return (s_aKeyStatetriggerMouse.rgbButtons[mouse] & 0x80) != 0;
}

//--------------------------------------------------
// �}�E�X�|�C���^�[�̈ʒu
//--------------------------------------------------
D3DXVECTOR3 GetMouse(void)
{
	//��ʏ�̃}�E�X�|�C���^�[�̈ʒu
	GetCursorPos(&s_MousePos);
	//�E�B���h�E��̃}�E�X�|�C���^�[�̈ʒu
	ScreenToClient(s_hMouseWnd, &s_MousePos);

	return D3DXVECTOR3((float)s_MousePos.x, (float)s_MousePos.y, 0.0f);
}

//--------------------------------------------------
// �}�E�X�̃z�C�[���̓������m
//--------------------------------------------------
int GetMouseWheel(void)
{
	return (int)s_aKeyStateMouse.lZ;
}