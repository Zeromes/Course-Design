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

struct block
{
	int left;
	int right;
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
	block b[8];
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
			for (int t = l; t <= r; t++)b[t].right = r;
			b[i].index = -1;
			b[i].left = -1;
			b[i].right = -1; 
			l = i + 1;
			r = i + 1;
			idx++;
		}
		else
		{
			b[i].left = l;
			b[i].index = idx;
			r = i;
		}
	}
	for (int t = l; t <= r; t++)b[t].right = r;
	//创建标签结束

	//生成其他（除最后两行)
	for (int j = 1; j < 6; j++)
	{
		//插入一个
		if (j % 2 == 0)
		{

		}
		//擦除一个
		else
		{
			bool done = false;
			for (int k = 0; k < 8; k++)
			{
				if (b[k].index != -1)
				{
					if (rand() % 100 < 50)
					{
						if (done)done = false;
						else
						{
							laby[j][k] = 0;
							done = true;
						}
					}
				}
				else
				{
					bool has = false;
					for (int t = b[k - 1].left; t <= b[k - 1].right; t++)
					{
						if (laby[j][t] == 0)has = true;
						break;
					}
					if (!has)laby[j][k - 1] = 0;
				}
			}
		}
	}

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