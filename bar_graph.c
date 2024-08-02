#include "bar_graph.h"
#include "data.h"
#include "lvgl/lvgl.h"
#include "lvgl/src/misc/lv_area.h"
#include "lvgl/src/misc/lv_event.h"
#include "lvgl/src/misc/lv_palette.h"
#include "lvgl/src/widgets/chart/lv_chart.h"
#include "lvgl/src/widgets/scale/lv_scale.h"
#include "memory.h"
#include <stdio.h>



void init_bar_graph(BarGraph *graph) {
  graph->count = 0;
  graph->capacity = 0;
  graph->values = NULL;
  graph->series = NULL;
}

void write_bar_graph(BarGraph *graph, Value value) {
  if (graph->capacity < graph->count + 1) {
    int old_capacity = graph->capacity;
    graph->capacity = GROW_CAPACITY(old_capacity);
    graph->values =
        GROW_ARRAY(Value, graph->values, old_capacity, graph->capacity);
  }
  graph->values[graph->count] = value;
  graph->count++;
}

void free_bar_graph(BarGraph *graph) {
  FREE_ARRAY(Value, graph->values, graph->capacity);
  init_bar_graph(graph);
}


void show_bar_graph(BarGraph *graph) {
  lv_obj_t *main_cont = lv_obj_create(lv_screen_active());
  lv_obj_set_size(main_cont, LV_SIZE_CONTENT,500);
  lv_obj_center(main_cont);

  lv_obj_t *wrapper = lv_obj_create(main_cont);
  lv_obj_remove_style_all(wrapper);
  lv_obj_set_size(wrapper, LV_SIZE_CONTENT, lv_pct(100));
  lv_obj_set_flex_flow(wrapper, LV_FLEX_FLOW_COLUMN);

  lv_obj_t *chart = lv_chart_create(wrapper);
  lv_obj_set_width(chart,800);
  lv_obj_set_flex_grow(chart,1);
  lv_chart_set_type(chart,LV_CHART_TYPE_BAR);
  lv_chart_set_range(chart,LV_CHART_AXIS_PRIMARY_Y,0,1000);
  lv_chart_set_range(chart,LV_CHART_AXIS_SECONDARY_Y,0,1000);
  lv_chart_set_point_count(chart,graph->count);
  lv_obj_set_style_radius(chart,0,0);

  graph->chart = chart;

   lv_chart_series_t *ser1 = lv_chart_add_series(chart,lv_palette_lighten(LV_PALETTE_LIGHT_GREEN, 2),LV_CHART_AXIS_PRIMARY_Y);
  graph->series = ser1;

  for(int i=0;i<graph->count;i++){
    lv_chart_set_next_value(chart,ser1,graph->values[i]);
  }

  lv_chart_refresh(chart);
}
