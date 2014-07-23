#include <iostream>
#include <string>
using namespace std;

// Your declarations and implementations would go here
class Highlight
{
    public:
        Highlight(string player);
        string star() const;
        virtual string type() const = 0;
        virtual string commentary() const = 0;

    private:
        string m_star;
};

Highlight::Highlight(string star)
{
    this->m_star = star;
}

string Highlight::star() const
{
    return this->m_star;
}

class PassingPlay : public Highlight
{
    public:
        PassingPlay(string player, int yards);
        virtual string type() const;
        virtual string commentary();

    private:
        int m_yards;
};

class RunningPlay : public Highlight
{
    public:
        virtual string type() const;
        virtual string commentary() const;
};

class Interception : public Highlight
{
    public:
        Interception(string player, bool score);
        virtual string type() const;
        virtual string commentary() const;

    private:
        bool m_score;
};

PassingPlay::PassingPlay(string player, int yards) : Highlight(player)
{
    this->m_yards = yards;
}

string PassingPlay::type() const
{
    return "Passing play";
}

string PassingPlay::commentary() 
{
    char numstr[21]; // enough to hold all numbers up to 64-bits
    return "complete for " + iota(this->m_yards, numstr, 10) + " yards!"; 
}

string RunningPlay::type() const
{
    return "Running play";
}

string RunningPlay::commentary() const
{
    return "that will keep the defense honest!";
}

Interception::Interception(string player, bool score) : Highlight(player)
{
    this->m_score = score;
}

string Interception::type() const
{
    return "Interception";
}

string Interception::commentary() const
{
    if (this->m_score)
        return "Good for a score!";
    else
        return "That will change the game!";
}


void describeHighlight(const Highlight* f)
{
    cout << f->type() << " starring ";
    f->star();
    cout << endl << "Commentary: ";
    f->commentary();
    cout << endl;
}

int main()
{
    Highlight* highlights[4];
    highlights[0] = new PassingPlay("Brett", 59);
    highlights[1] = new RunningPlay("Paul");
    highlights[2] = new Interception("Jordan", false);
    highlights[3] = new Interception("Myles", true);

    for (int k = 0; k < 4; k++)
        describeHighlight(highlights[k]);

        // Clean up the files before exiting
    cout << "Cleaning up" << endl;
    for (int n = 0; n < 4; n++)
        delete highlights[n];
}
