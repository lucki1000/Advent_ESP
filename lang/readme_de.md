# IOT LED Adventskranz

<p align="center">
  <span>Deutsch</span> |
  <a href="https://github.com/lucki1000/Advent_ESP/blob/main/readme.md">Englisch</a>
</p>

# Inhalt:
- [Wofür ist dieses Projekt?](#whatsthis)
- [Wie benutze ich das?](#howtouseit)
  - [Was du ändern musst](#changes)
  - [Kompilieren und Flashen](#compileandflash)

## Warum dieses Projekt?<a name="whatsthis"></a>

Warum machte ich dieses Projekt? Weil ich wohl zu Faul bin um jedes Jahr einzeln 4 Kerzen zum richtigen Zeitpunkt anzumachen.:wink:

Spaß beiseite, ich habe erfahrungen mit der Arduino IDE, ESP Board und mit C++ gesammelt. Wenn du gut im Basteln bist, kannst du einen schönen Adventskranz machen.  
Ich denke du kannst diesen Code auf jedem ESP/Arduino benutzen mit dem du dieses Modul benutzen kannst <ESP8266WiFi.h>.

## Wie benutze ich das?<a name="howtouseit"></a>

Einfach runterladen und auf das Gerät flashen:laughing:

## Was muss geändert werden?<a name="changes"></a>

Was du aufjeden fall ändern musst ist:
```
//WiFi setup
const char ssid[] = "SSID";
const char pass[] = "WLAN KEY";
```
Wenn du das nicht machst sucht das Programm nach dem WLan und zeigt dir für jeden Schleifen Durchlauf einen "." mehr im seriellen Monitor, und wird das Programm nicht fortsetzen bis das WLan gefunden wird.  

Wenn du den NTP Server ändern willst odere die Zeitzone, dann ändere das dort:
```
//NTP Server
static const char ntpServerName[] = "time.google.com";
//Set Timezone
const int timeZone = 1; //Central European Time
```

Wenn du die Ausgänge(GPIOs) änderen willst mach das dort:
```
//Set UP lights on GPIOs
const int first_led = 16;
const int second_led = 5;
const int third_led = 4;
const int fourth_led = 0;
```

## Kompilieren und Flashen<a name="compileandflash"></a>

Warum gibt es keine fertigen Builds? Weil ich dann dein WLan Passwort und den SSID Namen wissen müsste, aber es gibt 2 Wege wie du das möglich schnell kompilieren kannst mit hilfe der Arduino IDE:

1. Du kopierst den Inhalt meiner c++ Datei und fügst ihn in dein Sketch ein.
2. Du änderst die Dateienendung von .cpp in .ino z. B. irgendwas.ino oder auch irgendwas.cpp.ino und öffnest die dann einfach mit der Arduino IDE.

Dann wüsche ich dir viel Gück, Probleme kannst du bei den Issues melden.
