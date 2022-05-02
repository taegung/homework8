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
/* �ʿ��� ������� �߰� */

typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

/* �Լ� ����Ʈ */
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
		printf("[2019038059          ���°�              ");
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
		scanf(" %c", &command);//comaand �Է�

		switch(command) {
		case 'z': case 'Z'://z�� Z�� �Է������� ����
			initialize(&headnode);
			break;
		case 'p': case 'P'://p�� P�� �Է������� ����
			printList(headnode);
			break;
		case 'i': case 'I'://i�� I�� �Է������� ����
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D'://d�� D�� �Է������� ����
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N'://n�� N�� �Է������� ����
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E'://e�� E�� �Է������� ����
			deleteLast(headnode);
			break;
		case 'f': case 'F'://f�� F�� �Է������� ����
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T'://t�� T�� �Է������� ����
			deleteFirst(headnode);
			break;
		case 'r': case 'R'://r�� R�� �Է������� ����
			invertList(headnode);
			break;
		case 'q': case 'Q'://q�� Q�� �Է������� ����
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

	/* headNode�� NULL�� �ƴϸ�, freeNode�� ȣ���Ͽ� �Ҵ�� �޸� ��� ���� */
	if(*h != NULL)
		freeList(*h);

	/* headNode�� ���� �޸𸮸� �Ҵ��Ͽ� ���� */
	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h;//head����� rlink�� head��带 ����Ŵ
	(*h)->llink = *h;//head����� link�� head��带  ����Ŵ
	(*h)->key = -9999;//head����� key�� -9999�� �ʱ�ȭ
	return 1;
}

int freeList(listNode* h){

	if(h->rlink == h)//������� rlink�� ����带 ����Ű��
	{
		free(h);//����� �޸� �Ҵ�����
		return 1;
	}

	listNode* p = h->rlink;//p�� ����� ������� �Է�

	listNode* prev = NULL;
	while(p != NULL && p != h) {//p�� NUll�̾ƴϰ� p�� ����尡 �ƴϸ�
		prev = p;//prev�� p �Է�
		p = p->rlink;//p�� p�� ������� �Է�
		free(prev);//prev �޸� �Ҵ� ����
	}
	free(h);
	return 0;
}



void printList(listNode* h) {//����ϴ� �Լ�
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {//��� ��尡������
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink;//p�� ����� ���� ��� �Է�

	while(p != NULL && p != h) {//p�� NULL�̾ƴϰ� p�� h�� �ƴ϶��
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;//p�� P�� ���� ��� �Է�
		i++;//i�� ����
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
		p = p->rlink;//p�� p�� ���� ��� �Է�
		i++;//i�� ����
	}

}



/**
 * list�� key�� ���� ����ϳ��� �߰�
 */
int insertLast(listNode* h, int key) {

	if (h == NULL) return -1;//headnode�� NULL�̸� 

	listNode* node = (listNode*)malloc(sizeof(listNode));//key���� ���� ���ο� ��� �޸� �Ҵ�
	node->key = key;// ���ο� ����� key�� key�� ����
	node->rlink = NULL;//���ο� ����� rlink�� NULL
	node->llink = NULL;//���ο� ����� llink�� NULL

	if (h->rlink == h) /* ù ���� ���� */
	{
		h->rlink = node;//������� rlink�� ���ο� ���� ����
		h->llink = node;//������ llink�� ���ο� ���� ����
		node->rlink = h;//���ο� �����rlink�� ������ ����
		node->llink = h;//���ο� �����llink�� ������ ����
	} else {//ù��� ������ �ƴѰ��
		h->llink->rlink = node;//�����������rlink�� ���� ����
		node->llink = h->llink;//����� llink�� ���������� ����
		h->llink = node;//��������带 ���� ����
		node->rlink = h;//����� rlink�� ������ ����
	}

	return 1;
}


/**
 * list�� ������ ��� ����
 */
int deleteLast(listNode* h) {

	if (h->llink == h || h == NULL)
	{
		printf("nothing to delete.\n");
		return 1;
	}

	listNode* nodetoremove = h->llink;//nodetoremove�� ��������带 ����Ű����

	/* link ���� */
	nodetoremove->llink->rlink = h;//����������� ������� rlink�� ����带 ����Ű����
	h->llink = nodetoremove->llink;//������� llink�� ����������� llink�� ����

	free(nodetoremove);//nodetoremove�޸� �Ҵ� ����

	return 1;
}


/**
 * list ó���� key�� ���� ����ϳ��� �߰�
 */
int insertFirst(listNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));//���ο� ��� ����
	node->key = key;//����� key���� �Է¹��� key�� ����
	node->rlink = NULL;//���ο� ����� rlink�� NULL
	node->llink = NULL;//���ο� ����� llink�� NULL


	node->rlink = h->rlink;//����� rlink�� ù��°���� ����
	h->rlink->llink = node;//ù��°�����llink�� ���ο� ���� ����
	node->llink = h;//����� llink�� ������ ����
	h->rlink = node;//������� rlink�� ���ο� ���� ����


	return 1;
}

/**
 * list�� ù��° ��� ����
 */
int deleteFirst(listNode* h) {

	if (h == NULL || h->rlink == h)
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* nodetoremove = h->rlink;// nodetoremove�� ù���� ��尡��Ű�� �޸� �Ҵ�

	/* link ���� */
	nodetoremove->rlink->llink = h;//ù��°����� ������� llink�� ��� ��� ����
	h->rlink = nodetoremove->rlink;//������� rlink�� ù��° ����� rlink �Է�

	free(nodetoremove);// nodetoremove�޸� �Ҵ�����

	return 1;

}


/**
 * ����Ʈ�� ��ũ�� �������� �� ��ġ
 */
int invertList(listNode* h) {


	if(h->rlink == h || h == NULL) {
		printf("nothing to invert...\n");
		return 0;
	}
	listNode *n = h->rlink;
	listNode *trail = h;
	listNode *middle = h;

	/* ���� �ٲ� ��ũ ���� */
	h->llink = h->rlink;//������� rlink�� llink�� ��������

	while(n != NULL && n != h){
		trail = middle;//trail�� middle����
		middle = n;//middle�� n����
		n = n->rlink;//n�� n�� ������� ����
		middle->rlink = trail;//middle����� rlink�� trail�� ����
		middle->llink = n;//middle����� llink�� n�� ����
	}

	h->rlink = middle;//�������rlink�� middle����

	return 0;
}



/* ����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ���� */
int insertNode(listNode* h, int key) {

	if(h == NULL) return -1;

	listNode* node = (listNode*)malloc(sizeof(listNode));//���ο� ��带 �޸��Ҵ�����
	node->key = key;//����� key���� �Է¹��� key�� ����
	node->llink = node->rlink = NULL;//���ο� ����� rlink�� llink�� NULL

	if (h->rlink == h)//������� rlink�� ����带 ����Ű�� //�� ��尡 ������
	{
		insertFirst(h, key);//��尡 �����Ƿ� ù��°�� ��� ����
		return 1;
	}

	listNode* n = h->rlink;//n�� ù��°��� 

	/* key�� �������� ������ ��ġ�� ã�´� */
	while(n != NULL && n != h) {
		if(n->key >= key) {//n����� key���� �Է¹��� key������ ũ�ų� �������
			/* ù ��� ���ʿ� �����ؾ��� ��� ���� �˻� */
			if(n == h->rlink) {//n��尡 ù��° ����ΰ��
				insertFirst(h, key);//ù��°�� ����
			} else { /* �߰��̰ų� �������� ��� */
				node->rlink = n;//���ο��� �� rlink�� n�� ����Ŵ
				node->llink = n->llink;//���ο����� llink�� n��llink ����
				n->llink->rlink = node;//n����� ������� rlink�� ���ο� ��带 ����Ŵ
				n->llink = node;//n����� ������尡 ���ο� ��带 ����Ŵ
			}
			return 0;
		}

		n = n->rlink;//n�� n����Ǵ������� �ٱ���
	}

	/* ������ ������ ã�� ���� ���, �������� ���� */
	insertLast(h, key);
	return 0;
}


/**
 * list���� key�� ���� ��� ����
 */
int deleteNode(listNode* h, int key) {

	if (h->rlink == h || h == NULL)
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->rlink;//n�� ù��°��� 

	while(n != NULL && n != h) {
		if(n->key == key) {//n�� key���̶� �Է¹��� key���̶� ������
			if(n == h->rlink) { /* ù ���° ��� �ΰ�� */
				deleteFirst(h);
			} else if (n->rlink == h){ /* ������ ����� ��� */
				deleteLast(h);
			} else { /* �߰��� ��� */
				n->llink->rlink = n->rlink;//n����� ������� rlink�� n����� rlink����Ŵ
				n->rlink->llink = n->llink;//n����� �������� llink�� n����� llink����Ŵ
				free(n);
			}
			return 0;
		}

		n = n->rlink;//n�� n����Ǵ������� �ٱ���
	}

	/* ã�� �� �Ѱ�� */
	printf("cannot find the node for key = %d\n", key);
	return 0;
}


