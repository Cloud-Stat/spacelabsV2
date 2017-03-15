void updateThingSpeak(String tsData){
  ethClient.stop();
  if (ethClient.connect(thingip, 80)){     
    Serial.println("connecting...");    
    ethClient.print("POST /update HTTP/1.1\n");
    ethClient.print("Host: api.thingspeak.com\n");
    ethClient.print("User-Agent: arduino-ethernet\n");
    ethClient.print("Connection: close\n");
    ethClient.print("X-THINGSPEAKAPIKEY: "+writeAPIKey+"\n");
    ethClient.print("Content-Type: application/x-www-form-urlencoded\n");
    ethClient.print("Content-Length: ");
    ethClient.print(tsData.length());
    ethClient.print("\n\n");
    ethClient.print(tsData);
    
    lastConnectionTime = millis();    
    if (ethClient.connected()){
      Serial.println("Connecting to ThingSpeak...");
      Serial.println();      
      failedCounter = 0;
    } else {
      failedCounter++;  
      Serial.println("Connection to ThingSpeak failed ("+String(failedCounter, DEC)+")");   
      Serial.println();
    }    
  }else{
    failedCounter++;
    Serial.println("Connection to ThingSpeak Failed ("+String(failedCounter, DEC)+")");   
    Serial.println();    
    lastConnectionTime = millis(); 
  }
}
