#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal.h>
 
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   
 
LiquidCrystal lcd(6, 7, 5, 4, 3, 2); 
 
char st[20];
 
void setup() 
{
  Serial.begin(9600);   
  SPI.begin();     
  mfrc522.PCD_Init();   
  Serial.println("Kartinizi Okutunuz...");
  Serial.println(); 
  lcd.begin(16, 2);  
  mensageminicial();
}
 
void loop() 
{
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  Serial.print("\nKart ID :");
  String conteudo= "";
  byte letra;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     conteudo.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     conteudo.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("İleti : ");
  conteudo.toUpperCase();
  if (conteudo.substring(1) == "F3 9A BC A9")
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("ID KABUL EDİLDİ!");
    delay(3000);
    mensageminicial();
  }
 
  else
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("ID REDDEDILDI !");
    delay(3000);
    mensageminicial();
  }
} 
 
void mensageminicial()
{
  lcd.clear();
  lcd.print(" HOS GELDINIZ");  
  lcd.setCursor(0,1);
  lcd.print("KARTI OKUTUNUZ");  
}