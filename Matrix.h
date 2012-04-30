#ifndef MATRIX_H
#define MATRIX_H

#include "CGMath.h"

//----------------------------------------------

/*! \brief Class implementing transformation matrices. */
class Matrix
{
 	private:
  	/*! \brief Entries of the matrix in comlumn major order. */
  	float values[16];

 	public:
		/*! \brief Constructor initialising the matrix with the identity matrix. */
		Matrix();
		/*! \brief Constructor initialising the matrix with given values. 
		*
		* \param values Values to be assigned to the matrix.
		*/
		Matrix( float *values );

		/*! \brief Constructor initialising the matrix with given values. 
		*
		* \param values Values to be assigned to the matrix.
		*/
		Matrix( double *values );
		
		/*! \brief Return a reference to the entries of the matrix. */
		const float* getValues() const;

		//void setValues( float *values );
		//const float* getRow(int r) const;
		
		/*! \brief Access operator.
		*
		* This operator can only be used with one entry. Thus, entries have to be
		* addressed directly with values in the range 0 to 15. The matrix is 
		* column order.
		*
		* \param entry Id of the entry to get.
		*/
		float& operator [] ( unsigned int entry );
		
		/*! \brief Constant access operator.
		*
		* This operator can only be used with one entry. Thus, entries have to be
		* addressed directly with values in the range 0 to 15. The matrix is 
		* column order.
		*
		* \param entry Id of the entry to get.
		*/
		const float& operator [] ( unsigned int entry ) const;
		
		/*! \brief Access operator.
		*
		* The operator takes two arguments, the row and the column of the entry to
		* accessed.
		*
		* \param row Row of the entry.
		* \param column Column of the entry.
		*/
		float& operator () ( unsigned int row, unsigned int column );
		
		/*! \brief Matrix addition operator.
		*
		* \param matrix Matrix to be added to the current one.
		*/
		Matrix& operator += ( const Matrix& matrix );
		
		/*! \brief Matrix multiplication operator.
		*
		* \param matrix Second matrix for multiplication.
		*/
		Matrix operator * ( const Matrix& matrix ) const;
		
		/*! \brief Multiply a matrix by a vector.
		*
		* \param matrix Vector for multiplication.
		*/
		Vector operator * ( const Vector& vector ) const;
		
		/*! \brief Matrix assignment operator.
		*
		* \param matrix Matrix assigned to the current one. 
		*/
		Matrix& operator = ( const Matrix& matrix );
		
		/*! \brief Output operator to pipe matrices to cout.  */
		friend std::ostream& operator<<( std::ostream& out, const Matrix& v );
		
		Matrix GenerateInverseMatrix4f();
		
		void transpose();
			
		/*! \brief Method telling how a matrix is represented in output.*/
		void write( std::ostream& out ) const;
		
	private:
		
		float Determinant4f();
};

#endif

