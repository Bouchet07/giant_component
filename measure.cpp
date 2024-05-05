#include "graph.h"
#include <chrono>

int main(){
    std::cout << "Measure time and compare CNet, Net and MNet\n";
    std::cout << "Watts-Strogatz network\n";
    node nodes = 10000;
    size_t links = 1000;
    double beta = 0.9;
    // measure time
    auto start = std::chrono::high_resolution_clock::now();

    CNet Watts1 = CNet::WattsStrogatz(nodes, links, beta);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Time CNet: " << elapsed.count() << " s\n";


    /* start = std::chrono::high_resolution_clock::now();

    Net Watts2 = Net::WattsStrogatz(nodes, links, beta);

    end = std::chrono::high_resolution_clock::now();
    elapsed = end - start;
    std::cout << "Time Net: " << elapsed.count() << " s\n"; */

    start = std::chrono::high_resolution_clock::now();

    MNet Watts3 = MNet::WattsStrogatz(nodes, links, beta);

    end = std::chrono::high_resolution_clock::now();
    elapsed = end - start;
    std::cout << "Time MNet: " << elapsed.count() << " s\n";

    // print degree distribution
    /* auto vec1 = Watts1.degree_distribution();
    std::cout << "Degree distribution CNet: ";
    for (auto i : vec1) {
        std::cout << i << " ";
    } */
    /* std::cout << std::endl;
    auto vec2 = Watts2.degree_distribution();
    std::cout << "Degree distribution Net: ";
    for (auto i : vec2) {
        std::cout << i << " ";
    } */
    /* std::cout << std::endl;
    auto vec3 = Watts3.degree_distribution();
    std::cout << "Degree distribution MNet: ";
    for (auto i : vec3) {
        std::cout << i << " ";
    } */
    std::cout << "giant component\n";
    node r1 = 5, r2 = 10000;
    start = std::chrono::high_resolution_clock::now();

    CNet Watts4 = CNet::ring(r1) + CNet::ring(r2);
    CNet giant4 = Watts4.get_giant_component();

    end = std::chrono::high_resolution_clock::now();
    elapsed = end - start;
    std::cout << "Time CNet: " << elapsed.count() << " s\n";



    start = std::chrono::high_resolution_clock::now();

    Net Watts5 = Net::ring(r1) + Net::ring(r2);
    Net giant5 = Watts5.get_giant_component();

    end = std::chrono::high_resolution_clock::now();
    elapsed = end - start;
    std::cout << "Time Net: " << elapsed.count() << " s\n";

    return 0;
}