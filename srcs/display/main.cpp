#include <lvgl.h>
#include <demos/widgets/lv_demo_widgets.h>

#if LV_USE_TFT_ESPI
#include <TFT_eSPI.h>
#endif

/*Set to your screen resolution*/
#define WIDTH 240
#define HEIGHT 320

/*LVGL draw into this buffer, 1/10 screen size usually works well. The size is in bytes*/
#define DRAW_BUF_SIZE (HEIGHT * WIDTH / 10 * (LV_COLOR_DEPTH / 8))
uint32_t draw_buf[DRAW_BUF_SIZE / 4];

static void my_input_read(lv_indev_t *indev, lv_indev_data_t *data)
{
  #ifdef TOUCH_CS

  Serial.println("Pressed");

  static uint16_t x, y;

  lv_display_t *disp = lv_indev_get_display(indev);
  void **dsc = (void **)lv_display_get_driver_data(disp);
  TFT_eSPI *tft = (TFT_eSPI *)*dsc;
  if (tft->getTouch(&x, &y))
  {
    data->point.x = x;
    data->point.y = y;
    data->state = LV_INDEV_STATE_PRESSED;
  }
  else
  {
    data->state = LV_INDEV_STATE_RELEASED;
  }

  #endif
}

static void my_log(lv_log_level_t level, const char *buf)
{
  Serial.println(buf);
}

static uint32_t my_tick()
{
  return millis();
}

void setup()
{
  Serial.begin(9600);

  lv_init();

#if LV_USE_LOG
  lv_log_register_print_cb(my_log);
#endif

#if LV_USE_TFT_ESPI
  lv_tick_set_cb(my_tick);

  lv_display_t *disp = lv_tft_espi_create(WIDTH, HEIGHT, draw_buf, sizeof(draw_buf));
  void **dsc = (void **)lv_display_get_driver_data(disp);
  lv_display_set_rotation(disp, LV_DISPLAY_ROTATION_270);
  TFT_eSPI *tft = (TFT_eSPI *)*dsc;
  tft->setRotation(1);

  /* Create and set up at least one display before you register any input devices. */
  lv_indev_t *indev = lv_indev_create();           /* Create input device connected to Default Display. */
  lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER); /* Touch pad is a pointer-like device. */
  lv_indev_set_read_cb(indev, my_input_read);      /* Set driver function. */
  lv_demo_widgets();
#endif

  Serial.println("Setup done");
}

void loop()
{
  lv_task_handler(); /* let the GUI do its work */
  // delay(5);          /* let this time pass */
}
