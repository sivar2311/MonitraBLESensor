#include <Arduino.h>

#include <NimBLEDevice.h>
#include "SensorBLEMessage.h"

NimBLEScan* pBLEScan;

class MyAdvertisedDeviceCallbacks : public NimBLEAdvertisedDeviceCallbacks {
    void onResult(NimBLEAdvertisedDevice* advertisedDevice) {
        std::string manufacturerData = advertisedDevice->getManufacturerData();
        if (!SensorBLEMessage::isValid(manufacturerData)) return;

        SensorBLEMessage message(manufacturerData);
        Serial.printf("%s: ", advertisedDevice->getAddress().toString().c_str());
        message.hexDump(Serial); 
        Serial.println();
        message.dump(Serial); 
        Serial.println();
    }
};

void setup() {
    Serial.begin(115200);
    Serial.println("Scanning...");

    NimBLEDevice::setScanFilterMode(CONFIG_BTDM_SCAN_DUPL_TYPE_DATA);
    NimBLEDevice::init("");

    pBLEScan = NimBLEDevice::getScan();
    pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks(), false);
    pBLEScan->setActiveScan(false);
    pBLEScan->setMaxResults(0);
    pBLEScan->start(0, nullptr, false);
}

void loop() {
}