#include <Arduino.h>
#include <NimBLEDevice.h>

#include "SensorBLEMessage.h"

NimBLEAdvertising* advertiser;

void setup() {
    Serial.begin(115200);
    Serial.println();
    NimBLEDevice::init("ESP32Adv");
    advertiser = NimBLEDevice::getAdvertising();
    advertiser->setAdvertisementType(BLE_GAP_CONN_MODE_NON);
    Serial.println("Advertising started...");
    Serial.printf("Message length: %d\r\n", sizeof(SensorBLEMessage));
}

uint16_t cnt = 0;

void loop() {
    delay(1000);
    advertiser->stop();

    SensorBLEMessage message;

    message.setAirECO2(100);
    message.setAirTVOC(100);
    message.setAmbientLight(9500);
    message.setBatteryVoltage(1000);
    message.setHumidity(500);
    message.setMovement(1);
    message.setPIR(0);
    message.setTemperature(2500);
    message.setMessageCounter(cnt++);

    Serial.printf("%s: ", NimBLEDevice::getAddress().toString().c_str());
    message.hexDump(Serial); Serial.println();
    message.dump(Serial); Serial.println();

    advertiser->setManufacturerData(message);
    advertiser->start();
}
