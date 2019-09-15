#pragma once

#include <stdlib.h>

typedef int SListDataType;

// 链表中的一个结点
typedef struct Node {
	SListDataType	value;	// 值
	struct Node *next;		// 下一个结点的地址
}	Node, *NodePointer;

// Single List
typedef struct SList {
	Node *first;	// *head;		第一个结点的地址
}	SList;

// 初始化 / 销毁
void SListInit(SList *slist) {
	slist->first = NULL;
}

// 增 / 删 / 查 / 改
// 头插
void SListPushFront(SList *slist, SListDataType v) {
	// 1. 申请新结点
	Node *node = (Node *)malloc(sizeof(Node));
	node->value = v;

	// 更改链表的关系
	node->next = slist->first;
	slist->first = node;
	// 考虑完空链表和非空链表都是一样的处理
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
		// 找原来链表的最后一个结点
		Node *c = slist->first;
		while (c->next != NULL) {
			c = c->next;
		}
		// 循环结束，c->next 一定是 NULL，也就是 c 是最后一个结点
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
	// 排除掉链表中一个结点都没有的情况
	assert(s->first != NULL);

	if (s->first->next == NULL) {
		// 只有一个结点
		free(s->first);
		s->first = NULL;
		return;
	}

	// 找倒数第二个结点
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
		Node *second = s->first->next;	// 记录原来的第二个结点
		free(s->first);					// 释放第一个结点空间
		s->first = second;				// 原来的第二个升级第一个了
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
	// 除了第一个没有检查过

	if (s->first->value == v) {
		// 头删
		Node *first = s->first;
		s->first = s->first->next;
		free(first);
	}
}