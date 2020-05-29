#include "matrix.h"
//#include "UI.h"

#define __SIZE__ 2

int main()
{
	double array[][__SIZE__] = {{1,2},{3,4}};
	double **ARR = new double*[__SIZE__];
	
	for(int i=0; i<__SIZE__; i++)
		ARR[i] = new double[__SIZE__];

	for(int i=0; i<__SIZE__; i++)
		for(int j=0; j<__SIZE__; j++)
			ARR[i][j] = array[i][j];

	SqrMatrix x(ARR,__SIZE__);

	double array_2[][__SIZE__] = {{4,3},{2,1}};
	for(int i=0; i<__SIZE__; i++)
		for(int j=0; j<__SIZE__; j++)
			ARR[i][j] = array_2[i][j];

	SqrMatrix y(ARR,__SIZE__);

	cout << "\nA:\n";
	x.print();
	cout << "\nB:\n";
	y.print();
	
	cout << "\nA+B\n";
	SqrMatrix z(x+y);
	z.print();

	cout << "\nA-B\n";
	SqrMatrix z1(x-y);
	z1.print();

	cout << "\nB*7\n";
	SqrMatrix z2(y*7.0);
	z2.print();
	
	cout << "\nA*B\n";
	SqrMatrix z3(x*y);
	z3.print();
	
	cout << "\nA / 2\n"; // BUG: add int and float
	SqrMatrix z4(x / 2);
	z4.print();
	
	cout << "\nA**-1\n";
	SqrMatrix z5(x.reverse());
	z5.print();
	
	cout << "\nA/B\n";
	SqrMatrix z6(x/y);
	z6.print();

	cout << "\nDeterminant A:\n";
	cout << x.get_determinant() << endl;

	for(int i=0; i<__SIZE__; i++) delete[] ARR[i];
	delete[] ARR;
	
	SqrMatrix A2(2);
	SqrMatrix A3(3);

	SqrMatrix B(A2 * A3);
	B.print();
}

#undef __SIZE__
