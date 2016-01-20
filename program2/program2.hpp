#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

class BestFirstSearch {
public:
	class Item {
	public:
		int itemNumber;
		int weight;
		int profit;
		int p_over_w;
		Item() {}
		Item(int i, int j , int k, int l) : itemNumber(i), weight(j), profit(k), p_over_w(l) {} 
	};
	class Node {
	public:
		int level;
		int profit;
		int weight;
		int bound;	
		Node *left;
		Node *right;
		Node *parent;
		std::vector<Item *> other;
		Node() {}
		Node(int h, int i, int j) : level(h), profit(i), weight(j), left(nullptr), right(nullptr), parent(nullptr) {}
	};
	
	Node *head;
	Node *opt_Node;
	int capacity;
	int opt_val;
	int visited_tot;
	int leaf_tot;

	std::vector<Node *> nodes;
	std::vector<Item *> items;
	std::vector<Node *> heap;
	
	BestFirstSearch(std::string input, std::string output);
	void addItem(int n, int w, int p);
	void bfs(Node *, int);
	int getBound(Node *n);
	~BestFirstSearch();
};
