#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

// Define classes for each animal species
class Animal {
public:
    std::string name;
    int age;
    std::string sex;
    std::string species;
    std::string color;
    double weight;
    std::string birthday;

    Animal(std::string name, int age, std::string sex, std::string species, std::string color, double weight, std::string birthday) {
        this->name = name;
        this->age = age;
        this->sex = sex;
        this->species = species;
        this->color = color;
        this->weight = weight;
        this->birthday = birthday;
    }
};

class Hyena : public Animal {
public:
    Hyena(std::string name, int age, std::string sex, std::string color, double weight, std::string birthday)
        : Animal(name, age, sex, "Hyena", color, weight, birthday) {}
};

class Lion : public Animal {
public:
    Lion(std::string name, int age, std::string sex, std::string color, double weight, std::string birthday)
        : Animal(name, age, sex, "Lion", color, weight, birthday) {}
};

class Tiger : public Animal {
public:
    Tiger(std::string name, int age, std::string sex, std::string color, double weight, std::string birthday)
        : Animal(name, age, sex, "Tiger", color, weight, birthday) {}
};

class Bear : public Animal {
public:
    Bear(std::string name, int age, std::string sex, std::string color, double weight, std::string birthday)
        : Animal(name, age, sex, "Bear", color, weight, birthday) {}
};

int main() {
    // Load animal names from file
    std::ifstream animalNamesFile("animalNames.txt");
    std::vector<std::string> animalNames;
    std::string name;
    while (std::getline(animalNamesFile, name)) {
        animalNames.push_back(name);
    }
    animalNamesFile.close();

    // Load animal data from file
    std::ifstream arrivingAnimalsFile("arrivingAnimals.txt");
    std::vector<std::string> animalData;
    std::string line;
    while (std::getline(arrivingAnimalsFile, line)) {
        animalData.push_back(line);
    }
    arrivingAnimalsFile.close();

    // Initialize lists to store animals
    std::vector<Hyena> hyenas;
    std::vector<Lion> lions;
    std::vector<Tiger> tigers;
    std::vector<Bear> bears;

    // Initialize counters for unique IDs
    int hyenaId = 1;
    int lionId = 1;
    int tigerId = 1;
    int bearId = 1;

    // Process animal data
    for (int i = 0; i < animalData.size(); i++) {
        std::istringstream iss(animalData[i]);
        std::string token;
        std::vector<std::string> tokens;
        while (std::getline(iss, token, ',')) {
            tokens.push_back(token);
        }

        int age = std::stoi(tokens[0]);
        std::string sex = tokens[1];
        std::string species = tokens[2];
        std::string color = tokens[3];
        double weight = std::stod(tokens[4]);

        // Calculate birthday
        time_t now = time(0);
        tm* ltm = localtime(&now);
        ltm->tm_year -= age;
        ltm->tm_mon = 0; // January
        ltm->tm_mday = 1; // 1st day of the month
        time_t birthdayTime = mktime(ltm);
        char birthday[11];
        strftime(birthday, sizeof(birthday), "%Y-%m-%d", ltm);

        // Assign unique name
        std::string name = animalNames[i];

        // Create animal object and add to list
        if (species == "Hyena") {
            Hyena animal(name, age, sex, color, weight, birthday);
            hyenas.push_back(animal);
            std::cout << "Hyena ID: H" << hyenaId << std::endl;
            hyenaId++;
        } else if (species == "Lion") {
            Lion animal(name, age, sex, color, weight, birthday);
            lions.push_back(animal);
            std::cout << "Lion ID: L" << lionId << std::endl;
            lionId++;
        } else if (species == "Tiger") {
            Tiger animal(name, age, sex, color, weight, birthday);
            tigers.push_back(animal);
            std::cout << "Tiger ID: T" << tigerId << std::endl;
            tigerId++;
        } else if (species == "Bear") {
            Bear animal(name, age, sex, color, weight, birthday);
            bears.push_back(animal);
            std::cout << "Bear ID: B" << bearId << std::endl;
            bearId++;
        }
    }

    // Write report to file
    std::ofstream zooPopulationFile("zooPopulation.txt");
    zooPopulationFile << "Hyenas:\n";
    for (int i = 0; i < hyenas.size(); i++) {
        zooPopulationFile << "ID: H" << i + 1 << ", Name: " << hyenas[i].name << ", Age: " << hyenas[i].age << ", Sex: " << hyenas[i].sex << ", Color: " << hyenas[i].color << ", Weight: " << hyenas[i].weight << ", Birthday: " << hyenas[i].birthday << "\n";
    }
    zooPopulationFile << "\nLions:\n";
    for (int i = 0; i < lions.size(); i++) {
        zooPopulationFile << "ID: L" << i + 1 << ", Name: " << lions[i].name << ", Age: " << lions[i].age << ", Sex: " << lions[i].sex << ", Color: " << lions[i].color << ", Weight: " << lions[i].weight << ", Birthday: " << lions[i].birthday << "\n";
    }
    zooPopulationFile << "\nTigers:\n";
    for (int i = 0; i < tigers.size(); i++) {
        zooPopulationFile << "ID: T" << i + 1 << ", Name: " << tigers[i].name << ", Age: " << tigers[i].age << ", Sex: " << tigers[i].sex << ", Color: " << tigers[i].color << ", Weight: " << tigers[i].weight << ", Birthday: " << tigers[i].birthday << "\n";
    }
    zooPopulationFile << "\nBears:\n";
    for (int i = 0; i < bears.size(); i++) {
        zooPopulationFile << "ID: B" << i + 1 << ", Name: " << bears[i].name << ", Age: " << bears[i].age << ", Sex: " << bears[i].sex << ", Color: " << bears[i].color << ", Weight: " << bears[i].weight << ", Birthday: " << bears[i].birthday << "\n";
    }
    zooPopulationFile.close();

    return 0;
}
