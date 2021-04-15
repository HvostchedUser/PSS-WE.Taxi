#include <iostream>
#include <fstream>
#include <thread>
#include <math.h>
#include "database.cpp"
#include "clientside.cpp"
using namespace std;

int randRange(int min, int max){
    return min + (rand() % static_cast<int>(max - min + 1));

}
string namegen(bool fem){
    string res="";
    string mid[]={"gra","am","ni","cho","va","nad","si","vil","mi","sa","ik","shon", "ri","li","sa","ma","da","ad","re","su","vo","tyo","sla"};
    string endFem[]={"na","va","sha","rtha","ka","tya","ya","ad","el"};
    string endMa[]={"im","sim","kal","al","ed","ey","an","ok","chek","ad"};
    int randval=randRange(1,3);
    for(int i=0;i<randval;i++){
        res+=mid[randRange(0,22)];
    }
    if(fem){
        res+=endFem[randRange(0,8)];
    }else{
        res+=endMa[randRange(0,9)];
    }
    return res;
}
string surnamegen(bool fem){
    string res="";
    string mid[]={"gra","am","ni","cho","va","nad","si","vil","mi","sa","ki","shon", "ri","li","sa","ma","da","ad","re","su","vo","tyo","sla"};
    string endFem[]={"ova","ivech","cheva","anth","al","ets","ya","enko","on","and","oux"};
    string endMa[]={"ov","ivech","chev","anth","al","ets","ya","enko","er","and","oux"};
    
    int randval=randRange(1,3);
    for(int i=0;i<randval;i++){
        res+=mid[randRange(0,22)];
    }
    if(fem){
        res+=endFem[randRange(0,10)];
    }else{
        res+=endMa[randRange(0,10)];
    }
    
    return res;
}
string modelgen(){
    string res="";
    string mid[]={"mit","su","bi","su","ba","nis", "de","lo","ri","o", "volks", "mer","ce", "wa","la","ci","tro","peu","ge","au"};
    string end[]={"shi","ru","san","an","pel","des","gen","da","en","ot","di"};
    string beg[]={"white ", "dark ", "black ","gray ","dirty ", "blue ", "golden ","green ","silver ",""};
    string desc[]={"awful ","dirty ", "very fast ","extremely beautiful ","off-road ","racing ","limousine ","old ","rusty ","broken ","three-wheeled ", "rocket-powered ",""};
    
    int randval=randRange(1,3);
    for(int i=0;i<randval;i++){
        res+=mid[randRange(0,19)];
    }
    res=desc[randRange(0,12)]+beg[randRange(0,9)]+res;
    res+=end[randRange(0,10)];
    
    
    return res;
}
string addrgen(){
    string res="";
    string mid[]={"os","a","ri", "va","ne", "mu", "rat", "mov", "ho", "ver","chi","na","ka", "lu", "mi","ke", "ho","che","lin",""};
    string preend[]={"chev","sk","","ov","lin","berg","vo","er"};
    string end[]={" village", " street", " town"," city","'s blvrd", " ave.", " line"," mall"," park"," building"," station"};
    
    int randval=randRange(1,5);
    for(int i=0;i<randval;i++){
        res+=mid[randRange(0,19)];
    }
    res+=preend[randRange(0,8)];
    res+=end[randRange(0,11)];
    
    
    return res;
}
void sleep(int millisv){
        std::this_thread::sleep_for(std::chrono::milliseconds(millisv));
}
bool file_exists (const std::string& name) {
    ifstream f(name.c_str());
    return f.good();
}
void log_s(string s){
    cout<<"     >> "<<s<<endl;
    sleep(200);
}
void log_gen(string s){
    cout<<"     || "<<s<<endl;
    sleep(200);
}
void log_sub(string s){
    cout<<"             "<<s<<endl;
    sleep(10);
}
void log_sim(string s){
    cout<<"     << "<<s<<endl;
    sleep(200);
}
double dist(string a, string b){
    return fabs((int)a.size()-(int)b.size());
}
void write_data(Data data,string prefix, Route coordinates){
    data.put(prefix+"_destination",coordinates.destination);
    data.put(prefix+"_origin",coordinates.origin);
    data.put(prefix+"_passenger",coordinates.passenger);
    data.put(prefix+"_distance",to_string(coordinates.distance));
    data.put(prefix+"_position",to_string(coordinates.position));
}
void write_data(Data data,string prefix, vector<Route> vec){
    for(int i=0;i<vec.size();i++){
        write_data(data,prefix+"_"+to_string(i),vec[i]);
    }
}
Route get_data(Data data,string prefix){
    Route o;
    o.destination=data.get(prefix+"_destination");
    o.origin=data.get(prefix+"_origin");
    o.passenger=data.get(prefix+"_passenger");
    o.distance=stod(data.get(prefix+"_distance"));
    o.position=stod(data.get(prefix+"_position"));
    //cout<<o.distance<<o.origin<<o.destination<<o.position<<endl;
    return o;
}
vector<Route> get_data_multi_order(Data data,string prefix, int size){
    vector<Route> o;
    for(int i=0;i<size;i++){
        get_data(data, prefix+"_"+to_string(i));
    }
    return o;
}
int main(int argc, char **argv) {
    unsigned int time_ui = unsigned (int( time(NULL)) );
    srand( time_ui );
    vector<string> dest_points;
    vector<Driver> drivers;
    vector<Passenger> clients;
    vector<string> car_models;
    vector<string> cars;
    
    Data data;
    if(!file_exists("main.txt")){
        log_s("No data found. Generating new world...");
        log_gen("Names of destination points:");
        int lenv=randRange(10,50);
        for(int i=0;i<lenv;i++){
            string temp=addrgen();
            log_sub(temp);
            dest_points.push_back(temp);
        }
        
        log_gen("Drivers:");
        lenv=randRange(5,30);
        for(int i=0;i<lenv;i++){
            bool g=randRange(0,1);
            string temp=namegen(g)+" "+surnamegen(g);
            string tempm=modelgen();
            log_sub(temp+" with "+tempm);
            Driver r;
            Car c;
            c.model=tempm;
            int type=rand()%5;
            c.type="Economy";
            if(type==0){
            }else if(type==1){
                c.type="Comfort";
            }else if(type==2){
                c.type="ComfortPlus";
            }else if(type==3){
                c.type="Business";
            }
            Route o;
            o.origin=dest_points[randRange(0,dest_points.size()-1)];
            o.destination=dest_points[randRange(0,dest_points.size()-1)];
            o.distance=dist(o.origin,o.destination);
            if(o.distance==0){
                o.distance=1;
                o.position=0;
            }else{
                o.position=rand()%(int)(o.distance);
            }
            c.coordinates=o;
            r.name=temp;
            r.car=c;
            r.rating=randRange(1,10);
            r.status="free";
            drivers.push_back(r);
        }
        
        log_gen("Client names:");
        lenv=randRange(10,50);
        for(int i=0;i<lenv;i++){
            bool g=randRange(0,1);
            string temp=namegen(g)+" "+surnamegen(g);
            log_sub(temp);
            Passenger p;
            p.name=temp;
            vector<Card> pm;
            int tpm=randRange(1,4);
            for(int j=0;j<tpm;j++){
                Card dc;
                dc.money=randRange(0,10000);
                pm.push_back(dc);
            }
            p.paymentMethods=pm;
            p.rating=randRange(1,10);
            int tempran=randRange(0,10);
            for(int j=0;j<tempran;j++){
                p.pinnedAddresses.push_back(dest_points[randRange(0,dest_points.size()-1)]);
            }
            clients.push_back(p);
        }
        
    }else{
        log_gen("Names of destination points:");
        int lenv=atoi(data.get("places").c_str());
        for(int i=0;i<lenv;i++){
            string temp=data.get("place_"+to_string(i));
            log_sub(temp);
            dest_points.push_back(temp);
        }
        
        log_gen("Drivers:");
        lenv=atoi(data.get("drivers").c_str());
        for(int i=0;i<lenv;i++){
            string temp=data.get("driver_name_"+to_string(i));
            string tempm=data.get("driver_car_model_"+to_string(i));
            log_sub(temp+" with "+tempm);
            Driver r;
            Car c;
            c.model=tempm;
            int type=rand()%5;
            c.type=data.get("driver_car_type_"+to_string(i));
            c.coordinates=get_data(data, "driver_car_coordinates_"+to_string(i));
            r.available=get_data_multi_order(data,"driver_available_"+to_string(i),stoi(data.get("driver_availables_"+to_string(i))));
            r.name=temp;
            r.car=c;
            r.rating=stoi(data.get("driver_rating_"+to_string(i)));
            r.status=data.get("driver_status_"+to_string(i));
            drivers.push_back(r);
        }
        
        log_gen("Client names:");
        lenv=atoi(data.get("clients").c_str());
        for(int i=0;i<lenv;i++){
            string temp=data.get("passenger_name_"+to_string(i));
            log_sub(temp);
            Passenger p;
            p.name=temp;
            vector<Card> pm;
            int tpm=stoi(data.get("passenger_payment_methods_"+to_string(i)));
            for(int j=0;j<tpm;j++){
                Card dc;
                dc.money=stoi(data.get("passenger_card_"+to_string(i)+"_"+to_string(j)));
                pm.push_back(dc);
            }
            p.paymentMethods=pm;
            p.rating=stoi(data.get("passenger_rating_"+to_string(i)));
            int tempran=stoi(data.get("passenger_pinneds_"+to_string(i)));
            for(int j=0;j<tempran;j++){
                p.pinnedAddresses.push_back(data.get("passenger_pinned_"+to_string(i)+"_"+to_string(j)));
            }
            clients.push_back(p);
        }
        
    }
    log_sim("Simulation begins. To enter as a passenger, write passenger's name.");
    log_sim("To login as a passenger, write passenger's name.");
    log_sim("To login as a driver, write driver's name.");
    log_sim("To make a new step of simulation, just press enter");
    while(true){
        data.put("places",to_string(dest_points.size()));
        data.put("drivers",to_string(drivers.size()));
        data.put("clients",to_string(clients.size()));
        int iterd=0;
        for(string d:dest_points){
            data.put("place_"+to_string(iterd),d);
            iterd++;
        }
        iterd=0;
        for(Driver d:drivers){
            data.put("driver_name_"+to_string(iterd),d.name);
            data.put("driver_rating_"+to_string(iterd),to_string(d.rating));
            data.put("driver_status_"+to_string(iterd),d.status);
            data.put("driver_historys_"+to_string(iterd),to_string(d.orderHistory.size()));
            write_data(data,"driver_history_"+to_string(iterd),d.orderHistory);
            data.put("driver_availables_"+to_string(iterd),to_string(d.available.size()));
            write_data(data,"driver_available_"+to_string(iterd),d.available);
            data.put("driver_car_model_"+to_string(iterd),d.car.model);
            data.put("driver_car_type_"+to_string(iterd),d.car.type);
            write_data(data,"driver_car_coordinates_"+to_string(iterd), d.car.coordinates);
            iterd++;
        }
        iterd=0;
        for(Passenger p:clients){
            data.put("passenger_name_"+to_string(iterd),p.name);
            data.put("passenger_rating_"+to_string(iterd),to_string(p.rating));
            data.put("passenger_payment_methods_"+to_string(iterd),to_string(p.paymentMethods.size()));
            int subitd=0;
            for(Card c:p.paymentMethods){
                data.put("passenger_card_"+to_string(iterd)+"_"+to_string(subitd),to_string(c.money));
                subitd+=1;
            }
            data.put("passenger_historys_"+to_string(iterd),to_string(p.orderHistory.size()));
            write_data(data,"passenger_history_"+to_string(iterd),p.orderHistory);
            subitd=0;
            data.put("passenger_pinneds_"+to_string(iterd),to_string(p.pinnedAddresses.size()));
            for(string s:p.pinnedAddresses){
                data.put("passenger_pinned_"+to_string(iterd)+"_"+to_string(subitd),s);
                subitd+=1;
            }
            iterd++;
        }
        
        
        string input;
        getline(cin, input);
        if(input.length()<2){
            log_sub("step");
            for(int i=0;i<drivers.size();i++){
                drivers[i].car.coordinates.position=1+drivers[i].car.coordinates.position;
                if(drivers[i].car.coordinates.position>=drivers[i].car.coordinates.distance){
                    log_sub("DRIVER");
                    
                    log_sub(drivers[i].name);
                    
                    log_sub("WITH "+drivers[i].car.type+" CAR");
                    
                    log_sub(drivers[i].car.model);
                    
                    log_sub("HAS REACHED");
                    
                    log_sub(drivers[i].car.coordinates.destination);
                    log_sub("AND IS NOW GOING TO");
                    
                    drivers[i].car.coordinates.origin=drivers[i].car.coordinates.destination;
                    drivers[i].car.coordinates.destination=dest_points[randRange(0,dest_points.size()-1)];
                    if(drivers[i].status=="working"){
                        drivers[i].rating=(drivers[i].rating*9+randRange(0,10))/10;
                    }
                    log_sub("RATING:");
                    log_sub(to_string(drivers[i].rating));
                    drivers[i].status="free";
                    drivers[i].car.coordinates.passenger="";
                    
                    log_sub(drivers[i].car.coordinates.destination);
                    
                    drivers[i].car.coordinates.position=0;
                    drivers[i].car.coordinates.distance=dist(drivers[i].car.coordinates.origin,drivers[i].car.coordinates.destination);
                    log_sub("DRIVER IS");
                    log_sub(drivers[i].status);
                    
                    log_sub("");
                }
            }
        }else{
            for (int di=0;di<drivers.size();di++){
                Driver d=drivers[di];
                if(input==d.name){
                    log_s("Welcome to the driver console!");
                    log_s("Prepairing the list of available routes...");
                    DriverGateway dg;
                    dg.toAccept=d.available;
                    dg.drid=di;
                    
                    
                    if(dg.toAccept.size()==0){
                        log_s("Currently you don't have any work!");
                    }else{
                        if(d.status=="free"){
                            for(Route r:dg.toAccept){
                                log_sub("You have a route!");
                                log_sub(r.origin+"->"+r.destination);
                                log_sub("Distance:");
                                log_sub(to_string(r.distance));
                                log_sub("Passenger:");
                                log_sub(r.passenger);
                                log_sub("y/n?");
                                getline(cin, input);
                                if(input=="y"){
                                    drivers[di].car.coordinates=r;
                                    drivers[di].status="working";
                                    drivers[di].available.clear();
                                    log_sub("Route accepted!");
                                    break;
                                }
                            }
                        }else{
                            log_s("You are following the route already!");
                        }
                    }
                    log_s("Finishing... Bye");
                    
                }
            }
            for (int di=0;di<clients.size();di++){
                Passenger cl=clients[di];
                if(cl.name==input){
                    PassengerGateway pg;
                    pg.paymentMethods=cl.paymentMethods;
                    pg.psid=di;
                    log_s("Hello! We can drive you from one string to another!");
                    log_s("Where are you?");
                    string from;
                    getline(cin, from);
                    log_s("Where do you want to go?");
                    string to;
                    getline(cin, to);
                    log_s("Price:");
                    int price=dist(from,to)*10;
                    log_s(to_string(price));
                    log_s("Choose your payment method");
                    for(int p=0;p<pg.paymentMethods.size()+1;p++){
                        if(p>=pg.paymentMethods.size())p=0;
                        log_s("#"+to_string(p)+": "+to_string(pg.paymentMethods[p].money)+"$");
                        log_s("y/n/close?");
                        getline(cin, input);
                        if(input=="y"){
                            if(pg.paymentMethods[p].money>price){
                                pg.paymentMethods[p].money-=price;
                                log_s("Enjoy your ride! Waiting for a car.");
                                for(int dim=0;dim<drivers.size();dim++){
                                    Route n;
                                    n.destination=to;
                                    n.distance=price/10;
                                    n.position=0;
                                    n.origin=from;
                                    n.passenger=clients[pg.psid].name;
                                    drivers[dim].available.push_back(n);
                                }
                                break;
                            }else{
                                log_s("Not enough money =(");
                            }
                        }
                        if(input=="close"){
                            break;
                        }
                    }
                }
                
            }
        }
    }
    return 0;
}
