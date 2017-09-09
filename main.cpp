#include "Game.h"
#include "Player.h"
#include <iostream>
#include <string>

using namespace std;

bool addStandardShips(Game& g)
{
    return g.addShip(5, 'A', "aircraft carrier")  &&
    g.addShip(4, 'B', "battleship")  &&
    g.addShip(3, 'D', "destroyer")  &&
    g.addShip(3, 'S', "submarine")  &&
    g.addShip(2, 'P', "patrol boat");
}

int main()
{
    const int NTRIALS = 100;
    
    cout << "Select one of these choices for an example of the game:" << endl;
    cout << "  1.  A mini-game between two mediocre players" << endl;
    cout << "  2.  A mediocre player against a human player" << endl;
    cout << "  3.  A " << NTRIALS
    << "-game match between a mediocre and an awful player, with no pauses"
    << endl;
    cout<<"  4.  An awful player against an awful player" <<endl;
    cout<<"  5.  An awful player against a human player" <<endl;
    cout<<"  6.  A mini-game between an awful player and a human player" <<endl;
    cout<<"  7.  A 3 ship-game between an mediocre player and an mediocre player" <<endl;
    cout << "  8.  A mediocre player against a good player" << endl;
    cout << "  9.  A " << NTRIALS
    << "-game match between a mediocre and a good player, with no pauses"
    << endl;
    cout << "  a.  A good player against a human player" << endl;
    cout << "  b.  A good player against a good player, after having some hard times placing ships" << endl;
    cout << "  c.  A mediocre player against a mediocre player, after having some hard times placing ships" << endl;

    cout << "Enter your choice: ";
    string line;
    getline(cin,line);
    if (line.empty())
    {
        cout << "You did not enter a choice" << endl;
    }
    else if (line[0] == '1')
    {
        Game g(2, 3);
        g.addShip(2, 'R', "rowboat");
        Player* p1 = createPlayer("mediocre", "Popeye", g);
        Player* p2 = createPlayer("mediocre", "Bluto", g);
        cout << "This mini-game has one ship, a 2-segment rowboat." << endl;
        g.play(p1, p2);
        delete p1;
        delete p2;
    }
    else if (line[0] == '2')
    {
        Game g(10, 10);
        addStandardShips(g);
        Player* p1 = createPlayer("mediocre", "Mediocre Midorima", g);
        Player* p2 = createPlayer("human", "Shuman the Human", g);
        g.play(p1, p2);
        delete p1;
        delete p2;
    }
    else if (line[0] == '3')
    {
        int nMediocreWins = 0;
        
        for (int k = 1; k <= NTRIALS; k++)
        {
            cout << "============================= Game " << k
            << " =============================" << endl;
            Game g(10, 10);
            addStandardShips(g);
            Player* p1 = createPlayer("awful", "Awful Audrey", g);
            Player* p2 = createPlayer("mediocre", "Mediocre Mimi", g);
            Player* winner = (k % 2 == 1 ?
                              g.play(p1, p2, false) : g.play(p2, p1, false));
            if (winner == p2)
                nMediocreWins++;
            delete p1;
            delete p2;
        }
        cout << "The mediocre player won " << nMediocreWins << " out of "
        << NTRIALS << " games." << endl;
        // We'd expect a mediocre player to win most of the games against
        // an awful player.  Similarly, a good player should outperform
        // a mediocre player.
    }
    else if (line[0] == '4')
    {
        Game g(10, 10);
        addStandardShips(g);
        Player* p1 = createPlayer("awful", "Awful Andy", g);
        Player* p2 = createPlayer("awful", "Awful Annie", g);
        g.play(p1, p2);
        delete p1;
        delete p2;
    }
    else if (line[0] == '5')
    {
        Game g(10, 10);
        addStandardShips(g);
        Player* p1 = createPlayer("awful", "Awful (Destroy all Humans)Selena", g);
        Player* p2 = createPlayer("human", "Emily the Human", g);
        g.play(p1, p2);
        delete p1;
        delete p2;
    }
    else if (line[0] == '6')
    {
        Game g(2, 3);
        g.addShip(2, 'R', "rowboat");
        Player* p1 = createPlayer("awful", "Awful (Destroy all Humans)Selena", g);
        Player* p2 = createPlayer("human", "Emily the Human", g);
        g.play(p1, p2);
        delete p1;
        delete p2;
    }
    else if (line[0] == '7')
    {
        Game g(7, 7);
        g.addShip(2, 'R', "rowboat");
        g.addShip(3, 'S', "submarine");
        g.addShip(4, 'B', "battleship");

        Player* p1 = createPlayer("mediocre", "Mediocre Medli the Monster", g);
        Player* p2 = createPlayer("mediocre", "Mediocre Magnus the Minotaur", g);
        g.play(p1, p2);
        delete p1;
        delete p2;
    }
    else if (line[0] == '8')
    {
        Game g(10, 10);
        addStandardShips(g);
        Player* p1 = createPlayer("mediocre", "Mediocre Mei", g);
        Player* p2 = createPlayer("good", "Good Genji", g);
        g.play(p1, p2);
        delete p1;
        delete p2;
    }
    else if (line[0] == '9')
    {
        int nMediocreWins = 0;
        
        for (int k = 1; k <= NTRIALS; k++)
        {
            cout << "============================= Game " << k
            << " =============================" << endl;
            Game g(10, 10);
            addStandardShips(g);
            Player* p1 = createPlayer("mediocre", "Mediocre Mycroft", g);
            Player* p2 = createPlayer("good", "Good Georgios", g);
            Player* winner = (k % 2 == 1 ?
                              g.play(p1, p2, false) : g.play(p2, p1, false));
            if (winner == p2)
                nMediocreWins++;
            delete p1;
            delete p2;
        }
        cout << "The Good player won " << nMediocreWins << " out of "
        << NTRIALS << " games." << endl;
        // We'd expect a mediocre player to win most of the games against
        // an awful player.  Similarly, a good player should outperform
        // a mediocre player.
    }
    else if (line[0] == 'a')
    {
        Game g(10, 10);
        addStandardShips(g);
        Player* p1 = createPlayer("good", "Good God Gragas Bragas", g);
        Player* p2 = createPlayer("human", "You, the Human", g);
        g.play(p1, p2);
        delete p1;
        delete p2;
    }
    else if (line[0] == 'b')
    {
        //it should be able to place on a 5 by 5
        Game g(5, 5);
        addStandardShips(g);
        Player* p1 = createPlayer("good", "Good Garen", g);
        Player* p2 = createPlayer("good", "Good Guy Gee", g);
        g.play(p1, p2);
        delete p1;
        delete p2;
    }
    else if (line[0] == 'c')
    {
        //it should be able to place on a 5 by 5
        Game g(5, 5);
        addStandardShips(g);
        Player* p1 = createPlayer("mediocre", "MEDIOCRE Good Garen", g);
        Player* p2 = createPlayer("mediocre", "MEDIOCRE Good Guy Gee", g);
        g.play(p1, p2);
        delete p1;
        delete p2;
    }
    else
    {
        cout << "That's not one of the choices." << endl;
    }
}
