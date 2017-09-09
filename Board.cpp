#include "Board.h"
#include "Game.h"
#include "globals.h"
#include <iostream>
#include <vector>


//i still need to deallocate ship(?)
//i also need to implement block unblock and unplace ship
//2. next right after that i need to make sure there is no human playing like awful player

using namespace std;

class BoardImpl
{
public:
    BoardImpl(const Game& g);
    void clear();
    void block();
    void unblock();
    bool placeShip(Point topOrLeft, int shipId, Direction dir);
    bool unplaceShip(Point topOrLeft, int shipId, Direction dir); //oh so this is how i will be decrementing the ship counter and deallocating my ships! i think. 
    void display(bool shotsOnly) const;
    bool attack(Point p, bool& shotHit, bool& shipDestroyed, int& shipId);
    bool allShipsDestroyed() const;
    ~BoardImpl();
    
    
    
    
private:
    // TODO:  Decide what private members you need.  Here's one that's likely
    //        to be useful:
    int displayBoard[MAXROWS][MAXCOLS]; //we update this i guess and kinda like in proj 1 with the whole idea of "status" representing instead of rats, the types of ships.
    const Game& m_game; //m_game is likely to be useful
    int nCols;
    int nRows;
    vector<int> existingShipIDs; //update this guy for condition 5. probably globably and not in here, and gcan test it later. THIS IS ALSO HOW I THINK IM SUPPOSED TO REFERENCE THE SHIPS IDS LOL.

    //ship class will also be needed in order to place ship and unplace ship, as well as ships destroyed. so probably just like game cpp, will need ship class and a vector of ships. ACtually if iam implementing ship correctly in the other class, i technically only need it in one of them, since one of these boards has a game which should in theory also have a ship. therefore, if im good, this shouldnt be a reclass declaration.
    vector<int> destroyedShips;
    
};
//wait might actually not be able to use 0 as the water, b/c index 0 is also very likely to be a ship id.
BoardImpl::~BoardImpl()
{
    /*
    for(int c=0;c<ships.size();c++)
    {
        delete (ships[c]);
    }
     */
}
 

BoardImpl::BoardImpl(const Game& g)
: m_game(g)
{
    /*
     Initialize a board. The parameter g refers to the game the board is being used in. Board
     member functions that need to know the number of rows or columns or the characteristics
     of ships will presumably find out from the game object the board was constructed with.
     */
    //if(g>MAXCOLS)
    nRows=g.rows();
    nCols=g.cols();
    
    for(int r=0;r<nCols;r++)
    {
        for(int c=0;c<nRows;c++)
        {
            displayBoard[r][c]=-1; //set all of them to "-1" which means nothing happening. I will update displayBoard later on if there is something happening such as a "block" or a "status change w/ a ship.
        }
    }
    
}

void BoardImpl::clear()
{
    // This compiles, but may not be correct
    for (int r = 0; r < m_game.cols(); r++)
        for (int c = 0; c < m_game.rows(); c++)
        {
                displayBoard[r][c]=-1;//set it back to 0 or means unblock the cell.
        }
    
    //also have to get rid of any shipIds so basically do another nested and sweep up the ships or just pop all existent shipids
    existingShipIDs.clear();
    destroyedShips.clear();
    
}

void BoardImpl::block()
{
    // Block cells with 50% probability
    for (int r = 0; r < m_game.cols(); r++)
        for (int c = 0; c < m_game.rows(); c++)
            if (randInt(2) == 0)
            {
                displayBoard[r][c]=-2; // TODO:  Replace this with code to block cell (r,c)
            }//-2 will mean the cell is blocked. therefore, its code name for not being a ship, but also not a 0 or free spot.
}


void BoardImpl::unblock()
{
    for (int r = 0; r < m_game.cols(); r++)
        for (int c = 0; c < m_game.rows(); c++)
        {
            if(displayBoard[r][c]==-2)
            {
                displayBoard[r][c]=-1;//set it back to -1 or means unblock the cell.
            } // TODO:  Replace this with code to unblock cell (r,c) if blocked
            //oh and so thats how they get variance in their setup of the boards.
        }
}

bool BoardImpl::placeShip(Point topOrLeft, int shipId, Direction dir)
{
    //also seems like for this function, I am going to need to be placing ships based on good vs bad input, so ill need to be checking for those constraints for this.
    /*
     This function attempts to place the specified ship at the specified coordinate, in the
     specified direction. The parameter topOrLeft specifies the topmost segment of the ship if
     dir is VERTICAL, or the leftmost segment if dir is HORIZONTAL. The parameter
     shipId is the ship ID number. This function returns false if the ship cannot be placed
     because:
     1. The shipId is invalid
     2. The ship would be partly or fully outside the board.
     3. The ship would overlap an already-placed ship.
     4. The ship would overlap one or more positions that were blocked by a previous
     call to the block function.
     5. The ship with that ship ID has previously been placed on this Board and not
     yet been unplaced since its most recent placement.
     8
     If this function returns false, then the board must remain unchanged (i.e. no part of the
     ship may remain on the board upon failure). If this function successfully places the ship,
     the board is updated to reflect that, and the function returns true.
     */
   // bool shipExists=false; //assume shipId invalid unless found in our game ships.
    // there is an infinite loop here somewhere.
    //cout<<"ADDING SHIP"<<endl;
   
    //while(myShips!=m_game.nShips()) //while there are ships, should start placing them.
    //{
        
               // if(!shipExists)
       // {
        //    return false; //invalid shipId, false and say ship can't be placed.
       // }
        //sinc eshipExists is true lets implement how to push the ship onto the map
    
    if(topOrLeft.r+1>nRows||topOrLeft.c+1>nCols||topOrLeft.c<0||topOrLeft.r<0)
    {
        return false;
    }
    
        if(dir==HORIZONTAL)
        {
           // cout<<"HORIZONTALLY"<<endl;

            if(m_game.shipLength(shipId)+topOrLeft.c>nCols)//.c for cols val
            {
             //   cout<<m_game.shipLength(shipId);
             //   cout<<"RETU FALSE"<<endl;
                return false; //invalid because we step out of bounds.
            }
            else
            {
               //uh row is actually col and col is actually row, this kinda sucks
                
                
                
                    int c=topOrLeft.r; //freeze c ship length = 3 1 1 1 2 1 3
                    for(int r=topOrLeft.c;r<m_game.shipLength(shipId)+topOrLeft.c;r++) //less than ship length
                    { //also, can test to see if uh, there will be a overlap here. if it overlaps, instead of updating 1, we need to oh actually, will need to go outside this loop. we cant update if its a bad exception.
                        if(displayBoard[r][c]!=-1) //!0 means a ship space is occuping it, or a blocked square is there, and if we overlapping we can't be reaching yung blood
                        {
                          //  cout<<m_game.shipLength(shipId);
                          //  cout<<shipId;
                        //    cout<<"RET FALSE"<<endl; //calling this one when im adding one of the other ships after destroyer.

                            return false; //b/c of an overlap issue.
                        }
                    }
                
                //we update  the board...
                //since this only goes row wise or up down vertically,
               // int c=topOrLeft.c; //freeze c
                
                
                for(int c=0;c<m_game.nShips();c++)
                {
                    // cout<<"hi"<<endl;
                    if(shipId==c)
                    {
                       // cout<<"ADDING SHIP"<<m_game.shipName(shipId)<<"SHIP ID IS "<<shipId<<endl;
                        
                        //  shipExists=true;
                        for(int d=0;d<existingShipIDs.size();d++)
                        {
                            if(existingShipIDs[d]==shipId)
                            {
                                //SHIP EXISTS
                        //        cout<<"THIS SHIP EXISTS RETURNING FALSE NOW "<<endl;
                                return false;
                            }
                        }
                        existingShipIDs.push_back(c);
                        
                        //make sure we test for this later too for condition 5.
                        //this also allows me to track existing ships Ids, because im pushing in the shipid into a vector where ill be able to reference the shipid.
                    }
                }

                
                
                
                for(int r=topOrLeft.c;r<m_game.shipLength(shipId)+topOrLeft.c;r++) //less than ship length
                { //also, can test to see if uh, there will be a overlap here. if it overlaps, instead of updating 1, we need to oh actually, will need to go outside this loop. we cant update if its a bad exception.
                    displayBoard[r][c]=shipId; //honestly just call it shipId since it will all be unique and I can just map it from shipId here to its fucking char symbol.
                }
               // cout<<"SUCCESS ADDING SHIP"<<shipId<<endl;
                
                return true;
            }

        }
        if(dir==VERTICAL)
        {//top of the coordinate
          //  cout<<"VERTICALLY"<<endl;

            if(m_game.shipLength(shipId)+topOrLeft.r>nRows)//.r for row val
            {
          //      cout<<"RET FALSE"<<endl;

                return false; //invalid because we step out of bounds.
            }
            else
            {
               // bool isOverlapping=false;
                //if(!isOverlapping)
                //{
                    int r=topOrLeft.c; //freeze c
                    for(int c=topOrLeft.r;c<m_game.shipLength(shipId)+topOrLeft.r;c++) //less than ship length
                    { //also, can test to see if uh, there will be a overlap here. if it overlaps, instead of updating 1, we need to oh actually, will need to go outside this loop. we cant update if its a bad exception.
                        if(displayBoard[r][c]!=-1) //1 means a ship space is occuping it, and if we overlapping we can't be reaching yung blood
                        {
                 //           cout<<"RET FALSE"<<endl;

                            return false; //b/c of an overlap issue.
                        }
                    }
              //  }
                
                
                for(int c=0;c<m_game.nShips();c++)
                {
                    // cout<<"hi"<<endl;
                    if(shipId==c)
                    {
                      //  cout<<"ADDING SHIP"<<m_game.shipName(shipId)<<"SHIP ID IS "<<shipId<<endl;
                        
                        //  shipExists=true;
                        for(int d=0;d<existingShipIDs.size();d++)
                        {
                            if(existingShipIDs[d]==shipId)
                            {
                                //SHIP EXISTS
                         //       cout<<"THIS SHIP EXISTS RETURNING FALSE NOW "<<endl;
                                return false;
                            }
                        }
                        existingShipIDs.push_back(c);
                        
                        //make sure we test for this later too for condition 5.
                        //this also allows me to track existing ships Ids, because im pushing in the shipid into a vector where ill be able to reference the shipid.
                    }
                }

                
                //we update  the board...
                //since this only goes row wise or up down vertically,
               // int r=topOrLeft.r; //freeze c omg the code below ultimate juked me at first
                for(int c=topOrLeft.r;c<m_game.shipLength(shipId)+topOrLeft.r;c++) //less than ship length
                { //also, can test to see if uh, there will be a overlap here. if it overlaps, instead of updating 1, we need to oh actually, will need to go outside this loop. we cant update if its a bad exception.
                    displayBoard[r][c]=shipId; //1 means a ship space is occuping it.
                }
               // cout<<"SUCCESS ADDING SHIP"<<shipId<<endl;
                return true;
            }
            
        }
        
   // }
    //when you need to, check the private displayboard for any updates on possible ships and their layouts based on updating ti above, and then modify based on their mgame.getshipsymbol and yeah. thats how you would change the dsipaly. and clear would just be to litearlly turn all of that shit to nothingness. do i cnostruct the display board then in the default constructor? i think that makes sense. kinda like history in the project 1.
    

    return true; // This compiles, but may not be correct
}

bool BoardImpl::unplaceShip(Point topOrLeft, int shipId, Direction dir)
{
    /*
     This function attempts to remove the specified ship from the board, so the positions it
     occupied may be used to place other ships. The parameters are the same as for placeShip.
     This function returns false if the ship cannot be removed because:
     1. The shipId is invalid
     2. The board does not contain the entire ship at the indicated locations.
     If this function returns false, then the board must remain unchanged (i.e. no part of the
     ship may be removed upon failure). If this function successfully removes the ship, the
     board is updated to reflect that, and the function returns true.
     */
    bool shipexists=false;
   // cout<<"UNPLACING SHIPS"<<endl;
    if(topOrLeft.r+1>nRows||topOrLeft.c+1>nCols||topOrLeft.c<0||topOrLeft.r<0)
    {
        return false;
    }
    
    
  
    
    for(int c=0;c<existingShipIDs.size();c++)
    {
        
        if(existingShipIDs[c]==shipId)
        {
            //YES WE FOUND IT.dont need to mark it down.
            shipexists=true;
        }
    }
    
    
    if(shipexists)
    {
        
        if(dir==HORIZONTAL)
        {
            // cout<<"HORIZONTALLY"<<endl;
            
            if(m_game.shipLength(shipId)+topOrLeft.c>nCols)//.c for cols val
            {
                //   cout<<m_game.shipLength(shipId);
                //   cout<<"RETU FALSE"<<endl;
                return false; //invalid because we step out of bounds.
            }
            else
            {
                //uh row is actually col and col is actually row, this kinda sucks
                
                
                
                int c=topOrLeft.r; //freeze c ship length = 3 1 1 1 2 1 3
                for(int r=topOrLeft.c;r<m_game.shipLength(shipId)+topOrLeft.c;r++) //less than ship length
                { //also, can test to see if uh, there will be a overlap here. if it overlaps, instead of updating 1, we need to oh actually, will need to go outside this loop. we cant update if its a bad exception.
                    if(displayBoard[r][c]!=shipId) // means the ship was not at thel ocation said I is occuping it, or a blocked square is there, and if we overlapping we can't be reaching yung blood
                    {
                        //  cout<<m_game.shipLength(shipId);
                        //  cout<<shipId;
                        //    cout<<"RET FALSE"<<endl; //calling this one when im adding one of the other ships after destroyer.
                        
                        return false; //b/c of an issue with shipId not at specified location, but if i make it past here, then ik for sure my shipId is valid and that I can start removing the ship
                    }
                }
                
                //we update  the board...
                //since this only goes row wise or up down vertically,
                // int c=topOrLeft.c; //freeze c
                //this probably also means popping back the ship from that vector we had.
                /*
                for(int c=0;c<m_game.nShips();c++)
                {
                    // cout<<"hi"<<endl;
                    if(shipId==c)
                    {
                        // cout<<"ADDING SHIP"<<m_game.shipName(shipId)<<"SHIP ID IS "<<shipId<<endl;
                        
                        //  shipExists=true;
                        for(int d=0;d<existingShipIDs.size();d++)
                        {
                            if(existingShipIDs[d]==shipId)
                            {
                                //SHIP EXISTS
                                        cout<<"THIS SHIP EXISTS RETURNING FALSE NOW "<<endl;
                                return false;
                            }
                        }
                        existingShipIDs.push_back(c);
                        
                        //make sure we test for this later too for condition 5.
                        //this also allows me to track existing ships Ids, because im pushing in the shipid into a vector where ill be able to reference the shipid.
                    }
                }//call unplace b , then unplace a. so therefore, we are unplacing all them in order.
                 */
                
                
                
                
                for(int r=topOrLeft.c;r<m_game.shipLength(shipId)+topOrLeft.c;r++) //less than ship length
                { //also, can test to see if uh, there will be a overlap here. if it overlaps, instead of updating 1, we need to oh actually, will need to go outside this loop. we cant update if its a bad exception.
                    displayBoard[r][c]=-1; //here we area makingit go back to water. also need to update existing id to not include the uh, value of shipID
                    //hm, i can remove?
                    
                }
                 //cout<<"SUCCESS DELETING SHIP"<<shipId<<endl;
                display(false);
                
                existingShipIDs.pop_back();
                return true;
            }
            
        }
        if(dir==VERTICAL)
        {//top of the coordinate
            //  cout<<"VERTICALLY"<<endl;
            
            if(m_game.shipLength(shipId)+topOrLeft.r>nRows)//.r for row val
            {
                //      cout<<"RET FALSE"<<endl;
                
                return false; //invalid because we step out of bounds.
            }
            else
            {
                // bool isOverlapping=false;
                //if(!isOverlapping)
                //{
                int r=topOrLeft.c; //freeze c
                for(int c=topOrLeft.r;c<m_game.shipLength(shipId)+topOrLeft.r;c++) //less than ship length
                { //also, can test to see if uh, there will be a overlap here. if it overlaps, instead of updating 1, we need to oh actually, will need to go outside this loop. we cant update if its a bad exception.
                    if(displayBoard[r][c]!=shipId) //1 means a ship space is occuping it, and if we overlapping we can't be reaching yung blood
                    {
                        //           cout<<"RET FALSE"<<endl;
                        
                        return false; //b/c of an overlap issue.
                    }
                }
                //  }
                
                /*
                for(int c=0;c<m_game.nShips();c++)
                {
                    // cout<<"hi"<<endl;
                    if(shipId==c)
                    {
                        //  cout<<"ADDING SHIP"<<m_game.shipName(shipId)<<"SHIP ID IS "<<shipId<<endl;
                        
                        //  shipExists=true;
                        for(int d=0;d<existingShipIDs.size();d++)
                        {
                            if(existingShipIDs[d]==shipId)
                            {
                                //SHIP EXISTS
                                //       cout<<"THIS SHIP EXISTS RETURNING FALSE NOW "<<endl;
                                return false;
                            }
                        }
                        existingShipIDs.push_back(c);
                        
                        //make sure we test for this later too for condition 5.
                        //this also allows me to track existing ships Ids, because im pushing in the shipid into a vector where ill be able to reference the shipid.
                    }
                }
                
                 */
                
                //we update  the board...
                //since this only goes row wise or up down vertically,
                // int r=topOrLeft.r; //freeze c omg the code below ultimate juked me at first
                for(int c=topOrLeft.r;c<m_game.shipLength(shipId)+topOrLeft.r;c++) //less than ship length
                { //also, can test to see if uh, there will be a overlap here. if it overlaps, instead of updating 1, we need to oh actually, will need to go outside this loop. we cant update if its a bad exception.
                    displayBoard[r][c]=-1; //1 means a ship space is occuping it.
                }
               //  cout<<"SUCCESS DELETING SHIP"<<shipId<<endl;
                display(false);
                existingShipIDs.pop_back();
                return true;
            }
        }
    }
        /*
                    if(dir==VERTICAL)
                    {
                        //if vertical direction, then we only check the vertically and see if I can get the whole picture of the length and the whole picture of the ship. if works, then ill update it, else i return false, same drill for horizontal
                        int count=0;
                        if(m_game.shipLength(shipId)+topOrLeft.r>nRows)//.r for row val
                        {
                            return false; //invalid because we step out of bounds.
                        }
                        else
                        {
                                int r=topOrLeft.r; //freeze r
                                for(int c=topOrLeft.c;c<m_game.shipLength(shipId);c++) //less than ship length
                                { //also, can test to see if uh, there will be a overlap here. if it overlaps, instead of updating 1, we need to oh actually, will need to go outside this loop. we cant update if its a bad exception.
                                    if(displayBoard[r][c]==shipId) // means a shipID ship space is occuping it, and if we overlapping we can't be reaching yung blood
                                    {
                                        count++;
                                    }
                                }
                            
                            //we update  the board...
                            //since this only goes row wise or up down vertically,
                        }
                        if(count==m_game.shipLength(shipId))//if count matches the shipId length, then we can proceed.
                        {
                            int r=topOrLeft.r; //freeze r
                            for(int c=topOrLeft.c;c<m_game.shipLength(shipId);c++) //less than ship length
                            { //also, can test to see if uh, there will be a overlap here. if it overlaps, instead of updating 1, we need to oh actually, will need to go outside this loop. we cant update if its a bad exception.
                                displayBoard[r][c]=-1; //1 means a ship space is occuping it.
                            }
                            return true;
                        }
                      

                    }
                    if(dir==HORIZONTAL)
                    {
                        //if vertical direction, then we only check the vertically and see if I can get the whole picture of the length and the whole picture of the ship. if works, then ill update it, else i return false, same drill for horizontal
                        int count=0;
                        if(m_game.shipLength(shipId)+topOrLeft.c>nCols)//.r for row val
                        {
                            return false; //invalid because we step out of bounds.
                        }
                        else
                        {
                            int c=topOrLeft.c; //freeze r
                            for(int r=topOrLeft.r;r<m_game.shipLength(shipId);r++) //less than ship length
                            { //also, can test to see if uh, there will be a overlap here. if it overlaps, instead of updating 1, we need to oh actually, will need to go outside this loop. we cant update if its a bad exception.
                                if(displayBoard[r][c]==shipId) // means a shipID ship space is occuping it, and if we overlapping we can't be reaching yung blood
                                {
                                    count++;
                                }
                            }
                            
                            //we update  the board...
                            //since this only goes row wise or up down vertically,
                        }
                        if(count==m_game.shipLength(shipId))//if count matches the shipId length, then we can proceed.
                        {
                            int c=topOrLeft.c; //freeze r
                            for(int r=topOrLeft.r;r<m_game.shipLength(shipId);r++) //less than ship length
                            { //also, can test to see if uh, there will be a overlap here. if it overlaps, instead of updating 1, we need to oh actually, will need to go outside this loop. we cant update if its a bad exception.
                                displayBoard[r][c]=-1; //1 means a ship space is occuping it.
                            }
                            return true;
                        }
                        else
                        {
                            return false; //and dont update the board
                        }
                        
                    }
         */
    return false; // This compiles, but may not be correct
}

void BoardImpl::display(bool shotsOnly) const     //if shotsonly is true, means i am a human. I want to only see water and x until I win. only at the really end when results are posted am i allowed to see enemy board?
{
    // This compiles, but may not be correct
    //below just prints out the very basic board with nothing else on it. at least i have a board now lmao
    //char displayBoardC[nCols+3][nRows+1]; //assume for now, nRows=9, nCols=9? or nah
    char displayBoardC[MAXCOLS+3][MAXROWS+1];
    
    for(int c=0;c<nRows;c++) //for cols numbering, rows = 2
    {
        displayBoardC[0][c+1]='0'+c;
    }
    for(int c=1;c<nRows+1;c++)
    {
        displayBoardC[1][c]=' ';
    }
    for(int c=0;c<nCols;c++) //numbering for rows. row is 3 size.
    {
        displayBoardC[c+2][0]='0'+c;
    }
    
    //nrows=2
    //ncols=3
    //cout<<endl; the implementation sampel program doesnt have this line of code.
    
    
    
    cout<<"  ";//2 spaces?
    
    for(int c=0;c<nRows;c++)
    {
        for(int r=0;r<nCols;r++)
        {
            if(displayBoard[r][c]==-1) //display board maps to displayboardC plus 2 on row and col.
            {
                displayBoardC[r+2][c+1]='.';
            }
            if(displayBoard[r][c]==1000) //display board maps to displayboardC plus 2 on row and col.
            {
                displayBoardC[r+2][c+1]='o';
                
            }
            
            
            if(displayBoard[r][c]>1000) //display board maps to displayboardC plus 2 on row and col.
            {
                displayBoardC[r+2][c+1]='X';
            }
            if(displayBoard[r][c]==-2) //for mediocre players
            {
                displayBoardC[r+2][c+1]='#'; //means blocked.
            }
        }
    }
    
   
    
//if(!shotsOnly)
    {
        for(int c=0;c<nRows;c++)
        {
            for(int r=0;r<nCols;r++)
            {
               
                for(int d=0;d<m_game.nShips();d++)
                {
                   /*
                    if(r>(nRows-1)&&c==0)//special case, dont print the last 2
                    {
                        continue;
                    }
                    */
                     if(displayBoard[r][c]==d)//if its mapping to a ship id, then convert to symbol display
                    {
                    //actually after palcing all the hsips, its just the index of the shipsin the vector, which i have a size function to keep track of.
                        if(existingShipIDs.size()>d)
                        {
                            displayBoardC[r+2][c+1]=m_game.shipSymbol(existingShipIDs[d]);
                        }
                    }
                }
            }
        //endl;
        }
    }
    
    
    
    //if a ship is DAMAGED we must dispaly it as X instead.
    /*
     Remaining lines: The function must print a digit specifying the row number,
     starting at 0, followed by a space, followed by the contents of the current row,
     followed by a newline. You may assume there will be no more than 10 rows. In
     each of the positions of the row, use the following characters to represent the
     playing field:
     a. If the shotOnly parameter is false, use the ship's symbol to display an
     undamaged ship segment; if the shotsOnly parameter is true, show a
     period to display an undamaged ship segment.
     b. Use an X character to display any damaged ship segment.
     c. Use a period to display water where no attack has been made.
     d. Use a lower case letter o character to display water where an attack has
     been made that missed a ship.
     */
    
    //for hsotsonly it literally means, SHOTS ONLY LOL. so your literally only seeing water or if i hit a ship.
    
    //now use the shotsonly test to see if I shouldp lace a o or an X, X for displayBoard[r][c]!=0, and true, and a o for displayBoard[r][c]==0
    //basically the code below now doesn't seem necssary at all, ill take it out if it works.
    for(int c=0;c<nRows;c++)
    {
        for(int r=0;r<nCols;r++)
        {
           
            if(displayBoard[r][c]>1000) //a ship!
            { //so a ship. I should verify that my r and c is not going to be hitting any of the 0-9 on the cout board.
                displayBoardC[r+2][c+1]='X';
            }
            if(displayBoard[r][c]==1000) //a hit water.
            {
                displayBoardC[r+2][c+1]='o';
            }
            if(displayBoard[r][c]==-2) //for mediocre players
            {
                displayBoardC[r+2][c+1]='#'; //means blocked.
            }
        }
        //endl;
    }
    
    //how about just straight up hardcode first row, ignore the first row here, and then print rest
    
    if(!shotsOnly) //everytjing allowed
    {
        for(int c=0;c<nRows+1;c++) //1 space with number of rows
        {
            for(int r=0;r<nCols+2;r++) //should be 2 spaces due to number of cols
            {
                if(c==0&&r<2) //r>9
                {
                //cout<<r<<endl;
                    continue;
                }
           
            
                cout<<displayBoardC[r][c];
            }
            cout<<endl;
        }
    }
    if(shotsOnly) //everytjing not allowed
    {
        for(int c=0;c<nRows+1;c++) //1 space with number of rows
        {
            for(int r=0;r<nCols+2;r++) //should be 2 spaces due to number of cols
            {
                if(c==0&&r<2) //r>9
                {
                    //cout<<r<<endl;
                    continue;
                }
                if(r>1&&c>0)
                {
                    if(displayBoardC[r][c]=='X'||displayBoardC[r][c]=='o'||displayBoardC[r][c]=='.')
                    {
                        cout<<displayBoardC[r][c];
                    }
                    else
                    {
                        cout<<'.';//its just a normal water if we don't know what it is.
                    }
                }
                else
                {
                    cout<<displayBoardC[r][c]; //prints out the number of row and col
                }
                
            }
            cout<<endl;
        }
    }

}

bool BoardImpl::attack(Point p, bool& shotHit, bool& shipDestroyed, int& shipId)
{
    /*
     This function is used to submit an attack against the board. The function must return
     false if the attack is invalid (the attack point is outside of the board area, or an attack is
     made on a previously attacked location). The function returns true if the attack is valid,
     regardless of whether or not any ship is damaged.
     If any undamaged segment of a ship is at position p on the board, then the shotHit
     parameter must be set to true, and the segment must henceforth be considered a damaged
     segment. Otherwise the shotHit parameter must be set to false.
     If this specific attack destroyed the last undamaged segment of a ship, then the
     shipDestroyed parameter must be set to true and the shipId parameter must be set to the
     ship ID of the ship that was destroyed; otherwise the shipDestroyed parameter must be
     set to false and shipId must be left unchanged.
     It's up to you whether to set to some value or leave unchanged:
     1. shotHit, shipDestroyed, and shipId if the attack is invalid
     2. shipDestroyed and shipId if the attack missed     */
    
    
    //if a ship was there, and it got hit, then I HAVE TO UPDATE IT here. //maybe have a special number that rep shiphit? idk for int updating oh, shipID is passed by reference. i can get the physical ship here, and maybe update int display boards row col based on the point hit, and modify it to be like a "hit ship" version and update.
    
    if (p.r < 0  ||  p.r > nRows)
    {
        return false; //invalid on the rows.
    }
    if (p.c < 0  ||  p.c > nCols)
    {
        return false; //invalid on the cols.
    }
    //if(attacked this point before also return false)
    
    //ok if i have "hit this point of the hsip" it will be marked 1000. if a ship is on top, 1000+shipID or basically, if greater than 1000, it means i have essentially hit a ship and will mark it so that it should be displayed as a hit portion on the game board. ill worry about truncating and delting ships later.
   
    
    
    if(displayBoard[p.c][p.r]>=1000)
    {//before already visited.
        //if false the actual function, we print.
        return false;
    }
    
    
    
    //check if number is not there anymore of shipid, if it isn't we know we completely destroyed a ship.

    else
    {
        if(displayBoard[p.c][p.r]==-1)
        {
            //hit a water
            //cout<<"HIT WATER"<<endl;
            displayBoard[p.c][p.r]=1000; //version of just water
            shotHit=false; //b/c i missed the ship.
            return true;
        }
        else
        {
            //hit a ship?
            //cout<<"HIT SHIP"<<endl;
            int temp= displayBoard[p.c][p.r];//is equal to a shipID
            displayBoard[p.c][p.r]=1001+displayBoard[p.c][p.r]; //version of ship+water.
            shotHit=true; //b/c i hit a ship.
            for(int r=0;r<nCols;r++)
            {
                for(int c=0;c<nRows;c++)
                {
                    if(temp==displayBoard[r][c])
                    {
                       // cout<<displayBoard[r][c]<<endl;
                       
                        
                        //that means our shipID is still existent and no need to modify
                    //    cout<<"THOUGH U HIT MY HSIP U HAVENT DESTROYED ME YET"<<endl;
                        shipDestroyed=false;//damaged a ship but no destroy
                        return true;
                    }
                }
            }
            //at the end of this if no more, we know that the ship is destroyed.
            shipId=temp; //this is the ship that died. deallocate that ship please.
            //cout<<"ok fine u destroyed my ship"<<endl;
            destroyedShips.push_back(shipId); // another vector to keep track of ships destroyed.
            shipDestroyed=true;
            //and since this is true, we need a way to delete that shipID from the existingshipID of our vector.
            
            /*
            
            auto it=std::find(existingShipIDs.begin(),existingShipIDs.end(),shipId);
            if(it != existingShipIDs.end())
            {
             existingShipIDs.erase(it);
                //attempting to deallocate it. I think ik why it gave me that error, nothing points to the patrol boat now in the vector, so gotta probably deallocate the ship a little bit better.
            }
             */
            
        }
        
        
    }
    
    
    
    
    return true; // This compiles, but may not be correct
}

bool BoardImpl::allShipsDestroyed() const
{
    return existingShipIDs.size()==destroyedShips.size(); // This compiles, but may not be correct
}

//******************** Board functions ********************************

// These functions simply delegate to BoardImpl's functions.
// You probably don't want to change any of this code.

Board::Board(const Game& g)
{
    m_impl = new BoardImpl(g);
}

Board::~Board()
{
    delete m_impl;
}

void Board::clear()
{
    m_impl->clear();
}

void Board::block()
{
    return m_impl->block();
}

void Board::unblock()
{
    return m_impl->unblock();
}

bool Board::placeShip(Point topOrLeft, int shipId, Direction dir)
{
    return m_impl->placeShip(topOrLeft, shipId, dir);
}

bool Board::unplaceShip(Point topOrLeft, int shipId, Direction dir)
{
    return m_impl->unplaceShip(topOrLeft, shipId, dir);
}

void Board::display(bool shotsOnly) const
{
    m_impl->display(shotsOnly);
}

bool Board::attack(Point p, bool& shotHit, bool& shipDestroyed, int& shipId)
{
    return m_impl->attack(p, shotHit, shipDestroyed, shipId);
}

bool Board::allShipsDestroyed() const
{
    return m_impl->allShipsDestroyed();
}
