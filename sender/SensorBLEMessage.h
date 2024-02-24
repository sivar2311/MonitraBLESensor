#pragma once

#include <Arduino.h>

struct __attribute__((__packed__)) SensorBLEMessage {
    SensorBLEMessage();
    SensorBLEMessage(const std::string& other);
    void fromString(const std::string& other);
    std::string toString() const;
    void hexDump(Print& print) const;
    void dump(Print& print) const;
    operator std::string() const;
    void setPIR(uint8_t value);
    void setMovement(uint8_t value);
    void setAmbientLight(uint16_t value);
    void setTemperature(uint16_t value);
    void setHumidity(uint16_t value);
    void setAirECO2(uint16_t value);
    void setAirTVOC(uint16_t value);
    void setBatteryVoltage(uint16_t value);
    void setMessageCounter(uint16_t value);

    bool hasPIR() const;
    bool hasMovement() const;
    bool hasAmbientLight() const;
    bool hasTemperature() const;
    bool hasHumidity() const;
    bool hasAirECO2() const;
    bool hasAirTVOC() const;
    bool hasBatteryVoltage() const;

    static bool isValid(const std::string& other);

    uint16_t manufacturerId;
    uint8_t  packetType;
    uint8_t  connectionAttempts;
    uint8_t  reserved1;
    uint16_t messageCounter;
    union {
        uint8_t updateFlags;
        struct {
            uint8_t updatePIR : 1;
            uint8_t updateMovement : 1;
            uint8_t updateAmbientLight : 1;
            uint8_t updateTemperature : 1;
            uint8_t updateHumidity : 1;
            uint8_t updateAirECO2 : 1;
            uint8_t updateAirTVOC : 1;
            uint8_t updateBatteryVoltage : 1;
        };
    };
    union {
        uint8_t valueFlags;
        struct {
            uint8_t PIR : 1;
            uint8_t movement : 1;
            // uint8_t reserved : 6;
        };
    };
    uint16_t ambienLight;
    uint16_t temperature;
    uint16_t humidity;
    uint16_t airECO2;
    uint16_t airTVOC;
    uint16_t uptime;
    uint16_t batteryVoltage;
};
