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

		SqrMatrix operator= (SqrMatrix);
		SqrMatrix operator+ (SqrMatrix);
		SqrMatrix operator- (SqrMatrix);
		SqrMatrix operator* (SqrMatrix);
		SqrMatrix operator/ (SqrMatrix);
		template <class T> 	SqrMatrix operator/ (T);
		template <class T> 	SqrMatrix operator* (T);

		void print(void);

		void transpose(void);
		double getMinor(const int, const int);		
		double getAlgebraicComplement(const int, const int);
		SqrMatrix reverse(void);		

		double get_determinant(void) { return determinant; };
		void   set_determinant(double new_dt) { determinant = new_dt; };
		void  calcDeterminant(void);		

		double get_value(int i, int j) { return values[i][j]; };
		double set_value(int i, int j, double val) { return values[i][j] = val; };

		int size(void) { return _size; };
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
