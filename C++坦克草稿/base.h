#pragma once
#include<conio.h>
#include<time.h>
#include<vector>
#include<iostream>
#include<windows.h>
#include<Mmsystem.h>
#pragma comment(lib,"winmm.lib")
#include"Map.h"

using namespace std;

#define UP	0
#define DOWN	1
#define LEFT	2
#define RIGHT	3

#define �� 72
#define �� 80
#define �� 75
#define �� 77
#define ���� 49

//�Ʒֹ���
extern int nCount ;
//�ؿ�
extern int nLevel ;
//�༭��ͼ�ؿ�
extern int temp_level;
//�浵����
extern FILE* pFile;
//�����û�ѡ��
extern char nChoice ;

//���ݹ���ӡ
void WriteChar(int x, int y, const char* szBuf, int nColor = 0);
//���հ�������
char GetOper();
//̹�ˡ��ڵ��ĺ��ĺ���
void CoreInfo(int& level);
//��ӭ����
void Welcome(char & choice);
//�����ڵ���Ч
void  Sendout_bullet();
//����ʯǽ��Ч
void Smash_Stonewall();
//�༭��ͼ
void InitMap(int m_nMap[8][41][41], char & choice, int & level);
//��̹�� ����ͼ
void DrawAll(int level);
//����
void DrawHome();
//��ʼ��̹��
void Set_Tank();
//��ӡ���ڶ�ȡ
void PrintRead();
//��ӡ���ڴ浵
void PrintSave();
//��Ϸ���溯��
void GameStart();


//����
void ReadPassWordInfo();
//�浵
void SaveFile();