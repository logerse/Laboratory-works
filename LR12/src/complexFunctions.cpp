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


double SqrMatrix::getMinor(const int I, const int J) const
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


double SqrMatrix::getAlgebraicComplement(const int i, const int j) const
{
	if( i+j & 1 ) // -1**(i+j)
		return -1*getMinor(i,j);
	else
		return getMinor(i,j);
};


static void feelArray(double **buffer, double **array, int i, int j, int ord_)
{
  int index = 0;
  for(int r1=0; r1<ord_; r1++)
    for(int r2=0; r2<ord_; r2++) {
      buffer[r1][r2] = array[i+r1][j+r2];
    }
};


int SqrMatrix::calcRang(void) 
{

  if(_rang >= 0) return _rang;

  int flag;
  int max = 0;
  double **array;
  double det = 0;
  for(int ord=1; ord<=_size; ord++) {
    array = (double **) malloc(ord * 8);

    for(int i=0; i<ord; i++)
      array[i] = (double *) malloc(ord * sizeof(double));

    flag = 0;
    for(int i=0; i<=_size-ord; i++) {
      for(int j=0; j<=_size-ord; j++) {
        feelArray(array,values, i, j, ord);
        det = SqrMatrix(array, ord).determinant;
        if( det && max < ord ) {
          max = ord;
          flag = 1;
          break;
        };
      };
      
      if(flag) break;
    };
   
    for(int i=0; i<ord; i++)
      free(array[i]);

    free(array);
  };
 
  if(max >= 0) {
    _rang = max;
    return max;
  } else {
    return 0;
  };
};
