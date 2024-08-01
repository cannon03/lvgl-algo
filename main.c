#include "bar_graph.h"

#include "lvgl/lvgl.h"
#include "lvgl/src/core/lv_group.h"
#include "lvgl/src/display/lv_display.h"
#include "lvgl/src/drivers/sdl/lv_sdl_mouse.h"

#include <stdio.h>
#include <unistd.h>

static void hal_init(void) {
  const int width = 800;
  const int height = 800;
  lv_display_t *disp = lv_sdl_window_create(width, height);

  lv_indev_t *mouse = lv_sdl_mouse_create();
  lv_indev_set_group(mouse,lv_group_get_default());
  lv_indev_set_display(mouse,disp);
  lv_display_set_default(disp);
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

static void swap_event(lv_event_t *e){
  printf("");
}

void sort_button(){

  lv_obj_t *label;

  lv_obj_t *btn = lv_button_create(lv_screen_active());
  lv_obj_add_event_cb(btn,swap_event,LV_EVENT_CLICKED,NULL);
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

  BarGraph graph;
  Value values[12] = {12,8,9,11,10,7,2,3,5,4,6,1};
  graph.count = 12;
  graph.capacity = 16;
  graph.values = values;
  show_bar_graph(&graph);
  while(1){
    lv_timer_handler();
    usleep(5*1000);
  }
  return 0;
}
