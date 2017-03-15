void serialEvent() {
  long previous = millis();
  while (Serial3.available() && ((millis() - previous) < 1000)) {
    char inChar = (char)Serial3.read();
    if (inChar == '\n') {
      stringComplete = true;
    }else{
      inputString += inChar;
    }
  }
  //inputString.trim();
  Serial3.flush();
}
