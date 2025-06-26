#include <iostream>
#include <cstdlib>
#include <vector>
#include<ctime>
#include <fstream>

using namespace std;

//declare pc struct
struct Build {
    int cpu, gpu, ssd, ram, motherboard, psu;
};

//constant declaration
const int POP_SIZE = 10; // use 10 for initial testing
const int VAR = 20; //number of alleles

const double MAX_PERF = 600; //max performance
const double MAX_PRICE = 8563.97; //max price
const double MIN_PRICE = 1440.85; //should see the pattern here 
const double MAX_POP = 60;

const double BUDGET = 4000.00; //budget set for the project//

const int GENERATIONS = 30; //generation, can be changed

//fitness
double fitness[POP_SIZE];

//declare parents
int parents[2];


//struct declaration for part attributes
struct Part {
    string name;
    double price, performance, popularity;
};

//global declaration
vector<Part> cpu, gpu, ssd, ram, motherboard, psu;

//declare parts list
void declareParts() {
    cpu = {
        { "Intel Core i5-10400F", 424.51, 28.57, 6 },
        { "AMD Ryzen 7 9700X", 1293.39, 28.76, 8 },
        { "AMD Ryzen 5 4600G", 547.67, 29.21, 5 },
        { "Intel Core i5-13600", 1082.60, 29.29, 7 },
        { "Intel Core i3-14100", 509.25, 30.00, 6 },
        { "Intel Core i3-10105F", 297.14, 30.03, 4 },
        { "Intel Core i5-11600", 594.37, 30.17, 5 },
        { "Intel Core i7 12700F", 997.65, 30.54, 7 },
        { "AMD Ryzen 5 5600XT", 717.49, 30.83, 9 },
        { "Intel Core i5-11400", 534.89, 31.57, 6 },
        { "AMD Ryzen 7 7700", 1091.09, 31.58, 8 },
        { "AMD Ryzen 5 8600G", 802.23, 31.59, 7 },
        { "Intel Core i5-13490F", 827.83, 31.93, 8 },
        { "Intel Core i7-980X", 212.23, 32.23, 3 },
        { "AMD Ryzen 5 7600", 836.32, 32.35, 7 },
        { "Intel Xeon E5-2678 v3", 450.83, 32.62, 4 },
        { "AMD Ryzen 5 8500G", 653.81, 33.06, 6 },
        { "Intel Core i5-11600K", 587.75, 33.25, 5 },
        { "AMD Ryzen 9 7900", 1401.01, 34.57, 9 },
        { "AMD Ryzen 5 5600G", 573.14, 34.45, 7 }
    };

    gpu = {
        { "GeForce 7600 GS", 526.36, 0.3, 2 },
        { "Radeon HD 5450", 287.80, 0.47, 1 },
        { "GeForce 9800 GT", 707.64, 0.64, 3 },
        { "Radeon HD 5670", 424.51, 1.88, 3 },
        { "Radeon HD 4870", 719.19, 1.93, 2 },
        { "Radeon HD 5750", 549.37, 2.13, 3 },
        { "Radeon RX 6500 XT", 764.15, 12.57, 7 },
        { "GeForce GTX 1650", 1160.93, 6.79, 6 },
        { "Radeon HD 7850", 742.92, 5.23, 3 },
        { "GeForce GT 1030", 466.79, 5.20, 5 },
        { "Radeon RX 560", 871.69, 4.20, 4 },
        { "Radeon RX 550", 721.69, 3.72, 4 },
        { "Radeon HD 7750", 466.96, 3.62, 3 },
        { "Radeon 550", 603.71, 3.52, 4 },
        { "Radeon Pro WX", 905.06, 2.53, 3 },
        { "Radeon RX 9060 XT", 1273.61, 15.87, 8 },
        { "Radeon RX 7600", 1167.47, 14.21, 9 },
        { "GeForce RTX 3050 6GB", 806.60, 13.32, 8 },
        { "Radeon RX 7600 XT", 1443.43, 11.88, 7 },
        { "GeForce RTX 2060", 1137.28, 12.41, 8 }
    };

    ssd = {
        { "Samsung SSD 980 PRO 2TB", 815.14, 51.34, 8 },
        { "Corsair Force MP600 1TB", 551.49, 51.51, 6 },
        { "Gigabyte AORUS NVMe Gen 4 M.2 1TB", 538.37, 52.79, 6 },
        { "Patriot Burst Elite 120GB", 50.90, 53.32, 4 },
        { "Corsair MP600 CORE", 420.26, 55.56, 7 },
        { "Crucial P5 Plus 2TB SSD", 700.89, 55.82, 5 },
        { "Kingston FURY Renegade 1TB SSD", 750.82, 60.45, 7 },
        { "ADATA LEGEND 860", 643.70, 61.36, 7 },
        { "WD BLACK SN7100 2TB", 820.10, 64.73, 8 },
        { "Kingston NV2 1TB SSD", 286.32, 70.42, 6 },
        { "Crucial T700 2TB SSD", 933.97, 74.92, 9 },
        { "Corsair MP600 MICRO", 403.28, 76.23, 8 },
        { "Kingston FURY Renegade 2TB SSD", 653.81, 77.22, 9 },
        { "Nvme 512GB", 165.57, 77.43, 3 },
        { "Crucial P3 1TB SSD", 283.13, 79.79, 5 },
        { "Corsair MP600 GS", 411.77, 79.97, 7 },
        { "Western Digital Blue 500GB SSD", 190.62, 82.96, 8 },
        { "Samsung SSD 980 PRO 500GB", 382.90, 91.36, 9 },
        { "Viper VP4300 2TB", 450.02, 100.00, 7 },
        { "Kingston KC3000 1TB", 424.34, 100.00, 9 }
    };

    ram = {
        { "Lexar DDR4 3200 2x16GB", 309.92, 30.33, 7 },
        { "Kingston Fury Beast DDR4 3200 8GB", 420.30, 22.36, 6 },
        { "XPG Spectrix D35G DDR4 3200", 483.99, 21.07, 5 },
        { "Corsair Vengeance DDR4 3600", 403.32, 26.28, 6 },
        { "G.SKILL Trident Z DDR4 3600 CL16", 445.78, 26.92, 7 },
        { "Crucial Ballistix DDR4 3200", 360.87, 26.60, 6 },
        { "TeamGroup T-Force DDR4 3200", 373.60, 26.23, 5 },
        { "Patriot Viper DDR4 3600", 390.59, 27.14, 7 },
        { "Corsair Dominator DDR5 6200 CL36", 1018.92, 5.63, 4 },
        { "Corsair Vengeance DDR5 6000 CL40", 934.01, 5.43, 3 },
        { "Kingston Fury Beast DDR5 6000 CL30", 1286.39, 5.13, 3 },
        { "ADATA XPG Lancer Blade DDR5 6000 CL34", 972.22, 6.36, 3 },
        { "G.SKILL Trident Z5 DDR5 6000 CL36", 1061.38, 5.52, 3 },
        { "Corsair Dominator Platinum DDR5 6000 CL36", 1125.06, 5.11, 3 },
        { "G.SKILL Trident Z5 DDR5 6400 CL32", 1167.51, 6.17, 3 },
        { "ADATA XPG Gammix DDR5 6400 CL32", 1103.83, 6.45, 3 },
        { "Corsair Vengeance RGB DDR5 6400 CL32", 1146.28, 6.29, 3 },
        { "G.SKILL Trident Z5 DDR5 7200 CL34", 1358.56, 5.70, 3 },
        { "Patriot Viper Steel DDR4 3600", 382.09, 27.74, 7 },
        { "HyperX Fury DDR4 3200", 369.36, 25.43, 6 }
    };

    motherboard = {
        { "B550-F Gaming", 750, 88, 9 },
        { "B450M Mortar Max", 420, 80, 8 },
        { "X570 Aorus Elite", 950, 90, 9 },
        { "B550M Steel Legend", 550, 83, 7 },
        { "Z590-P", 800, 85, 6 },
        { "Z690 Tomahawk WiFi DDR4", 1200, 92, 8 },
        { "B760M DS3H DDR4", 500, 81, 7 },
        { "H610M-HVS R2.0", 350, 70, 5 },
        { "Z790 Hero", 2200, 98, 10 },
        { "B550 Aorus Pro V2", 700, 86, 8 },
        { "B760M-P DDR4", 450, 79, 6 },
        { "B660M-PLUS WiFi D4", 750, 84, 8 },
        { "Z690 Gaming X DDR4", 1050, 89, 7 },
        { "B650 PG Lightning", 850, 87, 6 },
        { "B460M-A", 430, 75, 7 },
        { "B550 Gaming Edge WiFi", 780, 85, 9 },
        { "Z790 Aorus Elite AX", 1350, 94, 8 },
        { "B450M Pro4", 390, 74, 7 },
        { "Z690-A Gaming WiFi D4", 1250, 91, 9 },
        { "Z790 Carbon WiFi", 1700, 96, 10 }
    };

    psu = {
        { "RM750x (2021)", 550, 88, 9 },
        { "650 Bronze V2", 330, 80, 7 },
        { "750W 80+ Gold", 600, 89, 9 },
        { "750 G5 80+ Gold", 580, 87, 8 },
        { "GF1 650W 80+ Gold", 490, 85, 7 },
        { "CX650M 80+ Bronze", 350, 82, 8 },
        { "P750GM 80+ Gold", 420, 84, 6 },
        { "PQ750M 80+ Gold", 460, 83, 5 },
        { "ST75F-GS 750W", 530, 85, 8 },
        { "GT Pro 650W 80+ Gold", 440, 84, 7 },
        { "850W 80+ Platinum", 1100, 95, 8 },
        { "C750 80+ Gold", 570, 86, 7 },
        { "V850 SFX Gold", 850, 90, 8 },
        { "TX-850 Titanium", 1200, 98, 9 },
        { "SF600 Platinum", 680, 88, 8 },
        { "11 750W Platinum", 900, 92, 8 },
        { "RGB 700W 80+ White", 280, 75, 6 },
        { "Gold Pro 750W", 490, 84, 6 },
        { "UD750GM 80+ Gold", 450, 82, 7 },
        { "DN650 80+ White", 230, 70, 5 }
    };
}


vector<Build> generateRandomBuilds() {
    vector<Build> builds(POP_SIZE);

    for (int i = 0; i < POP_SIZE; i++) {

        builds[i].cpu = rand() % VAR;
        builds[i].gpu = rand() % VAR;
        builds[i].ssd = rand() % VAR;
        builds[i].ram = rand() % VAR;
        builds[i].motherboard = rand() % VAR;
        builds[i].psu = rand() % VAR;


    }
    return builds;
}

void printChromosome(const Build& b) {
    cout << "CPU: " << cpu[b.cpu].name << endl;
    cout << "GPU: " << gpu[b.gpu].name << endl;
    cout << "SSD: " << ssd[b.ssd].name << endl;
    cout << "RAM: " << ram[b.ram].name << endl;
    cout << "Motherboard: " << motherboard[b.motherboard].name << endl;
    cout << "PSU: " << psu[b.psu].name << endl;
}




double evaluateChromosome(const Build& b) {
    double fitness;
    double w1 = 0.5, w2 = 0.3, w3 = 0.2;
    double penalty = 0;

    double totalPerf = cpu[b.cpu].performance +
        gpu[b.gpu].performance +
        ssd[b.ssd].performance +
        ram[b.ram].performance +
        motherboard[b.motherboard].performance +
        psu[b.psu].performance;

    double totalprice = cpu[b.cpu].price +
        gpu[b.gpu].price +
        ssd[b.ssd].price +
        ram[b.ram].price +
        motherboard[b.motherboard].price +
        psu[b.psu].price;

    double totalpop = cpu[b.cpu].popularity +
        gpu[b.gpu].popularity +
        ssd[b.ssd].popularity +
        ram[b.ram].popularity +
        motherboard[b.motherboard].popularity +
        psu[b.psu].popularity;

    if (totalprice > BUDGET) {
        penalty = BUDGET / totalprice;
    }
    else {
        penalty = 1;
    }

    fitness = (w1 * (totalPerf / MAX_PERF)) +
        (w2 * (((MAX_PRICE - totalprice) / (MAX_PRICE - MIN_PRICE)) * penalty)) +
        (w3 * (totalpop / MAX_POP));

    cout << "Total Performance: " << totalPerf << endl;
    cout << "Total Price: RM" << totalprice << endl;
    cout << "Total Popularity: " << totalpop << endl;
    cout << "Fitness: " << fitness << "\n" << endl;

    return fitness;
}

int parentSelection(double fitness[]) {
    int best = rand() % POP_SIZE; //to pick random chromosome

    for (int i = 0; i < 2; i++) {
        int challenger = rand() % POP_SIZE;
        if (fitness[challenger] > fitness[best]) {
            best = challenger;
        }
    }

    return best;
}

Build crossover(const Build& parent1, const Build& parent2) {
    Build child = parent1;

    int crossoverPoint = rand() % 6;

    switch (crossoverPoint) {
    case 0: child.cpu = parent2.cpu;
    case 1: child.gpu = parent2.gpu;
    case 2: child.ssd = parent2.ssd;
    case 3: child.ram = parent2.ram;
    case 4: child.motherboard = parent2.motherboard;
    case 5: child.psu = parent2.psu;
    }

    return child;
}

Build mutate(const Build& b, double mutationRate = 0.1) {
    Build mutated = b;

    // Each component has a chance to mutate
    if ((double)rand() / RAND_MAX < mutationRate)
        mutated.cpu = rand() % VAR;

    if ((double)rand() / RAND_MAX < mutationRate)
        mutated.gpu = rand() % VAR;

    if ((double)rand() / RAND_MAX < mutationRate)
        mutated.ssd = rand() % VAR;

    if ((double)rand() / RAND_MAX < mutationRate)
        mutated.ram = rand() % VAR;

    if ((double)rand() / RAND_MAX < mutationRate)
        mutated.motherboard = rand() % VAR;

    if ((double)rand() / RAND_MAX < mutationRate)
        mutated.psu = rand() % VAR;

    return mutated;
}

void survivalSelection(vector<Build>& builds, double fitness[], const Build& child, double childFitness, int parentIndex) {
    if (childFitness > fitness[parentIndex]) {
        builds[parentIndex] = child;
        fitness[parentIndex] = childFitness;
        cout << "Child replaces parent " << parentIndex << " (Fitness improved to " << childFitness << ")\n";
    }
    else {
        cout << "Child did not outperform parent " << parentIndex << " (Remains with fitness " << fitness[parentIndex] << ")\n";
    }
}

int main()
{
    srand(time(0));

    declareParts();
    ofstream csvFile("fitness_log.csv");
    csvFile << "Generation,BestFitness,AverageFitness\n";  // CSV header




    cout << "\n====== INITIAL POPULATION ======\n";
    vector<Build> builds = generateRandomBuilds();

    for (int i = 0; i < POP_SIZE; i++) {
        fitness[i] = evaluateChromosome(builds[i]);
    }



    for (int gen = 0; gen < GENERATIONS; gen++) {
        cout << "\n======= GENERATION " << gen + 1 << " =======\n";

        // PARENT SELECTION
        parents[0] = parentSelection(fitness);
        do {
            parents[1] = parentSelection(fitness);
        } while (parents[1] == parents[0]);

        cout << "Parent 1: Build " << parents[0] << "\n";
        cout << "Parent 2: Build " << parents[1] << "\n";

        // CROSSOVER
        Build child1 = crossover(builds[parents[0]], builds[parents[1]]);
        Build child2 = crossover(builds[parents[1]], builds[parents[0]]);

        // MUTATION
        Build mutatedChild1 = mutate(child1);
        Build mutatedChild2 = mutate(child2);

        // FITNESS EVALUATION
        double mutatedFitness1 = evaluateChromosome(mutatedChild1);
        double mutatedFitness2 = evaluateChromosome(mutatedChild2);

        // SURVIVAL SELECTION
        survivalSelection(builds, fitness, mutatedChild1, mutatedFitness1, parents[0]);
        survivalSelection(builds, fitness, mutatedChild2, mutatedFitness2, parents[1]);

        // Evaluate best and average fitness
        double best = fitness[0];
        double total = fitness[0];
        for (int i = 1; i < POP_SIZE; i++) {
            if (fitness[i] > best) best = fitness[i];
            total += fitness[i];
        }
        double avg = total / POP_SIZE;

        cout << "Best Fitness this generation: " << best << "\n";
        cout << "Average Fitness this generation: " << avg << "\n";
        csvFile << gen + 1 << "," << best << "," << avg << "\n";

        // Stop running if no improvement over x amount of generations
        const int IMPROVEMENT = 10;
        double globalBest = 0.0;
        int noImprovementCount = 0;

        if (best > globalBest) {
            globalBest = best;
            noImprovementCount = 0;
        }
        else {
            noImprovementCount++;
        }

        if (noImprovementCount >= IMPROVEMENT) {
            cout << "\nNo improvement in best fitness for 10 generations. Stopping early at generation " << gen + 1 << ".\n";
            break;
        }
    }

    csvFile.close();

    return 0;
}