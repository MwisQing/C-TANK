#pragma once
//��ͼ����
extern int m_nMap[8][41][41];
//��ͼ�ĺ�
#define WALL			1	//'��' �ɴݻ�
#define FRAME			4	//'��'���ɴݻ�
#define HOME			9	//'��'��
#define STEEL			6	//'��'���ɴݻ�
#define WATER			5	//'~' ˮ
#define GROUND		0	//�յ�
#define GRASS			2   //�� ��

#define �з��ڵ�		11
#define ����ڵ�		12
#define �з�̹��0		13
#define ���̹��0		14
#define �з�̹��1		15
#define ���̹��1		16
//����ͼ
void DrawMap(int level);