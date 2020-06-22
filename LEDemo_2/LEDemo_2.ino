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
   - Para conectar las 4 matrices LED 8x8 con driver MAX7219 en cascada, es suficiente con conectar
     las salidas del módulo situado más a la derecha (el que hemos conectado a nuestro Arduino), a las
     entradas del inmediatamente anterior (el de su izquierda) y así sucesivamente hasta llegar al
     primer módulo, el cual deberá tener sus salidas desconectadas puesto que no se tiene que comunicar
     con ninguno otro. Todos los módulos tienen que estar correctamente alimentados.    
*/
#include <LedControl.h>

const int DIN_PIN = 12;
const int CS_PIN = 10;
const int CLK_PIN = 11;

//Números
const uint64_t IMAGES[] PROGMEM = {
  0x008088fefe808000,
  0x00c4e6a2929e8c00,
  0x0044c69292fe6c00,
  0x00302824fefe2000,
  0x004ece8a8afa7200,
  0x007cfe9292f66400,
  0x000606e2fa1e0600,
  0x006cfe9292fe6c00,
  0x004cde9292fe7c00,
  0x007cfe928afe7c00
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
  uint64_t image;
  memcpy_P(&image, &IMAGES[i], 8);

  displayImage(image);
  if (++i >= IMAGES_LEN ) {
    i = 0;
  }
  delay(1000);
}
