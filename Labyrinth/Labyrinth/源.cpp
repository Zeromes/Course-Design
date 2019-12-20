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
	for (int k = 1; k < 8; k++)						//���ɵ�һ��
	{
		if (rand() % 100 < 50)
		{
			laby[0][k] = 1;
			k++;
		}
	}
	//������ǩ
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
	//������ǩ����

	//�������������������)
	for (int j = 1; j < 6; j++)
	{
		//����һ��
		if (j % 2 == 0)
		{
			for (int k = 0; k < 8; k++)//���ǽ
			{
				if (rand() % 100 < 50)
				{
					laby[j][k] = 1;
				}
			}
			l = 0;
			xunzhao:
			for (int t = l; t < 8; t++)//�������Ѱ���ҽ�
			{
				if (laby[j][t] == 1)
				{
					r = t - 1;
					break;
				}
			}
			if (l <= r)//�������ҽ�֮����ڿռ�
			{
				int d;
				bool found = false;
				for (int t = l; t <= r; t++)//�ұ�ʶ
				{
					if (laby[j - 1][t] == 0)
					{
						d = bs[t].index;
						found = true;
						break;
					}
				}
				if (found)//����ҵ���ʶ
				{
					for (int t = l; t <= r; t++)
					{
						bs[t].right = r;
						bs[t].left = l;
						bs[t].index = d;
					}
				}
				else//���û�ҵ���ʶ
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
		//����һ��
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
	//�������
	for (int k = 0; k < 8; k++)laby[6][k] = laby[5][k];
	

	for (int j = 1; j < 9; j++)						//�����ɵ��Թ���ֵ��show����
	{
		for (int k = 1; k < 9; k++)
		{
			show[j][k] = laby[j - 1][k - 1];
		}
	}
	for (int j = 0; j < 10; j++)						//�����ʼ�Թ�
	{
		for (int k = 0; k < 10; k++)
		{
			if (show[j][k] == 1)cout << "��";
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