#include <Arduino_FreeRTOS.h>

//***********************************************************************
// Tasks

// Task: Perform some mundane task
void testTask(void *parameters) {

  // Loop forever
  while(1) {
    int a = 1;
    int b[100];

    // Do something with array so it is not optimized out by the compiler
    for (int i = 0; i < 100; i++) {
      b[i] = a + 1;
    }
    Serial.println(b[0]);
  }
  
}

void setup() {
  // Configure Serial
  Serial.begin(115200);

  // Wait a moment to start (so we don't miss Serial output)
  vTaskDelay(1000 / portTICK_PERIOD_MS);
  
  //Serial.println();
  Serial.println("---FreeRTOS Memory Demo---");

  // Start print task
  xTaskCreate(testTask, 
              "Test Task",
              1024,
              NULL,
              1,
              NULL);
   // Delete "setup and loop" task
   vTaskDelete(NULL);
}

void loop() {
  
}
