#pragma once
//地图数组
extern int m_nMap[8][41][41];
//地图的宏
#define WALL			1	//'▓' 可摧毁
#define FRAME			4	//'■'不可摧毁
#define HOME			9	//'★'家
#define STEEL			6	//'■'不可摧毁
#define WATER			5	//'~' 水
#define GROUND		0	//空地
#define GRASS			2   //※ 草

#define 敌方炮弹		11
#define 玩家炮弹		12
#define 敌方坦克0		13
#define 玩家坦克0		14
#define 敌方坦克1		15
#define 玩家坦克1		16
//画地图
void DrawMap(int level);