#include<bits/stdc++.h>
using namespace std;

class RoutingManagmnetSystem {
public:
    map<char, vector<pair<char, int>>> RoutingData;
    char source, destination;

    RoutingManagmnetSystem() {
        // Initialize routing data in the constructor
        RoutingData['A'].push_back({'B',20});
        RoutingData['B'].push_back({'A',20});
        RoutingData['A'].push_back({'E',40});
        RoutingData['E'].push_back({'A',40});
        RoutingData['A'].push_back({'F',30});
        RoutingData['F'].push_back({'A',30});
        RoutingData['B'].push_back({'F',25});
        RoutingData['F'].push_back({'B',25});
        RoutingData['B'].push_back({'D',20});
        RoutingData['D'].push_back({'B',20});
        RoutingData['C'].push_back({'F',45});
        RoutingData['F'].push_back({'C',45});
        RoutingData['C'].push_back({'D',30});
        RoutingData['D'].push_back({'C',30});
        RoutingData['C'].push_back({'E',20});
        RoutingData['E'].push_back({'C',20});
    }

    void IntroductionMessage() {
        cout << "press 1 to see all the cities" << endl;
        cout << "press 2 to see if a city exists or not" << endl;
        cout << "press 3 to add routes between two cities" << endl;
        cout << "press 4 to see all the routes between two cities" << endl;
        cout << "press 5 to see the shortest route between two cities" << endl;
        cout << "press 6 to delete the route between two cities" << endl;
        cout << "press 7 to see the busiest city among all cities" << endl;
        cout << "press 8 to exit" << endl;
    }

    void validation(string textdisplay) {
        bool CorrectInputOrNot = false;
        while (CorrectInputOrNot == false) {
            cout << textdisplay << endl;
            cin >> source >> destination;
            if (!(source >= 'A' and source <= 'Z' and destination >= 'A' and destination <= 'Z')) {
                cout << "You have entered invalid input. Please give valid input" << endl;
                CorrectInputOrNot = false;
            }
            else
                CorrectInputOrNot = true;
        }
    }

    void ListCities() {
        cout << "The cities are:" << endl;
        for (auto printcities : RoutingData) {
            cout << printcities.first << endl;
        }
    }

    void CityFoundorNot() {
        char searchcity;
        EnterCorrectInput:
        cout << "Please enter the city to be searched" << endl;
        cin >> searchcity;
        if (!(searchcity >= 'A' and searchcity <= 'Z')) {
            cout << "You have entered invalid input. Please give valid input" << endl;
            goto EnterCorrectInput;
        }
        if (RoutingData.find(searchcity) != RoutingData.end()) {
            printf("%c city is found", searchcity);
            cout << endl;
        }
        else {
            printf("%c is not found", searchcity);
            cout << endl;
        }
    }

    void Addroutes() {
        validation("Enter the two cities to add routes between them");
        EnterCorrectDistance:
        cout << "Enter the distance between two cities" << endl;
        int distance;
        cin >> distance;
        if (distance <= 0) {
            cout << "You have entered invalid input. Please give valid input" << endl;
            goto EnterCorrectDistance;
        }
        bool findcity = false;
        if (RoutingData.find(source) == RoutingData.end() and RoutingData.find(destination) == RoutingData.end()) {
            printf("Unable to add route between %c to %c cities\n", source, destination);
        }
        else {
            for (auto tofind = RoutingData[source].begin(); tofind != RoutingData[source].end(); tofind++) {
                if (tofind->first == destination) {
                    findcity = true;
                    break;
                }
            }
            if (findcity) {
                printf("The route is already added between %c to %c cities ", source, destination);
                cout << endl;
            }
            else {
                RoutingData[source].push_back({ destination, distance });
                RoutingData[destination].push_back({ source, distance });
                printf("The route is successfully added between %c to %c cities with %d kilometers", source, destination, distance);
                cout << endl;
            }
        }
    }

    void AllRoutes(char source, char destination, map<char, vector<pair<char, int>>>& RoutingData1, string path, int kilometers, int& minimum, vector<pair<string, int>>& result, int behave = -1) {
        if (source == destination) {
            if (behave == 1) {
                result.push_back({ path, kilometers });
                minimum = min(kilometers, minimum);
            }
            else
                cout << "path is" << " " << path << " " << "with" << " " << kilometers << endl;
            return;
        }

        if (path.find(source) == string::npos)
            path.push_back(source);

        for (auto it : RoutingData1[source]) {
            if (path.find(it.first) == string::npos) {
                path.push_back(it.first);
                kilometers += it.second;
                AllRoutes(it.first, destination, RoutingData1, path, kilometers, minimum, result, behave);
                path.pop_back();
                kilometers -= it.second;
            }
        }
    }

    void PrintAllRoutes() {
        int minimum = 0;
        vector<pair<string, int>> result;
        validation("Enter the two cities to see all the possible routes between those cities");
        AllRoutes(source, destination, RoutingData, "", 0, minimum, result, -1);
    }

    void ShortestRoute() {
        int minimum = INT_MAX;
        vector<pair<string, int>> result;
        validation("Enter the two cities to see the shortest routes between two cities");

        if (RoutingData.find(source) == RoutingData.end() or RoutingData.find(destination) == RoutingData.end())
            printf("There is no route that is existed between %c to %c cities\n", source, destination);
        else {
            AllRoutes(source, destination, RoutingData, "", 0, minimum, result, 1);
            printf("The shortest routes between %c to %c cities is\n", source, destination);

            for (auto shorterroutes : result) {
                if (shorterroutes.second == minimum) {
                    cout << shorterroutes.first << " " << "with" << " " << shorterroutes.second << endl;
                }
            }
        }
    }

    // Other methods remain unchanged...
    void DeleteRoute(){
       validation("Enter those two city names to delete the route between them");
       int deleted=1;
       if(RoutingData.find(source)==RoutingData.end() or RoutingData.find(destination)==RoutingData.end()){
            cout<<"city/cities is not found"<<endl;
       }
       else{
       for(auto deleteornot= RoutingData[source].begin(); deleteornot!=RoutingData[source].end(); deleteornot++){
           if(deleteornot->first==destination){
               if(RoutingData[source].size()!=1  and RoutingData[destination].size()!=1){
                   RoutingData[source].erase(deleteornot);
                    for(auto deleteornot= RoutingData[destination].begin(); deleteornot!=RoutingData[destination].end();deleteornot++){
                      if(deleteornot->first==source){
                         RoutingData[destination].erase(deleteornot);
                         break;
                          }
                    }
                printf("The route between city %c and city %c is deleted successfully\n",source,destination);
                deleted=0;
                break;
            }
            else{
                deleted=2;
                break;
            }
        }
       }
       }
        if(deleted==1)
          printf("There is no route that is existed between %c to %c cities\n", source, destination);
            else if(deleted==2)
            printf("Unable to delete the route between %c to %c cities\n",source,destination);
    }

    void BusyCity() {
        string busycities;
        int maximum = 0;
        for (auto findmaximumroutes : RoutingData) {
            int temp = RoutingData[findmaximumroutes.first].size();
            maximum = max(maximum, temp);
        }

        for (auto findmaximumroutes : RoutingData) {
            if (maximum == int(RoutingData[findmaximumroutes.first].size())) {
                busycities.push_back(findmaximumroutes.first);
            }
        }
        cout << "The busiest cities are:" << endl;
        for (auto printcities : busycities) {
            cout << printcities << " ";
        }
        cout << endl;
    }

};

int main() {
    RoutingManagmnetSystem routingmanagmentsystem;
    while (1) {
        routingmanagmentsystem.IntroductionMessage();
        string option;
        cin >> option;
        while (!(option.size() == 1 and option[0] >= '1' and option[0] <= '8')) {
            cout << "Invalid input" << endl;
            routingmanagmentsystem.IntroductionMessage();
            cin >> option;
        }

        switch (option[0] - '0') {
        case 1:
            routingmanagmentsystem.ListCities();
            break;
        case 2:
            routingmanagmentsystem.CityFoundorNot();
            break;
        case 3:
            routingmanagmentsystem.Addroutes();
            break;
        case 4:
            routingmanagmentsystem.PrintAllRoutes();
            break;
        case 5:
            routingmanagmentsystem.ShortestRoute();
            break;
        case 6:
            routingmanagmentsystem.DeleteRoute();
            break;
        case 7:
            routingmanagmentsystem.BusyCity();
            break;
        case 8:
            cout << "Program is successfully exited" << endl;
            return 0;
        }
    }
}
