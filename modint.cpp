template<int MOD>
struct modint {
    int x;
    modint() { x = 0; }
    modint(int xx) {
        if(x = xx; x < 0 || x >= MOD) x %= MOD;
        if(x < 0) x += MOD;
    }
    modint(ll xx) { if(x = xx % MOD; x < 0) x += MOD; }
    #define op(A, B, C) modint &operator A(const modint &b) { C return *this; } friend modint operator B(modint a, const modint &b) { return a A b; }
    op(+=, +, x += b.x; if(x >= MOD) x %= MOD;)
    op(-=, -, x -= b.x; if(x < 0) x += MOD;)
    op(*=, *, x = (long long) x * b.x % MOD;)
    modint &operator/=(const modint &b) {
        int xx = 1, yy = 0, aa = MOD, bb = b.x;
        while(bb) swap(xx, yy -= xx * (aa / bb)), swap(bb, aa %= bb);
        if(xx % MOD == 0) swap(xx, yy);
        if(x = (long long) x * xx % MOD; x < 0 || x >= MOD) x %= MOD;
        if(x < 0) x += MOD;
        return *this;
    }
    friend modint operator/(modint a, const modint &b) { return a /= b; }
    friend modint pow(modint a, long long n) {
        if(n < 0) return pow(modint(1) / a, MOD - 1 ?  MOD - 1 - n % (MOD - 1): 0);
        if(!n) return modint(1);
        if(n & 1) return a * pow(a, n - 1);
        return pow(a * a, n >> 1);
    }
    modint &operator-() { if(x = -x; x != 0) x += MOD; return *this; }
    friend bool operator==(const modint &a, const modint &b) { return a.x == b.x; }
    friend ostream &operator<<(ostream &s, const modint &b) { return s << b.x; }
};
using mint = modint<(int) 1e9 + 7>; 