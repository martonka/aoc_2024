
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <queue>
#include <tuple>
#include <numeric>
#include <unordered_set>
#include <set>
#include <array>

using namespace std;
using ll = long long;

static int mx = 0, my = 0;

class Vec2d
{
public:
    int x, y;
    constexpr Vec2d(int x, int y) : x(x), y(y) {}
};

constexpr std::array<Vec2d, 8> all_dirs = {
    Vec2d{-1, -1},
    Vec2d{-1, 0},
    Vec2d{-1, 1},
    Vec2d{0, -1},
    Vec2d{0, 1},
    Vec2d{1, -1},
    Vec2d{1, 0},
    Vec2d{1, 1},
};

class Coords
{
public:
    Coords(int x, int y) : x(x), y(y) {}
    bool is_valid() const { return x >= 0 && x < mx && y >= 0 && y < my; }
     Coords operator+(const Vec2d &v) const { return {x + v.x, y + v.y}; }

    // bool operator<(const Coords& o) const {
    //     return q < o.q || q == o.q && r < o.r;
    // }

    // bool operator!=(const Coords& o) const {
    //     return q != o.q || r != o.r;
    // }
    // std::string to_string() const {
    //     return std::to_string(q) + " " + std::to_string(r);
    // }

    // struct HashFunction
    // {
    //     size_t operator()(const Coords& point) const
    //     {
    //         return std::hash<int>()(point.q * 1000000009 + point.r);
    //     }
    // };

    // int distanceFrom(const Coords& o) const {
    //     int qd = q - o.q;
    //     int rd = r - o.r;
    //     return std::max(std::abs(qd), std::max(std::abs(rd), std::abs(qd + rd)));
    // }

    int x, y;
    // friend inline std::ostream& operator<<(std::ostream& oss, const Coords& c);
};

int count(const vector<string> &tb, Coords c, int d, Vec2d dir)
{
    if (!c.is_valid())
        return 0;
    char ch = '.';
    if (d == 0)
    {
        ch = 'X';
    }

    if (d == 1)
    {
        ch = 'M';
    }
    if (d == 2)
    {
        ch = 'A';
    }
    if (d == 3)
    {
        ch = 'S';
    }

    if (tb[c.x][c.y] != ch)
    {
        return 0;
    }
    else
    {
        if (d == 3)
            return 1;
        int r2 = 0;
            r2 += count(tb, c + dir, d +1, dir);
        return r2;
    }

}

int main(int argc, const char **argv)
{
    constexpr ll magic_mod = 1e9 + 7;
    if (argc >= 3 && argv[1] == string("<"))
    {
        freopen(argv[2], "r", stdin);
    }
    vector<string> tb;
    string s;
    while ((cin >> s) && s.size())
    {
        tb.push_back(s);
    }
    mx = tb.size();
    my = tb[0].size();

    int res = 0;

    for (int x = 0; x < mx; ++x)
    {
        for (int y = 0; y < mx; ++y)
        {
            
        for (const auto dir : all_dirs)
            res += count(tb, {x, y}, 0, dir);
        }
    }

    cout << res << endl;
}