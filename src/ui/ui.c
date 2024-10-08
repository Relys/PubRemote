// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.2
// LVGL version: 8.3.6
// Project name: PubRemote

#include "ui.h"
#include "ui_helpers.h"

///////////////////// VARIABLES ////////////////////


// SCREEN: ui_SplashScreen
void ui_SplashScreen_screen_init(void);
void ui_event_SplashScreen( lv_event_t * e);
lv_obj_t *ui_SplashScreen;
lv_obj_t *ui_SplashScreenLogo;


// SCREEN: ui_StatsScreen
void ui_StatsScreen_screen_init(void);
void ui_event_StatsScreen( lv_event_t * e);
lv_obj_t *ui_StatsScreen;
lv_obj_t *ui_DutyCycle;
lv_obj_t *ui_LeftSensor;
lv_obj_t *ui_RightSensor;
lv_obj_t *ui_StatsScreenContent;
lv_obj_t *ui_StatsScreenHeader;
lv_obj_t *ui_Logo;
lv_obj_t *ui_TimeDisplay;
lv_obj_t *ui_StatsScreenBody;
lv_obj_t *ui_PrimaryStat;
lv_obj_t *ui_PrimaryStatUnit;
lv_obj_t *ui_SecondaryStats;
lv_obj_t *ui_ConnectionState;
lv_obj_t *ui_DistanceStats;
lv_obj_t *ui_TempStats;
lv_obj_t *ui_StatsScreenFooter;
void ui_event_BatteryDisplay( lv_event_t * e);
lv_obj_t *ui_BatteryDisplay;


// SCREEN: ui_PairingScreen
void ui_PairingScreen_screen_init(void);
void ui_event_PairingScreen( lv_event_t * e);
lv_obj_t *ui_PairingScreen;
lv_obj_t *ui_PairingScreenContent;
lv_obj_t *ui_PairingScreenHeader;
lv_obj_t *ui_PairingScreenBody;
lv_obj_t *ui_Label4;
lv_obj_t *ui_Label1;
lv_obj_t *ui_PairingScreenFooter;
void ui_event_PairingScreenMainActionButton( lv_event_t * e);
lv_obj_t *ui_PairingScreenMainActionButton;
lv_obj_t *ui_PairingScreenMainActionButtonLabel;


// SCREEN: ui_SettingsScreen
void ui_SettingsScreen_screen_init(void);
void ui_event_SettingsScreen( lv_event_t * e);
lv_obj_t *ui_SettingsScreen;
lv_obj_t *ui_SettingsScreenContent;
lv_obj_t *ui_SettingsScreenHeader;
lv_obj_t *ui_SettingsScreenBody;
lv_obj_t *ui_BrightnessLabel;
void ui_event_BrightnessSlider( lv_event_t * e);
lv_obj_t *ui_BrightnessSlider;
lv_obj_t *ui_SettingsScreenFooter;
void ui_event_SettingsScreenMainActionButton( lv_event_t * e);
lv_obj_t *ui_SettingsScreenMainActionButton;
lv_obj_t *ui_SettingsScreenMainActionButtonLabel;


// SCREEN: ui_CalibrationScreen
void ui_CalibrationScreen_screen_init(void);
void ui_event_CalibrationScreen( lv_event_t * e);
lv_obj_t *ui_CalibrationScreen;
lv_obj_t *ui_CalibrationScreenContent;
lv_obj_t *ui_CalibrationScreenHeader;
lv_obj_t *ui_CalibrationScreenBody;
lv_obj_t *ui_CalibrationScreenFooter;
lv_obj_t *ui_CalibrationScreenMainActionButton;
lv_obj_t *ui_CalibrationScreenMainActionButtonLabel;
lv_obj_t *ui____initial_actions0;

///////////////////// TEST LVGL SETTINGS ////////////////////
#if LV_COLOR_DEPTH != 16
    #error "LV_COLOR_DEPTH should be 16bit to match SquareLine Studio's settings"
#endif
#if LV_COLOR_16_SWAP !=1
    #error "LV_COLOR_16_SWAP should be 1 to match SquareLine Studio's settings"
#endif

///////////////////// ANIMATIONS ////////////////////

///////////////////// FUNCTIONS ////////////////////
void ui_event_SplashScreen( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_SCREEN_LOADED) {
      _ui_screen_change( &ui_StatsScreen, LV_SCR_LOAD_ANIM_FADE_ON, 500, 1000, &ui_StatsScreen_screen_init);
}
}
void ui_event_StatsScreen( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_GESTURE &&  lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_BOTTOM  ) {
lv_indev_wait_release(lv_indev_get_act());
      _ui_screen_change( &ui_SettingsScreen, LV_SCR_LOAD_ANIM_OVER_BOTTOM, 500, 0, &ui_SettingsScreen_screen_init);
}
}
void ui_event_BatteryDisplay( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_LONG_PRESSED) {
      toggleFooterDisplayMode( e );
}
}
void ui_event_PairingScreen( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_GESTURE &&  lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_TOP  ) {
lv_indev_wait_release(lv_indev_get_act());
      _ui_screen_change( &ui_StatsScreen, LV_SCR_LOAD_ANIM_OVER_TOP, 500, 0, &ui_StatsScreen_screen_init);
}
if ( event_code == LV_EVENT_GESTURE &&  lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_LEFT  ) {
lv_indev_wait_release(lv_indev_get_act());
      _ui_screen_change( &ui_CalibrationScreen, LV_SCR_LOAD_ANIM_MOVE_LEFT, 500, 0, &ui_CalibrationScreen_screen_init);
}
if ( event_code == LV_EVENT_GESTURE &&  lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_RIGHT  ) {
lv_indev_wait_release(lv_indev_get_act());
      _ui_screen_change( &ui_SettingsScreen, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 500, 0, &ui_SettingsScreen_screen_init);
}
}
void ui_event_PairingScreenMainActionButton( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_CLICKED) {
      _ui_screen_change( &ui_PairingScreen, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, &ui_PairingScreen_screen_init);
}
}
void ui_event_SettingsScreen( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_GESTURE &&  lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_LEFT  ) {
lv_indev_wait_release(lv_indev_get_act());
      _ui_screen_change( &ui_PairingScreen, LV_SCR_LOAD_ANIM_MOVE_LEFT, 500, 0, &ui_PairingScreen_screen_init);
}
if ( event_code == LV_EVENT_GESTURE &&  lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_TOP  ) {
lv_indev_wait_release(lv_indev_get_act());
      _ui_screen_change( &ui_StatsScreen, LV_SCR_LOAD_ANIM_OVER_TOP, 500, 0, &ui_StatsScreen_screen_init);
}
if ( event_code == LV_EVENT_GESTURE &&  lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_RIGHT  ) {
lv_indev_wait_release(lv_indev_get_act());
      _ui_screen_change( &ui_CalibrationScreen, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 500, 0, &ui_CalibrationScreen_screen_init);
}
}
void ui_event_BrightnessSlider( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_PRESSED) {
      _ui_flag_modify( ui_SettingsScreen, LV_OBJ_FLAG_GESTURE_BUBBLE, _UI_MODIFY_FLAG_ADD);
}
if ( event_code == LV_EVENT_RELEASED) {
      _ui_flag_modify( ui_SettingsScreen, LV_OBJ_FLAG_GESTURE_BUBBLE, _UI_MODIFY_FLAG_REMOVE);
}
}
void ui_event_SettingsScreenMainActionButton( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_CLICKED) {
      _ui_screen_change( &ui_StatsScreen, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, &ui_StatsScreen_screen_init);
}
}
void ui_event_CalibrationScreen( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_GESTURE &&  lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_TOP  ) {
lv_indev_wait_release(lv_indev_get_act());
      _ui_screen_change( &ui_StatsScreen, LV_SCR_LOAD_ANIM_OVER_TOP, 500, 0, &ui_StatsScreen_screen_init);
}
if ( event_code == LV_EVENT_GESTURE &&  lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_LEFT  ) {
lv_indev_wait_release(lv_indev_get_act());
      _ui_screen_change( &ui_SettingsScreen, LV_SCR_LOAD_ANIM_MOVE_LEFT, 500, 0, &ui_SettingsScreen_screen_init);
}
if ( event_code == LV_EVENT_GESTURE &&  lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_RIGHT  ) {
lv_indev_wait_release(lv_indev_get_act());
      _ui_screen_change( &ui_PairingScreen, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 500, 0, &ui_PairingScreen_screen_init);
}
}

///////////////////// SCREENS ////////////////////

void ui_init( void )
{
lv_disp_t *dispp = lv_disp_get_default();
lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), true, LV_FONT_DEFAULT);
lv_disp_set_theme(dispp, theme);
ui_SplashScreen_screen_init();
ui_StatsScreen_screen_init();
ui_PairingScreen_screen_init();
ui_SettingsScreen_screen_init();
ui_CalibrationScreen_screen_init();
ui____initial_actions0 = lv_obj_create(NULL);
lv_disp_load_scr( ui_SplashScreen);
}
