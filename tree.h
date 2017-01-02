#ifndef TREE_H
#define TREE_H

#include <string>
#include <iostream>

#include "type.h"

struct trace;
struct data;
struct node;

struct trace{
	bool color;
	pos_type pos;
};

struct data{
	trace tra;
	int win;
	int lose;
};

struct node{
	data dat;
	node* parent;
	node* sibling;
	node* child;
};

typedef node* pnode;
typedef const pnode& cpnode;

class tree{
public:
	node* root;

	tree():count(0){
		root = new node({{true,-1,0,0},NULL,NULL,NULL});
	}
	~tree(){
		destroy(root);
	}

	static const int threshold = 10;

	void print()const{
		print(root);
	}

	void save(const string& path);
	void load(const string& path);

	static node* find_child(node* ptr,pos_type pos){
		for(ptr = ptr->child;ptr;ptr = ptr->sibling){
			if(ptr->dat.tra.pos == pos){
				return ptr;
			}
		}
		return NULL;
	}
	static pair<node*,bool> get_child(node* ptr,pos_type pos){
		if(ptr->child){
			node* head = ptr;
			for(ptr = ptr->child;ptr;ptr = ptr->sibling){
				if(ptr->dat.tra.pos == pos){
					return pair<node*,bool>(ptr,true);
				}
				head = ptr;
			}
			return pair<node*,bool>(head->sibling = new node,false);
		}else{
			return pair<node*,bool>(ptr->child = new node,false);
		}
	}

	// void add_path(trace* path, cbool is_win){
		// auto p = get_child(root,path->pos);
		// while(path->pos >= 0){
			// if(p->second){
				// assert(p.first->dat.tra.color == path->color);
				// if(path->color ^ is_win){
					// ++p.first->dat.win;
				// }else{
					// ++p.first->dat.lose;
				// }
				// if(p.first->dat.win + p.first->dat.lose < threshold){
					// break;
				// }
			// }else{
				// p.first->dat.tra.color = path->color;
				// if(path->color ^ is_win){
					// p.first = node({{*path,1,0},NULL,NULL})
				// }else{
					// p.first = node({{*path,0,1},NULL,NULL})
				// }
			// }
			// ++path;
			// p = get_child(p->first,path->pos)
		// }
	// }

	void add_path(trace* path, cbool is_win){
		node* head = root;
		bool flag;
		for(node* ptr = head->child;path->pos >= 0;++path){
			flag = true;
			while(ptr){
				flag = false;
				assert(ptr->dat.tra.color == path->color);
				if(ptr->dat.tra.pos == path->pos){
					if(ptr->dat.tra.color ^ is_win){
						++ptr->dat.win;
					}else{
						++ptr->dat.lose;
					}
					if(ptr->dat.win + ptr->dat.lose >= threshold){
						goto label;
					}else{
						return;
					}
				};
				head = ptr;
				ptr = ptr->sibling;
			}

			(flag ? head->child : head->sibling)
				= (
					path->color ^ is_win
					? new node({{*path,1,0},NULL,NULL,NULL})
					: new node({{*path,0,1},NULL,NULL,NULL})
				);
			++count;
			break;

			label:
			head = ptr;
			ptr = ptr->child;
		}
	}

	void practice(method mthd,cshort height);

private:
	int count;

	static void destroy(node*& ptr){
		if(ptr){
			destroy(ptr->sibling);
			destroy(ptr->child);
			delete ptr;
		}
	}

	static void print(const node* const& ptr){
		cout<< "(((" << ptr->dat.tra.color << "," << ptr->dat.tra.pos << "),"
			<< ptr->dat.win << "," << ptr->dat.lose << "),"
			<< (ptr->child != NULL) << ","
			<< (ptr->sibling != NULL) << ")" << endl;
		
		if(ptr->child){
			print(ptr->child);
		}
		if(ptr->sibling){
			print(ptr->sibling);
		}
	}

	static void save(ostream& out,const node* const& ptr);
};

#endif //TREE_H