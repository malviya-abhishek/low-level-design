#include<bits/stdc++.h>
using namespace std;
#define ll long long

vector<string> splitOn(string s, char on)
{
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


// create_parking_lot <parking_lot_id> <no_of_floors> <no_of_slots_per_floor>
// park_vehicle <vehicle_type> <reg_no> <color>
// unpark_vehicle <ticket_id>
// display <display_type> <vehicle_type>
// Possible values of display_type: free_count, free_slots, occupied_slots
// exit


const string CAR = "CAR";
const string BIKE = "BIKE";
const string TRUCK = "TRUCK";

class Vehicle{
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

        set<int> parkedSpots;
        string id;
        int floors;
        int slots;
        
        priority_queue<int> parkedCars = {0};
        priority_queue<int> parkedBikes = {0};
        priority_queue<int> parkedTrucks = {0};

        vector<int> truckFreeCount;
        vector<int> bikeFreeCount;
        vector<int> carFreeCount;

        int genHash(int floor, int slot){
            return floor * (this->slots + 1) * slot;
        }


        // floor, slot
        vector<int> resolveHash(int hash){
            return { hash / (slots + 1), hash % (slots + 1) };
        }

    public:
        ParkingLot(string id, int floors, int slots){
            this->id = id;
            this->floors = floors;
            this->slots = slots;

            // Pre calculations

            for(int floor = 1 ; floor <= floors ; ++floor){
                parkedTrucks.push( this->genHash(floor, 1) );
                truckFreeCount.push(1);
                parkedBikes.push( this->genHash(floor, 2) );
                parkedBikes.push( this->genHash(floor, 3) );
                bikeFreeCount.push(2);
                for(int slot = 4 ; slot <= slots ; ++slot)
                    parkedCars.push( this->genHash(floor, slot));
                carFreeCount.push(slots - 3);
            }


        }

    



// park_vehicle CAR KA-01-DB-1234 black
        string park(Vehicle vehicle){
            string ticket = null;

            int emptySlot = -1;
            int floor = -1;
            int slot = -1;


            if(vehicle.type == TRUCK){
                if(!parkedTrucks.empty()){
                    emptySlot = parkedTrucks.top(); 
                    parkedTrucks.pop();
                    vector<int> resolve = resolveHash(emptySlot);
                    floor = resolve[0];
                    slot = resolve[1];
                    truckFreeCount[floor]--;
                }
            }
            else if(vehicle.type == BIKE){
                if(!parkedBikes.empty()){
                    emptySlot = parkedBikes.top(); 
                    parkedBikes.pop();
                    vector<int> resolve = resolveHash(emptySlot);
                    floor = resolve[0];
                    slot = resolve[1];
                    bikeFreeCount[floor]--;
                }
            }
            else if(vehicle.type ==CAR){
                if(!parkedCars.empty()){
                    emptySlot = parkedCars.top(); 
                    parkedCars.pop();
                    vector<int> resolve = resolveHash(emptySlot);
                    floor = resolve[0];
                    slot = resolve[1];
                    carFreeCount[floor]--;
                }
            }


            if(emptySlot != -1)
                return "Parking Lot Full";

            parkedSpots.insert(emptySlot);
            

            
            return 
                "Parked vehicle. Ticket ID: " +
                this->id + "_" + 
                to_string(floor) + "_" + 
                to_string(slot);   
        }

// unpark_vehicle PR1234_2_5
        void unpark(int floor, int slot){
            int hash = this->genHash(floor, slot);
            if(parkedSpots.find(hash) == parkedSpots.end()){
                cout << "Invalid Ticket\n";
                return;
            }
            parkedSpots.erase(hash);

            if(slot == 1){
                parkedTrucks.push(hash);
                truckFreeCount[floor]++;
            }
            else if(slot <= 3){
                parkedBikes.push(hash);
                bikeFreeCount[floor]++;
            }
            else{
                parkedCars.push(hash);
                carFreeCount[floor]++;
            } 
        }

// display free_count CAR
        void displayFreeCount(string type){
            if(type == TRUCK){
                for(int floor = 1 ; floor <= floors ; ++ floor)
                    cout << (
                        "No. of free slots for " + 
                        type + 
                        " on Floor " + 
                        to_string(floor) + 
                        ": " + 
                        to_string(truckFreeCount[floor]) + 
                        "\n");
            }
            if(type == BIKE){
                for(int floor = 1 ; floor <= floors ; ++ floor)
                    cout << (
                        "No. of free slots for " + 
                        type + 
                        " on Floor " + 
                        to_string(floor) + 
                        ": " + 
                        to_string(bikeFreeCount[floor]) + 
                        "\n");
            }
            if(type == CAR){
                for(int floor = 1 ; floor <= floors ; ++ floor)
                    cout << (
                        "No. of free slots for " + 
                        type + 
                        " on Floor " + 
                        to_string(floor) + 
                        ": " + 
                        to_string(carFreeCount[floor]) + 
                        "\n");
            }
        }

// display free_slots BIKE
        void displayFreeSlots(){

        }

// display occupied_slots CAR
        void dispalyOccupiedSlots(){

        }
};



int main(){
    #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    #endif
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    while(true){
        string input;
        cin >> input;
        vector<string> ins = splitOn(input, ' ');

        if(ins[0] == "exit"){
            exit(0);
        }
        else if(ins[0] == "create_parking_lot" ){

        }
        else if(ins[0] == "park_vehicle"){

        }
        else if(ins[0] == "unpark_vehicle"){

        }
        else if(ins[0] == "display"){
            if(ins[1] == "free_count"){

            }
            else if(ins[1] == "free_slots"){

            }
            else if(ins[1] == "occupied_slots"){

            }
        }


        

        
    }

    
    
    
    return 0;
}