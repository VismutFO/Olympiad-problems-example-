#include<iostream>
#include<set>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>
#include<map>
#include<stack>
#include <set>

using namespace std;

const long long INF = 1000 * 1000 * 1000 + 7;
#define MINF -2000000000

/*
Реализуйте структуру данных, которая поддерживает множество S целых чисел, с котором разрешается производить следующие операции:

add(i) — добавить в множество S число i (если он там уже есть, то множество не меняется);
next(i) — вывести минимальный элемент множества, не меньший i. Если искомый элемент в структуре отсутствует, необходимо вывести -1.
*/

int y = MINF;

struct Node
{
	int key, prior;
	Node *l, *r;
	Node() { }
	Node(int key, int prior) : key(key), prior(prior), l(nullptr), r(nullptr) { }
};

typedef Node* pNode;

pNode root = nullptr;

void split(pNode t, int key, pNode &l, pNode &r)
{
	if (!t)
	{
		l = r = nullptr;
		return;
	}
	else if (key <= t->key)
	{
		split(t->l, key, l, t->l), r = t;
	}
	else
	{
		split(t->r, key, t->r, r), l = t;
	}
}

void merge(pNode l, pNode r, pNode &t)
{
	if (!l || !r)
	{
		t = l ? l : r;
	}
	else if (l->prior > r->prior)
	{
		merge(l->r, r, l->r), t = l;
	}
	else
	{
		merge(l, r->l, r->l), t = r;
	}
}

int GetMin(pNode t)
{
	if (t == nullptr) return -1;
	if (t->l == nullptr) return t->key;
	return GetMin(t->l);
}

void add(int i)
{
	pNode L, R;
	split(root, i, L, R);

	if (GetMin(R) != i)
	{
		merge(L, new Node(i, rand()), root);
		merge(root, R, root);
	}

	else { merge(L, R, root); }
}

void next(int i)
{
	pNode L, R;
	split(root, i, L, R);
	y = GetMin(R);
	printf("%d\n", y);
	merge(L, R, root);
}



int main()
{
	int n;
	cin >> n;
	for(int in = 0; in < n; in++)
	{
		char c;
		int i;
		cin >> c >> i;
		if (c == '+')
		{
			if (y > MINF) { i = (i + y) % 1000000000, y = MINF; }
			add(i);
		}
		else next(i);
	}
	return 0;
}
