#include "CAStar.h"
#include "Map.h"


extern CAStar obj_AStar = {};

/****************************************************
函数功能:获取坦克九宫格坐标坐标
参数1 	:坦克坐标
返回值	:无
*****************************************************/
void CAStar::GetTankCoord(COORD tank)
{
	//tank[0],中心点坐标,tank[1-3]当前方向三点坐标

	//上
	m_TankCoord[0][0].X = tank.X;
	m_TankCoord[0][0].Y = tank.Y - 1;
	//下
	m_TankCoord[1][0].X = tank.X;
	m_TankCoord[1][0].Y = tank.Y + 1;
	//左
	m_TankCoord[2][0].X = tank.X - 1;
	m_TankCoord[2][0].Y = tank.Y;
	//右
	m_TankCoord[3][0].X = tank.X + 1;
	m_TankCoord[3][0].Y = tank.Y;

	//根据当前方向计算出前方三点 也就是九宫格的前面的坐标
	for (int i = 0; i < 4; i++)
	{
		switch (i)
		{
		case 0:
			m_TankCoord[i][1].X = m_TankCoord[i][0].X - 1;		//左上顶点
			m_TankCoord[i][1].Y = m_TankCoord[i][0].Y - 1;
			m_TankCoord[i][2].X = m_TankCoord[i][0].X + 1;		//右上顶点
			m_TankCoord[i][2].Y = m_TankCoord[i][0].Y - 1;
			m_TankCoord[i][3].X = m_TankCoord[i][0].X;			//上
			m_TankCoord[i][3].Y = m_TankCoord[i][0].Y - 1;
			break;
		case 1:
			m_TankCoord[i][1].X = m_TankCoord[i][0].X - 1;		//左下顶点
			m_TankCoord[i][1].Y = m_TankCoord[i][0].Y + 1;
			m_TankCoord[i][2].X = m_TankCoord[i][0].X + 1;		//右下顶点
			m_TankCoord[i][2].Y = m_TankCoord[i][0].Y + 1;
			m_TankCoord[i][3].X = m_TankCoord[i][0].X;			//下
			m_TankCoord[i][3].Y = m_TankCoord[i][0].Y + 1;
			break;
		case 2:
			m_TankCoord[i][1].X = m_TankCoord[i][0].X - 1;		//左上顶点
			m_TankCoord[i][1].Y = m_TankCoord[i][0].Y - 1;
			m_TankCoord[i][2].X = m_TankCoord[i][0].X - 1;		//左下顶点
			m_TankCoord[i][2].Y = m_TankCoord[i][0].Y + 1;
			m_TankCoord[i][3].X = m_TankCoord[i][0].X - 1;		//左
			m_TankCoord[i][3].Y = m_TankCoord[i][0].Y;
			break;
		case 3:
			m_TankCoord[i][1].X = m_TankCoord[i][0].X + 1;		//右上顶点
			m_TankCoord[i][1].Y = m_TankCoord[i][0].Y - 1;
			m_TankCoord[i][2].X = m_TankCoord[i][0].X + 1;		//右下顶点
			m_TankCoord[i][2].Y = m_TankCoord[i][0].Y + 1;
			m_TankCoord[i][3].X = m_TankCoord[i][0].X + 1;		//右
			m_TankCoord[i][3].Y = m_TankCoord[i][0].Y;
			break;
		default:break;
		}
	}
}

//*******************************************************
//函数功能	:初始化地图信息
//参数1		:地图指针
//参数2		:地图高度
//参数3		:地图宽度
//返回值		:无
//*******************************************************
void CAStar::InitMapInfo(int pMap[41][41], int nHigh, int nWidth)
{
	m_pMap = pMap;
	m_nMapH = nHigh;
	m_nMapW = nWidth;
	m_bInitMapInfo = true;
	//创建一个临时地图
	m_pTempMap = new TEMPMAP[m_nMapH * m_nMapW]();
}

//*******************************************************
//函数功能	:初始化起始坐标
//参数1		:起点坐标
//参数2		:终点坐标
//返回值		:无
//*******************************************************
void CAStar::InitCoordInfo(_In_ COORD codStart, _In_ COORD codEnd)
{
	m_Start = codStart;
	m_End = codEnd;
	m_bInitCoordInfo = true;
}

//*******************************************************
//函数功能	:获取最短路径
//参数		:无
//返回值		:无
//*******************************************************
void CAStar::GetPath()
{
	//每次重新获取路径 清空上一次的路径
	m_vecPath.clear();
	//最后一个点的下标(终点下标)
	int nIndex = m_vecCloseList.size() - 1;
	while (true)
	{
		for (vector <int>::size_type i = 0; i < m_vecCloseList.size(); i++)
		{
			//如果父节点是起点,说明找完了
			if (m_vecCloseList[nIndex].codParent == m_Start)
			{
				return;
			}
			//如果不是 就找自身的父节点
			if (m_vecCloseList[nIndex].codParent == m_vecCloseList[i].codSelf)
			{
				//找到父节点,把父节点坐标添加进m_vecPath中
				m_vecPath.push_back(m_vecCloseList[i].codSelf);
				//将nIndex赋值为父节点下标,然后重新开始找当前坐标的父节点
				nIndex = i;
				break;
			}
		}
	}
}

//*******************************************************
//函数功能	:寻找包含最短路径的坐标点
//参数1		:无
//返回值		:无
//*******************************************************
bool CAStar::FindPath(int level)
{
	if (!m_bInitCoordInfo || !m_bInitMapInfo)
	{
		return false;
	}
	//清空上次查找的节点
	m_vecOpenList.clear();
	m_vecCloseList.clear();
	memset(m_pTempMap, 0, m_nMapW * m_nMapH);	//清空临时地图标志

	//1.初始化起点
	NODEINFO startNode{};
	startNode.codSelf = m_Start;
	startNode.nG = 0;
	startNode.SetHF(m_End);

	//2.把起点添加到openList
	m_vecOpenList.push_back(startNode);
	//二维变一维:arr[Y][X]==arr(Y*w+X)
	m_pTempMap[startNode.codSelf.Y * m_nMapW + startNode.codSelf.X].bIsOpen = true;

	while (true)
	{
		//3.判断open是否为空(说明没找到)
		if (m_vecOpenList.empty())
		{
			return false;
		}
		//4.从open表中找到F最小值, 进行扩散
		int nIndex = 0;		//最小值下标
		for (vector <int>::size_type i = 1; i < m_vecOpenList.size(); i++)
		{
			if (m_vecOpenList[nIndex].nF > m_vecOpenList[i].nF)
			{
				nIndex = i;
			}
		}
		//使用此点进行扩散（4个九宫格）
		GetTankCoord(m_vecOpenList[nIndex].codSelf);
		//对周围九宫格中心点进行处理
		NODEINFO newNode[4] = {};
		for (int i = 0; i < 4; i++)
		{
			newNode[i].codSelf = m_TankCoord[i][0];
			newNode[i].codParent = m_vecOpenList[nIndex].codSelf;
			newNode[i].nG = m_vecOpenList[nIndex].nG + 1;
			newNode[i].SetHF(m_End);
			newNode[i].codSelf.d = i;		//自身方向
		}
		//5.把扩散过的点, 添加到close表中, 并从open表中删除
		m_pTempMap[m_vecOpenList[nIndex].codSelf.Y * m_nMapW + m_vecOpenList[nIndex].codSelf.X].bIsClose = true;
		m_pTempMap[m_vecOpenList[nIndex].codSelf.Y * m_nMapW + m_vecOpenList[nIndex].codSelf.X].bIsOpen = false;
		m_vecCloseList.push_back(m_vecOpenList[nIndex]);
		m_vecOpenList.erase(m_vecOpenList.begin() + nIndex);
		//6.检测扩散出来的点是否存在终点, 如果不是, 就检测是否可以添加到open表中
		for (int i = 0; i < 4; i++)
		{
			//6.1.是否是终点(是, 就直接返回true)
				//是否是终点==>老巢有墙围着,因此判断是否到达终点周围
			if (abs(newNode[i].codSelf.X - m_End.X) <= 5 && newNode[i].codSelf.Y == m_End.Y ||
				abs(newNode[i].codSelf.Y - m_End.Y) <= 5 && newNode[i].codSelf.X == m_End.X)
			{
				//保存终点进close表中
				m_vecCloseList.push_back(newNode[i]);
				return true;
			}
			//6.2.是否越界
			if (newNode[i].codSelf.X < 2 || newNode[i].codSelf.X > m_nMapW - 3 ||
				newNode[i].codSelf.Y < 2 || newNode[i].codSelf.Y > m_nMapH - 3)
			{
				//继续检测下一九宫格
				continue;
			}
			//6.3.是否是障碍物
			bool IsBlock = false;
			for (int j = 1; j < 4; j++)
			{
				if (m_nMap[level][m_TankCoord[i][j].Y][m_TankCoord[i][j].X] == WALL ||
					m_nMap[level][m_TankCoord[i][j].Y][m_TankCoord[i][j].X] == STEEL ||
					m_nMap[level][m_TankCoord[i][j].Y][m_TankCoord[i][j].X] == WATER)
				{
					IsBlock = true;
					break;	//继续检测下一九宫格
				}
			}
			if (IsBlock)
			{
				continue;
			}
			//6.4.是否在open表中					//6.5.是否在close表中
			if (m_pTempMap[newNode[i].codSelf.Y * m_nMapW + newNode[i].codSelf.X].bIsOpen ||
				m_pTempMap[newNode[i].codSelf.Y * m_nMapW + newNode[i].codSelf.X].bIsClose)
			{
				continue;
			}
			//7.把检测合格的点添加到open表中
			m_vecOpenList.push_back(newNode[i]);
			m_pTempMap[newNode[i].codSelf.Y * m_nMapW + newNode[i].codSelf.X].bIsOpen = true;
			//8.重复3 - 7步
		}
	}
	return true;
}
