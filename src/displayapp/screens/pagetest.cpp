#include "displayapp/screens/pagetest.h"

#include "displayapp/screens/Screen.h"
#include "displayapp/DisplayApp.h"
#include "displayapp/screens/Label.h"
#include "displayapp/screens/Symbols.h"

using namespace Pinetime::Applications::Screens;

pagetest::pagetest(Pinetime::Applications::DisplayApp* app) 
  : Screen(app),
    screens {app,
             0,
             {[this]() -> std::unique_ptr<Screen> {
               return CreateScreen1();
              },
              [this]() -> std::unique_ptr<Screen> {
                return CreateScreen2();
              }},
              Screens::ScreenListModes::UpDown} {
}

std::unique_ptr<Screen> pagetest::CreateScreen1() {
 
  onion = lv_label_create(lv_scr_act(), nullptr);
  lv_label_set_text(onion, Symbols::phone);
  lv_obj_align(onion, lv_scr_act(), LV_ALIGN_IN_TOP_RIGHT, 0, 0);
  
  obama = lv_label_create(lv_scr_act(), nullptr);
  lv_label_set_text(obama, Symbols::home);
  lv_obj_align(obama, lv_scr_act(), LV_ALIGN_CENTER, 0, 0);


  return std::make_unique<Screens::Label>(0, 2, app, onion);
}


std::unique_ptr<Screen> pagetest::CreateScreen2() {

  title = lv_label_create(lv_scr_act(), nullptr);
  lv_label_set_text(title, Symbols::phone);
  lv_obj_align(title, lv_scr_act(), LV_ALIGN_CENTER, 0, 0);

  return std::make_unique<Screens::Label>(1, 2, app, title);
}


pagetest::~pagetest() {
  lv_obj_clean(lv_scr_act());
}

bool pagetest::OnTouchEvent(Pinetime::Applications::TouchEvents event) {
  return screens.OnTouchEvent(event);
}




