#include <iostream>
#include <ctime>
using namespace std;

class LabyM
{
private:
	int laby[8][8];
	int show[10][10];
public:
	LabyM();
	void generate();
	void solve();
};

struct blocks
{
	int left;
	int right;
	int index;
};

struct blockm
{
	int index;
};

LabyM::LabyM()
{
	for (int j = 0; j < 10; j++) for (int k = 0; k < 10; k++)show[j][k] = 0;
	for (int j = 0; j < 8; j++) for (int k = 0; k < 8; k++)laby[j][k] = 1;
	for (int j = 0; j < 8; j += 2) for (int k = 0; k < 8; k++)laby[j][k] = 0;
	for (int k = 0; k < 8; k++)laby[6][k] = 1;
	for (int k = 0; k < 8; k++)laby[7][k] = 0;
	for (int i = 0; i < 9; i++)
	{
		show[0][i] = 1;
		show[i][0] = 1;
		show[9][i] = 1;
		show[i][9] = 1;
	}
	show[1][0] = 0;
	show[8][9] = 0;
}

void LabyM::generate()
{
	int idx = 1;
	blockm bm[8];
	blocks bs[8];
	int l = 0, r = 0;
	srand((unsigned)time(0));
	for (int k = 0; k < 8; k++)laby[0][k] = 0;
	for (int k = 1; k < 8; k++)						//生成第一行
	{
		if (rand() % 100 < 50)
		{
			laby[0][k] = 1;
			k++;
		}
	}
	//创建标签
	for (int i = 0; i < 8; i++)
	{
		if (laby[0][i] == 1)
		{
			for (int t = l; t <= r; t++)bs[t].right = r;
			bs[i].index = -1;
			bs[i].left = -1;
			bs[i].right = -1; 
			l = i + 1;
			r = i + 1;
			idx++;
		}
		else
		{
			bs[i].left = l;
			bs[i].index = idx;
			r = i;
		}
	}
	for (int t = l; t <= r; t++)bs[t].right = r;
	for (int t = 0; t < 8; t++)bm[t].index = -1;
	//创建标签结束

	//生成其他（除最后两行)
	for (int j = 1; j < 6; j++)
	{
		//插入一个
		if (j % 2 == 0)
		{
			for (int k = 0; k < 8; k++)//添加墙
			{
				if (rand() % 100 < 50)
				{
					laby[j][k] = 1;
				}
			}
			l = 0;
			xunzhao:
			for (int t = l; t < 8; t++)//根据左界寻找右界
			{
				if (laby[j][t] == 1)
				{
					r = t - 1;
					break;
				}
			}
			if (l <= r)//如果左界右界之间存在空间
			{
				int d;
				bool found = false;
				for (int t = l; t <= r; t++)//找标识
				{
					if (laby[j - 1][t] == 0)
					{
						d = bs[t].index;
						found = true;
						break;
					}
				}
				if (found)//如果找到标识
				{
					for (int t = l; t <= r; t++)
					{
						bs[t].right = r;
						bs[t].left = l;
						bs[t].index = d;
					}
				}
				else//如果没找到标识
				{
					idx++;
					for (int t = l; t <= r; t++)
					{
						bs[t].right = r;
						bs[t].left = l;
						bs[t].index = idx;
					}
				}
			}
			l = r + 2;
			if (l <= 7)goto xunzhao;
		}
		//擦除一个
		else
		{
			bool done = false;
			for (int k = 0; k < 8; k++)
			{
				if (bs[k].index != -1)
				{
					if (rand() % 100 < 50)
					{
						if (done)done = false;
						else
						{
							laby[j][k] = 0;
							bm[k].index = bs[k].index;
							done = true;
						}
					}
				}
				else
				{
					bool has = false;
					for (int t = bs[k - 1].left; t <= bs[k - 1].right; t++)
					{
						if (laby[j][t] == 0)has = true;
						break;
					}
					if (!has)laby[j][k - 1] = 0;
				}
			}
		}
	}
	//最后两行
	for (int k = 0; k < 8; k++)laby[6][k] = laby[5][k];
	

	for (int j = 1; j < 9; j++)						//将生成的迷宫赋值到show当中
	{
		for (int k = 1; k < 9; k++)
		{
			show[j][k] = laby[j - 1][k - 1];
		}
	}
	for (int j = 0; j < 10; j++)						//输出初始迷宫
	{
		for (int k = 0; k < 10; k++)
		{
			if (show[j][k] == 1)cout << "■";
			else cout << "  ";
		}
		cout << endl;
	}
}

void LabyM::solve()
{

}

int main()
{
	LabyM LM;
	LM.generate();
	return 0;
}