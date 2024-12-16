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

static ll mx = 0, my = 0;

class Vec2d
{
public:
    ll x, y;
    constexpr Vec2d(ll x, ll y) : x(x), y(y) {}
    Vec2d invers() const { return {-x, -y}; }
    bool operator<(const Vec2d& d) const {
        return x < d.x || x == d.x && y < d.y;
    }
    bool operator==(const Vec2d& d) const {
        return x == d.x && y == d.y;
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
    Coords(ll x, ll y) : x(x), y(y) {}
    bool is_valid() const { return x >= 0 && x < mx && y >= 0 && y < my; }
    Coords operator+(const Vec2d &v) const { return {x + v.x, y + v.y}; }
    Coords operator-(const Vec2d &v) const { return {x - v.x, y - v.y}; }

    bool operator<(const Coords &o) const
    {
        return x < o.x || x == o.x && y < o.y;
    }
    Vec2d operator-(const Coords &o)
    {
        return {x - o.x, y - o.y};
    }

    bool operator==(const Coords& o) const {
        return x == o.x && y == o.y;
    }

    std::string to_string() const {
        return std::to_string(x) + " " + std::to_string(y);
    }

    ll x, y;
};

// ---- Problem specific code ----


vector<string> fields;
Coords fpos = {0,0};

int main(int argc, const char **argv)
{
    constexpr ll magic_mod = 1e9 + 7;

    if (argc >= 3 && argv[1] == string("<"))
    {
        freopen(argv[2], "r", stdin);
    }

    string s;
    while(cin >> s) {
        fields.push_back(s);
    }

    mx = fields.size();
    my = fields[0].size();

    Coords sp = {0,0};
    
    for(int x = 0; x < mx; ++x) {
        for(int y = 0; y < my; ++y) {
            if (fields[x][y]=='E') {
                ::fpos = {x,y};
            }
            if (fields[x][y]=='S') {
                sp = {x,y};
            }
        }
    }

    Vec2d sd = Vec2d(0,1);
    ll start_score = 0;
    priority_queue<tuple<ll, Coords, Vec2d> > pq;

    pq.push({-start_score, sp, sd});

    bool good = false;
    ll good_score = 1e15;

    map<pair<Coords, Vec2d>, ll> cache;
    cache[{sp, sd}] = start_score;

    auto test = [&](ll score, Coords p, Vec2d d) {
        if (fields[p.x][p.y]=='#') {
            return;
        }
        if (p == ::fpos) {
            good_score = min(good_score, score);
        }
        if (cache.count({p,d}) == 0 || cache[{p,d}] > score) {
            cache[{p,d}] = score;
            pq.push({-score, p, d});
        }
    };

    while(pq.size()) {
        auto [s, p, d] = pq.top();
        s *= -1;
        pq.pop();

        test(s + 1, p + d, d);
        for (auto d2 : all_dirs) {
            if (abs(d2.x) == abs(d.x)) {
                continue;
            }
            test(s + 1000, p, d2);
        }
    } 

    set<pair<Coords, Vec2d> > res;
    deque< pair<Coords, Vec2d> > res_new;
    for(auto d : all_dirs) {
        auto it = cache.find({::fpos, d}); 
        if (it != cache.end() && it->second == good_score) {
            res_new.push_back({::fpos, d});
            res.insert({::fpos, d});
        }
    }

    
    while(res_new.size()) {
        auto [p,d] = res_new.front(); res_new.pop_front();
        auto s = cache[{p,d}];
        {
            Coords pp = p + d.invers();
            pair<Coords, Vec2d> key = {pp,d};
            if (cache.count(key) && cache[key] == s -1) {
                if (res.count(key) == 0) {
                    res.insert(key);
                    res_new.push_back(key);
                }
            }
        }
        for(auto d2 : all_dirs) {
            if (abs(d.x) == abs(d2.x))
                continue;
            
            pair<Coords, Vec2d> key = {p,d2};
            if (cache.count(key) && cache[key] == s -1000) {
                if (res.count(key) == 0) {
                    res.insert(key);
                    res_new.push_back(key);
                }
            }
        }

    }
    set<Coords> res2;
    for(auto [p,d] : res) {
        res2.insert(p);
    }

    cout << res2.size() << endl;

}