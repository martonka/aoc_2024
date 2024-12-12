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
#include <unordered_map>
#include <set>
#include <array>
#include <deque>

using namespace std;
using ll = long long;

static int mx = 0, my = 0;

class Vec2d
{
public:
    int x, y;
    constexpr Vec2d(int x, int y) : x(x), y(y) {}
    Vec2d invers() const { return {-x, -y}; }
    bool operator<(const Vec2d& d) const {
        return x < d.x || x == d.x && y < d.y;
    }
};

constexpr std::array<Vec2d, 4> all_dirs = {
    Vec2d{-1, 0},
    Vec2d{0, 1},
    Vec2d{1, 0},
    Vec2d{0, -1},
};

class Coords
{
public:
    Coords(int x, int y) : x(x), y(y) {}
    bool is_valid() const { return x >= 0 && x < mx && y >= 0 && y < my; }
    Coords operator+(const Vec2d &v) const { return {x + v.x, y + v.y}; }

    bool operator<(const Coords &o) const
    {
        return x < o.x || x == o.x && y < o.y;
    }
    Vec2d operator-(const Coords &o)
    {
        return {x - o.x, y - o.y};
    }

    std::string to_string() const {
        return std::to_string(x) + " " + std::to_string(y);
    }

    int x, y;
};

// ---- Problem specific code ----

vector<set<Coords> > get_areas(const vector<string>& fields) {
    vector<set<Coords>> areas;
    set<Coords> processed;
    for (int x = 0; x < mx; ++x)
    {
        for (int y = 0; y < my; ++y)
        {
            Coords p = {x, y};
            if (processed.count(p))
            {
                continue;
            }

            char t = fields[x][y];

            set<Coords> current;
            deque<Coords> hot;

            // Simple BFS
            current.insert(p);
            hot.push_back(p);
            while (hot.size())
            {
                auto p1 = hot.front();
                hot.pop_front();
                for (auto x : all_dirs)
                {
                    auto p2 = p1 + x;

                    if (p2.is_valid() && current.count(p2) == 0 && fields[p2.x][p2.y] == t)
                    {
                        current.insert(p2);
                        hot.push_back(p2);
                    }
                }
            }
            areas.push_back(current);
            processed.insert(current.begin(), current.end());
        }
    }
    return areas;
}

int sides(const set<Coords>& area) {
    int res = 0;
    for(const auto& p : area) {
        for(const auto& d : all_dirs) {
            if (area.count(p + d) == 0) {
                ++res;
            }
        }
    }
    return res;
}

ll sides_cont(const set<Coords> &area)
{
    map< pair<Vec2d, ll>, set<ll> > eq;
    ll res = 0;

    // For each grid line store the positions, where we have a side 
    for (auto f : area) {
        for(auto d : all_dirs) {
            if (area.count(f + d) == 0) {
                int line_idx = f.x;
                int pos_on_line = f.y;
                if (d.x == 0) {
                    swap(line_idx, pos_on_line);
                }
                eq[{d, line_idx}].insert(pos_on_line);
            }
        }
    }
    for(const auto& [k,line] : eq) {

        ll last = -4;
        for(const auto& x : line) {
            if (last + 1 != x) { // Count only if it starts right now
                ++res;
            }
            last = x;
        }
    }

    return res;
}

int main(int argc, const char **argv)
{
    // 6382582218784
    constexpr ll magic_mod = 1e9 + 7;

    if (argc >= 3 && argv[1] == string("<"))
    {
        freopen(argv[2], "r", stdin);
    }

    string s;
    vector<string> fields;
    while (cin >> s)
    {
        fields.push_back(s);
    }
    mx = fields.size();
    my = fields[0].size();

    auto areas = get_areas(fields);

    ll res1 = 0;
    ll res2 = 0;

    for(const auto& a : areas) {
        res1 += a.size() * sides(a);
        res2 += a.size() * sides_cont(a);
    }

    cout << " Res 1&2:" << endl;
    cout << res1 << endl;
    cout << res2 << endl;
}