#include <functional>
#include <algorithm>
#include <iostream>
#include <string.h>
#include <iomanip>
#include <climits>
#include <cstdlib>
#include <sstream>
#include <cstdint>
#include <vector>
#include <string>
#include <bitset>
#include <cstdio>
#include <math.h>
#include <stack>
#include <queue>
#include <cmath>
#include <set>
#include <map>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ll> vl;
typedef vector<vl> vvl;
typedef vector<char> vc;
typedef vector<vc> vvc;

const ll MAXN = 100000LL;
const ll INF = 1000000007LL;
const double EPS = 1e-10;

/*
Будем называть цепочкой слов длины n последовательность слов w[1], w[2], …, w[n], такую, что для всех i от 1 до n – 1 слово w[i]
является собственным префиксом слова wi+1.

Слово u длины k называется собственным префиксом слова v длины l, если l > k и первые k букв слова v совпадают со словом u.
Например, «program» является собственным префиксом слова «programmer».

Задано множество слов S = {s[1], s[2], …, s[m]} и последовательность чисел x[1], x[2], …, x[k]. Требуется найти такие числа l и r (l ≤ r),
что s[x[l]], s[x[l + 1]], …, s[x[r – 1]], s[x[r]] является цепочкой слов, и количество слов в цепочке (число r – l + 1) максимально.
*/

ll pow(ll n, ll i)
{
  if (i == 1LL)
  {
    return n;
  }
  if (i % 2LL == 0LL)
  {
    ll h = pow(n, i / 2LL);
    return h * h;
  }
  else
  {
    return pow(n, i - 1LL) * n;
  }
}

const ll p = 31LL;

ll getHash(vl &h, ll L, ll R)
{
	long long result = h[R];
	if (L > 0LL) result -= h[L - 1LL];
	return result;
}

bool isPrefix(vl &a, vl &b)
{
	if ((ll)a.size() >= (ll)b.size()) { return false; }
	return a[(ll)a.size() - 1LL] == b[(ll)a.size() - 1LL];
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0); cout.tie(0); cerr.tie(0);
	vl pow(250001LL);
	pow[0LL] = 1LL;
	for (ll i = 1LL; i < 250001LL; i++)
	{
		pow[i] = pow[i - 1LL] * p;
	}
	ll n; cin >> n;
	vector<string> Strings(n);
	vvl Hashs(n);
	for (ll i = 0LL; i < n; i++)
	{
		cin >> Strings[i];
		Hashs[i].resize(Strings[i].size());
		Hashs[i][0LL] = (Strings[i][0LL] - 'a' + 1LL);
		for (ll j = 1LL; j < Strings[i].size(); j++)
		{
			Hashs[i][j] = Hashs[i][j - 1LL] + pow[j] * (Strings[i][j] - 'a' + 1LL);
		}
	}
	ll m; cin >> m;
	vector<ll> arr(m);
	for (ll &x : arr) { cin >> x; x--; }
	pair<ll, ll> Ans = { -1LL, -1LL }, Temp = {0LL, 0LL};
	for (ll i = 1LL; i < m; i++)
	{
		if (!isPrefix(Hashs[arr[Temp.second]], Hashs[arr[i]]))
		{
			Temp.first = i;
		}
		Temp.second = i;
		if (Ans.second - Ans.first < Temp.second - Temp.first) { Ans = Temp; }
	}
	if (Ans.first >= Ans.second)
	{
		cout << "1 1" << endl;
		return 0LL;
	}
	cout << Ans.first + 1LL << " " << Ans.second + 1LL << endl;
	return 0LL;
}
