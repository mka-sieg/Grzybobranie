#ifndef __CPLAYER
#define __CPLAYER
#include "Ground.h"
//plik z zajêæ
// ----------------------------------------------------------------
// Klasa do reprezentacji obiektu, ktory porusza sie po scenie
class CPlayer
{

public:

	// skladowe
    glm::vec3 Position;
    glm::vec3 Direction;
    float Angle = 0.0;

	// macierz modelu
	glm::mat4 matModel;

	// potok openGL
    GLuint VAO;
    int VBO_Size;
    int Texture;

    // Podlaczenie do CGround
	CGround *Ground = NULL;


    CPlayer() { }

    // Inicjalizacja obiektu
    void Init(GLuint _tex, GLuint _vao, int _size,  CGround *_ground, glm::vec3 _initPos)
    {
    	Texture = _tex;
        VAO = _vao;
        VBO_Size = _size;
        Ground = _ground;
        Position = _initPos;

		UpdateLatitute();
		UpdateMatModel();

    }

	// Obliczenie wysokosci nad ziemia
	bool UpdateLatitute()
	{
		float newAlt = Ground->getAltitute(glm::vec2(Position.x, Position.z));
        if (newAlt != -1) {
            Position.y = newAlt;
            return true;
        }
        else {
            return false;
        }
		
	}

    // Rysowanie na scenie
    void Draw(glm::vec4 Color,glm::vec3 Poslight0, glm::vec3 Poslight1, glm::vec3 Poslight2,glm::vec3 Poslight3, Camera& camera, glm::mat4 scale, Shader& shader,int light_type,int light_color)
    {
        shader.Activate();
        glUniformMatrix4fv(glGetUniformLocation(shader.ID, "scale"), 1, GL_FALSE, glm::value_ptr(scale));
        glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(matModel));
     
        glUniform4f(glGetUniformLocation(shader.ID, "lightColor"), Color.x, Color.y, Color.z, Color.w);
        glUniform3f(glGetUniformLocation(shader.ID, "lightPos0"), Poslight0.x, Poslight0.y, Poslight0.z);
        glUniform3f(glGetUniformLocation(shader.ID, "lightPos1"), Poslight1.x, Poslight1.y, Poslight1.z);
        glUniform3f(glGetUniformLocation(shader.ID, "lightPos2"), Poslight2.x, Poslight2.y, Poslight2.z);
        glUniform3f(glGetUniformLocation(shader.ID, "lightPos3"), Poslight3.x, Poslight3.y, Poslight3.z);
        glUniform3f(glGetUniformLocation(shader.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
        glUniform1i(glGetUniformLocation(shader.ID, "light_type"), light_type);
        glUniform1i(glGetUniformLocation(shader.ID, "light_color"), light_color);

        glBindVertexArray(VAO);
 
        GLuint texUni = glGetUniformLocation(shader.ID, "diffuse0");
  
        glUniform1i(texUni, 1);
  
        glActiveTexture(GL_TEXTURE1);
      
        camera.Matrix(shader, "camMatrix");
        glBindTexture(GL_TEXTURE_2D, Texture);
        glDrawArrays(GL_TRIANGLES, 0, VBO_Size);
        glBindVertexArray(0);
        glUseProgram(0);

    }

	void UpdateMatModel()
	{
		matModel = glm::translate(glm::mat4(1.0), Position);
		matModel = glm::rotate(matModel, Angle, glm::vec3(0.0, 1.0, 0.0));
	}

    // ustawienie pozycji na scenie
    void SetPosition(glm::vec3 pos)
    {
        Position = pos;
        UpdateMatModel();
    }

    // zmiana pozycji na scenie
    void Move(float val)
    {
        Position += Direction * val;

        // Aktualizacja polozenia na Y
        bool ziemia=UpdateLatitute();
        if (ziemia) {
            UpdateMatModel();
        }
        
    }

    void Rotate(float angle)
    {
    	Angle += angle;
		Direction.x = cos(Angle);
		Direction.z = -sin(Angle);

		UpdateMatModel();
    }

};


#endif
