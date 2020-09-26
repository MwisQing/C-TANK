#pragma once
#include <windows.h>
#include <vector>
using std::vector;

/*********************************************************************************
AStar算法:
	openList:保存待检测的点
	closeList:保存已检测的点(包含最短路径)
	G Path:移动损耗(即从起点开始每走一步加1,斜走加根号2)
	H Path:离目的地距离
	F Path:F=G+H
**********************************************************************************/

class CAStar
{
public:
	//自定义的坐标结构体
	typedef struct _MYCOORD :public COORD
	{
		//重载等号运算符，方便比较
		bool operator==(COORD cod)
		{
			return (X == cod.X) && (Y == cod.Y);
		}
		//重载赋值运算符，方便赋值
		void operator=(COORD cod)
		{
			X = cod.X;
			Y = cod.Y;
		}
		int d; //坐标点方向
	}MYCOORD, * PMYCOORD;

	//节点的信息结构体
	typedef struct _NODEINFO
	{
		int nG;//移动损耗（每一动一次加1）
		int nH;//距离终点最短距离
		int nF;//nG+nH

		void SetHF(COORD cod2)
		{
			nH = abs(codSelf.X - cod2.X) + abs(codSelf.Y - cod2.Y);
			nF = nG + nH;
		}
		MYCOORD codSelf;  //自身坐标
		MYCOORD codParent;//父坐标点(由谁扩散出来的点的坐标)
	}NODEINFO, * PNODEINFO;

private:
	void GetTankCoord(COORD tank);		//获取坦克九宫格坐标坐标
	vector<NODEINFO> m_vecOpenList;		//待检测的点的集合
	vector<NODEINFO> m_vecCloseList;	//检测过的点（扩散过的点）的集合
	COORD m_TankCoord[4][4];			//坦克中心点坐标+当前方向三点坐标

	int m_nMapH;						//地图高度
	int m_nMapW;						//地图宽度
	int (*m_pMap)[41];					//地图首地址

	COORD m_Start;					//起点坐标
	COORD m_End;						//终点坐标

	bool m_bInitMapInfo;				//是否初始化地图信息
	bool m_bInitCoordInfo;				//是否初始化起始坐标
public:
	void InitMapInfo(int pMap[41][41], int nHigh, int nWidth);			//初始化地图信息
	void InitCoordInfo(_In_ COORD codStart, _In_ COORD codEnd);		//初始化起点终点坐标位置
	void GetPath();												//获取最短路径
	bool FindPath(int level);										//寻找包含最短路径的点

	typedef struct _TEMPMAP										//临时地图,保存该节点是否在open表或close中
	{
		bool bIsOpen;
		bool bIsClose;
	}TEMPMAP, * PTEMPMAP;
	PTEMPMAP m_pTempMap;											//临时地图
	vector<MYCOORD> m_vecPath;										//最短路径
};

extern CAStar obj_AStar;