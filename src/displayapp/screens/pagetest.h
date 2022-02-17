#pragma once

#include "displayapp/screens/Screen.h"
#include <lvgl/lvgl.h>
#include "displayapp/screens/Screen.h"
#include "displayapp/screens/ScreenList.h"

namespace Pinetime {
  namespace Applications {
    namespace Screens {
      class pagetest : public Screen {
      public:
        pagetest(DisplayApp* app);
        ~pagetest() override;
        bool OnTouchEvent(TouchEvents event) override;
      private:


        ScreenList<2> screens;
        std::unique_ptr<Screen> CreateScreen1();
        std::unique_ptr<Screen> CreateScreen2();

      };
    }
  }
}