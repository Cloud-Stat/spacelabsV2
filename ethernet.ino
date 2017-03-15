void startEthernet(){  
  Serial.print("Start ethernet...");
   ethClient.stop();
  delay(1000);
  // Connect to network amd obtain an IP address using DHCP
  if (Ethernet.begin(mac) == 0){
    Serial.println("DHCP Failed, reset Arduino to try again");
  }else{
    Serial.println("Arduino connected to network using DHCP");
    printIPAddress();
  }
  delay(1000);
}

void printIPAddress(){
  Serial.print("IP address: ");
  for (byte thisByte = 0; thisByte < 4; thisByte++) {
    // print the value of each byte of the IP address:
    Serial.print(Ethernet.localIP()[thisByte], DEC);
    Serial.print(".");
  }
  Serial.println();
}
