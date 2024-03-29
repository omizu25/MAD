//========================================================
//
//UI
//Author:ûüì]
//
//========================================================
#ifndef _UI_H_
#define _UI_H_

#include "main.h"
//====================================
//UI\¢ÌÌè`
//====================================
typedef struct
{
	D3DXVECTOR3 pos;	//Êu
	D3DXVECTOR3 scale;	//gå¦
	float nCnt;			//êx¾¯g¤
	float nCntTime;		//o»Ô
	float fWidth;		//
	float fHeight;		//³
	int nType;			//íÞ
	int nTexture;		//eNX`Ô
	bool bUse;			//gpµÄ¢é©Ç¤©
	bool bSwitch;		//oÄ­é©Á¦Ä¢­©
}Ui;
//====================================
//vg^Cvé¾
//====================================
void InitUi(void);
void UninitUi(void);
void UpdateUi(void);
void DrawUi(void);
void SetUi(D3DXVECTOR3 pos, float fWidth, float fHeight, int nType, D3DXVECTOR3 scale, int nTexture);
Ui * GetUi(void);

#endif