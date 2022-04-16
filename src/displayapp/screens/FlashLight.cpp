
#include "displayapp/screens/FlashLight.h"
#include "displayapp/DisplayApp.h"
#include "displayapp/screens/Symbols.h"
#include "components/settings/Settings.h"
#include "components/brightness/BrightnessController.h"

using namespace Pinetime::Applications::Screens;

namespace {
  void event_handler(lv_obj_t* obj, lv_event_t event) {
    auto* screen = static_cast<FlashLight*>(obj->user_data);
    screen->OnClickEvent(obj, event);
  }
}

FlashLight::FlashLight(Pinetime::Applications::DisplayApp* app,
                       System::SystemTask& systemTask,
                       Controllers::BrightnessController& brightnessController,
                       Controllers::Settings& settingsController)
  : Screen(app),
    systemTask {systemTask},
    brightnessController {brightnessController},
    settingsController {settingsController}

{
  brightnessController.Backup();

  brightnessLevel = brightnessController.Level();

  flashLight = lv_label_create(lv_scr_act(), nullptr);
  lv_obj_set_style_local_text_font(flashLight, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &lv_font_sys_48);
  lv_label_set_text_static(flashLight, Symbols::highlight);
  lv_obj_align(flashLight, nullptr, LV_ALIGN_CENTER, 0, 0);

  for (auto & i : indicators) {
    i = lv_obj_create(lv_scr_act(), nullptr);
    lv_obj_set_size(i, 15, 10);
    lv_obj_set_style_local_border_width(i, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, 2);
  }

  lv_obj_align(indicators[1], flashLight, LV_ALIGN_OUT_BOTTOM_MID, 0, 5);
  lv_obj_align(indicators[0], indicators[1], LV_ALIGN_OUT_LEFT_MID, -8, 0);
  lv_obj_align(indicators[2], indicators[1], LV_ALIGN_OUT_RIGHT_MID, 8, 0);

  SetIndicators();
  SetColors();

  backgroundAction = lv_label_create(lv_scr_act(), nullptr);
  lv_label_set_long_mode(backgroundAction, LV_LABEL_LONG_CROP);
  lv_obj_set_size(backgroundAction, 240, 240);
  lv_obj_set_pos(backgroundAction, 0, 0);
  lv_label_set_text(backgroundAction, "");
  lv_obj_set_click(backgroundAction, true);
  backgroundAction->user_data = this;
  lv_obj_set_event_cb(backgroundAction, event_handler);

  systemTask.PushMessage(Pinetime::System::Messages::DisableSleeping);
}

FlashLight::~FlashLight() {
  lv_obj_clean(lv_scr_act());
  lv_obj_set_style_local_bg_color(lv_scr_act(), LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_BLACK);
  settingsController.SaveSettings();
  brightnessController.Restore();
  systemTask.PushMessage(Pinetime::System::Messages::EnableSleeping);
}

void FlashLight::SetColors() {
  if (isOn) {
    lv_obj_set_style_local_bg_color(lv_scr_act(), LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_WHITE);
    lv_obj_set_style_local_text_color(flashLight, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_GRAY);
    for (auto & i : indicators) {
      lv_obj_set_style_local_bg_color(i, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_GRAY);
      lv_obj_set_style_local_bg_color(i, LV_OBJ_PART_MAIN, LV_STATE_DISABLED, LV_COLOR_WHITE);
      lv_obj_set_style_local_border_color(i, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_GRAY);
    }
  } else {
    lv_obj_set_style_local_bg_color(lv_scr_act(), LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_BLACK);
    lv_obj_set_style_local_text_color(flashLight, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_WHITE);
    for (auto & i : indicators) {
      lv_obj_set_style_local_bg_color(i, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_WHITE);
      lv_obj_set_style_local_bg_color(i, LV_OBJ_PART_MAIN, LV_STATE_DISABLED, LV_COLOR_BLACK);
      lv_obj_set_style_local_border_color(i, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_WHITE);
    }
  }
}

void FlashLight::SetIndicators() {
  using namespace Pinetime::Controllers;

  if (brightnessLevel == BrightnessController::Levels::High) {
    lv_obj_set_state(indicators[1], LV_STATE_DEFAULT);
    lv_obj_set_state(indicators[2], LV_STATE_DEFAULT);
  } else if (brightnessLevel == BrightnessController::Levels::Medium) {
    lv_obj_set_state(indicators[1], LV_STATE_DEFAULT);
    lv_obj_set_state(indicators[2], LV_STATE_DISABLED);
  } else {
    lv_obj_set_state(indicators[1], LV_STATE_DISABLED);
    lv_obj_set_state(indicators[2], LV_STATE_DISABLED);
  }
}

void FlashLight::OnClickEvent(lv_obj_t* obj, lv_event_t event) {
  if (obj == backgroundAction && event == LV_EVENT_CLICKED) {
    isOn = !isOn;
    SetColors();
  }
}

bool FlashLight::OnTouchEvent(Pinetime::Applications::TouchEvents event) {
  using namespace Pinetime::Controllers;

  if (event == TouchEvents::SwipeLeft) {
    if (brightnessLevel == BrightnessController::Levels::High) {
      brightnessLevel = BrightnessController::Levels::Medium;
      brightnessController.Set(brightnessLevel);
      SetIndicators();
     settingsController.SetFlashLight(Controllers::Settings::FlashLight::Medium);
    } else if (brightnessLevel == BrightnessController::Levels::Medium) {
      brightnessLevel = BrightnessController::Levels::Low;
      brightnessController.Set(brightnessLevel);
      SetIndicators();
      settingsController.SetFlashLight(Controllers::Settings::FlashLight::Low);
    }
    return true;
  }
  if (event == TouchEvents::SwipeRight) {
    if (brightnessLevel == BrightnessController::Levels::Low) {
      brightnessLevel = BrightnessController::Levels::Medium;
      brightnessController.Set(brightnessLevel);
      SetIndicators();
      settingsController.SetFlashLight(Controllers::Settings::FlashLight::Medium);
    } else if (brightnessLevel == BrightnessController::Levels::Medium) {
      brightnessLevel = BrightnessController::Levels::High;
      brightnessController.Set(brightnessLevel);
      SetIndicators();
      settingsController.SetFlashLight(Controllers::Settings::FlashLight::High);
    }
    return true;
  }


  return false;
}

void FlashLight::brightnessSet() {

  using namespace Pinetime::Controllers;

  if (settingsController.GetFlashLight() == Controllers::Settings::FlashLight::High) {
    brightnessLevel = BrightnessController::Levels::High;
    brightnessController.Set(brightnessLevel);
    SetIndicators();
  } else if (settingsController.GetFlashLight() == Controllers::Settings::FlashLight::Medium) {
    brightnessLevel == BrightnessController::Levels::Medium;
    SetIndicators();    
    brightnessController.Set(brightnessLevel);
  } else {
    brightnessLevel == BrightnessController::Levels::Low;
    SetIndicators();
  }
}

/*void FlashLight::brightnessSave() {
  brightnessLevel = FlashLightLevel
}

void FlashLight::Set(FlashLight::Levels level) {
  this->level = level;
  switch (level) {
    default:
    case Levels::High:
      
      break;
    case Levels::Medium:
      
      break;
    case Levels::Low:
      
      break;
    case Levels::Off:
   
      break;
  }
}*/