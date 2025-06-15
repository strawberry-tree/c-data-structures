정글 5주차 과제로는 기본적으로 제공하는 자료구조 구조체 및 함수를 이용해서, 다양한 응용문제를 풀게 됩니다.

블로그에서 모든 응용문제를 다루기보다는, 기본 제공 코드의 구조체 및 함수의 동작 원리만 분석할 계획입니다. 사실 이걸 제대로 알면 응용문제를 푸는 게 더 수월할 거에요.

- 따라서 **코드는 제가 직접 작성하진 않았고(약간의 수정은 있음) 정글에서 제공한 코드입니다**. 물론 주석, 설명이랑 그림은 제가 추가했습니다!

[큐에 대한 상세한 설명은 이 글을 참고해주세요](https://velog.io/@strawberry-tree/PS-%ED%81%90)

# 구조체 선언

- 본 코드에서는 [이전 글에서 구현한 **연결 리스트**를 이용](https://velog.io/@strawberry-tree/C-%EC%97%B0%EA%B2%B0-%EB%A6%AC%EC%8A%A4%ED%8A%B8-%EA%B5%AC%ED%98%84)해 큐를 구현
- 큐의 맨 앞(데이터를 꺼내는 쪽) 데이터가 머리 노드에 위치
  - **디큐 연산**: 연결 리스트의 머리 노드를 제거하면 됨
- 큐의 맨 뒤(데이터를 삽입하는 쪽) 데이터가 꼬리 노드에 위치
  - **인큐 연산**: 연결 리스트의 맨 뒤에 값을 추가하면 됨
- 현재 꼬리 노드에 바로 값을 삽입할 수 있게, `LinkedList` 구조체에 꼬리 노드를 가리키는 `tail` 포인터를 새로 추가

```c
// 각 노드를 나타내는 구조체 Node
typedef struct _listnode{
    int item;                   // 노드에 저장된 값
    struct _listnode *next;     // 다음 노드를 가리키는 포인터
} ListNode;

// 연결 리스트 전체를 나타내는 구조체 LinkedList
typedef struct _linkedlist{
    int size;                   // 연결 리스트의 원소 수
    ListNode *head;             // 머리 노드
    ListNode *tail;
} LinkedList;

// 큐를 나타내는 구조체 Queue
typedef struct _queue {
    LinkedList ll;
} Queue;
```

- 보통 함수는 `Queue *q`와 같이, `Queue` 구조체를 가리키는 포인터 `q`를 매개변수로 받음
- `q`는 포인터기 때문에, `q -> ll`을 이용해 연결 리스트에 접근
  - `(q -> ll).head`, `(q -> ll).tail`, `(q -> ll).size`을 이용해 `head`, `tail`, `size` 멤버에 접근

# 큐가 비어 있는지 확인
- 큐가 비어 있을 때 디큐를 하거나 맨 앞 값을 반환하는 오류를 막기 위해
- 큐가 비어 있는지 확인할 방법이 필요함

```c
int isEmptyQueue(Queue *q){
    // 원소 수가 0개거나 머리 / 꼬리 노드가 존재하지 않음
    if ((q -> ll).size < 1 || (q -> ll).head == NULL || (q -> ll).tail == NULL){
        return 1;   // 참, 비어 있음
    } else{
        return 0;   // 거짓, 비어 있지 않음
    }
}
```

- 큐의 원소 수가 1개 미만이거나 (`(q -> ll).size < 1`)
- 머리 혹은 꼬리 노드가 존재하지 않으면 (`(q -> ll).head == NULL`, `(q -> ll).tail == NULL`)
  - 큐가 비어 있으니 `1` 반환 (참)
  - 둘 중 하나만 체크해도 정상 작동하나, 혹시 모를 오류를 위해 둘 다 확인
- 비어 있지 않은 경우 `0` 반환 (거짓)

# 큐에 원소 인큐

- 기존의 `insertNode`는 지정한 인덱스에 도착할 때까지 모든 노드를 거친 후 삽입이 이루어짐
  - 맨 뒤 인덱스를 지정할 시, 꼬리 노드까지 이동한 뒤 삽입이 이루어져 $O(N)$이 소요됨
  - 따라서, 앞서 만들어 놓은 `insertNode` 함수를 사용하는 것은 비효율적
- $O(1)$의 시간 복잡도를 보장하기 위해, 꼬리 노드 다음에 바로 원소를 삽입하는 함수를 작성해야 함

```c
// 큐에 값 item을 인큐
void enqueue(Queue *q, int item){

  // 큐가 없는 경우 
  if (q == NULL) return;

  // 새로운 노드를 생성
  ListNode *newNode = malloc(sizeof(ListNode));
  newNode -> item = item;
  newNode -> next = NULL;

  // 꼬리 노드가 있는 경우
  if ((q -> ll).tail != NULL){
      // 현재 꼬리 노드의 다음 노드로 설정
      (q -> ll).tail -> next = newNode;
  } else {
      // 꼬리노드가 없으면, 빈 리스트
      // 머리노드로 설정
      (q -> ll).head = newNode;
  }

  // 새로운 노드를 꼬리노드로 설정
  (q -> ll).tail = newNode;
  (q -> ll).size++;
}
```
- `malloc`으로 새로운 노드 `newNode`를 생성
  - 맨 뒤에 갈 노드이기 때문에, `newNode -> next = NULL`로 저장
- 현재 꼬리 노드 (`(q -> ll).tail`)가 있는 경우
  - `(q -> ll).tail -> next = newNode`로, 기존 꼬리 노드의 다음 노드로 `newNode` 설정
- 현재 꼬리 노드가 없는 경우 (이 경우 빈 리스트)
  - 일단 빈 리스트이므로, 머리 노드부터 설정해야 함 (`(q -> ll).head = newNode`)
- 이후 `(q -> ll).tail = newNode`로, 새로운 노드를 꼬리 노드로 설정
- 마지막으로 `(q -> ll).size++`로 연결 리스트의 크기를 1 증가

# 큐에서 원소 디큐

- 디큐의 경우, 앞서 만든 연결 리스트에서 노드를 제거하는 `removeNode` 함수를 사용해도 무방
  - 머리 노드, 즉 0번째 인덱스의 노드를 제거하는 것이므로, 이동 없이 $O(1)$ 소요
- 단, 제거한 노드가 유일한 노드인 경우, 머리 노드이자 꼬리 노드가 제거되었으므로 `tail` 포인터를 `NULL`로 변경해 주어야 함
```c
// 큐의 맨 앞 값을 제거하고 반환
int dequeue(Queue *q){
    // 큐가 비어있지 않는 경우
    if (isEmptyQueue(q) == 0){
        // 머리노드의 값 저장
        int dequeue_value = (q -> ll).head -> item;
        // 0번째 노드 제거
        removeNode(&(q -> ll), 0);

        if ((q -> ll).size == 0 || (q -> ll).head == NULL){
          (q -> ll).tail = NULL;
        }
        return dequeue_value;
    } else {
        return -99999;  // 큐가 빈 경우 -99999 반환 (에러)
    } 
}
```
- 큐가 비어 있지 않은 경우 (앞서 만든 `isEmptyQueue` 사용)
  - 머리 노드의 값 (`(q -> ll).head -> item`)을 `dequeue_value`에 저장
  - `removeNode` 함수를 이용해 0번째 노드를 제거
  - 이후 `dequeue_value` 반환
- 유일한 노드를 삭제한 경우
  - `(q -> ll).tail = NULL`로 꼬리 노드가 제거되었음을 명시 
- 큐가 비어 있는 경우, 에러를 뜻하는 `-99999` 반환

# 큐의 맨 앞 값 반환
```c
// 큐의 맨 앞 값 확인
int queue_peek(Queue *q){
    // 큐가 비어있지 않는 경우 (머리 노드 존재)
    if (isEmptyQueue(q) == 0){
        // 머리노드의 값 반환
        return (q -> ll).head -> item;
    } else {
        return -99999;  // 스택이 빈 경우 -99999 반환 (에러)
    }
}
```
- `queue_peek`으로 함수 이름을 지은 이유
  - 앞선 스택 작성 글에 `peek`이라는 함수가 있었는데
  - 스택이랑 큐를 동시에 쓰는 경우도 있어, 중복되지 않도록 이름을 지었습니다
- 큐가 비어 있지 않은 경우 (앞서 만든 `isEmptyQueue` 사용)
  - 머리 노드의 값 (`(q -> ll).head -> item`)을 반환
- 큐가 비어 있는 경우, 에러를 뜻하는 `-99999` 반환

# 동작과정
```c
int main(void){
  Queue q;
  // 큐 내 연결 리스트의 size는 0, head, tail은 NULL로 초기화
  q.ll.size = 0;
  q.ll.head = NULL;
  q.ll.tail = NULL;

  // 큐에 인큐
  enqueue(&q, 10);
  enqueue(&q, 20);
  enqueue(&q, 30);

  // 큐에서 디큐
  printf("디큐한 원소: %d\n", dequeue(&q));
  // [출력] 디큐한 원소: 10

  // 다시 인큐
  enqueue(&q, 40);
  enqueue(&q, 50);

  // 맨 앞의 값 확인
  printf("맨 앞의 값: %d\n", queue_peek(&q));
  // [출력] 맨 앞의 값: 20
  
  // 현재 큐 확인
  printList(&(q.ll));
  // [출력] 20 30 40 50 (앞 -> 뒤 순서)

  // 큐의 크기 확인
  printf("큐의 크기: %d\n", q.ll.size);
  // [출력] 큐의 크기: 4

  return 0;
}

```
- 큐 내 연결 리스트의 크기는 0, 머리/꼬리 노드는 `NULL`로 초기화
- 전 글에서 만든 `printList` 함수로 연결 리스트의 주소(`&(q.ll)`)를 보내면 현재 큐를 출력할 수 있음
  - 앞 원소 -> 뒷 원소 순으로 출력됨에 유의하기
- 연결 리스트의 크기 (`q.ll.size`)로 스택의 크기를 확인할 수 있음
