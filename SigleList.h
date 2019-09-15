#pragma once

#include <stdlib.h>

typedef int SListDataType;

// �����е�һ�����
typedef struct Node {
	SListDataType	value;	// ֵ
	struct Node *next;		// ��һ�����ĵ�ַ
}	Node, *NodePointer;

// Single List
typedef struct SList {
	Node *first;	// *head;		��һ�����ĵ�ַ
}	SList;

// ��ʼ�� / ����
void SListInit(SList *slist) {
	slist->first = NULL;
}

// �� / ɾ / �� / ��
// ͷ��
void SListPushFront(SList *slist, SListDataType v) {
	// 1. �����½��
	Node *node = (Node *)malloc(sizeof(Node));
	node->value = v;

	// ��������Ĺ�ϵ
	node->next = slist->first;
	slist->first = node;
	// �����������ͷǿ�������һ���Ĵ���
}

void SListPushFrontVersion2(Node **ppFirst, SListDataType v) {
	Node *node = (Node *)malloc(sizeof(Node));
	node->value = v;

	node->next = *ppFirst;
	*ppFirst = node;
}

void SListPushBack(SList *slist, SListDataType v) {
	Node *node = (Node *)malloc(sizeof(Node));
	node->value = v;
	node->next = NULL;

	if (slist->first == NULL) {
		slist->first = node;
	}
	else {
		// ��ԭ����������һ�����
		Node *c = slist->first;
		while (c->next != NULL) {
			c = c->next;
		}
		// ѭ��������c->next һ���� NULL��Ҳ���� c �����һ�����
		c->next = node;
	}
}

// O(n)
void SListPushBackPractice(SList *slist, SListDataType v) {
	Node *n = (Node *)malloc(sizeof(Node));
	n->value = v;
	n->next = NULL;
	if (slist->first == NULL) {
		slist->first = n;
	}
	else {
		Node *c = slist->first;
		while (c->next != NULL) {
			c = c->next;
		}
		c->next = n;
	}
}

// O(n)
void SListPopBack(SList *s) {
	// �ų���������һ����㶼û�е����
	assert(s->first != NULL);

	if (s->first->next == NULL) {
		// ֻ��һ�����
		free(s->first);
		s->first = NULL;
		return;
	}

	// �ҵ����ڶ������
	Node *c;
	for (c = s->first; c->next->next != NULL; c = c->next);
	free(c->next);
	c->next = NULL;
}

Node * SListFind(SList *s, SListDataType v) {
	for (Node *c = s->first; c != NULL; c = c->next) {
		if (c->value == v) {
			return c;
		}
	}

	return NULL;
}

void SListInsertAfter(SList *s, Node *pos, SListDataType v) {
	Node *node = (Node *)malloc(sizeof(Node));
	node->value = v;
	node->next = pos->next;
	pos->next = node;
}

void SListEraseAfter(SList *s, Node *pos) {
	Node *next = pos->next->next;
	free(pos->next);
	pos->next = next;
}

void SListRemove(SList *s, SListDataType v) {
	if (s->first == NULL) {
		return;
	}
	if (s->first->value == v) {
		Node *second = s->first->next;	// ��¼ԭ���ĵڶ������
		free(s->first);					// �ͷŵ�һ�����ռ�
		s->first = second;				// ԭ���ĵڶ���������һ����
	}
	else {
		Node *c = s->first;
		while (c->next != NULL) {
			if (c->next->value == v) {
				Node *next = c->next;
				c->next = c->next->next;
				free(next);
				return;
			}

			c = c->next;
		}
	}
}

void SListRemoveAll(SList *s, SListDataType v) {
	if (s->first == NULL) {
		return;
	}

	Node *c = s->first;
	while (c->next != NULL) {
		if (c->next->value == v) {
			Node *next = c->next;
			c->next = c->next->next;
			free(next);
		}
		else {
			c = c->next;
		}
	}
	// ���˵�һ��û�м���

	if (s->first->value == v) {
		// ͷɾ
		Node *first = s->first;
		s->first = s->first->next;
		free(first);
	}
}