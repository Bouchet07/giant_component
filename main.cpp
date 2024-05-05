#include "graph.h"
#include <chrono>

int main(){
    CNet Watts1 =  CNet::WattsStrogatz(50000,10,0.5) + CNet::WattsStrogatz(50000,10,0.5);
    //Watts1.print();
    std::cout << "Network created\n";
    Net Watts2 = Net(Watts1);
    //Watts2.print();
    std::cout << "Network decompiled\n";
    Net giant = Watts2.get_giant_component();
    //giant.print();
    std::cout << "giant completed\n";
    //giant.print();
    //Watts1.plot_degree_distribution();

    return 0;
}