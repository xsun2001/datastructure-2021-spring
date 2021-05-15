#include <cstdio>
#include <cstdlib>
#include <i386/types.h>

struct Node{
	char c;
	Node *prv, *nxt;
	bool reversed;
};

struct Cursor{
	Node* node;
	bool reversed;
};

bool next(Cursor *c){
	Node* old_node = c->node;
	c->node = c->reversed ? c->node->prv : c->node->nxt;
	if(c->node == nullptr){
		c->node = old_node;
		return false;
	}
	if(c->node->reversed) c->reversed = !c->reversed;
	return true;
}

bool previous(Cursor *c){
	Node* old_node = c->node;
	c->node = c->reversed ? c->node->nxt : c->node->prv;
	if(c->node == nullptr){
		c->node = old_node;
		return false;
	}
	if(old_node->reversed) c->reversed = !c->reversed;
	return true;
}

void connect(Node *l, Node *r){
	l->nxt = r;
	r->prv = l;
}

void insert(Cursor *c, char c){

}

bool reverse(Cursor* l, Cursor* r){
	Node* ln = l->node,* rn = r->node;
	Node* lln = ln->prv,* rrn = rn->nxt;
	connect(
	return true;
}
