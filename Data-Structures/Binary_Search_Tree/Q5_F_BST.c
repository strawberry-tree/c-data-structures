//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section F - Binary Search Trees Questions
Purpose: Implementing the required functions for Question 5
		 Implementing 'remove node' operation for BST*/
//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _bstnode{
	int item;
	struct _bstnode *left;
	struct _bstnode *right;
} BSTNode;   // You should not change the definition of BSTNode

typedef struct _stackNode{
	BSTNode *data;
	struct _stackNode *next;
}StackNode; // You should not change the definition of StackNode

typedef struct _stack
{
	StackNode *top;
}Stack; // You should not change the definition of Stack

///////////////////////// function prototypes ////////////////////////////////////

// You should not change the prototypes of these functions
void postOrderIterativeS2(BSTNode *root);

void insertBSTNode(BSTNode **node, int value);

void push(Stack *stack, BSTNode *node);
BSTNode *pop(Stack *s);
BSTNode *peek(Stack *s);
int isEmpty(Stack *s);
void removeAll(BSTNode **node);
BSTNode* removeNodeFromTree(BSTNode *root, int value);
void inOrderTraversal(BSTNode *root);

///////////////////////////// main() /////////////////////////////////////////////

int main()
{
	int c, i;
	c = 1;

	//Initialize the Binary Search Tree as an empty Binary Search Tree
	BSTNode * root;
	root = NULL;

	printf("1: Insert an integer into the binary search tree;\n");
	printf("2: Print the post-order traversal of the binary search tree;\n");
	printf("0: Quit;\n");


	while (c != 0)
	{
		printf("Please input your choice(1/2/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to insert into the Binary Search Tree: ");
			scanf("%d", &i);
			insertBSTNode(&root, i);
			printf("현재 BST: ");
			inOrderTraversal(root);
			printf("\n");
			break;
		case 2:
			printf("The resulting post-order traversal of the binary search tree is: ");
			postOrderIterativeS2(root); // You need to code this function
			printf("\n");
			break;
		case 3:
			printf("삭제할 키값을 입력해 주세요: ");
			scanf("%d", &i);
			root = removeNodeFromTree(root, i);
			printf("현재 BST: ");
			inOrderTraversal(root);
			printf("\n");
			break;
		case 0:
			removeAll(&root);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}

	}

	return 0;
}

//////////////////////////////////////////////////////////////////////////////////

void postOrderIterativeS2(BSTNode *root)
{
	Stack s1;
	s1.top = NULL;
	Stack s2;
	s2.top = NULL;

	if (root != NULL) push(&s1, root);

	// (루트노드) -> (우측자식) -> (좌측자식) 순으로 순회한 결과
	// 팝을 한 뒤, (좌측자식) -> (우측자식) 순으로 푸시
	while (isEmpty(&s1) == 0){
		BSTNode *popNode = pop(&s1);

		if (popNode != NULL){
			push(&s2, popNode);
			push(&s1, popNode -> left);
			push(&s1, popNode -> right);
		}
	}

	while (isEmpty(&s2) == 0){
		printf("%d ", pop(&s2) -> item);
	}
}

/* Given a binary search tree and a key, this function
   deletes the key and returns the new root. Make recursive function. */
BSTNode* removeNodeFromTree(BSTNode *root, int value)
{
	// 삭제할 노드를 찾지 못함
	if (root == NULL){
		return root;
	}

	// 삭제할 노드까지 탐색
	if (value < (root -> item)){
		root -> left = removeNodeFromTree(root -> left, value);
		return root;
	} else if (value > (root -> item)){
		root -> right = removeNodeFromTree(root -> right, value);
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
		root -> left = removeNodeFromTree(root -> left, maxNode -> item);
		return root;
	}
}
///////////////////////////////////////////////////////////////////////////////

void insertBSTNode(BSTNode **node, int value){
	if (*node == NULL)
	{
		*node = malloc(sizeof(BSTNode));

		if (*node != NULL) {
			(*node)->item = value;
			(*node)->left = NULL;
			(*node)->right = NULL;
		}
	}
	else
	{
		if (value < (*node)->item)
		{
			insertBSTNode(&((*node)->left), value);
		}
		else if (value >(*node)->item)
		{
			insertBSTNode(&((*node)->right), value);
		}
		else
			return;
	}
}

//////////////////////////////////////////////////////////////////////////////////

void push(Stack *stack, BSTNode * node)
{
	StackNode *temp;

	temp = malloc(sizeof(StackNode));

	if (temp == NULL)
		return;
	temp->data = node;

	if (stack->top == NULL)
	{
		stack->top = temp;
		temp->next = NULL;
	}
	else
	{
		temp->next = stack->top;
		stack->top = temp;
	}
}


BSTNode * pop(Stack * s)
{
	StackNode *temp, *t;
	BSTNode * ptr;
	ptr = NULL;

	t = s->top;
	if (t != NULL)
	{
		temp = t->next;
		ptr = t->data;

		s->top = temp;
		free(t);
		t = NULL;
	}

	return ptr;
}

BSTNode * peek(Stack * s)
{
	StackNode *temp;
	temp = s->top;
	if (temp != NULL)
		return temp->data;
	else
		return NULL;
}

int isEmpty(Stack *s)
{
	if (s->top == NULL)
		return 1;
	else
		return 0;
}


void removeAll(BSTNode **node)
{
	if (*node != NULL)
	{
		removeAll(&((*node)->left));
		removeAll(&((*node)->right));
		free(*node);
		*node = NULL;
	}
}

void inOrderTraversal(BSTNode *root)
{
	if (root == NULL) return;

	// 스택 선언
	Stack s;
	s.top = NULL;

	// 현재 탐색 중인 노드
	BSTNode *curr = root;

	while (curr != NULL || isEmpty(&s) == 0){
		
		// 현재 탐색 중인 노드를 스택에 푸시하고, 왼쪽 노드로 이동
		if (curr != NULL){
			push(&s, curr);
			curr = curr -> left;
		} else {
			// curr == NULL인 경우는
			// (1) 왼쪽 노드에 자식이 없었던 경우 -> 스택에서 부모노드를 pop해 출력하고, 이후 오른쪽 자식으로 이동

			// (2) 직전에 pop하고 오른쪽 자식으로 이동했는데, 그 오른쪽 자식이 없는 경우

			// 이 과정이 종료되면 오른쪽 노드로 이동.
			curr = pop(&s);
			printf("%d ", curr -> item);
			curr = curr -> right;
		}
	}
}