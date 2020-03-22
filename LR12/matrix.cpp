#include "matrix.h"
#include <iostream>

#define DOUBLE_LOOP for(int i=0; i<_size; i++) for(int j=0; j<_size; j++)

void SqrMatrix::init(double **array, int size)
{
	assert(size > 0);
	_size = size;

	values = new double*[size];
	for(int i=0; i<size; i++)
		values[i] = new double[size];

	DOUBLE_LOOP {
		if(array)
			values[i][j] = array[i][j];
		else
			values[i][j] = 0;
	};
	
	calcDeterminant();
};


SqrMatrix::~SqrMatrix(void)
{
	for(int i=0; i<_size; i++) delete[] values[i];
	delete[] values;
};


//-----OPERATORS-----//

SqrMatrix SqrMatrix::operator= (SqrMatrix mx)
{
	if( _size != mx.size() ) {
		for(int i=0; i<_size; i++) delete[] values[i];
		delete[] values;

		_size = mx.size();
		values = new double*[_size];
		for(int i=0; i<_size; i++) values[i] = new double[_size]; 
	};

	DOUBLE_LOOP {
		values[i][j] = mx.values[i][j];
	};
	return *this;
};

SqrMatrix SqrMatrix::operator+ (SqrMatrix mx)
{
	assert(_size == mx.size());
	SqrMatrix ans = *this;
	
	DOUBLE_LOOP {
		ans.values[i][j] += values[i][j];
	};

	return ans;
};

SqrMatrix SqrMatrix::operator- (SqrMatrix mx)
{
	assert(_size == mx.size());
	SqrMatrix ans = *this; 
	
	DOUBLE_LOOP {
			ans.values[i][j] -= mx.values[i][j];
	};
	
	return ans;
};

SqrMatrix SqrMatrix::operator* (SqrMatrix mx)
{
	if(_size != mx.size())	{
		puts("Матрицы должны быть одного размера");
		exit(-2);
	};
	SqrMatrix ans = SqrMatrix(_size);

	DOUBLE_LOOP {
		for(int k=0; k<_size; k++)
			ans.values[i][j] += values[i][k] * mx.values[k][j]; 
	};

	return ans;
};

SqrMatrix SqrMatrix::operator/ (SqrMatrix mx)
{
	assert(_size == mx.size() && mx.get_determinant() != 0);

	return *this * mx.reverse();
};


//-----FUNCTIONS-----//


void SqrMatrix::print(void)
{
	for(int i=0; i<_size; i++) {
		for(int j=0; j<_size; j++)
		    cout << values[i][j] << ' ';
		cout << endl;
	}
};

#define SWAP \
			tmp = values[i][j];\
			values[i][j] = values[j][i];\
			values[j][i] = tmp;	
	

void SqrMatrix::transpose(void)
{
	double tmp;
	DOUBLE_LOOP {
		if(j > i) {
			SWAP
		};
	};
};

#undef SWAP

SqrMatrix SqrMatrix::reverse(void)
{
	SqrMatrix ans = *this;
		
	DOUBLE_LOOP {
		ans.values[i][j] = getAlgebraicComplement(i,j);
	};

	ans.transpose();

	return( ans / get_determinant() );
};
