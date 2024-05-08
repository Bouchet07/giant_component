#include "graph.h"
#include <chrono>

int main(){
    CNet Watts1 = CNet::WattsStrogatz(100000, 1000, 0.5);
    Watts1.plot_degree_distribution("qt",true);
    

    return 0;
}