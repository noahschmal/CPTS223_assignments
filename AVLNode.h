#ifndef __AVLNode_H
#define __AVLNode_H

template <typename T>
class AVLNode {
    public:
        // Data
        T data;

        // Left and Right Pointer
    	AVLNode *left;
        AVLNode *right;

        // Height
        int height;

        // Constructors
        AVLNode() {
            left = nullptr;
            right = nullptr;
            height = 1;
        }

        AVLNode(T newData) {
            left = nullptr;
            right = nullptr;
            data = newData;
			height = 1;
        }

        // Destructor
        ~AVLNode() {
			
        }

    

};

#endif
