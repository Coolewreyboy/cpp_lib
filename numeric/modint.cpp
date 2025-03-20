template<int MOD>
struct modint {
   int x;
   modint(): x{0} {}
   modint(int val): x{val} {
      if(x < -MOD || x >= MOD) x %= MOD;
      if(x < 0) x += MOD;
   }
   modint(ll val): x{val % MOD} { if(x < 0) x += MOD; }
   #define op(A, B, C) modint &operator A(const modint &b) { C return *this; } friend modint operator B(modint a, const modint &b) { return a A b; }
   op(+=, +, x >= MOD - b.x ? x += b.x - MOD: x += b.x;)
   op(-=, -, x -= b.x; if(x < 0) x += MOD;)
   op(*=, *, x = (long long) x * b.x % MOD;)
   modint &operator/=(const modint &b) {
      int xx = 1, yy = 0, aa = MOD, bb = b.x;
      while(bb) swap(xx, yy -= aa / bb * xx), swap(bb, aa %= bb);
      if(xx % MOD == 0) swap(xx, yy);
      x = (long long) x * xx % MOD;
      if(x < 0) x += MOD;
      return *this;
   }
   friend modint operator/(modint a, const modint &b) { return a /= b; }
   friend modint pow(modint a, long long n) {
      if(n < 0) return pow(1 / a, MOD - 1 ?  MOD - 1 - n % (MOD - 1): 0);
      modint q(1);
      for(; n; n >>= 1, a *= a) if(n & 1) q *= a;
      return q;
   }
   modint &operator-() { if(x = -x; x != 0) x += MOD; return *this; }
   friend bool operator==(const modint &a, const modint &b) { return a.x == b.x; }
   friend ostream &operator<<(ostream &s, const modint &b) { return s << b.x; }
   int &operator*() { return x; }
};
using mint = modint<998244353>;