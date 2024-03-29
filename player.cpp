//====================
//プレイヤー設定
//autho hamada ryuuga
//====================

#include "main.h"
#include "Player.h"
#include "input.h"
#include "fade.h"
#include "sound.h"
#include "rectangle.h"
#include "wall.h"
#include "game.h"
#include "effect.h"
#include "utility.h"
#include "mode.h"
#include "color.h"
#include "gauge.h"
#include <stdio.h>
#include <assert.h>

#define DEAD_ZONE (0.1f)			// スティックの遊び
#define MAX_DIVECOUNT (15)			// ダイブの硬直時間
#define MAX_RESET_SPEED (7.0f)		// リセット状態の速さ
#define MAX_HAVE_COUNT (120)		// 持ってる時間の最大値
#define DISC_SPEED_X (2.0f)			// ディスクのXの速さ
#define DISC_SPEED_Y (5.0f)			// ディスクのYの速さ
#define LIMIT_POS_Y (140.0f)		// 移動制限の上壁
#define GAUGE_MAX_WIDTH (475.0f)	// ゲージの幅
#define GAUGE_MAX_HEIGHT (20.0f)	// ゲージの高さ
#define BLINK_START_TIME (180)		// 点滅の開始時間
#define FRAME_SIZE (4.0f)			// 枠のサイズ
#define TACKLE_SREED (2.0f)			// タックルの速度
#define MIN_COLOR (0.5f)			// 色の最小値
#define MAXPLAYERTYPE (5)			//Type最大数
#define MOVESPEED (5.0f)			//速度
#define TACKLESIZE (50.0f)			//タックルの当たり判定
#define INTERVALMAX (60)			//skillのインターバル
#define SKILLMAX (600)				//skillの制限時間
#define SKILLSETCOUNT (5)			//skillが何回やったら発生するかのカウント
#define MOVESKILL (1.1f)			//skill発生中の動きの倍率
#define POWSKILL (1.5f)				//skill発生中の攻撃の倍率
#define MAXTRACK (540)				//soundの時間

//スタティック変数///スタティックをヘッタに使うなよ？

static LPDIRECT3DTEXTURE9 s_pTexturePlayer[MAXPLAYERTYPE] = {}; //テクスチャのポインタ
static Player s_Player[MAXPLAYER];//プレイヤー構造体取得
static Player s_PlayerType[MAXPLAYERTYPE];//プレイヤーのTypeを保存する
static bool	s_bKeyBoardWASD;			// WASDのキーボード入力があるかどうか
static bool	s_bKeyBoardNumPad;			// テンキーのキーボード入力があるかどうか
static bool	s_bJoyPad[MAXPLAYER];		// ジョイパッド入力があるかどうか
static bool	s_bStickLeft[MAXPLAYER];	// 左スティック入力があるかどうか
static int	s_nIdxGauge[MAXPLAYER];		// スキルゲージの矩形のインデックス
static int	s_nIdxFrame[MAXPLAYER];		// 枠の矩形のインデックス
static int	s_nIdxMax[MAXPLAYER];		// 最大値の矩形のインデックス
static int sound;
static bool fastsound;

// スタティック関数プロトタイプ宣言
static void UpdateNormal(void);
static void UpdateReset(void);
static void InputMove(void);

//=======================
//プレイヤーの初期化設定
//=======================
void InitPlayer(void)
{
	sound = 0;
	LoadFile("data\\txt\\Status.txt");

	for (int count = 0; count < MAXPLAYER; count++)
	{
		
		s_Player[count].state = PLAYESTATE_NORMAL;
		s_Player[count].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		s_Player[count].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		s_Player[count].nLife = 5;
		s_Player[count].Speed = 0;
		s_Player[count].bHave = false;
		s_Player[count].bUse = false;
		s_Player[count].bDive = false;
		s_Player[count].fheight = PLAYERSIZE;
		s_Player[count].fwidth = PLAYERSIZE;
		s_Player[count].nSkill = 0;
		s_Player[count].nSkilltimer = 0;
		s_Player[count].nSkillInterval = 0;
		s_Player[count].nDiveCount = 0;
		s_Player[count].nHaveCount = 0;
		// 矩形の設定
		s_Player[count].nIdx = SetRectangleWithTex(s_pTexturePlayer[s_Player[count].nType]);
	}
	fastsound = false;
}

//===================
//終了処理
//===================
void UninitPlayer(void)
{
	//テクスチャの破棄
	for (int Tex = 0; Tex < MAXPLAYERTYPE; Tex++)
	{
		//テクスチャの破棄
		if (s_pTexturePlayer[Tex] != NULL)
		{
			s_pTexturePlayer[Tex]->Release();
			s_pTexturePlayer[Tex] = NULL;
		}
	}

	for (int count = 0; count < MAXPLAYER; count++)
	{
		// 使うのを止める
		StopUseRectangle(s_Player[count].nIdx);
		StopUseRectangle(s_nIdxGauge[count]);
	}
}

//===================
//更新処理
//===================
void UpdatePlayer(void)
{
	if (GetMode() != MODE_GAME)
	{// ゲーム状態じゃない
		return;
	}
		
	switch (GetGameState())
	{
	case GAMESTATE_NONE:	// 何もしていない状態
		break;

	case GAMESTATE_START:	// 開始状態
		break;

	case GAMESTATE_NORMAL:	// 通常状態
		UpdateNormal();
		break;

	case GAMESTATE_RESET:	// リセット状態
		UpdateReset();
		break;

	case GAMESTATE_END:		// 終了状態

		break;
	case GAMESTATE_RESULT:	// リザルト状態

		break;

	default:
		assert(false);
		break;
	}

}
//===================
//描画処理
//===================
void DrawPlayer(void)
{
}

//===================
//セット
//===================
void SetPlayer(D3DXVECTOR3 pos, int nType,bool light,float siz)
{
	for (int count = 0; count< MAXPLAYER; count++)
	{
		Player *pPlayer = &s_Player[count];

		if (s_Player[count].bUse)
		{
			continue;
		}

		s_Player[count].nSkilltimer = 0;
		s_Player[count].nSkillInterval = 0;
		s_Player[count].nSkill = 0;
		s_Player[count].bSkill = false;
		s_Player[count].nType = nType;
		s_Player[count].bUse = true;
		s_Player[count].pos = pos;

		s_Player[count].state = PLAYESTATE_NORMAL;
		s_Player[count].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		s_Player[count].nLife = 5;
		s_Player[count].Speed = s_PlayerType[nType].Speed;
		s_Player[count].Pow = s_PlayerType[nType].Pow;
		s_Player[count].fheight = siz;
		s_Player[count].fwidth = siz;
		s_Player[count].bHave = false;
		if (light)
		{
			D3DXVECTOR2 texU(1.0f, 0.0f);
			D3DXVECTOR2 texV(0.0f, 1.0f);

			// 矩形のテクスチャ座標の設定
			SetTexRectangle(pPlayer->nIdx, texU, texV);
		}
		else
		{
			D3DXVECTOR2 texU(0.0f, 1.0f);
			D3DXVECTOR2 texV(0.0f, 1.0f);

			// 矩形のテクスチャ座標の設定
			SetTexRectangle(pPlayer->nIdx, texU, texV);
		}

		// 矩形の回転する位置の設定
		SetRotationPosRectangle(pPlayer->nIdx, pPlayer->pos, pPlayer->rot, pPlayer->fwidth, pPlayer->fheight);
		
		break;
	}
}

//===================
//スキルゲージのセット
//===================
void SetGaugePlayer(void)
{
	float fFrameWidth = (FRAME_SIZE * 2.0f);
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT * 0.175f, 0.0f);

	// ゲージの設定
	s_nIdxFrame[0] = SetGauge(pos, GetColor(COLOR_WHITE), GAUGE_MAX_WIDTH + FRAME_SIZE, GAUGE_MAX_HEIGHT + fFrameWidth, GAUGE_LEFT);
	s_nIdxMax[0] = SetGauge(pos, GetColor(COLOR_BLACK), GAUGE_MAX_WIDTH, GAUGE_MAX_HEIGHT, GAUGE_LEFT);
	s_nIdxGauge[0] = SetGauge(pos, GetColor(COLOR_RED), 0.0f, GAUGE_MAX_HEIGHT, GAUGE_LEFT);

	pos.x = SCREEN_WIDTH;

	// ゲージの設定
	s_nIdxFrame[1] = SetGauge(pos, GetColor(COLOR_WHITE), GAUGE_MAX_WIDTH + FRAME_SIZE, GAUGE_MAX_HEIGHT + fFrameWidth, GAUGE_RIGHT);
	s_nIdxMax[1] = SetGauge(pos, GetColor(COLOR_BLACK), GAUGE_MAX_WIDTH, GAUGE_MAX_HEIGHT, GAUGE_RIGHT);
	s_nIdxGauge[1] = SetGauge(pos, GetColor(COLOR_BLUE), 0.0f, GAUGE_MAX_HEIGHT, GAUGE_RIGHT);
}

//----------------------------
//Playerのステータス読み込み
//----------------------------
void LoadFile(char *Filename)
{
	char	s_aString[256];//
	int		Num_Tex = 0;

	// ファイルポインタの宣言
	FILE* pFile;

	//ファイルを開く
	pFile = fopen(Filename, "r");
	int number = 0;

	if (pFile != NULL)
	{//ファイルが開いた場合
		fscanf(pFile, "%s", &s_aString);

		while (strncmp(&s_aString[0], "SCRIPT", 6) != 0)
		{//スタート来るまで空白読み込む
			s_aString[0] = {};
			fscanf(pFile, "%s", &s_aString[0]);
		}
		D3DXVECTOR3	s_modelMainpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		while (strncmp(&s_aString[0], "END_SCRIPT", 10) != 0)
		{// 文字列の初期化と読み込み// 文字列の初期化と読み込み

			fscanf(pFile, "%s", &s_aString[0]);

			if (strncmp(&s_aString[0], "#", 1) == 0)
			{//これのあとコメント
				fgets(&s_aString[0], sizeof(s_aString), pFile);
				continue;
			}

			if (strcmp(&s_aString[0], "TEXTURE_FILENAME") == 0)
			{
				fscanf(pFile, "%s", &s_aString[0]);	//＝読み込むやつ
				fscanf(pFile, "%s", &s_aString[0]);
				LPDIRECT3DDEVICE9  pDevice;
				//デバイスの取得
				pDevice = GetDevice();
				//テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,
					&s_aString[0],
					&s_pTexturePlayer[Num_Tex]);
				Num_Tex++;
				
			}
			if (strcmp(&s_aString[0], "STATUSSET") == 0)
			{
				while(1)
				{
					fscanf(pFile, "%s", &s_aString[0]);

					if (strcmp(&s_aString[0], "ATTACKPOW") == 0)
					{
						fscanf(pFile, "%s", &s_aString[0]);//＝読み込むやつ
						fscanf(pFile, "%f", &s_PlayerType[number].Pow);
					}
					if (strcmp(&s_aString[0], "MOVESPEED") == 0)
					{
						fscanf(pFile, "%s", &s_aString[0]);//＝読み込むやつ
						fscanf(pFile, "%f", &s_PlayerType[number].Speed);
					}
					if (strcmp(&s_aString[0], "ENDSET") == 0)
					{
						number++;
						break;
					}
				}
			}
		}
		//ファイルを閉じる
		fclose(pFile);
	}
}

//----------------------------
//Player動き
//----------------------------
void MovePlayer(void)
{
	// 移動の入力があるかないか
	InputMove();

	Disc *pDisc = GetDisc();

	if (GetKeyboardPress(DIK_A)|| GetKeyboardPress(DIK_W)|| GetKeyboardPress(DIK_S)|| GetKeyboardPress(DIK_D)
		|| GetKeyboardPress(DIK_NUMPAD1)|| GetKeyboardPress(DIK_NUMPAD2)
		|| GetKeyboardPress(DIK_NUMPAD3)|| GetKeyboardPress(DIK_NUMPAD5)
		|| GetJoypadStick(JOYKEY_LEFT_STICK, 0).y > DEAD_ZONE|| GetJoypadStick(JOYKEY_LEFT_STICK, 0).y < -DEAD_ZONE
		|| GetJoypadStick(JOYKEY_LEFT_STICK, 1).y > DEAD_ZONE || GetJoypadStick(JOYKEY_LEFT_STICK, 1).y < -DEAD_ZONE
		|| GetJoypadStick(JOYKEY_LEFT_STICK, 0).x > DEAD_ZONE || GetJoypadStick(JOYKEY_LEFT_STICK, 0).x < -DEAD_ZONE
		|| GetJoypadStick(JOYKEY_LEFT_STICK, 1).x > DEAD_ZONE || GetJoypadStick(JOYKEY_LEFT_STICK, 1).x < -DEAD_ZONE)
	{//歩き音
		if (!fastsound)
		{
			PlaySound(SOUND_LABEL_RUN);
		}
		fastsound = true;
		sound++;
		if(sound >= MAXTRACK)
		{
			fastsound = false;
			PlaySound(SOUND_LABEL_RUN);
		}
	}
	else
	{
		//サウンド停止
		StopSound(SOUND_LABEL_RUN);
		fastsound = false;
		sound = 0;
	}

	//---------------------------------------
	//１体目の行動
	//----------------------------------------
	if (!s_Player[0].bHave)
	{// ディスクを持っていない
		
		if (pDisc->nThrow == 0)
		{// 自分がディスクを投げた
			if (GetKeyboardPress(DIK_Q) && GetKeyboardPress(DIK_E))
			{
				pDisc->move.y = 0.0f;
			}
			else if (GetKeyboardPress(DIK_E))
			{
				pDisc->move.y = DISC_SPEED_Y;
			}
			else if (GetKeyboardPress(DIK_Q))
			{
				pDisc->move.y = -DISC_SPEED_Y;
			}

			if (GetJoypadStick(JOYKEY_RIGHT_STICK, 0).y > DEAD_ZONE)
			{// 右スティックが傾いた
				pDisc->move.y = DISC_SPEED_Y;
			}
			else if (GetJoypadStick(JOYKEY_RIGHT_STICK, 0).y < -DEAD_ZONE)
			{
				pDisc->move.y = -DISC_SPEED_Y;
			}
		}
		
		if (s_Player[0].bDive == true)
		{
			s_Player[0].nDiveCount++;
			SetEffect(D3DXVECTOR3(s_Player[0].pos.x + 30.0f, s_Player[0].pos.y + 10.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), EFFECTSTATE_TACKLE, 10, 100.0f, false);
			if (s_Player[0].nDiveCount >= MAX_DIVECOUNT)
			{
				s_Player[0].nDiveCount = 0;
				s_Player[0].bDive = false;
			}
		}
		else if (GetKeyboardTrigger(DIK_C) || GetJoypadIdxTrigger(JOYKEY_B, 0) ||
			GetJoypadIdxTrigger(JOYKEY_LEFT_SHOULDER, 0))
		{//タックル
			s_Player[0].pos.x += s_Player[0].Speed * 5;
			s_Player[0].bDive = true;
			s_Player[0].nDiveCount = 0;
		}
		else if (s_bKeyBoardWASD)
		{// キーボード
			D3DXVECTOR3 vec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			if (GetKeyboardPress(DIK_A))
			{// キーが押された
				vec.x -= 1.0f;
			}
			if (GetKeyboardPress(DIK_D))
			{// キーが押された
				vec.x += 1.0f;
			}
			if (GetKeyboardPress(DIK_W))
			{// キーが押された
				vec.y -= 1.0f;
			}
			if (GetKeyboardPress(DIK_S))
			{// キーが押された
				vec.y += 1.0f;
			}

			// ベクトルの正規化
			D3DXVec3Normalize(&vec, &vec);

			s_Player[0].move = vec * s_Player[0].Speed;
		}
		else if (s_bJoyPad[0])
		{// ジョイパッド
			D3DXVECTOR3 vec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			if (GetJoypadIdxPress(JOYKEY_LEFT, 0))
			{// ボタンが押された
				vec.x -= 1.0f;
			}
			if (GetJoypadIdxPress(JOYKEY_RIGHT, 0))
			{// ボタンが押された
				vec.x += 1.0f;
			}
			if (GetJoypadIdxPress(JOYKEY_UP, 0))
			{// ボタンが押された
				vec.y -= 1.0f;
			}
			if (GetJoypadIdxPress(JOYKEY_DOWN, 0))
			{// ボタンが押された
				vec.y += 1.0f;
			}

			// ベクトルの正規化
			D3DXVec3Normalize(&vec, &vec);

			s_Player[0].move = vec * s_Player[0].Speed;
		}
		else if (s_bStickLeft[0])
		{// 右スティックが傾いた
			D3DXVECTOR3 stick = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			stick.x = GetJoypadStick(JOYKEY_LEFT_STICK, 0).x;
			stick.y = GetJoypadStick(JOYKEY_LEFT_STICK, 0).y;

			// ベクトルの正規化
			D3DXVec3Normalize(&stick, &stick);

			s_Player[0].move = stick * s_Player[0].Speed;
		}
	}
	else
	{// ディスクを持っている
		s_Player[0].nHaveCount++;
		if (GetKeyboardTrigger(DIK_SPACE) || GetJoypadIdxTrigger(JOYKEY_A, 0) ||
			GetJoypadIdxTrigger(JOYKEY_RIGHT_SHOULDER, 0) || s_Player[0].nHaveCount >= MAX_HAVE_COUNT)
		{//ここに玉投げる動作（パワーを玉の速度にするといいんじゃないかな）
			s_Player[0].bHave = false;
			pDisc->nThrow = 0;
			
			//投げる音
			PlaySound(SOUND_LABEL_SHOT);

			//タイミングのによって速度変えるやつ
			int Ross = s_Player[0].nHaveCount / 10;
			pDisc->move = D3DXVECTOR3(DISC_SPEED_X - Ross*0.1f, 0.0f, 0.0f)*s_Player[0].Pow;
			if (s_Player[0].bSkill)
			{
				pDisc->move *= POWSKILL;
			}
			pDisc->bHave = false;
			s_Player[0].nHaveCount = 0;
		}
	}

	//---------------------------------------
	//２体目の行動
	//----------------------------------------
	if (!s_Player[1].bHave)
	{// ディスクを持っていない
		if (pDisc->nThrow == 1)
		{// 自分がディスクを投げた
			if (GetKeyboardPress(DIK_NUMPAD4) && GetKeyboardPress(DIK_NUMPAD6))
			{
				pDisc->move.y = 0.0f;
			}
			else if (GetKeyboardPress(DIK_NUMPAD6))
			{
				pDisc->move.y = DISC_SPEED_Y;
			}
			else if (GetKeyboardPress(DIK_NUMPAD4))
			{
				pDisc->move.y = -DISC_SPEED_Y;
			}

			if (GetJoypadStick(JOYKEY_RIGHT_STICK, 1).y > DEAD_ZONE)
			{// 左スティックが傾いた
				pDisc->move.y = DISC_SPEED_Y;
			}
			else if (GetJoypadStick(JOYKEY_RIGHT_STICK, 1).y < -DEAD_ZONE)
			{
				pDisc->move.y = -DISC_SPEED_Y;
			}
		}

		if (s_Player[1].bDive == true)
		{
			s_Player[1].nDiveCount++;
			SetEffect(D3DXVECTOR3(s_Player[1].pos.x-30.0f, s_Player[1].pos.y+10.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), EFFECTSTATE_TACKLE, 10, 100.0f, true);
			if (s_Player[1].nDiveCount >= MAX_DIVECOUNT)
			{
				s_Player[1].nDiveCount = 0;
				s_Player[1].bDive = false;
			}
		}
		else if (GetKeyboardTrigger(DIK_L) || GetJoypadIdxTrigger(JOYKEY_B, 1) ||
			GetJoypadIdxTrigger(JOYKEY_LEFT_SHOULDER, 1))
		{//タックル

			s_Player[1].pos.x -= s_Player[1].Speed * 5;
			s_Player[1].bDive = true;
			s_Player[1].nDiveCount = 0;
		}
		else if (s_bKeyBoardNumPad)
		{// キーボード
			D3DXVECTOR3 vec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			if (GetKeyboardPress(DIK_NUMPAD1))
			{// キーが押された
				vec.x -= 1.0f;
			}
			if (GetKeyboardPress(DIK_NUMPAD3))
			{// キーが押された
				vec.x += 1.0f;
			}
			if (GetKeyboardPress(DIK_NUMPAD5))
			{// キーが押された
				vec.y -= 1.0f;
			}
			if (GetKeyboardPress(DIK_NUMPAD2))
			{// キーが押された
				vec.y += 1.0f;
			}

			// ベクトルの正規化
			D3DXVec3Normalize(&vec, &vec);

			s_Player[1].move = vec * s_Player[1].Speed;
		}
		else if (s_bJoyPad[1])
		{// ジョイパッド
			D3DXVECTOR3 vec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			if (GetJoypadIdxPress(JOYKEY_LEFT, 1))
			{// ボタンが押された
				vec.x -= 1.0f;
			}
			if (GetJoypadIdxPress(JOYKEY_RIGHT, 1))
			{// ボタンが押された
				vec.x += 1.0f;
			}
			if (GetJoypadIdxPress(JOYKEY_UP, 1))
			{// ボタンが押された
				vec.y -= 1.0f;
			}
			if (GetJoypadIdxPress(JOYKEY_DOWN, 1))
			{// ボタンが押された
				vec.y += 1.0f;
			}

			// ベクトルの正規化
			D3DXVec3Normalize(&vec, &vec);

			s_Player[1].move = vec * s_Player[1].Speed;
		}
		else if (s_bStickLeft[1])
		{// 左スティック
			D3DXVECTOR3 stick = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			stick.x = GetJoypadStick(JOYKEY_LEFT_STICK, 1).x;
			stick.y = GetJoypadStick(JOYKEY_LEFT_STICK, 1).y;

			// ベクトルの正規化
			D3DXVec3Normalize(&stick, &stick);

			s_Player[1].move = stick * s_Player[1].Speed;
		}
	}
	else
	{// ディスクを持っている
		s_Player[1].nHaveCount++;
		if (GetKeyboardTrigger(DIK_RETURN) || GetJoypadIdxTrigger(JOYKEY_A, 1) ||
			GetJoypadIdxTrigger(JOYKEY_RIGHT_SHOULDER, 1) || s_Player[1].nHaveCount >= MAX_HAVE_COUNT)
		{//ここに玉投げる動作（パワーを玉の速度にするといいんじゃないかな）
			s_Player[1].bHave = false;
			pDisc->nThrow = 1;

			//投げる音
			PlaySound(SOUND_LABEL_SHOT);
			//skill使用可能な時のエフェクト
		
			//タイミングのによって速度変えるやつ
			int Ross = s_Player[1].nHaveCount / 10;
			pDisc->move = D3DXVECTOR3(-DISC_SPEED_X + Ross*0.1f, 0.0f, 0.0f) * s_Player[1].Pow;
			if (s_Player[1].bSkill)
			{
				pDisc->move *= POWSKILL;
			}
			pDisc->bHave = false;
			s_Player[1].nHaveCount = 0;
		}
	}
}

//----------------------------
//Player当たり判定
//----------------------------
bool CollisionPlayer(Disc *pDisc, float Size, int number)
{
	bool bIsLanding = false;
	Player *pPlayer = &s_Player[number];

	float fDiscSize = Size * 0.0f;
	float fHeight = (fDiscSize + (PLAYERSIZE * 0.5f));
	float fWidth = (fDiscSize + (PLAYERSIZE * 0.5f));

	if ((pDisc->pos.y <= (pPlayer->pos.y + fHeight)) &&
		(pDisc->pos.y >= (pPlayer->pos.y - fHeight)) &&
		(pDisc->pos.x <= (pPlayer->pos.x + fWidth)) &&
		(pDisc->pos.x >= (pPlayer->pos.x - fWidth)))
	{// プレイヤーにディスクが当たった時

		if (!pPlayer->bDive)
		{// ダイブしてない
			switch (number)
			{
			case 0:
				pDisc->pos.x = pPlayer->pos.x + fWidth;
				break;

			case 1:

				pDisc->pos.x = pPlayer->pos.x - fWidth;
				break;

			default:
				assert(false);
				break;
			}
			pDisc->pos.y = pPlayer->pos.y;
			pDisc->move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pDisc->bHave = true;
			pPlayer->move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			if (!pPlayer->bSkill)
			{
				pPlayer->nSkill++;
				if (pPlayer->nSkill >= SKILLSETCOUNT)
				{
					pPlayer->nSkill = 0;
					pPlayer->nSkilltimer = 0;
					pPlayer->nSkillInterval = 0;
					pPlayer->bSkill = true;
				}
			}
			pPlayer->bHave = true;
		}
		else
		{// ダイブしてる
			if (pDisc->nThrow == 1)
			{
				pDisc->nThrow = 0;
				s_Player[0].bDive = false;
				s_Player[0].nDiveCount = 0;
				pDisc->move = D3DXVECTOR3(DISC_SPEED_X, 0.0f, 0.0f)*s_Player[0].Pow * TACKLE_SREED;
			}
			else if (pDisc->nThrow == 0)
			{
				pDisc->nThrow = 1;
				s_Player[1].bDive = false;
				s_Player[1].nDiveCount = 0;
				pDisc->move = D3DXVECTOR3(-DISC_SPEED_X, 0.0f, 0.0f)*s_Player[1].Pow * TACKLE_SREED;
			}
		}
	
		bIsLanding = true;
	}

	return bIsLanding;
}

//----------------------------
//ゲージのリセット
//----------------------------
void ResetGaugePlayer(void)
{
	for (int count = 0; count < MAXPLAYER; count++)
	{
		// ゲージの変更
		ChangeGauge(s_nIdxGauge[count], 0.0f, GAUGE_MAX_HEIGHT);
	}
}

//----------------------------
//Player情報を取得
//----------------------------
Player* GetPlayer(void)
{
	return s_Player;
}

//----------------------------
// 通常状態の更新
//----------------------------
static void UpdateNormal(void)
{
	MovePlayer();

	for (int count = 0; count < MAXPLAYER; count++)
	{
		Player *pPlayer = &s_Player[count];

		//skill使用可能な時のエフェクト
		if (s_Player[count].bSkill)
		{
			s_Player[count].nSkillInterval++;

			if (s_Player[count].nSkillInterval >= INTERVALMAX)
			{
				s_Player[count].nSkilltimer++;
			}
			
			if (s_Player[count].nSkilltimer >= SKILLMAX)
			{
				s_Player[count].nSkilltimer = 0;
				s_Player[count].nSkillInterval = 0;
				s_Player[count].nSkill = 0;
				s_Player[count].bSkill = false;
			}
			else if (s_Player[count].nSkilltimer >= (SKILLMAX - BLINK_START_TIME))
			{
				D3DXCOLOR col = GetColor(COLOR_WHITE);
				float fCurve = cosf((s_Player[count].nSkilltimer * 0.1f) * (D3DX_PI * 2.0f));

				switch (count)
				{
				case 0:

					col = GetColor(COLOR_RED);
					col.r = (((fCurve + 1.0f) * 0.5f) * (1.0f - MIN_COLOR)) + MIN_COLOR;
					break;

				case 1:
					col = GetColor(COLOR_BLUE);
					col.b = (((fCurve + 1.0f) * 0.5f) * (1.0f - MIN_COLOR)) + MIN_COLOR;
					break;

				default:
					assert(false);
					break;
				}
				
				// ゲージの色の設定
				SetColorGauge(s_nIdxGauge[count], col);
			}
  			
			s_Player[count].move*= MOVESKILL;
			SetEffect(D3DXVECTOR3(s_Player[count].pos.x, s_Player[count].pos.y - 70.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), EFFECTSTATE_SHOOT, 10, 200.0f, false);
		}

		float fWidth = 0.0f;

		if (s_Player[count].bSkill)
		{
			fWidth = GAUGE_MAX_WIDTH - ((GAUGE_MAX_WIDTH / SKILLMAX) * s_Player[count].nSkilltimer);
		}
		else
		{
			fWidth = (GAUGE_MAX_WIDTH / SKILLSETCOUNT) * s_Player[count].nSkill;
		}

		// ゲージの変更
		ChangeGauge(s_nIdxGauge[count], fWidth, GAUGE_MAX_HEIGHT);

		//移動量を更新(減衰させる)
		s_Player[count].move.x += (0.0f - s_Player[count].move.x)*0.2f;//（目的の値-現在の値）＊減衰係数											  
		s_Player[count].move.y += (0.0f - s_Player[count].move.y)*0.2f;//（目的の値-現在の値）＊減衰係数

			//前回の位置の保存
		s_Player[count].posOld = s_Player[count].pos;
		//更新
		s_Player[count].pos.x += s_Player[count].move.x;
		s_Player[count].pos.y += s_Player[count].move.y;

		//壁---------------------------------------------------
		if (s_Player[count].pos.x <= PLAYER_POS_X + pPlayer->fwidth)
		{//横壁（左）
			s_Player[count].pos.x = PLAYER_POS_X + pPlayer->fwidth;
		}
		else if (s_Player[count].pos.x >= SCREEN_WIDTH - PLAYER_POS_X - pPlayer->fwidth)
		{//横壁（右）
			s_Player[count].pos.x = SCREEN_WIDTH - PLAYER_POS_X - pPlayer->fwidth;
		}
		if (s_Player[count].pos.y <= LIMIT_POS_Y + pPlayer->fheight / 2.0f+ WALLSIZ_Y /2)
		{//上壁　
			s_Player[count].pos.y = LIMIT_POS_Y + pPlayer->fheight / 2.0f + WALLSIZ_Y / 2;
		}
		if (s_Player[count].pos.y >= SCREEN_HEIGHT - pPlayer->fheight / 2.0f - WALLSIZ_Y / 2)
		{//下壁
			s_Player[count].pos.y = SCREEN_HEIGHT - pPlayer->fheight / 2.0f - WALLSIZ_Y / 2;
		}
		//真ん中ライン
		if (s_Player[0].pos.x >= SCREEN_WIDTH* 0.5f - PLAYER_POS_X - pPlayer->fwidth / 2.0f)
		{
			s_Player[0].pos.x = SCREEN_WIDTH* 0.5f - PLAYER_POS_X - pPlayer->fwidth / 2.0f;
		}
		if (s_Player[1].pos.x <= SCREEN_WIDTH * 0.5f + PLAYER_POS_X + pPlayer->fwidth / 2.0f)
		{
			s_Player[1].pos.x = SCREEN_WIDTH * 0.5f + PLAYER_POS_X + pPlayer->fwidth / 2.0f;
		}
	
		// 矩形の回転する位置の設定
		SetRotationPosRectangle(pPlayer->nIdx, pPlayer->pos, pPlayer->rot, pPlayer->fwidth, pPlayer->fheight);
	}
}

//----------------------------
// リセット状態の更新
//----------------------------
static void UpdateReset(void)
{
	bool bOverlap[MAXPLAYER];

	for (int nPlayerNo = 0; nPlayerNo < MAXPLAYER; nPlayerNo++)
	{
		Player *pPlayer = &s_Player[nPlayerNo];

		bOverlap[nPlayerNo] = false;

		D3DXVECTOR3 posDest;
		
		switch (nPlayerNo)
		{
		case 0:
			posDest = D3DXVECTOR3(PLAYERSIZE + PLAYER_POS_X, SCREEN_HEIGHT * 0.6f, 0.0f);
			break;

		case 1:
			posDest = D3DXVECTOR3(SCREEN_WIDTH - PLAYERSIZE - PLAYER_POS_X, SCREEN_HEIGHT * 0.6f, 0.0f);
			break;
		
		default:
			posDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			assert(false);
			break;
		}

		// ホーミング
		bOverlap[nPlayerNo] = Homing(&pPlayer->pos, pPlayer->pos, posDest, MAX_RESET_SPEED);
		
		// 矩形の回転する位置の設定
		SetRotationPosRectangle(pPlayer->nIdx, pPlayer->pos, pPlayer->rot, pPlayer->fwidth, pPlayer->fheight);

		pPlayer->bDive = false;
		pPlayer->nDiveCount = 0;
	}
}

//----------------------------
// 移動の入力があるかないか
//----------------------------
static void InputMove(void)
{
	s_bKeyBoardWASD = false;
	s_bKeyBoardNumPad = false;

	for (int i = 0; i < MAXPLAYER; i++)
	{
		s_bJoyPad[i] = false;
		s_bStickLeft[i] = false;
	}

	if (GetKeyboardPress(DIK_A) || GetKeyboardPress(DIK_D) ||
		GetKeyboardPress(DIK_W) || GetKeyboardPress(DIK_S))
	{// キーが押された
		s_bKeyBoardWASD = true;
	}

	if (GetKeyboardPress(DIK_NUMPAD1) || GetKeyboardPress(DIK_NUMPAD3) ||
		GetKeyboardPress(DIK_NUMPAD5) || GetKeyboardPress(DIK_NUMPAD2))
	{// キーが押された
		s_bKeyBoardNumPad = true;
	}

	for (int i = 0; i < MAXPLAYER; i++)
	{
		if (GetJoypadIdxPress(JOYKEY_LEFT, i) || GetJoypadIdxPress(JOYKEY_RIGHT, i) ||
			GetJoypadIdxPress(JOYKEY_UP, i) || GetJoypadIdxPress(JOYKEY_DOWN, i))
		{// ボタンが押された
			s_bJoyPad[i] = true;
		}

		if (GetJoypadStick(JOYKEY_LEFT_STICK, i).x > DEAD_ZONE ||
			GetJoypadStick(JOYKEY_LEFT_STICK, i).x < -DEAD_ZONE ||
			GetJoypadStick(JOYKEY_LEFT_STICK, i).y > DEAD_ZONE ||
			GetJoypadStick(JOYKEY_LEFT_STICK, i).y < -DEAD_ZONE)
		{// 左スティックが傾いた
			s_bStickLeft[i] = true;
		}
	}
}
