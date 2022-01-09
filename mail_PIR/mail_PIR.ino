//Más proyectos en http://www.rogerbit.com
//Suscribete en http://www.youtube.com/user/carlosvolt?sub_confirmation=1
//Grupo en Facebook https://www.facebook.com/groups/RogerBit/
/*
 Circuito:
 Pin usados por el escudo ethernet 10, 11, 12, 13
 Tampoco usar el pin 4 ya que es para la parte del lector sd
 El pin número 5 es usado para conectar un led de monitoreo
 El pin número 6 se conecta a la pata OUT del sensor PIR que monitoreará el movimiento 
 */

#include <SPI.h>
#include <Ethernet.h>
//int led = 5;                // Pin 13 encenderá un led al detectar un movimiento
//int SensorPir = 6;               // elegir el pin de entrada para el sensor PIR
//int valor = 0;                    // variable para leer el estado del pin 6

void(* Resetea) (void) = 0;//Funcíon Reset por soft para el arduino (como si apretaramos el botón reset)

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };//Dirección MAC de nuestro módulo ethernet
char server[] = "192.168.10.6"; //Cambiar por la url del servidor a usar   
IPAddress ip(192,168,10,78);// Tomará esta ip si el servidor DHCP falla
EthernetClient client;

void setup() {
 //pinMode(led, OUTPUT);      // declarmos led como salida(pin 5)
  //pinMode(SensorPir, INPUT);     // declaramos SensorPir como entrada(pin 6)
   //digitalWrite(led, LOW);//Led 5 apagado
  Serial.begin(9600);//Velocidad del puerto serie
  while (!Serial) {
    ; 
  }
Serial.println("Sistema Listo");//Nos indica que ya estamos en condiciones de enviar un correo

}

void loop() {
int valor = 1;  // leemos el valor de entrada
  if (valor == 1) {            // comprobamos si la entrada es HIGH
   
      Envio_mail();//Llama a la función Envio_mail     
  }  
}
//////////////////////////////////
void Envio_mail() {
 delay(300);
////////////DHCP Activado////////////////////////////////   
  if (Ethernet.begin(mac) == 0) {
    Serial.println("No se pudo configurar Ethernet mediante DHCP");
    
    Ethernet.begin(mac, ip);
  }
////////////DHCP desactivado////////////////
//Ethernet.begin(mac, ip);
 
  delay(100);
  Serial.println("conectando espere...");
 
  if (client.connect(server, 80)) {
    Serial.println("connectado :-)");//Si se establece la conexión
    
    // Make a HTTP request:
    client.println("GET /arduino/email.php HTTP/1.1");// Colocar la dirección del archivo que se va a leer en el servidor
    client.println("Host: 192.168.10.6");//Dirección del servidor
    client.println();
    delay(2000);
    Serial.println("Mail Enviado");
    delay(5000);
 Resetea();     
  }
}
