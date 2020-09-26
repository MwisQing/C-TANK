#pragma once
#include <windows.h>
#include <vector>
using std::vector;

/*********************************************************************************
AStar�㷨:
	openList:��������ĵ�
	closeList:�����Ѽ��ĵ�(�������·��)
	G Path:�ƶ����(������㿪ʼÿ��һ����1,б�߼Ӹ���2)
	H Path:��Ŀ�ĵؾ���
	F Path:F=G+H
**********************************************************************************/

class CAStar
{
public:
	//�Զ��������ṹ��
	typedef struct _MYCOORD :public COORD
	{
		//���صȺ������������Ƚ�
		bool operator==(COORD cod)
		{
			return (X == cod.X) && (Y == cod.Y);
		}
		//���ظ�ֵ����������㸳ֵ
		void operator=(COORD cod)
		{
			X = cod.X;
			Y = cod.Y;
		}
		int d; //����㷽��
	}MYCOORD, * PMYCOORD;

	//�ڵ����Ϣ�ṹ��
	typedef struct _NODEINFO
	{
		int nG;//�ƶ���ģ�ÿһ��һ�μ�1��
		int nH;//�����յ���̾���
		int nF;//nG+nH

		void SetHF(COORD cod2)
		{
			nH = abs(codSelf.X - cod2.X) + abs(codSelf.Y - cod2.Y);
			nF = nG + nH;
		}
		MYCOORD codSelf;  //��������
		MYCOORD codParent;//�������(��˭��ɢ�����ĵ������)
	}NODEINFO, * PNODEINFO;

private:
	void GetTankCoord(COORD tank);		//��ȡ̹�˾Ź�����������
	vector<NODEINFO> m_vecOpenList;		//�����ĵ�ļ���
	vector<NODEINFO> m_vecCloseList;	//�����ĵ㣨��ɢ���ĵ㣩�ļ���
	COORD m_TankCoord[4][4];			//̹�����ĵ�����+��ǰ������������

	int m_nMapH;						//��ͼ�߶�
	int m_nMapW;						//��ͼ���
	int (*m_pMap)[41];					//��ͼ�׵�ַ

	COORD m_Start;					//�������
	COORD m_End;						//�յ�����

	bool m_bInitMapInfo;				//�Ƿ��ʼ����ͼ��Ϣ
	bool m_bInitCoordInfo;				//�Ƿ��ʼ����ʼ����
public:
	void InitMapInfo(int pMap[41][41], int nHigh, int nWidth);			//��ʼ����ͼ��Ϣ
	void InitCoordInfo(_In_ COORD codStart, _In_ COORD codEnd);		//��ʼ������յ�����λ��
	void GetPath();												//��ȡ���·��
	bool FindPath(int level);										//Ѱ�Ұ������·���ĵ�

	typedef struct _TEMPMAP										//��ʱ��ͼ,����ýڵ��Ƿ���open���close��
	{
		bool bIsOpen;
		bool bIsClose;
	}TEMPMAP, * PTEMPMAP;
	PTEMPMAP m_pTempMap;											//��ʱ��ͼ
	vector<MYCOORD> m_vecPath;										//���·��
};

extern CAStar obj_AStar;