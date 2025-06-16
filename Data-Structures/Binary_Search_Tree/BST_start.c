#include <stdio.h>
#include <stdlib.h>

// 각 노드를 나타내는 구조체 Node
typedef struct _bstnode{
	int item;                   // 노드에 저장된 값
	struct _bstnode *left;      // 왼쪽 자식 노드를 가리키는 포인터
	struct _bstnode *right;     // 오른쪽 자식 노드를 가리키는 포인터
} BSTNode;

// 이진 탐색 트리를 나타내는 구조체 BST
typedef struct _bst{
    struct _bstnode *root;      // 머리 노드를 가리키는 포인터
} BST;

// root가 루트노드인 트리에 값이 value인 노드를 삽입하고, 루트노드를 반환
BSTNode *insertBSTNode(BSTNode *root, int value){

    // 노드를 삽입할 위치까지 이동한 경우
	if (root == NULL){

        // 새로운 노드를 생성
		root = malloc(sizeof(BSTNode));

        // root != NULL을 체크하는 이유: 메모리 할당이 잘 이루어졌는지 확인
		if (root != NULL) {
			// 값은 value, 왼쪽 / 오른쪽 자식은 NULL로 초기화
            root -> item = value;
			root -> left = NULL;
			root -> right = NULL;
		}
	}
	else {
		if (value < (root -> item)){
            // 찾는 값 < 노드의 값 -> 왼쪽 노드 재귀호출
			root -> left = insertBSTNode(root->left, value);
		}
		else if (value > (root -> item)){
            // 찾는 값 > 노드의 값 -> 오른쪽 노드 재귀호출
			root -> right = insertBSTNode(root->right, value);
		}
        else {
            // 찾는 값 == 노드의 값 -> 삽입 불가능, 추가 재귀호출 없음
            printf("이미 동일한 노드가 존재합니다.\n");
        }
    }

    return root; // 노드를 반환
}

void insertBST(BST *tree, int value){
    // insertBSTNode 함수가 반환한 노드를 루트 노드로 설정
    tree -> root = insertBSTNode(tree -> root, value);
}

BSTNode *findBSTNode(BSTNode *node, int value){
    // 널 포인터 -> 탐색에 실패
    if (node == NULL) return NULL;
    
    if (value < (node -> item)){
        // 찾는 값 < 노드의 값 -> 왼쪽 노드 재귀호출
        return findBSTNode(node -> left, value);
    } else if (value > (node -> item)){
        // 찾는 값 > 노드의 값 -> 오른쪽 노드 재귀호출
        return findBSTNode(node -> right, value);
    } else {
        // 노드를 찾았으므로 노드를 반환
        return node;
    }
}

BSTNode *findBST(BST *tree, int value){
    if (tree == NULL) return NULL;
    return findBSTNode(tree -> root, value);
}


// root가 루트노드인 트리에서 값이 value인 노드를 삭제하고, 루트노드를 반환
BSTNode *removeBSTNode(BSTNode *root, int value)
{
	// 삭제할 노드를 찾지 못함
	if (root == NULL){
		return root;
	}

	// 삭제할 노드까지 탐색
	if (value < (root -> item)){
		root -> left = removeBSTNode(root -> left, value);
		return root;
	} else if (value > (root -> item)){
		root -> right = removeBSTNode(root -> right, value);
		return root;
	}

	// 삭제할 노드를 찾은 경우

	if (root -> left == NULL && root -> right == NULL){
		// (1) 내가 리프 노드일 때 -> 나만 사라지면 그만이야.
		free(root);
		return NULL;
	} else if (root -> left == NULL){
		// (2) 오른쪽 자식만 있을 때 -> 오른쪽 자식에게 넘겨주자.
		BSTNode *newNode = root -> right;
		free(root);
		return newNode;
	} else if (root -> right == NULL){
		// (2) 왼쪽 자식만 있을 때 -> 왼쪽 자식에게 넘겨주자.
		BSTNode *newNode = root -> left;
		free(root);
		return newNode;
	} else{
		// (3) 두 자식이 둘 다 있을 때
		// (3a) 삭제할 트리의 왼쪽 서브트리에서 최댓값 노드를 찾는다.
		// 그니까 처음엔 왼쪽으로 가고, 다음엔 계속 오른쪽으로 간다.
		BSTNode *maxNode = root -> left;
		while (maxNode -> right != NULL){
			maxNode = maxNode -> right;
		}
		// (3b) 루트의의 값을 바꾼다.
		root -> item = maxNode -> item;

		// (3c) 검색한 위치의 노드를 삭제한다.
		root -> left = removeBSTNode(root -> left, maxNode -> item);
		return root;
	}
}

void removeBST(BST *tree, int value){
    tree -> root = removeBSTNode(tree -> root, value);
}

void preOrder(BSTNode *root)
{
    // NULL일 땐 바로 return (종료조건)
	if (root == NULL) return;

	printf("%d ", root -> item);    // 자기 자신 방문
	preOrder(root -> left);         // 왼쪽 자식 탐색
	preOrder(root -> right);        // 오른쪽 자식 탐색
}

void inOrder(BSTNode *root)
{
	// NULL일 땐 바로 return (종료조건)
	if (root == NULL) return;

	inOrder(root -> left);          // 왼쪽 자식 탐색
	printf("%d ", root -> item);    // 자기 자신 방문
	inOrder(root -> right);         // 오른쪽 자식 탐색
}

void postOrder(BSTNode *root)
{
    // NULL일 땐 바로 return (종료조건)
	if (root == NULL) return;

	postOrder(root -> left);        // 왼쪽 자식 탐색
	postOrder(root -> right);       // 오른쪽 자식 탐색
	printf("%d ", root -> item);    // 자기 자신 방문
}

void removeAll(BSTNode *node)
{
	if (node != NULL)
	{
		removeAll(node -> left);
		removeAll(node -> right);
		free(node);

	}
}


int main(void){
	BST bs_tree;
	bs_tree.root = NULL;

	int nums[7] = {7, 3, 9, 1, 5, 8, 10};

	// 값을 삽입
	for (int i = 0; i < 7; i++){
		insertBST(&bs_tree, nums[i]);
	}

	// 전위 순회
	preOrder(bs_tree.root);		// 7 3 1 5 9 8 10 
	printf("\n");
	
	// 중위 순회
	inOrder(bs_tree.root);		// 1 3 5 7 8 9 10 
	printf("\n");

	// 후위 순회
	postOrder(bs_tree.root);	//1 5 3 8 10 9 7 
	printf("\n");

	// 노드 탐색
	BSTNode *found = findBST(&bs_tree, 10);
	if (found != NULL){
		printf("노드 10을 찾았습니다.\n");
	} else {
		printf("노드 10을 찾지 못했습니다.\n");
	}
	// 노드 10을 찾았습니다.

	found = findBST(&bs_tree, 33);
	if (found != NULL){
		printf("노드 33을 찾았습니다.\n");
	} else {
		printf("노드 33을 찾지 못했습니다.\n");
	}
	// 노드 33을 찾지 못했습니다.

	// 노드 삭제
	removeBST(&bs_tree, 7);
	preOrder(bs_tree.root);	// 5 3 1 9 8 10
	// 5가 새로운 루트노드가 되었음에 유의

	// 메모리할당해제
	removeAll(bs_tree.root);
	bs_tree.root = NULL;
}