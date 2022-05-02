/*
 *  doubly circular linked list
 *
 *  Data Structures
 *
 *  Department of Computer Science
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>
/* 필요한 헤더파일 추가 */

typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

/* 함수 리스트 */
int initialize(listNode** h);
int freeList(listNode* h);
int insertLast(listNode* h, int key);
int deleteLast(listNode* h);
int insertFirst(listNode* h, int key);
int deleteFirst(listNode* h);
int invertList(listNode* h);

int insertNode(listNode* h, int key);
int deleteNode(listNode* h, int key);

void printList(listNode* h);



int main()
{
	char command;
	int key;
	listNode* headnode=NULL;

	do{
		printf("[2019038059          윤태경              ");
		printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);//comaand 입력

		switch(command) {
		case 'z': case 'Z'://z나 Z를 입력했을떄 실행
			initialize(&headnode);
			break;
		case 'p': case 'P'://p나 P를 입력했을떄 실행
			printList(headnode);
			break;
		case 'i': case 'I'://i나 I를 입력했을떄 실행
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D'://d나 D를 입력했을떄 실행
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N'://n나 N를 입력했을떄 실행
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E'://e나 E를 입력했을떄 실행
			deleteLast(headnode);
			break;
		case 'f': case 'F'://f나 F를 입력했을떄 실행
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T'://t나 T를 입력했을떄 실행
			deleteFirst(headnode);
			break;
		case 'r': case 'R'://r나 R를 입력했을떄 실행
			invertList(headnode);
			break;
		case 'q': case 'Q'://q나 Q를 입력했을떄 실행
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}


int initialize(listNode** h) {//

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(*h != NULL)
		freeList(*h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h;//head노드의 rlink가 head노드를 가르킴
	(*h)->llink = *h;//head노드의 link가 head노드를  가르킴
	(*h)->key = -9999;//head노드의 key를 -9999로 초기화
	return 1;
}

int freeList(listNode* h){

	if(h->rlink == h)//헤드노드의 rlink가 헤드노드를 가르키면
	{
		free(h);//헤드노드 메모리 할당해제
		return 1;
	}

	listNode* p = h->rlink;//p에 헤드노드 다음노드 입력

	listNode* prev = NULL;
	while(p != NULL && p != h) {//p가 NUll이아니고 p가 헤드노드가 아니면
		prev = p;//prev에 p 입력
		p = p->rlink;//p에 p의 다음노드 입력
		free(prev);//prev 메모리 할당 헤재
	}
	free(h);
	return 0;
}



void printList(listNode* h) {//출력하는 함수
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {//헤드 노드가없으면
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink;//p에 헤드노드 다음 노드 입력

	while(p != NULL && p != h) {//p가 NULL이아니고 p가 h가 아니라면
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;//p에 P의 다음 노드 입력
		i++;//i를 증가
	}
	printf("  items = %d\n", i);


	/* print addresses */
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);

	i = 0;
	p = h->rlink;
	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		p = p->rlink;//p에 p의 다음 노드 입력
		i++;//i를 증가
	}

}



/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(listNode* h, int key) {

	if (h == NULL) return -1;//headnode가 NULL이면 

	listNode* node = (listNode*)malloc(sizeof(listNode));//key값을 받을 새로운 노드 메모리 할당
	node->key = key;// 새로운 노드의 key에 key값 대입
	node->rlink = NULL;//새로운 노드의 rlink는 NULL
	node->llink = NULL;//새로운 노드의 llink는 NULL

	if (h->rlink == h) /* 첫 노드로 삽입 */
	{
		h->rlink = node;//헤드노드의 rlink를 새로운 노드로 연결
		h->llink = node;//헤드노의 llink를 새로운 노드로 연결
		node->rlink = h;//새로운 노드의rlink를 헤드노드로 연결
		node->llink = h;//새로운 노드의llink를 헤드노드로 연결
	} else {//첫노드 삽입이 아닌경우
		h->llink->rlink = node;//마지막노드의rlink를 노드랑 연결
		node->llink = h->llink;//노드의 llink를 마지막노드랑 연결
		h->llink = node;//마지막노드를 노드랑 연결
		node->rlink = h;//노드의 rlink를 헤드노드랑 연결
	}

	return 1;
}


/**
 * list의 마지막 노드 삭제
 */
int deleteLast(listNode* h) {

	if (h->llink == h || h == NULL)
	{
		printf("nothing to delete.\n");
		return 1;
	}

	listNode* nodetoremove = h->llink;//nodetoremove가 마지막노드를 가르키게함

	/* link 정리 */
	nodetoremove->llink->rlink = h;//마지막노드의 이전노드 rlink를 헤드노드를 가르키게함
	h->llink = nodetoremove->llink;//헤드노드의 llink가 마지막노드의 llink와 연결

	free(nodetoremove);//nodetoremove메모리 할당 해제

	return 1;
}


/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(listNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));//새로운 노드 생성
	node->key = key;//노드의 key값에 입력받은 key값 대입
	node->rlink = NULL;//새로운 노드의 rlink는 NULL
	node->llink = NULL;//새로운 노드의 llink는 NULL


	node->rlink = h->rlink;//노드의 rlink를 첫번째노드와 연결
	h->rlink->llink = node;//첫번째노드의llink를 새로운 노드랑 연결
	node->llink = h;//노드의 llink를 헤드노드랑 연결
	h->rlink = node;//헤드노드의 rlink를 새로운 노드와 연결


	return 1;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(listNode* h) {

	if (h == NULL || h->rlink == h)
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* nodetoremove = h->rlink;// nodetoremove가 첫번쨰 노드가르키게 메모리 할당

	/* link 정리 */
	nodetoremove->rlink->llink = h;//첫번째노드의 다음노드 llink와 헤드 노드 연결
	h->rlink = nodetoremove->rlink;//헤드노드의 rlink에 첫번째 노드의 rlink 입력

	free(nodetoremove);// nodetoremove메모리 할당해제

	return 1;

}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(listNode* h) {


	if(h->rlink == h || h == NULL) {
		printf("nothing to invert...\n");
		return 0;
	}
	listNode *n = h->rlink;
	listNode *trail = h;
	listNode *middle = h;

	/* 최종 바뀔 링크 유지 */
	h->llink = h->rlink;//헤드노드의 rlink와 llink를 같게해줌

	while(n != NULL && n != h){
		trail = middle;//trail에 middle대입
		middle = n;//middle에 n대입
		n = n->rlink;//n에 n의 다음노드 대입
		middle->rlink = trail;//middle노드의 rlink를 trail을 연결
		middle->llink = n;//middle노드의 llink를 n을 연결
	}

	h->rlink = middle;//헤드노드의rlink를 middle연결

	return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(listNode* h, int key) {

	if(h == NULL) return -1;

	listNode* node = (listNode*)malloc(sizeof(listNode));//새로운 노드를 메모리할당해줌
	node->key = key;//노드의 key값에 입력받은 key값 대입
	node->llink = node->rlink = NULL;//새로운 노드의 rlink와 llink는 NULL

	if (h->rlink == h)//헤드노드의 rlink가 헤드노드를 가르키면 //즉 노드가 없으면
	{
		insertFirst(h, key);//노드가 없으므로 첫번째에 노드 삽입
		return 1;
	}

	listNode* n = h->rlink;//n은 첫번째노드 

	/* key를 기준으로 삽입할 위치를 찾는다 */
	while(n != NULL && n != h) {
		if(n->key >= key) {//n노드의 key값이 입력받은 key값보다 크거나 같은경우
			/* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
			if(n == h->rlink) {//n노드가 첫번째 노드인경우
				insertFirst(h, key);//첫번째에 삽입
			} else { /* 중간이거나 마지막인 경우 */
				node->rlink = n;//새로운노드 의 rlink가 n을 가르킴
				node->llink = n->llink;//새로운노드의 llink에 n의llink 대입
				n->llink->rlink = node;//n노드의 이전노드 rlink가 새로운 노드를 가르킴
				n->llink = node;//n노드의 이전노드가 새로운 노드를 가르킴
			}
			return 0;
		}

		n = n->rlink;//n은 n노드의다음노드로 바까줌
	}

	/* 마지막 노드까지 찾지 못한 경우, 마지막에 삽입 */
	insertLast(h, key);
	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(listNode* h, int key) {

	if (h->rlink == h || h == NULL)
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->rlink;//n은 첫번째노드 

	while(n != NULL && n != h) {
		if(n->key == key) {//n의 key값이랑 입력받은 key값이랑 같으면
			if(n == h->rlink) { /* 첫 노드째 노드 인경우 */
				deleteFirst(h);
			} else if (n->rlink == h){ /* 마지막 노드인 경우 */
				deleteLast(h);
			} else { /* 중간인 경우 */
				n->llink->rlink = n->rlink;//n노드의 이전노드 rlink가 n노드의 rlink가르킴
				n->rlink->llink = n->llink;//n노드의 다음도느 llink가 n노드의 llink가르킴
				free(n);
			}
			return 0;
		}

		n = n->rlink;//n은 n노드의다음노드로 바까줌
	}

	/* 찾지 못 한경우 */
	printf("cannot find the node for key = %d\n", key);
	return 0;
}


