#include <iostream> 
#include <vector>
#include <fstream>
#include <string>

/********************************************************************************
 *		TITLE: BasketBall Tournament
 *		author(s): Grady Walworth, Nadir Ali, Ethan Torres, Joseph Manahan
 *		adapted from: 
 *		other citations:
 *
 *		goal: Create a Basketball tournament that can contain up to 128 teams, all with unique players and scores.
 *      overview:
 *          Each player scores a different number of points each round, and those points are summed up per team, and then compared
 *          against the team they are playing. The winning teams move on to the next round, until there is only one team left.
 *
 *
 *
 ********************************************************************************/

using namespace std;


// abstract object, that other classes will inherit
class AbstractObject{
    
    public:
        int getTotalPoints();
        void setTotalPoints(int);
        string getName();
        void setName(string);
        int sumPoints;

    protected:
        string name;
        
};

string AbstractObject::getName(){
    return name;
}
void AbstractObject::setName(string myName){
    name = myName;
}

int AbstractObject::getTotalPoints(){
    return sumPoints;
}
void AbstractObject::setTotalPoints(int totalPoints){
    sumPoints = totalPoints;
}

// node class for linked list
class Node{
    public: 
        AbstractObject newObject;
        Node* next;
        Node* prev;

        Node(){
            next = nullptr;
            prev = nullptr;
        }

};



// linked list class
class LinkedList: public virtual AbstractObject{
    Node* head;
    public:
        LinkedList(){
            head = nullptr;
        }
        string teamName;

        // methods
        string getTeamName();

        void setTeamName(string);

        void addObjectToTail(AbstractObject);

        void printObjectList();

        void deleteNode(string);

        Node* returnHead();

};

string LinkedList::getTeamName(){
    return teamName;
}

void LinkedList::setTeamName(string newTeamName){
    teamName = newTeamName;
}

// method to add a node to the end of the linked list
void LinkedList::addObjectToTail(AbstractObject myObject){
    //Node* newNode = new Node(newObject);
    Node* newNode = new Node();
    newNode->newObject = myObject;

    //cout<<"Adding object to linked list"<< endl;
    //cout<<newNode->newObject.getName()<<": "<<newNode->newObject.getPoints()<<endl;

    if (head == nullptr){
        head = newNode;
        return;
    }
    Node* temp = head;
    while (temp->next != nullptr){
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->prev = temp;
}

// print linked list
void LinkedList::printObjectList(){
    Node* temp = head;
    //cout<<"List of remaining Teams: "<<endl;
    if (head == nullptr){
        cout << "List is empty!" << endl;
        return;
    }
    while (temp != nullptr){
        cout<<temp->newObject.getName()<<endl;
        //cout<< temp->newObject.getName()<<" scored: "<< temp->newObject.getPoints() << " points"<<endl;

        temp = temp->next;
    }
}

// method to delete a node from the linked list if it's found
void LinkedList::deleteNode(string nameOfTeamToDelete){
    Node* temp = head;

    if (head == nullptr){
        cout << "List is empty!" << endl;
        return;
    }

    // iterate through linked list
    while (temp != nullptr){

        // if we DO find the team
        if (nameOfTeamToDelete == temp->newObject.getName()){
            
            // if next node is NOT nullptr
            if (temp->next != nullptr){
                // set next node to point at prev node
                temp->next->prev = temp->prev;
            }

            // if previous node is NOT nullptr
            if (temp->prev != nullptr){
                // set prev node to point at next node
                temp->prev->next = temp->next;
            }
            // otherwise (if head node is being deleted)
            else{
                // make the second node the head node
                head = head->next;
            }
            //cout << "Your team was \'" << nameOfTeamToDelete << "\'. The team \'" << nameOfTeamToDelete << "\' has been deleted." << endl;
            delete(temp);
            return;
        }

        // if this word doesn't match, iterate to next node
        else{
            temp = temp->next;
        }
    } // end while loop

    // if we DON'T find the word
   cout << "Your team was \'" << nameOfTeamToDelete << "\'. We did not find your team. " << endl;
}

Node* LinkedList::returnHead(){
    return head;
}


// player class that inherits abstract object
class Player: public virtual AbstractObject{    
    protected: 
        int points;

    public:
        // variables
        string lastName;
        int playerNumber;
        void setPoints(int);
        int getPoints();

        // constructor methods
        Player(){
        }
        Player(string newName, int num){
            lastName = newName;
            name = newName;

            playerNumber = num;
            points = num;
            
        }
        Player(string newName){
            lastName = newName;
            name = newName;
            playerNumber = 0;
            points = 0;
        }

        // test print method
        void printNameAndNum();
};
void Player::setPoints(int newPoints){
    this->points = newPoints;
}
int Player::getPoints(){
    return points;
}
// test print method
void Player::printNameAndNum(){
    cout<<lastName <<": "<<playerNumber<<endl;
}


// Team class
// Team class that inherits abstract object
class Team: public virtual AbstractObject{
    //Node* head;
    private:
        string teamName;
        int teamPoints;
        Player players[5];

    //protected:
    //public:
        Player player1;
        Player player2;
        Player player3;
        Player player4;
        Player player5;

        LinkedList linkedPlayers;

    public:
        string getTeamName();
        void setTeamName(string);
        int sumTeamScores();
        void setPlayer(int, Player);
        Player getPlayer(int);

        Team(){

        }
};
string Team::getTeamName(){
    return teamName;
}
void Team::setTeamName(string newTeamName){
    teamName = newTeamName;
}

int Team::sumTeamScores(){
    int sum = 0;
    sum += player1.getPoints();
    sum += player2.getPoints();
    sum += player3.getPoints();
    sum += player4.getPoints();
    sum += player5.getPoints();
    sumPoints = sum;

    return sum;
}

void Team::setPlayer(int playerNum, Player playerToSet){
    if (playerNum == 0){
        player1 = playerToSet;
    }
    else if (playerNum == 1){
        player2 = playerToSet;
    }
    else if (playerNum == 2){
        player3 = playerToSet;
    }
    else if (playerNum == 3){
        player4 = playerToSet;
    }
    else if (playerNum == 4){
        player5 = playerToSet;
    }
    else{
        cout<<"DID NOT ENTER A NUMBER BETWEEN 0-4"<<endl;
    }
}
Player Team::getPlayer(int playerNum){
    if (playerNum == 0){
        return player1;
    }
    else if (playerNum == 1){
        return player2;
    }
    else if (playerNum == 2){
        return player3;
    }
    else if (playerNum == 3){
        return player4;
    }
    else{
        return player5;
    }
}





// League/Tournament Class
// League/Tournament class that inherits abstract object
class League: public virtual AbstractObject{
    private:
        LinkedList survivingTeams;
        vector<Team> finalTeams;
    public:
        League(){
        }
        void addTeamToLeague(Team);
        void printTeams();
        void playRound();
        Team getFinalTeam1();
        Team getFinalTeam2();
        void finalRound(Team, Team);
    
};
void League::addTeamToLeague(Team newTeam){
    survivingTeams.addObjectToTail(newTeam);

    // test
    finalTeams.push_back(newTeam);
}

void League::printTeams(){
    survivingTeams.printObjectList();
}
void League::playRound(){

    Node* tempNode = survivingTeams.returnHead();

    vector<string> deleteList;
    while (tempNode->next != nullptr){

        AbstractObject temp1 = tempNode->newObject;
        AbstractObject temp2 = tempNode->next->newObject;

        // if team1 wins (or they tie)
        if (temp1.sumPoints >= temp2.sumPoints){
            cout<<temp1.getName() << " scored " << temp1.sumPoints <<" points."<<endl;
            cout<<temp2.getName() << " scored " << temp2.sumPoints <<" points."<<endl;
            cout<<temp1.getName() << " wins!"<<endl;
            cout<<endl;
            deleteList.push_back(temp2.getName());
            if (tempNode->next->next == nullptr){
                break;
            }
            else{
                tempNode = tempNode->next->next;
            }
        }
        // if team2 wins
        else{
            cout<<temp1.getName() << " scored " << temp1.sumPoints <<" points."<<endl;
            cout<<temp2.getName() << " scored " << temp2.sumPoints <<" points."<<endl;
            cout<<temp2.getName() << " wins!"<<endl;
            cout<<endl;
            //survivingTeams.deleteNode(temp1.getName());

            deleteList.push_back(temp1.getName());
            if (tempNode->next->next == nullptr){
                break;
            }
            else{
                tempNode = tempNode->next->next;
            }
        }
    } // end while loop

    cout<<"Teams knocked out: "<<endl;
    for (int i = 0; i < deleteList.size(); i++){
        cout<<deleteList.at(i)<<endl;
    }

    for (int i = 0; i < finalTeams.size(); i++){
        for (int j = 0; j < deleteList.size(); j ++){
            if (finalTeams.at(i).getName() == deleteList.at(j)){
                //cout<<finalTeams.at(i).getName() << " erased from vector"<<endl;
                finalTeams.erase(finalTeams.begin() + i);
            }
        }
    }

    for (int i = 0; i < deleteList.size(); i++){
        survivingTeams.deleteNode(deleteList.at(i));
        //cout<<deleteList.at(i)<<endl;
    }
}
Team League::getFinalTeam1(){
    Team temp = finalTeams.at(0);
    return temp;
}
Team League::getFinalTeam2(){
    Team temp = finalTeams.at(1);
    return temp;
}


void League::finalRound(Team team1, Team team2){
    
    cout<<"Team: "<< team1.getName()<<endl;
    for (int i = 0; i < 5; i++){
        cout<< team1.getPlayer(i).getName() << " scored " << team1.getPlayer(i).getPoints() << " points"<<endl;
    }
    cout<<endl;
    cout<< team1.getName() << " scored " << team1.sumTeamScores() << " points total"<<endl;
    cout<<endl;
    cout<<endl;


    cout<<"Team: "<< team2.getName()<<endl;
    for (int i = 0; i < 5; i++){
        cout<< team2.getPlayer(i).getName() << " scored " << team2.getPlayer(i).getPoints() << " points"<<endl;
    }
    cout<<endl;
    cout<< team2.getName() << " scored " << team2.sumTeamScores() << " points total"<<endl;
    cout<<endl;
    cout<<endl;

    if (team1.sumTeamScores() >= team2.sumTeamScores()){
        cout<<team1.getName() <<" are the Champions!"<<endl;
    }
    else{
        cout<<team2.getName() <<" are the Champions!"<<endl;
    }

}







// main
int main(){

    srand((unsigned) time(0));
    cout<<endl;

    // import vector of 1000 player names
    ifstream newfile("lastNames.txt");
    vector<string> listOfNames;
    if (newfile.is_open()){
        string newString;
        while(getline(newfile, newString)){
            listOfNames.push_back(newString);
        }
        newfile.close();
    }

    // import vector of team names
    ifstream file("teamNames.txt");
    vector<string> listOfTeams;
    if (file.is_open()){
        string newString;
        while(getline(file, newString)){
            listOfTeams.push_back(newString);
        }
        file.close();
    }

    // create vector of 1000 random numbers, (between 1-1000)
    vector<int> listOfNums;
    for (int i = 0; i < 1000; i++){
        //srand((unsigned) time(NULL));
        //srand(time(0));
        listOfNums.push_back(rand()%1000);
    }
    // create vector of 1000 random scores, (between 5-20)
    vector<int> listOfScores;
    for (int i = 0; i < 1000; i++){
        listOfScores.push_back(5 + rand()%15);
    }


    int n;
    int x;
    bool validTournament = false;
    int numRounds = 0;

    cout<<"How many teams are in your basketball tournament?"<<endl;
    cout<<"(it must be a power of 2 (i.e. 2,4,8,16,32,64,etc and max of 128)"<<endl;
    while (validTournament == false){
        cout<<"Enter the number of teams: ";
        cin>>n;
        x = n;

        if ( (x > 0) && (x < 129) ){
            while (x % 2 == 0){
                x = x / 2;
                numRounds++;
            }
            if ( x == 1){
                cout<< n << " teams is a valid tournament"<<endl;
                cout<<endl;
                validTournament = true;
                break;
            }
            else{
                cout<< n << " is not a power of 2, please enter a number that is a power of 2 (i.e. 2,4,8,16,32,64, and max of 128) "<<endl;
            }
        }

        else {
            cout << "Enter a valid positive number" <<endl;
        }
    }
    cout<<"There will be " << numRounds << " rounds in the tournament"<<endl;
    cout<<endl;

    // count to iterate through listOfNames, listOfNums, and listOfScores
    int count = 0;



    // create the league
    League myLeague;

    // create n teams (using names from team Name txt file)
    Team teams[n];
    //for (int i = 0; i < n; i++)


    // create all the players for the teams (using names from player name txt file, and scores)
    Player players[n * 5];
    for (int i = 0; i < (n * 5); i++){
        players[i].setPoints(listOfScores.at(listOfNums.at(count)));
        players[i].setName(listOfNames.at(listOfNums.at(count)));
        count++;
    }

    // assign 5 players to each team using nested for loops (i and j)
    int playerCount = 0;
    // for loop to iterate through teams
    for (int i = 0; i < n; i++){
        teams[i].setName(listOfTeams.at(listOfNums.at(playerCount)));
        // for loop to iterate through players
        for (int j = 0; j < 5; j++){
            teams[i].setPlayer(j, players[playerCount]);
            playerCount++;
        }
        teams[i].setTotalPoints(teams[i].sumTeamScores());
    }

/*    // test print 
    cout<<"Team: " << teams[0].getName() <<endl;
    for (int i = 0; i < 5; i++){
        cout<< teams[0].getPlayer(i).getName() << " scored " << teams[0].getPlayer(i).getPoints() << " points"<<endl;
    }
    cout<<endl;
    cout<< teams[0].getName() << " scored " << teams[0].sumTeamScores() << " points total"<<endl;
*/


    // assign each team to the league
    for (int i = 0; i < n; i++){
        myLeague.addTeamToLeague(teams[i]);
    }

    // print names of teams in the tournament
    cout<<"Here are the teams in the tournament: "<<endl;
    myLeague.printTeams();

    for (int i = 0; i < numRounds - 1; i++){
        cout<<endl;
        cout<<endl;
        cout<<"Round "<< (i + 1) <<": "<<endl;
        cout<<endl;
        myLeague.playRound();
        cout<<endl;
        cout<<"List of Remaining Teams: "<<endl;
        myLeague.printTeams();
    }
    
    cout<<endl;
    cout<<"The Championship Game is here!"<<endl;
    //myLeague.printTeams();

    Team finalTeam1 = myLeague.getFinalTeam1();
    Team finalTeam2 = myLeague.getFinalTeam2();
    cout<<finalTeam1.getName()<<" vs. "<<finalTeam2.getName()<<endl;
    cout<<endl;
    myLeague.finalRound(finalTeam1, finalTeam2);

    cout<<endl;
    cout<<endl;

    return 0;
}