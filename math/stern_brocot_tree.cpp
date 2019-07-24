#include <iostream>
#include <algorithm>
using namespace std;

using ll = long long;

const ll T9 = 1000000000;
pair<ll, ll> calcAns(ll a, ll b = T9 * T9) {
    ll p1 = 0, p2 = 1;
    ll q1 = 1, q2 = 0;
    while (b != 0) {
        ll t = a / b;
        p1 += t * p2;
        q1 += t * q2;
        a -= t * b;
        if (q1 > T9) break;
        swap(p1, p2);
        swap(q1, q2);
        swap(a, b);
    }
    return {p2, q2};
}
int main() {
    int q;
    cin >> q;
    while (q--) {
        ll x = 0;
        char c;
        cin >> c >> c >> x;
        auto res = calcAns(x);
        cout << res.first << ' ' << res.second << endl;
    }
    return 0;
}