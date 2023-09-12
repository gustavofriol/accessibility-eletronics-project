#include <RHReliableDatagram.h>
#include <RH_ASK.h>
#include <SPI.h>

#define TX_ADDRESS 1 // Define o pino do arduino que funcionará como TX
#define RX_ADDRESS 2 // Define o pino do arduino que funcionará como RX
#define Linha "177"    // Define a linha do ônibus 

RH_ASK driver;
RHReliableDatagram manager(driver, TX_ADDRESS);

uint8_t count = 1;
uint8_t data[] = Linha;
uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];

void setup()
{
  Serial.begin(9600);
  if (!manager.init())
    Serial.println("Falha na inicializacao");
}

void loop()
{
  Serial.print("Transmitindo mensagem n. ");
  Serial.println(count);
  if (!manager.sendtoWait(data, sizeof(data), RX_ADDRESS))
  {
    Serial.print("Falha ao enviar mensagem: ");
    Serial.println((char*)data); // Mostra a mensagem que falhou em ser enviada
    count++;
  }
  else
  {
    Serial.print("Mensagem enviada com sucesso: ");
    Serial.println((char*)data); // Mostra a mensagem enviada com sucesso
  }
  delay(500);
}
