#include "matrix.h"
#include <cassert>

#define _a_ get_value
#define DET_2x2 _a_(0,0) * _a_(1,1) - _a_(0,1) * _a_(1,0)

#define SAR_pos _a_(0,0)*_a_(1,1)*_a_(2,2) + \
				_a_(0,1)*_a_(1,2)*_a_(2,0) + \
				_a_(0,2)*_a_(1,0)*_a_(2,1)

#define SAR_neg _a_(0,2)*_a_(1,1)*_a_(2,0) + \
				_a_(0,0)*_a_(1,2)*_a_(2,1) + \
				_a_(0,1)*_a_(1,0)*_a_(2,2)

#define DET_3x3 SAR_pos - (SAR_neg)


static double laplase(SqrMatrix *mx)
{
	double ans = 0;
	for(int i=0; i<mx->size(); i++)
		ans += mx->_a_(i,0) * mx->getAlgebraicComplement(i,0);
	return ans;
};


void SqrMatrix::calcDeterminant(void)
{
	assert(_size > 0);
	switch( _size ) { 
		case 1:
			determinant = **values;
			break;
		case 2:
			determinant = DET_2x2;
			break;
		case 3:
			determinant = DET_3x3;
			break;
		default:
			determinant = laplase(this);
			break;
	};
};


//------------//


double SqrMatrix::getMinor(const int I, const int J)
{	
	assert(I+J < _size*2 && _size > 1);
	
	int tmp_i, tmp_j;
	tmp_i = tmp_j = 0;

	double **array = new double*[ _size-1 ];

	for(int i=0; i<_size; i++, tmp_j=0) {
		if( i==I ) continue;
		array[tmp_i] = new double[ _size-1 ];
		for(int j=0; j<_size; j++) {
			if( j==J ) continue;
			array[tmp_i][tmp_j++] = _a_(i,j); 
		};
		tmp_i++;
	};

	SqrMatrix ans = SqrMatrix(array, _size-1);
	for(int i=0; i<_size-1; i++) delete[] array[i];
	delete[] array;

	return ans.get_determinant();
};


double SqrMatrix::getAlgebraicComplement(const int i, const int j)
{
	if( i+j & 1 ) // -1**(i+j)
		return -1*getMinor(i,j);
	else
		return getMinor(i,j);
};
