/*==============================================================================

    �A�C�X�e�B�[ [icetea.h]
                                                       Author : Norihiro Hayashi
                                                       Date   : 2016/5/31
--------------------------------------------------------------------------------
    ��Update : 2016/5/31

==============================================================================*/

#ifndef _ICETEA_H_
#define _ICETEA_H_

#include"main.h"

//#include <math.h>	//�}�X�w�b�_

void InitIcetea (void);
void UninitIcetea (void);
void UpdateIcetea(void);
void DrawIcetea(void);

void SetVertexIcetea ( VERTEX_2D *pVtx );

#endif