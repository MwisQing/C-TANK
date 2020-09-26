#pragma once
#include"base.h"


//�ڵ���
class BULLET
{
public:
	
	//����ڵ� ���Ҳ������µ��ڵ�
	void ClearBullet(int x, int y, int i, int level);

	//���ڵ�
	void DrawBullet(int x, int y, int colof, int play_enemy, int level);

	//�ж��ڵ�����ײ    ���룺�����ײ
	int IfCollide(int x, int y, int i,int player_enemy, int level);

	//�ƶ��ڵ�  �������������ڵ�  ���ڵ�
	void MoveBullet( int level);

	//����j��ı�vector
	void SetBullet_vector(int nDir, int x, int y,int play_enemy);
	//�ı��ڵ�ʱ��Ľӿ�
	void BULLET::SetTime(BULLET & blt);

	//��Ԫ����
	friend void CoreInfo(int& level);
	
	
private:
	COORD pos;
	int nDir;
	//�ڵ��ƶ����ٶ�
	int nSpeed;
	//�ڵ���¼��ʱ��
	int nLastClock;
	//�ж��ڵ��Ƿ����
	int nExist;
	//�ж��Ƿ������ڵ�
	int isNew;
	//�ж��ǵз��ڵ���������ڵ�
	int nBullet_player_enemy;
};

//�ڵ�����
extern vector<BULLET>bullet;

//�ڵ������(���߶���)
extern BULLET bullet_temp;

