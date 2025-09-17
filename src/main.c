#include <zephyr/kernel.h>
#include <zephyr/drivers/display.h>
#include <lvgl.h>
#include <string.h>

int main(void)
{
    const struct device *display;
    lv_obj_t *hello_label;

    display = DEVICE_DT_GET(DT_CHOSEN(zephyr_display));
    if (!device_is_ready(display)) {
        printk("Error: display not ready\r\n");
        return 0;
    }

    hello_label = lv_label_create(lv_scr_act());
    lv_label_set_text(hello_label, "Hello, World!");
    lv_obj_align(hello_label, LV_ALIGN_TOP_MID, 0, 5);

    display_blanking_off(display);

    while (1) {
        lv_task_handler();

        k_msleep(50);
    }
}
