/*
 This example prints the WiFi shield's MAC address, and
 scans for available WiFi networks using the WiFi shield.
 Every ten seconds, it scans again. It doesn't actually
 connect to any network, so no encryption scheme is specified.
 Circuit:
 * WiFi shield attached
 created 13 July 2010
 by dlf (Metodo2 srl)
 modified 21 Junn 2012
 by Tom Igoe and Jaymes Dec
 */

#include <SPI.h>
#include <ESP8266WiFi.h>

void intiWifiModul()
{
    Serial.println("Wifi init");
    // check for the presence of the shield:

    // Set WiFi to station mode
    WiFi.mode(WIFI_STA);

    // Disconnect from an AP if it was previously connected
    WiFi.disconnect();
}

void scanSSIDs()
{
    // scan for existing networks:
    Serial.println("Scanning available networks...");
    String ssid;
    int32_t rssi;
    uint8_t encryptionType;
    uint8_t *bssid;
    int32_t channel;
    bool hidden;
    int scanResult;

    Serial.println(F("Starting WiFi scan..."));

    scanResult = WiFi.scanNetworks(/*async=*/false, /*hidden=*/true);

    if (scanResult == 0)
    {
        Serial.println(F("No networks found"));
    }
    else if (scanResult > 0)
    {
        Serial.printf(PSTR("%d networks found:\n"), scanResult);
        String output;

        // Print unsorted scan results
        for (int8_t i = 0; i < scanResult; i++)
        {
            WiFi.getNetworkInfo(i, ssid, encryptionType, rssi, bssid, channel, hidden);

            output += bssid[0];
            output += bssid[1];
            output += bssid[2];
            output += bssid[3];
            output += bssid[4];
            output += bssid[5];
            output += rssi;

            if (i < scanResult - 1)
            {
                output += ",";
            }
        }
        Serial.println(output);
    }
    else
    {
        Serial.printf(PSTR("WiFi scan error %d"), scanResult);
    }
}

void printMacAddress()
{
    // the MAC address of your WiFi shield
    byte mac[6];

    // print your MAC address:
    WiFi.macAddress(mac);
    Serial.print("MAC: ");
    Serial.print(mac[5], HEX);
    Serial.print(":");
    Serial.print(mac[4], HEX);
    Serial.print(":");
    Serial.print(mac[3], HEX);
    Serial.print(":");
    Serial.print(mac[2], HEX);
    Serial.print(":");
    Serial.print(mac[1], HEX);
    Serial.print(":");
    Serial.println(mac[0], HEX);
}

void listNetworks()
{
    // scan for nearby networks:
    Serial.println("** Scan Networks **");
    int numSsid = WiFi.scanNetworks();
    if (numSsid == -1)
    {
        Serial.println("Couldn't get a WiFi connection");
        while (true)
            ;
    }

    // print the list of networks seen:
    Serial.print("number of available networks:");
    Serial.println(numSsid);

    // print the network number and name for each network found:
    for (int thisNet = 0; thisNet < numSsid; thisNet++)
    {
        Serial.print(thisNet);
        Serial.print(") ");
        Serial.print(WiFi.SSID(thisNet));
        Serial.print("\tSignal: ");
        Serial.print(WiFi.RSSI(thisNet));
        Serial.print(" dBm");
        Serial.print("\tEncryption: ");
        printEncryptionType(WiFi.encryptionType(thisNet));
    }
}

void printEncryptionType(int thisType)
{
    // read the encryption type and print out the name:
    switch (thisType)
    {
    case ENC_TYPE_WEP:
        Serial.println("WEP");
        break;
    case ENC_TYPE_TKIP:
        Serial.println("WPA");
        break;
    case ENC_TYPE_CCMP:
        Serial.println("WPA2");
        break;
    case ENC_TYPE_NONE:
        Serial.println("None");
        break;
    case ENC_TYPE_AUTO:
        Serial.println("Auto");
        break;
    }
}
