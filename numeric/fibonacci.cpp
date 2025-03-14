template<class T>
struct fibonacci {
   T operator()(long long n) {
      T x(0), y(1);
      bool sign = n < 0;
      n = abs(n);
      for(int i = (n ? __lg(n): 0); i >= 0; i--) {
         T xx = x * x, yy = y * y;
         x *= y + y - x, y = xx + yy;
         if((n >> i) & 1) swap(y, x += y);
      }
      if(!sign || n & 1) return x;
      return -x;
   }
   T gcd(long long i, long long j) {
      return operator()(std::gcd(i, j));
   }
};
//fibonacci<...> fib;