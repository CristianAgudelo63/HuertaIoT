/**
 * ------------------------------------------------------------------------------
 *         SISTEMA DE RIEGO AUTOMATIZADO CON IoT PARA HUERTA INTELIGENTE
 * ------------------------------------------------------------------------------
 * 
 * OPEN SOURCE DESARROLLADO POR: 
 * 
 *  - DIEGO A. TRUJILLO
 *  - CRISTIAN AGUDELO
 *  - YOINER A. LEUDO
 *  - MALENA HERNANDEZ
 *  - YULIANA OSORIO
 *  - ISABELLA TABORDA
 *  - CAMILO RIVERO
 *  - CESAR ACEVEDO
 *
 * ÚLTIMA ACTUALIZACIÓN 01 OCT 2023 
**/

#include <SPI.h>
#include <Ethernet.h>


const int bomba = 7; // salida a la bomba es al pin 13
const int humedad = A0; // la humedad al analogico 0

/**
 * CONFIGURACIÓN DE RED EN SKETCH DE ARDUINO
 *
 * byte mac[] = { Direccion física MAC de la tarjeta Shield Ethernet }
 * byte ip[] = { Dirección IP Local (LAN), en el segmento de red correspondiente }
 * byte gateway[] = { Puerta de enlace (dirección IP del Router) }
 * byte subnet[] = { Máscara de Sub Red }
 * EthernetServer server( Puerto para página web en localhost );
*/

byte mac[] = { 0xDE,0xAD,0xBE,0xEF,0xFE,0xED };
byte ip[] = { 192,168,1,250 };
byte gateway[] = { 192,168,1,1 };
byte subnet[] = { 255,255,255,0 };
EthernetServer server(80);     
String readString;

void setup() {

  Serial.begin(9600);
  pinMode(bomba, OUTPUT);

  pinMode(3, OUTPUT); // Se configura como salidas los puerto3
  Ethernet.begin(mac, ip, gateway, subnet); // Inicializa la conexion Ethernet y el servidor
  server.begin();
  Serial.print("El Servidor es: ");
  Serial.println(Ethernet.localIP()); // Imprime la direccion IP Local

}

void loop() {

  int conversion = map(analogRead(humedad), 0, 1023, 100, 0); // convertir a porcentaje
  int SensorValue = analogRead(humedad); //take a sample
  Serial.print(conversion);
  Serial.print(" %humedad ");
  Serial.println("  ");

  if (SensorValue > 500) {
    Serial.println("La tierra está seca, riego");
    digitalWrite(bomba, HIGH);
  } else {
    Serial.println("La tierra está humeda");
    digitalWrite(bomba, LOW);
  }
  delay(1000);

  //EMPIEZA SHIELD ETERNET
  EthernetClient cliente = server.available(); // Inicializa cliente como servidor ethernet
  if (cliente) {
    boolean currentLineIsBlank = true;
    while (cliente.connected()) {
      if (cliente.available()) {
        char c = cliente.read();
        //Lee caracter por caracter HTTP
        if (readString.length() < 100) {
          readString += c;  //Almacena los caracteres a un String
        }

        if (c == '\n' && currentLineIsBlank) {
          cliente.println("HTTP/1.1 200 OK");
          cliente.println("Content-Type: text/html"); // Envia el encabezado en codigo HTML estandar
          cliente.println("Connection: close");
          cliente.println("Refresh: 5"); // refresca la pagina automaticamente cada 5 segundos
          cliente.println();
          cliente.println("<!DOCTYPE HTML>");
            cliente.println("<html>");
              cliente.println("<HEAD>");
                cliente.println("<TITLE>HUERTA IOT FESA</TITLE>");
              cliente.println("</HEAD>");
            cliente.println("<BODY>");
              cliente.println("<body style=\"background-color: #fff52d;\">"); //FONDO DE PAGINA
              cliente.println("<hr />");
              // cliente.println("<H1 style=\"color: blue;\">SMART FARM </H1>");
              cliente.println("<div style=\"text-align: center;\">");
                cliente.println("<h1 style=\"color: blue;\">SMART FARM</h1>");
              cliente.println("</div>");

              cliente.println("<H2 style=\"color: green;\"> I.E FEDERICO SIERRA ARANGO centrodemonitoreofesa@gmail.com</H1>");
              cliente.println("<br />");
              cliente.println("<H2>Comunicacion Arduino Shiel Eternet</H2>");
              cliente.println("<H2>ELECTROVALVULA1 AUTOMATICA</H2>");

              cliente.println("<center>");
                cliente.println("Lectura del porcentaje de humedad");
                cliente.println("<br />");

                int SensorValue = analogRead(humedad);
                cliente.print("HUMEDAD DEL TERRENO");
                cliente.print(" es ");
                cliente.println("<br />");

                // cliente.print(conversion); //entrega valor de 1023 a 0% y 0 a 100%
                // cliente.print("<p style=\"font-size: 28px;\">"); // Cambia el tamaño de fuente a 24px (puedes ajustarlo según tus necesidades)
                //cliente.print(conversion);
                //cliente.print("<input type=\"text\" value=\"");
                //cliente.print(conversion);
                //cliente.print("\" />");
                //cliente.print("</p>");
                cliente.print("<p style=\"font-size: 28px;\">"); // Cambia el tamaño de fuente a 28px (puedes ajustarlo según tus necesidades)
                  cliente.print("<input type=\"text\" style=\"font-size: inherit;\" value=\"");
                  cliente.print(conversion);
                  cliente.print("\" />");
                cliente.print("</p>");
              cliente.println("</center>");

              // cliente.println("<br />");
              cliente.println("<H3>ACTIVAR ELECTROVALVULA2 DE SEGURIDAD</H3>");
              //cliente.println("<br />");
              //encender o apagar el pin 3 donde se puede instalar otra electrovalvula o una lampara
              //   cliente.println("<br />"); 
              //    cliente.print("<a href=\"/?button3off\"\"> PRENDER Pin3</a> ");
              //    cliente.println(" | | | ");
              //   cliente.println("<a href=\"/?button3on\"\"> APAGAR Pin3</a><br /> ");   
              //   cliente.println("<br />");
              cliente.print("<a href=\"/?button3off\"\">");
                cliente.print("<button style=\"background-color: green; color: white;\">"); // Estilo para el botón APAGAR
                  cliente.print("<span class=\"material-icons\">ELECTROVALVULA2</span>"); // Icono de APAGAR
                  cliente.print(" ON Pin3");
                cliente.print("</button>");
              cliente.print("</a>");

              cliente.println(" | | | ");

              cliente.print("<a href=\"/?button3on\"\">");
                cliente.print("<button style=\"background-color: red; color: white;\">"); // Estilo para el botón PRENDER
                  cliente.print("<span class=\"material-icons\">ELECTROVALVULA2</span>"); // Icono de PRENDER
                  cliente.print(" OFF Pin3");
                cliente.print("</button>");
              cliente.print("</a><br />");

              cliente.println("<br />");
              cliente.println("<H3>DESARROLLADORES</H3>");

              cliente.println("MALENA HERNANDEZ, YULIANA OSORIO, ISABELLA TABORDA, CAMILO RIVERO");
              cliente.println("<br />");
              cliente.println("CESAR ACEVEDO, YOINER LEUDO, CRISTIAN AGUDELO, DIEGO A. TRUJILLO ");

              //control del arduino si un boton es presionado
              if (readString.indexOf("?button3on") > 0) {
                digitalWrite(3, HIGH);
              }
              if (readString.indexOf("?button3off") > 0) {
                digitalWrite(3, LOW);
              }
              // Limpia el String(Cadena de Caracteres para una nueva lectura
              readString = "";
            cliente.println("</body>");
          cliente.println("</html>"); //ESTOS SON PARA REFRESCAR LA PAGINA
          break;
        }
        if (c == '\n') {
          currentLineIsBlank = true;
        } else if (c != '\r') {
          currentLineIsBlank = false;
        }
      }
    }
    delay(10); // Da tiempo al Servidor para que reciba los datos 15ms
    cliente.stop(); // cierra la conexion
  }
}