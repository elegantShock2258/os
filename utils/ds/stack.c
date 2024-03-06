

struct Stack {
	void* top;
	unsigned capacity;
	void** array;
};

struct Stack createStack(unsigned capacity)
{
  void** array[capacity];
  struct Stack stack = {0,capacity,array};
  return stack;
}

int isFull(struct Stack* stack)
{
	return stack->top == stack->capacity - 1;
}
int isEmpty(struct Stack* stack)
{
	return stack->top == -1;
}

void push(struct Stack* stack, int item)
{
	if (isFull(stack))
		return;
	stack->array[++stack->top] = item;
	printf("%d pushed to stack\n", item);
}

int pop(struct Stack* stack)
{
	if (isEmpty(stack))
		return INT_MIN;
	return stack->array[stack->top--];
}

int peek(struct Stack* stack)
{
	if (isEmpty(stack))
		return INT_MIN;
	return stack->array[stack->top];
}
