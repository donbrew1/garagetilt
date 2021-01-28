
//520K external resistor on A0
#include "donbrew7.h"

float RatioFactor = 1.7;
int BAT = A0;
#define tiltSensor D6

void setup() {
  pinMode(tiltSensor, INPUT);

  Serial.begin(115200);
  Serial.println("Woke up");
  uint32_t startTime = millis();


  float Tvoltage = 0.0;
  float Vvalue = 0.0, Rvalue = 0.0;

  /////////////////////////////////////Battery Voltage//////////////////////////////////
   for(unsigned int i=0;i<10;i++){
  Vvalue = Vvalue + analogRead(BAT);     //Read analog Voltage
    delay(5);                              //ADC stable
    }
    Vvalue=(float)Vvalue/10.0;            //Find average of 10 values
  Rvalue = (float)(Vvalue / 1024.0) * 5 ; //Convert Voltage in 3v factor
  Tvoltage = Rvalue * RatioFactor;      //Find original voltage by multiplying with factor
  /////////////////////////////////////Battery Voltage//////////////////////////////////
  
 
  connection_state = WiFiConnect(ssid, password);
  if (!connection_state) // if not connected to WIFI
    Awaits();          // constantly trying to connect

delay(5000);

  int tiltSensed = digitalRead(tiltSensor);

  if (tiltSensed == 0) {
    EMailSender::EMailMessage message;
    message.subject = "Garage Door Closed";
    message.message = "Door Open  <br>Voltage= " + String(Tvoltage) ;
 //   const char* arrayOfEmail[] = {"donbrew9@gmail.com"};

    EMailSender::Response resp = emailSend.send("donbrew9@gmail.com", message);

    Serial.println("Sending status: ");
    Serial.println(resp.status);
    Serial.println(resp.code);
    Serial.println(resp.desc);
  } else  {
    EMailSender::EMailMessage message;
    message.subject = "Garage Door Open";
    message.message = "Door Closed  <br>Voltage= " + String(Tvoltage) ;
 //   const char* arrayOfEmail[] = {"donbrew9@gmail.com"};

    EMailSender::Response resp = emailSend.send("donbrew9@gmail.com", message);

    Serial.println("Sending status: ");
    Serial.println(resp.status);
    Serial.println(resp.code);
    Serial.println(resp.desc);
  }
  {
    Serial.println("Deep Sleep");
    ESP.deepSleep(0);
  }
}
