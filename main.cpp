#include "graph.h"

int main(){
    
    /* std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, 1000);

    auto start = std::chrono::high_resolution_clock::now();
    Net net;
    for (int i = 0; i < 1000; i++) {
        net.add(i);
    }
    for (int i = 0; i < 1000; i++) {
        for (int j = 0; j < 1; j++) {
            net.link(i, dist(gen));
        }
    }
    Net giant = net.get_giant_component();
    giant.print();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Elapsed time: " << elapsed.count() << " s\n"; */
    Net Watts1 = Net::WattsStrogatz(5000, 10, 0.1);
    //Net Watts2 = Net::WattsStrogatz(10000, 10, 0.5);
    //Net Erdos1 = Net::ErdosRenyi(10000, 0.0001);
    Watts1.plot_degree_distribution();
    return 0;
}