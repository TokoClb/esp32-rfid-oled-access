# ESP32-OLED-RFID-System-Access

Développé par Toko_Clb Lab, ce projet met en œuvre un système complet de contrôle d’accès basé sur la lecture de badges RFID. Il intègre un affichage OLED pour afficher les informations utilisateur, ainsi qu’une LED RGB et un buzzer pour indiquer visuellement et sonorement l’état d’autorisation. Ce système est conçu pour être simple à utiliser, facilement personnalisable et adaptable à divers environnements nécessitant une gestion sécurisée des accès.

## Matériel utilisé

- ESP32 Dev Module
- Lecteur RFID MFRC522
- Écran OLED SSD1306
- LED RGB
- Résistance 220Ω
- Buzzer
- Câblage et alimentation

## Branchement

| Module      | ESP32 GPIO |
|-------------|------------|
| RFID SDA    | GPIO 5     |
| RFID RST    | GPIO 4     |
| RFID SCK	  | GPIO 18    |
| RFID MOSI   | GPIO 23    |
| RFID MISO	  | GPIO 19    |
| RFID GND	  | GND        |
| RFID 3.3V   | 3.3V       |
|-------------|------------|
| OLED SDA    | GPIO 21    |
| OLED SCL    | GPIO 22    |
| OLED GND	  | GND        |
| OLED 5V     | 5V         |
|-------------|------------|
| LED RGB R   | GPIO 2     |
| LED RGB G   | GPIO 15    |
| LED RGB GND | GND        |
|-------------|------------|
| Buzzer      | GPIO 13    |
| Buzzer GND  | GND        |

## Installation

1. Installer les bibliothèques suivantes dans Arduino IDE : MFRC522, Adafruit GFX, Adafruit SSD1306
2. Charger le code dans l'ESP32
3. Connecter les composants comme indiqué

## Fonctionnalités

- Affiche le nom/prénom sur OLED
- Indique accès autorisé/refusé avec LED RGB et buzzer
- Extensible avec servo ou relais


## Licence

MIT License - libre à utiliser et modifier



## Auteur

Toko_Clb Lab est une startup innovante fondée à Kinshasa, qui se veut être un véritable catalyseur d'innovation pour la République Démocratique du Congo. Notre mission est de révéler le potentiel immense du génie congolais en créant des solutions technologiques accessibles, durables et porteuses d'avenir. Nous accompagnons l'éveil des jeunes talents, le recyclage des déchets et la promotion d'une technologie responsable.

BUILD AND INVEST IN YOURSELF !

https://www.calebtoko.com/entreprise.html

