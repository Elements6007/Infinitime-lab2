#pragma once

#include <array>
#include <cstdint>
#include <lvgl/lvgl.h>

#include "components/settings/Settings.h"
#include "displayapp/screens/Screen.h"
#include "displayapp/screens/ScreenList.h"

namespace Pinetime {

  namespace Applications {
    namespace Screens {

      class SettingTimeFormat : public Screen {
      public:
        SettingTimeFormat(DisplayApp* app, Pinetime::Controllers::Settings& settingsController);
        ~SettingTimeFormat() override;
        bool OnTouchEvent(TouchEvents event) override;

        void UpdateSelected(lv_obj_t* object, lv_event_t event);

      private:
        static constexpr std::array<const char*, 3> options = {" 12-hour", " 24-hour", " Global"};
        Controllers::Settings& settingsController;
        lv_obj_t* cbOption[options.size()];

        ScreenList<2> screens;

        std::unique_ptr<Screen> CreateScreen1();
        std::unique_ptr<Screen> CreateScreen2();
      };
    }
  }
}
