#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <set>
using namespace std;

int main()
{
// input for title
string input;
cout << "Enter a title for the data:" << endl;
getline(cin, input);
cout << "You entered: " << input << endl;

//input for header 1 
string column1;
cout << "Enter the column 1 header:" << endl;
getline(cin, column1);
cout << "You entered: " << column1 << endl;

//input for header 2
string column2;
cout << "Enter the column 2 header:" << endl;
getline(cin, column2);
cout << "You entered: " << column2 << endl;

//Prompting for data points
vector<string> dStrings;
vector<int> dInts;
while (true){
  try {
      string dpoint;
      cout << "Enter a data point (-1 to stop input):" << endl;
      getline(cin, dpoint);
      if (dpoint == "-1"){
        break;
      }

      int position = dpoint.find(",");
      int counter = 0;
      for(int i = 0; i < dpoint.length(); i++){
        if (dpoint[i] == ','){
          counter++;
        }
      }

      if(counter > 1){
        cout << "Error: Too many commas in input." << endl;
        continue;
      }
      else if(counter < 1){
        cout << "Error: No comma in string." << endl;
        continue;
      }

      string name = dpoint.substr(0, position);
      string snumnovel = dpoint.substr(position + 1);
      int numnovel = stoi(snumnovel);
      dStrings.push_back(name);
      dInts.push_back(numnovel);

      cout << "Data string: " << name << endl;
      cout << "Data integer: " << numnovel << endl;
    }
  catch(invalid_argument){
    cout << "Error: Comma not followed by an integer." << endl;
    continue;
  }       
}
  //formatting table
  if(dStrings.size()!=0){
    cout << endl;
    cout << setw(33) << input << endl;
    cout << setw(20) << left << column1 << "|" << setw(23) << right << column2 << endl;
    cout << "--------------------------------------------" << endl;
    for(int j = 0; j < dStrings.size(); j++){
      cout << setw(20) << left << dStrings[j] << "|" << setw(23) << right << dInts[j] << endl;
    }

    int count = 0;
    cout << endl;
    while(count < dStrings.size()){
        cout << setw(20) << right << dStrings[count] << " ";
        for(int i = 0 ; i<dInts[count] ; i++){
          cout <<"*";
        }
        cout << endl;
        count++;
    }
  }
return 0;
}

