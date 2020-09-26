#include "CTank.h"
#include "CBullet.h"

//����һ�����̹��
extern TANK g_stcTank = {};
//����һ�����2̹��
extern TANK g_stcTank2 = {};

//����з�̹������
extern vector<TANK>g_Tank_Enemy[1] = {};
//����һ���з�̹�˶���
extern TANK g_Tank_Enemy_temp = {};
//����һ���з�̹�˶���2
extern TANK g_Tank_Enemy_temp2 = {};

/********************************************************
��������	:��ʼ���з�̹��1
����		:��
����ֵ	:��
*********************************************************/
void TANK::Set_EnemyTank()
{
	g_Tank_Enemy_temp.nDir = DOWN;
	g_Tank_Enemy_temp.pos.X = 2;
	g_Tank_Enemy_temp.pos.Y = 2;
	g_Tank_Enemy_temp.nTank_Exist = 1;
	//�з�̹��
	g_Tank_Enemy_temp.nTank_Play_or_Enemy = �з�̹��0;
}

/********************************************************
��������	:��ʼ���з�̹��2
����		:��
����ֵ	:��
*********************************************************/
void TANK::Set_EnemyTank2()
{
	g_Tank_Enemy_temp2.nDir = DOWN;
	g_Tank_Enemy_temp2.pos.X = 38;
	g_Tank_Enemy_temp2.pos.Y = 2;
	g_Tank_Enemy_temp2.nTank_Exist = 1;
	//�з�̹��
	g_Tank_Enemy_temp2.nTank_Play_or_Enemy = �з�̹��1;
}

/********************************************************
��������	:�ж��ϰ���
����		:��ͼ�������̹꣬�˷��򣬹ؿ�
����ֵ	:int���� 0 or 1
*********************************************************/
int TANK::IfTankCollide(int x, int y, int dir,int level)
{
	//��������ϰ���
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
��������	:��̹��
����		:̹�˶�����ɫ��̹���ڵ�ͼ�ϵ����֣��ؿ�
����ֵ	:��
*********************************************************/
void TANK::DrawTank(TANK Tank,int color,int num,int level)
{
	if (Tank.nTank_Exist == 1)
	{
		//�ü�̵�x y  ������ "�����ܳ���" ̹�˵�x�� y�� 
		int x = Tank.pos.X;
		int y = Tank.pos.Y;
		//���ݷ����ӡ̹��
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
				WriteChar(x, y - 1, "��", color);
			}
			if (m_nMap[level][y - 1][x + 1] != GRASS)
			{
				m_nMap[level][y - 1][x + 1] = 0;
				WriteChar(x + 1, y - 1, "  ", color);
			}
			if (m_nMap[level][y][x] != GRASS)
			{
				m_nMap[level][y][x] = num;
				WriteChar(x, y, "��", color);
			}
			if (m_nMap[level][y][x - 1] != GRASS)
			{
				m_nMap[level][y][x - 1] = num;
				WriteChar(x - 1, y, "��", color);
			}
			if (m_nMap[level][y][x + 1] != GRASS)
			{
				m_nMap[level][y][x + 1] = num;
				WriteChar(x + 1, y, "��", color);
			}
			if (m_nMap[level][y + 1][x - 1] != GRASS)
			{
				m_nMap[level][y + 1][x - 1] = num;
				WriteChar(x - 1, y + 1, "��", color);
			}
			if (m_nMap[level][y + 1][x] != GRASS)
			{
				m_nMap[level][y + 1][x] = 0;
				WriteChar(x, y + 1, "  ", color);
			}
			if (m_nMap[level][y + 1][x + 1] != GRASS)
			{
				m_nMap[level][y + 1][x + 1] = num;
				WriteChar(x + 1, y + 1, "��", color);
			}
			break;
		case DOWN:
			if (m_nMap[level][y - 1][x - 1] != GRASS)
			{
				m_nMap[level][y - 1][x - 1] = num;
				WriteChar(x - 1, y - 1, "��", color);
			}
			if (m_nMap[level][y - 1][x] != GRASS)
			{
				m_nMap[level][y - 1][x] = 0;
				WriteChar(x, y - 1, "  ", color);
			}
			if (m_nMap[level][y - 1][x + 1] != GRASS)
			{
				m_nMap[level][y - 1][x + 1] = num;
				WriteChar(x + 1, y - 1, "��", color);
			}
			if (m_nMap[level][y][x] != GRASS)
			{
				m_nMap[level][y][x] = num;
				WriteChar(x, y, "��", color);
			}
			if (m_nMap[level][y][x - 1] != GRASS)
			{
				m_nMap[level][y][x - 1] = num;
				WriteChar(x - 1, y, "��", color);
			}
			if (m_nMap[level][y][x + 1] != GRASS)
			{
				m_nMap[level][y][x + 1] = num;
				WriteChar(x + 1, y, "��", color);
			}
			if (m_nMap[level][y + 1][x - 1] != GRASS)
			{
				m_nMap[level][y + 1][x - 1] = 0;
				WriteChar(x - 1, y + 1, "  ", color);
			}
			if (m_nMap[level][y + 1][x] != GRASS)
			{
				m_nMap[level][y + 1][x] = num;
				WriteChar(x, y + 1, "��", color);
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
				WriteChar(x, y - 1, "��", color);
			}
			if (m_nMap[level][y - 1][x + 1] != GRASS)
			{
				m_nMap[level][y - 1][x + 1] = num;
				WriteChar(x + 1, y - 1, "��", color);
			}
			if (m_nMap[level][y][x] != GRASS)
			{
				m_nMap[level][y][x] = num;
				WriteChar(x, y, "��", color);
			}
			if (m_nMap[level][y][x - 1] != GRASS)
			{
				m_nMap[level][y][x - 1] = num;
				WriteChar(x - 1, y, "��", color);
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
				WriteChar(x, y + 1, "��", color);
			}
			if (m_nMap[level][y + 1][x + 1] != GRASS)
			{
				m_nMap[level][y + 1][x + 1] = num;
				WriteChar(x + 1, y + 1, "��", color);
			}
			break;
		case RIGHT:

			if (m_nMap[level][y - 1][x - 1] != GRASS)
			{
				m_nMap[level][y - 1][x - 1] = num;
				WriteChar(x - 1, y - 1, "��", color);
			}
			if (m_nMap[level][y - 1][x] != GRASS)
			{
				m_nMap[level][y - 1][x] = num;
				WriteChar(x, y - 1, "��", color);
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
				WriteChar(x, y, "��", color);
			}
			if (m_nMap[level][y][x + 1] != GRASS)
			{
				m_nMap[level][y][x + 1] = num;
				WriteChar(x + 1, y, "��", color);
			}
			if (m_nMap[level][y + 1][x - 1] != GRASS)
			{
				m_nMap[level][y + 1][x - 1] = num;
				WriteChar(x - 1, y + 1, "��", color);
			}
			if (m_nMap[level][y + 1][x] != GRASS)
			{
				m_nMap[level][y + 1][x] = num;
				WriteChar(x, y + 1, "��", color);
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
��������	:�ƶ�̹��
����		:̹�˶��󣬹ؿ�
����ֵ	:��
*********************************************************/
void TANK::ClearTank(TANK Tank, int level)
{
	//�ü�̵�x y  ������ "�����ܳ���" ̹�˵�x�� y�� 
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
��������	:��ʼ��̹�˵�����λ��
����		:̹�˶���̹�����֣�����
����ֵ	:��
*********************************************************/
void TANK::initialization_TANK(TANK & tank,int num,int x,int y)
{
	tank.pos.X = x;
	tank.pos.Y = y;
	tank.nDir = UP;
	//�Ƿ���
	tank.nTank_Exist = 1;
	//���̹��
	tank.nTank_Play_or_Enemy = num;
}


/********************************************************
��������	:����ı�з�̹�˷���
����		:̹���ϴ��ƶ����ʱ�䣬̹�˷���̹�˵ķ��򣬲������ֵ�ļ��,���̹�����꣬�ؿ���Ŀ��̹������
����ֵ	:��
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
��������	:̹��������ʱ�򣬵ı�־
����		:̹�˴��ı�־��̹�˶���
����ֵ	:��
*********************************************************/
void TANK::SetTankIfExist(int exist, TANK & tank)
{
	tank.nTank_Exist = exist;
}

/********************************************************
��������	:�ƶ��з�̹��1
����		:�з�̹��1�ķ��򣬹ؿ�
����ֵ	:��
*********************************************************/
void TANK::MoveEnemyTank(char& Random_Dir, int level,TANK &tank,int color)
{
	if (tank.nTank_Exist == 1)
	{
		switch (Random_Dir)
		{
		case'w':
			tank.ClearTank(tank, level);
			//������ǳ��� �͸�Ϊ���� 
			if (tank.nDir != UP)
			{
				tank.nDir = UP;
			}
			//����ǳ��Ͼ�������һ��
			else
			{
				tank.pos.Y--;
				//�������ײ��ȡ���ƶ�
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
				//�������ײ��ȡ���ƶ�
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
				//�������ײ��ȡ���ƶ�
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
				//�������ײ��ȡ���ƶ�
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
		//�ı��˷���  ����  �ƶ���֮��  �ٻ�̹��
		tank.DrawTank(tank, color, tank.nTank_Play_or_Enemy, level);
		Sleep(1);
		//��ģ����յз�̹�˵�������0
		Random_Dir = 0;
	}
	else if (tank.nTank_Exist == 0)
	{
		tank.ClearTank(tank, level);
		tank.nTank_Exist = 2;
	}
}

/********************************************************
��������	:�ƶ����̹��
����		:̹�˷��򣬹ؿ�
����ֵ	:��
*********************************************************/
void TANK::MovePlayerTank(char cOper, int level)
{
	if (g_stcTank.nTank_Exist == 1)
	{
		switch (cOper)
		{
		case'w':
			g_stcTank.ClearTank(g_stcTank, level);
			//������ǳ��� �͸�Ϊ���� 
			if (g_stcTank.nDir != UP)
			{
				g_stcTank.nDir = UP;
			}
			//����ǳ��Ͼ�������һ��
			else
			{
				g_stcTank.pos.Y--;
				//�������ײ��ȡ���ƶ�
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
				//�������ײ��ȡ���ƶ�
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
				//�������ײ��ȡ���ƶ�
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
				//�������ײ��ȡ���ƶ�
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
			//������ǳ��� �͸�Ϊ���� 
			if (g_stcTank.nDir != UP)
			{
				g_stcTank.nDir = UP;
			}
			//����ǳ��Ͼ�������һ��
			else
			{
				g_stcTank.pos.Y--;
				//�������ײ��ȡ���ƶ�
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
				//�������ײ��ȡ���ƶ�
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
				//�������ײ��ȡ���ƶ�
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
				//�������ײ��ȡ���ƶ�
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
		//�ı��˷���  ����  �ƶ���֮��  �ٻ�̹��
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
��������	:�ƶ����̹��2
����		:̹�˷��򣬹ؿ�
����ֵ	:��
*********************************************************/
void TANK::MovePlayerTank2(char cOper, int level)
{
	if (g_stcTank2.nTank_Exist == 1)
	{
		switch (cOper)
		{
		case ��:
			g_stcTank2.ClearTank(g_stcTank2, level);
			//������ǳ��� �͸�Ϊ���� 
			if (g_stcTank2.nDir != UP)
			{
				g_stcTank2.nDir = UP;
			}
			//����ǳ��Ͼ�������һ��
			else
			{
				g_stcTank2.pos.Y--;
				//�������ײ��ȡ���ƶ�
				if (g_stcTank2.IfTankCollide(g_stcTank2.pos.X, g_stcTank2.pos.Y, g_stcTank2.nDir, level) == 0)
				{
					g_stcTank2.pos.Y++;
				}
			}
			break;
		case ��:
			g_stcTank2.ClearTank(g_stcTank2, level);
			if (g_stcTank2.nDir != DOWN)
			{
				g_stcTank2.nDir = DOWN;
			}
			else
			{
				g_stcTank2.pos.Y++;
				//�������ײ��ȡ���ƶ�
				if (g_stcTank2.IfTankCollide(g_stcTank2.pos.X, g_stcTank2.pos.Y, g_stcTank2.nDir, level) == 0)
				{
					g_stcTank2.pos.Y--;
				}
			}
			break;
		case ��:
			g_stcTank2.ClearTank(g_stcTank2, level);
			if (g_stcTank2.nDir != LEFT)
			{
				g_stcTank2.nDir = LEFT;
			}
			else
			{
				g_stcTank2.pos.X--;
				//�������ײ��ȡ���ƶ�
				if (g_stcTank2.IfTankCollide(g_stcTank2.pos.X, g_stcTank2.pos.Y, g_stcTank2.nDir, level) == 0)
				{
					g_stcTank2.pos.X++;
				}
			}
			break;
		case ��:
			g_stcTank2.ClearTank(g_stcTank2, level);
			if (g_stcTank2.nDir != RIGHT)
			{
				g_stcTank2.nDir = RIGHT;
			}
			else
			{
				g_stcTank2.pos.X++;
				//�������ײ��ȡ���ƶ�
				if (g_stcTank2.IfTankCollide(g_stcTank2.pos.X, g_stcTank2.pos.Y, g_stcTank2.nDir, level) == 0)
				{
					g_stcTank2.pos.X--;
				}
			}
			break;
		case ����:
			Sendout_bullet();
			bullet_temp.SetBullet_vector(g_stcTank2.nDir, g_stcTank2.pos.X, g_stcTank2.pos.Y, 12);
			break;
		case 't':
			g_stcTank2.ClearTank(g_stcTank2, level);
			//������ǳ��� �͸�Ϊ���� 
			if (g_stcTank2.nDir != UP)
			{
				g_stcTank2.nDir = UP;
			}
			//����ǳ��Ͼ�������һ��
			else
			{
				g_stcTank2.pos.Y--;
				//�������ײ��ȡ���ƶ�
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
				//�������ײ��ȡ���ƶ�
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
				//�������ײ��ȡ���ƶ�
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
				//�������ײ��ȡ���ƶ�
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
		//�ı��˷���  ����  �ƶ���֮��  �ٻ�̹��
		g_stcTank2.DrawTank(g_stcTank2, 06, g_stcTank2.nTank_Play_or_Enemy, level);
		Sleep(1);
	}
	else if (g_stcTank2.nTank_Exist == 0)
	{
		g_stcTank2.ClearTank(g_stcTank2, level);
		g_stcTank2.nTank_Exist = 2;
	}
}