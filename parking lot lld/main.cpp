#include<bits/stdc++.h>
using namespace std;
#define ll long long

vector<string> splitOn(string s, char on){
    vector<string> res;
    s = s + on;
    string temp = "";
    for(char c : s){
        if(c == on){
            res.push_back(temp);
            temp = "";
        }
        else
            temp += c;
    }
    return res;
}


// Hard coded 
const string CAR = "CAR";
const string BIKE = "BIKE";
const string TRUCK = "TRUCK";
unordered_map<string, string> vehicleTypes;

unordered_map<string, pair<int,int>> slotsInfo;


class Vehicle
{
    public:
        string type;
        string regNo;
        string color;

        Vehicle(string type, string regNo, string color){
            this->type = type;
            this->regNo = regNo;
            this->color = color;
        }
};

class ParkingLot{
        string id;
        int floors;
        int slots;

        unordered_map<string, set<vector<int>>> emptySlots;
        unordered_map<string, vector<int>> freeCounts;
        unordered_map<int, unordered_map<int, Vehicle*>> parkedSpots;

        void dispalyOccupiedSlotsHelper(string type, int floor, string count){
            cout << "Occupied slots for " + type + " on Floor " + to_string(floor) + ": " + count +"\n";
        }

        void dispalyFreeCountHelper(string type, int floor, int count){
            cout << ( "No. of free slots for " + type + " on Floor " + to_string(floor) + ": " + to_string(count) + "\n");
        }

        void displayFreeSlotsHelper(string type, int floor, string count){
            cout << ("Free slots for " + type +" on Floor " + to_string(floor) + ": " + count + "\n" );
        }

        string parkingDispalyHelper(int floor, int slot){
            return "Parked vehicle. Ticket ID: " + this->id + "_" + to_string(floor) + "_" + to_string(slot);
        }

    public:
        ParkingLot(string id, int floors, int slots){
            this->id = id;
            this->floors = floors;
            this->slots = slots;
            // Pre calculations

            for(auto e : vehicleTypes){
                emptySlots[e.first] = set<vector<int>>();
                freeCounts[e.first] = vector<int>(1, 0);
            }

            for(int floor = 1 ; floor <= floors ; ++floor){
                emptySlots[TRUCK].insert({floor, 1});
                emptySlots[BIKE].insert({floor, 2});
                emptySlots[BIKE].insert({floor, 3});
                for(int slot = 4 ; slot <= slots ; ++slot)
                    emptySlots[CAR].insert({floor, slot});
                freeCounts[TRUCK].push_back(1);
                freeCounts[BIKE].push_back(2);
                freeCounts[CAR].push_back(slots - 3);
            }
            cout << ("Created parking lot with " + to_string(floors)  +" floors and "+ to_string(slots) + " slots per floor\n");
        }

// park_vehicle CAR KA-01-DB-1234 black
        string park(Vehicle *vehicle){
            string ticket = "";
            int floor = -1;
            int slot = -1;
            if(!emptySlots[vehicle->type].empty()){
                vector<int> temp = *(emptySlots[vehicle->type].begin());
                emptySlots[vehicle->type].erase(emptySlots[vehicle->type].begin());
                floor = temp[0], slot = temp[1];
                freeCounts[vehicle->type][floor]--;
            }
            if(floor == -1)
                return "Parking Lot Full";
            parkedSpots[floor][slot] = vehicle;
            return parkingDispalyHelper(floor, slot);
        }

        string unpark(int floor, int slot){
            if( parkedSpots[floor].count(slot) == 0  )
                return "Invalid Ticket";
            Vehicle *vehicle = parkedSpots[floor][slot];
            parkedSpots[floor].erase(slot);
            emptySlots[vehicle->type].insert({floor, slot});
            freeCounts[vehicle->type][floor]++;
            return "Unparked vehicle with Registration Number: " + vehicle->regNo +  " and Color: " + vehicle->color;
        }

        void displayFreeCount(string type){
            for(int floor = 1 ; floor <= floors ; ++ floor)
                dispalyFreeCountHelper(type, floor, freeCounts[type][floor]);
        }

        void displayFreeSlots(string type){
            unordered_map<int,string> onFloor;
            for(auto v : emptySlots[type]){
                int floor = v[0], slot = v[1];
                if(onFloor.count(floor))
                    onFloor[floor] = onFloor[floor] + "," + to_string(slot);
                else
                    onFloor[floor] = to_string(slot);
            }
            for(int floor = 1 ; floor <= floors ; ++ floor)
                displayFreeSlotsHelper(type, floor, onFloor[floor]);
        }

        void displayOccupiedSlots(string type){
            for(int floor = 1 ; floor <= floors ; ++floor){
                string s = "";
                for(int slot = slotsInfo[type].first ; slot <= slotsInfo[type].second ; ++slot)
                    if(parkedSpots[floor][slot] != NULL )
                            if(s.empty())
                                s = to_string(slot);
                            else
                                s = s + "," + to_string(slot);
                dispalyOccupiedSlotsHelper(type, floor, s);
            }
        }
};


int main(){
    #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    #endif
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    // Init

    vehicleTypes[CAR] = CAR;
    vehicleTypes[BIKE] = BIKE;
    vehicleTypes[TRUCK] = TRUCK;

    

    ParkingLot *parkingLot = NULL;

    bool loop = true;

    while(loop){
        string input;
        getline(cin,input);
        vector<string> ins = splitOn(input, ' ');

        if(ins[0] == "exit")
            loop = false;

        else if(ins[0] == "create_parking_lot" ){
            string id = ins[1];
            int floors = stoi(ins[2]);
            int slots = stoi(ins[3]);
            parkingLot = new ParkingLot(id, floors, slots);
            slotsInfo[TRUCK] = {1, 1};
            slotsInfo[BIKE] = {2, 2};
            slotsInfo[CAR] = {3, slots};
        }
        
        else if(ins[0] == "park_vehicle")
            cout << parkingLot->park(new Vehicle(ins[1], ins[2], ins[3])) << "\n";
        
        else if(ins[0] == "unpark_vehicle"){
            vector<string> ticket = splitOn(ins[1], '_');
            cout << parkingLot->unpark(stoi(ticket[1]), stoi(ticket[2])) << "\n";
        }

        else if(ins[0] == "display"){
            if(ins[1] == "free_count")
                parkingLot->displayFreeCount(ins[2]);
            else if(ins[1] == "free_slots")
                parkingLot->displayFreeSlots(ins[2]);
            else if(ins[1] == "occupied_slots")
                parkingLot->displayOccupiedSlots(ins[2]);
        }
    }

    return 0;
}