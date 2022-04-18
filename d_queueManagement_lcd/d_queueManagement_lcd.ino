#include <Arduino_FreeRTOS.h>
#include <queue.h>

// add LCD i2c include code
// add lcd instance HERE

QueueHandle_t xQueue;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  // add lcd begin code HERE

  xQueue = xQueueCreate(5, sizeof(long));

  if (xQueue != NULL) {

    xTaskCreate( adcTask,
                 "Sender",
                 240,
                 (void *) 100,
                 1,
                 NULL);
    xTaskCreate( lcdTask,
                 "Receiver",
                 240,
                 (void *) 200,
                 2,
                 NULL);
    vTaskStartScheduler();
  }
  else {
    /* The quee could not be created*/
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}

void adcTask (void *pvParameters) {
  long lValueToSend;
  lValueToSend = (long) pvParameters;

  for (;;) {
    int adc_value;
    adc_value = analogRead(A4);
    xQueueSend( xQueue, &adc_value, portMAX_DELAY == pdPASS);
    Serial.print( "adcTask = ");
    Serial.println(adc_value);
    //taskYIELD();
  }
}
void lcdTask( void *pvParameters )
{
  int receivedValue = 0;
  for ( ;; ) {
    if (xQueueReceive( xQueue, &receivedValue, portMAX_DELAY ) == pdPASS) {
      Serial.print( "Received = ");
      Serial.println(receivedValue);
      /*lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("ADC : ");
      lcd.setCursor(6, 0);
      lcd.print(ReceivedValue);*/
    }
    taskYIELD();
  }
}
