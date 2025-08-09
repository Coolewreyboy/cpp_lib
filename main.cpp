template<class T, class M>
struct dj_sparse_table {
	vector<vector<T>> t;
	dj_sparse_table(M a) {
		int sz = size(a);
		t.resize(__lg(sz) + 1, vector<T>(sz));
		for(int len = 1, j = 0; len < sz; len *= 2, j++) {
			for(int mid = len - 1; mid < sz; mid += 2 * len) {
				t[j][mid] = T(a[mid], c[mid]);
				for(int i = 1; i < len; i++)
					t[j][mid - i] = T(T(a[mid - i], c[mid - i]), t[j][mid - i + 1]);
				if(mid + 1 >= sz)
					break;
				t[j][mid + 1] = T(a[mid + 1], c[mid + 1]);
				for(int i = 1; i < len && mid + 1 + i < sz; i++)
					t[j][mid + 1 + i] = T(t[j][mid + 1 + i - 1], T(a[mid + 1 + i], c[mid + 1 + i]));	
			}
		}
	}
	T get(int l, int r) {
		if(l == r)
			return t[0][l];
		int lg = __lg(l ^ r);
		return T(t[lg][l], t[lg][r]);
	}
};
