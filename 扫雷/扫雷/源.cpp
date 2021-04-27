#include<stdio.h>
#include<easyx.h>
#include<time.h>

//��ͼ����
int map[10][10] = { 0 };
//���ø�������
struct nodeMap
{
	int val;  //��Ӧ��ͼ�ڵ���ֵ
	int x, y;  //��Ӧ��ͼ����
	int sign;  //���(����/δ����)
};
//ͼƬ����
IMAGE img[14];
nodeMap myMap[10][10] = { 0 };
int dir[8][2] = { 
	{ -1, -1 }, { -1, 0 }, { -1, 1 }, { 0, -1 },
	{ 0, 1 }, { 1, -1 }, { 1, 0 }, { 1, 1 }
};
//��ʼ����ͼ
//-1��ʾ��
//0��ʾû����
//�������ֱ�ʾ�����׵ĸ���
void initMap()
{
	int x = 0, y = 0; //����׵�����
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
//��ʼ��ͼƬ����
void initImg()
{
	//sprintf(��ʽ��д�뺯��)
	char str[30] = { 0 };
	for (int i = 0; i < 14; i++)
	{
		sprintf(str, "res/%d.jpg", i);
		loadimage(&img[i], str, 50, 50);
	}

}
//��ʼ����������
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
//��ͼ
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
//������
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
		if (MessageBox(GetHWnd(), "��������������С��㣡", "��ʾ", MB_YESNO) == IDYES)
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
	MOUSEMSG msg = GetMouseMsg();  //��ȡ�����Ϣ
	switch (msg.uMsg)
	{
	case WM_LBUTTONDOWN:  //���
		x = msg.y / 50;
		y = msg.x / 50;
		if (myMap[x][y].val >= 10) 
			break;
		else if (myMap[x][y].val == -1)
		{
			//MessageBox()����������
			if (MessageBox(GetHWnd(), "������󱿵�", "��ʾ", MB_YESNO) == IDYES)
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
	case WM_RBUTTONDOWN:  //�Ҽ�
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
//������
int main()
{
	initgraph(10 * 50, 10 * 50);
	srand((unsigned)time(NULL));   //���ü����������
	initMap();
	initImg();
	initMymap();
	while (1)
	{
		drawMap();
		play();
	}

	//չʾ��ͼ����
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