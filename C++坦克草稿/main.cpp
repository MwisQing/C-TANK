#include"CBullet.h"
#include"base.h"
#include"Map.h"
#include "CTank.h"


int main()
{
	//欢迎界面
	Welcome(nChoice);
	//初始化坦克
	Set_Tank();
	//游戏引擎
	GameStart();
	return 0;
}

