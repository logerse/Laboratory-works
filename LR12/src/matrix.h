#include <iostream>
#include <cassert>

//add const
using namespace std;


class SqrMatrix {
	public:
		SqrMatrix(int sz=DefaultSize) { init(0, sz); };
		SqrMatrix(double **array, int sz=DefaultSize) { init(array, sz); };
		SqrMatrix(const SqrMatrix& mx) { init(mx.values, mx._size); };
		~SqrMatrix(void);

		SqrMatrix operator= (SqrMatrix) const;
		SqrMatrix operator+ (SqrMatrix) const;
		SqrMatrix operator- (SqrMatrix) const;
		SqrMatrix operator* (SqrMatrix) const;
		SqrMatrix operator/ (SqrMatrix) const;
		template <class T> 	SqrMatrix operator/ (T) const;
		template <class T> 	SqrMatrix operator* (T) const;

		void print(void);

		void transpose(void);
		double getMinor(const int, const int) const;		
		double getAlgebraicComplement(const int, const int) const;
		SqrMatrix reverse(void);		

		double get_determinant(void) { return determinant; } const;
		void   set_determinant(double new_dt) { determinant = new_dt; };
		void  calcDeterminant(void);		

		double get_value(int i, int j) { return values[i][j]; } const;
		double set_value(int i, int j, double val) { return values[i][j] = val; } const;

		int size(void) { return _size; } const;
		double **values;
	private:
		int _size;
		double determinant;
		static const int DefaultSize = 3;
		void init(double **, int);
};

template <class T>
SqrMatrix SqrMatrix::operator/ (T _const) 
{
	assert( _const != 0 );
	SqrMatrix ans = *this;
	
	for(int i=0; i<_size; i++)
		for(int j=0; j<_size; j++)
			ans.values[i][j] /= _const;
	return ans;
};

template <class T>
SqrMatrix SqrMatrix::operator* (T _const) 
{
	SqrMatrix ans = *this;
	
	for(int i=0; i<_size; i++)
		for(int j=0; j<_size; j++)
			ans.values[i][j] *= _const;
	return ans;
};
