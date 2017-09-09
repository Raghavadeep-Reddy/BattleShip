#include "Game.h"
#include "Board.h"
#include "Player.h"
#include "globals.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <cctype>
#include <vector>


using namespace std;

class GameImpl
{
public:
    GameImpl(int nRows, int nCols);
    int rows() const;
    int cols() const;
    bool isValid(Point p) const;
    Point randomPoint() const;
    bool addShip(int length, char symbol, string name);
    int nShips() const;
    int shipLength(int shipId) const;
    char shipSymbol(int shipId) const;
    string shipName(int shipId) const; //unique
    Player* play(Player* p1, Player* p2, Board& b1, Board& b2, bool shouldPause);
    
  //  int shipID()const;
    //YOU MAY ADD MEMBERS EVEN PUBLIC ONES WOAH lol
    //should i make a ship accessor here, and also a ship setter?
    ~GameImpl();
    //void destroyShip(int shipId);

private:

    
    int mRows;
    int mCols;
    //i think a ship is technically a struct, that contains a length,symbol,and name, and is given an id to keep track of. also need to allocate memory for it, so if i still have ships in the end, i have to deallocate them. is this a linked list of ships then?
    //need 2 boards later.
    
    //shoudl a SHIP HAVE A POINT?
    
    //thats also why i think, technically , a struct is enough to handle the ships.
    class Ship
    {
    public:
        Ship(int mlength, char msymbol, std::string mname):sName(mname),sLength(mlength),sSymbol(msymbol)
        {
            if(mlength<0)
            {
                isValid=false;
            }
            else
            {
                isValid=true;
            }
        }
        string getName()const {return sName;}
        int getsID()const {return sID;}
        int getsLength()const {return sLength;}
        char getsSymbol()const {return sSymbol;}
        bool getisValid()const {return isValid;}
        void setId(int someID){sID=someID;}
    private: //check for valid/invalid as well in the ship class...
        string sName;
        int sID;
        int sLength;
        char sSymbol;
        bool isValid;
    };
    
   
    //you can actually create any length ships, the ones below were literally just for lols and practice, though any type of ship can be created at any time. its not like aircraft carrier, battleship, destroyer etc, you cna create w/e
    std::vector <Ship  > ships; //ship pointers.
    
    //a game actually has 2 boards?
 
    
    
};


GameImpl::~GameImpl()
{
}

void waitForEnter()
{
    cout << "Press enter to continue: ";
    cin.ignore(10000, '\n');
}

GameImpl::GameImpl(int nRows, int nCols)
:mRows(nRows),mCols(nCols) //i think its a board construction...
{
    // This compiles but may not be correct
}

int GameImpl::rows() const
{
    return mRows; 
}

int GameImpl::cols() const
{
    return mCols;
}

bool GameImpl::isValid(Point p) const
{
    return p.r >= 0  &&  p.r < rows()  &&  p.c >= 0  &&  p.c < cols(); //probs correct.
}

Point GameImpl::randomPoint() const
{
    return Point(randInt(rows()), randInt(cols()));
}

bool GameImpl::addShip(int length, char symbol, string name) //watch how i add ships here for board place ship.
{
    //int n=0; //how about hsip id becomes index of vector of it.
    //GameImpl::addShip(int length, char symbol, string name)
    //Add a ship type to your ship type collection
    //Argument checks, like “can the ship fit on the board?” are handled for you in Game::addShip(...)
   // cout<<"ADDING SHIP"<<endl;
    //bool somecondition=true; //going to have to change this later
    //if(somecondition)
    //{
        Ship newShip= Ship(length,symbol,name); //if newShip->isValid()
        if(newShip.getisValid())
        {
            ships.push_back(newShip); //right now im assuming its all good;
            int c=0;
           // cout<<"ADDING SHIP"<<endl;

            while(ships[c].getName()!=newShip.getName())
            {
                c++;
            }
            newShip.setId(c); //should give us the index as the shipId.
            return true;
        }
        else
        {
            return false;
        }
    //}
    return false;  // This happens if unable to add the ship due to
}
/*
void GameImpl::destroyShip(int shipId)
{
    //delete(ships[shipId]);
}
 */

int GameImpl::nShips() const
{
    int c=0;
    for(int p=0;p<ships.size();p++)
    {
        c++;
    }
    return c;
    // This compiles but may not be correct
}

int GameImpl::shipLength(int shipId) const
{
    return ships[shipId].getsLength();  // This compiles but may not be correct
}

char GameImpl::shipSymbol(int shipId) const
{
    return ships[shipId].getsSymbol();  // This compiles but may not be correct
}

string GameImpl::shipName(int shipId) const
{
    return ships[shipId].getName();  // This compiles but may not be correct
}

Player* GameImpl::play(Player* p1, Player* p2, Board& b1, Board& b2, bool shouldPause)
{//some invariants i think ill need to keep track of is also to deallocate the winners ships as well, seen by and controlled by the board.
    
    
    
    // This compiles but may not be correct   The play function must do the following:
    /*1. It creates two Board objects, one for each of the players. i assume this is supplied and good.
        2. It calls the placeShips function of each player to place the ships on their
        respective board. It is possible that the placeShips function may fail to place the
        ships in some instances (e.g., if the game parameters are such that there is no
                                 configuration of ships that will fit, or if a MediocrePlayer is unable to place all of
                                 the ships because of blocked squares). If a player's placeShips function returns
        false, your play function must return nullptr.
        3. Once both players have successfully placed their ships, game play starts.
        4. Until one of the players wins the game:
        a. Display the second player's board (since the first player will be attacking
        that board). If the first player is human, do not show undamaged segments
            on the opponent's board, since that would be cheating. If the first player is
            not human, then show the entire opponent's board, since we're just an
            onlooker to what the computer player will decide for itself.
                b. Make the first player's attack.
                c. Display the result of the attack.
                d. Repeat these steps with the roles of the first and second player reversed.
                5. If the losing player is human, display the winner's board, showing everything.
                You can't go wrong by having your play function conduct the game the way it does in our
                sample program.
    */
    Player * answer=nullptr;
    //CREATE A NEW GAME? WTF?
    
  
    
    if(!(p1->placeShips(b1))) //should also place both p1 and p2 ships assuming those are implemented right.
    {
        return nullptr;
    }
    if(!(p2->placeShips(b2)))
    {
        return nullptr;
    }
    //bool shouldPause=true; //this is to tweak later if im doing part 3 for the no pauses. jk its already dealt w/ and defaulted to true, so its my fault in the impl
    
    //before displaying the press enter to continue, it already displayed the board for both npcs, as well as one guy shooting the otehr guy.
   
    bool validShot=true;
    bool sHit=true;
    bool sDestroyed=true;
    int shID;
    
    int p1shipCount=p1->game().nShips();
    int p2shipCount=p2->game().nShips();
    while(b2.allShipsDestroyed()==false&&b1.allShipsDestroyed()==false) //while their ships are not at 0, the game goes on. should be same as if the alldestroyed conditions is true
    {
    
      
       // cout<<"ENTERING DISPLAY PORTION OF PLAY"<<endl;
            //first player attacks first, display 2nd player board  a)
        //so basically, display the board for p2 first, then display p1 attacking p2 board result.
       cout<<p1->name()<<"'s turn. Board for "<<p2->name()<<": "<<endl;
        b2.display(p1->isHuman()); //figure out what shotsonly means later. might have something to do w/ if p1 is human. if p1 is human, then p2's undamaged segment board is shown, else p2's whole board is shown
        
            //b)
        Point p1attackingp2=p1->recommendAttack(); //returns a point, created by p1, that p2 must use.
        
        
        
        if(b2.attack(p1attackingp2, sHit, sDestroyed, shID ))
        {
        //then display the attack.
        //assume it missed for now, but will modify after boolean.
            if(!sHit)
            {
                cout<<p1->name()<<" attacked "<<"("<<p1attackingp2.r<<","<<p1attackingp2.c<<")"<<" and missed, resulting in: "<<endl;
            }
            else
            {
            //also check if shot killed a boat.
                if(sDestroyed)
                {
                    cout<<p1->name()<<" attacked "<<"("<<p1attackingp2.r<<","<<p1attackingp2.c<<")"<<" and destroyed the "<<p2->game().shipName(shID)<<", resulting in: "<<endl;
                //actually we don't want to mess with dallocating any ships until the end, but we should just notify when the ship is destroyed. do we use a counter then to count up how many ships destroyed then? i think thats ok and easier.
                    p2shipCount--;
                //p2->game().destroyShip(shID);
                    
                    if(p2shipCount==0)
                    {
                        b2.display(p1->isHuman());

                        break;
                    }
                }
                else
                {
                    cout<<p1->name()<<" attacked "<<"("<<p1attackingp2.r<<","<<p1attackingp2.c<<")"<<" and hit something, resulting in: "<<endl;
                }
            }
            p1->recordAttackResult(p1attackingp2, validShot, sHit, sDestroyed, shID);//what are validShot, shotHit, shipDestroyed?
            p2->recordAttackByOpponent(p1attackingp2);


        }
        
        
        
        else
        {
            cout<<p1->name()<<" wasted a shot at " <<"("<<p1attackingp2.r<<","<<p1attackingp2.c<<")"<<endl;

        }
        b2.display(p1->isHuman());
        
        if(p1->isHuman())
        {
            if(shouldPause)
            {
                cout<<"Press enter to continue: ";
                cin.ignore(10000,'\n');
                cin.ignore(10000,'\n');
            }
        }
        else
        {
            if(shouldPause)
            {
                cout<<"Press enter to continue: ";
                cin.ignore(10000,'\n');
            }
        }
        
        cout<<endl;
        cout<<p2->name()<<"'s turn. Board for "<<p1->name()<<": "<<endl;

        b1.display(p2->isHuman());
        
        Point p2attackingp1=p2->recommendAttack(); //returns a point, created by p2, that p1 must use.
        if(b1.attack(p2attackingp1, sHit, sDestroyed, shID ))//if true, assume it has landed a shot.
        {  //assume it missed for now, but will modify after boolean.
            if(!sHit)
            {
                cout<<p2->name()<<" attacked "<<"("<<p2attackingp1.r<<","<<p2attackingp1.c<<")"<<" and missed, resulting in: "<<endl;
             //something about the coordinates are over 1000 or non existent.
            }
            else
            {
                if(sDestroyed)
                {
                    cout<<p2->name()<<" attacked "<<"("<<p2attackingp1.r<<","<<p2attackingp1.c<<")"<<" and destroyed the "<<p1->game().shipName(shID)<<", resulting in: "<<endl;
//actually we don't want to mess with dallocating any ships until the end, but we should just notify when the ship is destroyed. do we use a counter then to count up how many ships destroyed then? i think thats ok and easier.
                    p1shipCount--;
                
                    if(p1shipCount==0)
                    {
                        b1.display(p2->isHuman());
                        break;
                    }
                }
                else
                {
                    //also check if shot killed a boat.
                    cout<<p2->name()<<" attacked "<<"("<<p2attackingp1.r<<","<<p2attackingp1.c<<")"<<" and hit something, resulting in: "<<endl;
                }
            }
            p2->recordAttackResult(p2attackingp1, validShot, sHit, sDestroyed, shID);//what are validShot, shotHit, shipDestroyed?
            p1->recordAttackByOpponent(p2attackingp1);


        }
        else
        {
            cout<<p2->name()<<" wasted a shot at " <<"("<<p2attackingp1.r<<","<<p2attackingp1.c<<")"<<endl;
        }
        
        b1.display(p2->isHuman());
        if(p2->isHuman())
        {
            if(shouldPause)
            {
                cout<<"Press enter to continue: ";
                cin.ignore(10000,'\n');
                cin.ignore(10000,'\n');
           //  for some reason this is needed for a human player. 2 pauses???
            }
        }
        else
        {
            if(shouldPause)
            {
                cout<<"Press enter to continue: ";
                cin.ignore(10000,'\n');
              //  cin.ignore(10000,'\n');
                //  for some reason this is needed for a human player. 2 pauses???
            }
        }
 
    }
    
    //win condition
   // cout<<"WIN CONDITON TIME"<<endl;
    if(p2shipCount==0&&p2->isHuman()&&p1shipCount>0) //clear winner is non human and p1, display p1 board
    {
        //display winner's board.
       b1.display(false);
        answer=p1; //point to the fking winner
        
        cout<<p1->name()<<" wins!"<<endl;
    }
    if(p1shipCount==0&&p1->isHuman()&&p2shipCount>0) //clear winner is non human and is p2
    {
        //display winner's board.
        b2.display(false);
        answer=p2; //point to the fking winner.
        cout<<p2->name()<<" wins!"<<endl;

    }
    if(p1->isHuman()&&p2->isHuman()&&p2shipCount==0&&p1shipCount>0)
    {
        //both are human, but p1 is the winner
        b1.display(false);
    }
    if(p1->isHuman()&&p2->isHuman()&&p1shipCount==0&&p2shipCount>0)
    {
        //both are human, but p2 is the winner
        b2.display(false);
    }
    if(p1shipCount==0&&p2shipCount>0) //if 2 cpus, p2 wins? doesnt matter who is what actually at this point, as longa s ur a human and losing just do above, else ignore that condition and just point to winner when it happens. i dont have to print my own board for the loser if the loser is a non human.
    {
       // b2.display(false);
        answer=p2;
        cout<<p2->name()<<" wins!"<<endl;

    }
    if(p2shipCount==0&&p1shipCount>0) //if 2 cpus, p1 wins?
    {
        //b1.display(false);
        answer=p1;
        cout<<p1->name()<<" wins!"<<endl;

    }
    return answer;
    
}

//******************** Game functions *******************************

// These functions for the most part simply delegate to GameImpl's functions.
// You probably don't want to change any of the code from this point down.

Game::Game(int nRows, int nCols)
{
    if (nRows < 1  ||  nRows > MAXROWS)
    {
        cout << "Number of rows must be >= 1 and <= " << MAXROWS << endl;
        exit(1);
    }
    if (nCols < 1  ||  nCols > MAXCOLS)
    {
        cout << "Number of columns must be >= 1 and <= " << MAXCOLS << endl;
        exit(1);
    }
    m_impl = new GameImpl(nRows, nCols); //before i pass into my constructor basically, above already checks for me if i have bad input or invalid number of row cols.
}

Game::~Game()
{
    delete m_impl;
}

int Game::rows() const
{
    return m_impl->rows();
}

int Game::cols() const
{
    return m_impl->cols();
}

bool Game::isValid(Point p) const
{
    return m_impl->isValid(p);
}

Point Game::randomPoint() const
{
    return m_impl->randomPoint();
}

bool Game::addShip(int length, char symbol, string name)
{
    //i believe the condiitons for isValid is all already checked here tbh, so I don't have to worry about throwing false above and checking error bad length etc.
    if (length < 1)
    {
        cout << "Bad ship length " << length << "; it must be >= 1" << endl;
        return false;
    }
    if (length > rows()  &&  length > cols())
    {
        cout << "Bad ship length " << length << "; it won't fit on the board"
        << endl;
        return false;
    }
    if (!isascii(symbol)  ||  !isprint(symbol))
    {
        cout << "Unprintable character with decimal value " << symbol
        << " must not be used as a ship symbol" << endl;
        return false;
    }
    if (symbol == 'X'  ||  symbol == '.'  ||  symbol == 'o')
    {
        cout << "Character " << symbol << " must not be used as a ship symbol"
        << endl;
        return false;
    }
    int totalOfLengths = 0;
    for (int s = 0; s < nShips(); s++)
    {
        totalOfLengths += shipLength(s);
        if (shipSymbol(s) == symbol)
        {
            cout << "Ship symbol " << symbol
            << " must not be used for more than one ship" << endl;
            return false;
        }
    }
    if (totalOfLengths + length > rows() * cols())
    {
        cout << "Board is too small to fit all ships" << endl;
        return false;
    }
    return m_impl->addShip(length, symbol, name);
}

int Game::nShips() const
{
    return m_impl->nShips();
}

int Game::shipLength(int shipId) const
{
    assert(shipId >= 0  &&  shipId < nShips());
    return m_impl->shipLength(shipId);
}

char Game::shipSymbol(int shipId) const
{
    assert(shipId >= 0  &&  shipId < nShips());
    return m_impl->shipSymbol(shipId);
}

string Game::shipName(int shipId) const
{
    assert(shipId >= 0  &&  shipId < nShips());
    return m_impl->shipName(shipId);
}

Player* Game::play(Player* p1, Player* p2, bool shouldPause) //return a player pointer. a board constructed w/ a game pointer dereferenced.
{
    if (p1 == nullptr  ||  p2 == nullptr  ||  nShips() == 0)
        return nullptr;
    Board b1(*this); //so this is how i technically "create" my 2 boards for them to use.
    Board b2(*this); //both boards are housing the same game instance.
    return m_impl->play(p1, p2, b1, b2, shouldPause);
}

