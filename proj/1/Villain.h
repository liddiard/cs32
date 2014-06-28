#ifndef VILLAIN_INCLUDED
#define VILLAIN_INCLUDED

class Colosseum;  // This is needed to let the compiler know that Colosseum is a
              // type name, since it's mentioned in the Villain declaration.

class Villain
{
  public:
      // Constructor
    Villain(Colosseum* colosseum, int r, int c);

      // Accessors
    int  row() const;
    int  col() const;
    bool isDead() const;
    

      // Mutators
    void move();
    void setDead();
    void push(int dir); // pushes this villain in this direction.

  private:
    Colosseum* m_colosseum;
    int    m_row;
    int    m_col;
    bool   m_dead;
};

#endif
