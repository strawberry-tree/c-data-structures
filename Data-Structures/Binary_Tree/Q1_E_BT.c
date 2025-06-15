//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section E - Binary Trees Questions
Purpose: Implementing the required functions for Question 1 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////
typedef struct _btnode{
	int item;
	struct _btnode *left;
	struct _btnode *right;
} BTNode;   // You should not change the definition of BTNode

/////////////////////////////////////////////////////////////////////////////////

typedef struct _stackNode{
    BTNode *btnode;
    struct _stackNode *next;
}StackNode;

typedef struct _stack{
    StackNode *top;
}Stack;

///////////////////////// function prototypes ////////////////////////////////////

// You should not change the prototypes of these functions
int identical(BTNode *tree1, BTNode *tree2);

BTNode* createBTNode(int item);

BTNode* createTree();
void push( Stack *stk, BTNode *node);
BTNode* pop(Stack *stk);

void printTree(BTNode *node);
void removeAll(BTNode **node);

///////////////////////////// main() /////////////////////////////////////////////

int main()
{
    int c, s;
    char e;
    BTNode *root1, *root2;

    root1 = NULL;
    root2 = NULL;
    c = 1;

    printf("1: Create a binary tree1.\n");
    printf("2: Create a binary tree2.\n");
    printf("3: Check whether two trees are structurally identical.\n");
    printf("0: Quit;\n");

    while(c != 0){
        printf("Please input your choice(1/2/3/0): ");
        if(scanf("%d", &c) > 0)

        {

            switch(c)
            {
            case 1:
                removeAll(&root1);
                printf("Creating tree1:\n");
                root1 = createTree();
                printf("The resulting tree1 is: ");
                printTree(root1);
                printf("\n");
                break;
            case 2:
                removeAll(&root2);
                printf("Creating tree2:\n");
                root2 = createTree();
                printf("The resulting tree2 is: ");
                printTree(root2);
                printf("\n");
                break;
            case 3:
                s = identical(root1, root2);
                if(s){
                printf("Both trees are structurally identical.\n");
                }
                else{
                printf("Both trees are different.\n");
                }
                removeAll(&root1);
                removeAll(&root2);
                break;
            case 0:
                removeAll(&root1);
                removeAll(&root2);
                break;
            default:
                printf("Choice unknown;\n");
                break;
            }
		}
        else
        {
            scanf("%c",&e);
        }

    }
    return 0;
}

//////////////////////////////////////////////////////////////////////////////////

int identical(BTNode *tree1, BTNode *tree2)

{
   // 결국엔 재귀문제
   // 종료조건: 리프노드의 자식은 NULL, 거기까지 간 경우
   if (tree1 == NULL){
     if (tree2 == NULL){
        return 1;       // identical
     } else {
        return 0;       // not identical
     }
   }

   if (tree2 == NULL){
       return 0;        // not identical
   }

   if (tree1 -> item == tree2 -> item && identical(tree1 -> left, tree2 -> left) && identical(tree1 -> right, tree2 -> right)){
        return 1;       // identical
   } else {
        return 0;       // not identical
   }
}

/////////////////////////////////////////////////////////////////////////////////

BTNode *createBTNode(int item){
    // 일단 값을 받고 노드를 만듦
    BTNode *newNode = malloc(sizeof(BTNode));
    newNode->item = item;

    // 자식은 일단 비우고 스택으로 만듦
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

//////////////////////////////////////////////////////////////////////////////////

// 트리를 만든다.
BTNode *createTree()
{
    Stack stk;              // 트리 만들기용 스택
    BTNode *root, *temp;    // 트리의 루트 노드 및 현재 노드
    char s;
    int item;               // 노드의 데이터 값

    stk.top = NULL;         // 현재 스택은 비어 있음
    root = NULL;            // 루트 노드를 가리키는 포인터

    // 루트 노드 만들기
    printf("Input an integer that you want to add to the binary tree. Any Alpha value will be treated as NULL.\n");
    printf("Enter an integer value for the root: ");
    if(scanf("%d",&item) > 0)
    {
        root = createBTNode(item);      // 루트 노드를 만들고
        push(&stk,root);                // 스택에 푸시한다
    }
    else
    {
        scanf("%c",&s);
    }

    while((temp =pop(&stk)) != NULL)    // 스택에서 노드를 팝한다
    {

        printf("Enter an integer value for the Left child of %d: ", temp->item);

        if(scanf("%d",&item)> 0)
        {
            // 현재 노드의 왼쪽 자식 노드를 만든다
            temp->left = createBTNode(item);
        }
        else
        {
            // a를 입력한 경우
            scanf("%c",&s);
        }

        printf("Enter an integer value for the Right child of %d: ", temp->item);
        if(scanf("%d",&item)>0)
        {
            // 현재 노드의 오른쪽 자식 노드를 만든다
            temp->right = createBTNode(item);
        }
        else
        {
            // a를 입력한 경우
            scanf("%c",&s);
        }

        // 자식 노드가 존재하면 스택에 푸시해준다
        // 나중에 너도 자식을 가질 수 있게
        if(temp->right != NULL)
            push(&stk,temp->right);
        if(temp->left != NULL)
            push(&stk,temp->left);
    }
    return root;
}

// 스택에 노드를 푸시한다.
// 이때 스택은 연결리스트의 형태로 구현
// 연결리스트의 머리 노드가, 스택의 최상단 노드
void push( Stack *stk, BTNode *node){
    StackNode *temp;

    temp = malloc(sizeof(StackNode));
    if(temp == NULL)
        return;
    temp->btnode = node;

    // 스택이 비어 있을 때 푸시
    if(stk->top == NULL){
        stk->top = temp;
        temp->next = NULL;
    }
    // 스택이 안 비어 있을 때 푸시
    else{
        temp->next = stk->top;
        stk->top = temp;
    }
}

BTNode* pop(Stack *stk){
   StackNode *temp, *top;
   BTNode *ptr;
   ptr = NULL;

   top = stk->top;
   if(top != NULL){
        temp = top->next;
        ptr = top->btnode;

        stk->top = temp;
        free(top);
        top = NULL;
   }
   return ptr;
}

// 중위 순회로 트리의 모든 노드 값을 출력한다.
void printTree(BTNode *node){
    if(node == NULL) return;

    printTree(node->left);
    printf("%d ",node->item);
    printTree(node->right);
}

// 트리의 모든 노드를 제거한다.
void removeAll(BTNode **node){
    if(*node != NULL){
        removeAll(&((*node)->left));
        removeAll(&((*node)->right));
        free(*node);
        *node = NULL;
    }
}
