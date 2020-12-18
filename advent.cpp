#include <bits/stdc++.h>
#include <TimeLib.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <stdio.h>
#include <string>

using namespace std;
const char ssid[] = "SSID";
const char pass[] = "WLAN KEY";
static const char ntpServerName[] = "time.google.com";
const int timeZone = 1; 
const int first_led = 16;
const int second_led = 5;
const int third_led = 4;
const int fourth_led = 0;

WiFiUDP Udp;
unsigned int localPort = 8888;

time_t getNtpTime();
void printDigits(int digits);
void sendNTPpacket(IPAddress &address);

void setup() {
    Serial.begin(115200);
    pinMode(first_led, OUTPUT); 
    pinMode(second_led, OUTPUT);
    pinMode(third_led, OUTPUT);
    pinMode(fourth_led, OUTPUT);
    digitalWrite(first_led, LOW); 
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

int day_of_week(int y, int m, int d)
{
    static int t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
    y -= m < 3;
    return (y + y/4 - y/100 + y/400 + t[m-1] + d) % 7;
}

int doy_calc(int year, int mon, int day)
{
    int days_in_feb = 28, doy; 
    doy = day;
    
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

    return doy;
}

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
    int fourth_advent_doy = doy_calc(jahr, 12, fourth_advent); 
    int three_advent_doy = fourth_advent_doy - 7, second_advent_doy = three_advent_doy - 7, first_advent_doy = second_advent_doy - 7;
    int actual_doy = doy_calc(jahr, monat, tag);
        if ((actual_doy >= first_advent_doy) && (actual_doy < second_advent_doy)) {
            digitalWrite(first_led, HIGH);
            digitalWrite(second_led, LOW);
            digitalWrite(third_led, LOW);
            digitalWrite(fourth_led, LOW);
        }
        else if ((actual_doy >= second_advent_doy) && (actual_doy < three_advent_doy)) {
            digitalWrite(first_led, HIGH);
            digitalWrite(second_led, HIGH);
            digitalWrite(third_led, LOW);
            digitalWrite(fourth_led, LOW);
        }
        else if ((actual_doy >= three_advent_doy) && (actual_doy < fourth_advent_doy)) {
            digitalWrite(first_led, HIGH);
            digitalWrite(second_led, HIGH);
            digitalWrite(third_led, HIGH);
            digitalWrite(fourth_led, LOW);
        }
        else if (actual_doy >= fourth_advent_doy) {
            digitalWrite(first_led, HIGH);
            digitalWrite(second_led, HIGH);
            digitalWrite(third_led, HIGH);
            digitalWrite(fourth_led, HIGH);
        }
        else {
            digitalWrite(first_led, LOW);
            digitalWrite(second_led, LOW);
            digitalWrite(third_led, LOW);
            digitalWrite(fourth_led, LOW);
        }

    delay(40000);
    void printDigits(int digits);
    void sendNTPpacket(IPAddress &address);
}

const int NTP_PACKET_SIZE = 48; 
byte packetBuffer[NTP_PACKET_SIZE];

time_t getNtpTime() {
    IPAddress ntpServerIP; 

    while (Udp.parsePacket() > 0); 
    Serial.println("Transmit NTP Request");
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
            Udp.read(packetBuffer, NTP_PACKET_SIZE); 
            unsigned long secsSince1900;
            secsSince1900 = (unsigned long) packetBuffer[40] << 24;
            secsSince1900 |= (unsigned long) packetBuffer[41] << 16;
            secsSince1900 |= (unsigned long) packetBuffer[42] << 8;
            secsSince1900 |= (unsigned long) packetBuffer[43];
            return secsSince1900 - 2208988800UL + timeZone * SECS_PER_HOUR;
        }
    }
    Serial.println("No NTP Response :-(");
    return 0; 
}
void sendNTPpacket(IPAddress &address) {
    memset(packetBuffer, 0, NTP_PACKET_SIZE);
    packetBuffer[0] = 0b11100011;  
    packetBuffer[1] = 0;   
    packetBuffer[2] = 6;    
    packetBuffer[3] = 0xEC;  
    packetBuffer[12] = 49;
    packetBuffer[13] = 0x4E;
    packetBuffer[14] = 49;
    packetBuffer[15] = 52;
    Udp.beginPacket(address, 123); 
    Udp.write(packetBuffer, NTP_PACKET_SIZE);
    Udp.endPacket();
}
