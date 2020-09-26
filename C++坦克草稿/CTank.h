#pragma once
#include<Windows.h>
#include"base.h"
#include "CAStar.h"

//坦克类
class TANK
{
public:
	//初始化坦克的中心位置
	void initialization_TANK(TANK& tank, int num, int x, int y);

	//判断障碍物
	int IfTankCollide(int x, int y, int dir, int level);

	//画坦克
	void DrawTank(TANK Tank, int color,int num, int level);

	//在坦克移动之前 把原先的坦克清除 然后再画新的
	void ClearTank(TANK Tank, int level);

	//友元函数
	friend void CoreInfo(int & level);
	//移动玩家坦克
	void MovePlayerTank(char cOper, int level);
	//移动玩家2坦克
	void MovePlayerTank2(char cOper, int level);
	//移动地方坦克
	void MoveEnemyTank(char& Random_Dir, int level, TANK &tank, int color);

	//初始化敌方坦克
	void Set_EnemyTank();
	//初始化敌方坦克2
	void Set_EnemyTank2();

	//随机改变敌方坦克方向
	void GetEnemyTankDir(int& time, char& dir, int& num, int ntime, TANK tank,int level, TANK tank2);

	//坦克死亡的时候，改变存活的标志
	void SetTankIfExist(int exist, TANK & tank);

private:
	//COORD是一个结构体存放 x轴 y轴
	//pos 存放坦克的中心位置
	COORD pos;
	//方向
	int nDir;
	//判断坦克是否存活
	int nTank_Exist;
	//每一个坦克的标记都不一样
	//#define 敌方坦克0		13
	//#define 玩家坦克0		14
	int nTank_Play_or_Enemy;
};

//定义一个玩家坦克的对象
extern TANK g_stcTank;
//定义一个玩家坦克2的对象
extern TANK g_stcTank2;

//定义一个敌方坦克对象
extern TANK g_Tank_Enemy_temp;
//定义一个敌方坦克对象
extern TANK g_Tank_Enemy_temp2;

