
//fifth_degree_polynomial: Ax^5 + Bx^4.... + E
//root: 
//sine: A*sin(Bx+C)+ D 
//cosine: A*cos(Bx+C)+ D
enum equation_type
{
	fifth_degree_polynomial, root, negative, sine, cosine, exponential
};
class Formula
{
private:
	int A, B, C, D, E;
	equation_type type;
public:
	Formula()
	{
		A = 0;
		B = 0;
		C = 0;
		D = 0;
		E = 0;
	}
}