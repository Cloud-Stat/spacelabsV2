int tokenizeString(char* cadena){
  char *tmp=NULL;
  int i = 0; 
  tmp = strtok(cadena, " ");  
  while (tmp) {
    if (tmp=="??.")
        result[i++] = "0";
    else{
        result[i++] = tmp;
    }
    tmp = strtok(NULL, " ");
    delay(10);
  }
  return i;
}

boolean detectarHora(){
  result[0].trim();
  Serial.println("Campo 0 : "+result[0]+" "+String(result[0].indexOf(":"))+" "+String(result[0].lastIndexOf(":")));
  if(result[0].indexOf(":")==2 && result[0].lastIndexOf(":")==5){
    return true;
  }else{
    return false;
  }
}

void printTokens(int cant_tokens){
  Serial.println("------Received Tokens------");
  for (int i=0;i<cant_tokens;i++){
    Serial.println(String(i)+". "+result[i]);
  }
  Serial.println("---------------------------");
}
