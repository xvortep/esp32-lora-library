#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "lora.h"
#include "esp_log.h"

uint8_t buf[32];

void task_rx(void *p)
{
   int x;
   for(;;) {
      lora_receive();    // put into receive mode
      while(lora_received()) {
         lora_dump_registers();
         x = lora_receive_packet(buf, sizeof(buf));
         // buf[x] = 0;
         printf("Received: %c, size %d, snr %f, rssi %d\n", buf[0], x, lora_packet_snr(), lora_packet_rssi());
         lora_receive();
      }
      vTaskDelay(pdMS_TO_TICKS(50));
   }
}

void app_main()
{
   ESP_LOGE("receiver", "receiver");
   lora_init();
   lora_set_frequency(433e6);
   lora_enable_crc();
   xTaskCreate(&task_rx, "task_rx", 2048, NULL, 5, NULL);

   for (;;) {
      vTaskDelay(1000);
   }
}
