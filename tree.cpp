struct node {
	int h;
	long long x;
	node *l, *r;
	node(long long val) {
		x = val;
		h = 1;
		l = nullptr;
		r = nullptr;
	}
};

int h(node* v) { return v ? v->h : 0; }
void upd(node* v) {
	if(!v)
		return;
	v->h = max(h(v->l), h(v->r)) + 1;
}

void right_rotate(node** v) {
	if(!*v)
		return;
	node* new_v = (*v)->r;
	(*v)->r = new_v->l;
	upd(*v);
	new_v->l = *v;
	*v = new_v;
	upd(*v);
}

void left_rotate(node** v) {
	if(!*v)
		return;
	node* new_v = (*v)->l;
	(*v)->l = new_v->r;
	upd(*v);
	new_v->r = *v;
	*v = new_v;
	upd(*v);
}

void balance(node** v) {
	if(!*v)
		return;
	if(abs(h((*v)->l) - h((*v)->r)) < 2)
		return;
	if(h((*v)->r) - h((*v)->l) > 0) {
		if(h((*v)->r->l) > h((*v)->r->r))
			left_rotate(&((*v)->r));
		right_rotate(v);
		return;
	}
	if(h((*v)->l->r) > h((*v)->l->l))
		right_rotate(&((*v)->l));
	left_rotate(v);
	
}
void insert(node** v, long long x) {
	if(!*v) {
		*v = new node(x);
		return;
	}
	if((*v)->x >= x)
		insert(&(*v)->l, x);
	else
		insert(&(*v)->r, x);
	balance(v);
	upd(*v);
}
node* remove_min(node** v) {
	 if((*v)->l)
		 return remove_min(&((*v)->l));
	 node *res = *v;
	 *v = (*v)->r;
	 balance(v);
	 return res;
}

void remove(node** v, long long x) {
	if(!*v)
		return;
	if((*v)->x == x) {
		node *new_v = nullptr;
		if((*v)->r && (*v)->l) {
			new_v = remove_min(&((*v)->r));
			new_v->r = (*v)->r;
			new_v->l = (*v)->l;
		}	
		else if((*v)->r)
			new_v = (*v)->r;
		else if((*v)->l)
			new_v = (*v)->l;
		*v = new_v;
		balance(v);
		return;
	}
	if((*v)->x > x)
		remove(&((*v)->l), x);
	else
		remove(&((*v)->r), x);
	balance(v);

}

node* get_min(node* v) {
	if(!v)
		return nullptr;
	if(v->l)
		return get_min(v->l);
	return v;	
}
node* get_max(node* v) {
	if(!v)
		return nullptr;
	if(v->r)
		return get_max(v->r);
	return v;
}

int count(node* v, long long x) {
	if(!v)
		return 0;
	if(v->x == x)
		return 1;
	if(v->x > x)
		return count(v->l, x);
	return count(v->r, x);
}
void print(node *root) {
	if(!root)
		return;
	print(root->l);
	cout << h(root->l) << ' ' << h(root->r) << endl;
	print(root->r);
}
