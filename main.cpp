#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <GL/glut.h>

// Declaração de variáveis globais
GLfloat tx = 0, ty = -23;
GLfloat win = 25, tamanhoPlayer = 1;
GLint collision = 0, batidas = 0;


// Função para calcular colisões com as linhas
int colisao(GLfloat LinhaX, GLfloat comprimentoLinha, GLfloat alturaLinha){
    if ((ty >= alturaLinha-1)&&(ty <= alturaLinha+1))
    {        
        if(tx + (tamanhoPlayer/2) >= LinhaX - (comprimentoLinha/2) && (tx - (tamanhoPlayer/2) <= LinhaX + (comprimentoLinha/2))){
            return 1;
        }
    }
}

// Desenha texto na tela
void DesenhaTexto(char *string, int x, int y)
{
  	glPushMatrix();
        // Posição no universo onde o texto será colocado
        glRasterPos2f(x, y);
        // Exibe caracter a caracter
        while(*string)
             glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,*string++);
	glPopMatrix();
}

// Função para desenhar o player
void desenhaPlayer()
{
	glLineWidth(3);
	glBegin(GL_LINE_LOOP);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex2f(-tamanhoPlayer/2, tamanhoPlayer/2);
		glVertex2f(tamanhoPlayer/2, tamanhoPlayer/2);
		glVertex2f(tamanhoPlayer/2, -tamanhoPlayer/2);
		glVertex2f(-tamanhoPlayer/2, -tamanhoPlayer/2);
	glEnd();
	glBegin(GL_QUADS);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex2f(-tamanhoPlayer/2, tamanhoPlayer/2);
		glVertex2f(tamanhoPlayer/2, tamanhoPlayer/2);
		glVertex2f(tamanhoPlayer/2, -tamanhoPlayer/2);
		glVertex2f(-tamanhoPlayer/2, -tamanhoPlayer/2);
	glEnd();
}

// Função para desenhar as linhas
void DesenhaLinha(GLfloat x, GLfloat comprimento, GLfloat altura)
{
	glLineWidth(2);
	glBegin(GL_LINES);
        glColor3f(0.0f, 0.0f, 0.0f);
		glVertex2f(x - (comprimento/2), altura);
		glVertex2f(x + (comprimento/2), altura);
	glEnd(); 
}

void DesenhaObjetivo()
{
	glLineWidth(2);
	glBegin(GL_QUADS);
        glColor3f(1.0f, 0.0f, 0.0f);
		glVertex2f(9.0f, 21.0f);
		glVertex2f(14.0f, 21.0f);
		glVertex2f(14.0f, 23.0f);
		glVertex2f(9.0f, 23.0f);
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
	// Alcançar o objetivo
	
	// Desenho das linhas
	DesenhaLinha(20, 10, -16.0f);
	DesenhaLinha(-9, 35, -16.0f);

	DesenhaLinha(-20, 10, -12.0f);
	DesenhaLinha(9, 35, -12.0f);
	
	DesenhaLinha(15, 22, -8.0f);
	DesenhaLinha(-15, 25, -8.0f);

	DesenhaLinha(-20, 10, -4.0f);
	DesenhaLinha(9, 35, -4.0f);

	DesenhaLinha(0, 40, 0.0f);

	DesenhaLinha(15, 22, 4.0f);
	DesenhaLinha(-15, 25, 4.0f);

	DesenhaLinha(20, 10, 8.0f);
	DesenhaLinha(-9, 35, 8.0f);

	DesenhaLinha(-20, 10, 12.0f);
	DesenhaLinha(9, 35, 12.0f);

	DesenhaLinha(0, 40, 16.0f);

	DesenhaLinha(20, 10, 20.0f);
	DesenhaLinha(-9, 35, 20.0f);   

	// Desenha objetivo
	DesenhaObjetivo();

	// Movimento do Player               
	glTranslatef(tx, ty, 0.0f);
    
	// Desenho do player
	glScalef(2.5f,2.5f,0.0f);
	glColor3f(1.0f,0.0f,0.0f);
	desenhaPlayer();  

	DesenhaObjetivo();
	glColor3f(0.0f,0.0f,0.0f);

	// Verificação de quantidade de colisões
    if(collision == 1){
        batidas++;
        if(batidas == 2){
            tx = 0;
            ty = -23;
            batidas = 0;
			glLoadIdentity();
			DesenhaTexto("DERROTA!!", -5, 23);
        }
    }
	if(ty >= 20.0f && ((tx >= 9.0f)&&(tx<=14.0f))){
		tx = 0; ty = -23;
		glLoadIdentity();
		DesenhaTexto("VITORIA!!", -5, 23);
		
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
	// Calculo colisões
	collision = colisao(20, 10, -16.0f);
	collision = colisao(-9, 35, -16.0f);

	collision = colisao(-20, 10, -12.0f);
	collision = colisao(9, 35, -12.0f);
	
	collision = colisao(15, 22, -8.0f);
	collision = colisao(-15, 25, -8.0f);

	collision = colisao(-20, 10, -4.0f);
	collision = colisao(9, 35, -4.0f);

	collision = colisao(0, 40, 0.0f);

	collision = colisao(15, 22, 4.0f);
	collision = colisao(-15, 25, 4.0f);

	collision = colisao(20, 10, 8.0f);
	collision = colisao(-9, 35, 8.0f);

	collision = colisao(-20, 10, 12.0f);
	collision = colisao(9, 35, 12.0f);

	collision = colisao(0, 40, 16.0f);

	collision = colisao(20, 10, 20.0f);
	collision = colisao(-9, 35, 20.0f);

    // Movimento do player
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