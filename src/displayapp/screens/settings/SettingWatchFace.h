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
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
        static constexpr std::array<const char*, 5> options = {" Digital face", " Analog face", " PineTimeStyle", "Terminal face", " Simpe face"};
        Controllers::Settings& settingsController; 
=======
=======
>>>>>>> parent of 187ea0f (Merge branch 'develop' of JF/PineTime into master)
=======
>>>>>>> parent of 187ea0f (Merge branch 'develop' of JF/PineTime into master)
        static constexpr std::array<const char*, 3> options = {" Digital face", " Analog face", " PineTimeStyle"};
        Controllers::Settings& settingsController;
>>>>>>> parent of 187ea0f (Merge branch 'develop' of JF/PineTime into master)

        lv_obj_t* cbOption[options.size()];

      };
    }
  }
}
