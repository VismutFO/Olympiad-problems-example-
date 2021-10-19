#include<iostream>
#include<set>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>
#include<map>
#include<stack>
#include <cstdlib>

using namespace std;
typedef long long ll;
const ll INF = 1000 * 1000 * 1000 + 7;

/*
Перед возвращением в штаб-квартиру корпорации Аазу и Скиву пришлось заполнить на местной таможне декларацию о доходах за время визита.
Получилась довольно внушительная последовательность чисел. Обработка этой последовательности заняла весьма долгое время.

— Своппер кривой, — со знанием дела сказал таможенник.

— А что такое своппер? — спросил любопытный Скив.

Ааз объяснил, что своппер — это структура данных, которая умеет делать следующее.

Взять отрезок чётной длины от x до y и поменять местами число x с x+1, x+2 с x+3, и т.д.
Посчитать сумму чисел на произвольном отрезке от a до b.
Учитывая, что обсчёт может затянуться надолго, корпорация «МИФ» попросила Вас решить проблему со своппером и промоделировать ЭТО эффективно.
*/

struct Node
{
	ll size;
	ll value;
	ll y;
	ll sum;
	Node *l, *r;
	Node() { }
	Node(ll value) : y(rand() * rand()),
	value(value), sum(value), l(nullptr), r(nullptr) { }
};

typedef Node* pNode;
pNode T1, T2;

ll get_size(pNode t)
{
	return (t ? t->size : 0);
}

ll get_sum(pNode t)
{
	return (t ? t->sum : 0);
}

void update(pNode t)
{
	if (t)
	{
		t->size = 1 + get_size(t->l) + get_size(t->r);
		t->sum = t->value + get_sum(t->l) + get_sum(t->r);
	}
}

void merge(pNode l, pNode r, pNode &t)
{
	if (!l || !r)
	{
		t = l ? l : r;
	}
	else if (l->y > r->y)
	{
		merge(l->r, r, l->r);
		t = l;
	}
	else
	{
		merge(l, r->l, r->l);
		t = r;
	}
	update(t);
}

void split(pNode t, pNode &l, pNode &r, ll pos)
{
	if (!t)
	{
		l = r = nullptr;
	}
	else if (pos <= get_size(t->l))
	{
		split(t->l, l, t->l, pos);
		r = t;
	}
	else
	{
		split(t->r, t->r, r, pos - 1 - get_size(t->l));
		l = t;
	}
	update(t);
}

ll get_sum(ll l, ll r)
{
	if (l > r)
	{
		return 0LL;
	}
	ll l1 = (l + 1) / 2, r1 = r / 2;
	ll l2 = l / 2, r2 = (r + 1) / 2 - 1;
	pNode a1, b1, c1, a2, b2, c2;
	split(T1, a1, b1, l1);
	split(b1, b1, c1, r1 - l1 + 1);
	split(T2, a2, b2, l2);
	split(b2, b2, c2, r2 - l2 + 1);
	ll res = get_sum(b1) + get_sum(b2);
	merge(a1, b1, b1); merge(b1, c1, T1);
	merge(a2, b2, b2); merge(b2, c2, T2);
	return res;
}

void tree_swap(ll l, ll r)
{
	ll l1 = (l + 1) / 2, r1 = r / 2;
	ll l2 = l / 2, r2 = (r + 1) / 2 - 1;
	pNode a1, b1, c1, a2, b2, c2;

	split(T1, a1, b1, l1);
	split(b1, b1, c1, r1 - l1 + 1);
	split(T2, a2, b2, l2);
	split(b2, b2, c2, r2 - l2 + 1);

	merge(a1, b2, b2);
	merge(b2, c1, T1);
	merge(a2, b1, b1);
	merge(b1, c2, T2);
}

int main()
{
	ll n, m, cs = 1;
	while (cin >> n >> m && n + m)
	{
		T1 = T2 = nullptr;
		if (cs != 1) { cout << endl; }
		cout << "Swapper " << cs++ << ":" << endl;
		for (ll i = 1; i <= n; i++)
		{
			int val;
			cin >> val;
			if (i % 2 != 0) { merge(T1, new Node(val), T1); }
			else { merge(T2, new Node(val), T2); }
		}
		for (ll i = 0; i < m; i++)
		{
			ll type, a, b;
			cin >> type >> a >> b; a--; b--;
			if (type == 1)
			{
				tree_swap(a, b);
			}
			else
			{
				cout << get_sum(a, b) << endl;
			}
		}
	}
	return 0;
}
