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

#define 上 72
#define 下 80
#define 左 75
#define 右 77
#define 发射 49

//计分功能
extern int nCount ;
//关卡
extern int nLevel ;
//编辑地图关卡
extern int temp_level;
//存档读档
extern FILE* pFile;
//接收用户选择
extern char nChoice ;

//根据光标打印
void WriteChar(int x, int y, const char* szBuf, int nColor = 0);
//接收按键操作
char GetOper();
//坦克、炮弹的核心函数
void CoreInfo(int& level);
//欢迎界面
void Welcome(char & choice);
//发出炮弹音效
void  Sendout_bullet();
//击碎石墙音效
void Smash_Stonewall();
//编辑地图
void InitMap(int m_nMap[8][41][41], char & choice, int & level);
//画坦克 画地图
void DrawAll(int level);
//画家
void DrawHome();
//初始化坦克
void Set_Tank();
//打印正在读取
void PrintRead();
//打印正在存档
void PrintSave();
//游戏引擎函数
void GameStart();


//读档
void ReadPassWordInfo();
//存档
void SaveFile();