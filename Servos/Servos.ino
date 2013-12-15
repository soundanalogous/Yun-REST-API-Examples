/*
  Bridge Servo controller
  Context: Arduino, for Yún
  
  Controls 2 servo motors
  
  Prepare your Yun's SD card with an empty folder in the SD root named 
  "arduino" and a subfolder of that named "www". 
  This will ensure that the Yún will create a link 
  to the SD to the "/mnt/sd" path.
 
  When you upload your sketch, these files will be placed in
  the /arduino/www/Servos folder on your SD card.
 
  You can then go to http://arduino.local/sd/Servos
  to see the output of this sketch.  

  created 14 July 2013
  by Jeff Hoefs
  */
  
#include <Bridge.h>
#include <YunServer.h>
#include <YunClient.h>
#include <Servo.h>

YunServer server;

Servo servo1;
Servo servo2;

void setup() {
  
  servo1.attach(9);
  servo2.attach(10);
  
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  // begin() is blocking and takes about 2 seconds to complete
  Bridge.begin();
  digitalWrite(13, HIGH);
  
  // Listen for incoming connection only from localhost
  // (no one from the external network can connect)
  server.listenOnLocalhost();
  server.begin();
}

void loop() {
  // Get clients coming from the server
  YunClient client = server.accept();
  
  if (client) {
    process(client);
    client.stop();
  }
  
  delay(50);
}

void process(YunClient client) {
  if (client.available() > 0) {
    String command = client.readStringUntil('/');
    
    if (command == "servos") {
      servoCommand(client);    
    }
  }
}

// expecting "/(int)id/(String)angle/(int)value"
int servoCommand(YunClient client) {
  int id, angle;
  
  id = client.parseInt();

  // provide meaningful error messages to the client application
  if (id < 1 || id > 2) {
    client.print(F("Error: Servo "));
    client.print(id);
    client.println(F(" not attached"));
    return 0;
  }
  
  client.read();  // skip "/"
  String servoCommand = client.readStringUntil('/'); // skip "angle/"
  
  if (servoCommand != "angle") {
    client.print(F("Error: Servo command "));
    client.print(servoCommand);
    client.println(F(" not defined"));
    return 0;
  }
  
  angle = client.parseInt();
  
  if (angle < 0 || angle > 180) {
    client.print(F("Error: Angle value must be between 0 and 180 degrees"));
    return 0;
  }
  
  if (id == 1) {
    servo1.write(angle);
  }
  else if (id == 2) {
    servo2.write(angle);
  }
  
  return 1;
}

