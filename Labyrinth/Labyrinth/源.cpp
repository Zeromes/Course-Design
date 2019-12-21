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

//初始化空迷宫
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
			if (laby[j][k] == 1)cout << "■";
			else if (laby[j][k] == 5)cout << "☆";
			else cout << "  ";
		}
		cout << endl;
	}
}

void LabyM::generate()
{
	srand((unsigned)time(0));
	//最外围设置为路，可以有效的保护里面一层墙体，并防止挖出界
	for (int i = 0; i < 12; i++) 
	{
		laby[i][0] = 0;
		laby[0][i] = 0;
		laby[11][i] = 0;
		laby[i][11] = 0;
	}

	//墙队列
	vector<int> X;
	vector<int> Y;

	//初始位置
	X.push_back(2);
	Y.push_back(2);

	//当墙队列为空时结束循环
	while (X.size()) 
	{
		//在墙队列中随机取一点
		int r = rand() % X.size();
		int x = X[r];
		int y = Y[r];

		//判读上下左右四个方向是否为路
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

		//若四周无路或只有一个方向有路
		if (count <= 1) 
		{
			//挖去这一块
			laby[x][y] = 0;
			//在墙队列中插入新的墙
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
		//删除当前墙
		X.erase(X.begin() + r);
		Y.erase(Y.begin() + r);
	}

	//设置迷宫进出口
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

	//输出初始迷宫
	showLaby();
}

void LabyM::solve(int x, int y)
{
	laby[2][1] = 5;
	//如果当前点是出口
	if (x == exitX && y == exitY)
	{
		visited[x][y] = 1;
		laby[x][y] = 5;
		solved = true;
		return;
	}
	//如果当前点非出口
	else
	{
		visited[x][y] = 1;
		laby[x][y] = 5;
		//寻找周围是否有路
		for (int i = x - 1; i < x + 2; i++)
		{
			for (int j = y - 1; j < y + 2; j++)
			{
				//如果上下左右有路且没走过，且迷宫未解决，访问该路
				if (abs(x - i) + abs(y - j) == 1 && laby[i][j] == 0 && visited[i][j] == 0 && !solved)
				{
					solve(i, j);
				}
			}
		}
		//访问完周边所有方块后，若迷宫未解决,移除当前的的路标并返回
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
	cout << "生成唯一解迷宫（8×8）：" << endl;
	lm.generate();
	lm.solve(2, 2);
	cout << "最优解（唯一解）：" << endl;
	lm.showLaby();
	return 0;
}