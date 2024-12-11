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

using namespace std;
using ll = long long;

struct pair_hash {
    template <class T1, class T2>
    std::size_t operator () (const std::pair<T1,T2> &p) const {
        auto h1 = std::hash<T1>{}(p.first) * 1000000009;
        auto h2 = std::hash<T2>{}(p.second);

        return h1 ^ h2;  
    }
};

unordered_map<pair<ll,ll>, ll, pair_hash> cache;
ll count(ll num, ll rem_dept) {
    if (rem_dept == 0) {
        return 1;
    }
    pair<ll,ll> key = {num, rem_dept};
    auto it = cache.find(key);
    if (it != cache.end()) {
        return it -> second;
    }

    ll res = 0;
    if (num == 0) {
        res += count(1, rem_dept -1);
    } else if (auto s =  to_string(num); s.size() % 2 == 0) {
        ll x1 = 0, x2 = 0;
        for(int idx = 0; idx < s.size()/2; ++ idx) {
            x1 *=10;
            x1 += s[idx] - '0';
        } 

        for(int idx = s.size() / 2; idx < s.size(); ++ idx) {
            x2 *=10;
            x2 += s[idx] - '0';
        } 
        res += count(x1, rem_dept - 1);
        res += count(x2, rem_dept - 1);
        
        
    } else {
        if (num > (INT64_MAX) / 2024) {
            cerr << "Problem" << endl;
        }
        res += count(num * 2024, rem_dept - 1);
    }
    cache[key] = res;
    return res;

}

int main(int argc, const char **argv)
{
    constexpr ll magic_mod = 1e9 + 7;
    if (argc >= 3 && argv[1] == string("<"))
    {
        freopen(argv[2], "r", stdin);
    }

    int s;
    vector<int> v1;
    while(cin >> s) {
        v1.push_back(s);
    }

    constexpr int depth = 75;
    ll res = 0;
    for(const auto& x : v1) {
        res += count(x, depth);
    }

    cout << res << endl;
    cout << cache.size() << endl;
}