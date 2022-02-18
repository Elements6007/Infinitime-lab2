#pragma once

#include <memory>

#include "displayapp/screens/Screen.h"
#include "displayapp/screens/ScreenList.h"
#include "components/settings/Settings.h"

namespace Pinetime {
  namespace Applications {
    namespace Screens {
      class pagetest : public Screen {
      public:
        explicit pagetest(DisplayApp* app);
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
