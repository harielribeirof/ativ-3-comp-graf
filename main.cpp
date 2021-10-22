//int main(int argc, char** argv)
//{
//    glutInit(&argc, argv);

#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

// Declaração de variáveis globais
GLfloat tx = 0, ty = -23;
GLfloat win = 25, tamanhoPlayer = 1;
GLint collision = 0, batidas = 0;

// Função para desenhar um "braço" do objeto
// Função para desenhar a base do objeto 

int colisao(GLfloat LinhaX, GLfloat comprimentoLinha, GLfloat alturaLinha){
    if ((ty >= alturaLinha-1)&&(ty <= alturaLinha+1))
    {        
        if(tx + (tamanhoPlayer/2) >= LinhaX - (comprimentoLinha/2) && (tx - (tamanhoPlayer/2) <= LinhaX + (comprimentoLinha/2))){
            return 1;
        }
    }
}

void DesenhaBase()
{
	glLineWidth(2);
	glBegin(GL_LINE_LOOP);
		glVertex2f(-tamanhoPlayer/2, tamanhoPlayer/2);
		glVertex2f(tamanhoPlayer/2, tamanhoPlayer/2);
		glVertex2f(tamanhoPlayer/2, -tamanhoPlayer/2);
		glVertex2f(-tamanhoPlayer/2, -tamanhoPlayer/2);
	glEnd();
}

void DesenhaLinha(GLfloat x, GLfloat comprimento, GLfloat altura)
{
	glLineWidth(2);
	glBegin(GL_LINES);
        glColor3f(0.0f, 0.0f, 0.0f);
		glVertex2f(x - (comprimento/2), altura);
		glVertex2f(x + (comprimento/2), altura);
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
    DesenhaLinha(0, 25, 5.0f);
    DesenhaLinha(20, 25, 10.0f);
                      
	// Desenha um objeto modelado com transformações hierárquicas
    
	glPushMatrix();                   
                    
	glTranslatef(tx, ty, 0.0f);
    
	glPushMatrix();
    
	glScalef(2.5f,2.5f,1.0f);
	glColor3f(1.0f,0.0f,0.0f);
	DesenhaBase();  
	glPopMatrix();

    if(collision == 1){
        batidas++;
        if(batidas == 2){
            tx = 0;
            ty = -23;
            batidas = 0;
        }
    }    
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
	
    collision = colisao(20, 25, 10.0f); 
    collision = colisao(0, 25, 5.0f); 
    // Move a base
    
    if(key == GLUT_KEY_LEFT)
    {
        tx-=1;
        if ( tx < -win )
            tx = -win; 
    }
    if(key == GLUT_KEY_RIGHT)
    {
        tx+=1;
        if ( tx > win )
            tx = win; 
    }
    if(key == GLUT_KEY_UP)
    {
        ty+=1;
        if ( ty > win )
            ty = win; 
    }
    if(key == GLUT_KEY_DOWN)
    {
        ty-=1;
        if ( ty < -win )
            ty = -win; 
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
}

// Programa Principal 
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);  
	glutInitWindowPosition(5,5);     
	glutInitWindowSize(600,900);  
	glutCreateWindow("Atividade 3"); 
 
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