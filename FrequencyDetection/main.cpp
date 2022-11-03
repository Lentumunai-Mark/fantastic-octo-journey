#include <Arduino.h>
#include <ESP32Servo.h>

Servo myservo;
uint16_t LED_Pin = 32;
namespace monitoringSystem
{
    class babyMonitor{
        protected:
        
        //the volume to detect if the baby is crying or no
        int isCrying; 
        //  Sometimes the baby start mumbling or playing, specially at the age when he starts learning how to speak 
        int isMumbling; 
        //This is to configure the baby 
        

        public: 
        
         void setVoice(int voiceLevel, boolean isC)
          // set voice level, isC =True to set the voice level of "isCrying" else to set the voice level of isMumbeling
         {
           if (isC){
             isCrying= voiceLevel;
           }
           else{
             isMumbling= voiceLevel;
           
           }
            
         }
        void monitor() {
               
                boolean hasCalledMom= false;
                int noise;
                  
                delay(1000); 
                noise = analogRead(LED_Pin);
                Serial.println(noise);
                
                if (noise < isMumbling) {
                // digitalWrite(fistLed, LOW);
                // digitalWrite(secLed, LOW);
                // myservo.write(0);
                Serial.println("No noise");

                }
                if (noise > isMumbling && noise < isCrying ) {
                // digitalWrite(fistLed, HIGH);
                // digitalWrite(secLed, LOW);
                for(int i = 0; i < 1000; i++){
                  myservo.write(0);
                  delay(1000);
                  myservo.write(90);
                  delay(1000);
                }
                Serial.println("Mumbling");
                }
              
                if (noise > isCrying) {
                // digitalWrite(fistLed, HIGH);
                // digitalWrite(secLed, HIGH);
                myservo.write(0);
                delay(1000);
                myservo.write(90);
                Serial.println("Crying");
                }
        }
    };
};

monitoringSystem::babyMonitor _babyMonitor;
void setup() {
  Serial.begin(9600);
  myservo.attach(17); 

  myservo.write(0);

  delay(2000);
  // set isCrying at 600
  _babyMonitor.setVoice(200,false);
  // set isMumbling at 300
  _babyMonitor.setVoice(400,true);
}

void loop() {
  _babyMonitor.monitor();
}
/*
integrate withe the input of the sound sensor - Done
Optimize the sound sensor to be accurate - Pending
Design the cradle - Pending
Finish up on all - Pending
*/


/*

void setup(){
  Serial.begin(9600);
    // set isCrying at 600
    _babyMonitor.setVoice(200,false);
    
    // set isMumbling at 300
    _babyMonitor.setVoice(400,true);
}
void loop(){
    _babyMonitor.monitor();
}


*/