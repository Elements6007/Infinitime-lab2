#pragma once

#include <lvgl/src/lv_core/lv_obj.h>
#include <chrono>
#include <cstdint>
#include <memory>
#include "displayapp/screens/Screen.h"
#include "components/datetime/DateTimeController.h"

namespace Pinetime {
  namespace Controllers {
    class Settings;
  }

  namespace Applications {
    namespace Screens {

      class WatchFaceSimple : public Screen {
      public:
        WatchFaceSimple(DisplayApp* app,
                         Controllers::DateTime& dateTimeController,
                         Controllers::Settings& settingsController);
        ~WatchFaceSimple() override;

        void Refresh() override;

      private:
        char displayedChar[5] {};

        uint16_t currentYear = 1970;
        Pinetime::Controllers::DateTime::Months currentMonth = Pinetime::Controllers::DateTime::Months::Unknown;
        Pinetime::Controllers::DateTime::Days currentDayOfWeek = Pinetime::Controllers::DateTime::Days::Unknown;
        uint8_t currentDay = 0;

        DirtyValue<std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds>> currentDateTime {};

        lv_obj_t* label_time;
        lv_obj_t* label_time_ampm;
        lv_obj_t* label_date;
        lv_obj_t* backgroundLabel;

        Controllers::DateTime& dateTimeController;
        Controllers::Settings& settingsController;

        lv_task_t* taskRefresh;
      };
    }
  }
}
