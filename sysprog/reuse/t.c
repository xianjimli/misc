typedef int Type;
typedef struct _DListNode
{
	struct _DListNode* prev;
	struct _DListNode* next;
	Type data;
}DListNode;

typedef struct _DListNode
{
	struct _DListNode* prev;
	struct _DListNode* next;
	void*  data;
	size_t length;
}DListNode;

typedef struct _DListNode
{
	struct _DListNode* prev;
	struct _DListNode* next;
	void*  data;
}DListNode;
