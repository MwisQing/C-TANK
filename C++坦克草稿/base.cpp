#include "base.h"
#include "CBullet.h"
#include "CTank.h"

//计分功能
extern int nCount = 0;
//关卡
extern int nLevel = 0;
//编辑地图关卡
extern int temp_level = 0;
//存档读档
extern FILE* pFile = nullptr;
//接收用户选择
extern char nChoice = 0;

//根据光标打印
void WriteChar(int x, int y, const char* szBuf, int nColor)
{
	COORD pos = { 2 * x,y };
	HANDLE hStdin = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hStdin, pos);
	//设置颜色
	SetConsoleTextAttribute(hStdin, nColor);
	printf(szBuf);

	// 隐藏光标 
	CONSOLE_CURSOR_INFO cursor;
	cursor.bVisible = FALSE;
	cursor.dwSize = sizeof(cursor);
	SetConsoleCursorInfo(hStdin, &cursor);
}

//判断时候有键盘输入  有就return键盘输入的值  没有就return 0
char GetOper()
{
	if (_kbhit())
	{
		return _getch();
	}
	return 0;
}
/********************************************************
函数功能	:坦克、炮弹的核心函数
参数		:关卡
返回值	:无
*********************************************************/
void CoreInfo(int & level)
{
	//接收按键的变量
	char cOper = 0;

	//敌方坦克变化方向的时间
	int temp_time1 = 0;
	//随机坦克的方向
	char Random_Dir1 = 0;
	int Random_num1 = 0;
	//敌方坦克变化方向的时间
	int temp_time2 = 0;
	//随机坦克2的方向
	char Random_Dir2 = 0;
	int Random_num2 = 0;

	WriteChar(42, 2, "Player 1 按键:          W ", 12);
	WriteChar(42, 4, "                  A     S     D      发炮: J", 12);
	WriteChar(42, 6, "Player 2 按键:          up ", 14);
	WriteChar(42, 8, "                left   down   right  发炮: num1", 14);
	WriteChar(42, 10, "同时操控两个坦克 按键: ", 10);
	WriteChar(42, 11, "                        T ", 10);
	WriteChar(42, 13, "                  F     G     H      发炮: K", 10);
	WriteChar(42, 16, "按C存档 ", 12);
	


	
	while (true)
	{
		//接收按键输入
		cOper = GetOper();
		bullet_temp.MoveBullet(level);
		//计分
		WriteChar(42, 20, "得分：", 11);
		cout << nCount << endl;
		
		//随机改变敌方坦克方向
		g_Tank_Enemy_temp.GetEnemyTankDir(temp_time1, Random_Dir1, Random_num1,300, g_Tank_Enemy_temp,level, g_stcTank);
		//随机改变敌方坦克2方向
		g_Tank_Enemy_temp2.GetEnemyTankDir(temp_time2, Random_Dir2, Random_num2,100, g_Tank_Enemy_temp2, level, g_stcTank2);
		
		//移动玩家坦克
		g_stcTank.MovePlayerTank(cOper, level);
		//移动玩家2坦克
		g_stcTank2.MovePlayerTank2(cOper, level);
		//移动敌方坦克
		g_Tank_Enemy_temp.MoveEnemyTank(Random_Dir1, level, g_Tank_Enemy_temp,02);
		//移动敌方坦克2
		g_Tank_Enemy_temp2.MoveEnemyTank(Random_Dir2, level, g_Tank_Enemy_temp2,01);

		//当两个敌方坦克都死亡
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
				WriteChar(20, 20, "恭 喜 通 关", 0x0004 | 0x0008);
				Sleep(1000);
				WriteChar(30, 30, " ", 3);
			}
		}
		//当两个玩家坦克都死亡  or 家被破坏
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
函数功能	:欢迎界面
参数		:用户的选择
返回值	:无
*********************************************************/
void Welcome(char & choice)
{
	//控制台窗口大小
	system("mode con cols=145 lines=50");

	WriteChar(23, 16, "1.  新 游 戏", 4);
	WriteChar(23, 19, "2.  继续游戏", 2);
	WriteChar(23, 22, "3.  地图设置", 6);
	WriteChar(23, 25, "4.  退出游戏", 3);
	WriteChar(23, 40, "", 0);
	choice = _getch();
	system("cls");
}

//发出炮弹音效
void Sendout_bullet()
{
	//PlaySound(TEXT("D:\\1学习代码\\新草稿\\新草稿\\发出炮弹.wav"), NULL, SND_FILENAME | SND_ASYNC);
}
//击碎石墙
void Smash_Stonewall()
{
	//PlaySound(TEXT("D:\\1学习代码\\新草稿\\新草稿\\击碎石墙.wav"), NULL, SND_FILENAME | SND_ASYNC);
}




/********************************************************
函数功能	:编辑地图
参数		:地图数组  用户的选择  关卡
返回值	:无
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


	char* cCh = "▓";
	int nNum = 1;
	int nColor = 228;

	WriteChar(42, 2, "左键画    右键擦", 10);
	WriteChar(42, 4, "q  石 墙", 12);
	WriteChar(48, 4, "▓", 228);
	WriteChar(42, 6, "w  铁 墙", 12);
	WriteChar(48, 6, "■", 15);
	WriteChar(42, 8, "e   水", 12);
	WriteChar(48, 8, "~~", 25);
	WriteChar(42, 10, "r 草 地", 12);
	WriteChar(48, 10, "※", 10);
	WriteChar(42, 12, "按两下空格   下一关", 11);
	WriteChar(42, 14, "m   退出，进入游戏", 14);

	while (true)
	{
		ReadConsoleInput(  //能够读取控制台相关的输入：包括鼠标和键盘
			hStdIn, //输入句柄
			&ir,    //获取输入信息的结构体
			1,      //缓冲区有几个结构体
			&nSize  //传输了多少个字节，没有什么用
		);

		//如果是一个鼠标事件的话
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
				cCh = "▓";
				nNum = 1;
				nColor = 228;
			}
			if (ir.Event.KeyEvent.uChar.AsciiChar == 'w')
			{
				cCh = "■";
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
				cCh = "※";
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
函数功能	:初始化4个坦克
参数		:无
返回值	:无
*********************************************************/
void Set_Tank()
{
	//初始化玩家坦克的中心位置
	g_stcTank.initialization_TANK(g_stcTank, 玩家坦克0, 14, 38);
	//初始化玩家2坦克的中心位置
	g_stcTank2.initialization_TANK(g_stcTank2, 玩家坦克1, 26, 38);
	//初始化敌方坦克
	g_Tank_Enemy_temp.Set_EnemyTank();
	//初始化敌方坦克2
	g_Tank_Enemy_temp2.Set_EnemyTank2();
}

/********************************************************
函数功能:画坦克 画地图
参数		:关卡
返回值	:无
*********************************************************/
void DrawAll(int level)
{
	//画地图
	DrawMap(level);
	DrawHome();
	//画一个初始敌方坦克
	g_Tank_Enemy_temp.DrawTank(g_Tank_Enemy_temp, 02, 敌方坦克0, level);
	//画一个初始敌方坦克2
	g_Tank_Enemy_temp2.DrawTank(g_Tank_Enemy_temp2, 01, 敌方坦克1, level);
	//画一个初始玩家坦克
	g_stcTank.DrawTank(g_stcTank, 04, 玩家坦克0, level);
	//画一个初始玩家坦克2
	g_stcTank2.DrawTank(g_stcTank2, 06, 玩家坦克1, level);
}

/********************************************************
函数功能:读档
参数		:无
返回值	:无
*********************************************************/
void ReadPassWordInfo()
{
	int nError = fopen_s(    //打开文件
		&pFile,
		"坦克大战存档文件.a",
		"rb+"
	);
	if (nError != 0) //如果没有文件  则返回
	{
		return;
	}
	
	//读取地图
	fread(m_nMap, 4, 8 * 41 * 41, pFile);
	//读取关卡
	fread(&nLevel, 4, 1, pFile);
	//读取分数
	fread(&nCount, 4, 1, pFile);
	//读取玩家坦克1
	fread(&g_stcTank, sizeof(TANK), 1, pFile);
	//读取玩家坦克2
	fread(&g_stcTank2, sizeof(TANK), 1, pFile);
	//读取敌方坦克1
	fread(&g_Tank_Enemy_temp, sizeof(TANK), 1, pFile);
	//读取敌方坦克2
	fread(&g_Tank_Enemy_temp2, sizeof(TANK), 1, pFile);
	//子弹数量
	int nBulletNum = 0;
	// 1. 读取子弹长度
	fread(&nBulletNum, 4, 1, pFile);
	// 2. 清空vector内容
	bullet.clear();
	// 3. 给vector申请空间
	bullet.resize(nBulletNum);
	// 4.循环读取内容
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
函数功能:存档
参数		:无
返回值	:无
*********************************************************/
void SaveFile()
{
	fopen_s(
		&pFile,
		"坦克大战存档文件.a",
		"wb"
	);
	//保存地图
	fwrite(m_nMap, 4, 8*41*41, pFile);
	//存关卡
	fwrite(&nLevel, 4, 1, pFile);
	//存分数
	fwrite(&nCount, 4, 1, pFile);
	//保存玩家坦克1
	fwrite(&g_stcTank, sizeof(TANK), 1, pFile);
	//保存玩家坦克2
	fwrite(&g_stcTank2, sizeof(TANK), 1, pFile);
	//保存敌方坦克1
	fwrite(&g_Tank_Enemy_temp, sizeof(TANK), 1, pFile);
	//保存敌方坦克2
	fwrite(&g_Tank_Enemy_temp2, sizeof(TANK), 1, pFile);
	//保存子弹数量
	int nBulletNum = bullet.size();
	fwrite(&nBulletNum, 4, 1, pFile);
	for (int i = 0; i < nBulletNum; i++)
	{
		fwrite(&bullet[i], sizeof(BULLET), 1, pFile);
	}
	fclose(pFile);
}

/********************************************************
函数功能 :打印正在读档
参数		:无
返回值	:无
*********************************************************/
void PrintRead()
{
	for (int i = 0; i < 1; i++)
	{
		WriteChar(20, 20, "                ", 0x0004 | 0x0008);
		WriteChar(20, 20, "正 在 读 取", 0x0004 | 0x0008);
		Sleep(500);
		WriteChar(20, 20, "                ", 0x0004 | 0x0008);
		WriteChar(20, 20, "正 在 读 取.", 0x0004 | 0x0008);
		Sleep(500);
		WriteChar(20, 20, "                ", 0x0004 | 0x0008);
		WriteChar(20, 20, "正 在 读 取..", 0x0004 | 0x0008);
		Sleep(500);
		WriteChar(20, 20, "                ", 0x0004 | 0x0008);
		WriteChar(20, 20, "正 在 读 取...", 0x0004 | 0x0008);
		Sleep(500);
	}

}
/********************************************************
函数功能 :打印正在存档
参数		:无
返回值	:无
*********************************************************/
void PrintSave()
{
	for (int i = 0; i < 2; i++)
	{
		WriteChar(42, 16, "            ", 0);
		WriteChar(42, 16, "正在存档", 3);
		Sleep(500);
		WriteChar(42, 16, "正在存档.", 3);
		Sleep(500);
		WriteChar(42, 16, "正在存档..", 3);
		Sleep(500);
		WriteChar(42, 16, "正在存档...", 3);
		Sleep(500);
	}
	WriteChar(42, 16, "            ", 0);
	WriteChar(42, 16, "存档成功!", 3);
	Sleep(1000);
	WriteChar(42, 16, "            ", 0);
}
/********************************************************
函数功能:画家
参数		:无
返回值	:无
*********************************************************/
void DrawHome()
{
	WriteChar(19, 37, "◣★◢",15); 
	WriteChar(19, 38, "███",15); 
	WriteChar(19, 39,	"◢█◣",15); 
}

//游戏引擎函数
void GameStart()
{
	//读档
	if (nChoice == '2')
	{
		//读档
		ReadPassWordInfo();
		//打印一个正在读取
		PrintRead();
		system("cls");
	}
	//退出游戏
	if (nChoice == '4')
	{
		return ;
	}
	//编辑地图
	while (nChoice == '3')
	{
		InitMap(m_nMap, nChoice, temp_level);
	}
	//进入游戏
	while (nLevel < 8)
	{
		//画坦克画地图
		DrawAll(nLevel);
		//进入游戏
		CoreInfo(nLevel);
		//初始化坦克
		Set_Tank();
	}
}