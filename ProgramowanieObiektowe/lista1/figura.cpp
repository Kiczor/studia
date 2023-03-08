struct Figura
{
	int typfig; //1 - trojkat, 2 - kolo, 3 - kwadrat
	float x1, y1, x2, y2, x3, y3; // trojkat
	float x, y, R; // kolo
	float x1, y1, x2, y2, x3, y3, x4, y4; //kwadrat

	Figura(){}
	Figura( float a, float b, float c, float d, float e, float f )
	{
		x1 = a; y1 = b; x2 = c; y2 = d; x3 = e; y3 = f;
	}
	Figura( float a, float b, float c )
	{
		x = a, y = b, R = c;
	}

	
};

int main()
{

}
