#ifndef CONFIG_H
#define CONFIG_H

#include <string>

class Config {      //Class that contains Config information
    public: 
        std::string GetRegion();
        int GetTime();
        int GetRefreshRate();

        void SetRegion(std::string region);
        void SetTime(int time);
        void SetRefreshRate(int refreshRate);

        Config();
    private: 
        std::string region;
        int time;
        int refreshRate;
};

#endif