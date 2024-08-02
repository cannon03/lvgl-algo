#ifndef algo_data_h
#define algo_data_h


#define GROW_ARRAY(type,pointer,old_capacity,new_capacity)\
(type*)reallocate(pointer,sizeof(type) * (old_capacity),\
		  sizeof(type) * (new_capacity))


#define FREE_ARRAY(type,pointer,old_capacity)\
reallocate(pointer,sizeof(type) * (old_capacity), 0)


typedef int Value;

typedef struct{
	int capacity;
	int count;
	Value *values;
}ValueArray;

typedef struct{
	int capacity;
	int curr;
	Value *values;
}ValueQueue;

void init_value_array(ValueArray* array);
void write_value_array(ValueArray *array,Value value);
void free_value_array(ValueArray *array);

void  init_value_queue(ValueQueue *queue);
void  push_value(ValueQueue *queue,Value value);
Value pop_value(ValueQueue *queue);
void  free_value_queue(ValueQueue *queue);

#endif
