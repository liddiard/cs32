class Piece
{
	public:
		Piece();
		virtual void display();
		virtual void fallOne();
		virtual void fallAll();
		virtual void rotateClockwise();
		virtual void rotateCounterclockwise();

	private:
		char m_piece[4][4];
}