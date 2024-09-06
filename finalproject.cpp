#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <vector>
#include <random>


class Device {
public:
    double price; //asking price
    int coords[2]; //location on map in (x, y) form
    int radius = 5; //will always be 5
    int weight = 0; //how many devices are in the area
    double efficiency; //weight/price, determined after area creation
    bool cover = false; //set true if covered by a collected device


    //no-arg constructor
    Device() {
    }

    //price input constructor
    Device(double price) {
        this->price = price;
    }
};

//function prototypes
void testingMode(double& budget);
void generationSelect(double& budget);

void genRegion();
void genUniform(double budget);
void genRandom(double budget);
void countWeight();

void printResults(std::vector<Device*> solSet);

std::vector<Device*> pureGreedy(double budget);
std::vector<Device*> pureRandom(double budget);
std::vector<Device*> solution(double budget);


//global variables
int location[100][2];
Device* area[100][100];

int main() {
    //allows for rng
    srand(time(0));

    //set budget
    double budget = 20.00;
    
    genRegion();
    countWeight();

    std::cout << "Pure greedy selection method\n";
    printResults(pureGreedy(budget));
    std::cout << "Random selection method\n";
    printResults(pureRandom(budget));
    std::cout << "Knapsack efficiency based selection method\n";
    printResults(solution(budget));

    return 0;
}

void printResults(std::vector<Device*> solSet) {
    int nodes = 0, coverage = 0;
    double cost = 0;
    
    for(unsigned int i; i < solSet.size(); i++) {
        nodes++;
        coverage += solSet[i]->weight;
        cost += solSet[i]->price;
    }
    
    std::cout << "Number of devices collected: " << nodes << std::endl;
    std::cout << std::setprecision(3) << "Total Cost: $" << cost << std::endl;
    std::cout << "This covers a total of " << coverage << " nodes!" << std::endl;
    std::cout << std::endl;
}

void testingMode(double& budget) {
    system("clear");
    std::cout << "Hello! You are now in Testing Mode!" << std::endl << std::endl;
    
    generationSelect(budget);
}

void generationSelect(double& budget) {
    
    //variables
    int popType;

    //population prompt
    std::cout << std::endl << "What kind of population would you like to work with?" << std::endl;
    std::cout << "1) Uniform Distribution" << std::endl;
    std::cout << "2) Realistic Distribution" << std::endl;
    std::cout << "3) Random Distribution" << std::endl;
    std::cin >> popType;
    std::cout << std::endl;

    //display choice
    switch (popType) {
        case 1:
            std::cout << "You have selected a uniform distribution!" << std::endl;
            std::cout << "This means all devices have an equal chance of " << std::endl << "appearing in a given location." << std::endl;
            break;
            genUniform(budget);
        case 2:
            std::cout << "You have selected a realistic distribution!" << std::endl;
            std::cout << "This means that devices with similar prices will " << std::endl << "cluster together." << std::endl;
            genRegion();
            break;
        case 3:
            std::cout << "You have selected a random distribution!" << std::endl;
            std::cout << "This means that devices will appear with no rhyme " << std::endl << "or reason." << std::endl;
            genRandom(budget);
            break;
        default:
            std::cout << "Please select a valid input!" << std::endl;
            generationSelect(budget);
    }
    return;
}


void genRegion() { //create devices in 4 regions
    std::default_random_engine engi;
    std::normal_distribution<double> regi1x(10, 3); //initialize random location objects
    std::normal_distribution<double> regi1y(7, 3);
    std::normal_distribution<double> price1(2, .25);

    std::normal_distribution<double> regi2x(10, 2);
    std::normal_distribution<double> regi2y(60, 4);
    std::normal_distribution<double> price2(3, .15);

    std::normal_distribution<double> regi3x(73, 4);
    std::normal_distribution<double> regi3y(82, 4);
    std::normal_distribution<double> price3(10, .6);

    std::normal_distribution<double> regi4x(58, 6);
    std::normal_distribution<double> regi4y(45, 8);
    std::normal_distribution<double> price4(7, .4);


    int x, y;

    for (int i = 0; i < 25; i++) {
        x = (int)regi1x(engi);
        y = (int)regi1y(engi);
        area[x][y] = new Device(price1(engi));
        location[i][0] = x;
        location[i][1] = y;
    }
    for (int i = 0; i < 25; i++) {
        x = (int)regi2x(engi);
        y = (int)regi2y(engi);
        area[x][y] = new Device(price2(engi));
        location[i + 25][0] = x;
        location[i + 25][1] = y;
    }
    for (int i = 0; i < 25; i++) {
        x = (int)regi3x(engi);
        y = (int)regi3y(engi);
        area[x][y] = new Device(price3(engi));
        location[i + 50][0] = x;
        location[i + 50][1] = y;
    }
    for (int i = 0; i < 25; i++) {
        x = (int)regi4x(engi);
        y = (int)regi4y(engi);
        area[x][y] = new Device(price4(engi));
        location[i + 75][0] = x;
        location[i + 75][1] = y;
    }

}

void genUniform(double budget) {
    int x, y;
    double price;
    for (int i = 0; i < 100; i ++) {
        price = (rand()/(double)RAND_MAX) * (budget/10) + ((budget/10)/2);
        x = rand()%100;
        y = rand()%100;
        area[x][y] = new Device(price);
    }
}

void genRandom(double budget) {
    int a[4], b[4];
    int x, y, chance;
    double price;

    //creates 4 different sets of "reference" coordinates
    for (int j = 0; j < 4; j++) {
        a[j] = rand()%100;
        b[j] = rand()%100;
    }

    //assigns values skewed towards reference 1
    for (int i = 0; i < 25; i++) {
        price = (rand()/(double)RAND_MAX) * (budget/10) + ((budget/10)/2);
        chance = (rand()%4 + 1) * 10;
        x = rand()%chance + (a[0] - chance / 2);
        y = rand()%chance + (b[0] - chance / 2);
        area[x][y] = new Device(price);
    }

    //assigns values skewed towards reference 2
    for (int i = 0; i < 25; i++) {
        price = (rand()/(double)RAND_MAX) * (budget/10) + ((budget/10)/2);
        chance = (rand()%4 + 1) * 10;
        x = rand()%chance + (a[1] - chance / 2);
        y = rand()%chance + (b[1] - chance / 2);
        area[x][y] = new Device(price);
    }

    //assigns values skewed towards reference 3
    for (int i = 0; i < 25; i++) {
        price = (rand()/(double)RAND_MAX) * (budget/10) + ((budget/10)/2);
        chance = (rand()%4 + 1) * 10;
        x = rand()%chance + (a[2] - chance / 2);
        y = rand()%chance + (b[2] - chance / 2);
        area[x][y] = new Device(price);
    }

    //assigns values skewed towards reference 4
    for (int i = 0; i < 25; i++) {
        price = (rand()/(double)RAND_MAX) * (budget/10) + ((budget/10)/2);
        chance = (rand()%4 + 1) * 10;
        x = rand()%chance + (a[3] - chance / 2);
        y = rand()%chance + (b[3] - chance / 2);
        area[x][y] = new Device(price);
    }
}


void countWeight() {//iterate over each device's covered area, count total devices covered. will count self
    for (int i = 0; i < 100; i++) {//each device...
        if (area[location[i][0]][location[i][1]]->cover == false) {//that is not covered.
            area[location[i][0]][location[i][1]]->weight = 0;
            for (int j = -5; j < 5; j++) {//slices of vertical area covered by the device
                if (location[i][0] + j >= 0) {//within area bounds
                    for (int k = 0; k <= -abs(j) + 5; k++) {//top half of the slice
                      //if within bounds, check if a device is at each position
                        if (area[location[i][0]][location[i][1] + k] != NULL)
                            area[location[i][0]][location[i][1]]->weight++;
                    }
                    for (int k = 1; k <= -abs(j) + 5; k++) {//bottom half of the slice, not counting middle horizontal
                        if (area[location[i][0]][location[i][1] - k] != NULL)
                            area[location[i][0]][location[i][1]]->weight++;
                    }
                }
            }
        }
        area[location[i][0]][location[i][1]]->efficiency = area[location[i][0]][location[i][1]]->weight / area[location[i][0]][location[i][1]]->price;
    }
}

std::vector<Device*> pureGreedy(double budget) {
    std::vector<Device*> set;
    set.clear(); //ensures set is empty before starting
    Device* min = area[location[0][0]][location[0][1]];
    int vectIt = 0; //vector iterator

    
    for (int i = 0; i < 100; i++) {//each device...

        //calculates lowest price
        for (int j = 0; j < 100; j++) {
            if ((area[location[j][0]][location[j][1]]->price < min->price)) {
                min = area[location[j][0]][location[j][1]]; //looks for a lower price and sets it to min
           }
        }
        
        //adds device with lowest price to set
        if (min->price <= budget) {
            set.push_back(min);
            budget -= min->price;
            if (vectIt == 0) {
                //skips ahead
            } else if (min != set[vectIt]) {
                vectIt++;
            }
        }

        countWeight();

        //exit when budget is filled
        if (budget <= 0) {
            break;
        }
    }
    
    return set;
}

std::vector<Device*> pureRandom(double budget) {
    std::vector<Device*> set;
    set.clear(); //ensures set is empty before starting
    Device* rng;
    int vectIt = 0;

    //create and initialize array of indexes from 1 to 99
    int indexes[100];
    for (int i = 1; i < 100; i++) {
        indexes[i] = i;
    }
    
    for (int i = 1; i < 100; i++) {
        
        //select rng number randomly
        int num = rand()%99;

        //search for rng number in array of indexes
        for (int a : indexes) {
            if (indexes[a] == num) {
                indexes[a] = -1;

                //assign the corresponding device to set
                rng = area[location[num][0]][location[num][1]];
                set.push_back(rng);
                budget -= rng->price;
                if (vectIt == 0) {
                    //skips ahead
                } else if (rng != set[vectIt]) {
                    vectIt++;
                }
            }
        }

        countWeight();
        
        //exit when budget is filled
        if (budget <= 0) {
            break;
        }
    }

    return set;
}

std::vector<Device*> solution(double budget) {
    std::vector<Device*> set;
    Device* max = area[location[0][0]][location[0][1]];
    int vectIt = 0; //vector iterator
    for (int i = 1; i < 100; i++) {//each device...
        if (area[location[i][0]][location[i][1]]->cover == false) {//that is not covered.
            countWeight();
            for (int j = i; j < 100; j++) { //check rest of the list of devices for higher efficiency
                if (area[location[j][0]][location[j][1]]->efficiency > max->efficiency) {
                    max = area[location[j][0]][location[j][1]];
                }
            }
            if ((vectIt == 0) && (max->price <= budget)) {
                set.push_back(max);
                budget -= max->price;
            }
            else if ((max != set[vectIt]) && (max->price <= budget)) {
                set.push_back(max);
                budget -= max->price;
                vectIt++;
            }

            for (int j = -5; j < 5; j++) {//slices of vertical area covered by the device
                if (location[i][0] + j >= 0) {//within area bounds
                    for (int k = 0; k <= -abs(j) + 5; k++) {//top half of the slice
                      //if within bounds, check if a device is at each position
                        if (area[location[i][0]][location[i][1] + k] != NULL)
                            area[location[i][0]][location[i][1]]->cover = true;
                    }
                    for (int k = 1; k <= -abs(j) + 5; k++) {//bottom half of the slice, not counting middle horizontal
                        if (area[location[i][0]][location[i][1] + k] != NULL)
                            area[location[i][0]][location[i][1]]->cover = true;
                    }
                }
            }
        }
    }
    return set;
}