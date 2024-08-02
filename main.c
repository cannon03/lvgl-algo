#include "lvgl/src/core/lv_refr.h"
#include "tree.h"
#include "bar_graph.h"
#include "lvgl/src/misc/lv_area.h"
#include "lvgl/src/widgets/chart/lv_chart.h"
#include "sorting/sorting.h"
#include "lvgl/lvgl.h"
#include "lvgl/src/core/lv_group.h"
#include "lvgl/src/display/lv_display.h"
#include "lvgl/src/drivers/sdl/lv_sdl_mouse.h"

#include <stdio.h>
#include <string.h>
#include <unistd.h>


BarGraph graph;


int data_sample[3][20] = {{
                           179, 167, 53,  10, 158, 126, 21,  150, 9,  59,
                           27,  95,  102, 86, 46,  77,  191, 122, 89, 25,
                       },
                       {
                           97,  109, 298, 229, 253, 72,  133, 51,  193, 159,
                           260, 233, 165, 147, 111, 145, 180, 128, 226, 244,
                       },
                       {
                           99,  161, 117, 130, 157, 98,  134, 159, 96,  111,
                           199, 195, 193, 175, 113, 118, 142, 121, 115, 127,
                       }};



static void hal_init(void) {
  const int width = 800;
  const int height = 800;
  lv_display_t *disp = lv_sdl_window_create(width, height);

  lv_indev_t *mouse = lv_sdl_mouse_create();
  lv_indev_set_group(mouse,lv_group_get_default());
  lv_indev_set_display(mouse,disp);
  lv_display_set_default(disp);
}

void show_values(){
  for(int i = 0;i < graph.count ; i++){
    printf("%d   %d \n",graph.series->y_points[i],graph.values[i]);
  }
  printf("-----------------------------END-------------------------------------  \n");
}

static void event_handler(lv_event_t *e) {
  lv_event_code_t code = lv_event_get_code(e);

  if (code == LV_EVENT_CLICKED) {
    LV_LOG_USER("Clicked");
  } else if (code == LV_EVENT_VALUE_CHANGED) {
    LV_LOG_USER("Toggled");
  }
}
void lv_example_button_1(void) {
  lv_obj_t *label;

  lv_obj_t *btn1 = lv_button_create(lv_screen_active());
  lv_obj_add_event_cb(btn1, event_handler, LV_EVENT_ALL, NULL);
  lv_obj_align(btn1, LV_ALIGN_CENTER, 0, -40);
  lv_obj_remove_flag(btn1, LV_OBJ_FLAG_PRESS_LOCK);

  label = lv_label_create(btn1);
  lv_label_set_text(label, "Button");
  lv_obj_center(label);

  lv_obj_t *btn2 = lv_button_create(lv_screen_active());
  lv_obj_add_event_cb(btn2, event_handler, LV_EVENT_ALL, NULL);
  lv_obj_align(btn2, LV_ALIGN_CENTER, 0, 40);
  lv_obj_add_flag(btn2, LV_OBJ_FLAG_CHECKABLE);
  lv_obj_set_height(btn2, LV_SIZE_CONTENT);

  label = lv_label_create(btn2);
  lv_label_set_text(label, "Toggle");
  lv_obj_center(label);
}
static void swap_values(Value *v1,Value *v2){
  int i1,i2;
  i1 = v1 - graph.values;
  i2 = v2 - graph.values;
  Value temp = *v1;
  graph.series->y_points[i1] = *v2;
  graph.series->y_points[i2] = *v1;
  *v1 = *v2;
  *v2 = temp;
  lv_chart_refresh(graph.chart);
  lv_refr_now(NULL);
  usleep(20000);
}

static void sort_event(lv_event_t *e){
  bubble_sort(graph.values, graph.count, swap_values);
  show_values();
}

void sort_button(){

  lv_obj_t *label;

  lv_obj_t *btn = lv_button_create(lv_screen_active());
  lv_obj_add_event_cb(btn,sort_event,LV_EVENT_CLICKED,NULL);
  lv_obj_align(btn,LV_ALIGN_TOP_MID,0,0);
  lv_obj_set_height(btn,LV_SIZE_CONTENT);

  label = lv_label_create(btn);
  lv_label_set_text(label,"SORT");
  lv_obj_center(label);
}
int main(void) {
  lv_init();

  hal_init();

  sort_button();

  Value values[12] = {12,8,9,11,10,7,2,3,5,4,6,1};
  graph.count = 20;
  graph.capacity = 32;
  graph.values = data_sample[0];
  show_bar_graph(&graph);
  show_values();
 // show_tree();
  while(1){
    lv_timer_handler();
    usleep(50);
  }

  return 0;
}
