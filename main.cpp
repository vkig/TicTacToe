#include "graphics.hpp"
#include "GSetNumber.hpp"
#include "Application.hpp"
#include "GSelect.hpp"
#include "fstream"
#include <chrono>
#include <ctime>
#define quote(x) #x

using namespace genv;

void writeToFile(std::vector<GWidget*>& w){
    std::ofstream f("results.txt", std::ios_base::app);
    auto actTime = std::chrono::system_clock::now();
    std::time_t timeFlag = std::chrono::system_clock::to_time_t(actTime);
    f << std::ctime(&timeFlag) << "\t";
    for(GWidget* act : w){
        int idx = 0;
        std::string s(typeid(*act).name());
        for(int i=0;i<s.size();i++){
            if(s[i] == 'G'){
                idx = i;
                break;
            }
        }
        f << s.substr(idx, s.size()-idx) << ":\t";
        if(s.substr(idx, s.size()-idx) == "GSelect")
        {
            f<<((GSelect*) act)->getSelected()<<"\t";
        }
        if(s.substr(idx, s.size()-idx) == "GSetNumber")
        {
            f<<((GSetNumber*) act)->getValue()<<"\t";
        }
    }
    f << "\n";
    f.close();

}

class MyApp : public Application{
private:
    GSelect * gs1;
    GSelect * gs2;
    GButton * gb1;
    GButton * gb2;
public:
    MyApp(){
        gs1 = new GSelect(this,10, 10, 380, 30, 1, 90, {"lehetőség1", "lehetőség2","lehetőség3", "lehetőség4"});
        gs2 = new GSelect(this,10, 140, 380, 20, 1, 150, {"abrakadabraabrakadabraabrakadabra1", "abrakadabraabrakadabraabrakadabra2","abrakadabraabrakadabraabrakadabra3",
                                                     "abrakadabraabrakadabraabrakadabra4", "abrakadabraabrakadabraabrakadabra5", "abrakadabraabrakadabraabrakadabra6",
                                                     "abrakadabraabrakadabraabrakadabra7", "abrakadabraabrakadabraabrakadabra8","abrakadabraabrakadabraabrakadabra9",
                                                     "abrakadabraabrakadabraabrakadabra10", "abrakadabraabrakadabraabrakadabra11", "abrakadabraabrakadabraabrakadabra12",
                                                     "abrakadabraabrakadabraabrakadabra13", "abrakadabraabrakadabraabrakadabra14", "abrakadabraabrakadabraabrakadabra15",
                                                     "abrakadabraabrakadabraabrakadabra16", "abrakadabraabrakadabraabrakadabra17", "abrakadabraabrakadabraabrakadabra18",
                                                     "abrakadabraabrakadabraabrakadabra19", "abrakadabraabrakadabraabrakadabra20", "abrakadabraabrakadabraabrakadabra21",
                                                     "abrakadabraabrakadabraabrakadabra22", "abrakadabraabrakadabraabrakadabra23", "abrakadabraabrakadabraabrakadabra24",
                                                     "abrakadabraabrakadabraabrakadabra25", "abrakadabraabrakadabraabrakadabra26", "abrakadabraabrakadabraabrakadabra27",
                                                     "abrakadabraabrakadabraabrakadabra28", "abrakadabraabrakadabraabrakadabra29", "abrakadabraabrakadabraabrakadabra30"});
        gb1 = new GButton(this,10, 350, 50, 30, 1, genv::color(0, 100, 255),
                          genv::color(255, 0, 0),[this](){ moveItem(gs1, gs2);},GButton::LABELED, genv::color(255, 255, 255), "1->2");
        gb2 = new GButton(this,100, 350, 50, 30, 1, genv::color(0, 100, 255),
                          genv::color(255, 0, 0),[this](){ moveItem(gs2, gs1);},GButton::LABELED, genv::color(255, 255, 255), "2->1");
        addWidget(gs1);
        addWidget(gs2);
        addWidget(gb1);
        addWidget(gb2);
        gout.open(400,400);
        gout<<move_to(0, 0)<<color(0, 0, 0)<<box_to(399, 399)<< refresh;
    }
    ~MyApp(){
        delete gs1;
        delete gs2;
    }
    void moveItem(GSelect * from, GSelect * to){
        std::string s = from->getSelected();
        if(s != ""){
            to->addItem(s);
            from->removeItem(from->getSelected());
        }
    }
};

int main()
{
    MyApp ma;
    ma.eventManager();
    return 0;
}
