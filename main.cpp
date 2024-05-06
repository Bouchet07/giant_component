#include "graph.h"
#include <chrono>

int main(){
    CNet Watts1 = CNet::WattsStrogatz(30000, 100, 0.1);
    Watts1.plot_degree_distribution();
    

    return 0;
}