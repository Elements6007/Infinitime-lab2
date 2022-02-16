#pragma once

#include "displayapp/screens/Screen.h"
#include <lvgl/lvgl.h>

namespace Pinetime {
  namespace Applications {
    namespace Screens {
      class pagetest : public Screen {
      public:
        pagetest(DisplayApp* app);
        ~pagetest() override;
      };
    }
  }
}