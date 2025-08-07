#include <bits/stdc++.h>

using namespace std;

struct node {
	long long value;
	node *left, *right, *parent;
	node(long long val, node *par) {
		value = val;
		left = nullptr;
		right = nullptr;
		parent = par;
		if(parent && parent->value < value)
			parent->right = this;
		else if(parent)
			parent->left = this;
	}
};

void print(node* v) {
	if(!v)
		return;
	print(v->left);
	cout << v->value << ' ';
	print(v->right);
}

void right_rotate(node* &v) {
	node *new_v = v->right;
	new_v->parent = v->parent;
	if(new_v->parent && new_v->parent->right == v) {
		new_v->parent->right = new_v;
	}
	else if(new_v->parent) {
		new_v->parent->left = new_v;
	}
	v->parent = new_v;
	v->right = new_v->left;
	if(v->right)
		v->right->parent = v;
	new_v->left = v;
	v = new_v;
}
void left_rotate(node* &v) {
	node *new_v = v->left;
	new_v->parent = v->parent;
	if(new_v->parent && new_v->parent->left == v) {
		new_v->parent->left = new_v;
	}
	else if(new_v->parent) {
		new_v->parent->right = new_v;
	}
	v->parent = new_v;
	v->left = new_v->right;
	if(v->left)
		v->left->parent = v;
	new_v->right = v;
	v = new_v;
}

void splay(node* &root) {
	while(root->parent) {
		if(!root->parent->parent) {
			if(root->parent->right == root) {
				root = root->parent;
				right_rotate(root);
			}
			else {
				root = root->parent;
				left_rotate(root);
			}
		}
		else {
			if(root->parent->left == root && root->parent->parent->right == root->parent) {
				root = root->parent;
				left_rotate(root);
				root = root->parent;
				right_rotate(root);
			}	
			else if(root->parent->right == root && root->parent->parent->left == root->parent) {
				root = root->parent;
				right_rotate(root);
				root = root->parent;
				left_rotate(root);
			}
			else if(root->parent->right == root && root->parent->parent->right == root->parent) {
				root = root->parent->parent;
				right_rotate(root);
				right_rotate(root);
			}
			else {
				root = root->parent->parent;
				left_rotate(root);
				left_rotate(root);
			}
		}
	}	
}
void insert(long long x, node* &root) {
	node *prev = nullptr;
	while(root) {
		prev = root;
		if(root->value < x)
			root = root->right;
		else
			root = root->left;
	}
	root = new node(x, prev);
	splay(root);
}
node* merge(node *left_root, node *right_root)
{
	if(!left_root) return right_root;
	if(!right_root) return left_root;
	while(left_root->right)
		left_root = left_root->right;
	splay(left_root);
	left_root->right = right_root;
	left_root->parent = nullptr;
	right_root->parent = left_root;
	return left_root;
}
pair<node*, node*> split(long long x, node* root) //<= x and x <
{
	if(!root)
		return {nullptr, nullptr};
	node *v, *res = nullptr;
	for(; root;) {
		v = root;
		if(root->value <= x) {
			if(!res || root->value > res->value)
			       res = root;	
			root = root->right;
		}
		else
			root = root->left;	
	}
	if(!res)
		return {nullptr, v};
	v = res;
	splay(v);
	node *right_root = v->right;
	v->right = nullptr;
	if(right_root)
		right_root->parent = nullptr;
	return {v, right_root};
}
void remove(long long x, node* &root)
{
	for(; root;) {
		if(root->value == x)
			break;
		if(root->value < x && root->right)
			root = root->right;
		else if(root->value > x && root->left)
			root = root->left;
		else
			break;
	}	
	splay(root);
	if(root->value != x)
		return;
	if(root->left)
		root->left->parent = nullptr;
	if(root->right)
		root->right->parent = nullptr;
	root = merge(root->left, root->right);
}
node* get_min(node* &root)
{
	for(; root->left; root = root->left);
	splay(root);
	return root;
}
node* get_max(node* &root)
{
	for(; root->right; root = root->right);
	splay(root);
	return root;
}

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	long long n, k;
	node *root = nullptr;
	cin >> n >> k;
	vector<long long> a(n);
	for(auto &i : a)
		cin >> i;
	long long j = 0, c = 0;
	for(int i = 0; i < n; i++) {
		insert(a[i], root);
		while(j < n && get_max(root)->value - get_min(root)->value > k) {
			remove(a[j], root);
			j++;
		}
		if(get_max(root)->value - get_min(root)->value <= k)
			c += i  - j + 1;
	}
	cout << c;
	return 0;
}
