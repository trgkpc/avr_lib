// 入出力機能
#include <iostream>
#include <fstream>
#include <string>
using std::cout, std::cerr, std::endl;
using std::ofstream;
using std::string, std::to_string;
#define _SFR_IO8(id) (id)
#define print(name) (cout << (#name) << " " <<(name) << endl);
ofstream f;
// gpio
void define_gpio(string name, string X, int ddr, int port, int pin)
{
    for(int id=0; id<8; id++){
        string defname = name + "_" + X + to_string(id);
        string type = name + "<" + to_string(ddr) + "," + to_string(port) + "," + to_string(pin) + "," + to_string(id) + ">";
        f << "#define" << " " << defname << " " << type << endl;
    }
}
#define LED(X) define_gpio("LED", #X, DDR##X, PORT##X, PIN##X)
#define SWITCH(X) define_gpio("SWITCH", #X, DDR##X, PORT##X, PIN##X)

// ピン周りのファイル読み込み
#define _AVR_IO_H_
#include </usr/lib/avr/include/avr/iom328p.h>

int main()
{
    print(DDRD);
    print(PORTD);
    print(PIND);

    f = ofstream("led.hpp");
    LED(B);
    LED(C);
    LED(D);
    f.close();

    f = ofstream("switch.hpp");
    SWITCH(B);
    SWITCH(C);
    SWITCH(D);
    f.close();
}
