
#ifndef AHT15_TASK_H
#define AHT15_TASK_H

#define CONFIG_I2C_MASTER_SCL GPIO_NUM_19
#define CONFIG_I2C_MASTER_SDA GPIO_NUM_18
#define AHT_TYPE AHT_TYPE_AHT1x
#define ADDR AHT_I2C_ADDRESS_GND

void aht15_task(void *pvParameters);

float get_aht_temperature(void);
float get_aht_humidity(void);

void aht15_start(void);

#endif /* AHT15_TASK_H */
