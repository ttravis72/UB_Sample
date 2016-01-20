#include "program2.hpp"

using namespace std;

//comparator for heap
bool comparator(BestFirstSearch::Node *n1, BestFirstSearch::Node *n2);

BestFirstSearch::BestFirstSearch(string input, string output) : head(new Node()), opt_Node(nullptr), opt_val(0), visited_tot(0), leaf_tot(0) {
	string num_items;
	string cap;
	int weight;
	int profit;
	fstream input_file;
	input_file.open(input);
	getline(input_file, num_items, ',');
	input_file >> capacity;
	for(int i = 1; i <= atoi(num_items.c_str()); i++) {
		input_file.ignore(10000, '\n');
		getline(input_file, cap, ',');
		weight = atoi(cap.c_str());
		input_file >> profit;
		addItem(i, weight, profit);
	}
	input_file.close();

	//Assign values for head node
	head->profit = 0;
	head->weight = 0;
	head->level = 0;
	head->bound = getBound(head);
	head->other = items;
	head->parent = head;
	heap.push_back(head);
	nodes.push_back(head);

	bfs(heap.front(), 0);

	ofstream output_file;
	output_file.open(output);
	output_file << items.size() << "," << opt_val << "," << opt_Node->other.size() << endl;
	output_file << visited_tot << "," << leaf_tot << endl;
	for(auto i : opt_Node->other) {
		output_file << i->weight << "," << i->profit << endl;
	}
	output_file.close();
}



//push item onto heap
void BestFirstSearch::addItem(int n, int w, int p) {
	Item *new_item = new Item(n, w, p, p/w);
	if(items.size() == 0) {
		items.push_back(new_item);
	}
	else {
		for(int i = 0; i <= items.size(); i++) {
			if(i == items.size()) {
				items.push_back(new_item);
				break;
			}
			if(items[i]->p_over_w < new_item->p_over_w) {
				items.emplace(items.begin() + i, new_item);
				break;
			}
		}
	}
}

//remove all instances of bfs
BestFirstSearch::~BestFirstSearch() {
	for(auto i : items) {
		delete i;
	}
	for(auto i : nodes) {
		delete i;
	}
}

//calculate bound for each node
int BestFirstSearch::getBound(Node *n) {
	int current_weight = 0;
	int bound = 0;
	for(auto i : n->other) {
		if((i->weight + current_weight) > capacity) {
			bound += (i->profit * (capacity - current_weight)) / i->weight;
			return bound;
		}
		else {
			current_weight += i->weight;
			bound += i->profit;
		}
	}
	return bound;
}

//actual search part
void BestFirstSearch::bfs(Node *n, int i) {
	
	while(!heap.empty()) {
		heap.erase(heap.begin());
		if(n->bound <= opt_val || n->weight > capacity) {
			leaf_tot++;
			visited_tot++;
			n = heap.front();
			i = n->level;
		}
		else {
			n->left = new Node(i+1, items[i]->profit + n->profit, items[i]->weight + n->weight);
			n->left->parent = n;
			n->left->other = n->other;
			n->left->bound = getBound(n->left);
			if(opt_val <= n->left->profit && n->left->weight <= capacity) {
				opt_val = n->left->profit;
				opt_Node = n->left;
			}
			heap.push_back(n->left);
			nodes.push_back(n->left);

			n->right = new Node(i+1, n->profit, n->weight);
			n->right->parent = n;
			n->right->other = n->other;
			for (auto iterator = n->right->other.begin(); iterator != n->right->other.end();  ++iterator ) {
				if(*iterator == items[i]) {
					n->right->other.erase(iterator);
					break;
				}
			}
			n->right->bound = getBound(n->right);
			if(opt_val <= n->right->profit) opt_Node = n->right;
			heap.push_back(n->right);
			nodes.push_back(n->right);

			std::sort(heap.begin(),heap.end(), comparator);

			visited_tot++;
			n = heap.front();
			i = n->level;
		}
	}
}

// not a member
bool comparator(BestFirstSearch::Node *n1, BestFirstSearch::Node *n2) {
	if(n1->bound > n2->bound) return true;
	else return false; 
}