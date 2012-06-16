#include <GL/glew.h>
#include "Model.h"


Model::Model(int name, vector<Vector> vectors, vector<Face> faces, vector<Vector> normals, vector<Mesh> meshes, vector<Material> materials, vector<Vector> tex_coords)
{
	this->name = name;
	this->meshes = meshes;
	this->faces = faces;
	this->materials = materials;
	this->normals = normals;
	this->vectors = vectors;
	this->tex_coords = tex_coords;
	calcCenter();
	initDisplayLists();

}

int Model::getName()
{
	return name;
}

Model::~Model()
{
	for (unsigned int i=0;i<materials.size();++i)
	{
		if (materials[i].isTexture)
			glDeleteTextures( 1, &(materials[i].tex_id) );
		//delete[] textures[i].data;
	}
	glDeleteLists(displayList,1);
	meshes.clear();
	faces.clear();
	materials.clear();
	normals.clear();
	vectors.clear();
	tex_coords.clear();
}

void Model::calcCenter()
{
	float minX, minY, minZ, maxX, maxY, maxZ;
	minX = vectors[0](0);
	maxX = vectors[0](0);
	minY = vectors[0](1);
	maxY = vectors[0](1);
	minZ = vectors[0](2);
	maxZ = vectors[0](2);

	for (size_t i=1;i<vectors.size();++i)
	{
		if (vectors[i](0) < minX)
			minX = vectors[i](0);
		if (vectors[i](0) > maxX)
			maxX = vectors[i](0);
		if (vectors[i](1) < minY)
			minY = vectors[i](1);
		if (vectors[i](1) > maxY)
			maxY = vectors[i](1);
		if (vectors[i](2) < minZ)
			minZ = vectors[i](2);
		if (vectors[i](2) > maxZ)
			maxZ = vectors[i](2);		
	}
	
	center = Vector(minX+fabs(maxX-minX)*0.5, minY+fabs(maxY-minY)*0.5, minZ+fabs(maxZ-minZ)*0.5);
}

Vector Model::getCenter()
{
	return center;
}

void Model::rotate( Vector axis, float angle )
{
    
	axis.normalize();
	float vals[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

	glPushMatrix();
	glLoadIdentity();
	glRotatef( angle, axis(0), axis(1), axis(2) );
	glGetFloatv(GL_MODELVIEW_MATRIX, vals);
	glPopMatrix();
	
	Matrix m(vals);
	trafoMatrix = m*trafoMatrix;
	rotateMatrix = m*rotateMatrix;
	center = m * center;
}


//----------------------------------------------------------------------------

void Model::translate(double dx, double dy, double dz )
{
	float vals[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	
	glPushMatrix();
	glLoadIdentity();
	glTranslatef( dx, dy, dz );
	glGetFloatv(GL_MODELVIEW_MATRIX, vals);
	glPopMatrix();
	
	Matrix m(vals);
	trafoMatrix = m*trafoMatrix;
	translateMatrix = m*translateMatrix;
	center = m*center;

}

//----------------------------------------------------------------------------

void Model::translateTo(double dx, double dy, double dz )
{
	float vals[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	//first translate the min,max
	glPushMatrix();
	glLoadIdentity();
	//clean all transformations
	glTranslatef( dx-center(0),dy-center(1), dz-center(2) );
	glGetFloatv(GL_MODELVIEW_MATRIX, vals);
	glPopMatrix();
	
	Matrix m(vals);
	trafoMatrix = m*trafoMatrix;
	translateMatrix = m*translateMatrix;
	center = Vector(dx, dy, dz);
}

//----------------------------------------------------------------------------

void Model::scale( double sx, double sy, double sz )
{
  
	float vals[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	
	glPushMatrix();
	glLoadIdentity();
	glScalef( sx, sy, sz );
	glGetFloatv(GL_MODELVIEW_MATRIX, vals);
	glPopMatrix();
	
	Matrix m(vals);
	trafoMatrix = m * trafoMatrix;
	scaleMatrix = m * scaleMatrix;
	center = m * center;
}

//----------------------------------------------------------------------------

void Model::transform( const Matrix& matrix )
{
	trafoMatrix = matrix*trafoMatrix;
}
/*
const Matrix& Model::getTransformations() const
{
  	return trafoMatrix;
}
*/
void Model::draw(int selectedName)
{
	glPushMatrix();
	//glMultMatrixf( (translateMatrix*rotateMatrix).getValues() );
	glMultMatrixf( trafoMatrix.getValues() );
	glEnable(GL_NORMALIZE);
	if (selectedName==name) //set diffuse color if the model is selected (or not)	
		glCallList(greyDisplayList);
	else	
		glCallList(displayList);
	
	//initDisplayLists();
	glDisable(GL_NORMALIZE);
	glPopMatrix();
}

void Model::initDisplayLists()
{
	displayList = glGenLists(1);
	glNewList(displayList,GL_COMPILE);
	//first draw everything that is fully visible
	for (unsigned int i=0;i<meshes.size();++i)
	{
		if (!isTransparent(materials[meshes[i].material]))
		{
			glDisable(GL_BLEND);		// Turn Blending Off
			glEnable(GL_DEPTH_TEST);
			glDisable(GL_COLOR_MATERIAL);
			glDisable(GL_TEXTURE_2D);
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, materials[meshes[i].material].ambient );
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, materials[meshes[i].material].diffuse);
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, materials[meshes[i].material].specular );
			glMaterialf(GL_FRONT, GL_SHININESS, materials[meshes[i].material].shininess );
			if (materials[meshes[i].material].isTexture)
			{
				glEnable(GL_TEXTURE_2D);
				glActiveTextureARB(GL_TEXTURE0_ARB);
				glBindTexture(GL_TEXTURE_2D, materials[meshes[i].material].tex_id);
				if (materials[meshes[i].material].hasNormalMap)
				{
					glActiveTextureARB(GL_TEXTURE1_ARB);
					glBindTexture(GL_TEXTURE_2D, materials[meshes[i].material].tex_id);
				}
			}				
			for (unsigned int j=0;j<meshes[i].faces.size();++j)
			{
				glBegin(GL_POLYGON);
				for (unsigned int k=0;k<faces[meshes[i].faces[j]].vectors.size();++k)
				{
					if (!normals.empty()>0) //just prevents a crash but looks pretty ugly
						glNormal3fv(normals[faces[meshes[i].faces[j]].normals[k]].getValues() );
					else //use plane normal
					{
						Vector v1 = vectors[faces[meshes[i].faces[j]].vectors[0]];
						Vector v2 = vectors[faces[meshes[i].faces[j]].vectors[1]];
						Vector v3 = vectors[faces[meshes[i].faces[j]].vectors[2]];
						glNormal3fv(crossProduct( (v2 - v1), (v3 - v1) ).getValues() );
					}
					if (materials[meshes[i].material].isTexture)
						glTexCoord2f(tex_coords[faces[meshes[i].faces[j]].tex_coords[k]](0), tex_coords[faces[meshes[i].faces[j]].tex_coords[k]](1));
					else
						glTexCoord2f(-1.0,-1.0);
					glVertex3fv( (vectors[faces[meshes[i].faces[j]].vectors[k]]).getValues() );
				}
				glEnd();
			}
			glActiveTextureARB(GL_TEXTURE0_ARB);
		}				
	}

	//now draw everything that is only partly visible
	for (unsigned int i=0;i<meshes.size();++i)
	{
		
		if (isTransparent(materials[meshes[i].material]))
		{
			glDisable(GL_COLOR_MATERIAL);
			glEnable(GL_BLEND);		// Turn Blending On
			//TODO: we need different blend functions for textures and pure materials
			//because textures are translucent only at some parts
			//whereas a translucent material is translucent everywhere 
			glBlendFunc (GL_DST_COLOR, GL_SRC_COLOR);
			glDisable(GL_TEXTURE_2D);
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, materials[meshes[i].material].ambient );
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, materials[meshes[i].material].diffuse);
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, materials[meshes[i].material].specular );
			glMaterialf(GL_FRONT, GL_SHININESS, materials[meshes[i].material].shininess );
			if (materials[meshes[i].material].isTexture)
			{
				glEnable(GL_TEXTURE_2D);
				glActiveTextureARB(GL_TEXTURE0_ARB);
				glBindTexture(GL_TEXTURE_2D, materials[meshes[i].material].tex_id);
				if (materials[meshes[i].material].hasNormalMap)
				{
					glActiveTextureARB(GL_TEXTURE1_ARB);
					glBindTexture(GL_TEXTURE_2D, materials[meshes[i].material].tex_id);
				}
			}
								
			for (unsigned int j=0;j<meshes[i].faces.size();++j)
			{
				glBegin(GL_POLYGON);
				for (unsigned int k=0;k<faces[meshes[i].faces[j]].vectors.size();++k)
				{
					if (!normals.empty()) //just prevents a crash but looks pretty ugly
						glNormal3fv(normals[faces[meshes[i].faces[j]].normals[k]].getValues() );
					else
					{
						Vector v1 = vectors[faces[meshes[i].faces[j]].vectors[0]];
						Vector v2 = vectors[faces[meshes[i].faces[j]].vectors[1]];
						Vector v3 = vectors[faces[meshes[i].faces[j]].vectors[2]];
						glNormal3fv(crossProduct( (v2 - v1), (v3 - v1) ).getValues() );
					}
					if (materials[meshes[i].material].isTexture)
						glTexCoord2f(tex_coords[faces[meshes[i].faces[j]].tex_coords[k]](0),tex_coords[faces[meshes[i].faces[j]].tex_coords[k]](1));
					else
						glTexCoord2f(-1.0,-1.0);
					glVertex3fv( (vectors[faces[meshes[i].faces[j]].vectors[k]]).getValues() );
				}
				glEnd();
			}
			glActiveTextureARB(GL_TEXTURE0_ARB);				
		}
	}
	
	
	glEndList();

	//-------------------------------------------------
	
	//now init the grey list
	greyDisplayList = glGenLists(1);
	glNewList(greyDisplayList,GL_COMPILE);
	glDisable(GL_COLOR_MATERIAL);
	for (unsigned int i=0;i<meshes.size();++i)
	{
		glDisable(GL_BLEND);		// Turn Blending Off
		glEnable(GL_DEPTH_TEST);
		glDisable(GL_COLOR_MATERIAL);
		glDisable(GL_TEXTURE_2D);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, materials[meshes[i].material].ambient );
		float diffuse[]={0.8,0.8,0.8,1.0}; //the grey material
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse );
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, materials[meshes[i].material].specular );
		glMaterialf(GL_FRONT, GL_SHININESS, materials[meshes[i].material].shininess );
		for (unsigned int j=0;j<meshes[i].faces.size();++j)
		{
			glBegin(GL_POLYGON);
			for (unsigned int k=0;k<faces[meshes[i].faces[j]].vectors.size();++k)
			{
				if (!normals.empty()) //just prevents a crash but looks pretty ugly
					glNormal3fv(normals[faces[meshes[i].faces[j]].normals[k]].getValues() );
				glTexCoord2f(-1.0,-1.0);
				glVertex3fv( (vectors[faces[meshes[i].faces[j]].vectors[k]]).getValues() );
			}
			glEnd();
		}
				
	}

	glEndList();
	
}

bool Model::isTransparent(Material material)
{
	if (material.alpha<1.0)
			return true;
	else
		if (material.isTexture)
		{
			if (!material.texture.hasAlphaChannel()) //no alpha channel
				return false;
			//check if alphaChannel has somewhere a value less than 1.0 (255)
			QImage alphaChannel = material.texture.alphaChannel();
			for (int i=0;i<alphaChannel.width();++i)
				for (int j=0;j<alphaChannel.height();++j)
				{
					if (qRed(alphaChannel.pixel(i,j))<255)
						return true;
				}
			return false;			
		}
	return false;	
}


