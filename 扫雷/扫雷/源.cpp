#include<stdio.h>
#include<easyx.h>
#include<time.h>

//地图数组
int map[10][10] = { 0 };
//设置辅助数组
struct nodeMap
{
	int val;  //对应地图内的数值
	int x, y;  //对应地图坐标
	int sign;  //标记(翻开/未翻开)
};
//图片数组
IMAGE img[14];
nodeMap myMap[10][10] = { 0 };
int dir[8][2] = { 
	{ -1, -1 }, { -1, 0 }, { -1, 1 }, { 0, -1 },
	{ 0, 1 }, { 1, -1 }, { 1, 0 }, { 1, 1 }
};
//初始化地图
//-1表示雷
//0表示没有雷
//其他数字表示附近雷的个数
void initMap()
{
	int x = 0, y = 0; //标记雷的坐标
	for (int i = 0; i < 10;)
	{
		x = rand() % 10;
		y = rand() % 10;
		if (map[x][y] != -1)
		{
			map[x][y] = -1;
			i++;
		}
	}
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (map[i][j] == -1)
			{
				for (int m = i - 1; m <= i + 1; m++)
				{
					for (int n = j - 1; n <= j + 1; n++)
					{
						if (m >= 0 && m <= 9 && n >= 0 && n <= 9 && map[m][n] != -1)
							map[m][n]++;
					}
				}
			}
		}

	}


}
//初始化图片数组
void initImg()
{
	//sprintf(格式化写入函数)
	char str[30] = { 0 };
	for (int i = 0; i < 14; i++)
	{
		sprintf(str, "res/%d.jpg", i);
		loadimage(&img[i], str, 50, 50);
	}

}
//初始化辅助数组
void initMymap()
{

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			myMap[i][j].sign = 0;
			myMap[i][j].val = map[i][j];
			myMap[i][j].x = i;
			myMap[i][j].y = j;
		}
	}
}
//贴图
void drawMap()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			switch (myMap[i][j].val)
			{
			case 10:
				putimage(j * 50, i * 50, &img[0]);
				break;
			case 11:
				putimage(j * 50, i * 50, &img[1]);
				break;
			case 12:
				putimage(j * 50, i * 50, &img[2]);
				break;
			case 13:
				putimage(j * 50, i * 50, &img[3]);
				break;
			case 14:
				putimage(j * 50, i * 50, &img[4]);
				break;
			case 15:
				putimage(j * 50, i * 50, &img[5]);
				break;
			case 16:
				putimage(j * 50, i * 50, &img[6]);
				break;
			case 17:
				putimage(j * 50, i * 50, &img[7]);
				break;
			case 18:
				putimage(j * 50, i * 50, &img[8]);
				break;
			case 9:
				putimage(j * 50, i * 50, &img[9]);
				break;
			case 111:
				putimage(j * 50, i * 50, &img[11]);
				break;
			case 222:
				putimage(j * 50, i * 50, &img[10]);
				break;
			default:
				putimage(j * 50, i * 50, &img[12]);
			}
		}
	}
}
//鼠标操作
void overreturn(int x,int y)
{
	for (int i = 0; i < 8; i++)
	{
		if (myMap[x][y].val != -1)
		{
			int dx = dir[i][1] + x;
			int dy = dir[i][0] + y;
			if (dx < 0 || dx >= 10 || dy < 0 || dy >= 10)
				continue;
			if (myMap[dx][dy].val == 0)
			{
				myMap[dx][dy].val += 10;
				overreturn(dx, dy);
			}
			else if (myMap[dx][dy].val < 9 && myMap[dx][dy].val != -1)
			{
				myMap[dx][dy].val += 10;
			}
		}
	}
}

void iswin()
{
	int sum = 0;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (myMap[i][j].val<9 || myMap[i][j].val>100)
			{
				sum++;
			}
		}
		
	}
	if (sum == 10)
	{
		if (MessageBox(GetHWnd(), "不愧是你李淑媛小姐姐！", "提示", MB_YESNO) == IDYES)
		{
			memset(map, 0, 400);
			initMap();
			initMymap();
			drawMap();
		}
		else
		{
			exit(0);
		}
	}
}

void play()
{
	iswin();
	int x = 0, y = 0;
	MOUSEMSG msg = GetMouseMsg();  //获取鼠标消息
	switch (msg.uMsg)
	{
	case WM_LBUTTONDOWN:  //左键
		x = msg.y / 50;
		y = msg.x / 50;
		if (myMap[x][y].val >= 10) 
			break;
		else if (myMap[x][y].val == -1)
		{
			//MessageBox()函数：弹窗
			if (MessageBox(GetHWnd(), "你这个大笨蛋", "提示", MB_YESNO) == IDYES)
			{
				memset(map, 0, 400);
				initMap();
				initMymap();
				drawMap();
			}
			else{
				exit(0);
			}
		}
		else if (myMap[x][y].val == 0)
		{
			myMap[x][y].val += 10;
			overreturn(x, y);
		}
		else
		{
			myMap[x][y].val += 10;
		}
		break;
	case WM_RBUTTONDOWN:  //右键
			x = msg.y / 50;
		y = msg.x / 50;
		if (myMap[x][y].val < 9 || myMap[x][y].val == 111 || myMap[x][y].val == 222)
		{
			if (myMap[x][y].sign == 0)
			{
				myMap[x][y].sign++;
				myMap[x][y].val = 111;
			}
			else if (myMap[x][y].sign == 1)
			{
				myMap[x][y].sign++;
				myMap[x][y].val = 222;
			}
			else if (myMap[x][y].sign == 2)
			{
				myMap[x][y].sign = 0;
				myMap[x][y].val = map[x][y];
			}
		}
		break;
	}
}
void show()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (myMap[i][j].val < 9)
			{
				myMap[i][j].val += 10;
			}

		}
	}
}
//主函数
int main()
{
	initgraph(10 * 50, 10 * 50);
	srand((unsigned)time(NULL));   //设置及随机数种子
	initMap();
	initImg();
	initMymap();
	while (1)
	{
		drawMap();
		play();
	}

	//展示地图数组
	/*for (int i = 0; i < 10; i++)
	{
	for (int j = 0; j < 10; j++)
	{
	printf("%d\t", map[i][j]);
	}
	printf("\n");
	}*/
	getchar();
	getchar();
	return 0;
}