#pragma once

#include <array>
#include <cstdint>
#include <lvgl/lvgl.h>

#include "components/settings/Settings.h"
#include "displayapp/screens/Screen.h"

namespace Pinetime {

  namespace Applications {
    namespace Screens {

      class SettingTimeFormat : public Screen {
      public:
        SettingTimeFormat(DisplayApp* app, Pinetime::Controllers::Settings& settingsController);
        ~SettingTimeFormat() override;

        void UpdateSelected(lv_obj_t* object, lv_event_t event);

      private:
        static constexpr std::array<const char*, 2> options = {" 12-hour", " 24-hour"};
        Controllers::Settings& settingsController;
        lv_obj_t* cbOption[options.size()];
        lv_obj_t* btnInfo;
        lv_obj_t* txtInfo;
        lv_obj_t* txtInfo;
        void MenuInfo();
        void HideInfo();
        lv_obj_t* txtStatus = nullptr;
        lv_obj_t* btnStatus = nullptr;
      };
    }
  }
}