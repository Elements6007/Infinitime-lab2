#pragma once

#include <memory>

#include "components/datetime/DateTimeController.h"
#include "displayapp/screens/Screen.h"
#include "displayapp/screens/ScreenList.h"

namespace Pinetime {
  namespace Applications {
    namespace Screens {
      class pagetest : public Screen {
      public:
        explicit pagetest(DisplayApp* app, Pinetime::Controllers::DateTime &dateTimeController);
        ~pagetest() override;
        bool OnTouchEvent(TouchEvents event) override;

      private:
        Controllers::DateTime& dateTimeController;

        int dayValue;
        lv_obj_t * onion;
        lv_obj_t * obama;
        lv_obj_t * title; 

        ScreenList<2> screens;
        std::unique_ptr<Screen> CreateScreen1();
        std::unique_ptr<Screen> CreateScreen2();
      };
    }
  }
}
