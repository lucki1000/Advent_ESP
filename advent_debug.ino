#include <bits/stdc++.h>
#include <TimeLib.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <stdio.h>
#include <string>

using namespace std;
//WiFi setup
const char ssid[] = "SSID";
const char pass[] = "WLAN KEY";
//NTP Server
static const char ntpServerName[] = "time.google.com";
//Set Timezone
const int timeZone = 1; //Central European Time
//Set UP lights on GPIOs
const int first_led = 16; //D0
const int second_led = 5; //D1
const int third_led = 4; //D2
const int fourth_led = 0; //D3

WiFiUDP Udp;
unsigned int localPort = 8888;

//call time
time_t getNtpTime();
void digitalClockDisplay();
void printDigits(int digits);
void sendNTPpacket(IPAddress &address);

//Setup
void setup() {
    Serial.begin(115200);
    pinMode(first_led, OUTPUT); // set port to on
    pinMode(second_led, OUTPUT);
    pinMode(third_led, OUTPUT);
    pinMode(fourth_led, OUTPUT);
    digitalWrite(first_led, LOW); // Turn off light
    digitalWrite(second_led, LOW);
    digitalWrite(third_led, LOW);
    digitalWrite(fourth_led, LOW);
    while (!Serial);
    delay(250);
    Serial.println("TimeNTP");
    Serial.println("Connect to");
    Serial.println(ssid);
    WiFi.begin(ssid, pass);
    while(WiFi.status() != WL_CONNECTED){
        delay(500);
        Serial.print(".");
    }

    Serial.print("IP nunmber assigned: ");
    Serial.println(WiFi.localIP());
    Serial.println("Satrting UDP");
    Udp.begin(localPort);
    Serial.print("Local port: ");
    Serial.println(Udp.localPort());
    Serial.println("waiting for sync");
    setSyncProvider(getNtpTime);
    setSyncInterval(300);
}

time_t prevDisplay = 0;
//Calculate Weekday
int day_of_week(int y, int m, int d)
{
    static int t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
    y -= m < 3;
    return (y + y/4 - y/100 + y/400 + t[m-1] + d) % 7;
}

//Calc DOY
int doy_calc(int year, int mon, int day)
{
    int /*day, mon, year,*/ days_in_feb = 28, doy;    // day of year

    //printf("Enter date (MM/DD/YYYY): ");
    //scanf("%d %d %d", &mon, &day, &year);
    //day = 24, mon = 12, year = 2022;
    doy = day;

    // check for leap year
    if( (year % 4 == 0 && year % 100 != 0 ) || (year % 400 == 0) )
    {
        days_in_feb = 29;
    }

    switch(mon)
    {
        case 2:
            doy += 31;
            break;
        case 3:
            doy += 31+days_in_feb;
            break;
        case 4:
            doy += 31+days_in_feb+31;
            break;
        case 5:
            doy += 31+days_in_feb+31+30;
            break;
        case 6:
            doy += 31+days_in_feb+31+30+31;
            break;
        case 7:
            doy += 31+days_in_feb+31+30+31+30;
            break;
        case 8:
            doy += 31+days_in_feb+31+30+31+30+31;
            break;
        case 9:
            doy += 31+days_in_feb+31+30+31+30+31+31;
            break;
        case 10:
            doy += 31+days_in_feb+31+30+31+30+31+31+30;
            break;
        case 11:
            doy += 31+days_in_feb+31+30+31+30+31+31+30+31;
            break;
        case 12:
            doy += 31+days_in_feb+31+30+31+30+31+31+30+31+30;
            break;
    }

    return doy; // return doy to operating system
}
// END CALC DOY

int calc_4th_advent(string silent) {
    int advent_4th;
    if (silent == "Sunday") {
        advent_4th = 24;
    } else if (silent == "Saturday") {
        advent_4th = 18;
    } else if (silent == "Friday") {
        advent_4th = 19;
    } else if (silent == "Thursday") {
        advent_4th = 20;
    } else if (silent == "Wednesday") {
        advent_4th = 21;
    } else if (silent == "Tuesday") {
        advent_4th = 22;
    } else {
        advent_4th = 23;
    }
    return advent_4th;
}

void loop() {
    if (timeStatus() != timeNotSet) {
        Serial.println("Time has changed");
    }
    string silent;
    int y, m, d;
    //use the 24.12 to calc the 4 Advent
    d = 24;
    m = 12;
    y = year();
    switch (day_of_week(y, m, d)) {
        case 0:
            silent = "Sunday";
            break;
        case 1:
            silent = "Monday";
            break;
        case 2:
            silent = "Tuesday";
            break;
        case 3:
            silent = "Wednesday";
            break;
        case 4:
            silent = "Thursday";
            break;
        case 5:
            silent = "Friday";
            break;
        case 6:
            silent = "Saturday";
            break;
    }

    int tag = day();
    int monat = month();
    int jahr = year();
    int fourth_advent = calc_4th_advent(silent);
    int fourth_advent_doy = doy_calc(jahr, 12, fourth_advent); //2020 it should be 355
    int three_advent_doy = fourth_advent_doy - 7, second_advent_doy = three_advent_doy - 7, first_advent_doy = second_advent_doy - 7;
    Serial.println("4th Advent DOY: ");
    Serial.println(fourth_advent_doy);
    Serial.println("3th Advent DOY: ");
    Serial.println(three_advent_doy);
    Serial.println("2th Advent DOY: ");
    Serial.println(second_advent_doy);
    Serial.println("1th Advent DOY: ");
    Serial.println(first_advent_doy);
    Serial.println("Actual DOY:");
    int actual_doy = doy_calc(jahr, monat, tag);
    Serial.println(actual_doy);
        if ((actual_doy >= first_advent_doy) && (actual_doy < second_advent_doy)) {
            Serial.println("First Case");
            digitalWrite(first_led, HIGH);
            digitalWrite(second_led, LOW);
            digitalWrite(third_led, LOW);
            digitalWrite(fourth_led, LOW);
        }
        else if ((actual_doy >= second_advent_doy) && (actual_doy < three_advent_doy)) {
            Serial.println("Second Case");
            digitalWrite(first_led, HIGH);
            digitalWrite(second_led, HIGH);
            digitalWrite(third_led, LOW);
            digitalWrite(fourth_led, LOW);
        }
        else if ((actual_doy >= three_advent_doy) && (actual_doy < fourth_advent_doy)) {
            Serial.println("Thrid Case");
            digitalWrite(first_led, HIGH);
            digitalWrite(second_led, HIGH);
            digitalWrite(third_led, HIGH);
            digitalWrite(fourth_led, LOW);
        }
        else if (actual_doy >= fourth_advent_doy) {
            Serial.println("Fourth Case");
            digitalWrite(first_led, HIGH);
            digitalWrite(second_led, HIGH);
            digitalWrite(third_led, HIGH);
            digitalWrite(fourth_led, HIGH);
        }
        else {
            Serial.println("No Case matched");
            digitalWrite(first_led, LOW);
            digitalWrite(second_led, LOW);
            digitalWrite(third_led, LOW);
            digitalWrite(fourth_led, LOW);
        }
    delay(40000);
    void printDigits(int digits);
    void sendNTPpacket(IPAddress &address);
    //Setup
}
const int NTP_PACKET_SIZE = 48; // NTP time is in the first 48 bytes of message
byte packetBuffer[NTP_PACKET_SIZE]; //buffer to hold incoming & outgoing packets

time_t getNtpTime() {
    IPAddress ntpServerIP; // NTP server's ip address

    while (Udp.parsePacket() > 0); // discard any previously received packets
    Serial.println("Transmit NTP Request");
    // get a random server from the pool
    WiFi.hostByName(ntpServerName, ntpServerIP);
    Serial.print(ntpServerName);
    Serial.print(": ");
    Serial.println(ntpServerIP);
    sendNTPpacket(ntpServerIP);
    uint32_t beginWait = millis();
    while (millis() - beginWait < 1500) {
        int size = Udp.parsePacket();
        if (size >= NTP_PACKET_SIZE) {
            Serial.println("Receive NTP Response");
            Udp.read(packetBuffer, NTP_PACKET_SIZE);  // read packet into the buffer
            unsigned long secsSince1900;
            // convert four bytes starting at location 40 to a long integer
            secsSince1900 = (unsigned long) packetBuffer[40] << 24;
            secsSince1900 |= (unsigned long) packetBuffer[41] << 16;
            secsSince1900 |= (unsigned long) packetBuffer[42] << 8;
            secsSince1900 |= (unsigned long) packetBuffer[43];
            return secsSince1900 - 2208988800UL + timeZone * SECS_PER_HOUR;
        }
    }
    Serial.println("No NTP Response :-(");
    return 0; // return 0 if unable to get the time
}
void sendNTPpacket(IPAddress &address) {
    // set all bytes in the buffer to 0
    memset(packetBuffer, 0, NTP_PACKET_SIZE);
    // Initialize values needed to form NTP request
    // (see URL above for details on the packets)
    packetBuffer[0] = 0b11100011;   // LI, Version, Mode
    packetBuffer[1] = 0;     // Stratum, or type of clock
    packetBuffer[2] = 6;     // Polling Interval
    packetBuffer[3] = 0xEC;  // Peer Clock Precision
    // 8 bytes of zero for Root Delay & Root Dispersion
    packetBuffer[12] = 49;
    packetBuffer[13] = 0x4E;
    packetBuffer[14] = 49;
    packetBuffer[15] = 52;
    // all NTP fields have been given values, now
    // you can send a packet requesting a timestamp:
    Udp.beginPacket(address, 123); //NTP requests are to port 123
    Udp.write(packetBuffer, NTP_PACKET_SIZE);
    Udp.endPacket();
}
