#include "CAStar.h"
#include "Map.h"


extern CAStar obj_AStar = {};

/****************************************************
��������:��ȡ̹�˾Ź�����������
����1 	:̹������
����ֵ	:��
*****************************************************/
void CAStar::GetTankCoord(COORD tank)
{
	//tank[0],���ĵ�����,tank[1-3]��ǰ������������

	//��
	m_TankCoord[0][0].X = tank.X;
	m_TankCoord[0][0].Y = tank.Y - 1;
	//��
	m_TankCoord[1][0].X = tank.X;
	m_TankCoord[1][0].Y = tank.Y + 1;
	//��
	m_TankCoord[2][0].X = tank.X - 1;
	m_TankCoord[2][0].Y = tank.Y;
	//��
	m_TankCoord[3][0].X = tank.X + 1;
	m_TankCoord[3][0].Y = tank.Y;

	//���ݵ�ǰ��������ǰ������ Ҳ���ǾŹ����ǰ�������
	for (int i = 0; i < 4; i++)
	{
		switch (i)
		{
		case 0:
			m_TankCoord[i][1].X = m_TankCoord[i][0].X - 1;		//���϶���
			m_TankCoord[i][1].Y = m_TankCoord[i][0].Y - 1;
			m_TankCoord[i][2].X = m_TankCoord[i][0].X + 1;		//���϶���
			m_TankCoord[i][2].Y = m_TankCoord[i][0].Y - 1;
			m_TankCoord[i][3].X = m_TankCoord[i][0].X;			//��
			m_TankCoord[i][3].Y = m_TankCoord[i][0].Y - 1;
			break;
		case 1:
			m_TankCoord[i][1].X = m_TankCoord[i][0].X - 1;		//���¶���
			m_TankCoord[i][1].Y = m_TankCoord[i][0].Y + 1;
			m_TankCoord[i][2].X = m_TankCoord[i][0].X + 1;		//���¶���
			m_TankCoord[i][2].Y = m_TankCoord[i][0].Y + 1;
			m_TankCoord[i][3].X = m_TankCoord[i][0].X;			//��
			m_TankCoord[i][3].Y = m_TankCoord[i][0].Y + 1;
			break;
		case 2:
			m_TankCoord[i][1].X = m_TankCoord[i][0].X - 1;		//���϶���
			m_TankCoord[i][1].Y = m_TankCoord[i][0].Y - 1;
			m_TankCoord[i][2].X = m_TankCoord[i][0].X - 1;		//���¶���
			m_TankCoord[i][2].Y = m_TankCoord[i][0].Y + 1;
			m_TankCoord[i][3].X = m_TankCoord[i][0].X - 1;		//��
			m_TankCoord[i][3].Y = m_TankCoord[i][0].Y;
			break;
		case 3:
			m_TankCoord[i][1].X = m_TankCoord[i][0].X + 1;		//���϶���
			m_TankCoord[i][1].Y = m_TankCoord[i][0].Y - 1;
			m_TankCoord[i][2].X = m_TankCoord[i][0].X + 1;		//���¶���
			m_TankCoord[i][2].Y = m_TankCoord[i][0].Y + 1;
			m_TankCoord[i][3].X = m_TankCoord[i][0].X + 1;		//��
			m_TankCoord[i][3].Y = m_TankCoord[i][0].Y;
			break;
		default:break;
		}
	}
}

//*******************************************************
//��������	:��ʼ����ͼ��Ϣ
//����1		:��ͼָ��
//����2		:��ͼ�߶�
//����3		:��ͼ���
//����ֵ		:��
//*******************************************************
void CAStar::InitMapInfo(int pMap[41][41], int nHigh, int nWidth)
{
	m_pMap = pMap;
	m_nMapH = nHigh;
	m_nMapW = nWidth;
	m_bInitMapInfo = true;
	//����һ����ʱ��ͼ
	m_pTempMap = new TEMPMAP[m_nMapH * m_nMapW]();
}

//*******************************************************
//��������	:��ʼ����ʼ����
//����1		:�������
//����2		:�յ�����
//����ֵ		:��
//*******************************************************
void CAStar::InitCoordInfo(_In_ COORD codStart, _In_ COORD codEnd)
{
	m_Start = codStart;
	m_End = codEnd;
	m_bInitCoordInfo = true;
}

//*******************************************************
//��������	:��ȡ���·��
//����		:��
//����ֵ		:��
//*******************************************************
void CAStar::GetPath()
{
	//ÿ�����»�ȡ·�� �����һ�ε�·��
	m_vecPath.clear();
	//���һ������±�(�յ��±�)
	int nIndex = m_vecCloseList.size() - 1;
	while (true)
	{
		for (vector <int>::size_type i = 0; i < m_vecCloseList.size(); i++)
		{
			//������ڵ������,˵��������
			if (m_vecCloseList[nIndex].codParent == m_Start)
			{
				return;
			}
			//������� ��������ĸ��ڵ�
			if (m_vecCloseList[nIndex].codParent == m_vecCloseList[i].codSelf)
			{
				//�ҵ����ڵ�,�Ѹ��ڵ�������ӽ�m_vecPath��
				m_vecPath.push_back(m_vecCloseList[i].codSelf);
				//��nIndex��ֵΪ���ڵ��±�,Ȼ�����¿�ʼ�ҵ�ǰ����ĸ��ڵ�
				nIndex = i;
				break;
			}
		}
	}
}

//*******************************************************
//��������	:Ѱ�Ұ������·���������
//����1		:��
//����ֵ		:��
//*******************************************************
bool CAStar::FindPath(int level)
{
	if (!m_bInitCoordInfo || !m_bInitMapInfo)
	{
		return false;
	}
	//����ϴβ��ҵĽڵ�
	m_vecOpenList.clear();
	m_vecCloseList.clear();
	memset(m_pTempMap, 0, m_nMapW * m_nMapH);	//�����ʱ��ͼ��־

	//1.��ʼ�����
	NODEINFO startNode{};
	startNode.codSelf = m_Start;
	startNode.nG = 0;
	startNode.SetHF(m_End);

	//2.�������ӵ�openList
	m_vecOpenList.push_back(startNode);
	//��ά��һά:arr[Y][X]==arr(Y*w+X)
	m_pTempMap[startNode.codSelf.Y * m_nMapW + startNode.codSelf.X].bIsOpen = true;

	while (true)
	{
		//3.�ж�open�Ƿ�Ϊ��(˵��û�ҵ�)
		if (m_vecOpenList.empty())
		{
			return false;
		}
		//4.��open�����ҵ�F��Сֵ, ������ɢ
		int nIndex = 0;		//��Сֵ�±�
		for (vector <int>::size_type i = 1; i < m_vecOpenList.size(); i++)
		{
			if (m_vecOpenList[nIndex].nF > m_vecOpenList[i].nF)
			{
				nIndex = i;
			}
		}
		//ʹ�ô˵������ɢ��4���Ź���
		GetTankCoord(m_vecOpenList[nIndex].codSelf);
		//����Χ�Ź������ĵ���д���
		NODEINFO newNode[4] = {};
		for (int i = 0; i < 4; i++)
		{
			newNode[i].codSelf = m_TankCoord[i][0];
			newNode[i].codParent = m_vecOpenList[nIndex].codSelf;
			newNode[i].nG = m_vecOpenList[nIndex].nG + 1;
			newNode[i].SetHF(m_End);
			newNode[i].codSelf.d = i;		//������
		}
		//5.����ɢ���ĵ�, ��ӵ�close����, ����open����ɾ��
		m_pTempMap[m_vecOpenList[nIndex].codSelf.Y * m_nMapW + m_vecOpenList[nIndex].codSelf.X].bIsClose = true;
		m_pTempMap[m_vecOpenList[nIndex].codSelf.Y * m_nMapW + m_vecOpenList[nIndex].codSelf.X].bIsOpen = false;
		m_vecCloseList.push_back(m_vecOpenList[nIndex]);
		m_vecOpenList.erase(m_vecOpenList.begin() + nIndex);
		//6.�����ɢ�����ĵ��Ƿ�����յ�, �������, �ͼ���Ƿ������ӵ�open����
		for (int i = 0; i < 4; i++)
		{
			//6.1.�Ƿ����յ�(��, ��ֱ�ӷ���true)
				//�Ƿ����յ�==>�ϳ���ǽΧ��,����ж��Ƿ񵽴��յ���Χ
			if (abs(newNode[i].codSelf.X - m_End.X) <= 5 && newNode[i].codSelf.Y == m_End.Y ||
				abs(newNode[i].codSelf.Y - m_End.Y) <= 5 && newNode[i].codSelf.X == m_End.X)
			{
				//�����յ��close����
				m_vecCloseList.push_back(newNode[i]);
				return true;
			}
			//6.2.�Ƿ�Խ��
			if (newNode[i].codSelf.X < 2 || newNode[i].codSelf.X > m_nMapW - 3 ||
				newNode[i].codSelf.Y < 2 || newNode[i].codSelf.Y > m_nMapH - 3)
			{
				//���������һ�Ź���
				continue;
			}
			//6.3.�Ƿ����ϰ���
			bool IsBlock = false;
			for (int j = 1; j < 4; j++)
			{
				if (m_nMap[level][m_TankCoord[i][j].Y][m_TankCoord[i][j].X] == WALL ||
					m_nMap[level][m_TankCoord[i][j].Y][m_TankCoord[i][j].X] == STEEL ||
					m_nMap[level][m_TankCoord[i][j].Y][m_TankCoord[i][j].X] == WATER)
				{
					IsBlock = true;
					break;	//���������һ�Ź���
				}
			}
			if (IsBlock)
			{
				continue;
			}
			//6.4.�Ƿ���open����					//6.5.�Ƿ���close����
			if (m_pTempMap[newNode[i].codSelf.Y * m_nMapW + newNode[i].codSelf.X].bIsOpen ||
				m_pTempMap[newNode[i].codSelf.Y * m_nMapW + newNode[i].codSelf.X].bIsClose)
			{
				continue;
			}
			//7.�Ѽ��ϸ�ĵ���ӵ�open����
			m_vecOpenList.push_back(newNode[i]);
			m_pTempMap[newNode[i].codSelf.Y * m_nMapW + newNode[i].codSelf.X].bIsOpen = true;
			//8.�ظ�3 - 7��
		}
	}
	return true;
}
