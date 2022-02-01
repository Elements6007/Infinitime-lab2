#pragma once

#include <array>
#include <cstdint>
#include <lvgl/lvgl.h>

#include "components/settings/Settings.h"
#include "displayapp/screens/Screen.h"

namespace Pinetime {

  namespace Applications {
    namespace Screens {

      class SettingWatchFace : public Screen {
      public:
        SettingWatchFace(DisplayApp* app, Pinetime::Controllers::Settings& settingsController);
        ~SettingWatchFace() override;

        void UpdateSelected(lv_obj_t* object, lv_event_t event);

      private:
        static constexpr std::array<const char*, 5> options = {" Digital face", " Analog face", " PineTimeStyle", "Terminal face", " Simpe face"};
        Controllers::Settings& settingsController; 

        lv_obj_t* cbOption[options.size()];

        ScreenList<2> screens;  
        std::unique_ptr<screen> CreateScreen1();
        std::unique_ptr<screen> CreateScreen2();
      };
    }
  }
}
