정글 5주차 과제로는 기본적으로 구현된 재료구조 구조체 및 함수를 이용해서 다양한 응용문제를 풀게 됩니다.

블로그에서 모든 응용문제를 다루는 건 어려울 것 같고, 대신 자료구조 기초 동작의 뼈대를 이루는 구조체 및 함수의 동작 원리에 대해서만 분석할 계획입니다.

다만 어쩌다 제가 코어타임이나 목요일 때 발표를 맡은 응용문제에 대해서는 추가로 풀이를 쓰도록 하겠습니다.


[연결 리스트에 대한 상세한 설명은 이 글을 참고해주세요](https://velog.io/@strawberry-tree/PS-%EC%97%B0%EA%B2%B0-%EB%A6%AC%EC%8A%A4%ED%8A%B8)

# 구조체 선언

[사진]

```c
#include <stdio.h>
#include <stdlib.h>

// 각 노드를 나타내는 구조체 ListNode
typedef struct _listnode{
    int item;                   // 노드에 저장된 값
    struct _listnode *next;     // 다음 노드를 가리키는 포인터
} ListNode;

// 연결 리스트 전체를 나타내는 구조체 LinkedList
typedef struct _linkedlist{
    int size;                   // 연결 리스트의 원소 수
    ListNode *head;             // 머리 노드를 가리키는 포인터
} LinkedList;
```

- 연결 리스트는 각 노드가 다음 노드를 가리키는 구조
  - 따라서 `ListNode` 구조체에, 다음 노드를 가리키는 `ListNode *`형 포인터 `next`를 둠
  - 꼬리 노드라 다음 노드를 가리키지 않을 시, `next`의 값은 `NULL` (널 포인터)

- 머리 노드의 위치를 모르면 연결 리스트의 탐색을 할 수 없음
  - 따라서 `LinkedList` 구조체에, 머리 노드를 가리키는 `LinkedList *`형 포인터 `head`를 둠
  - 연결 리스트가 비어 있을 땐, 머리 노드가 없으므로 `head`의 값은 `NULL` (널 포인터)

# 특정 인덱스의 원소 찾기

- 머리 노드부터 차례로 찾고자 하는 위치의 노드까지 이동
- 도착하면 해당 노드를 반환

[사진]

```c
// 연결 리스트의 특정 인덱스 노드를 반환
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
```
- 리스트 내에서 이동할 때, 현재 노드를 가리키는 포인터 `temp` 선언
- `index`번째 요소를 찾기 위해선, 0번째 노드인 `head`부터 총 `index`번 이동해야 함
  - `while`문으로 `temp = temp -> next`로 다음 노드로 이동하며 - `index--`로 값을 1씩 감소시킴
- `index == 0`이 되었을 때 `temp`를 반환하여, 현재 위치의 노드 반환

# 노드 삽입
```c
// 연결 리스트 ll의 인덱스 index에 값 value 삽입
int insertNode(LinkedList *ll, int index, int value){

    // pre는 이전 노드, cur은 현재 노드를 가리킴
    ListNode *pre, *cur;

    // 연결 리스트가 없거나, 인덱스가 범위를 벗어나는 경우
    if (ll == NULL || index < 0 || index > ll->size + 1)
		return -1;

    // 이후 코드에 계속
}
```

- 노드를 삽입할 때도 연결 리스트에서 삽입할 위치까지 이동해야 함
  - 따라서 현재 노드를 가리키는 포인터 `cur`을 선언
- 추가로, 노드를 삽입할 땐 이전 노드의 `next` 포인터가 삽입된 노드를 가리키도록 변경해야 함
  - 따라서 현재 노드의 직전 노드를 가리키는 포인터 `pre` 역시 선언
- 이후 동작은, 삽입할 노드의 위치가 머리 (맨 앞)인지, 다른 위치인지에 따라 달라짐

## 머리 노드에 삽입할 때

[사진]

```c
int insertNode(LinkedList *ll, int index, int value){
    // 위 코드에서 계속

    // 리스트가 비어 있거나 머리에 삽입할 때 (index == 0)
    if (ll -> head == NULL || index == 0) {
        // (1) 현재 머리 노드를 cur에 저장
        cur = ll -> head;
        
        // (2) 새로운 노드 생성 후, 머리 노드를 새로운 노드로 변경
        ll -> head = malloc(sizeof(ListNode));
        ll -> head -> item = value;

        // (3) 새로운 노드는 기존 머리노드 (cur)를 가리키게 함
        ll -> head -> next = cur;

        // (4) 연결리스트의 size를 1 증가
        ll -> size++;
        return 0;
    }

    // 아래 코드에서 계속
}
```

- (1단계) 기존 머리 노드를 `cur`에 임시 저장
- (2단계) 새로운 노드를 생성 후, `ll -> head`를 생성한 노드로 변경
  - 생성 과정에서 `malloc(sizeof(ListNode))` 썼으니, 나중에 삭제 시 `free`해줘야 함!!
  - 이후 `ll -> head -> item`, `ll -> head -> next`로 새로운 노드의 멤버 설정 가능
- (3단계) 새로운 노드의 `next`가 기존 머리 노드 `cur`을 가리키게 연결
- (4단계) 연결리스트의 원소 수인 `ll -> size`를 1 증가

## 머리 노드가 아닌 위치에 삽입할 때

```c
int insertNode(LinkedList *ll, int index, int value){
    // 위 코드에서 계속

    // 0이 아닌 인덱스에 삽입하는 경우
    // (1) 삽입할 인덱스 직전 노드를 `pre`에 저장
    // 앞서 만든 findNode로 index-1번째 노드를 찾으면 됨
    if ((pre = findNode(ll, index - 1)) != NULL){
        // (1계속) 그리고 삽입할 인덱스의 노드는 `cur`에 저장
        // 당연히 `pre`의 다음 노드
        cur = pre -> next;

        // (2) 새로운 노드 생성 후, 인덱스 이전의 노드가 새로운 노드를 가리키게 함
        pre -> next = malloc(sizeof(ListNode));
        pre -> next -> item = value;

        // (3) 새로운 노드는 원래 인덱스의 노드를 가리키게 함
        pre -> next -> next = cur;

        // (4) 연결리스트의 size를 1 증가
        ll -> size++;

        return 0;
    }

    // findNode 과정에서 NULL을 만나면 -1 반환
    return -1;
}
```

- (1단계) 삽입할 인덱스의 직전 노드를 `pre`, 삽입할 인덱스의 기존 노드를 `cur`에 저장 
  - 앞서 **특정 인덱스의 원소 찾기**에서 구현한 `findIndex`로 `index-1`번째 노드를 찾아 `pre`를 구함
  - `cur`은 `pre`의 다음 노드
- (2단계) 새로운 노드를 생성 후, `pre -> next`가 생성한 노드를 가리키게 설정
  - 생성 과정에서 `malloc(sizeof(ListNode))` 썼으니, 나중에 삭제 시 `free`해줘야 함!!
  - 이후 `pre -> next -> item`, `pre -> next -> next`로 새로운 노드의 멤버 설정 가능
- (3단계) 새로운 노드의 `next`가 기존 위치의 `cur`을 가리키게 연결
- (4단계) 연결리스트의 원소 수인 `ll -> size`를 1 증가

**🫤 연결 리스트의 맨 끝에 삽입을 해도 정상 작동하나요? 이 경우 삽입할 위치에 아무것도 없으니 `cur`이 `NULL`이 될 것 같은데요.**
- 네, 정상 작동합니다.
- (3단계)에서 새 노드의 `next`를 `cur`로 설정하면, 결국 `NULL`이 저장되므로 새 노드가 꼬리 노드가 됩니다.
- 코드 내에서 `cur`을 `*` 연산자로 참조할 일이 없기 때문에, 널 포인터를 참조하는 오류는 발생하지 않습니다.

# 노드 삭제
```c
// 연결 리스트 ll의 index번째 노드를 제거
int removeNode(LinkedList *ll, int index){

    // pre는 이전 노드, cur은 현재 노드를 가리킴
    ListNode *pre, *cur;

    // 연결 리스트가 없거나, 인덱스가 범위를 벗어나는 경우
    if (ll == NULL || index < 0 || index >= ll -> size){
        return -1;
    }

    // 이후 코드에 계속
}
```

- 노드를 삭제할 때도 연결 리스트에서 삭제할 위치까지 이동해야 함
  - 따라서 현재 노드를 가리키는 포인터 `cur`을 선언
- 추가로, 노드를 삽입할 땐 이전 노드의 `next` 포인터가 삭제할 노드 다음의 노드를 가리키도록 변경해야 함
  - 따라서 현재 노드의 직전 노드를 가리키는 포인터 `pre` 역시 선언
- 이후 동작은, 삭제할 노드의 위치가 머리 (맨 앞)인지, 다른 위치인지에 따라 달라짐

## 머리 노드를 삭제할 때
```c
int removeNode(LinkedList *ll, int index){
    // 위 코드에서 계속
    // 머리 노드를 삭제하는 경우 (index == 0)
    if (index == 0){
        // (1) 삭제할 노드의 다음 노드를 cur에 저장
        cur = ll -> head -> next;

        // (2) 삭제할 노드의 메모리 사용 해제
        free(ll -> head);

        // (3) 머리 노드를, 삭제할 노드의 다음 노드로 변경
        ll -> head = cur;

        // (4) 연결 리스트의 size를 1 감소
        ll -> size--;
        return 0;
    }

    // 아래 코드에서 계속
}
```

- (1단계) 삭제할 노드의 다음 노드를 `cur`에 저장
  - 머리 노드 (`ll -> head`)를 삭제하므로, `cur`은 (`ll -> head -> next`)
- (2단계) 삭제할 노드의 메모리 사용 해제
  - 이전에 `malloc`으로 메모리를 할당했으니, `free`해 주어야 함
- (3단계) 머리 노드, 즉 `ll -> head`를 `cur`로 변경
- (4단계) 연결 리스트의 원소 수인 `ll -> size`를 1 감소

## 머리 노드가 아닌 위치의 노드를 삭제할 때
```c
// 연결 리스트 ll의 index번째 노드를 제거
int removeNode(LinkedList *ll, int index){
    // 위 코드에서 계속
    
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

        // (2) 삭제할 인덱스 직전 노드가, 삭제할 인덱스 다음 노드를 가리키게 함
        pre -> next = cur -> next;
        
        // (3) 삭제할 `cur`의 메모리 사용 해제
        free(cur);

        // (4) 연결 리스트의 size를 1 감소
        ll -> size--;

        return 0;
    }
}
```
- (1단계) 삭제할 인덱스 직전 노드를 `pre`에, 삭제할 노드를 `cur`에 저장
  - 앞서 **특정 인덱스의 원소 찾기**에서 구현한 `findIndex`로 `index-1`번째 노드를 찾아 `pre`를 구함
  - `cur`은 `pre`의 다음 노드
- (2단계) `pre -> next`에 `cur -> next`를 저장해, 삭제할 인덱스 직전 노드가 삭제할 인덱스 다음 노드를 가리키게 함
- (3단계) 삭제할 노드의 메모리 사용 해제
  - 이전에 `malloc`으로 메모리를 할당했으니, `free`해 주어야 함
- (4단계) 연결 리스트의 원소 수인 `ll -> size`를 1 감소

# 연결 리스트 출력
```c
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
```
- 연결 리스트를 탐색하면서, `NULL` 주소를 만날 때까지 각 값을 출력
- 현재 노드를 가리키는 포인터 `cur`을 두고, `cur -> item`으로 출력
- 그리고 `cur = cur -> next`로 다음 노드로 이동

# 동작과정
```c
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

    return 0;
}
```
- 연결 리스트의 크기는 0, 머리 노드는 `NULL`로 초기화
- 연결 리스트 맨 끝에 노드를 삽입할 땐, `ll.size`번째 인덱스에 삽입할 수 있음