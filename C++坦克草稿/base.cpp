#include "base.h"
#include "CBullet.h"
#include "CTank.h"

//�Ʒֹ���
extern int nCount = 0;
//�ؿ�
extern int nLevel = 0;
//�༭��ͼ�ؿ�
extern int temp_level = 0;
//�浵����
extern FILE* pFile = nullptr;
//�����û�ѡ��
extern char nChoice = 0;

//���ݹ���ӡ
void WriteChar(int x, int y, const char* szBuf, int nColor)
{
	COORD pos = { 2 * x,y };
	HANDLE hStdin = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hStdin, pos);
	//������ɫ
	SetConsoleTextAttribute(hStdin, nColor);
	printf(szBuf);

	// ���ع�� 
	CONSOLE_CURSOR_INFO cursor;
	cursor.bVisible = FALSE;
	cursor.dwSize = sizeof(cursor);
	SetConsoleCursorInfo(hStdin, &cursor);
}

//�ж�ʱ���м�������  �о�return���������ֵ  û�о�return 0
char GetOper()
{
	if (_kbhit())
	{
		return _getch();
	}
	return 0;
}
/********************************************************
��������	:̹�ˡ��ڵ��ĺ��ĺ���
����		:�ؿ�
����ֵ	:��
*********************************************************/
void CoreInfo(int & level)
{
	//���հ����ı���
	char cOper = 0;

	//�з�̹�˱仯�����ʱ��
	int temp_time1 = 0;
	//���̹�˵ķ���
	char Random_Dir1 = 0;
	int Random_num1 = 0;
	//�з�̹�˱仯�����ʱ��
	int temp_time2 = 0;
	//���̹��2�ķ���
	char Random_Dir2 = 0;
	int Random_num2 = 0;

	WriteChar(42, 2, "Player 1 ����:          W ", 12);
	WriteChar(42, 4, "                  A     S     D      ����: J", 12);
	WriteChar(42, 6, "Player 2 ����:          up ", 14);
	WriteChar(42, 8, "                left   down   right  ����: num1", 14);
	WriteChar(42, 10, "ͬʱ�ٿ�����̹�� ����: ", 10);
	WriteChar(42, 11, "                        T ", 10);
	WriteChar(42, 13, "                  F     G     H      ����: K", 10);
	WriteChar(42, 16, "��C�浵 ", 12);
	


	
	while (true)
	{
		//���հ�������
		cOper = GetOper();
		bullet_temp.MoveBullet(level);
		//�Ʒ�
		WriteChar(42, 20, "�÷֣�", 11);
		cout << nCount << endl;
		
		//����ı�з�̹�˷���
		g_Tank_Enemy_temp.GetEnemyTankDir(temp_time1, Random_Dir1, Random_num1,300, g_Tank_Enemy_temp,level, g_stcTank);
		//����ı�з�̹��2����
		g_Tank_Enemy_temp2.GetEnemyTankDir(temp_time2, Random_Dir2, Random_num2,100, g_Tank_Enemy_temp2, level, g_stcTank2);
		
		//�ƶ����̹��
		g_stcTank.MovePlayerTank(cOper, level);
		//�ƶ����2̹��
		g_stcTank2.MovePlayerTank2(cOper, level);
		//�ƶ��з�̹��
		g_Tank_Enemy_temp.MoveEnemyTank(Random_Dir1, level, g_Tank_Enemy_temp,02);
		//�ƶ��з�̹��2
		g_Tank_Enemy_temp2.MoveEnemyTank(Random_Dir2, level, g_Tank_Enemy_temp2,01);

		//�������з�̹�˶�����
		if (g_Tank_Enemy_temp.nTank_Exist == 2 && g_Tank_Enemy_temp2.nTank_Exist == 2)
		{
			system("cls");
			WriteChar(20, 20, "You     Win", 3);
			WriteChar(30, 30, " ", 3);
			Sleep(1000);
			level++;
			system("cls");
			for (int i = 0; i < bullet.size(); i++)
			{
				bullet_temp.ClearBullet(bullet[i].pos.X, bullet[i].pos.Y, i, level);
				bullet[i].nExist = 0;
			}
			vector<BULLET>().swap(bullet);
			obj_AStar.m_vecPath.clear();
			break;
			if (level > 7)
			{
				system("cls");
				WriteChar(20, 20, "�� ϲ ͨ ��", 0x0004 | 0x0008);
				Sleep(1000);
				WriteChar(30, 30, " ", 3);
			}
		}
		//���������̹�˶�����  or �ұ��ƻ�
		if (g_stcTank.nTank_Exist == 2 && g_stcTank2.nTank_Exist == 2)
		{
			system("cls");
			WriteChar(20, 20, "You     Lose", 0x0004 | 0x0008);
			WriteChar(30, 30, " ", 3);
			Sleep(2000);
			system("cls");
			for (int i = 0; i < bullet.size(); i++)
			{
				bullet_temp.ClearBullet(bullet[i].pos.X, bullet[i].pos.Y, i, level);
				bullet[i].nExist = 0;
			}
			vector<BULLET>().swap(bullet);
			break;
		}
		
	}
}

/********************************************************
��������	:��ӭ����
����		:�û���ѡ��
����ֵ	:��
*********************************************************/
void Welcome(char & choice)
{
	//����̨���ڴ�С
	system("mode con cols=145 lines=50");

	WriteChar(23, 16, "1.  �� �� Ϸ", 4);
	WriteChar(23, 19, "2.  ������Ϸ", 2);
	WriteChar(23, 22, "3.  ��ͼ����", 6);
	WriteChar(23, 25, "4.  �˳���Ϸ", 3);
	WriteChar(23, 40, "", 0);
	choice = _getch();
	system("cls");
}

//�����ڵ���Ч
void Sendout_bullet()
{
	//PlaySound(TEXT("D:\\1ѧϰ����\\�²ݸ�\\�²ݸ�\\�����ڵ�.wav"), NULL, SND_FILENAME | SND_ASYNC);
}
//����ʯǽ
void Smash_Stonewall()
{
	//PlaySound(TEXT("D:\\1ѧϰ����\\�²ݸ�\\�²ݸ�\\����ʯǽ.wav"), NULL, SND_FILENAME | SND_ASYNC);
}




/********************************************************
��������	:�༭��ͼ
����		:��ͼ����  �û���ѡ��  �ؿ�
����ֵ	:��
*********************************************************/
void InitMap(int m_nMap[8][41][41], char & choice, int & level)
{
	DrawAll(level);
	HANDLE hStdIn = GetStdHandle(STD_INPUT_HANDLE);
	DWORD modle;
	GetConsoleMode(hStdIn, &modle);
	SetConsoleMode(hStdIn, modle | ENABLE_MOUSE_INPUT);
	INPUT_RECORD ir = { 0 };
	unsigned long nSize = 0;


	char* cCh = "��";
	int nNum = 1;
	int nColor = 228;

	WriteChar(42, 2, "�����    �Ҽ���", 10);
	WriteChar(42, 4, "q  ʯ ǽ", 12);
	WriteChar(48, 4, "��", 228);
	WriteChar(42, 6, "w  �� ǽ", 12);
	WriteChar(48, 6, "��", 15);
	WriteChar(42, 8, "e   ˮ", 12);
	WriteChar(48, 8, "~~", 25);
	WriteChar(42, 10, "r �� ��", 12);
	WriteChar(48, 10, "��", 10);
	WriteChar(42, 12, "�����¿ո�   ��һ��", 11);
	WriteChar(42, 14, "m   �˳���������Ϸ", 14);

	while (true)
	{
		ReadConsoleInput(  //�ܹ���ȡ����̨��ص����룺�������ͼ���
			hStdIn, //������
			&ir,    //��ȡ������Ϣ�Ľṹ��
			1,      //�������м����ṹ��
			&nSize  //�����˶��ٸ��ֽڣ�û��ʲô��
		);

		//�����һ������¼��Ļ�
		if (ir.EventType == MOUSE_EVENT)
		{
			if (ir.Event.MouseEvent.dwButtonState == 1)
			{
				int x = ir.Event.MouseEvent.dwMousePosition.X;
				int y = ir.Event.MouseEvent.dwMousePosition.Y;
				if (x/2 < 41 && y < 41 && m_nMap[level][y][x / 2] == 0)
				{
					m_nMap[level][y][x / 2] = nNum;
					WriteChar(x / 2, y, cCh, nColor);
				}
			}
			if (ir.Event.MouseEvent.dwButtonState == 2)
			{
				int x = ir.Event.MouseEvent.dwMousePosition.X;
				int y = ir.Event.MouseEvent.dwMousePosition.Y;
				if (m_nMap[level][y][x / 2] < 9 && m_nMap[level][y][x / 2] != 4)
				{
					m_nMap[level][y][x / 2] = 0;
					WriteChar(x / 2, y, "  ");
				}
			}
		}
		else if (ir.EventType == KEY_EVENT)
		{
			if (ir.Event.KeyEvent.uChar.AsciiChar == 'm')
			{
				WriteChar(0, 0, " ", 0);
				system("cls");
				choice = 1;
				break;
			}
			if (ir.Event.KeyEvent.uChar.AsciiChar == 'q')
			{
				cCh = "��";
				nNum = 1;
				nColor = 228;
			}
			if (ir.Event.KeyEvent.uChar.AsciiChar == 'w')
			{
				cCh = "��";
				nNum = 6;
				nColor = 15;
			}
			if (ir.Event.KeyEvent.uChar.AsciiChar == 'e')
			{
				cCh = "~~";
				nNum = 5;
				nColor = 25;
			}
			if (ir.Event.KeyEvent.uChar.AsciiChar == 'r')
			{
				cCh = "��";
				nNum = 2;
				nColor = 10;
			}
			if (ir.Event.KeyEvent.uChar.UnicodeChar == ' ')
			{
				char cCh = _getch();
				if (level < 7 && cCh == ' ')
				{
					system("cls");
					level++;
					break;
				}
			}
		}
	}
}
/********************************************************
��������	:��ʼ��4��̹��
����		:��
����ֵ	:��
*********************************************************/
void Set_Tank()
{
	//��ʼ�����̹�˵�����λ��
	g_stcTank.initialization_TANK(g_stcTank, ���̹��0, 14, 38);
	//��ʼ�����2̹�˵�����λ��
	g_stcTank2.initialization_TANK(g_stcTank2, ���̹��1, 26, 38);
	//��ʼ���з�̹��
	g_Tank_Enemy_temp.Set_EnemyTank();
	//��ʼ���з�̹��2
	g_Tank_Enemy_temp2.Set_EnemyTank2();
}

/********************************************************
��������:��̹�� ����ͼ
����		:�ؿ�
����ֵ	:��
*********************************************************/
void DrawAll(int level)
{
	//����ͼ
	DrawMap(level);
	DrawHome();
	//��һ����ʼ�з�̹��
	g_Tank_Enemy_temp.DrawTank(g_Tank_Enemy_temp, 02, �з�̹��0, level);
	//��һ����ʼ�з�̹��2
	g_Tank_Enemy_temp2.DrawTank(g_Tank_Enemy_temp2, 01, �з�̹��1, level);
	//��һ����ʼ���̹��
	g_stcTank.DrawTank(g_stcTank, 04, ���̹��0, level);
	//��һ����ʼ���̹��2
	g_stcTank2.DrawTank(g_stcTank2, 06, ���̹��1, level);
}

/********************************************************
��������:����
����		:��
����ֵ	:��
*********************************************************/
void ReadPassWordInfo()
{
	int nError = fopen_s(    //���ļ�
		&pFile,
		"̹�˴�ս�浵�ļ�.a",
		"rb+"
	);
	if (nError != 0) //���û���ļ�  �򷵻�
	{
		return;
	}
	
	//��ȡ��ͼ
	fread(m_nMap, 4, 8 * 41 * 41, pFile);
	//��ȡ�ؿ�
	fread(&nLevel, 4, 1, pFile);
	//��ȡ����
	fread(&nCount, 4, 1, pFile);
	//��ȡ���̹��1
	fread(&g_stcTank, sizeof(TANK), 1, pFile);
	//��ȡ���̹��2
	fread(&g_stcTank2, sizeof(TANK), 1, pFile);
	//��ȡ�з�̹��1
	fread(&g_Tank_Enemy_temp, sizeof(TANK), 1, pFile);
	//��ȡ�з�̹��2
	fread(&g_Tank_Enemy_temp2, sizeof(TANK), 1, pFile);
	//�ӵ�����
	int nBulletNum = 0;
	// 1. ��ȡ�ӵ�����
	fread(&nBulletNum, 4, 1, pFile);
	// 2. ���vector����
	bullet.clear();
	// 3. ��vector����ռ�
	bullet.resize(nBulletNum);
	// 4.ѭ����ȡ����
	for (int i = 0; i < nBulletNum; i++)
	{
		fread(&bullet[i], sizeof(BULLET), 1, pFile);
	}
	for (int i = 0; i < nBulletNum; i++)
	{
		bullet[i].SetTime(bullet[i]);
	}
	fclose(pFile);
}


/********************************************************
��������:�浵
����		:��
����ֵ	:��
*********************************************************/
void SaveFile()
{
	fopen_s(
		&pFile,
		"̹�˴�ս�浵�ļ�.a",
		"wb"
	);
	//�����ͼ
	fwrite(m_nMap, 4, 8*41*41, pFile);
	//��ؿ�
	fwrite(&nLevel, 4, 1, pFile);
	//�����
	fwrite(&nCount, 4, 1, pFile);
	//�������̹��1
	fwrite(&g_stcTank, sizeof(TANK), 1, pFile);
	//�������̹��2
	fwrite(&g_stcTank2, sizeof(TANK), 1, pFile);
	//����з�̹��1
	fwrite(&g_Tank_Enemy_temp, sizeof(TANK), 1, pFile);
	//����з�̹��2
	fwrite(&g_Tank_Enemy_temp2, sizeof(TANK), 1, pFile);
	//�����ӵ�����
	int nBulletNum = bullet.size();
	fwrite(&nBulletNum, 4, 1, pFile);
	for (int i = 0; i < nBulletNum; i++)
	{
		fwrite(&bullet[i], sizeof(BULLET), 1, pFile);
	}
	fclose(pFile);
}

/********************************************************
�������� :��ӡ���ڶ���
����		:��
����ֵ	:��
*********************************************************/
void PrintRead()
{
	for (int i = 0; i < 1; i++)
	{
		WriteChar(20, 20, "                ", 0x0004 | 0x0008);
		WriteChar(20, 20, "�� �� �� ȡ", 0x0004 | 0x0008);
		Sleep(500);
		WriteChar(20, 20, "                ", 0x0004 | 0x0008);
		WriteChar(20, 20, "�� �� �� ȡ.", 0x0004 | 0x0008);
		Sleep(500);
		WriteChar(20, 20, "                ", 0x0004 | 0x0008);
		WriteChar(20, 20, "�� �� �� ȡ..", 0x0004 | 0x0008);
		Sleep(500);
		WriteChar(20, 20, "                ", 0x0004 | 0x0008);
		WriteChar(20, 20, "�� �� �� ȡ...", 0x0004 | 0x0008);
		Sleep(500);
	}

}
/********************************************************
�������� :��ӡ���ڴ浵
����		:��
����ֵ	:��
*********************************************************/
void PrintSave()
{
	for (int i = 0; i < 2; i++)
	{
		WriteChar(42, 16, "            ", 0);
		WriteChar(42, 16, "���ڴ浵", 3);
		Sleep(500);
		WriteChar(42, 16, "���ڴ浵.", 3);
		Sleep(500);
		WriteChar(42, 16, "���ڴ浵..", 3);
		Sleep(500);
		WriteChar(42, 16, "���ڴ浵...", 3);
		Sleep(500);
	}
	WriteChar(42, 16, "            ", 0);
	WriteChar(42, 16, "�浵�ɹ�!", 3);
	Sleep(1000);
	WriteChar(42, 16, "            ", 0);
}
/********************************************************
��������:����
����		:��
����ֵ	:��
*********************************************************/
void DrawHome()
{
	WriteChar(19, 37, "���嗀",15); 
	WriteChar(19, 38, "������",15); 
	WriteChar(19, 39,	"������",15); 
}

//��Ϸ���溯��
void GameStart()
{
	//����
	if (nChoice == '2')
	{
		//����
		ReadPassWordInfo();
		//��ӡһ�����ڶ�ȡ
		PrintRead();
		system("cls");
	}
	//�˳���Ϸ
	if (nChoice == '4')
	{
		return ;
	}
	//�༭��ͼ
	while (nChoice == '3')
	{
		InitMap(m_nMap, nChoice, temp_level);
	}
	//������Ϸ
	while (nLevel < 8)
	{
		//��̹�˻���ͼ
		DrawAll(nLevel);
		//������Ϸ
		CoreInfo(nLevel);
		//��ʼ��̹��
		Set_Tank();
	}
}