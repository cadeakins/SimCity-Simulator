#include "Config.h"

std::string Config::GetRegion() {
    return region;
}
int Config::GetTime() {
    return time;
}
int Config::GetRefreshRate() {
    return refreshRate;
}
int Config::GetWindDirection() {
    return windDirection;
}

void Config::SetRegion(std::string region) {
    this->region = region;
}
void Config::SetTime(int time) {
    this->time = time;
}
void Config::SetRefreshRate(int refreshRate) {
    this->refreshRate = refreshRate;
}
void Config::SetWindDirection(int windDirection) {
    this->windDirection = windDirection;
}

Config::Config() {
    region = "None";
    time = 0;
    refreshRate = 0;
}