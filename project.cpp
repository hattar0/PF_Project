#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

void create(fstream &file, const char str[],int num){
    char spaces[] = "                              ";
    char buffer[100];
    cout << str;
    cin.getline(buffer,100);
    file << buffer;
    if(strcmp(str, "Enter  the time of the event(hh-mm-ss)") == 0){
        file << buffer << endl;
    }else{
        file.write(spaces, num - strlen(buffer));
    }
}

void createEvent(fstream &events){

    create(events, "Enter event name: ", 24);
    create(events, "Enter event type: ", 24);
    create(events, "Enter date of the event(dd-mm-yy):", 24);
    create(events, "Enter  the time of the event(hh-mm-ss)", 24);
    events << endl;

}

void registerParticipant(fstream &participant){
    
    
    char spaces[] = "                              ";
    
    int num=0;
    char c;

    
    if(participant.peek() == ifstream::traits_type::eof()){
        num = -1;
        participant.clear();
    }else{
        participant.seekg(-5, ios::end);

        for(int i=0; i<3; i++){
            participant.get(c);
            num *= 10;
            num += c - 48;
        }

        cout << num;
        participant.seekg(0);
        participant.clear();
    }

    create(participant, "Enter name: ", 24);
    create(participant, "Enter department: ", 30);
    create(participant, "Enter contact number: ", 27);
    create(participant, "Enter event name: ", 25);
    create(participant, "Enter Roll number: ", 31);
    create(participant, "Enter the time slot (Example: 02:00 - 04:00) ", 29);

    if(num == -1){
        participant << "TECHFEST-2025-";
        participant << "001";
    }else{
        participant << "TECHFEST-2025-";
        ++num;
        if(num < 10){
            participant << 0 << 0 << num;
        }else if(num < 100 && num >= 10){
            participant << 0 << num;
        }else if(num >= 100){
            participant << num;
        }
    }
    
   
    participant << endl;

}

void submitScores(int (*scores)[30], fstream &participant){

    participant.seekg(0);
    participant.clear();

    char compitition1[20]={'\0'};
    char compitition2[20]={'\0'};
    cout << "Which compititon do you want to add scores for?: ";
    cin >> compitition1 >> compitition2;

    char buffer[50];

    while(participant >> buffer){
        if(strcmp(buffer, compitition1) == 0){
            participant >> buffer >> buffer;
            cout << buffer << endl;
        }
    }

}



int main(){

    fstream events("events.txt",ios::in | ios::out | ios::app );
    fstream participants("participants.txt", ios::in| ios::out |  ios::app);

    char spaces[] = "                    ";

    if(events.peek() == ifstream::traits_type::eof()){
        events.clear();
        events << "Name" << spaces <<"Type"<< spaces << "Date" << spaces << "Time" << endl;
    }

    if(participants.peek() == ifstream::traits_type::eof()){
        participants.clear();
        participants << "Name"<< spaces << "Department" << spaces << "Contact" << spaces << "Event"  << spaces <<"Roll Number" << spaces <<  "Time Slot" << spaces <<"Participation ID" << endl;
    }


    // createEvent(events);
    // registerParticipant(participants);

    int scores[10][30];

    submitScores(scores, participants);


    return 0;
}