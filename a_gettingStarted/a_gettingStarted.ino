#include <Arduino_FreeRTOS.h>

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println(F("In Setup Function"));

  // Create three tasks with labels Task1, Task2 and Task3
  // and assigned prority
  // We also create the fourth task labeled as IdleTask when there is no task in
  // Operation and it has the higest priority

  //xTaskCreate(MyTask_pointer, "task_name", 100, Parameter, Priority, TaskHandle);

  xTaskCreate(MyTask1, "Task1", 100, NULL, 1, NULL);
  xTaskCreate(MyTask2, "Task2", 100, NULL, 2, NULL);
  xTaskCreate(MyTask3, "Task3", 100, NULL, 3, NULL);
  xTaskCreate(MyIdleTask, "IdleTask", 100, NULL, 0, NULL);

}

void loop() {
  // put your main code here, to run repeatedly:
  //There is no instruction in the loop section of the code.
  // Because each task executes on interrupt after specified time
}

static void MyTask1(void* pvParameters)
{
  while (1)
  {
    Serial.println(F("Task1"));
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}


static void MyTask2(void* pvParameters)

{
  while (1)

  {
    Serial.println(F("Task2"));
    vTaskDelay(1100 / portTICK_PERIOD_MS);
  }
}

static void MyTask3(void* pvParameters)
{
  while (1)

  {
    Serial.println(F("Task3"));
    vTaskDelay(1200 / portTICK_PERIOD_MS);
  }
}

static void MyIdleTask(void* pvParameters)

{
  while (1)

  {
    Serial.println(F("IdleTask"));
    delay(500);
  }
}
