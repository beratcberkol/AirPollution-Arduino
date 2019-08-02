#include <Arduino_FreeRTOS.h>
#include <Servo.h>




//TickType_t xTimeInTicks = pdMS_TO_TICKS( 3000 );
void vSmoke(void *pvParameters);
void vTemperature(void *pvParameters);
int Led1 = 2;
int Led2 = 3;
int Led3 = 53;
int Led4 = 42;
int smokeA0 = A5;
int sensorThres = 400;
float temp;
int tempPin = A0;
Servo servo;


void setup() {
  pinMode(Led1, OUTPUT);
  pinMode(Led2, OUTPUT);
  pinMode(Led3, OUTPUT);
  pinMode(Led4, OUTPUT);
  pinMode(smokeA0, INPUT);
  pinMode(tempPin, INPUT);
  
  servo.attach(7);

  xTaskCreate(  vSmoke,
                (const portCHAR *)"Task 1",
                100,
                NULL,
                1,
                NULL);


  xTaskCreate(  vTemperature,
                (const portCHAR *)"Task 2",
                100,
                NULL,
                1,
                NULL);
  vTaskStartScheduler();

}


void loop() {
  // put your main code here, to run repeatedly:

}

void vSmoke(void *pvParameters)
{
  (void) pvParameters;
  digitalWrite(Led3, HIGH);
  digitalWrite(Led4, HIGH);
  Serial.begin(9600);
  for (;;)
  {
    int analogSensor = analogRead(smokeA0);
    Serial.print("Pin A0: ");
    Serial.println(analogSensor);

    if (analogSensor < 250)
    {
      digitalWrite(Led1, HIGH);
      digitalWrite(Led2, LOW);
    }
    else if (analogSensor >= 250)
    {
      digitalWrite(Led1, LOW);
      digitalWrite(Led2, HIGH);

    }
    vTaskDelay(1000/ portTICK_PERIOD_MS);
  }
}

void vTemperature(void *pvParameters)
{
  (void) pvParameters;
  Serial.begin(9600);
  const char *pcTaskName = "Temperature çalıştı";

  for (;;)
  {
    temp = (3.8 * analogRead(tempPin) * 100.0) / 1024;
    Serial.println("Sıcaklık = ");
    Serial.println(temp);
    Serial.println();
    vTaskDelay(1000/ portTICK_PERIOD_MS);
    if (temp > 15)
    {   
      servo.write(360);
      vTaskDelay(800/ portTICK_PERIOD_MS);
      servo.write(0);
      vTaskDelay(800/ portTICK_PERIOD_MS);
      servo.write(360);
      
    }
    
  }

}
