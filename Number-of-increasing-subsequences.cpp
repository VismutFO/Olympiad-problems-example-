#include <unordered_map>
#include <unordered_set>
#include <type_traits>
#include <functional>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <utility>
#include <thread>
#include <vector>
#include <string>
#include <bitset>
#include <cstdio>
#include <math.h>
#include <stack>
#include <ctime>
#include <queue>
#include <cmath>
#include <list>
#include <set>
#include <map>

using namespace std;

#define SZ(v)			ll((v).size())
#define ALL(data)       data.begin(),data.end()
#define RALL(data)      data.rbegin(),data.rend()
#define TYPEMAX(type)   numeric_limits<type>::max()
#define TYPEMIN(type)   numeric_limits<type>::min()

typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> pll;
typedef vector<ll> vl;
typedef vector<vl> vvl;
typedef vector<char> vc;
typedef vector<vc> vvc;

const ll INF = 1000000007LL;
const double EPS = 1e-9;

/*
Задана последовательность из n чисел a1, a2, ..., an. Подпоследовательностью длины k этой последовательности называется
набор индексов i1, i2, ..., ik, удовлетворяющий неравенствам 1 ≤ i1 < i2 < ... < ik ≤ n. Подпоследовательность называется
возрастающей, если выполняются неравенства ai1 < ai2 < ... < aik.

Необходимо найти число возрастающих подпоследовательностей наибольшей длины заданной последовательности a1, ... ,an.
Так как это число может быть достаточно большим, необходимо найти остаток от его деления на 10^9 + 7.
*/

pair<long long, long long> combine(pair<long long, long long> a, pair<long long, long long> b)
{
	if (a.first > b.first)
	{
		return a;
	}
	if (b.first > a.first)
	{
		return b;
	}
	pair<long long, long long> ans;
	ans.first = a.first;
	ans.second = (a.second + b.second) % INF;
	return ans;
}

ll sizet = 1LL;
struct Tree
{
	vector<pll> tree;
	Tree(vl& v, vl& count)
	{
		while (sizet < v.size()) { sizet <<= 1; }
		tree.resize(sizet * 2LL);
		for (ll i = sizet; i < sizet + v.size(); i++)
		{
			tree[i].first = v[i - sizet];
			tree[i].second = count[i - sizet] % INF;
		}
		for (ll i = sizet - 1LL; i > 0LL; i--)
		{
			tree[i] = combine(tree[i * 2LL], tree[i * 2LL + 1LL]);
		}
	}
	Tree(vl& v)
	{
		while (sizet < v.size()) { sizet <<= 1; }
		tree.resize(sizet * 2LL);
		for (ll i = sizet; i < sizet + v.size(); i++)
		{
			tree[i].first = v[i - sizet];
			tree[i].second = 0LL;
		}
		for (ll i = sizet - 1LL; i > 0LL; i--)
		{
			tree[i] = combine(tree[i * 2LL], tree[i * 2LL + 1LL]);
		}
	}
	pll sums(ll l, ll r, ll n = 1LL, ll tl = 0LL, ll tr = sizet)
	{
		if (tl >= r || tr <= l)
		{
			return { -INF - 1LL, -INF - 1LL };
		}
		if (tl >= l && tr <= r)
		{
			return tree[n];
		}
		ll mid = (tl + tr) / 2LL;
		return combine(sums(l, r, n * 2LL, tl, mid), sums(l, r, n * 2LL + 1LL, mid, tr));
	}
	void change(ll pos, pll x, ll n = 1LL, ll tl = 0LL, ll tr = sizet)
	{
		if (pos < tl || pos >= tr)
		{
			return;
		}
		if (tl + 1LL == tr)
		{
			tree[n] = combine(x, tree[n]);
			return;
		}
		ll mid = (tl + tr) / 2LL;
		change(pos, x, n * 2LL, tl, mid); change(pos, x, n * 2LL + 1LL, mid, tr);
		tree[n] = combine(tree[n * 2LL], tree[n * 2LL + 1LL]);
	}
};

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0); cout.tie(0); cerr.tie(0);
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	ll n; cin >> n;
	vector<pll> arr_zag(n);
	for (ll i = 0LL; i < n; i++)
	{
		cin >> arr_zag[i].first;
		arr_zag[i].second = i;
	}
	sort(arr_zag.begin(), arr_zag.end());
	vl arr(n);
	arr[arr_zag[0].second] = 0;
	ll i_n = 1;
	for (ll i = 1; i < n; i++)
	{
		if (arr_zag[i].first != arr_zag[i - 1].first)
		{
			arr[arr_zag[i].second] = i_n;
			i_n++;
		}
		else
		{
			arr[arr_zag[i].second] = arr[arr_zag[i - 1].second];
		}
	}
	vector<pll> d(n, { 1, 0 });
	vl t(i_n, 0);
	Tree root(t);
	map<ll, ll> my_map;
	for (ll i = 0; i < n; i++)
	{
		my_map[arr[i]]++;
		my_map[arr[i]] %= INF;
		if (arr[i] > 0)
		{
			d[i] = root.sums(0, arr[i]);
			d[i].first++;
			if (d[i].first == 1)
			{
				d[i].second = 1;
			}
			root.change(arr[i], d[i]);
		}
		else
		{
			d[i].first = 1;
			d[i].second = 1;
			root.change(arr[i], d[i]);
		}
	}
	pll pair_ans = { -INF - 1, -INF - 1 };
	for (ll i = 0LL; i < n; i++)
	{
		pair_ans = combine(pair_ans, d[i]);
	}
	cout << pair_ans.second % INF << endl;
	return 0;
}
