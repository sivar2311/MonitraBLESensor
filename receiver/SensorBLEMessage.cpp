#include "SensorBLEMessage.h"

SensorBLEMessage::SensorBLEMessage() {
    static_assert((sizeof(*this) <= (29)), "Advertisment too long! Maximum is 29 bytes!");
    memset(this, 0, sizeof(*this));
    manufacturerId = 0x033E;
}

SensorBLEMessage::SensorBLEMessage(const std::string& other) {
    memset(this, 0, sizeof(*this));
    fromString(other);
}

void SensorBLEMessage::fromString(const std::string& other) {
    if (isValid(other)) memcpy(this, other.c_str(), sizeof(*this));
}

std::string SensorBLEMessage::toString() const {
    return std::string((const char*)this, sizeof(*this));
}

void SensorBLEMessage::hexDump(Print& print) const {
    auto str = toString();
    for (char c : str) print.printf("%02X ", c);
}

void SensorBLEMessage::dump(Print& print) const {
    if (hasPIR())            print.printf("  PIR:            %s\r\n", PIR ? "true" : "false");
    if (hasMovement())       print.printf("  Movement:       %s\r\n", movement ? "true" : "false");
    if (hasAmbientLight())   print.printf("  AmbientLight:   %d\r\n", ambienLight);
    if (hasTemperature())    print.printf("  Temperature:    %d\r\n", temperature);
    if (hasHumidity())       print.printf("  Humidity:       %d\r\n", humidity);
    if (hasAirECO2())        print.printf("  AirECO2:        %d\r\n", airECO2);
    if (hasAirTVOC())        print.printf("  AirTVOC:        %d\r\n", airTVOC);
    if (hasBatteryVoltage()) print.printf("  BatteryVoltage: %d\r\n", batteryVoltage);
                             print.printf("  MessageCounter: %d\r\n", messageCounter);
}

SensorBLEMessage::operator std::string() const {
    return toString();
}

void SensorBLEMessage::setPIR(uint8_t value) {
    PIR       = value > 0;
    updatePIR = 1;
}

void SensorBLEMessage::setMovement(uint8_t value) {
    movement       = value > 0;
    updateMovement = 1;
}

void SensorBLEMessage::setAmbientLight(uint16_t value) {
    ambienLight        = value;
    updateAmbientLight = 1;
}

void SensorBLEMessage::setTemperature(uint16_t value) {
    temperature       = value;
    updateTemperature = 1;
}

void SensorBLEMessage::setHumidity(uint16_t value) {
    humidity       = value;
    updateHumidity = 1;
}

void SensorBLEMessage::setAirECO2(uint16_t value) {
    airECO2       = value;
    updateAirECO2 = 1;
}

void SensorBLEMessage::setAirTVOC(uint16_t value) {
    airTVOC       = value;
    updateAirTVOC = 1;
}

void SensorBLEMessage::setBatteryVoltage(uint16_t value) {
    batteryVoltage       = value;
    updateBatteryVoltage = 1;
}

void SensorBLEMessage::setMessageCounter(uint16_t value) {
    messageCounter = value;
}

bool SensorBLEMessage::hasPIR() const {
    return updatePIR == 1;
}

bool SensorBLEMessage::hasMovement() const {
    return updateMovement == 1;
}

bool SensorBLEMessage::hasAmbientLight() const {
    return updateAmbientLight == 1;
}

bool SensorBLEMessage::hasTemperature() const {
    return updateTemperature == 1;
}

bool SensorBLEMessage::hasHumidity() const {
    return updateHumidity == 1;
}

bool SensorBLEMessage::hasAirECO2() const {
    return updateAirECO2 == 1;
}

bool SensorBLEMessage::hasAirTVOC() const {
    return updateAirTVOC == 1;
}

bool SensorBLEMessage::hasBatteryVoltage() const {
    return updateBatteryVoltage == 1;
}

bool SensorBLEMessage::isValid(const std::string& other) {
    if (other.length() != sizeof(SensorBLEMessage)) return false;
    uint16_t* manId = (uint16_t*) other.c_str();
    if (*manId != 0x033E) return false;
    return true;
}