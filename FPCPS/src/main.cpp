//bIBLIOTECAS NO NATIVAS DE ESPRESSIF
#include <Arduino.h> 
#include <WiFi.h> 
//------------------------------------------------------------------------------
//VARIABLES WI-FI
WiFiServer server(80); //NUMERO DE YTUNEL PARA HTTP
const char* ssid     = "Totalplay-979D";
const char* password = "979D7A1Bb3H677Uf";

int contconexion = 0;
String header; // Variable para guardar el HTTP request
//Manual
String ForwardS = "off"; // Variables auxiliares que guardan el estado de la salida 
String BackwardS = "off";
String StopS = "off";
String RightS = "off";
String LeftS = "off";
//Automatico
String StartAuto = "off";
String StopAuto = "off";

const int Forward = 25;     //Asignar los GPIO a cada salida COMO PRUEBA
const int Backward = 27;
const int Stop = 32;
const int Left = 33;
const int Right = 35;
const int StartA = 17;
const int StopA = 16;
int conexion = 0;
//------------------------------------------------------------------------------
//CÓDIGO HTML PARA PÁGINA WEB
String pagina = "<!DOCTYPE html>"
"<html>"
"<style>"
"body { background-image: url('https://cdn.pixabay.com/photo/2016/09/08/12/00/stars-1654074_960_720.jpg'); }"
"#centro { text-align: center; color: rgb(255, 255, 255);font-size: 300%; font-family: 'Franklin Gothic Medium', 'Arial Narrow', Arial, sans-serif; }"
"#par { color: rgb(255, 255, 255);font-size: 150%};"
".slider-wrapper { display: inline-block; width: 20px; height: 50px;  padding: 0; }"
".slider-wrapper input {  width: 250px;  height: 20px;margin: 0;transform-origin: 270px -100px;transform: rotate(-90deg); }"
"a.animated-button:link, a.animated-button:visited { margin: 20px 50px 0; padding: 9px 10px;color: #fff;font-size: 14px;font-weight: bold;text-align: center; text-decoration: none;letter-spacing: .5em; }"
"a.animated-button.thar-three { color: #fff; display: block; position: relative; border: 2px solid #3b59ff; }"
"a.animated-button.thar-three:hover { color: #000 !important; background-color: transparent; }"
"a.animated-button.thar-three:hover:before { left: 0%; right: auto; width: 100%;}"
"a.animated-button.thar-three:before { position: absolute; top: 0px;right: 0px; height: 100%;width: 0px;z-index: -1;content: '';color: #000 !important; background: #2c7baf;transition: all 0.4s cubic-bezier(0.42, 0, 0.58, 1) 0s; }"

"</style>"
"<title> Robot evasor de obstaculos con Freertos </title> "
"<body> "
"<link  rel='icon'   href='https://esphome.io/_images/esp32.png' type='image/png' />"

"<div id='fondo'> <p id='centro'>Cyber physical Systems</p><p id='centro' style='text-align: center; font-size: 130%;>Sistemas Ciberfisicos.</p>"
"<p id='par' style='text-align: center; font-size: 120%; ' > Team Members: </p> <p id='par' style='text-align: center; font-size: 120%;' > Villavicencio Ramirez Uriel-18220798 </p>"
"<p id='par' style='text-align: center; font-size: 120%; ' > Ramirez Flores Daniel-18220762 </p> <p id='par' style='text-align: center; font-size: 120%;' > Trujillo Rodriguez Erika Kassandra-16221433  </p>"
"<p id='par' style='text-align: center; ' > Robot Movement: </p>"

"<p class='col-md-3 col-sm-3 col-xs-6'> <a href='/auto' class='btn btn-sm animated-button thar-three'>AUTO</a> </p>"
"<p class='col-md-3 col-sm-3 col-xs-6'> <a href='/forward' class='btn btn-sm animated-button thar-three'>FORWARD</a> </p>"
"<p class='col-md-3 col-sm-3 col-xs-6'> <a href='/back' class='btn btn-sm animated-button thar-three'>BACK</a> </p>"
"<p class='col-md-3 col-sm-3 col-xs-6'> <a href='/left' class='btn btn-sm animated-button thar-three'>LEFT</a> </p>"
"<p class='col-md-3 col-sm-3 col-xs-6'> <a href='/right' class='btn btn-sm animated-button thar-three'>RIGHT</a> </p>"
"<p class='col-md-3 col-sm-3 col-xs-6'> <a href='/stop' class='btn btn-sm animated-button thar-three'>STOP</a> </p>"       
"</body>"
"</html>";
//------------------------------------------------------------------------------
//VARIABLES MOTORES
int MD = 23; //MOTOR DERECHA ATRAS
int MI = 22; //MOTOR IZQUIERDA ADELANTE
int MD2 = 12; //MOTOR DERECHA ATRAS
int MI2 = 14; //MOTOR IZQUIERDA ADELANTE
//------------------------------------------------------------------------------
//VARIABLES ULTRASÓNICO
int Trigger = 5;
int Echo = 18;
int Duracion;
int Distancia;
//------------------------------------------------------------------------------
//TAREAS
//------------------------------------------------------------------------------
//TAREA PÁGINA
static void pag(void *parameter){
  vTaskDelay(1);
  for(;;){
  WiFiClient client = server.available();   // Escucha a los clientes entrantes

   if (client) {                             // Si se conecta un nuevo cliente
    Serial.println("New Client.");          // 
    String currentLine = "";                //
    while (client.connected()) {            // loop mientras el cliente está conectado
      if (client.available()) {             // si hay bytes para leer desde el cliente
        char c = client.read();             // lee un byte
        Serial.write(c);                    // imprime ese byte en el monitor serial
        header += c;
        if (c == '\n') {                    // si el byte es un caracter de salto de linea
          // si la nueva linea está en blanco significa que es el fin del 
          // HTTP request del cliente, entonces respondemos:
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            // enciende y apaga el GPIO
           if (header.indexOf("GET /forward") >= 0) {
              Serial.println("Forward");
              ForwardS = "on";
              conexion = 1;
              digitalWrite(Forward, HIGH);
              Serial.println("Forward");

            } else if (header.indexOf("GET /forward") >= 0) {
              Serial.println("Forward");
              ForwardS = "off";
              digitalWrite(Forward, LOW);
              /////////////////////////////////////      
            } else if (header.indexOf("GET /back") >= 0) {
              Serial.println("Backward");
              BackwardS = "on";
              conexion = 2;
              digitalWrite(Backward, HIGH);
               Serial.println("Backward");
            } else if (header.indexOf("GET /back") >= 0) {
              Serial.println("Backward");
              BackwardS = "off";
              digitalWrite(Backward, LOW);
            
               //////////
            } else if (header.indexOf("GET /stop") >= 0) {
              Serial.println("StopManual");
              StopS = "on";
              conexion = 0;
              digitalWrite(Stop, HIGH);
                Serial.println("Stop");
            } else if (header.indexOf("GET /stop") >= 0) {
              Serial.println("StopManual");
              StopS = "off";
              digitalWrite(Stop, LOW);
            
              ////////
            } else if (header.indexOf("GET /left") >= 0) {
              Serial.println("Left");
              LeftS = "on";
              conexion = 3;
              digitalWrite(Left, HIGH);
              Serial.println("Left");
            } else if (header.indexOf("GET /left") >= 0) {
              Serial.println("Left");
              LeftS = "off";
              digitalWrite(Left, LOW);
            
            //////////
            } else if (header.indexOf("GET /right") >= 0) {
              Serial.println("Right");
              RightS = "on";
              conexion = 4;
              digitalWrite(Right, HIGH);
            } else if (header.indexOf("GET /right") >= 0) {
              Serial.println("Right");
              RightS = "off";
              digitalWrite(Right, LOW);    
            

            } else if (header.indexOf("GET /auto") >= 0) {
              Serial.println("Auto");
              StartAuto = "on";
              conexion = 5;
              digitalWrite(StartA, HIGH);
            } else if (header.indexOf("GET /auto") >= 0) {
              Serial.println("Auto");
              StartAuto = "off";
              digitalWrite(StartA, LOW);    
            }
            //--------------------------------------------
         
            // Muestra la página web
            client.println(pagina);
            
            // la respuesta HTTP temina con una linea en blanco
            client.println();
            break;
          } 
          else { // si tenemos una nueva linea limpiamos currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // si C es distinto al caracter de retorno de carro
          currentLine += c;      // lo agrega al final de currentLine
        }
      }
    }
    // Limpiamos la variable header
    header = "";
    // Cerramos la conexión
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
    
}
}
//------------------------------------------------------------------------------
//TAREAS MANUAL
void avanzar(void *parameter){
  for(;;){
    vTaskDelay(1);
    if (conexion == 1){
    digitalWrite(MI,HIGH);
    digitalWrite(MI2,HIGH);
    Serial.println("Adelante");
    delay(1);
    }
    else if(conexion == 0) {
      digitalWrite(MI,LOW);
      digitalWrite(MI2,LOW);
    }
    }
  vTaskDelay(10);
}

void atras(void *parameter){
  for(;;){
    vTaskDelay(1);
    if (conexion == 2){
    digitalWrite(MD,HIGH);
    digitalWrite(MD2,HIGH);
    Serial.println("Atras");
    delay(1);
    }
    else if (conexion == 0){
    digitalWrite(MD2,LOW);
    digitalWrite(MD,LOW);
    }
    }
  vTaskDelay(10);
}

void izquierda(void *parameter){
  for(;;){
    vTaskDelay(1);
    if (conexion == 3){
    digitalWrite(MD,HIGH);
    digitalWrite(MI,LOW);
    digitalWrite(MI2,HIGH);
    digitalWrite(MD2,LOW);
    Serial.println("Izquierda");
    delay(2000);
    }
    else if (conexion == 0){
    digitalWrite(MD,LOW);
    digitalWrite(MI2,LOW);
    
    }
    }
  vTaskDelay(10);
}

void derecha(void *parameter){
  for(;;){
    vTaskDelay(1);
    if (conexion == 4){
    digitalWrite(MD,LOW);
    digitalWrite(MI,HIGH);
    digitalWrite(MI2,LOW);
    digitalWrite(MD2,HIGH);
    Serial.println("Derecha");
    delay(2000);
    }
    else if (conexion == 0){
    digitalWrite(MD,LOW);
    digitalWrite(MI,LOW); 
    digitalWrite(MD2,LOW);
    digitalWrite(MI2,LOW);
    }
  }
  vTaskDelay(10);
}

void ultra(void *parameter){
  for(;;){
    vTaskDelay(1);
    digitalWrite(Trigger,HIGH);
    delay(1);
    digitalWrite(Trigger,LOW);
    Duracion = pulseIn(Echo,HIGH);
    Distancia = Duracion/58.2;
    Serial.println("Distancia: ");
    Serial.println(Distancia);
    Serial.println("Conexión: ");
    Serial.println(conexion);
    delay(200);
    }
  vTaskDelay(10);
}
//------------------------------------------------------------------------------
//TAREA RUTINA DE AUTOMÁTICO
void loop10(void *parameter){
  for(;;){
    vTaskDelay(1);
    if(conexion == 5){
    if(Distancia>15){
    digitalWrite(MD,HIGH);
    digitalWrite(MI,HIGH);
    }
    else{
    digitalWrite(MD,LOW);
    digitalWrite(MI,LOW);
    delay(2000);
    }
    digitalWrite(MD,HIGH);
    digitalWrite(MI,LOW);
    digitalWrite(MI2,LOW);
    digitalWrite(MD2,HIGH);
    delay(5000);
  }
  }
}
//------------------------------------------------------------------------------
void setup() {
  Serial.begin(115200);
//------------------------------------------------------------------------------
//CONFIGURACIÓN DE PINES DE MOTORES
  pinMode(MD,OUTPUT);
  pinMode(MI,OUTPUT);
  pinMode(MD2,OUTPUT);
  pinMode(MI2,OUTPUT);
//------------------------------------------------------------------------------
//CONFIGURACIÓN DE PINES ULTRASÓNICO
  pinMode(Trigger,OUTPUT);
  pinMode(Echo,INPUT);
//------------------------------------------------------------------------------
//CONFIGURACIÓN WI-FI
  WiFi.begin(ssid, password);
  //Cuenta hasta 50 si no se puede conectar lo cancela
  while (WiFi.status() != WL_CONNECTED and contconexion <50) { 
    ++contconexion;
    delay(500);
    Serial.print(".");
  }
  if (contconexion <50) {
      Serial.println("");
      Serial.println("WiFi conectado");
      Serial.println(WiFi.localIP());
      server.begin(); // iniciamos el servidor
  }
  else { 
      Serial.println("");
      Serial.println("Error de conexion");
  }
//------------------------------------------------------------------------------
  xTaskCreatePinnedToCore(avanzar,"Task_1",1000,NULL,1,NULL,0);
  xTaskCreatePinnedToCore(atras,"Task_2",1000,NULL,1,NULL,0);
  xTaskCreatePinnedToCore(izquierda,"Task_3",1000,NULL,1,NULL,0);
  xTaskCreatePinnedToCore(derecha,"Task_4",1000,NULL,1,NULL,0);
  xTaskCreatePinnedToCore(ultra,"Task_7",1000,NULL,1,NULL,0);
  xTaskCreatePinnedToCore(pag,"Task_8",2000,NULL,1,NULL,1);
  xTaskCreatePinnedToCore(loop10,"Task_9",1000,NULL,1,NULL,0);
}
//--------
void loop() {
  
}