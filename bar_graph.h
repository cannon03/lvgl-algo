#ifndef algo_bargraph_h
#define algo_bargraph_h

#include "memory.h"
#include "data.h"

typedef struct{
	int count;
	int capacity;
	Value *values;
}BarGraph;

void init_bar_graph(BarGraph *graph);
void write_bar_graph(BarGraph *graph,Value value);
void free_bar_graph(BarGraph *graph);


void show_bar_graph(BarGraph *graph);

#endif



