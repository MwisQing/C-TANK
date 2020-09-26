#pragma once
#include"base.h"


//炮弹类
class BULLET
{
public:
	
	//清除炮弹 并且不再是新的炮弹
	void ClearBullet(int x, int y, int i, int level);

	//画炮弹
	void DrawBullet(int x, int y, int colof, int play_enemy, int level);

	//判断炮弹的碰撞    翻译：如果碰撞
	int IfCollide(int x, int y, int i,int player_enemy, int level);

	//移动炮弹  里面包含了清除炮弹  画炮弹
	void MoveBullet( int level);

	//按下j后改变vector
	void SetBullet_vector(int nDir, int x, int y,int play_enemy);
	//改变炮弹时间的接口
	void BULLET::SetTime(BULLET & blt);

	//友元函数
	friend void CoreInfo(int& level);
	
	
private:
	COORD pos;
	int nDir;
	//炮弹移动的速度
	int nSpeed;
	//炮弹记录的时间
	int nLastClock;
	//判断炮弹是否存在
	int nExist;
	//判断是否是新炮弹
	int isNew;
	//判断是敌方炮弹还是玩家炮弹
	int nBullet_player_enemy;
};

//炮弹数组
extern vector<BULLET>bullet;

//炮弹类对象(工具对象)
extern BULLET bullet_temp;

