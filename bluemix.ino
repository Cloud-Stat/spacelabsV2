void postBluemix(){
  char clientStr[50];
  char topicStr[26];  
  clientName.toCharArray(clientStr,50);
  topicName.toCharArray(topicStr,26);
  //Check if connected
  if (!client.connected()) {
    Serial.println("Trying to connect to: "+String(clientStr));
    client.connect(clientStr);
  }
  //When connected post
  if (client.connected() ) {
    String json = buildJson();
    char jsonStr[200];
    json.toCharArray(jsonStr,200);
    boolean pubresult = client.publish(topicStr,jsonStr);
    Serial.print("Attempting to send ");
    Serial.println(jsonStr);
    Serial.print("to ");
    Serial.println(topicStr);
    if (pubresult)
      Serial.println("successfully sent");
    else
      Serial.println("unsuccessfully sent");
  }
}

String buildJson() {
  result[5].trim();
  result[6].trim();
  String data = "{\n";
    data+= "\"d\": {";
              data+="\n";
              data+="\"myName\": \"MDI ALPHA\",";
              data+="\n";
              //data+="\"serialString\": \"";data+=inputString;data+="\"\n";
              data+="\"presion\":";
              data+=result[5];data+=",\n";
              data+="\"O2\": ";data+=result[6];data+="\n";              
          data+="}\n";
  data+="}";
  return data;
}
