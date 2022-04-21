#include <Arduino_FreeRTOS.h>
#include <queue.h>

// settings 
static const uint8_t msgQueueLen = 5;

static QueueHandle_t msgQueue;

//***********************************************************************
// Tasks

// Task: wait for item on queue and print it
void printMessages(void *parameters) {

  int item;

  // Loop forever
  while(1) {

    // See if there's a message in the queue (do not block)
    if (xQueueReceive(msgQueue, (void *)&item, 0) ==pdPASS) {

      Serial.println(item);

      // Wait before trying again
      vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
  }
  
}

void setup() {
  // Configure Serial
  Serial.begin(9600);

  // Wait a moment to start (so we don't miss Serial output)
  // vTaskDelay(1000 / portTICK_PERIOD_MS);
  
  //Serial.println();
  Serial.println("---FreeRTOS Queue Demo---");

  // Create queue
  msgQueue = xQueueCreate(msgQueueLen, sizeof(int));

  // Start print task
  xTaskCreate(printMessages, 
              "Print Message",
              240,
              NULL,
              1,
              NULL);
   vTaskStartScheduler();
}

void loop() {

  static int num = 0;

  // Try to add item to queue for 10 ticks, fail if queue is full
  if (xQueueSend(msgQueue, (void *)&num, 10) != pdPASS) {
    Serial.println("Queue full");
  }
  num++;

  // Wait before trying again
  vTaskDelay(1000 / portTICK_PERIOD_MS);
  
}
