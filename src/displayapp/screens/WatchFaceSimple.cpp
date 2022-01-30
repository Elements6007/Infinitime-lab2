#include "displayapp/screens/WatchFaceSimple.h"

#include <date/date.h>
#include <lvgl/lvgl.h>
#include <cstdio>
#include "displayapp/screens/BatteryIcon.h"
#include "displayapp/screens/BleIcon.h"
#include "displayapp/screens/NotificationIcon.h"
#include "displayapp/screens/Symbols.h"
#include "components/battery/BatteryController.h"
#include "components/ble/BleController.h"
#include "components/ble/NotificationManager.h"
#include "components/heartrate/HeartRateController.h"
#include "components/motion/MotionController.h"
#include "components/settings/Settings.h"

using namespace Pinetime::Applications::Screens;

WatchFaceSimple::WatchFaceSimple(DisplayApp* app,
                                   Controllers::DateTime& dateTimeController,
                                   Controllers::Settings& settingsController)
  : Screen(app),
    currentDateTime {{}},
    dateTimeController {dateTimeController},
    settingsController {settingsController} {
  settingsController.SetClockFace(4);

  label_date = lv_label_create(lv_scr_act(), nullptr);
  lv_obj_align(label_date, lv_scr_act(), LV_ALIGN_CENTER, 0, 60);
  lv_obj_set_style_local_text_color(label_date, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_hex(0x999999));

  label_time = lv_label_create(lv_scr_act(), nullptr);
  lv_obj_set_style_local_text_font(label_time, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &jetbrains_mono_extrabold_compressed);

  lv_obj_align(label_time, lv_scr_act(), LV_ALIGN_IN_RIGHT_MID, 0, 0);

  label_time_ampm = lv_label_create(lv_scr_act(), nullptr);
  lv_label_set_text_static(label_time_ampm, "");
  lv_obj_align(label_time_ampm, lv_scr_act(), LV_ALIGN_IN_RIGHT_MID, -30, -55);

  backgroundLabel = lv_label_create(lv_scr_act(), nullptr);
  lv_obj_set_click(backgroundLabel, true);
  lv_label_set_long_mode(backgroundLabel, LV_LABEL_LONG_CROP);
  lv_obj_set_size(backgroundLabel, 240, 240);
  lv_obj_set_pos(backgroundLabel, 0, 0);
  lv_label_set_text(backgroundLabel, "");

  taskRefresh = lv_task_create(RefreshTaskCallback, LV_DISP_DEF_REFR_PERIOD, LV_TASK_PRIO_MID, this);
  Refresh();
}

WatchFaceSimple::~WatchFaceSimple() {
  lv_task_del(taskRefresh);
  lv_obj_clean(lv_scr_act());
}

void WatchFaceSimple::Refresh() {

  currentDateTime = dateTimeController.CurrentDateTime();

  if (currentDateTime.IsUpdated()) {
    auto newDateTime = currentDateTime.Get();

    auto dp = date::floor<date::days>(newDateTime);
    auto time = date::make_time(newDateTime - dp);
    auto yearMonthDay = date::year_month_day(dp);

    auto year = static_cast<int>(yearMonthDay.year());
    auto month = static_cast<Pinetime::Controllers::DateTime::Months>(static_cast<unsigned>(yearMonthDay.month()));
    auto day = static_cast<unsigned>(yearMonthDay.day());
    auto dayOfWeek = static_cast<Pinetime::Controllers::DateTime::Days>(date::weekday(yearMonthDay).iso_encoding());

    int hour = time.hours().count();
    auto minute = time.minutes().count();

    char minutesChar[3];
    sprintf(minutesChar, "%02d", static_cast<int>(minute));

    char hoursChar[3];
    char ampmChar[3];
    if (settingsController.GetClockType() == Controllers::Settings::ClockType::H24) {
      sprintf(hoursChar, "%02d", hour);
    } else {
      if (hour == 0 && hour != 12) {
        hour = 12;
        sprintf(ampmChar, "AM");
      } else if (hour == 12 && hour != 0) {
        hour = 12;
        sprintf(ampmChar, "PM");
      } else if (hour < 12 && hour != 0) {
        sprintf(ampmChar, "AM");
      } else if (hour > 12 && hour != 0) {
        hour = hour - 12;
        sprintf(ampmChar, "PM");
      }
      sprintf(hoursChar, "%02d", hour);
    }

    if ((hoursChar[0] != displayedChar[0]) or (hoursChar[1] != displayedChar[1]) or (minutesChar[0] != displayedChar[2]) or
        (minutesChar[1] != displayedChar[3])) {
      displayedChar[0] = hoursChar[0];
      displayedChar[1] = hoursChar[1];
      displayedChar[2] = minutesChar[0];
      displayedChar[3] = minutesChar[1];

      if (settingsController.GetClockType() == Controllers::Settings::ClockType::H12) {
        lv_label_set_text(label_time_ampm, ampmChar);
        if (hoursChar[0] == '0') {
          hoursChar[0] = ' ';
        }
      }

      lv_label_set_text_fmt(label_time, "%s:%s", hoursChar, minutesChar);

      if (settingsController.GetClockType() == Controllers::Settings::ClockType::H12) {
        lv_obj_align(label_time, lv_scr_act(), LV_ALIGN_IN_RIGHT_MID, 0, 0);
      } else {
        lv_obj_align(label_time, lv_scr_act(), LV_ALIGN_CENTER, 0, 0);
      }
    }

    if ((year != currentYear) || (month != currentMonth) || (dayOfWeek != currentDayOfWeek) || (day != currentDay)) {
      if (settingsController.GetClockType() == Controllers::Settings::ClockType::H24) {
        lv_label_set_text_fmt(label_date, "%s %d %s %d", dateTimeController.DayOfWeekShortToString(), day, dateTimeController.MonthShortToString(), year);
      } else {
        lv_label_set_text_fmt(label_date, "%s %s %d %d", dateTimeController.DayOfWeekShortToString(), dateTimeController.MonthShortToString(), day, year);
      }
      lv_obj_align(label_date, lv_scr_act(), LV_ALIGN_CENTER, 0, 60);

      currentYear = year;
      currentMonth = month;
      currentDayOfWeek = dayOfWeek;
      currentDay = day;
    }
  }
}
