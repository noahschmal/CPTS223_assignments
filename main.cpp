#include "AVLTree.h"


#include <random>

// Verificiation: CMake works

int main () {
	srand(unsigned(time(0)));

	// Create three sequences of odd numbers between 1 - 100
        // 1 in ascending order, 1 in descending order, and 1 in random order
	int data1[50], data2[50], data3[50];
	for (int i = 1; i < 51; i++) {
		data1[i - 1] = i * 2 - 1;
		data2[i - 1] = 100 - (i * 2 - 1);
		data3[i - 1] = i * 2 - 1;
	}

	unsigned seed = 0;
	shuffle(&data3[0], &data3[49], std::default_random_engine(seed));


    // Create three trees and insert the data
	AVLTree<int> tree1;
	AVLTree<int> tree2;
	AVLTree<int> tree3;

	for (int i = 0; i < 50; i++) {
		tree1.insert(data1[i]);
		tree2.insert(data2[i]);
		tree3.insert(data3[i]);
	}

	// Print height of each tree
	cout << "Height of tree1: " << tree1.height() << "\n";
	cout << "Height of tree2: " << tree2.height() << "\n";
	cout << "Height of tree3: " << tree3.height() << "\n";

	// Print result of validate for each tree
	cout << "Validate of tree1: " << tree1.validate() << "\n";
	cout << "Validate of tree2: " << tree2.validate() << "\n";
	cout << "Validate of tree3: " << tree3.validate() << "\n";

	// Loop through contains with numbers 1-100
	for (int i = 1; i < 101; i++) {
		if (i % 2 == 0 && (tree1.contains(i) || tree2.contains(i) || tree3.contains(i))) {
			cout << "My AVL tree implementation is wrong\n";
		}
		cout << "tree1 contains " << i << ": " << tree1.contains(i) << "\n";
		cout << "tree2 contains " << i << ": " << tree2.contains(i) << "\n";
		cout << "tree3 contains " << i << ": " << tree3.contains(i) << "\n";
	}
}
