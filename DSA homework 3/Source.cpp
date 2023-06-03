#include <iostream>
#include<queue>
#include<vector>
#include<algorithm>
#include<stack>

using namespace std;


// the distance between start and end shouldn't be more than 15


struct QNode
{
	int x;
	int y;
	int dist;

	QNode()
	{
	}

	QNode(int x, int y, int distance)
	{
		this->x = x;
		this->y = y;
		this->dist = distance;
	}
};

struct Prev
{
	int x;
	int y;

	Prev()
	{

	}

	Prev(int x, int y)
	{
		this->x = x;
		this->y = y;
	}
};

void fill_M(char(&M)[20][40], int length, int height)
{
	for (size_t i = 0; i < height; i++)
	{
		for (size_t j = 0; j < length; j++)
		{
			M[i][j] = '-';
		}
	}
	int a = 10;
	for (size_t i = 0; i < height; i++)
	{
		if (i <= 10)
		{
			M[i][a] = '0';
		}
		else
		{
			M[i][a + 3] = '0';
		}

	}
}

void fill_bool(bool(&visited)[20][40], int length, int height)
{
	for (size_t i = 0; i < height; i++)
	{
		for (size_t j = 0; j < length; j++)
		{
			visited[i][j] = false;
		}
	}
}

void shortestpath(char M[20][40], int Startx, int Starty,
	queue<QNode>& qNodes,
	Prev(&d)[20][40], Prev(&p)[20][40])
{
	if (M[Starty][Startx] == 'E')
	{
		return;
		
	}
	int moveX[] = { 0,0,1,-1 };
	int moveY[] = { 1,-1,0,0 };
	bool visited[20][40];
	fill_bool(visited, 40, 20);
	qNodes.emplace(Startx, Starty, 0);
	QNode start(Startx, Starty, 0);
	d[Starty][Startx].x = Startx;
	d[Starty][Startx].y = Starty;
	p[Starty][Startx].x = -1;
	p[Starty][Startx].y = -1;
	while (!qNodes.empty())
	{
		QNode currNode = qNodes.front();
		qNodes.pop();
		int currX = currNode.x;
		int currY = currNode.y;
		int currDistance = currNode.dist;
		visited[currY][currX] = true;
		if (M[currY][currX] == 'E')
		{
			break;
			
		}

		for (size_t i = 0; i < 4; i++)
		{
			int newX = currX + moveX[i];
			int newY = currY + moveY[i];

			if (newX >= 0 && newX < 40 &&
				newY >= 0 && newY < 20 &&
				visited[newY][newX] == false &&
				M[newY][newX] != '0')
			{
				qNodes.emplace(newX, newY, currDistance + 1);
				d[newY][newX].x = newX;
				d[newY][newX].y = newY;
				p[newY][newX].x = currX;
				p[newY][newX].y = currY;
			}
		}
	}
	return;
	
}


void print(char(&M)[20][40], int length, int height, stack<Prev>& places, Prev& help)
{
	for (size_t i = 0; i < height; i++)
	{
		for (size_t j = 0; j < length; j++)
		{
			cout << M[i][j];
		}
		cout << endl;
	}
	Prev temp = places.top();
	places.pop();
	M[help.y][help.x] = '-';
	M[temp.y][temp.x] = '*';
	help = temp;
}

using namespace std;
int main() {

	char M[20][40];
	fill_M(M, 40, 20);

	int x2;
	int y2;
	cout << "Start position x: ";
	cin >> x2;
	cout << "Start position y: ";
	cin >> y2;
	cin.ignore();

	M[y2][x2] = 'S';

	int x1;
	int y1;
	cout << "end position x: ";
	cin >> x1;
	cout << "end position y: ";
	cin >> y1;
	cin.ignore();

	M[y1][x1] = 'E';

	system("CLS");

	queue<QNode> qNodes;

	Prev d[20][40];
	Prev p[20][40];

	
	shortestpath(M, x2, y2, qNodes, d, p);

	stack<Prev> places;

	while (p[y1][x1].x != -1 && p[y1][x1].y != -1) {
		
		places.emplace(x1, y1);
		int x3 = p[y1][x1].x;
		int y3 = p[y1][x1].y;
		x1 = x3;
		y1 = y3;
	}

	Prev help(places.top());
	while (!places.empty())
	{
		print(M, 40, 20, places, help);
		cout << endl;
		;
	}

	

	return 0;
}
