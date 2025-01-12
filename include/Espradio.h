#include <Arduino.h>

class Espradio
{
protected:
    uint8_t cur_station = 0;
    uint8_t max_volume = 21;
    uint8_t cur_volume = 10;
private:
    
public:
    Espradio(uint8_t I2S_BCLK, uint8_t I2S_LRC, uint8_t I2S_DOUT);
    ~Espradio();
    int radioplaypos(int pos);
    int radioplay(String url);
    int radiorm(int pos);
    int radioset(int pos, String url);
    int radioput(String url);
    String radioget(int pos = 0);
    int spkmute();
    int volchange(int volume);
    int volminmax(bool max);
    int readSerial();
    int sendSerial(String message, bool nl = 1);
};
