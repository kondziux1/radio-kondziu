
class Espradio
{
protected:
    uint8_t cur_station = 0;
    uint8_t max_volume = 21;
    uint8_t cur_volume = 10;
private:
    String stations[15];

public:
    Espradio(uint8_t I2S_BCLK, uint8_t I2S_LRC, uint8_t I2S_DOUT);
    ~Espradio();
    int playpos(int pos);
    int play(String url);
    int rm(int pos);
    int set(int pos, String url);
    int put(String url);
    String get(int pos = 0);
    int spkmute();
    int volchange(int volume);
    int volminmax(bool max);
    int readSerial();
    int sendSerial(String message, bool nl = 1);
};
