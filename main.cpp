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
    Net Watts = Net::WattsStrogatz(20, 2, 0.9);
    //Watts.print();
    std::cout << "Degree distribution: " << std::endl;
    for (const auto& i : Watts.degree_distribution()) {
        std::cout << i << " ";
    }
    //Net ring = Net::ring(10000, 10);
    //ring.print(); */
    return 0;
}