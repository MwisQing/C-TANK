#include "CBullet.h"
#include"CTank.h"

//�ڵ���̬����
extern vector<BULLET>bullet = {};

//�ڵ�����(���߶���)���ú���ר��
extern BULLET bullet_temp = {};

/********************************************************
��������	:����ڵ������ұ��Ϊ���ڵ�
����		:�ڵ������꣬�ڵ�������±꣬�ؿ�
����ֵ	:��
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
��������	:���ڵ�
����		:�ڵ������꣬��ɫ���ڵ�����Ӫ���ؿ�
����ֵ	:��
*********************************************************/
void BULLET::DrawBullet(int x, int y, int color, int play_enemy, int level)
{
	WriteChar(x, y, "��", color);
	m_nMap[level][y][x] = play_enemy;
}

/********************************************************
��������	:�ж��ڵ�����ײ
����		:�ڵ������꣬�ڵ�������±꣬�ڵ�����Ӫ���ؿ�
����ֵ	:��
*********************************************************/
int BULLET::IfCollide(int x, int y, int i,int player_enemy, int level)
{
	//ʯǽ �ɻ���
	if (m_nMap[level][y][x] == WALL)
	{
		WriteChar(x, y, "  ");
		m_nMap[level][y][x] = GROUND;
		bullet[i].nExist = 0;
		Smash_Stonewall();
		return 0;
	}
	//�� ���ƻ�
	if (m_nMap[level][y][x] == GRASS)
	{
		WriteChar(x, y, "  ");
		m_nMap[level][y][x] = GROUND;
		bullet[i].nExist = 0;
		Smash_Stonewall();
		return 0;
	}
	//��ǽ���ɻ���
	if (m_nMap[level][y][x] == STEEL)
	{
		bullet[i].nExist = 0;
		return 0;
	}
	//Χǽ���ɻ���
	if (m_nMap[level][y][x] == FRAME)
	{
		bullet[i].nExist = 0;
		return 0;
	}
	//ˮ
	if (m_nMap[level][y][x] == WATER)
	{
		bullet[i].nExist = 1;
		return 1;
	}
	//�յ�
	if (m_nMap[level][y][x] == GROUND)
	{
		return 1;
	}
	//��
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
	if (m_nMap[level][y][x] == �з�̹��0)
	{
		bullet[i].nExist = 0;
		if (player_enemy == ����ڵ�)
		{
			g_Tank_Enemy_temp.SetTankIfExist(0,g_Tank_Enemy_temp);
			nCount += 1000;
		}
		return 0;
	}
	if (m_nMap[level][y][x] == �з�̹��1)
	{
		bullet[i].nExist = 0;
		if (player_enemy == ����ڵ�)
		{
			g_Tank_Enemy_temp2.SetTankIfExist(0, g_Tank_Enemy_temp2);
			nCount += 1000;
		}
		return 0;
	}
	if (m_nMap[level][y][x] == ���̹��0)
	{
		bullet[i].nExist = 0;
		if (player_enemy == �з��ڵ�)
		{
			g_stcTank.SetTankIfExist(0, g_stcTank);
		}
		return 0;
	}
	if (m_nMap[level][y][x] == ���̹��1)
	{
		bullet[i].nExist = 0;
		if (player_enemy == �з��ڵ�)
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
��������	:�ƶ��ڵ������� ����ڵ�  ���ڵ�
����		:�ؿ�
����ֵ	:��
*********************************************************/
void BULLET::MoveBullet(int level)
{
	for (int i = 0; i < bullet.size(); i++)
	{
		//ֻ��ʱ��� == 200  �Ż�
		if (clock() - bullet[i].nLastClock >= bullet[i].nSpeed)
		{
			//�ж��ڵ�����ײ
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
			//���¼�ʱ���
			bullet[i].nLastClock = clock();
			//ֻ�����ڵ��ڵ����Ҳ����µ��ڵ�
			if (bullet[i].nExist != 0 && bullet[i].isNew == 0)
			{
				//��������������ƶ��ڵ�
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
				//����Ƿ�ݻٵĳ���
				int bullet_sign = 0;
				bullet_sign = IfCollide(bullet[i].pos.X, bullet[i].pos.Y, i, bullet[i].nBullet_player_enemy, level);

				//�ж��ڵ��Ƿ����ڵ���ײ����������
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
					//ȷ����ײ����
					//Ȼ���ڵ�
					DrawBullet(bullet[i].pos.X, bullet[i].pos.Y, 0x0004 | 0x0002 | 0x0001, bullet[i].nBullet_player_enemy, level);
				}

				//����Ƿ�ݻ�
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
��������	:�����ڵ�
����		:̹�˷���̹�����̹꣬����Ӫ
����ֵ	:��
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
��������	:�ı��ڵ�ʱ�䣬�������������̷���
����		:�ڵ�����
����ֵ	:��
*********************************************************/
void BULLET::SetTime(BULLET & blt)
{
	blt.nLastClock = -100;
}