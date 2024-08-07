#include <lvgl.h>
#include <demos/widgets/lv_demo_widgets.h>

#if LV_USE_TFT_ESPI
#include <TFT_eSPI.h>
#endif

/*Set to your screen resolution*/
#define TFT_HOR_RES 320
#define TFT_VER_RES 240

/*LVGL draw into this buffer, 1/10 screen size usually works well. The size is in bytes*/
#define DRAW_BUF_SIZE (TFT_HOR_RES * TFT_VER_RES / 10 * (LV_COLOR_DEPTH / 8))
uint32_t draw_buf[DRAW_BUF_SIZE / 4];

void setup()
{
  Serial.begin(9600);

  lv_init();

#if LV_USE_TFT_ESPI
  lv_display_t *disp = lv_tft_espi_create(TFT_HOR_RES, TFT_VER_RES, draw_buf, sizeof(draw_buf));
#endif

  Serial.println("Setup done");

  lv_demo_widgets();
}

void loop()
{
  lv_task_handler(); /* let the GUI do its work */
  delay(5);          /* let this time pass */
}
