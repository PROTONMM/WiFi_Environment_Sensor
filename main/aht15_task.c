#include "aht15_task.h"
#include "aht.h"
#include "esp_log.h"

float aht_temperature, aht_humidity;

static const char *TAG = "AHT15_task";

void aht15_task(void *pvParameters) {

  ESP_ERROR_CHECK(i2cdev_init());
  aht_t dev = {0};
  dev.mode = AHT_MODE_NORMAL;
  dev.type = AHT_TYPE;

  ESP_ERROR_CHECK(aht_init_desc(&dev, ADDR, 0, CONFIG_I2C_MASTER_SDA,
                                CONFIG_I2C_MASTER_SCL));
  ESP_ERROR_CHECK(aht_init(&dev));

  bool calibrated;
  ESP_ERROR_CHECK(aht_get_status(&dev, NULL, &calibrated));
  if (calibrated)
    ESP_LOGI(TAG, "Sensor calibrated");
  else
    ESP_LOGW(TAG, "Sensor not calibrated!");

  while (1) {
    esp_err_t res = aht_get_data(&dev, &aht_temperature, &aht_humidity);
    if (res == ESP_OK)
      ESP_LOGI(TAG, "Temperature: %.1f C, Humidity: %.2f% %", aht_temperature,
               aht_humidity);
    else
      ESP_LOGE(TAG, "Error reading data: %d (%s)", res, esp_err_to_name(res));

    vTaskDelay(pdMS_TO_TICKS(1000 * 5));
  }
}


float get_aht_temperature(void){
	return aht_temperature;
}

float get_aht_humidity(void){
	return aht_humidity;
}

void aht15_start(void){
	xTaskCreatePinnedToCore(aht15_task, "AHT15", configMINIMAL_STACK_SIZE * 8, NULL, 5, NULL, 1);
}
