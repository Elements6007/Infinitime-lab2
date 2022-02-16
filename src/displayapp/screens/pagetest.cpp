#include "displayapp/screens/pagetest.h"
#include "displayapp/DisplayApp.h"

using namespace Pinetime::Applications::Screens;

//taskRefresh = lv_task_create(RefreshTaskCallback, LV_DISP_DEF_REFR_PERIOD, LV_TASK_PRIO_MID, this);

pagetest::pagetest(DisplayApp* app) : Screen(app) {
  lv_obj_t* title = lv_label_create(lv_scr_act(), nullptr);
  lv_label_set_text_static(title, "My test application");
  lv_label_set_align(title, LV_LABEL_ALIGN_CENTER);
  lv_obj_align(title, lv_scr_act(), LV_ALIGN_CENTER, 0, 0);
}

pagetest::~pagetest() {
  lv_obj_clean(lv_scr_act());
}






