#include "CBullet.h"
#include"CTank.h"

//炮弹动态数组
extern vector<BULLET>bullet = {};

//炮弹对象(工具对象)调用函数专用
extern BULLET bullet_temp = {};

/********************************************************
函数功能	:清除炮弹，并且标记为旧炮弹
参数		:炮弹的坐标，炮弹数组的下标，关卡
返回值	:无
*********************************************************/
void BULLET::ClearBullet(int x, int y, int i, int level)
{
	if (bullet[i].nExist == 1)
	{
		WriteChar(x, y, "  ");
		bullet[i].isNew = 0;
		m_nMap[level][y][x] = 0;
	}
}

/********************************************************
函数功能	:画炮弹
参数		:炮弹的坐标，颜色，炮弹的阵营，关卡
返回值	:无
*********************************************************/
void BULLET::DrawBullet(int x, int y, int color, int play_enemy, int level)
{
	WriteChar(x, y, "☉", color);
	m_nMap[level][y][x] = play_enemy;
}

/********************************************************
函数功能	:判断炮弹的碰撞
参数		:炮弹的坐标，炮弹数组的下标，炮弹的阵营，关卡
返回值	:无
*********************************************************/
int BULLET::IfCollide(int x, int y, int i,int player_enemy, int level)
{
	//石墙 可击碎
	if (m_nMap[level][y][x] == WALL)
	{
		WriteChar(x, y, "  ");
		m_nMap[level][y][x] = GROUND;
		bullet[i].nExist = 0;
		Smash_Stonewall();
		return 0;
	}
	//草 可破坏
	if (m_nMap[level][y][x] == GRASS)
	{
		WriteChar(x, y, "  ");
		m_nMap[level][y][x] = GROUND;
		bullet[i].nExist = 0;
		Smash_Stonewall();
		return 0;
	}
	//铁墙不可击碎
	if (m_nMap[level][y][x] == STEEL)
	{
		bullet[i].nExist = 0;
		return 0;
	}
	//围墙不可击碎
	if (m_nMap[level][y][x] == FRAME)
	{
		bullet[i].nExist = 0;
		return 0;
	}
	//水
	if (m_nMap[level][y][x] == WATER)
	{
		bullet[i].nExist = 1;
		return 1;
	}
	//空地
	if (m_nMap[level][y][x] == GROUND)
	{
		return 1;
	}
	//家
	if (m_nMap[level][y][x] == HOME)
	{
		WriteChar(x, y, "  ");
		m_nMap[level][y][x] = HOME;
		bullet[i].nExist = 0;
		g_stcTank.SetTankIfExist(0, g_stcTank);
		g_stcTank2.SetTankIfExist(0, g_stcTank2);
		return 1;
	}
	if (x > 41 || y > 41)
	{
		bullet[i].nExist = 0;
		return 0;
	}
	if (m_nMap[level][y][x] == 敌方坦克0)
	{
		bullet[i].nExist = 0;
		if (player_enemy == 玩家炮弹)
		{
			g_Tank_Enemy_temp.SetTankIfExist(0,g_Tank_Enemy_temp);
			nCount += 1000;
		}
		return 0;
	}
	if (m_nMap[level][y][x] == 敌方坦克1)
	{
		bullet[i].nExist = 0;
		if (player_enemy == 玩家炮弹)
		{
			g_Tank_Enemy_temp2.SetTankIfExist(0, g_Tank_Enemy_temp2);
			nCount += 1000;
		}
		return 0;
	}
	if (m_nMap[level][y][x] == 玩家坦克0)
	{
		bullet[i].nExist = 0;
		if (player_enemy == 敌方炮弹)
		{
			g_stcTank.SetTankIfExist(0, g_stcTank);
		}
		return 0;
	}
	if (m_nMap[level][y][x] == 玩家坦克1)
	{
		bullet[i].nExist = 0;
		if (player_enemy == 敌方炮弹)
		{
			g_stcTank2.SetTankIfExist(0, g_stcTank2);
		}
		return 0;
	}
	else
	{
		return 0;
	}
}

/********************************************************
函数功能	:移动炮弹，调用 清除炮弹  画炮弹
参数		:关卡
返回值	:无
*********************************************************/
void BULLET::MoveBullet(int level)
{
	for (int i = 0; i < bullet.size(); i++)
	{
		//只有时间差 == 200  才画
		if (clock() - bullet[i].nLastClock >= bullet[i].nSpeed)
		{
			//判断炮弹的碰撞
			if (IfCollide(bullet[i].pos.X, bullet[i].pos.Y, i, bullet[i].nBullet_player_enemy,level) == 0 && m_nMap[level][bullet[i].pos.Y][bullet[i].pos.X] != WATER)
			{
				ClearBullet(bullet[i].pos.X, bullet[i].pos.Y, i, level);
			}
			if (bullet[i].nExist != 0 && m_nMap[level][bullet[i].pos.Y][bullet[i].pos.X] != WATER)
			{
				ClearBullet(bullet[i].pos.X, bullet[i].pos.Y, i, level);
			}
			if (m_nMap[level][bullet[i].pos.Y][bullet[i].pos.X] == WATER)
			{
				bullet[i].isNew = 0;
			}
			//重新计时间差
			bullet[i].nLastClock = clock();
			//只画存在的炮弹并且不是新的炮弹
			if (bullet[i].nExist != 0 && bullet[i].isNew == 0)
			{
				//条件成立则进来移动炮弹
				switch (bullet[i].nDir)
				{
				case UP:
					bullet[i].pos.Y--;
					break;
				case DOWN:
					bullet[i].pos.Y++;
					break;
				case LEFT:
					bullet[i].pos.X--;
					break;
				case RIGHT:
					bullet[i].pos.X++;
					break;
				default:
					break;
				}
				//标记是否摧毁的常量
				int bullet_sign = 0;
				bullet_sign = IfCollide(bullet[i].pos.X, bullet[i].pos.Y, i, bullet[i].nBullet_player_enemy, level);

				//判断炮弹是否与炮弹相撞，互相销毁
				for (int j = 0; j < bullet.size(); j++)
				{
					if (bullet[i].nDir != bullet[j].nDir)
					{
						if (bullet[i].pos.X == bullet[j].pos.X && bullet[i].pos.Y == bullet[j].pos.Y)
						{
							ClearBullet(bullet[i].pos.X, bullet[i].pos.Y, i, level);
							ClearBullet(bullet[j].pos.X, bullet[j].pos.Y, j, level);
							bullet[i].nExist = 0;
							bullet[j].nExist = 0;
							bullet.erase(bullet.begin() + j);
							j--;
							if (i != 0)
							{
								i--;
							}
						}
					}
				}

				if (bullet[i].nExist != 0 && m_nMap[level][bullet[i].pos.Y][bullet[i].pos.X] != WATER)
				{
					//确认碰撞无误
					//然后画炮弹
					DrawBullet(bullet[i].pos.X, bullet[i].pos.Y, 0x0004 | 0x0002 | 0x0001, bullet[i].nBullet_player_enemy, level);
				}

				//标记是否摧毁
				if (bullet_sign == 0)
				{
					bullet.erase(bullet.begin() + i);
					i--;
				}

			}
		}
	}
}


/********************************************************
函数功能	:创建炮弹
参数		:坦克方向，坦克坐标，坦克阵营
返回值	:无
*********************************************************/
void BULLET::SetBullet_vector(int nDir, int x, int y,int play_enemy)
{
	BULLET temp;
	temp.nDir;
	temp.nSpeed = 100;
	temp.nLastClock = clock();
	temp.nExist = 1;
	temp.isNew = 1;
	temp.nBullet_player_enemy = play_enemy;
	switch (nDir)
	{
	case UP:
		temp.nDir = nDir;
		temp.pos.X = x;
		temp.pos.Y = y - 2;
		break;
	case DOWN:
		temp.nDir = nDir;
		temp.pos.X = x;
		temp.pos.Y = y + 2;
		break;
	case LEFT:
		temp.nDir = nDir;
		temp.pos.X = x - 2;
		temp.pos.Y = y;
		break;
	case RIGHT:
		temp.nDir = nDir;
		temp.pos.X = x + 2;
		temp.pos.Y = y;
		break;
	default:
		break;
	}
	bullet.insert(bullet.end(), temp);
}

/********************************************************
函数功能	:改变炮弹时间，让他读档后立刻发射
参数		:炮弹对象
返回值	:无
*********************************************************/
void BULLET::SetTime(BULLET & blt)
{
	blt.nLastClock = -100;
}