#include "CTank.h"
#include "CBullet.h"

//定义一个玩家坦克
extern TANK g_stcTank = {};
//定义一个玩家2坦克
extern TANK g_stcTank2 = {};

//定义敌方坦克数组
extern vector<TANK>g_Tank_Enemy[1] = {};
//定义一个敌方坦克对象
extern TANK g_Tank_Enemy_temp = {};
//定义一个敌方坦克对象2
extern TANK g_Tank_Enemy_temp2 = {};

/********************************************************
函数功能	:初始化敌方坦克1
参数		:无
返回值	:无
*********************************************************/
void TANK::Set_EnemyTank()
{
	g_Tank_Enemy_temp.nDir = DOWN;
	g_Tank_Enemy_temp.pos.X = 2;
	g_Tank_Enemy_temp.pos.Y = 2;
	g_Tank_Enemy_temp.nTank_Exist = 1;
	//敌方坦克
	g_Tank_Enemy_temp.nTank_Play_or_Enemy = 敌方坦克0;
}

/********************************************************
函数功能	:初始化敌方坦克2
参数		:无
返回值	:无
*********************************************************/
void TANK::Set_EnemyTank2()
{
	g_Tank_Enemy_temp2.nDir = DOWN;
	g_Tank_Enemy_temp2.pos.X = 38;
	g_Tank_Enemy_temp2.pos.Y = 2;
	g_Tank_Enemy_temp2.nTank_Exist = 1;
	//敌方坦克
	g_Tank_Enemy_temp2.nTank_Play_or_Enemy = 敌方坦克1;
}

/********************************************************
函数功能	:判断障碍物
参数		:地图数组坐标，坦克方向，关卡
返回值	:int类型 0 or 1
*********************************************************/
int TANK::IfTankCollide(int x, int y, int dir,int level)
{
	//如果遇到障碍物
	switch (dir)
	{
	case UP:
		if ((m_nMap[level][y - 1][x + 1] == GROUND || m_nMap[level][y - 1][x + 1] == GRASS) && (m_nMap[level][y - 1][x - 1] == GROUND || m_nMap[level][y - 1][x - 1] == GRASS) && (m_nMap[level][y - 1][x] == GROUND || m_nMap[level][y - 1][x] == GRASS))
		{
			return 1;
		}
		else
		{
			return 0;
		}
		break;
	case DOWN:
		if ((m_nMap[level][y + 1][x + 1] == GROUND || m_nMap[level][y + 1][x + 1] == GRASS) && (m_nMap[level][y + 1][x - 1] == GROUND || m_nMap[level][y + 1][x - 1] == GRASS) && (m_nMap[level][y + 1][x] == GROUND || m_nMap[level][y + 1][x] == GRASS))
		{
			return 1;
		}
		else
		{
			return 0;
		}
		break;
	case LEFT:
		if ((m_nMap[level][y - 1][x - 1] == GROUND || m_nMap[level][y - 1][x - 1] == GRASS) && (m_nMap[level][y][x - 1] == GROUND || m_nMap[level][y][x - 1] == GRASS) && (m_nMap[level][y + 1][x - 1] == GROUND || m_nMap[level][y + 1][x - 1] == GRASS))
		{
			return 1;
		}
		else
		{
			return 0;
		}
		break;
	case RIGHT:
		if ((m_nMap[level][y - 1][x + 1] == GROUND || m_nMap[level][y - 1][x + 1] == GRASS) && (m_nMap[level][y][x + 1] == GROUND || m_nMap[level][y][x + 1] == GRASS) && (m_nMap[level][y + 1][x + 1] == GROUND || m_nMap[level][y + 1][x + 1] == GRASS))
		{
			return 1;
		}
		else
		{
			return 0;
		}
		break;
	default:
		break;
	}
}


/********************************************************
函数功能	:画坦克
参数		:坦克对象，颜色，坦克在地图上的数字，关卡
返回值	:无
*********************************************************/
void TANK::DrawTank(TANK Tank,int color,int num,int level)
{
	if (Tank.nTank_Exist == 1)
	{
		//用简短的x y  来代替 "命名很长的" 坦克的x轴 y轴 
		int x = Tank.pos.X;
		int y = Tank.pos.Y;
		//根据方向打印坦克
		switch (Tank.nDir)
		{
		case UP:

			if (m_nMap[level][y - 1][x - 1] != GRASS)
			{
				m_nMap[level][y - 1][x - 1] = 0;
				WriteChar(x - 1, y - 1, "  ", color);
			}
			if (m_nMap[level][y - 1][x] != GRASS)
			{
				m_nMap[level][y - 1][x] = num;
				WriteChar(x, y - 1, "■", color);
			}
			if (m_nMap[level][y - 1][x + 1] != GRASS)
			{
				m_nMap[level][y - 1][x + 1] = 0;
				WriteChar(x + 1, y - 1, "  ", color);
			}
			if (m_nMap[level][y][x] != GRASS)
			{
				m_nMap[level][y][x] = num;
				WriteChar(x, y, "■", color);
			}
			if (m_nMap[level][y][x - 1] != GRASS)
			{
				m_nMap[level][y][x - 1] = num;
				WriteChar(x - 1, y, "■", color);
			}
			if (m_nMap[level][y][x + 1] != GRASS)
			{
				m_nMap[level][y][x + 1] = num;
				WriteChar(x + 1, y, "■", color);
			}
			if (m_nMap[level][y + 1][x - 1] != GRASS)
			{
				m_nMap[level][y + 1][x - 1] = num;
				WriteChar(x - 1, y + 1, "■", color);
			}
			if (m_nMap[level][y + 1][x] != GRASS)
			{
				m_nMap[level][y + 1][x] = 0;
				WriteChar(x, y + 1, "  ", color);
			}
			if (m_nMap[level][y + 1][x + 1] != GRASS)
			{
				m_nMap[level][y + 1][x + 1] = num;
				WriteChar(x + 1, y + 1, "■", color);
			}
			break;
		case DOWN:
			if (m_nMap[level][y - 1][x - 1] != GRASS)
			{
				m_nMap[level][y - 1][x - 1] = num;
				WriteChar(x - 1, y - 1, "■", color);
			}
			if (m_nMap[level][y - 1][x] != GRASS)
			{
				m_nMap[level][y - 1][x] = 0;
				WriteChar(x, y - 1, "  ", color);
			}
			if (m_nMap[level][y - 1][x + 1] != GRASS)
			{
				m_nMap[level][y - 1][x + 1] = num;
				WriteChar(x + 1, y - 1, "■", color);
			}
			if (m_nMap[level][y][x] != GRASS)
			{
				m_nMap[level][y][x] = num;
				WriteChar(x, y, "■", color);
			}
			if (m_nMap[level][y][x - 1] != GRASS)
			{
				m_nMap[level][y][x - 1] = num;
				WriteChar(x - 1, y, "■", color);
			}
			if (m_nMap[level][y][x + 1] != GRASS)
			{
				m_nMap[level][y][x + 1] = num;
				WriteChar(x + 1, y, "■", color);
			}
			if (m_nMap[level][y + 1][x - 1] != GRASS)
			{
				m_nMap[level][y + 1][x - 1] = 0;
				WriteChar(x - 1, y + 1, "  ", color);
			}
			if (m_nMap[level][y + 1][x] != GRASS)
			{
				m_nMap[level][y + 1][x] = num;
				WriteChar(x, y + 1, "■", color);
			}
			if (m_nMap[level][y + 1][x + 1] != GRASS)
			{
				m_nMap[level][y + 1][x + 1] = 0;
				WriteChar(x + 1, y + 1, "  ", color);
			}
			break;
		case LEFT:
			if (m_nMap[level][y - 1][x - 1] != GRASS)
			{
				m_nMap[level][y - 1][x - 1] = 0;
				WriteChar(x - 1, y - 1, "  ", color);
			}
			if (m_nMap[level][y - 1][x] != GRASS)
			{
				m_nMap[level][y - 1][x] = num;
				WriteChar(x, y - 1, "■", color);
			}
			if (m_nMap[level][y - 1][x + 1] != GRASS)
			{
				m_nMap[level][y - 1][x + 1] = num;
				WriteChar(x + 1, y - 1, "■", color);
			}
			if (m_nMap[level][y][x] != GRASS)
			{
				m_nMap[level][y][x] = num;
				WriteChar(x, y, "■", color);
			}
			if (m_nMap[level][y][x - 1] != GRASS)
			{
				m_nMap[level][y][x - 1] = num;
				WriteChar(x - 1, y, "■", color);
			}
			if (m_nMap[level][y][x + 1] != GRASS)
			{
				m_nMap[level][y][x + 1] = 0;
				WriteChar(x + 1, y, "  ", color);
			}
			if (m_nMap[level][y + 1][x - 1] != GRASS)
			{
				m_nMap[level][y + 1][x - 1] = 0;
				WriteChar(x - 1, y + 1, "  ", color);
			}
			if (m_nMap[level][y + 1][x] != GRASS)
			{
				m_nMap[level][y + 1][x] = num;
				WriteChar(x, y + 1, "■", color);
			}
			if (m_nMap[level][y + 1][x + 1] != GRASS)
			{
				m_nMap[level][y + 1][x + 1] = num;
				WriteChar(x + 1, y + 1, "■", color);
			}
			break;
		case RIGHT:

			if (m_nMap[level][y - 1][x - 1] != GRASS)
			{
				m_nMap[level][y - 1][x - 1] = num;
				WriteChar(x - 1, y - 1, "■", color);
			}
			if (m_nMap[level][y - 1][x] != GRASS)
			{
				m_nMap[level][y - 1][x] = num;
				WriteChar(x, y - 1, "■", color);
			}
			if (m_nMap[level][y - 1][x + 1] != GRASS)
			{
				m_nMap[level][y - 1][x + 1] = 0;
				WriteChar(x + 1, y - 1, "  ", color);
			}
			if (m_nMap[level][y][x - 1] != GRASS)
			{
				m_nMap[level][y][x - 1] = 0;
				WriteChar(x - 1, y, "  ", color);
			}
			if (m_nMap[level][y][x] != GRASS)
			{
				m_nMap[level][y][x] = num;
				WriteChar(x, y, "■", color);
			}
			if (m_nMap[level][y][x + 1] != GRASS)
			{
				m_nMap[level][y][x + 1] = num;
				WriteChar(x + 1, y, "■", color);
			}
			if (m_nMap[level][y + 1][x - 1] != GRASS)
			{
				m_nMap[level][y + 1][x - 1] = num;
				WriteChar(x - 1, y + 1, "■", color);
			}
			if (m_nMap[level][y + 1][x] != GRASS)
			{
				m_nMap[level][y + 1][x] = num;
				WriteChar(x, y + 1, "■", color);
			}
			if (m_nMap[level][y + 1][x + 1] != GRASS)
			{
				m_nMap[level][y + 1][x + 1] = 0;
				WriteChar(x + 1, y + 1, "  ", color);
			}
			break;
		default:
			break;
		}
	}
}

/********************************************************
函数功能	:移动坦克
参数		:坦克对象，关卡
返回值	:无
*********************************************************/
void TANK::ClearTank(TANK Tank, int level)
{
	//用简短的x y  来代替 "命名很长的" 坦克的x轴 y轴 
	int x = Tank.pos.X;
	int y = Tank.pos.Y;

	if (m_nMap[level][y - 1][x - 1] != GRASS)
	{
		m_nMap[level][y - 1][x - 1] = 0;
		WriteChar(x - 1, y - 1, "  ");
	}
	if (m_nMap[level][y - 1][x] != GRASS)
	{
		m_nMap[level][y - 1][x] = 0;
		WriteChar(x, y - 1, "  "  );
	}
	if (m_nMap[level][y - 1][x + 1] != GRASS)
	{
		m_nMap[level][y - 1][x + 1] = 0;
		WriteChar(x + 1, y - 1, "  "  );
	}
	if (m_nMap[level][y][x] != GRASS)
	{
		m_nMap[level][y][x] = 0;
		WriteChar(x, y, "  "  );
	}
	if (m_nMap[level][y][x - 1] != GRASS)
	{
		m_nMap[level][y][x - 1] = 0;
		WriteChar(x - 1, y, "  "  );
	}
	if (m_nMap[level][y][x + 1] != GRASS)
	{
		m_nMap[level][y][x + 1] = 0;
		WriteChar(x + 1, y, "  "  );
	}
	if (m_nMap[level][y + 1][x - 1] != GRASS)
	{
		m_nMap[level][y + 1][x - 1] = 0;
		WriteChar(x - 1, y + 1, "  "  );
	}
	if (m_nMap[level][y + 1][x] != GRASS)
	{
		m_nMap[level][y + 1][x] = 0;
		WriteChar(x, y + 1, "  "  );
	}
	if (m_nMap[level][y + 1][x + 1] != GRASS)
	{
		m_nMap[level][y + 1][x + 1] = 0;
		WriteChar(x + 1, y + 1, "  "  );
	}

}


/********************************************************
函数功能	:初始化坦克的中心位置
参数		:坦克对象，坦克数字，坐标
返回值	:无
*********************************************************/
void TANK::initialization_TANK(TANK & tank,int num,int x,int y)
{
	tank.pos.X = x;
	tank.pos.Y = y;
	tank.nDir = UP;
	//是否存活
	tank.nTank_Exist = 1;
	//玩家坦克
	tank.nTank_Play_or_Enemy = num;
}


/********************************************************
函数功能	:随机改变敌方坦克方向
参数		:坦克上次移动后的时间，坦克方向，坦克的方向，产生随机值的间隔,起点坦克坐标，关卡，目标坦克坐标
返回值	:无
*********************************************************/
void TANK::GetEnemyTankDir(int& time, char& dir, int& num, int ntime,TANK tank, int level,TANK tank2)
{
	if (clock() - time >= ntime)
	{
		time = clock();
		
		obj_AStar.InitMapInfo(m_nMap[level],41,41);
		obj_AStar.InitCoordInfo(tank.pos, tank2.pos);
		if (obj_AStar.FindPath(level))
		{
			obj_AStar.GetPath();
		}
		reverse(obj_AStar.m_vecPath.begin(), obj_AStar.m_vecPath.end());
		if (obj_AStar.m_vecPath.size() > 0)
		{
			num = obj_AStar.m_vecPath[0].d;
		}
		else
		{
			num = rand() % 5;
		}
		switch (num)
		{
		case 0:
			dir = 'w';
			break;
		case 1:
			dir = 's';
			break;
		case 2:
			dir = 'a';
			break;
		case 3:
			dir = 'd';
			break;
		case 4:
			dir = 'j';
			break;
		default:
			break;
		}
	}
}


/********************************************************
函数功能	:坦克死亡的时候，的标志
参数		:坦克存活的标志，坦克对象
返回值	:无
*********************************************************/
void TANK::SetTankIfExist(int exist, TANK & tank)
{
	tank.nTank_Exist = exist;
}

/********************************************************
函数功能	:移动敌方坦克1
参数		:敌方坦克1的方向，关卡
返回值	:无
*********************************************************/
void TANK::MoveEnemyTank(char& Random_Dir, int level,TANK &tank,int color)
{
	if (tank.nTank_Exist == 1)
	{
		switch (Random_Dir)
		{
		case'w':
			tank.ClearTank(tank, level);
			//如果不是朝上 就改为朝上 
			if (tank.nDir != UP)
			{
				tank.nDir = UP;
			}
			//如果是朝上就向上走一步
			else
			{
				tank.pos.Y--;
				//如果会碰撞就取消移动
				if (tank.IfTankCollide(tank.pos.X, tank.pos.Y, tank.nDir, level) == 0)
				{
					tank.pos.Y++;
				}
			}
			break;
		case's':
			tank.ClearTank(tank, level);
			if (tank.nDir != DOWN)
			{
				tank.nDir = DOWN;
			}
			else
			{
				tank.pos.Y++;
				//如果会碰撞就取消移动
				if (tank.IfTankCollide(tank.pos.X, tank.pos.Y, tank.nDir, level) == 0)
				{
					tank.pos.Y--;
				}
			}
			break;
		case'a':
			tank.ClearTank(tank, level);
			if (tank.nDir != LEFT)
			{
				tank.nDir = LEFT;
			}
			else
			{
				tank.pos.X--;
				//如果会碰撞就取消移动
				if (tank.IfTankCollide(tank.pos.X, tank.pos.Y, tank.nDir, level) == 0)
				{
					tank.pos.X++;
				}
			}
			break;
		case'd':
			tank.ClearTank(tank, level);
			if (tank.nDir != RIGHT)
			{
				tank.nDir = RIGHT;
			}
			else
			{
				tank.pos.X++;
				//如果会碰撞就取消移动
				if (tank.IfTankCollide(tank.pos.X, tank.pos.Y, tank.nDir, level) == 0)
				{
					tank.pos.X--;
				}
			}
			break;
		case'j':
			Sendout_bullet();
			bullet_temp.SetBullet_vector(tank.nDir, tank.pos.X, tank.pos.Y, 11);
			break;
		default:
			break;
		}
		//改变了方向  或者  移动了之后  再画坦克
		tank.DrawTank(tank, color, tank.nTank_Play_or_Enemy, level);
		Sleep(1);
		//把模拟接收敌方坦克的输入置0
		Random_Dir = 0;
	}
	else if (tank.nTank_Exist == 0)
	{
		tank.ClearTank(tank, level);
		tank.nTank_Exist = 2;
	}
}

/********************************************************
函数功能	:移动玩家坦克
参数		:坦克方向，关卡
返回值	:无
*********************************************************/
void TANK::MovePlayerTank(char cOper, int level)
{
	if (g_stcTank.nTank_Exist == 1)
	{
		switch (cOper)
		{
		case'w':
			g_stcTank.ClearTank(g_stcTank, level);
			//如果不是朝上 就改为朝上 
			if (g_stcTank.nDir != UP)
			{
				g_stcTank.nDir = UP;
			}
			//如果是朝上就向上走一步
			else
			{
				g_stcTank.pos.Y--;
				//如果会碰撞就取消移动
				if (g_stcTank.IfTankCollide(g_stcTank.pos.X, g_stcTank.pos.Y, g_stcTank.nDir, level) == 0)
				{
					g_stcTank.pos.Y++;
				}
			}
			break;
		case's':
			g_stcTank.ClearTank(g_stcTank, level);
			if (g_stcTank.nDir != DOWN)
			{
				g_stcTank.nDir = DOWN;
			}
			else
			{
				g_stcTank.pos.Y++;
				//如果会碰撞就取消移动
				if (g_stcTank.IfTankCollide(g_stcTank.pos.X, g_stcTank.pos.Y, g_stcTank.nDir, level) == 0)
				{
					g_stcTank.pos.Y--;
				}
			}
			break;
		case'a':
			g_stcTank.ClearTank(g_stcTank, level);
			if (g_stcTank.nDir != LEFT)
			{
				g_stcTank.nDir = LEFT;
			}
			else
			{
				g_stcTank.pos.X--;
				//如果会碰撞就取消移动
				if (g_stcTank.IfTankCollide(g_stcTank.pos.X, g_stcTank.pos.Y, g_stcTank.nDir, level) == 0)
				{
					g_stcTank.pos.X++;
				}
			}
			break;
		case'd':
			g_stcTank.ClearTank(g_stcTank, level);
			if (g_stcTank.nDir != RIGHT)
			{
				g_stcTank.nDir = RIGHT;
			}
			else
			{
				g_stcTank.pos.X++;
				//如果会碰撞就取消移动
				if (g_stcTank.IfTankCollide(g_stcTank.pos.X, g_stcTank.pos.Y, g_stcTank.nDir, level) == 0)
				{
					g_stcTank.pos.X--;
				}
			}
			break;
		case'j':
			Sendout_bullet();
			bullet_temp.SetBullet_vector(g_stcTank.nDir, g_stcTank.pos.X, g_stcTank.pos.Y, 12);
			break;
		case't':
			g_stcTank.ClearTank(g_stcTank, level);
			//如果不是朝上 就改为朝上 
			if (g_stcTank.nDir != UP)
			{
				g_stcTank.nDir = UP;
			}
			//如果是朝上就向上走一步
			else
			{
				g_stcTank.pos.Y--;
				//如果会碰撞就取消移动
				if (g_stcTank.IfTankCollide(g_stcTank.pos.X, g_stcTank.pos.Y, g_stcTank.nDir, level) == 0)
				{
					g_stcTank.pos.Y++;
				}
			}
			break;
		case'g':
			g_stcTank.ClearTank(g_stcTank, level);
			if (g_stcTank.nDir != DOWN)
			{
				g_stcTank.nDir = DOWN;
			}
			else
			{
				g_stcTank.pos.Y++;
				//如果会碰撞就取消移动
				if (g_stcTank.IfTankCollide(g_stcTank.pos.X, g_stcTank.pos.Y, g_stcTank.nDir, level) == 0)
				{
					g_stcTank.pos.Y--;
				}
			}
			break;
		case'f':
			g_stcTank.ClearTank(g_stcTank, level);
			if (g_stcTank.nDir != LEFT)
			{
				g_stcTank.nDir = LEFT;
			}
			else
			{
				g_stcTank.pos.X--;
				//如果会碰撞就取消移动
				if (g_stcTank.IfTankCollide(g_stcTank.pos.X, g_stcTank.pos.Y, g_stcTank.nDir, level) == 0)
				{
					g_stcTank.pos.X++;
				}
			}
			break;
		case'h':
			g_stcTank.ClearTank(g_stcTank, level);
			if (g_stcTank.nDir != RIGHT)
			{
				g_stcTank.nDir = RIGHT;
			}
			else
			{
				g_stcTank.pos.X++;
				//如果会碰撞就取消移动
				if (g_stcTank.IfTankCollide(g_stcTank.pos.X, g_stcTank.pos.Y, g_stcTank.nDir, level) == 0)
				{
					g_stcTank.pos.X--;
				}
			}
			break;
		case'k':
			Sendout_bullet();
			bullet_temp.SetBullet_vector(g_stcTank.nDir, g_stcTank.pos.X, g_stcTank.pos.Y, 12);
			break;
		case 'c':
			SaveFile();
			PrintSave();
			break;
		default:
			break;
		}
		//改变了方向  或者  移动了之后  再画坦克
		g_stcTank.DrawTank(g_stcTank, 04, g_stcTank.nTank_Play_or_Enemy, level);
		Sleep(1);
	}
	else if (g_stcTank.nTank_Exist == 0)
	{
		g_stcTank.ClearTank(g_stcTank, level);
		g_stcTank.nTank_Exist = 2;
	}
}

/********************************************************
函数功能	:移动玩家坦克2
参数		:坦克方向，关卡
返回值	:无
*********************************************************/
void TANK::MovePlayerTank2(char cOper, int level)
{
	if (g_stcTank2.nTank_Exist == 1)
	{
		switch (cOper)
		{
		case 上:
			g_stcTank2.ClearTank(g_stcTank2, level);
			//如果不是朝上 就改为朝上 
			if (g_stcTank2.nDir != UP)
			{
				g_stcTank2.nDir = UP;
			}
			//如果是朝上就向上走一步
			else
			{
				g_stcTank2.pos.Y--;
				//如果会碰撞就取消移动
				if (g_stcTank2.IfTankCollide(g_stcTank2.pos.X, g_stcTank2.pos.Y, g_stcTank2.nDir, level) == 0)
				{
					g_stcTank2.pos.Y++;
				}
			}
			break;
		case 下:
			g_stcTank2.ClearTank(g_stcTank2, level);
			if (g_stcTank2.nDir != DOWN)
			{
				g_stcTank2.nDir = DOWN;
			}
			else
			{
				g_stcTank2.pos.Y++;
				//如果会碰撞就取消移动
				if (g_stcTank2.IfTankCollide(g_stcTank2.pos.X, g_stcTank2.pos.Y, g_stcTank2.nDir, level) == 0)
				{
					g_stcTank2.pos.Y--;
				}
			}
			break;
		case 左:
			g_stcTank2.ClearTank(g_stcTank2, level);
			if (g_stcTank2.nDir != LEFT)
			{
				g_stcTank2.nDir = LEFT;
			}
			else
			{
				g_stcTank2.pos.X--;
				//如果会碰撞就取消移动
				if (g_stcTank2.IfTankCollide(g_stcTank2.pos.X, g_stcTank2.pos.Y, g_stcTank2.nDir, level) == 0)
				{
					g_stcTank2.pos.X++;
				}
			}
			break;
		case 右:
			g_stcTank2.ClearTank(g_stcTank2, level);
			if (g_stcTank2.nDir != RIGHT)
			{
				g_stcTank2.nDir = RIGHT;
			}
			else
			{
				g_stcTank2.pos.X++;
				//如果会碰撞就取消移动
				if (g_stcTank2.IfTankCollide(g_stcTank2.pos.X, g_stcTank2.pos.Y, g_stcTank2.nDir, level) == 0)
				{
					g_stcTank2.pos.X--;
				}
			}
			break;
		case 发射:
			Sendout_bullet();
			bullet_temp.SetBullet_vector(g_stcTank2.nDir, g_stcTank2.pos.X, g_stcTank2.pos.Y, 12);
			break;
		case 't':
			g_stcTank2.ClearTank(g_stcTank2, level);
			//如果不是朝上 就改为朝上 
			if (g_stcTank2.nDir != UP)
			{
				g_stcTank2.nDir = UP;
			}
			//如果是朝上就向上走一步
			else
			{
				g_stcTank2.pos.Y--;
				//如果会碰撞就取消移动
				if (g_stcTank2.IfTankCollide(g_stcTank2.pos.X, g_stcTank2.pos.Y, g_stcTank2.nDir, level) == 0)
				{
					g_stcTank2.pos.Y++;
				}
			}
			break;
		case 'g':
			g_stcTank2.ClearTank(g_stcTank2, level);
			if (g_stcTank2.nDir != DOWN)
			{
				g_stcTank2.nDir = DOWN;
			}
			else
			{
				g_stcTank2.pos.Y++;
				//如果会碰撞就取消移动
				if (g_stcTank2.IfTankCollide(g_stcTank2.pos.X, g_stcTank2.pos.Y, g_stcTank2.nDir, level) == 0)
				{
					g_stcTank2.pos.Y--;
				}
			}
			break;
		case 'f':
			g_stcTank2.ClearTank(g_stcTank2, level);
			if (g_stcTank2.nDir != LEFT)
			{
				g_stcTank2.nDir = LEFT;
			}
			else
			{
				g_stcTank2.pos.X--;
				//如果会碰撞就取消移动
				if (g_stcTank2.IfTankCollide(g_stcTank2.pos.X, g_stcTank2.pos.Y, g_stcTank2.nDir, level) == 0)
				{
					g_stcTank2.pos.X++;
				}
			}
			break;
		case 'h':
			g_stcTank2.ClearTank(g_stcTank2, level);
			if (g_stcTank2.nDir != RIGHT)
			{
				g_stcTank2.nDir = RIGHT;
			}
			else
			{
				g_stcTank2.pos.X++;
				//如果会碰撞就取消移动
				if (g_stcTank2.IfTankCollide(g_stcTank2.pos.X, g_stcTank2.pos.Y, g_stcTank2.nDir, level) == 0)
				{
					g_stcTank2.pos.X--;
				}
			}
			break;
		case 'k':
			Sendout_bullet();
			bullet_temp.SetBullet_vector(g_stcTank2.nDir, g_stcTank2.pos.X, g_stcTank2.pos.Y, 12);
			break;
		default:
			break;
		}
		//改变了方向  或者  移动了之后  再画坦克
		g_stcTank2.DrawTank(g_stcTank2, 06, g_stcTank2.nTank_Play_or_Enemy, level);
		Sleep(1);
	}
	else if (g_stcTank2.nTank_Exist == 0)
	{
		g_stcTank2.ClearTank(g_stcTank2, level);
		g_stcTank2.nTank_Exist = 2;
	}
}