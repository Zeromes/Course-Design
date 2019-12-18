#include <iostream>
#include <ctime>
using namespace std;

class LabyM
{
private:
	int laby[8][8];
	int show[9][9];
public:
	LabyM();
	void generate();
	void bestSolve();
	void allSolve();
};

LabyM::LabyM()
{
	for (int j = 0; j < 9; j++) for (int k = 0; k < 9; k++)show[j][k] = 0;
	for (int j = 0; j < 8; j++) for (int k = 0; k < 8; k++)laby[j][k] = 0;
	for (int i = 0; i < 9; i++)
	{
		show[0][i] = 1;
		show[i][0] = 1;
		show[8][i] = 1;
		show[i][8] = 1;
	}
	show[1][0] = 0;
	show[7][8] = 0;
}

void LabyM::generate()
{
	srand((unsigned)time(0));

	for (int j = 0; j < 9; j++)
	{
		for (int k = 0; k < 9; k++)
		{
			if (show[j][k] == 1)cout << "¡ö";
			else cout << "  ";
		}
		cout << endl;
	}
}

void LabyM::bestSolve()
{

}

void LabyM::allSolve()
{

}

int main()
{
	LabyM LM;
	LM.generate();
	return 0;
}