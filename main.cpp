#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <tuple>
#include <string>
#include <algorithm>
#include <ranges>

using namespace std;

using ll = long long;
using vb = vector<bool>;
using vvb = vector<vb>;
using vi = vector<int>;
using vvi = vector<vi>;
using vl = vector<ll>;
using vvl = vector<vl>;
using pii = pair<int, int>;
using vii = vector<pii>;
using pll = pair<ll, ll>;
using vll = vector<pll>;

int n, m;
vvi f;
int ans;

const auto dx = vi{ -1,1,0,0 };
const auto dy = vi{ 0,0,-1,1 };

bool checkCheese() {
	for (const auto& row : f) {
		for (const auto& x : row) {
			if (1 == x) {
				return true;
			}
		}
	}

	return false;
}

void findOutter(vvi& g) {
	auto st = stack<pii>{};
	st.push({ 0, 0 });

	while (!st.empty()) {
		const auto [y, x] = move(st.top());
		st.pop();

		g[y][x] = 1;

		for (auto d = 0; d < 4; ++d) {
			const auto nx = x + dx[d];
			const auto ny = y + dy[d];

			if (nx < 0 || m <= nx ||
				ny < 0 || n <= ny) {
				continue;
			}

			if (1 == g[ny][nx]) {
				continue;
			}

			if (0 == f[ny][nx]) {
				st.push({ ny, nx });
			}
		}
	}
}

void checkRemoved(vvi& g, vvb& isVisited, const vvi& outter, const int i, const int j) {
	auto st = stack<pii>{};

	st.push({ i, j });
	while (!st.empty()) {
		const auto [y, x] = move(st.top());
		st.pop();

		isVisited[y][x] = true;

		auto wct = int{ 0 };
		for (auto d = 0; d < 4; ++d) {
			const auto nx = x + dx[d];
			const auto ny = y + dy[d];

			if (nx < 0 || m <= nx ||
				ny < 0 || n <= ny) {
				continue;
			}

			if (isVisited[ny][nx]) {
				continue;
			}

			if (1 == outter[ny][nx]) {
				++wct;
			}

			if (1 == f[ny][nx]) {
				st.push({ ny, nx });
			}
		}

		if (2 <= wct) {
			g[y][x] = 0;
		}
	}
}

void removeCheese() {
	auto outter = vvi(n, vi(m, 0));

	findOutter(outter);

	auto cpy = vvi{ f };
	auto isVisited = vvb(n, vb(m, false));
	for (const auto& i : ranges::iota_view{ 0, n }) {
		for (const auto& j : ranges::iota_view{ 0, m }) {
			if (0 == f[i][j]) {
				continue;
			}

			if (isVisited[i][j]) {
				continue;
			}

			checkRemoved(cpy, isVisited, outter, i, j);
		}
	}

	f = vvi{ cpy };
}

void solve() {
	ans = 0;

	while (checkCheese()) {
		removeCheese();
		++ans;
	}
}

int main() {
	ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	cin >> n >> m;
	f = vvi(n, vi(m));
	for (auto&& row : f) {
		for (auto&& x : row) {
			cin >> x;
		}
	}

	solve();
	cout << ans;

	return 0;
}