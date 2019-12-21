#include <iostream>
#include <ctime>
#include<vector>
using namespace std;

class LabyM
{
private:
	int laby[12][12];
	int visited[12][12];
	bool solved;
	int exitX;
	int exitY;
public:
	LabyM();
	void showLaby();
	void generate();
	void solve(int, int);
};

//��ʼ�����Թ�
LabyM::LabyM()
{
	for (int j = 0; j < 11; j++) for (int k = 0; k < 12; k++)laby[j][k] = 1;
	for (int j = 0; j < 11; j++) for (int k = 0; k < 12; k++)visited[j][k] = 0;
	solved = false;
}

void LabyM::showLaby()
{
	for (int j = 0; j < 11; j++)
	{
		for (int k = 0; k < 11; k++)
		{
			if (laby[j][k] == 1)cout << "��";
			else if (laby[j][k] == 5)cout << "��";
			else cout << "  ";
		}
		cout << endl;
	}
}

void LabyM::generate()
{
	srand((unsigned)time(0));
	//����Χ����Ϊ·��������Ч�ı�������һ��ǽ�壬����ֹ�ڳ���
	for (int i = 0; i < 12; i++) 
	{
		laby[i][0] = 0;
		laby[0][i] = 0;
		laby[11][i] = 0;
		laby[i][11] = 0;
	}

	//ǽ����
	vector<int> X;
	vector<int> Y;

	//��ʼλ��
	X.push_back(2);
	Y.push_back(2);

	//��ǽ����Ϊ��ʱ����ѭ��
	while (X.size()) 
	{
		//��ǽ���������ȡһ��
		int r = rand() % X.size();
		int x = X[r];
		int y = Y[r];

		//�ж����������ĸ������Ƿ�Ϊ·
		int count = 0;
		for (int i = x - 1; i < x + 2; i++) 
		{
			for (int j = y - 1; j < y + 2; j++) 
			{
				if (abs(x - i) + abs(y - j) == 1 && laby[i][j] == 0) {
					++count;
				}
			}
		}

		//��������·��ֻ��һ��������·
		if (count <= 1) 
		{
			//��ȥ��һ��
			laby[x][y] = 0;
			//��ǽ�����в����µ�ǽ
			for (int i = x - 1; i < x + 2; i++) 
			{
				for (int j = y - 1; j < y + 2; j++) 
				{
					if (abs(x - i) + abs(y - j) == 1 && laby[i][j] == 1) 
					{
						X.push_back(i);
						Y.push_back(j);
					}
				}
			}
		}
		//ɾ����ǰǽ
		X.erase(X.begin() + r);
		Y.erase(Y.begin() + r);
	}

	//�����Թ�������
	laby[2][1] = 0;
	visited[2][2] = 1;
	for (int i = 9; i >= 0; i--) 
	{
		if (laby[i][9] == 0) 
		{
			laby[i][10] = 0;
			exitX = i;
			exitY = 10;
			break;
		}
	}

	//�����ʼ�Թ�
	showLaby();
}

void LabyM::solve(int x, int y)
{
	laby[2][1] = 5;
	//�����ǰ���ǳ���
	if (x == exitX && y == exitY)
	{
		visited[x][y] = 1;
		laby[x][y] = 5;
		solved = true;
		return;
	}
	//�����ǰ��ǳ���
	else
	{
		visited[x][y] = 1;
		laby[x][y] = 5;
		//Ѱ����Χ�Ƿ���·
		for (int i = x - 1; i < x + 2; i++)
		{
			for (int j = y - 1; j < y + 2; j++)
			{
				//�������������·��û�߹������Թ�δ��������ʸ�·
				if (abs(x - i) + abs(y - j) == 1 && laby[i][j] == 0 && visited[i][j] == 0 && !solved)
				{
					solve(i, j);
				}
			}
		}
		//�������ܱ����з�������Թ�δ���,�Ƴ���ǰ�ĵ�·�겢����
		if (!solved)
		{
			laby[x][y] = 0;
			return;
		}
		return;
	}
}

int main()
{
	LabyM lm;
	cout << "����Ψһ���Թ���8��8����" << endl;
	lm.generate();
	lm.solve(2, 2);
	cout << "���Ž⣨Ψһ�⣩��" << endl;
	lm.showLaby();
	return 0;
}