#include "memory.h"
#include <stdio.h>
#include "data.h"


void init_value_array(ValueArray *array){
	array->values = NULL;
	array->capacity = 0;
	array->count = 0;
}
void init_value_queue(ValueQueue *queue){
	queue->values = NULL;
	queue->capacity = 0;
	queue->curr = 0;
}
void write_value_array(ValueArray *array, Value value){
	if (array->capacity < array->count +1){
		int old_capacity = array->capacity;
		array->capacity = GROW_CAPACITY(old_capacity);
		array->values = GROW_ARRAY(Value,array->values, old_capacity, array->capacity);
	}
	array->values[array->count] = value;
	array->count++;
}

void push_value(ValueQueue *queue,Value value){
	if (queue->capacity < queue->curr + 1){
		int old_capacity = queue->capacity;
		queue->capacity = GROW_CAPACITY(old_capacity);
		queue->values = GROW_ARRAY(Value, queue->values, old_capacity, queue->capacity);
	}
	queue->values[queue->curr] = value;
	queue->curr++;
}
Value pop_value(ValueQueue *queue){
	if (queue->curr == 0){
		return -1;
	}
	return queue->values[queue->curr--];
}

void free_value_array(ValueArray *array){
	FREE_ARRAY(Value, array->values, array->capacity);
}

void free_value_queue(ValueQueue *queue){
	FREE_ARRAY(Value, queue->values, queue->capacity);
}


