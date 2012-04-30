#include "Matrix.h"

#include <cassert>
#include "string.h"

#include <iostream>
using namespace std;

Matrix::Matrix()
{
	values[0]  = values[5]  = values[10] = values[15] = 1.0;
	values[1]  = values[2]  = values[3]  = 0.0;
	values[4]  = values[6]  = values[7]  = 0.0;
	values[8]  = values[9]  = values[11] = 0.0;
	values[12] = values[13] = values[14] = 0.0;
}

void Matrix::transpose()
{
	float temp[16];
	temp[0]  = values[0];
	temp[1]  = values[4];
	temp[2]  = values[8];
	temp[3]  = values[12];
	temp[4]  = values[1];
	temp[5]  = values[5];
	temp[6]  = values[9];
	temp[7]  = values[13];
	temp[8]  = values[2];
	temp[9]  = values[6];
	temp[10]  = values[10];
	temp[11]  = values[14];
	temp[12]  = values[3];
	temp[13]  = values[7];
	temp[14]  = values[11];
	temp[15]  = values[15];

	for(int i=0; i<16; i++)
		values[i] = temp[i];
	
}

//----------------------------------------------------------------------------

Matrix::Matrix( float *values )
{
  	memcpy(this->values, values, 16*sizeof(float));
}

Matrix::Matrix( double *values )
{
  	this->values[0] = values[0];
	this->values[1] = values[1];
	this->values[2] = values[2];
	this->values[3] = values[3];
	this->values[4] = values[4];
	this->values[5] = values[5];
	this->values[6] = values[6];
	this->values[7] = values[7];
	this->values[8] = values[8];
	this->values[9] = values[9];
	this->values[10] = values[10];
	this->values[11] = values[11];
	this->values[12] = values[12];
	this->values[13] = values[13];
	this->values[14] = values[14];
	this->values[15] = values[15];
}

//----------------------------------------------------------------------------

float& Matrix::operator [] ( unsigned int entry )
{
	assert( entry <= 16 );
	
	return values[entry];
}

//----------------------------------------------------------------------------

const float& Matrix::operator [] ( unsigned int entry ) const
{
	assert( entry <= 16 );
	
	return values[entry];
}

//----------------------------------------------------------------------------

float& Matrix::operator () ( unsigned int row, unsigned int column ) 
{
  	return values[row + column*4];
}

//----------------------------------------------------------------------------

Matrix& Matrix::operator += ( const Matrix& matrix )
{
	for( unsigned int i = 0; i < 16; i++ )
		values[i] += matrix[i];
	
	return *this;
}

//----------------------------------------------------------------------------

Matrix Matrix::operator * ( const Matrix& matrix ) const
{
  	Matrix mult;

  	for( unsigned int i = 0; i < 4; i++ )
		for( unsigned int j = 0; j < 4; j++ )
		{
			mult(i,j) = 0;
			//cout << "[" << i << ", " << j << "] = ";
			for( unsigned int k = 0; k < 4; k++ )
			{
				//cout << values[k*4+i]  << "*" << matrix[j*4+k] << " + ";
				mult(i,j) += values[k*4+i]*matrix[j*4+k];
			}
			//cout << " = " << mult(i,j) << endl;
		}

  	return mult;
}

//----------------------------------------------------------------------------

Vector Matrix::operator * ( const Vector& vector ) const
{
	Vector result;
	
	for( unsigned int i = 0; i < 4; i++ )
	{
		result(i) = 0;
	
		for( unsigned int k = 0; k < 4; k++ )
		{
			result(i) += values[k*4+i]*vector(k);
			//cout<<values[k*4+i]<<"*"<<vector.pos[k]<<" ";//<<values[k*4+i]<<","<<values[k*4+i]<<endl;
		}
	}
	//cout<<endl;
	
	return result;
}

//----------------------------------------------------------------------------

Matrix& Matrix::operator = ( const Matrix& matrix ) 
{
  	for( unsigned int i = 0; i < 16; i++ )
    		values[i] = matrix[i];

  	return *this;
}

//----------------------------------------------------------------------------

std::ostream& operator<<( std::ostream& out, const Matrix& m )
{
	m.write( out );
	return out;
}

//----------------------------------------------------------------------------

void Matrix::write( std::ostream& out ) const
{
	out 	<< values[0] << " " << values[4] << " " 
		<< values[8] << " " << values[12] << endl
		<< values[1] << " " << values[5] << " " 
		<< values[9] << " " << values[13] << endl
		<< values[2] << " " << values[6] << " " 
		<< values[10] << " " << values[14] << endl
		<< values[3] << " " << values[7] << " " 
		<< values[11] << " " << values[15] << endl;
}

//----------------------------------------------------------------------------

const float* Matrix::getValues() const
{
  	return values;
}

/*
void Matrix::setValues( float *values )
{
  	memcpy(this->values, values, 16*sizeof(float));
}*/

/*
const float* Matrix::getRow(int r) const
{
	assert(r<4);
	assert(r>=0);
	if(r==0)
	{
		float row[4]={values[0], values[4], values[8], values[12]};
		return row;
	}
	
	if(r==1)
	{
		float row[4]={values[1], values[5], values[9], values[13]};
		return row;
	}
	
	if(r==2)
	{
		float row[4]={values[2], values[6], values[10], values[14]};
		return row;
	}
	
	if(r==3)
	{
		float row[4]={values[3], values[5], values[11], values[15]};
		return row;
	}

}
*/


float Matrix::Determinant4f()
{
	return
		values[12]*values[9]*values[6]*values[3]-
		values[8]*values[13]*values[6]*values[3]-
		values[12]*values[5]*values[10]*values[3]+
		values[4]*values[13]*values[10]*values[3]+
		values[8]*values[5]*values[14]*values[3]-
		values[4]*values[9]*values[14]*values[3]-
		values[12]*values[9]*values[2]*values[7]+
		values[8]*values[13]*values[2]*values[7]+
		values[12]*values[1]*values[10]*values[7]-
		values[0]*values[13]*values[10]*values[7]-
		values[8]*values[1]*values[14]*values[7]+
		values[0]*values[9]*values[14]*values[7]+
		values[12]*values[5]*values[2]*values[11]-
		values[4]*values[13]*values[2]*values[11]-
		values[12]*values[1]*values[6]*values[11]+
		values[0]*values[13]*values[6]*values[11]+
		values[4]*values[1]*values[14]*values[11]-
		values[0]*values[5]*values[14]*values[11]-
		values[8]*values[5]*values[2]*values[15]+
		values[4]*values[9]*values[2]*values[15]+
		values[8]*values[1]*values[6]*values[15]-
		values[0]*values[9]*values[6]*values[15]-
		values[4]*values[1]*values[10]*values[15]+
		values[0]*values[5]*values[10]*values[15];
}

Matrix Matrix::GenerateInverseMatrix4f()
{
	float x=this->Determinant4f();
	Matrix i;
	
	i.values[0]= (-values[13]*values[10]*values[7] +values[9]*values[14]*values[7] +values[13]*values[6]*values[11]
	-values[5]*values[14]*values[11] -values[9]*values[6]*values[15] +values[5]*values[10]*values[15])/x;
	i.values[4]= ( values[12]*values[10]*values[7] -values[8]*values[14]*values[7] -values[12]*values[6]*values[11]
	+values[4]*values[14]*values[11] +values[8]*values[6]*values[15] -values[4]*values[10]*values[15])/x;
	i.values[8]= (-values[12]*values[9]* values[7] +values[8]*values[13]*values[7] +values[12]*values[5]*values[11]
	-values[4]*values[13]*values[11] -values[8]*values[5]*values[15] +values[4]*values[9]* values[15])/x;
	i.values[12]=( values[12]*values[9]* values[6] -values[8]*values[13]*values[6] -values[12]*values[5]*values[10]
	+values[4]*values[13]*values[10] +values[8]*values[5]*values[14] -values[4]*values[9]* values[14])/x;
	i.values[1]= ( values[13]*values[10]*values[3] -values[9]*values[14]*values[3] -values[13]*values[2]*values[11]
	+values[1]*values[14]*values[11] +values[9]*values[2]*values[15] -values[1]*values[10]*values[15])/x;
	i.values[5]= (-values[12]*values[10]*values[3] +values[8]*values[14]*values[3] +values[12]*values[2]*values[11]
	-values[0]*values[14]*values[11] -values[8]*values[2]*values[15] +values[0]*values[10]*values[15])/x;
	i.values[9]= ( values[12]*values[9]* values[3] -values[8]*values[13]*values[3] -values[12]*values[1]*values[11]
	+values[0]*values[13]*values[11] +values[8]*values[1]*values[15] -values[0]*values[9]* values[15])/x;
	i.values[13]=(-values[12]*values[9]* values[2] +values[8]*values[13]*values[2] +values[12]*values[1]*values[10]
	-values[0]*values[13]*values[10] -values[8]*values[1]*values[14] +values[0]*values[9]* values[14])/x;
	i.values[2]= (-values[13]*values[6]* values[3] +values[5]*values[14]*values[3] +values[13]*values[2]*values[7]
	-values[1]*values[14]*values[7] -values[5]*values[2]*values[15] +values[1]*values[6]* values[15])/x;
	i.values[6]= ( values[12]*values[6]* values[3] -values[4]*values[14]*values[3] -values[12]*values[2]*values[7]
	+values[0]*values[14]*values[7] +values[4]*values[2]*values[15] -values[0]*values[6]* values[15])/x;
	i.values[10]=(-values[12]*values[5]* values[3] +values[4]*values[13]*values[3] +values[12]*values[1]*values[7]
	-values[0]*values[13]*values[7] -values[4]*values[1]*values[15] +values[0]*values[5]* values[15])/x;
	i.values[14]=( values[12]*values[5]* values[2] -values[4]*values[13]*values[2] -values[12]*values[1]*values[6]
	+values[0]*values[13]*values[6] +values[4]*values[1]*values[14] -values[0]*values[5]* values[14])/x;
	i.values[3]= ( values[9]* values[6]* values[3] -values[5]*values[10]*values[3] -values[9]* values[2]*values[7]
	+values[1]*values[10]*values[7] +values[5]*values[2]*values[11] -values[1]*values[6]* values[11])/x;
	i.values[7]= (-values[8]* values[6]* values[3] +values[4]*values[10]*values[3] +values[8]* values[2]*values[7]
	-values[0]*values[10]*values[7] -values[4]*values[2]*values[11] +values[0]*values[6]* values[11])/x;
	i.values[11]=( values[8]* values[5]* values[3] -values[4]*values[9]* values[3] -values[8]* values[1]*values[7]
	+values[0]*values[9]* values[7] +values[4]*values[1]*values[11] -values[0]*values[5]* values[11])/x;
	i.values[15]=(-values[8]* values[5]* values[2] +values[4]*values[9]* values[2] +values[8]* values[1]*values[6]
	-values[0]*values[9]* values[6] -values[4]*values[1]*values[10] +values[0]*values[5]* values[10])/x;
	
	return i;
} 
 
