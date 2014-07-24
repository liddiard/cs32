#include <iostream>
#include <string>
using namespace std;

// Your declarations and implementations would go here
class Highlight
{
    public:
        Highlight(string player);
        virtual ~Highlight();
        void star() const;
        virtual string type() const = 0;
        virtual void commentary() const = 0;

    private:
        string m_star;
};

Highlight::Highlight(string star)
{
    this->m_star = star;
}

Highlight::~Highlight() {}

void Highlight::star() const
{
    cout << this->m_star;
}

class PassingPlay : public Highlight
{
    public:
        PassingPlay(string player, int yards);
        ~PassingPlay();
        virtual string type() const;
        virtual void commentary() const;

    private:
        int m_yards;
};

class RunningPlay : public Highlight
{
    public:
        RunningPlay(string player);
        ~RunningPlay();
        virtual string type() const;
        virtual void commentary() const;
};

class Interception : public Highlight
{
    public:
        Interception(string player, bool score);
        ~Interception();
        virtual string type() const;
        virtual void commentary() const;

    private:
        bool m_score;
};

PassingPlay::PassingPlay(string player, int yards) : Highlight(player)
{
    this->m_yards = yards;
}

PassingPlay::~PassingPlay() {}

string PassingPlay::type() const
{
    return "Passing play";
}

void PassingPlay::commentary() const
{
    cout << "complete for " << this->m_yards << " yards!";
}

RunningPlay::RunningPlay(string player) : Highlight(player) {}

RunningPlay::~RunningPlay() {}

string RunningPlay::type() const
{
    return "Running play";
}

void RunningPlay::commentary() const
{
    cout << "that will keep the defense honest!";
}

Interception::Interception(string player, bool score) : Highlight(player)
{
    this->m_score = score;
}

Interception::~Interception() {}

string Interception::type() const
{
    return "Interception";
}

void Interception::commentary() const
{
    if (this->m_score)
        cout << "Good for a score!";
    else
        cout << "That will change the game!";
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
