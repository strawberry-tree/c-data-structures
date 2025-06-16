#include <stdio.h>
#include <stdlib.h>

// 각 노드를 나타내는 구조체 Node
typedef struct _listnode{
    int item;                   // 노드에 저장된 값
    struct _listnode *next;     // 다음 노드를 가리키는 포인터
} ListNode;

// 연결 리스트 전체를 나타내는 구조체 LinkedList
typedef struct _linkedlist{
    int size;                   // 연결 리스트의 원소 수
    ListNode *head;             // 머리 노드
} LinkedList;

// 연결 리스트의 특정 인덱스 원소 찾기
ListNode *findNode(LinkedList *ll, int index){
    
    // 연결 리스트가 없거나, 인덱스가 범위를 벗어나는 경우
    if (ll == NULL || index < 0 || index >= ll -> size){
        return NULL;
    }

    // 리스트 순회 중 현재 노드
    ListNode *temp = ll -> head;    // 머리부터 시작

    // 리스트에 노드가 없는 경우 (그럼 head가 NULL이겠죠)
    if (temp == NULL){
        return NULL;
    }

    // 본격적으로 연결 리스트 탐색
    // index번째 요소를 찾으려면, 총 index번 이동해야 함
    while (index > 0){
        temp = temp -> next;    // 다음 노드로 이동
        if (temp == NULL) return NULL;
        index--;                // index 값 1 감소
    }

    // 현재 위치의 노드 반환
    return temp;
}

// 연결 리스트에 원소 삽입
int insertNode(LinkedList *ll, int index, int value){

    // pre는 이전 노드, cur은 현재 노드를 가리킴
    ListNode *pre, *cur;

    // 연결 리스트가 없거나, 인덱스가 범위를 벗어나는 경우
    if (ll == NULL || index < 0 || index > ll->size + 1)
		return -1;

    // 머리 노드가 없어, 인덱스 0에 삽입하는 경우
    // 머리에 삽입하게 됨
    if (ll -> head == NULL || index == 0) {
        // (1) 현재 머리 노드를 cur에 저장
        cur = ll -> head;
        
        // (2) 새로운 노드 생성 후, head가 새로운 노드를 가리키게 함
        ll -> head = malloc(sizeof(ListNode));
        ll -> head -> item = value;

        // (3) 새로운 노드는 기존 머리노드 (cur)를 가리키게 함
        ll -> head -> next = cur;

        // (4) 연결리스트의 size를 1 증가
        ll -> size++;
        return 0;
    }

    // 0이 아닌 인덱스에 삽입하는 경우
    // (1) 삽입할 인덱스 직전 노드를 `pre`에 저장
    // 앞서 만든 findNode로 index-1번째 노드를 찾으면 됨
    if ((pre = findNode(ll, index - 1)) != NULL){
        // (1계속) 그리고 삽입할 인덱스의 노드는 `cur`에 저장
        // 당연히 `pre`의 다음 노드
        cur = pre -> next;

        // (2) 새로운 노드 생성 후, pre가 새로운 노드를 가리키게 함
        pre -> next = malloc(sizeof(ListNode));
        pre -> next -> item = value;

        // (3) 새로운 노드는 cur를 가리키게 함
        pre -> next -> next = cur;

        // (4) 연결리스트의 size를 1 증가
        ll -> size++;

        return 0;
    }

    // findNode 과정에서 NULL을 만나면 -1 반환
    return -1;
}

// 연결 리스트 ll의 index번째 노드를 제거
int removeNode(LinkedList *ll, int index){

    // pre는 이전 노드, cur은 현재 노드를 가리킴
    ListNode *pre, *cur;

    // 연결 리스트가 없거나, 인덱스가 범위를 벗어나는 경우
    if (ll == NULL || index < 0 || index >= ll -> size){
        return -1;
    }

    // 머리 노드를 제거하는 경우
    if (index == 0){
        // (1) 제거할 노드의 다음 노드를 cur로 설정
        cur = ll -> head -> next;

        // (2) 제거할 노드의 메모리 사용 해제
        free(ll -> head);

        // (3) ll -> head를 cur로 변경
        ll -> head = cur;

        // (4) 연결 리스트의 size를 1 감소
        ll -> size--;
        return 0;
    }

    // 머리 노드가 아닌 노드를 제거하는 경우

    // (1) 제거할 인덱스 직전 노드를 `pre`에 저장
    // 앞서 만든 findNode로 index-1번째 노드를 찾으면 됨
    if ((pre = findNode(ll, index - 1)) != NULL){
        
        // 제거할 인덱스의 노드가 NULL인 경우 삭제 불가
        // -1 반환
        if (pre -> next == NULL) return -1;

        // (1계속) 제거할 인덱스의 노드는 `cur`에 저장
        // 당연히 `pre`의 다음 노드
        cur = pre -> next;

        // (2) `pre -> next`가 `cur`의 다음 노드를 가리키게 함
        pre -> next = cur -> next;
        
        // (3) 삭제할 `cur`의 메모리 사용 해제
        free(cur);

        // (4) 연결 리스트의 size를 1 감소
        ll -> size--;

        return 0;
    }

    // 삭제에 실패
    return -1;
}

void printList(LinkedList *ll){
    // 연결리스트가 없는 경우
    if (ll == NULL) return;

    // 탐색하는 현재 노드
    // 머리 노드부터 시작
    ListNode *cur = ll -> head;

    // 연결 리스트가 비어 있을 때
    if (cur == NULL) printf("빈 리스트입니다.");

    // NULL을 만날 때까지 각 노드를 이동하며 값 출력
    while (cur != NULL){
        printf("%d ", cur -> item);
        cur = cur -> next;
    }
    printf("\n");
}

// 모든 노드를 삭제
void removeAllItems(LinkedList *ll)
{
	ListNode *cur = ll->head;   // 현재 노드
	ListNode *tmp;              // 다음 노드를 저장할 임시 변수

    // 모든 노드의 메모리 할당 해제
	while (cur != NULL){
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}
    
    // 머리 노드는 NULL, 연결리스트 크기는 0으로 
	ll -> head = NULL;
	ll -> size = 0;
}

int main(void){
    // size는 0, head는 NULL로 초기화
    LinkedList ll = {0, NULL};
    
    // 순서대로 노드 삽입
    insertNode(&ll, ll.size, 41);
    insertNode(&ll, ll.size, 9);
    insertNode(&ll, ll.size, 33);
    printList(&ll); // 41 9 33

    // 노드 10을 1번 인덱스에 삽입
    insertNode(&ll, 1, 10);
    printList(&ll); // 41 10 9 33

    // 2번 인덱스의 노드를 삭제
    removeNode(&ll, 2);
    printList(&ll); // 41 10 33

    // 메모리 해제(free) 위해 실행
    removeAllItems(&ll);

    return 0;
}