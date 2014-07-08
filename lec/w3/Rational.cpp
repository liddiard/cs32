class Rational
{
public:
    Rational(int numerator=0, int denominator=0);
private:
    int numerator;
    int denominator;
}

friend Rational operator*(const Rational& other)
{
    
}
