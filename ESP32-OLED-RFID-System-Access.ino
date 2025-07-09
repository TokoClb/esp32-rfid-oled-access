#include <Wire.h>
#include <SPI.h>
#include <MFRC522.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// === OLED ===
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// === RFID ===
#define SS_PIN 5     // GPIO5 - SDA du module RFID
#define RST_PIN 4    // GPIO4 - RST
MFRC522 rfid(SS_PIN, RST_PIN);

// === Périphériques ===
#define BUZZER_PIN 13
#define LED_ROUGE 2
#define LED_VERTE 15

// === Structure utilisateur ===
struct Utilisateur {
  String uid;
  String nom;
  String prenom;
};

Utilisateur utilisateurs[] = {
  {"FA5E45A5", "CHAKA", "Joyce"},
  {"232B5127", "TOKO", "Caleb"}
  // U can add some users if u want, but flemme up to me, two users R anough
};

void setup() {
  Serial.begin(115200);

  // OLED
  Wire.begin(21, 22); // SDA = GPIO21, SCL = GPIO22
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("Erreur OLED");
    while (true);
  }

  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(10, 20);
  display.print("Scan un badge RFID...");
  display.display();

  // SPI & RFID
  SPI.begin(); // Par défaut : SCK=18, MISO=19, MOSI=23
  rfid.PCD_Init();

  // Sorties
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_ROUGE, OUTPUT);
  pinMode(LED_VERTE, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);
  digitalWrite(LED_ROUGE, LOW);
  digitalWrite(LED_VERTE, LOW);
}

void loop() {
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) return;

  // Lire l’UID
  String uidString = "";
  for (byte i = 0; i < rfid.uid.size; i++) {
    if (rfid.uid.uidByte[i] < 0x10) uidString += "0";
    uidString += String(rfid.uid.uidByte[i], HEX);
  }
  uidString.toUpperCase();

  Serial.print("UID détecté : ");
  Serial.println(uidString);

  bool utilisateurTrouve = false;
  String nom = "";
  String prenom = "";

  for (int i = 0; i < sizeof(utilisateurs) / sizeof(utilisateurs[0]); i++) {
    if (uidString == utilisateurs[i].uid) {
      nom = utilisateurs[i].nom;
      prenom = utilisateurs[i].prenom;
      utilisateurTrouve = true;
      break;
    }
  }

  display.clearDisplay();

  if (utilisateurTrouve) {
    // Affichage accepté
    display.setTextSize(1);
    display.setCursor(0, 18);
    display.print("Nom: ");
    display.println(nom);
    display.setCursor(0, 40);
    display.print("Prenom: ");
    display.println(prenom);
    display.display();

    // Action autorisée
    digitalWrite(LED_VERTE, HIGH);
    digitalWrite(BUZZER_PIN, HIGH);
    delay(200);
    digitalWrite(BUZZER_PIN, LOW);
    delay(1800);
    digitalWrite(LED_VERTE, LOW);

  } else {
    // Affichage refusé
    display.setTextSize(1);
    display.setCursor(20, 0);
    display.println("Badge inconnu !");
    display.setTextSize(2);
    display.setCursor(36, 20);
    display.println("ACCES");
    display.setCursor(30, 40);
    display.println("REFUSE");
    display.display();

    digitalWrite(LED_ROUGE, HIGH);
    digitalWrite(BUZZER_PIN, HIGH);
    delay(1000);
    digitalWrite(BUZZER_PIN, LOW);
    digitalWrite(LED_ROUGE, LOW);
  }

  // Retour à l’écran d’accueil
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(10, 20);
  display.print("Scan un badge RFID...");
  display.display();

  rfid.PICC_HaltA();
}
