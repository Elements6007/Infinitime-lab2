#pragma once

#include <memory>
#include <lvgl/lvgl.h>
#include "displayapp/screens/Screen.h"
#include "displayapp/screens/ScreenList.h"

namespace Pinetime {

  namespace Applications {
    class DisplayApp;

    namespace Screens {
      class pagetest : public Screen {
      public:
        explicit pagetest(DisplayApp* app);
        ~pagetest() override;
        bool OnTouchEvent(TouchEvents event) override;


       // private:
        
        //lv_obj_t* onion;
        //lv_obj_t* obama;

      //  ScreenList<2> screens;

      //  std::unique_ptr<Screen> CreateScreen1();
      //  std::unique_ptr<Screen> CreateScreen2();
      };
    }
  }