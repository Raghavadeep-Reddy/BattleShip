#include "Player.h"
#include "Board.h"
#include "Game.h"
#include "globals.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

//*********************************************************************
//  AwfulPlayer
//*********************************************************************

class AwfulPlayer : public Player
{
public:
    AwfulPlayer(string nm, const Game& g);
    virtual bool placeShips(Board& b);
    virtual Point recommendAttack();
    virtual void recordAttackResult(Point p, bool validShot, bool shotHit,
                                    bool shipDestroyed, int shipId);
    virtual void recordAttackByOpponent(Point p);
    
    virtual ~AwfulPlayer(){} //implement a v dtor.
private:
    Point m_lastCellAttacked;
};

AwfulPlayer::AwfulPlayer(string nm, const Game& g)
: Player(nm, g), m_lastCellAttacked(0, 0)
{}

bool AwfulPlayer::placeShips(Board& b)
{
    // Clustering ships is bad strategy
    for (int k = 0; k < game().nShips(); k++)
        if ( ! b.placeShip(Point(k,0), k, HORIZONTAL))
            return false;
    return true;
}

Point AwfulPlayer::recommendAttack() //returns a point
{
    if (m_lastCellAttacked.c > 0)
        m_lastCellAttacked.c--;
    else
    {
        m_lastCellAttacked.c = game().cols() - 1;
        if (m_lastCellAttacked.r > 0)
            m_lastCellAttacked.r--;
        else
            m_lastCellAttacked.r = game().rows() - 1;
    }
    return m_lastCellAttacked;
}

void AwfulPlayer::recordAttackResult(Point /* p */, bool /* validShot */,
                                     bool /* shotHit */, bool /* shipDestroyed */,
                                     int /* shipId */)
{
    // AwfulPlayer completely ignores the result of any attack
}

void AwfulPlayer::recordAttackByOpponent(Point /* p */)
{
    // AwfulPlayer completely ignores what the opponent does
}

//*********************************************************************
//  HumanPlayer
//*********************************************************************

bool getLineWithTwoIntegers(int& r, int& c)
{
    bool result(cin >> r >> c);
    if (!result)
        cin.clear();  // clear error state so can do more input operations
    cin.ignore(10000, '\n');
    return result;
}


class HumanPlayer : public Player
{
public:
    HumanPlayer(string nm, const Game& g);
    virtual bool isHuman()const;
    virtual bool placeShips(Board& b);
    virtual Point recommendAttack();
    virtual void recordAttackResult(Point p, bool validShot, bool shotHit,
                                    bool shipDestroyed, int shipId);
    virtual void recordAttackByOpponent(Point p);
    
    virtual ~HumanPlayer(){} //implement a v dtor.
private:
    Point m_lastCellAttacked;
};
bool HumanPlayer::isHuman()const
{
    return true;
}

HumanPlayer::HumanPlayer(string nm, const Game& g)
: Player(nm, g), m_lastCellAttacked(0, 0)
{}

bool HumanPlayer::placeShips(Board& b)
{
    // Clustering ships is bad strategy
    
   // b.display(true);
    //b.block();  //part 1, blocking and unblocking is working!

    
    cout<<name()<<" must place "<<game().nShips() <<" ships."<<endl;
    for (int k = 0; k < game().nShips(); k++)
    {
        b.display(false);

        cout<<"Enter h or v for direction of " << game().shipName(k) <<" (length " <<game().shipLength(k) <<"): ";
        string cinDirection;
        if(k!=0)
            cin.ignore(); //for some reason i need this for fluidity of spacing
        getline(cin,cinDirection);
        //cout<<cinDirection.size();
        Direction cinDirect=VERTICAL; //default to vertical
        if(cinDirection.size()>1||(cinDirection[0]!='v'&&cinDirection[0]!='h'))
        {
            bool condition=true;
            while(condition)
            {
                
                cout<<"Direction must be h or v"<<endl;
                cout<<"Enter h or v for direction of " << game().shipName(k) <<" (length " <<game().shipLength(k) <<"): ";
                cin>>cinDirection;
                if(cinDirection[0]=='v'&&cinDirection.size()==1)
                {
                    cinDirect=VERTICAL;
                    condition=false;
                }
                if(cinDirection[0]=='h'&&cinDirection.size()==1)
                {
                    cinDirect=HORIZONTAL;
                    condition=false;
                }
            }
        }
        else if(cinDirection[0]=='v')//horizontal
        {
            cinDirect=VERTICAL;
        }
       else if(cinDirection[0]=='h')
        {
            cinDirect=HORIZONTAL;
        }
        
      
        
       
        string coordinatesr,coordinatesc;
        int cinr=-1,cinc=-1;
        
        //cin>>coordinatesr;
        while(true)//not even an int
        {
            cout<<"Enter row and column of leftmost cell (e.g. 3 5): ";
            cin>>coordinatesr>>coordinatesc;
            stringstream myStreamr(coordinatesr); //seeems like also i only care about first 2 numbers.
            stringstream myStreamc(coordinatesc);
            if(myStreamr>>cinr&&myStreamc>>cinc)
            {
                break; //entered 1 good number
            }
            cout<<"You must enter two integers."<<endl;
        
            
        //2. i should also be looking at the board each time even including the beginning
        }
        
        while ( ! b.placeShip(Point(cinr,cinc), k,cinDirect))
        {
            //    cout<<"K VALUE IS " <<k<<endl;
            cout<<"The ship can not be placed there."<<endl;
            cout<<"Enter row and column of leftmost cell (e.g. 3 5): ";
            cin>>coordinatesr>>coordinatesc;
            stringstream myStreamr(coordinatesr); //seeems like also i only care about first 2 numbers.
            //  cin>>coordinates;
            stringstream myStreamc(coordinatesc);

            while(true)//not even an int
            {
                if(myStreamr>>cinr&&myStreamc>>cinc)
                {
                    break; //entered a good number
                }
                
                cout<<"You must enter two integers."<<endl;
                
                //2. i should also be looking at the board each time even including the beginning
            }

            //cout<<cinr<<" "<<cinc<<endl;
            //how to handle entering bad integers?
            
        }
    }
    b.display(false);


    return true;
}

Point HumanPlayer::recommendAttack() //returns a point

{
    Point PointToAttack;
    string coordinatesr,coordinatesc;
    int cinr=-1,cinc=-1;
    //cin>>coordinatesr;
    while(true)//not even an int
    {
        cout<<"Enter row and column of leftmost cell (e.g. 3 5): ";
        cin>>coordinatesr>>coordinatesc;
        stringstream myStreamr(coordinatesr); //seeems like also i only care about first 2 numbers.
        stringstream myStreamc(coordinatesc);
        if(myStreamr>>cinr&&myStreamc>>cinc)
        {
            break; //entered 2 good number
        }
        cout<<"You must enter two integers."<<endl;
        //2. i should also be looking at the board each time even including the beginning
    }
    if (cinr>game().rows()||cinc>game().cols()||cinc<0||cinr<0)
    {
        //    cout<<"K VALUE IS " <<k<<endl;
        m_lastCellAttacked.r=cinr;
        m_lastCellAttacked.c=cinc;
        //but its a bad one, guess just return it doesnt matter here.
    }
    else
    {
        m_lastCellAttacked.r=cinr;
        m_lastCellAttacked.c=cinc;
    }
    return m_lastCellAttacked;
}

void HumanPlayer::recordAttackResult(Point /* p */, bool /* validShot */,
                                     bool /* shotHit */, bool /* shipDestroyed */,
                                     int /* shipId */)
{
//humans dont need this
}

void HumanPlayer::recordAttackByOpponent(Point /* p */)
{
//humans dont need this
}

//*********************************************************************
//  MediocrePlayer
//*********************************************************************

// TODO:  You need to replace this with a real class declaration and
//        implementation.
//typedef AwfulPlayer MediocrePlayer;

class MediocrePlayer : public Player
{
public:
    MediocrePlayer(string nm, const Game& g);
    virtual bool placeShips(Board& b);
    virtual Point recommendAttack();
    virtual void recordAttackResult(Point p, bool validShot, bool shotHit,
                                    bool shipDestroyed, int shipId);
    virtual void recordAttackByOpponent(Point p);
    
    virtual ~MediocrePlayer(){} //implement a v dtor.
private:
    bool myRecursivePlacements(Board &b, bool &fiftyTries,int n,int position, int &count, int & numberofShipsPlaced);
    Point m_lastCellAttacked;
    //should i implement an orientation type that baiscally has an orientation and a point coordinate, and push those onto a vector of orientations? this way i can use that to check and make sure i dont attempt to keep placing stuff like that.
    vector<Point> myBadPoints; //each index corresponds to like the ID of a bad point and a bad direction?
    vector<Direction> myBadDirections;
    struct Orientation
    {
        Point myP;
        Direction myD;
        int myID;
    };
    //the provisional points
    vector<Point> myProvisionalPoints; //each index corresponds to like the ID of a bad point and a bad direction?
    vector<Direction> myProvisoinalDirections;
    //1. i need a way to place all the ships first. then check if i can rearrange if it fails, each time when i need to rearrange, ill pop all the ships and i guess, change orientation then. so for now, or initial attempt is to just try to fit everything horizontally.
    vector<vector<Orientation> >holders; //a holder will have 0th line reference coords for SiD 0's possible orientations.
    vector<Orientation>temp;
    /*
     
     
     //storing the holders with appropriate orientations for each line corresponding to a SID
     for(int r=0;r<game().nships();r++)
     {
        vector<Orientation> temp;
        for(int c=0;c<#oforientations;c++)
        {
             temp.push_back(r);
        }
        holders.push_back(temp);
     }
     */
    /*
     vector<vector<int> > buff;
     
     for(int i = 0; i < 10; i++)
     {
     vector<int> temp; // create an array, don't work directly on buff yet.
     for(int j = 0; j < 10; j++)
     temp.push_back(i);
     
     buff.push_back(temp); // Store the array in the buffer
     }
     */
    
    
    
    
    //for attack
    vector<Point> attackedCells;
    vector<Point> limitedCells;
    vector<Point> attackedLimitedCells;
    Point PointofState2;
    bool state1;
    
    
};

MediocrePlayer::MediocrePlayer(string nm, const Game& g)
: Player(nm, g), m_lastCellAttacked(0, 0)
{state1=true;}
bool MediocrePlayer::myRecursivePlacements(Board &b,bool &fiftyTries, int n,int position, int &count,int & numberofShipsPlaced)
{
 //   Point myRandom=game().randomPoint(); //returns a random point so
    //// Clustering ships is bad strategy
   /* for (int k = 0; k < game().nShips(); k++)
        if ( ! b.placeShip(Point(k,0), k, HORIZONTAL))
            return false;
    return true;
    */
    //need to also make sure each random point is unique after testing it w/ a specific orientation
    //actually how about this, create a point called myRandom, and have it sweep through the board until a point in the board verifies it is not a #, then use that as my legit mypoint to be pushed to a point vector if it fails, and if that vector hits 50 points then I return false with a condition
   // Point myRandom=Point(0,0); //actually should I just use a systematic way of getting points instead of random?
    //i cna call game row and col to get all the points technically
   // Direction myDirection=HORIZONTAL; //initially start only testing horizontal options? actually why not just test if both orientations work, if both don't work then is my point actually a bad point.
    
  //  b.block();  //part 1, blocking and unblocking is working!
   // b.block();  //part 1, blocking and unblocking is working!

    //and almost now, at some point, for example my most recent test case, i will need a recursive impelmentation to backtrack and replace some ships.
    //if i finish and recursve back up here, i might be needing to start using the provisional vectors to place my stuff
   /*
    if(temp.size()>0)
    {
       
            for(int c=0;c<game().nShips();c++)
            {
                vector <Orientation> toPush;
                for(int r=0;r<temp.size();r++)  //position gets capped at nships though so...
                {
                    if(temp[r].myID==c) //c is 0 all values turn into all of temp r is going into topush. next, c is 1, all of
                    {
                        toPush.push_back(temp[c]);
                    }
                }
                if(toPush.size()>0)
                    holders.push_back(toPush);

            }
        
    }
    */
    //actually each temp already has an id and a but the temp is pretty big too wtf but in theory, i just need to match id and see if id is same as position, and if i am still trying to map it to the board, i must now consider it a skip.
    
    int p=game().rows()*game().cols();
    int sum=0;
    for(int d=0;d<game().nShips();d++)
    {
        sum+=game().shipLength(d);
    }
    if(sum>p)
    {
        return false; //checking to make sure that all the ships can infact indeed, fit on the board. if it fails the above, we know it has no chances of fitting, regardless of situation.
    }
    
    
   // b.block();
   // b.block();
   // b.display(false);
   
    if(n==1)
    {
     //   cout<<"NSHIPS="<<endl;
        bool shipNotPlaced=true;
                for(int r=0;r<game().rows()&&shipNotPlaced;r++)
                    {
                        for(int c=0;c<game().cols()&&shipNotPlaced;c++)
                        {
                            bool badpointsSkip=false;
                            //for dealing w/ bad points and to skip the below loops if there are bad points.
                            for(int d=0;d<myBadPoints.size();d++)   //making sure there is unique points
                            {
                                if(r==myBadPoints[d].r&&c==myBadPoints[d].c)
                                {
                                    //check the directions too.
                                    if(myBadDirections[d]==HORIZONTAL)//know we can skip horizontal case
                                    {
                                        badpointsSkip=true;
                                    }
                                
                                }
                            }
                            
                            for(int d=0;d<temp.size();d++)
                            {
                                if(r==temp[d].myP.r&&position==temp[d].myID&&c==temp[d].myP.c)
                                {
                                    //skip it
                                    badpointsSkip=true;
                                }
                            }
                            
                          
                            
                            
                            if(badpointsSkip)
                            {
                               // cout<<"SKIPPING A BAD POINT"<<r<<c<<endl;
                            }
                            else
                            {
                                if(!b.placeShip(Point(r,c),position,HORIZONTAL)) //can't place it at 0 0 0 1 1 0 1 2 2 0 2 1 2 2, horizontally.
                                {
                                //d=VERTICAL; //switch to vertical.
                                //myRecursivePlacements(b,fiftyTries);
                                // b.display(false); //for debugging purposes.
                                //oh after a fail, i should mark it down as oh i should NOT attempt to go that way again.
                              //  cout<<"ROW"<<r<<"COL"<<c<<endl;
                              //  cout<<"H   ROW"<<r<<"COL"<<c<<endl;

                                    if(!b.placeShip(Point(r,c),position, VERTICAL))
                                    {
                                        myBadPoints.push_back(Point(r,c));//its a bad point! unplacaeable at this point.
                                        myBadDirections.push_back(VERTICAL);
                                        //   cout<<"V   ROW"<<r<<"COL"<<c<<endl;

                                    }
                                    else
                                    {
                                        /*
                                        for(int d=0;d<holders.size();d++)
                                        {
                                            for(int e=0;e<holders[d].size();e++)
                                            {
                                                if(holders[d][e].myID==position)
                                                {
                                                    if(holders[d][e].myP.r==r&&holders[d][e].myP.c==c)
                                                    {
                                                        //if direction is horizontal too
                                                        if(holders[d][e].myD==VERTICAL)
                                                        {
                                                            //its a skip
                                                            cout<<"HOLDERS"<<endl;

                                                            badpointsSkip=true;
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                        
                                        if(badpointsSkip)
                                        {
                                         //   cout<<"SKIPPING A BAD POINT"<<r<<c<<endl;
                                        }
                                         */
                                        
                                        {
                                            myProvisionalPoints.push_back(Point(r,c));
                                            myProvisoinalDirections.push_back(VERTICAL);
                                            Orientation thisPos;
                                            thisPos.myD=VERTICAL;
                                            thisPos.myP=Point(r,c);
                                            thisPos.myID=position;
                                            temp.push_back(thisPos);
                                            shipNotPlaced=false;
                                            if(count>0)
                                                numberofShipsPlaced++;
                                        }
                                    }
                                }
                            //else placed horizontally on specified location.
                                
                                else
                                {
                                    /*
                                    for(int d=0;d<holders.size();d++)
                                    {
                                        for(int e=0;e<holders[d].size();e++)
                                        {
                                            if(holders[d][e].myID==position)
                                            {
                                                if(holders[d][e].myP.r==r&&holders[d][e].myP.c==c)
                                                {
                                                    //if direction is horizontal too
                                                    if(holders[d][e].myD==HORIZONTAL)
                                                    {
                                                        //its a skip
                                                        cout<<"HOLDERS"<<endl;

                                                        badpointsSkip=true;
                                                    }
                                                }
                                            }
                                        }
                                    }
                                    if(badpointsSkip)
                                    {
                                      //  cout<<"SKIPPING A BAD POINT"<<r<<c<<endl;
                                    }
                                     
                                    else*/
                                    {
                                        myProvisionalPoints.push_back(Point(r,c));
                                        myProvisoinalDirections.push_back(HORIZONTAL);
                                        Orientation thisPos;
                                        thisPos.myD=HORIZONTAL;
                                        thisPos.myP=Point(r,c);
                                        thisPos.myID=position;
                                        temp.push_back(thisPos);
                                        shipNotPlaced=false;
                                        if(count>0)
                                            numberofShipsPlaced++;
                                    }
                                }
                            }
                        }
                    }
                if(shipNotPlaced)
                {
                    //return false; //recursive it back and try again. this function returns false.
                    //try again
                   // count++;//increment the count because that was a failed attempt to recurse this route.
                    //unplace ships in previous calls.
                    
                    //if your at iniitila position and literally have no way out, we can also just return false early
                   // if(position==0)
                    //{
                     //   return false;
                    //}
                    
                    while(position>=0)
                    {
                        if(count==0) //first guy and its already not fitting no matter how you look at it
                            //check if size of the provisoinal points is 0. i mean number of ships placed
                        {
                            if(myProvisionalPoints.size()>0)
                            {
                                //check to unplace a ship first before return size.
                                while(position>=0)
                                {
                                    position--;
                                    b.unplaceShip(myProvisionalPoints[position], position, myProvisoinalDirections[position]);
                                }
                                
                            }
                            return false;
                        }
                        if(count>0)
                        {
                            
                            b.unplaceShip(myProvisionalPoints[position+numberofShipsPlaced], position, myProvisoinalDirections[position+numberofShipsPlaced]);
                        //myBadPoints.push_back(myProvisionalPoints[position]); //but if i dont push back those points, how do i make sure i am bypassing them? question qustion question. i think i just needa develop the bypasss a differenty way, b/c im not actually completely ignoring those points.
                        // myBadDirections.push_back(myProvisoinalDirections[position]); //rip misspelling.
                        }
                        else
                        {
                             b.unplaceShip(myProvisionalPoints[position], position, myProvisoinalDirections[position]);
                        }
                        
                        
                        //actually don't need those push backs, but i might want to check something else. or should ij ust mark my board somehow with unpalce ship?
                        position--;
                        
                    }
                    //and now also, push those guys into the points that "don't work"
                    
                    //  myProvisionalPoints.pop_back();//get rid of the provisional, no longer useful.
                    //  myProvisoinalDirections.pop_back();
                    // cout<<count<<endl;
                    //cout<<n<<endl;
                    //cout<<position<<endl;
                    position=0;
                    n=game().nShips();
             //       b.display(false);
                    count++;//increment the count because that was a failed attempt to recurse this route.

                    return myRecursivePlacements(b, fiftyTries, n,position , count,numberofShipsPlaced); //the function needs to backtrack and increment call of count by 1
                    

                }
        
    }
    else //for n!=1, then you can say get next. check if next is also ok and proceed as above. if not ok, then backtracking must occur and I must unplace a ship before placing the next ship. when i unplace the ship, i need to remind my guy here that I can't try to push that coordinate back anymore because it will fail the same way here. (slowly but surely also seeing how i might be able to count this up. i should use another int count and update that and check if int count ==50 with count starting at 0 passed by reference.
    {//ship id=0->4
        //i think i test the current one first, then move on to the next one.
        //cout<<game().nShips();
        //cout<<position<<"POSITON"<<endl;
        bool shipNotPlaced=true;
       // cout<<game().nShips();

        for(int r=0;r<game().rows()&&shipNotPlaced;r++)
        {
            for(int c=0;c<game().cols()&&shipNotPlaced;c++)
            {
                bool badpointsSkip=false;
                //for dealing w/ bad points and to skip the below loops if there are bad points.
                for(int d=0;d<myBadPoints.size();d++)   //making sure there is unique points
                {
                    if(r==myBadPoints[d].r&&c==myBadPoints[d].c)
                    {
                        //check the directions too.
                        if(myBadDirections[d]==HORIZONTAL)//know we can skip horizontal case
                        {
                            badpointsSkip=true;
                        }
                        
                    }
                }
                /*
                for(int d=0;d<myProvisoinalDirections.size();d++)
                {
                    if(r==myProvisionalPoints[d].r&&position==d&&c==myProvisionalPoints[d].c)
                    {
                        //skip it
                        badpointsSkip=true;
                    }
                }
                 */
                for(int d=0;d<temp.size();d++)
                {
                    if(r==temp[d].myP.r&&position==temp[d].myID&&c==temp[d].myP.c)
                    {
                        //skip it
                        badpointsSkip=true;
                    }
                }
                
                if(badpointsSkip)
                {
                   // cout<<"skipping bad pt"<<r<<c<<endl;
                }
                else
                {
                    if(!b.placeShip(Point(r,c),position,HORIZONTAL)) //can't place it at 0 0 0 1 1 0 1 2 2 0 2 1 2 2, horizontally.
                    {
                        //d=VERTICAL; //switch to vertical.
                        //myRecursivePlacements(b,fiftyTries);
                        // b.display(false); //for debugging purposes.
                        //oh after a fail, i should mark it down as oh i should NOT attempt to go that way again.
                        //  cout<<"ROW"<<r<<"COL"<<c<<endl;
                        //  cout<<"H   ROW"<<r<<"COL"<<c<<endl;
                        
                        if(!b.placeShip(Point(r,c),position, VERTICAL))
                        {
                            myBadPoints.push_back(Point(r,c));//its a bad point! unplacaeable at this point.
                            myBadDirections.push_back(VERTICAL);
                            //   cout<<"V   ROW"<<r<<"COL"<<c<<endl;
                            
                        }
                        else
                        {
                            /*
                            for(int d=0;d<holders.size();d++)
                            {
                                for(int e=0;e<holders[d].size();e++)
                                {
                                    if(holders[d][e].myID==position)
                                    {
                                        if(holders[d][e].myP.r==r&&holders[d][e].myP.c==c)
                                        {
                                            //if direction is horizontal too
                                            if(holders[d][e].myD==VERTICAL)
                                            {
                                                //its a skip
                                                cout<<"HOLDERS"<<endl;

                                                badpointsSkip=true;
                                            }
                                        }
                                    }
                                }
                            }
                            if(badpointsSkip)
                            {
                              //  cout<<"SKIPPING A BAD POINT"<<r<<c<<endl;
                            }
                            else*/
                            {
                                myProvisionalPoints.push_back(Point(r,c));
                                myProvisoinalDirections.push_back(VERTICAL);
                                Orientation thisPos;
                                thisPos.myD=VERTICAL;
                                thisPos.myP=Point(r,c);
                                thisPos.myID=position;
                                temp.push_back(thisPos);
                                shipNotPlaced=false;
                                if(count>0)
                                    numberofShipsPlaced++;
                            }
                        }

                    }
                    //else placed horizontally on specified location.
                    else
                    {
                        /*
                        for(int d=0;d<holders.size();d++)
                        {
                            for(int e=0;e<holders[d].size();e++)
                            {
                                if(holders[d][e].myID==position)
                                {
                                    if(holders[d][e].myP.r==r&&holders[d][e].myP.c==c)
                                    {
                                        //if direction is horizontal too
                                        if(holders[d][e].myD==HORIZONTAL)
                                        {
                                            //its a skip
                                            badpointsSkip=true;
                                            cout<<"HOLDERS"<<endl;
                                        }
                                    }
                                }
                            }
                        }
                        if(badpointsSkip)
                        {
                        //    cout<<"SKIPPING A BAD POINT"<<r<<c<<endl;
                        }
                        else*/
                        
                        {
                            myProvisionalPoints.push_back(Point(r,c));
                            myProvisoinalDirections.push_back(HORIZONTAL);
                            Orientation thisPos;
                            thisPos.myD=HORIZONTAL;
                            thisPos.myP=Point(r,c);
                            thisPos.myID=position;
                            temp.push_back(thisPos);
                            shipNotPlaced=false;
                            if(count>0)
                                numberofShipsPlaced++;
                        }
                    }
                }
            }
        }
        
        
        if(shipNotPlaced)
        {
           // return false; //recursive it back and try again. this function returns false.
            //unplace ships in previous calls.
            
            while(position>=0)
            {
                if(count==0) //first guy and its already not fitting no matter how you look at it
                    //check if size of the provisoinal points is 0. i mean number of ships placed
                {
                    if(myProvisionalPoints.size()>0)
                    {
                        //check to unplace a ship first before return size.
                        while(position>=0)
                        {
                            position--;
                            b.unplaceShip(myProvisionalPoints[position], position, myProvisoinalDirections[position]);
                        }
                        
                    }
                    return false;
                }
                if(count>0)
                {
                    b.unplaceShip(myProvisionalPoints[position+numberofShipsPlaced], position, myProvisoinalDirections[position+numberofShipsPlaced]);
                    //myBadPoints.push_back(myProvisionalPoints[position]); //but if i dont push back those points, how do i make sure i am bypassing them? question qustion question. i think i just needa develop the bypasss a differenty way, b/c im not actually completely ignoring those points.
                    // myBadDirections.push_back(myProvisoinalDirections[position]); //rip misspelling.
                }
                else
                {
                    b.unplaceShip(myProvisionalPoints[position], position, myProvisoinalDirections[position]);
                }
                
                
                //actually don't need those push backs, but i might want to check something else. or should ij ust mark my board somehow with unpalce ship?
                position--;
                
            }
            //and now also, push those guys into the points that "don't work"
            
            //  myProvisionalPoints.pop_back();//get rid of the provisional, no longer useful.
            //  myProvisoinalDirections.pop_back();
            // cout<<count<<endl;
            //cout<<n<<endl;
            //cout<<position<<endl;
            position=0;
            n=game().nShips();
          //  b.display(false);
            count++;//increment the count because that was a failed attempt to recurse this route.

            return myRecursivePlacements(b, fiftyTries, n,position , count,numberofShipsPlaced); //the function needs to backtrack and increment call of count by 1
            
        

        }
       // b.display(false); //for debugging purposes.

       // cout<<"CALLING RECURSION"<<endl;
        if(myRecursivePlacements(b, fiftyTries, n-1,position +1 ,count,numberofShipsPlaced))
        {
           // return (myRecursivePlacements(b, fiftyTries, n-1, position+1, count));//no count up.
            return true;
        }
        else //means no good on the next ship, we have to backtrack
        {
            //unplace ships in previous calls.
            
            while(position>=0)
            {
                if(count==0) //first guy and its already not fitting no matter how you look at it
                    //check if size of the provisoinal points is 0. i mean number of ships placed
                {
                    if(myProvisionalPoints.size()>0)
                    {
                        //check to unplace a ship first before return size.
                        while(position>=0)
                        {
                            position--;
                            b.unplaceShip(myProvisionalPoints[position], position, myProvisoinalDirections[position]);
                        }
                        
                    }
                    return false;
                }
                if(count>0)
                {
                    b.unplaceShip(myProvisionalPoints[position+numberofShipsPlaced], position, myProvisoinalDirections[position+numberofShipsPlaced]);
                    //myBadPoints.push_back(myProvisionalPoints[position]); //but if i dont push back those points, how do i make sure i am bypassing them? question qustion question. i think i just needa develop the bypasss a differenty way, b/c im not actually completely ignoring those points.
                    // myBadDirections.push_back(myProvisoinalDirections[position]); //rip misspelling.
                }
                else
                {
                    b.unplaceShip(myProvisionalPoints[position], position, myProvisoinalDirections[position]);
                }
                
                
                //actually don't need those push backs, but i might want to check something else. or should ij ust mark my board somehow with unpalce ship?
                position--;
                
            }            //and now also, push those guys into the points that "don't work"
            
          //  myProvisionalPoints.pop_back();//get rid of the provisional, no longer useful.
          //  myProvisoinalDirections.pop_back();
           // cout<<count<<endl;
            //cout<<n<<endl;
            //cout<<position<<endl;
            position=0;
            n=game().nShips();
        //    b.display(false);
            count++;//increment the count because that was a failed attempt to recurse this route.

            return myRecursivePlacements(b, fiftyTries, n,position , count,numberofShipsPlaced); //the function needs to backtrack and increment call of count by 1

        }
    }
    //b.display(false);//testing purposes.

    return true;
    //so should i just sweep the whole game board with a ship of size 1 and
}

bool MediocrePlayer::placeShips(Board& b)   //i guess for debugging purposes, i can turn this player into a human to display his board better for me.
{/*
    1. First, it must call the block function on the specified board. This will randomly
    block off about half the positions on the board. No segment of any ship will
    occupy one of these squares.
    2. Second, you must use a recursive algorithm to place each of the five ships on the
    board, ensuring that no ship overlaps any other ship and that no ship overlaps a
    blocked position. You must use the board class’s placeShip function to attempt to
    place a ship on the board, and unplaceShip to remove it from the board if the
        position isn’t appropriate. To fit each ship, you may need to place some of them
        vertically, others horizontally, etc. You may find that after placing some of the
        ships, you have misallocated the space and need to backtrack, removing the ships
        you’ve already placed to try a different configuration.
        3. After attempting to place the ships, your function must call the unblock function
        to remove the blocked squares. This will leave just the ships on your board.
        4. If all ships could be placed, this function returns true. If it is impossible to fit all
        of the ships on the board, given the set of blocked positions from the first step,
        then your function must go back to step 1 and try again if it hasn't yet done so 50
            times. The function has not returned true after 50 tries, then it must return false.
            (Hint: placeShips itself will probably not be recursive. For step 2 above, though, it may
             well call an auxiliary function that will be recursive.)
            Here's an example of the backtracking algorithm. Suppose we wish to place three ships
            into the board below, a 4-segment battleship, a 3-segment submarine, and a 2-segment
            patrol boat. (Note that # represents a blocked position; the actual block() function will
                          not block this high a percentage of the squares):
  
  
  
  
  
  
   is to  try to add current ship, then try to add the next, if i can't i would have to unplace this one
  */
    for(int c=0;c<50;c++)
    {
        b.block();  //part 1, blocking and unblocking is working!
   // b.display(false); //for debugging purposes.

    //place the ships, part 2
    //Direction d=HORIZONTAL;
        bool fiftyTries=false;
        int fiftycount=0;
        int pos=0;
        int numberofShipsPlaced=0;
        //block it a few more times and display the resuklts to test that im actually blocking and retrying the unblock.
        //cout<<"TRIAL"<<c<<endl; should be working based on what im seeing. gj
        //b.block();
       // b.block();
       // b.display(false);
        if(myRecursivePlacements(b,fiftyTries, game().nShips(),pos,fiftycount,numberofShipsPlaced)) //if success then return true.
        {
        //double block to make it harder
         //   b.display(false);

            b.unblock();
      //  b.display(false); //for debugging purposes.
        //part 3, unblock
    
        //part 4 , if all placeable, true, else rinse and repeat step 1. up to 50 tries. if it hasn't then return false.
        //oh ok placeships this function isn't recursive, call another function that WILL Be recursive. i guess he wants me to be implementing a diff function that is recursive to do that for me.
            return true;
        }
       // b.display(false);
        myProvisionalPoints.clear();
        myProvisoinalDirections.clear();
        myBadPoints.clear();
        myBadDirections.clear();
        temp.clear();
        b.unblock(); //try again.

    }   //tests the block and unblock step 50 times. if it fails 50 times, then i giveu p .
    return false;

}

Point MediocrePlayer::recommendAttack() //returns a point
{
    if(state1)
    {
        m_lastCellAttacked=game().randomPoint(); //state 1

        if(attackedCells.size()>0)
        {
            //m_lastCellAttacked=game().randomPoint(); //state 1
            bool unique=false;
            while(!unique)
            {
                m_lastCellAttacked=game().randomPoint(); //state 1
                //cout<<m_lastCellAttacked.r<<m_lastCellAttacked.c<<endl;
                //cout<<"ASF"<<endl; random works, i was just having a problem in the board cpp
                for(int c=0;c<attackedCells.size();c++)
        //while(m_lastCellAttacked==a value in the attackedCellsvector)
                {
                    if(m_lastCellAttacked.r==attackedCells[c].r&&m_lastCellAttacked.c==attackedCells[c].c)
                    {
                        unique=false;
                        break;
                    }
                    else
                    {
                        unique=true;
                        
                    }
                }
            }
        }
    }
    if(!state1)
    {
        //cout<<"IM IN STATE 2"<<endl;
      
      //  bool bounded=false;
        if(limitedCells.size()>0)
        {
            //for(int c=0;c<limitedCells.size();c++)
           // {
                //cout<<"my coords in limited cells are "<<limitedCells[c].r<<limitedCells[c].c<<endl;
                //limited cells are ok
            //}
          //  vector<Point>::iterator q=limitedCells.begin();
            
            //if all values in attackedlimitcells belong to limitedcells.size() then return recommendAttack(); acttually.
            int count=0;
            for(int c=0;c<attackedLimitedCells.size();c++)
            {
                for(int d=0;d<limitedCells.size();d++)
                {
                    if(attackedLimitedCells[c].r==limitedCells[d].r&&attackedLimitedCells[c].c==limitedCells[d].r)
                    {
                        count++;
                    }
                }
            }
            if(count>=limitedCells.size())
            {
                state1=true;
                return recommendAttack();//recursive attack
            }
            
        }
        
        
        //shit still needs to be unique here even though that is limited.
            if(attackedCells.size()>0)
            {
                //m_lastCellAttacked=game().randomPoint(); //state 1
                bool unique=false;
                bool actualValid=true;
            while(!unique)
            {
                
                //new plan:
                //1. after recoding the vector of poss attacked cells, compare it with the coords in the other attacked cell vector to make sure no overlapping
                //2. next, throw out any overlapping. after that, make sure stay in state 2 only if still in state 2, once state 2 is over, clear the limited cells vector. use couts to make sure i guess and also print out the actual sizes etc of the vector and the coords of poss attack so i dont have to keep breakpointng just to see stuff.
                
                actualValid=true;
                m_lastCellAttacked=game().randomPoint();
                
                          //cout<<m_lastCellAttacked.r<<m_lastCellAttacked.c<<endl;
                //cout<<"ASF"<<endl; random works, i was just having a problem in the board cpp
                for(int c=0;c<limitedCells.size();c++)
                    //while(m_lastCellAttacked==a value in the attackedCellsvector)
                {
                    //and if in the case size of ship is too big, what i can just do instead would be to check if size of limitedcells=size of attacklimited cells. if thats the case then ik i can just switch to state 1.
                    if(m_lastCellAttacked.r==limitedCells[c].r&&m_lastCellAttacked.c==limitedCells[c].c)
                    {
                        //cout<<"SHOT SELECTION IS"<<endl;
                        //cout<<m_lastCellAttacked.r<<m_lastCellAttacked.c<<endl;
                        
                        //after choosing the shot, i need to mark that as a no longer potential shot to choose from inside this, so i guess ill create a new vector for that too....
                        if(attackedLimitedCells.size()>0)
                        {
                            for(int d=0;d<attackedLimitedCells.size();d++)
                            {
                                if(attackedLimitedCells[d].c==m_lastCellAttacked.c&&attackedLimitedCells[d].r==m_lastCellAttacked.r)
                                {
                                    //not actually a unique, but a repeat. so don't break and unique is not true.
                                    actualValid=false;
                                }
                            }
                        }
                        if(actualValid)
                        {
                            attackedLimitedCells.push_back(m_lastCellAttacked);
                            unique=true;
                            break;  //its valid here and bcomes my shot
                        }
                    }
                    else
                    {
                        unique=false;
                    }
                }
            }
        }

        
        
    }
   // bool didIhit=true;
   // bool validShot=true;
   // bool sDestroyed=false;
   // int sID=0;
    
   // b.attack(m_lastCellAttacked,validShot,didIhit,sDestroyed,sID);
    
    //recordAttackResult(m_lastCellAttacked, validShot, didIhit, sDestroyed, sID); DONT CALL IT HERE?
    
    
    return m_lastCellAttacked;
}

void MediocrePlayer::recordAttackResult(Point p , bool  validShot ,bool  shotHit, bool  shipDestroyed ,int  shipId )
{
    /*The Mediocre Player is in one of two states; initially it is in state 1.
     1. In state 1, recommendAttack returns a randomly chosen position on the board that
     has not been chosen before. There are then three possible outcomes when this
     position is attacked:
     16
     a. The attack missed. In this case, the player stays in state 1 (so it will
     again make a random choice for the next recommendation).
     b. The attack hits a ship, destroying its final undestroyed segment, so the
     ship is destroyed. In this case, the random attack got lucky and
     completely destroyed a ship that was almost destroyed earlier. In this
     case, the player stays in state 1.
     c. The attack hits a ship, but does not destroy it. In this case, the player
     switches to state 2 (so will use the algorithm below for the next
     recommendation)
     */
    attackedCells.push_back(p); //so i dont hit again
    bool justSwitched=false;
    if(state1)
    {
        if(!shotHit)
        {
            state1=true;
        }
        if(shotHit&&shipDestroyed)
        {
            state1=true;
        }
        else if(shotHit&&!shipDestroyed)
        {
            state1=false;
            justSwitched=true;
        }
    }
    if(!state1)
    {
        /*In state 2, let (r,c) be the position that was hit that caused the transition from state
         1 to state 2. In state 2, recommendAttack returns a randomly chosen position
         drawn from a limited set: the set of valid positions no more than 4 steps away
         from (r,c) either horizontally or vertically, that have not been chosen before. This
         set defines a cross around (r,c). For example, assume that in state 1, a shot was
         fired on position (5,3) that hit a ship, but did not destroy it, resulting in:
         */
        if(justSwitched)
        {
           // cout<<"YOU FUKING TRIGGERED ME"<<endl;
            
            if(limitedCells.size()>0)
            {
                for(int c=0;c<limitedCells.size();c++)
                {
                    limitedCells.pop_back();
                }
            }
            
            PointofState2=p; //4 4   0  0
            int rS2Left=PointofState2.r-4; //4 0    - 4 0    (my row left so -4 off grid
            int rS2Right=PointofState2.r+4;  //4 8     8  0
            int cS2Top=PointofState2.c-4; //0 4     -4   4
            int cS2Bot=PointofState2.c+4; // 8 4
            
            attackedLimitedCells.push_back(PointofState2);
            
            
            //run a check to see that if these values are also in the point of attacked cells. if they are, then dont even bother trying to push it in as a coordinate. also, check if the coordinate to push in is a valid one to begin with. if this is implemented right, the above wouldn't have to worry about iterators at all.
            for(int c=rS2Left;c<=rS2Right;c++) //-4 -3 -2 -1 0 1 2 3
            {
                bool canpush=true;
                for(int d=0;d<attackedCells.size();d++)
                {//if attacked cells
             //1 0
                    if(attackedCells[d].r==c&&attackedCells[d].c==PointofState2.c)
                    {
                        canpush=false;
                    }
                    else
                    {
                        
                    }
                }
                Point tryingtoPush;
                tryingtoPush.r=c;
                tryingtoPush.c=PointofState2.c;
                if(!game().isValid(tryingtoPush))
                {
                    canpush=false;
                }
                
                if(canpush)
                {
                    limitedCells.push_back(Point(c,PointofState2.c));//coordinates for left to right
                }
            }
            for(int c=cS2Top;c<=cS2Bot;c++)
            {
                bool canpush=true;
                for(int d=0;d<attackedCells.size();d++)
                {//if attacked cells
                    
                    if(attackedCells[d].c==c&&attackedCells[d].r==PointofState2.r)
                    {
                        canpush=false;
                    }
                    else
                    {
                        
                    }
                }
                Point tryingtoPush;
                tryingtoPush.r=c;
                tryingtoPush.c=PointofState2.r;
                if(!game().isValid(tryingtoPush))
                {
                    canpush=false;
                }
                if(canpush)
                {
                    limitedCells.push_back(Point(PointofState2.r,c));//top to bot

                }
                
                //limitedCells.push_back(Point(c,PointofState2.c));//coordinates for left to right
                //oh shoot if theres a new one u have to pop_back all the limited cells so u dont bait it .
            }
            
            
            //last but not least, if all possible checks in that area can be checked is done for, then i have to say to go back to random selection.
            
        }
        else
        {
          //  cout<<"Resuming state 2 barage"<<endl;
            if(!shotHit)//miss
            {
                state1=false;
            }
            else if(shotHit&&!shipDestroyed)
            {
                state1=false;
            }
            else if(shotHit&&shipDestroyed)
            {
                state1=true; //i go back to normal
            //    cout<<"Since i sank ur ship im going back to normal me."<<endl;
                /*
                for(int c=0;c<attackedLimitedCells.size();c++)
                {
                    attackedLimitedCells.pop_back();
                }
                 */
            }
        }
    }
    
    
    
}

void MediocrePlayer::recordAttackByOpponent(Point /* p */)
{
    // Mediocre completely ignores what the opponent does For a MediocrePlayer, this function does nothing. What attacks an opponent has made do
   // not affect a MediocrePlayer's attack decisions.
}
// Remember that Mediocre::placeShips(Board& b) must start by calling
// b.block(), and must call b.unblock() just before returning.


//*********************************************************************
//  GoodPlayer
//*********************************************************************

// TODO:  You need to replace this with a real class declaration and
//        implementation.

/* RECORD ATTACK BY OPPOENENT
 This function must be implemented in concrete derived player classes. Game::play()
 must call this function when an attack is made on this player's board. The position p is
 where the attack was made. The player may very well have this function do nothing.
 However, an intelligent non-human player might want to keep track of an opponent's
 attacks and adjust its own attack strategy accordingly. For example, the player might
 notice the opponent is attacking in a certain pattern, use that to predict how far from
 winning the opponent is, and play differently depending on whether or not an opponent is
 far from or close to winning
 */
//for the goodplayer, maybe a good player is when a guy attacks a certain spot on my board, I think it might be a spot that he has on his board and attack there?



class GoodPlayer : public Player
{
public:
    GoodPlayer(string nm, const Game& g);
    virtual bool placeShips(Board& b);
    virtual Point recommendAttack();
    virtual void recordAttackResult(Point p, bool validShot, bool shotHit,
                                    bool shipDestroyed, int shipId);
    virtual void recordAttackByOpponent(Point p);
    
    virtual ~GoodPlayer(){} //implement a v dtor.
private:
    bool myRecursivePlacements(Board &b, bool &fiftyTries,int n,int position, int &count, int & numberofShipsPlaced);
    Point m_lastCellAttacked;
    //should i implement an orientation type that baiscally has an orientation and a point coordinate, and push those onto a vector of orientations? this way i can use that to check and make sure i dont attempt to keep placing stuff like that.
    vector<Point> myBadPoints; //each index corresponds to like the ID of a bad point and a bad direction?
    vector<Direction> myBadDirections;
    struct Orientation
    {
        Point myP;
        Direction myD;
        int myID;
        
        bool canPlace; //set this to eitehr true or false, i can actually probably make into a base case from this?
    };
    //how bout a mybadpoints orientation vector, that takes in a point and a direction. and for each index it regards all the bad configurations for a ship on the board?
    
    
    //the provisional points
    vector<Point> myProvisionalPoints; //each index corresponds to like the ID of a bad point and a bad direction?
    vector<Direction> myProvisoinalDirections;
    //1. i need a way to place all the ships first. then check if i can rearrange if it fails, each time when i need to rearrange, ill pop all the ships and i guess, change orientation then. so for now, or initial attempt is to just try to fit everything horizontally.
    vector<vector<Orientation> >holders; //a holder will have 0th line reference coords for SiD 0's possible orientations.
    vector<Orientation>temp; //temp will be the way for me to check actually, my Provsionals and skip them.
    /*
     
     
     //storing the holders with appropriate orientations for each line corresponding to a SID
     for(int r=0;r<game().nships();r++)
     {
     vector<Orientation> temp;
     for(int c=0;c<#oforientations;c++)
     {
     temp.push_back(r);
     }
     holders.push_back(temp);
     }
     */
    /*
     vector<vector<int> > buff;
     
     for(int i = 0; i < 10; i++)
     {
     vector<int> temp; // create an array, don't work directly on buff yet.
     for(int j = 0; j < 10; j++)
     temp.push_back(i);
     
     buff.push_back(temp); // Store the array in the buffer
     }
     */
    
    
    //partition that board in half later too.
    
    //for attack
    vector<Point> attackedCells;
    vector<Point> limitedCells;
    vector<Point> attackedLimitedCells;
    
    vector<Point> partitionedPointsCheck;
    
    Point PointofState2;
    bool state1;
    //maybe more than 1 state?
    
    
    enum state {STATE1,STATE2,STATE3,STATE4};
    
    
    
    
    
    vector <Point> enemyAttacks;
    
    //for state 3, considering if i should go up or down or left or right.
    vector<Point> DirectionPattern;
    state currentState=STATE1;

    
    
    
    bool justSwitched=false;
    bool justSwitched2=false;
    bool justSwitched3=false;
};

GoodPlayer::GoodPlayer(string nm, const Game& g)
: Player(nm, g), m_lastCellAttacked(0, 0)
{state1=true;}
bool GoodPlayer::myRecursivePlacements(Board &b,bool &fiftyTries, int n,int position, int &count,int & numberofShipsPlaced)
{
    //he can place ships exactly like a mediocre player, it doesnt really matter tbh i think since its also kinda nicely scattered out.
    
    
    //   Point myRandom=game().randomPoint(); //returns a random point so
    //// Clustering ships is bad strategy
    /* for (int k = 0; k < game().nShips(); k++)
     if ( ! b.placeShip(Point(k,0), k, HORIZONTAL))
     return false;
     return true;
     */
    //need to also make sure each random point is unique after testing it w/ a specific orientation
    //actually how about this, create a point called myRandom, and have it sweep through the board until a point in the board verifies it is not a #, then use that as my legit mypoint to be pushed to a point vector if it fails, and if that vector hits 50 points then I return false with a condition
    // Point myRandom=Point(0,0); //actually should I just use a systematic way of getting points instead of random?
    //i cna call game row and col to get all the points technically
    // Direction myDirection=HORIZONTAL; //initially start only testing horizontal options? actually why not just test if both orientations work, if both don't work then is my point actually a bad point.
    
    //  b.block();  //part 1, blocking and unblocking is working!
    // b.block();  //part 1, blocking and unblocking is working!
    
    //and almost now, at some point, for example my most recent test case, i will need a recursive impelmentation to backtrack and replace some ships.
    //if i finish and recursve back up here, i might be needing to start using the provisional vectors to place my stuff
    /*
     if(temp.size()>0)
     {
     
     for(int c=0;c<game().nShips();c++)
     {
     vector <Orientation> toPush;
     for(int r=0;r<temp.size();r++)  //position gets capped at nships though so...
     {
     if(temp[r].myID==c) //c is 0 all values turn into all of temp r is going into topush. next, c is 1, all of
     {
     toPush.push_back(temp[c]);
     }
     }
     if(toPush.size()>0)
     holders.push_back(toPush);
     
     }
     
     }
     */
    //actually each temp already has an id and a but the temp is pretty big too wtf but in theory, i just need to match id and see if id is same as position, and if i am still trying to map it to the board, i must now consider it a skip.
    
    // b.block();
    // b.block();
    // b.display(false);
    
    
    
    //before a return i should empty bad points and bad direcitions as well so each ship has a unique chance of testing for placement on the board.
    //from now on also provsional poitns and directions will now literally just be relying on temp. temp already does all that better and can arrange/sort better.
   //oh if it some how considered all valid points, on the board so literally all points on the board, and still fails, thats when we know we can truly return false. therefore, size of provisional points is == validPoints on the board.
   
    
    //MIGHT WANT TO MAKE SURE THERE ARE ALSO NO DUPLICATES TO MAKE IT EASIER TO TRACK and debug.
    if(count>=300) //one of the big base cases
    //{
        return false;//exceeded 50 checks of rearranging. //what if i dont have 50 ways to rearrange?
    //}
    if(n==1)
    {
        //   cout<<"NSHIPS="<<endl;
        bool shipNotPlaced=true;
        for(int r=0;r<game().rows()&&shipNotPlaced;r++)
        {
            for(int c=0;c<game().cols()&&shipNotPlaced;c++)
            {
                bool badpointsSkip=false;
                //for dealing w/ bad points and to skip the below loops if there are bad points.
                for(int d=0;d<myBadPoints.size();d++)   //making sure there is unique points
                {
                    if(r==myBadPoints[d].r&&c==myBadPoints[d].c)
                    {
                        //check the directions too.
                        if(myBadDirections[d]==HORIZONTAL)//know we can skip horizontal case
                        {
                            badpointsSkip=true;
                        }
                        
                    }
                }
                
                for(int d=0;d<temp.size();d++)
                {
                    if(r==temp[d].myP.r&&position==temp[d].myID&&c==temp[d].myP.c)
                    {
                        //skip it
                        badpointsSkip=true;
                    }
                }
                
                
                
                
                if(badpointsSkip)
                {
                    // cout<<"SKIPPING A BAD POINT"<<r<<c<<endl;
                }
                else
                {
                    if(!b.placeShip(Point(r,c),position,HORIZONTAL)) //can't place it at 0 0 0 1 1 0 1 2 2 0 2 1 2 2, horizontally.
                    {
                        //d=VERTICAL; //switch to vertical.
                        //myRecursivePlacements(b,fiftyTries);
                        // b.display(false); //for debugging purposes.
                        //oh after a fail, i should mark it down as oh i should NOT attempt to go that way again.
                        //  cout<<"ROW"<<r<<"COL"<<c<<endl;
                        //  cout<<"H   ROW"<<r<<"COL"<<c<<endl;
                        
                        if(!b.placeShip(Point(r,c),position, VERTICAL))
                        {
                            myBadPoints.push_back(Point(r,c));//its a bad point! unplacaeable at this point.
                            myBadDirections.push_back(VERTICAL);
                            //   cout<<"V   ROW"<<r<<"COL"<<c<<endl;
                            
                        }
                        else
                        {
                            /*
                             for(int d=0;d<holders.size();d++)
                             {
                             for(int e=0;e<holders[d].size();e++)
                             {
                             if(holders[d][e].myID==position)
                             {
                             if(holders[d][e].myP.r==r&&holders[d][e].myP.c==c)
                             {
                             //if direction is horizontal too
                             if(holders[d][e].myD==VERTICAL)
                             {
                             //its a skip
                             cout<<"HOLDERS"<<endl;
                             
                             badpointsSkip=true;
                             }
                             }
                             }
                             }
                             }
                             
                             if(badpointsSkip)
                             {
                             //   cout<<"SKIPPING A BAD POINT"<<r<<c<<endl;
                             }
                             */
                            
                            {
                                myProvisionalPoints.push_back(Point(r,c));
                                myProvisoinalDirections.push_back(VERTICAL);
                                Orientation thisPos;
                                thisPos.myD=VERTICAL;
                                thisPos.myP=Point(r,c);
                                thisPos.myID=position;
                                temp.push_back(thisPos);
                                shipNotPlaced=false;
                                if(count>0)
                                    numberofShipsPlaced++;
                            }
                        }
                    }
                    //else placed horizontally on specified location.
                    
                    else
                    {
                        /*
                         for(int d=0;d<holders.size();d++)
                         {
                         for(int e=0;e<holders[d].size();e++)
                         {
                         if(holders[d][e].myID==position)
                         {
                         if(holders[d][e].myP.r==r&&holders[d][e].myP.c==c)
                         {
                         //if direction is horizontal too
                         if(holders[d][e].myD==HORIZONTAL)
                         {
                         //its a skip
                         cout<<"HOLDERS"<<endl;
                         
                         badpointsSkip=true;
                         }
                         }
                         }
                         }
                         }
                         if(badpointsSkip)
                         {
                         //  cout<<"SKIPPING A BAD POINT"<<r<<c<<endl;
                         }
                         
                         else*/
                        {
                            myProvisionalPoints.push_back(Point(r,c));
                            myProvisoinalDirections.push_back(HORIZONTAL);
                            Orientation thisPos;
                            thisPos.myD=HORIZONTAL;
                            thisPos.myP=Point(r,c);
                            thisPos.myID=position;
                            temp.push_back(thisPos);
                            shipNotPlaced=false;
                            if(count>0)
                                numberofShipsPlaced++;
                        }
                    }
                }
            }
        }
        if(shipNotPlaced)
        {
            //return false; //recursive it back and try again. this function returns false.
            //try again
            // count++;//increment the count because that was a failed attempt to recurse this route.
            //unplace ships in previous calls.
            
            //if your at iniitila position and literally have no way out, we can also just return false early
            // if(position==0)
            //{
            //   return false;
            //}
            
            while(position>=0)
            {
                if(count==0) //first guy and its already not fitting no matter how you look at it
                {
                    return false;
                }
                if(count>0)
                {
                    
                    b.unplaceShip(myProvisionalPoints[position+numberofShipsPlaced], position, myProvisoinalDirections[position+numberofShipsPlaced]);
                    //myBadPoints.push_back(myProvisionalPoints[position]); //but if i dont push back those points, how do i make sure i am bypassing them? question qustion question. i think i just needa develop the bypasss a differenty way, b/c im not actually completely ignoring those points.
                    // myBadDirections.push_back(myProvisoinalDirections[position]); //rip misspelling.
                }
                else
                {
                    b.unplaceShip(myProvisionalPoints[position], position, myProvisoinalDirections[position]);
                }
                
                
                //actually don't need those push backs, but i might want to check something else. or should ij ust mark my board somehow with unpalce ship?
                position--;
                
            }
            //and now also, push those guys into the points that "don't work"
            
            //  myProvisionalPoints.pop_back();//get rid of the provisional, no longer useful.
            //  myProvisoinalDirections.pop_back();
            // cout<<count<<endl;
            //cout<<n<<endl;
            //cout<<position<<endl;
            position=0;
            n=game().nShips();
            //       b.display(false);
            count++;//increment the count because that was a failed attempt to recurse this route.
            
            return myRecursivePlacements(b, fiftyTries, n,position , count,numberofShipsPlaced); //the function needs to backtrack and increment call of count by 1
            
            
        }
        
    }
    else //for n!=1, then you can say get next. check if next is also ok and proceed as above. if not ok, then backtracking must occur and I must unplace a ship before placing the next ship. when i unplace the ship, i need to remind my guy here that I can't try to push that coordinate back anymore because it will fail the same way here. (slowly but surely also seeing how i might be able to count this up. i should use another int count and update that and check if int count ==50 with count starting at 0 passed by reference.
    {//ship id=0->4
        //i think i test the current one first, then move on to the next one.
        //cout<<game().nShips();
        //cout<<position<<"POSITON"<<endl;
        bool shipNotPlaced=true;
        // cout<<game().nShips();
        
        for(int r=0;r<game().rows()&&shipNotPlaced;r++)
        {
            for(int c=0;c<game().cols()&&shipNotPlaced;c++)
            {
                bool badpointsSkip=false;
                //for dealing w/ bad points and to skip the below loops if there are bad points.
                for(int d=0;d<myBadPoints.size();d++)   //making sure there is unique points
                {
                    if(r==myBadPoints[d].r&&c==myBadPoints[d].c)
                    {
                        //check the directions too.
                        if(myBadDirections[d]==HORIZONTAL)//know we can skip horizontal case
                        {
                            badpointsSkip=true;
                        }
                        
                    }
                }
                /*
                 for(int d=0;d<myProvisoinalDirections.size();d++)
                 {
                 if(r==myProvisionalPoints[d].r&&position==d&&c==myProvisionalPoints[d].c)
                 {
                 //skip it
                 badpointsSkip=true;
                 }
                 }
                 */
                for(int d=0;d<temp.size();d++)
                {
                    if(r==temp[d].myP.r&&position==temp[d].myID&&c==temp[d].myP.c)
                    {
                        //skip it
                        badpointsSkip=true;
                    }
                }
                
                if(badpointsSkip)
                {
                    // cout<<"skipping bad pt"<<r<<c<<endl;
                }
                else
                {
                    if(!b.placeShip(Point(r,c),position,HORIZONTAL)) //can't place it at 0 0 0 1 1 0 1 2 2 0 2 1 2 2, horizontally.
                    {
                        //d=VERTICAL; //switch to vertical.
                        //myRecursivePlacements(b,fiftyTries);
                        // b.display(false); //for debugging purposes.
                        //oh after a fail, i should mark it down as oh i should NOT attempt to go that way again.
                        //  cout<<"ROW"<<r<<"COL"<<c<<endl;
                        //  cout<<"H   ROW"<<r<<"COL"<<c<<endl;
                        
                        if(!b.placeShip(Point(r,c),position, VERTICAL))
                        {
                            myBadPoints.push_back(Point(r,c));//its a bad point! unplacaeable at this point.
                            myBadDirections.push_back(VERTICAL);
                            //   cout<<"V   ROW"<<r<<"COL"<<c<<endl;
                            
                        }
                        else
                        {
                            /*
                             for(int d=0;d<holders.size();d++)
                             {
                             for(int e=0;e<holders[d].size();e++)
                             {
                             if(holders[d][e].myID==position)
                             {
                             if(holders[d][e].myP.r==r&&holders[d][e].myP.c==c)
                             {
                             //if direction is horizontal too
                             if(holders[d][e].myD==VERTICAL)
                             {
                             //its a skip
                             cout<<"HOLDERS"<<endl;
                             
                             badpointsSkip=true;
                             }
                             }
                             }
                             }
                             }
                             if(badpointsSkip)
                             {
                             //  cout<<"SKIPPING A BAD POINT"<<r<<c<<endl;
                             }
                             else*/
                            {
                                myProvisionalPoints.push_back(Point(r,c));
                                myProvisoinalDirections.push_back(VERTICAL);
                                Orientation thisPos;
                                thisPos.myD=VERTICAL;
                                thisPos.myP=Point(r,c);
                                thisPos.myID=position;
                                temp.push_back(thisPos);
                                shipNotPlaced=false;
                                if(count>0)
                                    numberofShipsPlaced++;
                            }
                        }
                        
                    }
                    //else placed horizontally on specified location.
                    else
                    {
                        /*
                         for(int d=0;d<holders.size();d++)
                         {
                         for(int e=0;e<holders[d].size();e++)
                         {
                         if(holders[d][e].myID==position)
                         {
                         if(holders[d][e].myP.r==r&&holders[d][e].myP.c==c)
                         {
                         //if direction is horizontal too
                         if(holders[d][e].myD==HORIZONTAL)
                         {
                         //its a skip
                         badpointsSkip=true;
                         cout<<"HOLDERS"<<endl;
                         }
                         }
                         }
                         }
                         }
                         if(badpointsSkip)
                         {
                         //    cout<<"SKIPPING A BAD POINT"<<r<<c<<endl;
                         }
                         else*/
                        
                        {
                            myProvisionalPoints.push_back(Point(r,c));
                            myProvisoinalDirections.push_back(HORIZONTAL);
                            Orientation thisPos;
                            thisPos.myD=HORIZONTAL;
                            thisPos.myP=Point(r,c);
                            thisPos.myID=position;
                            temp.push_back(thisPos);
                            shipNotPlaced=false;
                            if(count>0)
                                numberofShipsPlaced++;
                        }
                    }
                }
            }
        }
        
        
        if(shipNotPlaced)
        {
            // return false; //recursive it back and try again. this function returns false.
            //unplace ships in previous calls.
            
            while(position>=0)
            {
                if(count==0) //first guy and its already not fitting no matter how you look at it
                {
                    return false;
                }
                if(count>0)
                {
                        if(myProvisoinalDirections.size()>0)
                    b.unplaceShip(myProvisionalPoints[position+numberofShipsPlaced], position, myProvisoinalDirections[position+numberofShipsPlaced]);
                    //myBadPoints.push_back(myProvisionalPoints[position]); //but if i dont push back those points, how do i make sure i am bypassing them? question qustion question. i think i just needa develop the bypasss a differenty way, b/c im not actually completely ignoring those points.
                    // myBadDirections.push_back(myProvisoinalDirections[position]); //rip misspelling.
                }
                else
                {
                    b.unplaceShip(myProvisionalPoints[position], position, myProvisoinalDirections[position]);
                }
                
                
                //actually don't need those push backs, but i might want to check something else. or should ij ust mark my board somehow with unpalce ship?
                position--;
                
            }
            //and now also, push those guys into the points that "don't work"
            
            //  myProvisionalPoints.pop_back();//get rid of the provisional, no longer useful.
            //  myProvisoinalDirections.pop_back();
            // cout<<count<<endl;
            //cout<<n<<endl;
            //cout<<position<<endl;
            position=0;
            n=game().nShips();
            //  b.display(false);
            count++;//increment the count because that was a failed attempt to recurse this route.
            
            return myRecursivePlacements(b, fiftyTries, n,position , count,numberofShipsPlaced); //the function needs to backtrack and increment call of count by 1
            
            
            
        }
        // b.display(false); //for debugging purposes.
        
        // cout<<"CALLING RECURSION"<<endl;
        if(myRecursivePlacements(b, fiftyTries, n-1,position +1 ,count,numberofShipsPlaced))
        {
            // return (myRecursivePlacements(b, fiftyTries, n-1, position+1, count));//no count up.
            return true;
        }
        else //means no good on the next ship, we have to backtrack
        {
            //unplace ships in previous calls.
            
            while(position>=0)
            {
                if(count==0) //first guy and its already not fitting no matter how you look at it
                {
                    return false;
                }
                if(count>0)
                {
                    b.unplaceShip(myProvisionalPoints[position+numberofShipsPlaced], position, myProvisoinalDirections[position+numberofShipsPlaced]);
                    //myBadPoints.push_back(myProvisionalPoints[position]); //but if i dont push back those points, how do i make sure i am bypassing them? question qustion question. i think i just needa develop the bypasss a differenty way, b/c im not actually completely ignoring those points.
                    // myBadDirections.push_back(myProvisoinalDirections[position]); //rip misspelling.
                }
                else
                {
                    b.unplaceShip(myProvisionalPoints[position], position, myProvisoinalDirections[position]);
                }
                
                
                //actually don't need those push backs, but i might want to check something else. or should ij ust mark my board somehow with unpalce ship?
                position--;
                
            }            //and now also, push those guys into the points that "don't work"
            
            //  myProvisionalPoints.pop_back();//get rid of the provisional, no longer useful.
            //  myProvisoinalDirections.pop_back();
            // cout<<count<<endl;
            //cout<<n<<endl;
            //cout<<position<<endl;
            position=0;
            n=game().nShips();
            //    b.display(false);
            count++;//increment the count because that was a failed attempt to recurse this route.
            
            return myRecursivePlacements(b, fiftyTries, n,position , count,numberofShipsPlaced); //the function needs to backtrack and increment call of count by 1
            
        }
    }
    //b.display(false);//testing purposes.
    
    return true;

    
    /*
    int p=game().rows()*game().cols();
    int sum=0;
    for(int d=0;d<game().nShips();d++)
    {
        sum+=game().shipLength(d);
    }
    if(sum>p)
    {
        return false; //checking to make sure that all the ships can infact indeed, fit on the board. if it fails the above, we know it has no chances of fitting, regardless of situation.
    }
    //if for the current position, if i traverse the whole vector temp and find for each guy of that position an unplaceable coordinate on this board, I know for sure that there is no possible configuration and must quit.
    int limit=0;
    for(int c=0;c<temp.size();c++)
    {
        if(position==temp[c].myID)
        {
            if(!temp[c].canPlace)
            {
                limit++;
            }
        }
    }
    if(limit>=2*p)
    {
        return false; // this is because we have reached the limit of tries. maybe ill need to check if i can unwind before this? idk .
    }
    //wait how about, check every possible way you can place a ship and push those onto temp, which will also be pushed onto the provisional? then check the next ones using same process? when you reach a dead end, unwind by setting the first instance of the call of canplace then into false and each one it was corresponding to as well to false.
    
    if(n==0)
    //for n!=1, then you can say get next. check if next is also ok and proceed as above. if not ok, then backtracking must occur and I must unplace a ship before placing the next ship. when i unplace the ship, i need to remind my guy here that I can't try to push that coordinate back anymore because it will fail the same way here. (slowly but surely also seeing how i might be able to count this up. i should use another int count and update that and check if int count ==50 with count starting at 0 passed by reference.
    {//ship id=0->4
        //i think i test the current one first, then move on to the next one.
        //cout<<game().nShips();
        //cout<<position<<"POSITON"<<endl;
        bool shipNotPlaced=true;
        for(int r=0;r<game().rows()&&shipNotPlaced;r++)
        {
            for(int c=0;c<game().cols()&&shipNotPlaced;c++)
            {
     
                //make a "is unique orientation" before any kind of pushing, we want to make sure that orientation is going to be a unique orientation to our temp vector.
     
     
                if(!b.placeShip(Point(r,c),position,HORIZONTAL)) //can't place it at 0 0 0 1 1 0 1 2 2 0 2 1 2 2, horizontally.
                {
     
                    
                    
                    Orientation thisPos;
                    thisPos.myD=HORIZONTAL;
                    thisPos.myP=Point(r,c);
                    thisPos.myID=position;
                    thisPos.canPlace=false;
                    
                    bool unique=true;
                    for(int d=0;d<temp.size();d++)
                    {
                        if(temp[d].myD==thisPos.myD&&temp[d].myP.r==thisPos.myP.r&&temp[d].canPlace==thisPos.canPlace&&temp[d].myID==thisPos.myID&&temp[d].myP.c==thisPos.myP.c)
                        {
                            unique=false;
                        }
                    }
                    if(unique)
                        temp.push_back(thisPos);
                    
                    if(!b.placeShip(Point(r,c),position, VERTICAL))
                    {
                        Orientation thisPos;
                        thisPos.myD=VERTICAL;
                        thisPos.myP=Point(r,c);
                        thisPos.myID=position;
                        thisPos.canPlace=false;
                        
                        bool unique=true;
                        for(int d=0;d<temp.size();d++)
                        {
                            if(temp[d].myD==thisPos.myD&&temp[d].myP.r==thisPos.myP.r&&temp[d].canPlace==thisPos.canPlace&&temp[d].myID==thisPos.myID&&temp[d].myP.c==thisPos.myP.c)
                            {
                                unique=false;
                            }
                        }
                        if(unique)
                            temp.push_back(thisPos);
                        //temp.push_back(thisPos);
                        
                    }
                    else    //vertically placeable, but not horizontally.
                    {//but double check, have i placed it here before?
                        
                        bool reRun=false;
                        for(int d=0;d<temp.size();d++)
                        {
                            if(!temp[d].canPlace&&temp[d].myP.r==r&&temp[d].myP.c==c&&temp[d].myD==VERTICAL) //at this rc, orientation matters...
                            {
                                //skip the trying to place the ships in segment below.
                                reRun=true;
                                //and unplace
                            }
                        }
                        if(!reRun)
                        {
                            Orientation thisPos;
                            thisPos.myD=VERTICAL;
                            thisPos.myP=Point(r,c);
                            thisPos.myID=position;
                            thisPos.canPlace=true;
                            temp.push_back(thisPos);
                            shipNotPlaced=false;
                            numberofShipsPlaced++;
                        }
                        else
                        {
                            b.unplaceShip(Point(r,c),position,VERTICAL);
                        }
                    }
                }
                else
                {
                    //horizontal placeable
                    //but double check, have i placed it here before?
                    bool reRun=false;
                    for(int d=0;d<temp.size();d++)
                    {
                        if(!temp[d].canPlace&&temp[d].myP.r==r&&temp[d].myP.c==c&&temp[d].myD==HORIZONTAL) //at this rc, orientation matters...
                        {
                            //skip the trying to place the ships in segment below.
                            reRun=true;
                            //and unplace
                        }
                    }
                    
                    
                    
                    //vertical technically needs 2 checks
                    if(!b.placeShip(Point(r,c),position, VERTICAL))
                    {
                        Orientation thisPos;
                        thisPos.myD=VERTICAL;
                        thisPos.myP=Point(r,c);
                        thisPos.myID=position;
                        thisPos.canPlace=false;
                        
                        bool unique=true;
                        for(int d=0;d<temp.size();d++)
                        {
                            if(temp[d].myD==thisPos.myD&&temp[d].myP.r==thisPos.myP.r&&temp[d].canPlace==thisPos.canPlace&&temp[d].myID==thisPos.myID&&temp[d].myP.c==thisPos.myP.c)
                            {
                                unique=false;
                            }
                        }
                        if(unique)
                            temp.push_back(thisPos);
                        //temp.push_back(thisPos);
                        
                    }
                    else //its vertically placeable.
                    {
                        bool reRun=false;
                        for(int d=0;d<temp.size();d++)
                        {
                            if(!temp[d].canPlace&&temp[d].myP.r==r&&temp[d].myP.c==c&&temp[d].myD==VERTICAL) //at this rc, orientation matters...
                            {
                                //skip the trying to place the ships in segment below.
                                reRun=true;
                                //and unplace
                            }
                        }
                        if(!reRun)
                        {
                            Orientation thisPos;
                            thisPos.myD=VERTICAL;
                            thisPos.myP=Point(r,c);
                            thisPos.myID=position;
                            thisPos.canPlace=true;
                            temp.push_back(thisPos);
                            shipNotPlaced=false;
                            numberofShipsPlaced++;
                        }
                        else
                        {
                            b.unplaceShip(Point(r,c),position,VERTICAL);
                        }

                    }
                    
                    
                    
                    if(!reRun) //this rerun condition already checks for me if its a unique.
                    {
                        Orientation thisPos;
                        thisPos.myD=HORIZONTAL;
                        thisPos.myP=Point(r,c);
                        thisPos.myID=position;
                        thisPos.canPlace=true;
                        temp.push_back(thisPos);
                        shipNotPlaced=false;
                        numberofShipsPlaced++;
                    }
                    else
                    {
                        b.unplaceShip(Point(r,c),position,HORIZONTAL); //this was a false alarm.
                    }
                }
            }
        }
        
        //if u can place a ship assume thats all covered. if u can't place a ship, what must happen?
        //check where i am in terms of position, and unwind, or basically unplace each ship based on position.
        // don't increment count in here, theres no oneed to, that will not be how we exit this loop in any case.
        //how we exit this loop is based on the size of myprovsionalpoints. each time a unplaceship is called on a provisional point, we have to keep it marked though so we don't go there again, actually those turn into bad points. provisonal points might get a chance. if i try to place given this one configuration and fail, i need to unwind, but still try to place based on the SAME configuration before giving up and incrementing the count.
        
        
        
        if(shipNotPlaced)
        {
            // return false; //recursive it back and try again. this function returns false.
            //unplace ships in previous calls.
            //omg so it has to be unplacing ships before returning false, but its not.... i need to somehow code that in here before its too late.
            if(position>=0)
            {
                b.display(false);
                if(temp.size()>0)
                {
                    //check to unplace a ship first before return size.
                    int limit=0;
                    for(int c=0;c<temp.size();c++)
                    {
                        if(position==temp[c].myID)
                        {
                            if(!temp[c].canPlace)
                            {
                                limit++;
                            }
                        }
                    }
                    if(limit>=2*p) //have to change p by a bit based on how much space AAAAA takes up (5, so 4x5 left is 20 so 40==limit
                    {
                        position--;
                        while(position>=0)
                        {
                            for(int c=0;c<temp.size();c++)
                            {
                                if(temp[c].canPlace==true&&temp[c].myID==position&&b.unplaceShip(temp[c].myP, temp[c].myID, temp[c].myD)) //if you can unplace the ship, we have to set that position in temp's mybool to false.
                                {
                                    b.display(false);
                                    cout<<"unplace"<<endl;
                                    temp[c].canPlace=false;
                                }
                            }
                            position=0;
                            position--;
                        }
                        return false; // this is because we have reached the limit of tries. maybe ill need to check if i can unwind before this? idk .
                    }
                    
                    
                 
                    
                }
                
                
            }
            //and now also, push those guys into the points that "don't work"
            
            //  myProvisionalPoints.pop_back();//get rid of the provisional, no longer useful.
            //  myProvisoinalDirections.pop_back();
            // cout<<count<<endl;
            //cout<<n<<endl;
            //cout<<position<<endl;
            position=0;
            n=game().nShips();
            //  b.display(false);
            // count++;//increment the count because that was a failed attempt to recurse this route.
            
            return myRecursivePlacements(b, fiftyTries, n,position , count,numberofShipsPlaced); //the function needs to
        }
        // b.display(false); //for debugging purposes.
        
        // cout<<"CALLING RECURSION"<<endl;
        if(myRecursivePlacements(b, fiftyTries, n-1,position +1 ,count,numberofShipsPlaced))
        {
            // return (myRecursivePlacements(b, fiftyTries, n-1, position+1, count));//no count up.
            return true;
        }
        else //means no good on the next ship, we have to backtrack
        {
            //unplace ships in previous calls.
            
            if(position>=0)
            {
                
                if(temp.size()>0)
                {
                    //check to unplace a ship first before return size.
                    int limit=0;
                    for(int c=0;c<temp.size();c++)
                    {
                        if(position==temp[c].myID)
                        {
                            if(!temp[c].canPlace)
                            {
                                limit++;
                            }
                        }
                    }
                    if(limit>=2*p) //have to change p by a bit based on how much space AAAAA takes up (5, so 4x5 left is 20 so 40==limit
                    {
                        position--;
                        while(position>=0)
                        {
                            for(int c=0;c<temp.size();c++)
                            {
                                if(temp[c].canPlace==true&&temp[c].myID==position&&b.unplaceShip(temp[c].myP, temp[c].myID, temp[c].myD)) //if you can unplace the ship, we have to set that position in temp's mybool to false.
                                {
                                    b.display(false);
                                    cout<<"unplace"<<endl;
                                    temp[c].canPlace=false;
                                }
                            }
                            position--;
                        }
                        position=0;
                        return false; // this is because we have reached the limit of tries. maybe ill need to check if i can unwind before this? idk .
                    }
                    
                }
                
            }
            position=0;
            n=game().nShips();
            //    b.display(false);
            //count++;//increment the count because that was a failed attempt to recurse this route.
            
            return myRecursivePlacements(b, fiftyTries, n,position , count,numberofShipsPlaced); //the function needs to backtrack and increment call of count by 1
        }
    }
    
    else //for n!=1, then you can say get next. check if next is also ok and proceed as above. if not ok, then backtracking must occur and I must unplace a ship before placing the next ship. when i unplace the ship, i need to remind my guy here that I can't try to push that coordinate back anymore because it will fail the same way here. (slowly but surely also seeing how i might be able to count this up. i should use another int count and update that and check if int count ==50 with count starting at 0 passed by reference.
    {//ship id=0->4
        //i think i test the current one first, then move on to the next one.
        //cout<<game().nShips();
        //cout<<position<<"POSITON"<<endl;
        bool shipNotPlaced=true;
        for(int r=0;r<game().rows()&&shipNotPlaced;r++)
        {
            for(int c=0;c<game().cols()&&shipNotPlaced;c++)
            {
                
                //make a "is unique orientation" before any kind of pushing, we want to make sure that orientation is going to be a unique orientation to our temp vector.
                
                
                if(!b.placeShip(Point(r,c),position,HORIZONTAL)) //can't place it at 0 0 0 1 1 0 1 2 2 0 2 1 2 2, horizontally.
                {
                    
                    
                  
                    Orientation thisPos;
                    thisPos.myD=HORIZONTAL;
                    thisPos.myP=Point(r,c);
                    thisPos.myID=position;
                    thisPos.canPlace=false;
                    
                    bool unique=true;
                    for(int d=0;d<temp.size();d++)
                    {
                        if(temp[d].myD==thisPos.myD&&temp[d].myP.r==thisPos.myP.r&&temp[d].canPlace==thisPos.canPlace&&temp[d].myID==thisPos.myID&&temp[d].myP.c==thisPos.myP.c)
                        {
                            unique=false;
                        }
                    }
                    if(unique)
                        temp.push_back(thisPos);
                    
                    if(!b.placeShip(Point(r,c),position, VERTICAL))
                    {
                        Orientation thisPos;
                        thisPos.myD=VERTICAL;
                        thisPos.myP=Point(r,c);
                        thisPos.myID=position;
                        thisPos.canPlace=false;
                        
                        bool unique=true;
                        for(int d=0;d<temp.size();d++)
                        {
                            if(temp[d].myD==thisPos.myD&&temp[d].myP.r==thisPos.myP.r&&temp[d].canPlace==thisPos.canPlace&&temp[d].myID==thisPos.myID&&temp[d].myP.c==thisPos.myP.c)
                            {
                                unique=false;
                            }
                        }
                        if(unique)
                            temp.push_back(thisPos);
                        //temp.push_back(thisPos);
                        
                    }
                    else    //vertically placeable, but not horizontally.
                    {//but double check, have i placed it here before?
                        
                        bool reRun=false;
                        for(int d=0;d<temp.size();d++)
                        {
                            if(!temp[d].canPlace&&temp[d].myP.r==r&&temp[d].myP.c==c&&temp[d].myD==VERTICAL) //at this rc, orientation matters...
                            {
                                //skip the trying to place the ships in segment below.
                                reRun=true;
                                //and unplace
                            }
                        }
                        if(!reRun)
                        {
                            Orientation thisPos;
                            thisPos.myD=VERTICAL;
                            thisPos.myP=Point(r,c);
                            thisPos.myID=position;
                            thisPos.canPlace=true;
                            temp.push_back(thisPos);
                            shipNotPlaced=false;
                            numberofShipsPlaced++;
                            cout<<"tjs"<<endl;
                        }
                        else
                        {
                            b.unplaceShip(Point(r,c),position,VERTICAL);
                        }
                    }
                }
                else
                {
                    //horizontal placeable
                    //but double check, have i placed it here before?
                    bool reRun=false;
                    for(int d=0;d<temp.size();d++)
                    {
                        if(!temp[d].canPlace&&temp[d].myP.r==r&&temp[d].myP.c==c&&temp[d].myD==HORIZONTAL) //at this rc, orientation matters...
                        {
                            //skip the trying to place the ships in segment below.
                            reRun=true;
                            //and unplace
                        }
                    }
                    
                    
                    
                    //vertical technically needs 2 checks
                    if(!b.placeShip(Point(r,c),position, VERTICAL))
                    {
                        Orientation thisPos;
                        thisPos.myD=VERTICAL;
                        thisPos.myP=Point(r,c);
                        thisPos.myID=position;
                        thisPos.canPlace=false;
                        
                        bool unique=true;
                        for(int d=0;d<temp.size();d++)
                        {
                            if(temp[d].myD==thisPos.myD&&temp[d].myP.r==thisPos.myP.r&&temp[d].canPlace==thisPos.canPlace&&temp[d].myID==thisPos.myID&&temp[d].myP.c==thisPos.myP.c)
                            {
                                unique=false;
                            }
                        }
                        if(unique)
                            temp.push_back(thisPos);
                        //temp.push_back(thisPos);
                        
                    }
                    else //its vertically placeable.
                    {
                        bool reRun=false;
                        for(int d=0;d<temp.size();d++)
                        {
                            if(!temp[d].canPlace&&temp[d].myP.r==r&&temp[d].myP.c==c&&temp[d].myD==VERTICAL) //at this rc, orientation matters...
                            {
                                //skip the trying to place the ships in segment below.
                                reRun=true;
                                //and unplace
                            }
                        }
                        if(!reRun)
                        {
                            Orientation thisPos;
                            thisPos.myD=VERTICAL;
                            thisPos.myP=Point(r,c);
                            thisPos.myID=position;
                            thisPos.canPlace=true;
                            temp.push_back(thisPos);
                            shipNotPlaced=false;
                            numberofShipsPlaced++;
                            cout<<"horizontal leak vertical"<<endl;
                        }
                        else
                        {
                            b.unplaceShip(Point(r,c),position,VERTICAL);
                        }
                        
                    }
                    
                    
                    
                    if(!reRun) //this rerun condition already checks for me if its a unique.
                    {
                        Orientation thisPos;
                        thisPos.myD=HORIZONTAL;
                        thisPos.myP=Point(r,c);
                        thisPos.myID=position;
                        thisPos.canPlace=true;
                        temp.push_back(thisPos);
                        shipNotPlaced=false;
                        numberofShipsPlaced++;
                    }
                    else
                    {
                        b.unplaceShip(Point(r,c),position,HORIZONTAL); //this was a false alarm.
                    }
                }
            }
        }
        
        //if u can place a ship assume thats all covered. if u can't place a ship, what must happen?
        //check where i am in terms of position, and unwind, or basically unplace each ship based on position.
        // don't increment count in here, theres no oneed to, that will not be how we exit this loop in any case.
        //how we exit this loop is based on the size of myprovsionalpoints. each time a unplaceship is called on a provisional point, we have to keep it marked though so we don't go there again, actually those turn into bad points. provisonal points might get a chance. if i try to place given this one configuration and fail, i need to unwind, but still try to place based on the SAME configuration before giving up and incrementing the count.
        
        
        
        if(shipNotPlaced)
        {
            // return false; //recursive it back and try again. this function returns false.
            //unplace ships in previous calls.
            //omg so it has to be unplacing ships before returning false, but its not.... i need to somehow code that in here before its too late.
            if(position>=0)
            {
                b.display(false);
                    if(temp.size()>0) //it doesn't have 0 0 vertical
                    {
                        //check to unplace a ship first before return size.
                        int limit=0;
                        for(int c=0;c<temp.size();c++)
                        {
                            if(position==temp[c].myID)
                            {
                                if(!temp[c].canPlace) // ialaredy marked that false? but where is the unplace
                                {
                                    //cout<<temp[c].myP.r<<temp[c].myP.c<<endl;
                                    limit++;
                                }
                            }
                        }
                        if(limit>=2*p) //time to unwind.
                        {
                            position--;
                            while(position>=0)
                            {
                                for(int c=0;c<temp.size();c++)
                                {
                                    if(temp[c].canPlace==true&&temp[c].myID==position&&b.unplaceShip(temp[c].myP, temp[c].myID, temp[c].myD)) //if you can unplace the ship, we have to set that position in temp's mybool to false.
                                    {
                                        b.display(false);
                                        cout<<"unplace"<<endl;
                                        temp[c].canPlace=false;
                                    }
                                }
                                position--;
                            }
                            position=0;
                            return false; // this is because we have reached the limit of tries. maybe ill need to check if i can unwind before this? idk . 
                        }

                        
                      
                        
                    }
               
                
            }
            //and now also, push those guys into the points that "don't work"
            
            //  myProvisionalPoints.pop_back();//get rid of the provisional, no longer useful.
            //  myProvisoinalDirections.pop_back();
            // cout<<count<<endl;
            //cout<<n<<endl;
            //cout<<position<<endl;
            position=0;
            n=game().nShips();
            //  b.display(false);
           // count++;//increment the count because that was a failed attempt to recurse this route.
            
            return myRecursivePlacements(b, fiftyTries, n,position , count,numberofShipsPlaced); //the function needs to
        }
        // b.display(false); //for debugging purposes.
        
        // cout<<"CALLING RECURSION"<<endl;
        if(myRecursivePlacements(b, fiftyTries, n-1,position +1 ,count,numberofShipsPlaced))
        {
            // return (myRecursivePlacements(b, fiftyTries, n-1, position+1, count));//no count up.
            return true;
        }
        else //means no good on the next ship, we have to backtrack, and retry with the same configuration IFF i still have viable options for shipID 0
        {
            //unplace ships in previous calls, i have already taken care of.
            for(int c=0;c<temp.size();c++)
            {
                if(temp[c].myID==0&&temp[c].canPlace)
                {
                    return myRecursivePlacements(b, fiftyTries, n,position , count,numberofShipsPlaced); //the function needs to backtrack and increment call of count by 1
                        //we KEEP TRYING.
                }
            }
            cout<<"i ran out of tries and im done with this bad configu"<<endl;
            return false;  //i give up theres no more configurations we need a new board.
        }
    }
    
    return true; //like a placeholder, its not going to fall here.
*/
}

bool GoodPlayer::placeShips(Board& b)   //i guess for debugging purposes, i can turn this player into a human to display his board better for me.
{
  
  
  
  
  //actually lets just make a thing where you want your ships not as clustered. a position would be considered good if there is no ship at the middle positions of the grid, so in other words for the 10x10, 2x2 middle, shouldn't be able to place ships if the ship might end up overlapping at.
  
    int fiftycount=0;

    for(int c=0;c<100;c++) //ill try this 100 times instead b/c of the limitation there.
    {
        b.block();  //part 1, blocking and unblocking is working!
        // b.display(false); //for debugging purposes.
        
        //place the ships, part 2
        //Direction d=HORIZONTAL;
        bool fiftyTries=false;
        int pos=0;
        int numberofShipsPlaced=0;
        //block it a few more times and display the resuklts to test that im actually blocking and retrying the unblock.
        //cout<<"TRIAL"<<c<<endl; should be working based on what im seeing. gj
        //b.block();
        // b.block();
        // b.display(false);
        //bool provisionalcheck=false;
        if(myRecursivePlacements(b,fiftyTries, game().nShips(),pos,fiftycount,numberofShipsPlaced)) //if success then return true.
            {
            b.unblock();

            return true;
            //double block to make it harder
            //   b.display(false);
            /*
            bool unplacedaShip=false;
            if(game().nShips()>0)
            {
                //(4 4->6 6 has a ship, thats bad)
                //use clear to check for this? nah jk
                if(game().rows()>4&&game().cols()>4)
                {//assume big enough of a game to actually worry about separating extra
                    int badRows=game().rows()-game().rows()/2;
                    int badCols=game().cols()-game().cols()/2;
                    for(int r=badRows-1;r<=badRows+1;r++)
                    {
                        for(int c=badCols-1;c<=badCols+1;c++)
                        {
                            for(int d=0;d<game().nShips();d++)
                            {
                                //if i can attack my stuff, then that means I can't
                                //bool pSH=true;
                                //bool
                                if(b.unplaceShip(Point(r,c),d,HORIZONTAL))
                                {
                                    //b.display(false);
                                    //unplace that ship
                                    unplacedaShip=true;
                                }
                                if(b.unplaceShip(Point(r,c),d,VERTICAL))
                                {
                                    unplacedaShip=true;
                                }
                                else
                                {
                                       //proceed.
                                }
                            //       }
                            }
                            
                        }
                    }
                }
             */
            }
           /* if(unplacedaShip)
            {
                //then we can't proceed, and must replace the ship and recall the recursive method.
                provisionalcheck=true;
            }
            */
            
            //b.unblock();
            //  b.display(false); //for debugging purposes.
            //part 3, unblock
            
            //part 4 , if all placeable, true, else rinse and repeat step 1. up to 50 tries. if it hasn't then return false.
            //oh ok placeships this function isn't recursive, call another function that WILL Be recursive. i guess he wants me to be implementing a diff function that is recursive to do that for me.
            /*if(provisionalcheck)
            {
                continue; //which will call unblock and replace.
            }
            else
             */
           // return true;
       // }
        // b.display(false);
        myProvisionalPoints.clear();
        myProvisoinalDirections.clear();
        myBadDirections.clear();
        myBadPoints.clear();
        temp.clear();
        if(fiftycount==0)
            fiftycount++;
        b.unblock(); //try again.
        
    }   //tests the block and unblock step 50 times. if it fails 50 times, then i giveu p .
    //before giving up, just try to see if it can still place ships given an unblocked situation...
    //b.display(false);
    for(int c=0;c<1;c++) //you got one shot to just try to fit it.
    {
       // b.block();  //no more blocking just try to fit it.
        // b.display(false); //for debugging purposes.
        
        //place the ships, part 2
        //Direction d=HORIZONTAL;
        bool fiftyTries=false;
        int fiftycount=0;
        int pos=0;
        int numberofShipsPlaced=0;
        //block it a few more times and display the resuklts to test that im actually blocking and retrying the unblock.
        //cout<<"TRIAL"<<c<<endl; should be working based on what im seeing. gj
        //b.block();
        // b.block();
        // b.display(false);
        //b.display(false);
       // cout<<game().nShips();
        //oh all the bad points are still there and we can't place anything due to that...so lets pop_Back all of that
        
        
        /*
         vector<Point> myBadPoints; //each index corresponds to like the ID of a bad point and a bad direction?
         vector<Direction> myBadDirections;
         struct Orientation
         {
         Point myP;
         Direction myD;
         int myID;
         };
         //the provisional points
         vector<Point> myProvisionalPoints; //each index corresponds to like the ID of a bad point and a bad direction?
         vector<Direction> myProvisoinalDirections;
         //1. i need a way to place all the ships first. then check if i can rearrange if it fails, each time when i need to rearrange, ill pop all the ships and i guess, change orientation then. so for now, or initial attempt is to just try to fit everything horizontally.

         */
        myBadPoints.clear();
        myBadDirections.clear();
        myProvisoinalDirections.clear();
        myProvisionalPoints.clear();
        temp.clear();
        b.clear();

        //if(myBadPoints.size()>0)
        //{
         //   cout<<"SIKE"<<endl;
        //}
        
       // cout<<"OLACE"<<endl;
        
        if(myRecursivePlacements(b,fiftyTries, game().nShips(),pos,fiftycount,numberofShipsPlaced)) //if success then return true.
        {
           // b.display(false);

            //double block to make it harder
            //   b.display(false);
            
           // b.unblock();
            //  b.display(false); //for debugging purposes.
            //part 3, unblock
           // cout<<"mediocre after all"<<endl;
            //part 4 , if all placeable, true, else rinse and repeat step 1. up to 50 tries. if it hasn't then return false.
            //oh ok placeships this function isn't recursive, call another function that WILL Be recursive. i guess he wants me to be implementing a diff function that is recursive to do that for me.
            return true;
        }
        // b.display(false);
        
        //b.unblock(); //try again.
       // b.display(false);

    }   //tests the block and unblock step 50 times. if it fails 50 times, then i giveu p .
//    return false;
    
    b.clear();
   // b.display(false);
    for (int k = 0; k < game().nShips(); k++)
    {
        //cout<<"AWFUL"<<endl;
        if ( ! b.placeShip(Point(k,0), k, HORIZONTAL))
            return false;
    }
    return true;
    
  //  return false;
    
}







Point GoodPlayer::recommendAttack() //returns a point
{
    if(currentState==STATE1)
    {
        m_lastCellAttacked=game().randomPoint(); //state 1
        
        if(attackedCells.size()>0)
        {
            //m_lastCellAttacked=game().randomPoint(); //state 1
            bool unique=false;
            while(!unique)
            {
                m_lastCellAttacked=game().randomPoint(); //state 1
                //cout<<m_lastCellAttacked.r<<m_lastCellAttacked.c<<endl;
                //cout<<"ASF"<<endl; random works, i was just having a problem in the board cpp
                //by the time all partitioned checks have been hit, i should have at least landed a shot sooooo.
                
                int countoverlap=0;
                for(int check=0;check<attackedCells.size();check++)
                {
                    for(int checkP=0;checkP<partitionedPointsCheck.size();checkP++)
                    {
                        if(partitionedPointsCheck[checkP].r==attackedCells[check].r&&partitionedPointsCheck[checkP].c==attackedCells[check].c)
                        {
                            countoverlap++;
                        }
                    }
                }
                
                for(int c=0;c<attackedCells.size();c++)
                    //while(m_lastCellAttacked==a value in the attackedCellsvector)
                {
                    bool proceed=false;
                    
                    
                    for(int d=0;d<partitionedPointsCheck.size();d++)
                    {
                        if(m_lastCellAttacked.r==partitionedPointsCheck[d].r&&partitionedPointsCheck[d].c==m_lastCellAttacked.c)
                        {
                            //then its good. we can proceed.
                            proceed=true;
                        }
                        
                    }
                    if(countoverlap==partitionedPointsCheck.size())
                    {
                        proceed=true;
                    }
                    
                    if(proceed)
                    {
                        if(m_lastCellAttacked.r==attackedCells[c].r&&m_lastCellAttacked.c==attackedCells[c].c)
                        {
                            unique=false;
                            break;
                        }
                        else
                        {
                            unique=true;
                        
                        }
                    }
                }
            }
        }
    }
    //********STATE 2*******//
    if(currentState==STATE2)
    {
       // cout<<"IM IN STATE 2"<<endl;
        
        //  bool bounded=false;
        int count=0;
        for(int c=0;c<attackedLimitedCells.size();c++)
        {
            for(int d=0;d<limitedCells.size();d++)
            {
                if(attackedLimitedCells[c].r==limitedCells[d].r&&attackedLimitedCells[c].c==limitedCells[d].r)
                {
                    count++;
                }
            }
        }
        if(count>=limitedCells.size())
        {
            currentState=STATE1;
            return recommendAttack();//recursive attack
        }
        
        int count2=0;

        //shit still needs to be unique here even though that is limited.
        if(attackedCells.size()>0)
        {
            //m_lastCellAttacked=game().randomPoint(); //state 1
            bool unique=false;
            bool actualValid=true;
            while(!unique&&count2<1001)//try this roughly 100 times, if it keeps failing, we retreat to state1 and break with a random point not attacked yet.
            {
                
                //new plan:
                //1. after recoding the vector of poss attacked cells, compare it with the coords in the other attacked cell vector to make sure no overlapping
                //2. next, throw out any overlapping. after that, make sure stay in state 2 only if still in state 2, once state 2 is over, clear the limited cells vector. use couts to make sure i guess and also print out the actual sizes etc of the vector and the coords of poss attack so i dont have to keep breakpointng just to see stuff.
                count2++;
                actualValid=true;
                m_lastCellAttacked=game().randomPoint();
                
                //cout<<m_lastCellAttacked.r<<m_lastCellAttacked.c<<endl;
                //cout<<"ASF"<<endl; random works, i was just having a problem in the board cpp
                for(int c=0;c<limitedCells.size();c++)
                    //while(m_lastCellAttacked==a value in the attackedCellsvector)
                {
                    //and if in the case size of ship is too big, what i can just do instead would be to check if size of limitedcells=size of attacklimited cells. if thats the case then ik i can just switch to state 1.
                    if(m_lastCellAttacked.r==limitedCells[c].r&&m_lastCellAttacked.c==limitedCells[c].c)
                    {
                        //cout<<"SHOT SELECTION IS"<<endl;
                        //cout<<m_lastCellAttacked.r<<m_lastCellAttacked.c<<endl;
                        
                        //after choosing the shot, i need to mark that as a no longer potential shot to choose from inside this, so i guess ill create a new vector for that too....
                        if(attackedLimitedCells.size()>0)
                        {
                            for(int d=0;d<attackedLimitedCells.size();d++)
                            {
                                if(attackedLimitedCells[d].c==m_lastCellAttacked.c&&attackedLimitedCells[d].r==m_lastCellAttacked.r)
                                {
                                    //not actually a unique, but a repeat. so don't break and unique is not true.
                                    actualValid=false;
                                }
                            }
                        }
                        if(actualValid)
                        {
                            attackedLimitedCells.push_back(m_lastCellAttacked);
                            unique=true;
                            break;  //its valid here and bcomes my shot
                        }
                    }
                    else
                    {
                        unique=false;
                    }
                } //while block
            }//if statement
            
            
            if(count2>1000)
            {
                currentState=STATE1;
           // m_lastCellAttacked=game().randomPoint(); //state 1
            
                if(attackedCells.size()>0)
                {
                //m_lastCellAttacked=game().randomPoint(); //state 1
                    bool unique=false;
                    while(!unique)
                    {
                        m_lastCellAttacked=game().randomPoint(); //state 1
                        //cout<<m_lastCellAttacked.r<<m_lastCellAttacked.c<<endl;
                        //cout<<"ASF"<<endl; random works, i was just having a problem in the board cpp
                        for(int c=0;c<attackedCells.size();c++)
                        //while(m_lastCellAttacked==a value in the attackedCellsvector)
                        {
                            if(m_lastCellAttacked.r==attackedCells[c].r&&m_lastCellAttacked.c==attackedCells[c].c)
                            {
                                unique=false;
                                break;
                            }
                            else
                            {
                                unique=true;
                            }
                        }
                    }
                }
            }
        }
    }
    //******state3****///
    if(currentState==STATE3)
    {
        cout<<"IM IN STATE 3"<<endl;
        
        //  bool bounded=false;
        int count=0;
        for(int c=0;c<attackedLimitedCells.size();c++)
        {
            for(int d=0;d<limitedCells.size();d++)
            {
                if(attackedLimitedCells[c].r==limitedCells[d].r&&attackedLimitedCells[c].c==limitedCells[d].r)
                {
                    count++;
                }
            }
        }
        if(count>=limitedCells.size())
        {
            currentState=STATE1;
            return recommendAttack();//recursive attack
        }
        
        
        //shit still needs to be unique here even though that is limited.
        if(attackedCells.size()>0)
        {
            //m_lastCellAttacked=game().randomPoint(); //state 1
            bool unique=false;
            bool actualValid=true;
            while(!unique)
            {
                
                //new plan:
                //1. after recoding the vector of poss attacked cells, compare it with the coords in the other attacked cell vector to make sure no overlapping
                //2. next, throw out any overlapping. after that, make sure stay in state 2 only if still in state 2, once state 2 is over, clear the limited cells vector. use couts to make sure i guess and also print out the actual sizes etc of the vector and the coords of poss attack so i dont have to keep breakpointng just to see stuff.
                
                actualValid=true;
                m_lastCellAttacked=game().randomPoint();
                
                //cout<<m_lastCellAttacked.r<<m_lastCellAttacked.c<<endl;
                //cout<<"ASF"<<endl; random works, i was just having a problem in the board cpp
                for(int c=0;c<limitedCells.size();c++)
                    //while(m_lastCellAttacked==a value in the attackedCellsvector)
                {
                    //and if in the case size of ship is too big, what i can just do instead would be to check if size of limitedcells=size of attacklimited cells. if thats the case then ik i can just switch to state 1.
                    if(m_lastCellAttacked.r==limitedCells[c].r&&m_lastCellAttacked.c==limitedCells[c].c)
                    {
                        //cout<<"SHOT SELECTION IS"<<endl;
                        //cout<<m_lastCellAttacked.r<<m_lastCellAttacked.c<<endl;
                        
                        //after choosing the shot, i need to mark that as a no longer potential shot to choose from inside this, so i guess ill create a new vector for that too....
                        if(attackedLimitedCells.size()>0)
                        {
                            for(int d=0;d<attackedLimitedCells.size();d++)
                            {
                                if(attackedLimitedCells[d].c==m_lastCellAttacked.c&&attackedLimitedCells[d].r==m_lastCellAttacked.r)
                                {
                                    //not actually a unique, but a repeat. so don't break and unique is not true.
                                    actualValid=false;
                                }
                            }
                        }
                        if(actualValid)
                        {
                            attackedLimitedCells.push_back(m_lastCellAttacked);
                            unique=true;
                            break;  //its valid here and bcomes my shot
                        }
                    }
                    else
                    {
                        unique=false;
                    }
                }
            }
        }
        //***state4***//
        if(currentState==STATE4)
        {
            //cout<<"IM IN STATE 2"<<endl;
            
            //  bool bounded=false;
            int count=0;
            for(int c=0;c<attackedLimitedCells.size();c++)
            {
                for(int d=0;d<limitedCells.size();d++)
                {
                    if(attackedLimitedCells[c].r==limitedCells[d].r&&attackedLimitedCells[c].c==limitedCells[d].r)
                    {
                        count++;
                    }
                }
            }
            if(count>=limitedCells.size())
            {
                currentState=STATE1;
                return recommendAttack();//recursive attack
            }
            
            
            //shit still needs to be unique here even though that is limited.
            if(attackedCells.size()>0)
            {
                //m_lastCellAttacked=game().randomPoint(); //state 1
                bool unique=false;
                bool actualValid=true;
                while(!unique)
                {
                    
                    //new plan:
                    //1. after recoding the vector of poss attacked cells, compare it with the coords in the other attacked cell vector to make sure no overlapping
                    //2. next, throw out any overlapping. after that, make sure stay in state 2 only if still in state 2, once state 2 is over, clear the limited cells vector. use couts to make sure i guess and also print out the actual sizes etc of the vector and the coords of poss attack so i dont have to keep breakpointng just to see stuff.
                    
                    actualValid=true;
                    m_lastCellAttacked=game().randomPoint();
                    
                    //cout<<m_lastCellAttacked.r<<m_lastCellAttacked.c<<endl;
                    //cout<<"ASF"<<endl; random works, i was just having a problem in the board cpp
                    for(int c=0;c<limitedCells.size();c++)
                        //while(m_lastCellAttacked==a value in the attackedCellsvector)
                    {
                        //and if in the case size of ship is too big, what i can just do instead would be to check if size of limitedcells=size of attacklimited cells. if thats the case then ik i can just switch to state 1.
                        if(m_lastCellAttacked.r==limitedCells[c].r&&m_lastCellAttacked.c==limitedCells[c].c)
                        {
                            //cout<<"SHOT SELECTION IS"<<endl;
                            //cout<<m_lastCellAttacked.r<<m_lastCellAttacked.c<<endl;
                            
                            //after choosing the shot, i need to mark that as a no longer potential shot to choose from inside this, so i guess ill create a new vector for that too....
                            if(attackedLimitedCells.size()>0)
                            {
                                for(int d=0;d<attackedLimitedCells.size();d++)
                                {
                                    if(attackedLimitedCells[d].c==m_lastCellAttacked.c&&attackedLimitedCells[d].r==m_lastCellAttacked.r)
                                    {
                                        //not actually a unique, but a repeat. so don't break and unique is not true.
                                        actualValid=false;
                                    }
                                }
                            }
                            if(actualValid)
                            {
                                attackedLimitedCells.push_back(m_lastCellAttacked);
                                unique=true;
                                break;  //its valid here and bcomes my shot
                            }
                        }
                        else
                        {
                            unique=false;
                        }
                    }
                }
            }

        }
        
    }
    
    
    
    
    
    return m_lastCellAttacked;
}

void GoodPlayer::recordAttackResult(Point p , bool  validShot ,bool  shotHit, bool  shipDestroyed ,int  shipId )
{
    /* how should i do good player
     
     1st make sure no repeating attacks
     2nd make sure that if im attacking a point, attack in a pattern as described during dinner on wednseday night. where we 
     */
    attackedCells.push_back(p); //so i dont hit again
    
    
    
    for(int r=0;r<game().rows();r+=1)
    {
        for(int c=0;c<game().cols();c+=2)
        {
            //if r==1, c starts at 1 and +=2
            if(r%2!=0&&c==0)
            {
                c++; //so we start on col 1 and go up
            }
          //  cout<<"PUSHING BACK"<<r<<c<<endl;
            partitionedPointsCheck.push_back(Point(r,c));
        }
    }
    
    
    
    
    
    
    /* //for attack
     vector<Point> attackedCells;
     vector<Point> limitedCells;
     vector<Point> attackedLimitedCells;
     Point PointofState2;
     bool state1;
     //maybe more than 1 state?
     enum state {STATE1,STATE2,STATE3};
     vector <Point> enemyAttacks;
     currentState=state1;
     */
    
    
    //state 1 is partition. ill figure that out later b/c that seems kinda hard. for now ill use a random shot.
    //state 2 will be to do +1 -1 on both top and bot, see if i get a hit. if i miss, i stay in state 2 and try other 3, then 2, then 1 shot (this will expire after i run out of stuff to shoot and retreat back to state 1.) ofc also needs to be unique shots. if i get a hit and it doesnt destroy, i go into stage 3. if i get a hit and destroy, i go back to state 1 (partition)
    //state 3 will be to continue in that direction and eliminate the other direction, either going up or down. if i went down first and miss, i know i will have to go up. if i went down and hit, i dont know if i still need to go up or down, so ill keep checking up and down. if i get a kill, i go back to state 1. once im certain about the direction of the ship, ill move to state 4 and stop shooting in either up or down.
    // state 4 will be to go only in the direction ik. if i get a kill i stop. if i dont get a kill, i keep going. if i run out of places to shoot i stop. by stop in this context, i retreat back to state 1.
    
    
   
    if(currentState==STATE1)
    {
        if(!shotHit)
        {
            currentState=STATE1;
        }
        if(shotHit&&shipDestroyed)
        {
            currentState=STATE1;
        }
        else if(shotHit&&!shipDestroyed)
        {
            currentState=STATE2;
            justSwitched=true;
           // currentState=STATE2;
        }
    }
    if(currentState==STATE2)
    {
        
        if(justSwitched)
        {
            // cout<<"YOU FUKING TRIGGERED ME to stage2"<<endl;
            justSwitched=false;
            if(limitedCells.size()>0)
            {
                for(int c=0;c<limitedCells.size();c++)
                {
                    limitedCells.pop_back();
                }
            }
            
            PointofState2=p; //4 4   0  0 point of state 2 is going to kinda be like the "focus fire point" the range of points that are chosen are nice, so i think i will keep them here. but, i will choose to fire in an evn more specific range of points and keep eliminating based on how well i go off the states.
            int rS2Left=PointofState2.r-4; //4 0    - 4 0    (my row left so -4 off grid
            int rS2Right=PointofState2.r+4;  //4 8     8  0
            int cS2Top=PointofState2.c-4; //0 4     -4   4
            int cS2Bot=PointofState2.c+4; // 8 4
            
            attackedLimitedCells.push_back(PointofState2);
            for(int c=rS2Left;c<=rS2Right;c++) // hit 1 0 , so top bot
            {
                bool canpush=true;
                for(int d=0;d<attackedCells.size();d++)
                {//if attacked cells
                    //1 0
                    if(attackedCells[d].r==c&&attackedCells[d].c==PointofState2.c)
                    {
                        canpush=false;
                    }
                    else
                    {
                        
                    }
                }
                Point tryingtoPush;
                tryingtoPush.r=c;
                tryingtoPush.c=PointofState2.c;
                if(!game().isValid(tryingtoPush))
                {
                    canpush=false;
                }
                
                //another criteria for canpush. is it 1 + or 1- from my pointofstate2?
                
                if(tryingtoPush.r!=PointofState2.r+1&&tryingtoPush.r!=PointofState2.r-1)//literally only 2 points are allowed to push, in this direction everything else is ruled out.
                { //correspond to a vertical search.
                    canpush=false;
                }
                
                
                if(canpush)
                {
                    //cout<<"pushing"<<c<<PointofState2.c<<endl;
                    limitedCells.push_back(Point(c,PointofState2.c));//coordinates for left to right
                }
            }
            for(int c=cS2Top;c<=cS2Bot;c++)
            {
                bool canpush=true;
                for(int d=0;d<attackedCells.size();d++)
                {//if attacked cells
                    
                    if(attackedCells[d].c==c&&attackedCells[d].r==PointofState2.r)
                    {
                        canpush=false;
                    }
                    else
                    {
                        
                    }
                }
                Point tryingtoPush;
                tryingtoPush.r=PointofState2.r;
                tryingtoPush.c=c;
                //cout<<"PROSPECTIVE push values are"<<tryingtoPush.r<<tryingtoPush.c<<endl;

                
                if(!game().isValid(tryingtoPush))
                {
                    canpush=false;
                }
                
                if(tryingtoPush.c!=PointofState2.c+1&&tryingtoPush.c!=PointofState2.c-1)//literally only 2 points are allowed to push, in this direction everything else is ruled out.
                {
                    //coorespond to a horizontal search.
                    canpush=false;
                }
                
                if(canpush)
                {
                    //cout<<"pushing"<<PointofState2.r<<c<<endl;
                    limitedCells.push_back(Point(PointofState2.r,c));//top to bot
                    
                }
                
                //limitedCells.push_back(Point(c,PointofState2.c));//coordinates for left to right
                //oh shoot if theres a new one u have to pop_back all the limited cells so u dont bait it .
            }
            
            
            //last but not least, if all possible checks in that area can be checked is done for, then i have to say to go back to random selection.
            
        }
        
        else //not just switched
        {
            //  cout<<"Resuming state 2 barage"<<endl;
            if(!shotHit)//miss
            {
                    //if 1st miss, i still have 3 options to explore.
                //if u miss in state 2, u can throw out the other point on the same line if there are any.
                //if(m_lastCellAttacked.r==attackedCells.back().r) //is equal to the top of the attackedcells, check the limitedCells and throw out the bad shot.
               // {
                    //throwing out horizontals
                    
               // }
                DirectionPattern.push_back(p); //this will be used to check w/ pointofSTate2 later in state 3, to make sure that I know if there is enough info to decide if i should just start attacking from one direction. if there isn't enough information, then ill have to just repeat state 2 and do another "state 2 attack".
                
            }
            else if(shotHit&&!shipDestroyed)
            {
                //activate stage 3
                Point PointofState2new=p;//rechoose a point of state 2 and compare that to original
               // cout<<"SWitch back to s2, my p is "<<PointofState2.r<<PointofState2.c<<endl;
              //  cout<<"WILL NOW ADD POINTS PARALLEL TO THIS DIRECTION."<<endl;
                //4 4 hit
                //4 3  hit so go horizontal or left only.
                //
                bool addLeft=true;
                bool addTop=true;
                if(PointofState2new.r==PointofState2.r)
                {
                    //go only horizontal. so left or right only. so only control the columns.
                    //therefore, don't add top or bot
                    addTop=false;
                }
                if(PointofState2new.c==PointofState2.c)
                {
                    addLeft=false;
                }
                
                
                int rS2Left=PointofState2new.r-2; //4 0    - 4 0    (my row left so -4 off grid
                int rS2Right=PointofState2new.r+2;  //4 8     8  0
                int cS2Top=PointofState2new.c-2; //0 4     -4   4
                int cS2Bot=PointofState2new.c+2; // 8 4
                
                attackedLimitedCells.push_back(PointofState2);
                for(int c=rS2Left;c<=rS2Right;c++) // hit 1 0 , so top bot
                {
                    bool canpush=true;
                    for(int d=0;d<attackedCells.size();d++)
                    {//if attacked cells
                        //1 0
                        if(attackedCells[d].r==c&&attackedCells[d].c==PointofState2.c)
                        {
                            canpush=false;
                        }
                        else
                        {
                            
                        }
                    }
                    Point tryingtoPush;
                    tryingtoPush.r=c;
                    tryingtoPush.c=PointofState2new.c;
                    if(!game().isValid(tryingtoPush))
                    {
                        canpush=false;
                    }
                    
                    //another criteria for canpush. is it 1 + or 1- from my pointofstate2?
                    
                    if(tryingtoPush.r!=PointofState2new.r+1&&tryingtoPush.r!=PointofState2new.r-1&&tryingtoPush.r!=PointofState2new.r+2&&tryingtoPush.r!=PointofState2new.r-2)//literally only 4 points are allowed to push, in this direction everything else is ruled out.
                    { //correspond to a vertical search.
                        canpush=false;
                    }
                    if(!addTop)
                    {
                        canpush=false;
                    }
                    
                    if(canpush)
                    {
                        cout<<"pushing"<<c<<PointofState2new.c<<endl;
                        limitedCells.push_back(Point(c,PointofState2new.c));//coordinates for left to right
                    }
                }
                for(int c=cS2Top;c<=cS2Bot;c++)
                {
                    bool canpush=true;
                    for(int d=0;d<attackedCells.size();d++)
                    {//if attacked cells
                        
                        if(attackedCells[d].c==c&&attackedCells[d].r==PointofState2new.r)
                        {
                            canpush=false;
                        }
                        else
                        {
                            
                        }
                    }
                    Point tryingtoPush;
                    tryingtoPush.r=PointofState2new.r;
                    tryingtoPush.c=c;
                    //cout<<"PROSPECTIVE push values are"<<tryingtoPush.r<<tryingtoPush.c<<endl;
                    
                    
                    if(!game().isValid(tryingtoPush))
                    {
                        canpush=false;
                    }
                    
                    if(tryingtoPush.c!=PointofState2new.c+1&&tryingtoPush.c!=PointofState2new.c-1&&tryingtoPush.c!=PointofState2new.c+2&&tryingtoPush.c!=PointofState2new.c-2)//literally only 4 points are allowed to push, in this direction everything else is ruled out.
                    {
                        //coorespond to a horizontal search.
                        canpush=false;
                    }
                    
                    if(!addLeft)
                    {
                        canpush=false;
                    }
                    
                    if(canpush)
                    {
                        cout<<"pushing"<<PointofState2new.r<<c<<endl;
                     //   cout<<"add left"<<endl;
                        limitedCells.push_back(Point(PointofState2new.r,c));//top to bot
                        
                    }
                //you just add more points in the direction of hit, which was what i was tryna do earlier in state 3.
               // currentState=STATE2;
               // justSwitched=true;
                }
            }
            
            else if(shotHit&&shipDestroyed)
            {
                currentState=STATE1;
                //probably a 2 ship length or something i was working on earlier.
            }
        }
        
        
        if(currentState==STATE3)
        {
            if(justSwitched2)
            {
                justSwitched2=false;
                //3rd stage intro
               // cout<<"NOW IM IN MY 3rd LEVEL OF TRIGGER"<<endl;
                //if size of that vector i had was 0, as in i hit everything then i go back to state 2
                if(DirectionPattern.size()==0)
                {
                    //cout<<"SIKE im going back to state 2, i dont know enough information yet"<<endl;
                    currentState=STATE2;
                    justSwitched=true;
                    //recordAttackResult(p, validShot, shotHit, shipDestroyed, shipId);
                }
                else
                {
                    bool attackHorizontal=false;
                    bool attackVertical=false;
                    int count1=0;
                    int count2=0;
                    bool count2V=false;
                    bool count2H=false;
                    for(int c=0;c<DirectionPattern.size();c++)
                    { //horizontal direction only?
                        
                        if(DirectionPattern[c].r==PointofState2.r)
                        {
                            count1++; // get that i had 2 shots missed in the direction pattern that shares same row. therefore, ik i have to go up
                        }
                        if(DirectionPattern[c].c==PointofState2.c)
                        {
                            count2++;
                        }
                        //you are guaranteed so that they can't both be nothing.
                        if(count1==2)
                        {
                            count2H=true;
                        }
                        if(count2==2)
                        {
                            count2V=true;
                        }
                        if(count2V)
                        {
                            attackHorizontal=true;
                            break;
                        }
                        if(count2H)
                        {
                            attackVertical=true;
                            break;
                            //only enqueue a vertical attack
                        }
                    }
                    
                    
                    //if neither attackvertical or attack horizontal, can only mean that we should go back to state 2 due to a hit on the edge of the board.
                    
                    if(attackHorizontal)
                    {
                        //only take in values that share the same column number, different changing r every time.
                        //start by going either 1 up or 1 down, if connect one direction fail the other, we have to go to state 4. else just repeat.
                        //same idea for attackHorizontal.
                        limitedCells.clear();
                        
                        int cS2Top=PointofState2.c-2; //0 4     -4   4
                        int cS2Bot=PointofState2.c+2; // 8 4
                        
                        
                        
                        for(int c=cS2Top;c<=cS2Bot;c++)
                        {
                            bool canpush=true;
                            for(int d=0;d<attackedCells.size();d++)
                            {//if attacked cells
                                
                                if(attackedCells[d].c==c&&attackedCells[d].r==PointofState2.r)
                                {
                                    canpush=false;
                                }
                                else
                                {
                                    
                                }
                            }
                            Point tryingtoPush;
                            tryingtoPush.r=PointofState2.r;
                            tryingtoPush.c=c;
                            //cout<<"PROSPECTIVE push values are"<<tryingtoPush.r<<tryingtoPush.c<<endl;
                            
                            
                            if(!game().isValid(tryingtoPush))
                            {
                                canpush=false;
                            }
                            
                            if(tryingtoPush.c!=PointofState2.c+1&&tryingtoPush.c!=PointofState2.c-1)//literally only 2 points are allowed to push, in this direction everything else is ruled out.
                            {
                                //coorespond to a horizontal search.
                                canpush=false;
                            }
                            
                            if(canpush)
                            {
                                cout<<"pushing"<<PointofState2.r<<c<<endl;
                                limitedCells.push_back(Point(PointofState2.r,c));//top to bot
                                
                            }
                            
                            //limitedCells.push_back(Point(c,PointofState2.c));//coordinates for left to right
                            //oh shoot if theres a new one u have to pop_back all the limited cells so u dont bait it .
                        }

                    }
                    if(attackVertical)
                    {
                        //only take in values that share the same row number, different changing r every time.
                        //start by going either 1 up or 1 down, if connect one direction fail the other, we have to go to state 4. else just repeat.
                        //same idea for attackHorizontal.
                        limitedCells.clear();
                        
                        int rS2Left=PointofState2.r-2; //4 0    - 4 0    (my row left so -4 off grid
                        int rS2Right=PointofState2.r+2;  //4 8     8  0
                        
                        
                       // attackedLimitedCells.push_back(PointofState2);
                        for(int c=rS2Left;c<=rS2Right;c++) // hit 1 0 , so top bot
                        {
                            bool canpush=true;
                            for(int d=0;d<attackedCells.size();d++)
                            {//if attacked cells
                                //1 0
                                if(attackedCells[d].r==c&&attackedCells[d].c==PointofState2.c)
                                {
                                    canpush=false;
                                }
                                else
                                {
                                    
                                }
                            }
                            Point tryingtoPush;
                            tryingtoPush.r=c;
                            tryingtoPush.c=PointofState2.c;
                            if(!game().isValid(tryingtoPush))
                            {
                                canpush=false;
                            }
                            
                            //another criteria for canpush. is it 1 + or 1- from my pointofstate2?
                            
                            if(tryingtoPush.r!=PointofState2.r+1&&tryingtoPush.r!=PointofState2.r-1)//literally only 2 points are allowed to push, in this direction everything else is ruled out.
                            { //correspond to a vertical search.
                                canpush=false;
                            }
                            if(canpush)
                            {
                                //cout<<"pushing"<<c<<PointofState2.c<<endl;
                                limitedCells.push_back(Point(c,PointofState2.c));//coordinates for left to right
                            }
                        }
                    }
                    if(!count2H&&!count2V)
                    {
                        currentState=STATE2;
                    }
                } //end of else block
            }//end of just switched.
            
            
            else
            { //not just switched
                if(!shotHit)//miss
                {
                    //if 1st miss, i still have 3 options to explore.
                    //if u miss in state 2, u can throw out the other point on the same line if there are any.
                    //if(m_lastCellAttacked.r==attackedCells.back().r) //is equal to the top of the attackedcells, check the limitedCells and throw out the bad shot.
                    // {
                    //throwing out horizontals
                    
                    // }
//                    DirectionPattern.push_back(p); //this will be used to check w/ pointofSTate2 later in state 3, to make sure that I know if there is enough info to decide if i should just start attacking from one direction. if there isn't enough information, then ill have to just repeat state 2 and do another "state 2 attack".
                    //idk?
                }
                else if(shotHit&&!shipDestroyed)
                {
                    //activate stage 3
                    currentState=STATE4;
                    justSwitched3=true;
                }
                else if(shotHit&&shipDestroyed)
                {
                    currentState=STATE1;
                    //probably a 2 ship length or something i was working on earlier.
                }

            }
            
            
            
            
            
            
        }
        if(currentState==STATE4)
        {
            if(justSwitched3)
            {
                cout<<"NOW IM IN MY LAST LEVEL OF TRIGGER PREPARE to lose soon :) . "<<endl;
            }
        }
        
    }

}

void GoodPlayer::recordAttackByOpponent(Point  p )
{
    //how should i use this to change my strategy?
    cout<<"IM RECORDING YOUR ATTACK. BESCARED OF ME, "<<name()<<"IS COMING FOR YOUR HEAD. "<<endl;
    enemyAttacks.push_back(p);
    //im not really sure what to do with this, i think the attack algorithm shouldn't depend on recording enemy attacks, but i can notify the enemy that im being attacked and that I recorded that attack so as if like, a scare tactic?? idk
    
}
// Remember that Mediocre::placeShips(Board& b) must start by calling
// b.block(), and must call b.unblock() just before returning.








//typedef AwfulPlayer GoodPlayer;

//*********************************************************************
//  createPlayer
//*********************************************************************

Player* createPlayer(string type, string nm, const Game& g)
{
    static string types[] = {
        "human", "awful", "mediocre", "good"
    };
    
    int pos;
    for (pos = 0; pos != sizeof(types)/sizeof(types[0])  &&
         type != types[pos]; pos++)
        ;
    switch (pos)
    {
        case 0:  return new HumanPlayer(nm, g);
        case 1:  return new AwfulPlayer(nm, g);
        case 2:  return new MediocrePlayer(nm, g);
        case 3:  return new GoodPlayer(nm, g);
        default: return nullptr;
    }
}
