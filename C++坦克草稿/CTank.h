#pragma once
#include<Windows.h>
#include"base.h"
#include "CAStar.h"

//̹����
class TANK
{
public:
	//��ʼ��̹�˵�����λ��
	void initialization_TANK(TANK& tank, int num, int x, int y);

	//�ж��ϰ���
	int IfTankCollide(int x, int y, int dir, int level);

	//��̹��
	void DrawTank(TANK Tank, int color,int num, int level);

	//��̹���ƶ�֮ǰ ��ԭ�ȵ�̹����� Ȼ���ٻ��µ�
	void ClearTank(TANK Tank, int level);

	//��Ԫ����
	friend void CoreInfo(int & level);
	//�ƶ����̹��
	void MovePlayerTank(char cOper, int level);
	//�ƶ����2̹��
	void MovePlayerTank2(char cOper, int level);
	//�ƶ��ط�̹��
	void MoveEnemyTank(char& Random_Dir, int level, TANK &tank, int color);

	//��ʼ���з�̹��
	void Set_EnemyTank();
	//��ʼ���з�̹��2
	void Set_EnemyTank2();

	//����ı�з�̹�˷���
	void GetEnemyTankDir(int& time, char& dir, int& num, int ntime, TANK tank,int level, TANK tank2);

	//̹��������ʱ�򣬸ı���ı�־
	void SetTankIfExist(int exist, TANK & tank);

private:
	//COORD��һ���ṹ���� x�� y��
	//pos ���̹�˵�����λ��
	COORD pos;
	//����
	int nDir;
	//�ж�̹���Ƿ���
	int nTank_Exist;
	//ÿһ��̹�˵ı�Ƕ���һ��
	//#define �з�̹��0		13
	//#define ���̹��0		14
	int nTank_Play_or_Enemy;
};

//����һ�����̹�˵Ķ���
extern TANK g_stcTank;
//����һ�����̹��2�Ķ���
extern TANK g_stcTank2;

//����һ���з�̹�˶���
extern TANK g_Tank_Enemy_temp;
//����һ���з�̹�˶���
extern TANK g_Tank_Enemy_temp2;

