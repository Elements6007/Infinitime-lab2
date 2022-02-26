#pragma once

#include <cstdint>
#include <lvgl/lvgl.h>
#include "components/datetime/DateTimeController.h"
#include "displayapp/screens/Screen.h"
#include "displayapp/screens/ScreenList.h"

namespace Pinetime {
  namespace Applications {
    namespace Screens {
      class SettingSetDate : public Screen{
        public:
          SettingSetDate(DisplayApp* app, Pinetime::Controllers::DateTime &dateTimeController);
          ~SettingSetDate() override;
          bool OnTouchEvent(TouchEvents event) override;

          void HandleButtonPress(lv_obj_t *object, lv_event_t event);
         
        private:
          Controllers::DateTime& dateTimeController;

          int dayValue;
          Pinetime::Controllers::DateTime::Months currentMonth = Pinetime::Controllers::DateTime::Months::Unknown;
          int yearValue;
          lv_obj_t * lblDay;
          lv_obj_t * lblMonth;
          lv_obj_t * lblYear;
          lv_obj_t * btnDayPlus;
          lv_obj_t * btnDayMinus;
          lv_obj_t * btnMonthPlus;
          lv_obj_t * btnMonthMinus;
          lv_obj_t * btnYearPlus;
          lv_obj_t * btnYearMinus;
          lv_obj_t * btnSetTime;

          int MaximumDayOfMonth() const;
          void CheckDay();
          void UpdateMonthLabel();

          ScreenList<2> screens;

          std::unique_ptr<Screen> CreateScreen1();
          std::unique_ptr<Screen> CreateScreen2();
      };
    }
  }
}
