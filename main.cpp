//int main(int argc, char** argv)
//{
//    glutInit(&argc, argv);

//*****************************************************
//
// ObjetoComTransformacoesHierarquicas.cpp
// Um programa OpenGL simples que abre uma janela GLUT, 
// desenha e permite interagir com um objeto que é 
// modelado através da utilização de transformações
// hierárquicas.
//
// Marcelo Cohen e Isabel H. Manssour
// Este código acompanha o livro 
// "OpenGL - Uma Abordagem Prática e Objetiva"
// 
//*****************************************************

#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

// Declaração de variáveis globais
GLfloat tx = 0, ty = 0;
GLfloat win = 25;

// Função para desenhar um "braço" do objeto
// Função para desenhar a base do objeto 

int colisao(GLfloat playerY){
    if(playerY > 5.0f){
        return 1;
    }
    return 0;
}

void DesenhaBase()
{
	glLineWidth(2);
	glBegin(GL_LINE_LOOP);
		glVertex2f(-0.5, -8.0);
		glVertex2f(0.5, -8.0);
		glVertex2f(0.5,-9.0);
		glVertex2f(-0.5,-9.0);
	glEnd();
}

void DesenhaLinha(GLfloat x1, GLfloat x2, GLfloat altura)
{
	glLineWidth(2);
	glBegin(GL_LINES);
        glColor3f(0.0f, 0.0f, 0.0f);
		glVertex2f(x1, altura);
		glVertex2f(x2, altura);
	glEnd();
}
           
// Função callback de redesenho da janela de visualização
void Desenha(void)
{
	// Muda para o sistema de coordenadas do modelo
	glMatrixMode(GL_MODELVIEW);
	// Inicializa a matriz de transformação corrente
	glLoadIdentity();
     
	// Limpa a janela de visualização com a cor  
	// de fundo definida previamente
	glClear(GL_COLOR_BUFFER_BIT);

	// Desenha o "chão"
    DesenhaLinha(-win, win, -0.0f);

                               
	// Desenha um objeto modelado com transformações hierárquicas
    
	glPushMatrix();                   
                    
	glTranslatef(tx, ty, 0.0f);
    
	glPushMatrix();
    
	glScalef(2.5f,2.5f,1.0f);
	glColor3f(1.0f,0.0f,0.0f);
	DesenhaBase();
    
	glPopMatrix();   
      
	// Executa os comandos OpenGL 
	glFlush();
}

// Função callback chamada quando o tamanho da janela é alterado 
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
	GLsizei largura, altura;
                   
	// Evita a divisao por zero
	if(h == 0) h = 1;

	// Atualiza as variáveis
	largura = w;
	altura = h;
                                              
	// Especifica as dimensões da Viewport
	glViewport(0, 0, largura, altura);

	// Inicializa o sistema de coordenadas
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Estabelece a janela de seleção (esquerda, direita, inferior, 
	// superior) mantendo a proporção com a janela de visualização
	gluOrtho2D (-win, win, -win, win);       
}

// Função callback chamada para gerenciar eventos de teclas especiais(F1,PgDn,...)
void TeclasEspeciais(int key, int x, int y)
{
	// Move a base
	if(key == GLUT_KEY_LEFT)
	{
		tx-=2;
		if ( tx < -win+1 )
			tx = -win+1; 
	}
	if(key == GLUT_KEY_RIGHT)
	{
		tx+=2;
		if ( tx > win-1 )
			tx = win-1; 
	}
    if(key == GLUT_KEY_UP)
	{
		ty+=2;
		if ( ty > win+20 )
			ty = win+20; 
	}
    if(key == GLUT_KEY_DOWN)
	{
		ty-=2;
		if ( ty < -win+22 )
			ty = -win+22; 
	}                 
                                                
	glutPostRedisplay();
}

// Função callback chamada para gerenciar eventos de teclas
void Teclado (unsigned char key, int x, int y)
{
	if (key == 27)
		exit(0);
}
           
// Função responsável por inicializar parâmetros e variáveis
void Inicializa (void)
{   
	// Define a cor de fundo da janela de visualização como branca
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    
	// Exibe mensagem que avisa como interagir
	printf(" Setas para esquerda e para direita movimentam a base (vermelha)");
	printf("\n Home e End rotacionam o braco 1 (verde)");
	printf("\n PageUP e PageDn rotacionam o braco 2 (azul)");    
}

// Programa Principal 
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);  
	glutInitWindowPosition(5,5);     
	glutInitWindowSize(400,600);  
	glutCreateWindow("Desenho de objeto modelado com transformações hierárquicas"); 
 
	// Registra a função callback de redesenho da janela de visualização
	glutDisplayFunc(Desenha);  
	
	// Registra a função callback de redimensionamento da janela de visualização
	glutReshapeFunc(AlteraTamanhoJanela);    

	// Registra a função callback para tratamento das teclas especiais
	glutSpecialFunc(TeclasEspeciais);

	// Registra a função callback para tratamento das teclas ASCII
	glutKeyboardFunc (Teclado);

	// Chama a função responsável por fazer as inicializações 
	Inicializa(); 

    
	// Inicia o processamento e aguarda interações do usuário
	glutMainLoop();

	return 0;
}