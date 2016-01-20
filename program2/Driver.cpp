#include "program2.hpp"

using namespace std;

int main(int argc, char** argv) {
	if(argc != 3) {
		cout << "To use this program:" << endl;
		cout << "./BestFirstSearch input.txt output.txt" << endl;
		return 0;
	}
	BestFirstSearch bfs(argv[1], argv[2]);
	return 0;
}
