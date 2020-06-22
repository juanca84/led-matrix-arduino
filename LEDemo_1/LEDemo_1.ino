/*  TITULO: Prueba panel luminoso de Matrices LED 8x8 con driver MAX7219.

   
    DESCRIPCIÓN DEL PROGRAMA
   
    Con este programa vamos a visualizar mensajes de texto desplazandose de derecha a izquierda a través
    de un panel luminoso compuesto por 4 matrices LED 8x8 con driver MAX7219.
   
   
    ESQUEMA DE CONEXION
   
                                      +-----+
         +----[PWR]-------------------| USB |--+
         |                            +-----+  |
         |         GND/RST2  [ ][ ]            |
         |       MOSI2/SCK2  [ ][ ]  A5/SCL[ ] |
         |          5V/MISO2 [ ][ ]  A4/SDA[ ] |  
         |                             AREF[ ] |
         |                              GND[ ] |
         | [ ]N/C                    SCK/13[ ] |  
         | [ ]IOREF                 MISO/12[ ] |   Pin DIN del módulo MAX7219
         | [ ]RST                   MOSI/11[ ] |   Pin CLK del módulo MAX7219
         | [ ]3V3    +---+               10[ ] |   Pin CS del módulo MAX7219
         | [ ]5v    -| A |-               9[ ] |   
         | [ ]GND   -| R |-               8[ ] |   
         | [ ]GND   -| D |-                    |
         | [ ]Vin   -| U |-               7[ ] |  
         |          -| I |-               6[ ] |  
         | [ ]A0    -| N |-               5[ ] |  
         | [ ]A1    -| O |-               4[ ] |  
         | [ ]A2     +---+           INT1/3[ ] |  
         | [ ]A3                     INT0/2[ ] |  
         | [ ]A4/SDA  RST SCK MISO     TX>1[ ] |  
         | [ ]A5/SCL  [ ] [ ] [ ]      RX<0[ ] |  
         |            [ ] [ ] [ ]              |
         |  UNO_R3    GND MOSI 5V  ____________/
          \_______________________/
 
  NOTAS:
 
   - La alimentación del panel luminoso (VCC y GND) puede ir directamente conectada a los pines
     +5V y GND de nuestro Arduino, aunque es recomendable alimentar el panel luminoso
     mediante una fuente de alimentación de 5VDC/3000mA para evitar problemas en el puerto USB
     de nuestro PC. 
*/
#include <LedControl.h>

const int DIN_PIN = 12;
const int CS_PIN = 10;
const int CLK_PIN = 11;

const uint64_t IMAGES[] = {
  0x0000fcf3f3fc0000,
  0x000789f189070000,
  0x00c0e07e02040000,
  0x00c0e07c0662723e,
  0x3008fb3ffb083000,
  0x003008fb3ffb0830,
  0x000608fb3ffb0806,
  0x0608fb3ffb080600
};
const int IMAGES_LEN = sizeof(IMAGES)/8;


LedControl display = LedControl(DIN_PIN, CLK_PIN, CS_PIN);


void setup() {
  display.clearDisplay(0);
  display.shutdown(0, false);
  display.setIntensity(0, 10);
}

void displayImage(uint64_t image) {
  for (int i = 0; i < 8; i++) {
    byte row = (image >> i * 8) & 0xFF;
    for (int j = 0; j < 8; j++) {
      display.setLed(0, i, j, bitRead(row, j));
    }
  }
}

int i = 0;

void loop() {
  displayImage(IMAGES[i]);
  if (++i >= IMAGES_LEN ) {
    i = 0;
  }
  delay(5 00); //Tiempo en milisegundos
}
