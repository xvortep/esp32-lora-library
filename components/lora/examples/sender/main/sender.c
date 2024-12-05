#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "lora.h"
#include "esp_log.h"

#define TAG "sender"

uint8_t buf[2] = {'a', 's'};

const uint8_t* pbuf = buf;

void task_tx(void *p)
{
   for(;;) {
      vTaskDelay(pdMS_TO_TICKS(2000));
      ESP_LOGI(TAG, "sending '%c' from address %p",*pbuf, pbuf);
      lora_send_packet(pbuf, 2);
      printf("packet sent...\n");
   }
}

void app_main()
{
   ESP_LOGE("sender", "sender");

   lora_init();
   lora_set_frequency(433e6);
   lora_set_tx_power(14);
   lora_enable_crc();
   
   ESP_LOGE("sender", "creating the task");
   
   xTaskCreate(&task_tx, "task_tx", 2048, NULL, 5, NULL);
   
   for (;;) {
      vTaskDelay(1000);
   }
}

