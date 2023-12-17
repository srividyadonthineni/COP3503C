#include <iostream>
#include <map>
#include <random>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

mt19937 random_mt;

class StateData{
    private:
        string name;
        int income;
        int population;
        int medIncome;
        int numHousehold;

    public:
        StateData() : name(""), income(0), population(0), medIncome(0), numHousehold(0) {}

        StateData(const std::string& nameData, int incomeData, int popData, int medData, int houseData)
                : name(nameData), income(incomeData), population(popData), medIncome(medData), numHousehold(houseData) {}

        void PrintData() const{
            cout << name << endl;
            cout << "Population: " << population << endl;
            cout << "Per Capita Income: " << income << endl;
            cout << "Median Household Income: " << medIncome << endl;
            cout << "Number of Households: " << numHousehold << endl;
        }
};

int Random(int min, int max)
{
	uniform_int_distribution<int> dist(min, max);
	return dist(random_mt);
}

void RollDice(int numberOfRolls, int numberOfSides){
	map<int,int> diceMap;
    for (unsigned int i = 1; i <= numberOfSides; i++) {
        diceMap[i] = 0;
    }

    for (unsigned int i = 0; i < numberOfRolls; i++) {
        int result = Random(1, numberOfSides);
        diceMap[result]++;
    }

    for (const auto& pair : diceMap) {
        std::cout << pair.first << ": " << pair.second << endl;
    }

}

int main()
{
    map<string, StateData> maps;
	cout << "1. Random Numbers\n";
	cout << "2. State Info\n";

	int option;
	cin >> option;

	if (option == 1)
	{
		int randomSeed;
		cout << "Random seed value: ";
		cin >> randomSeed;
		random_mt.seed(randomSeed);


		cout << "Number of times to roll the die: ";
      // user input
			int diceRoll;
			cin >> diceRoll;

		cout << "Number of sides on this die: ";
      // user input
			int dieSides;
			cin >> dieSides;

		// Roll Dice
		RollDice(diceRoll, dieSides);
	}
	else if (option == 2)
	{
	  // Load the states
        vector<string> stateData;
        string row;
        string data;

        ifstream stream;
        stream.open("states.csv");
        if(!stream.is_open()){
            throw runtime_error("Could not open file.");
        }

        getline(stream, row);

        while(!stream.eof()){
            stateData.clear();
            getline(stream, row);
            istringstream stateStream(row);
            while(getline(stateStream, data, ',')){
                stateData.push_back(data);
            }

            StateData current((stateData[0]), stoi(stateData[1]), stoi(stateData[2]), stoi(stateData[3]), stoi(stateData[4]));
            maps[stateData[0]] = current;
        }

        // Get input for option 1 (show all states) or 2 (do a search for a particular state)
        cout << "1. Print all states\n";
        cout << "2. Search for a state\n";
        int secondOption;
        cin >> secondOption;

        if(secondOption == 1) {
            for (const auto& pair : maps) {
                string stateName = pair.first;
                StateData stateInfo = pair.second;
                stateInfo.PrintData();
            }
        }
        if(secondOption == 2){
            string stateName;
            cin >> stateName;

            if (maps.find(stateName) != maps.end()) {
                StateData temp = maps[stateName];
                temp.PrintData();
            }
            else { cout << "No match found for " << stateName << "\n"; }
        }
    }

	return 0;
}
