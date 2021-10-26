// ATIVIDADE 3 - LABIRINTO - COMPUTAÇÃO GRÁFICA
// ALUNO: Hariel Ribeiro

#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

// CONSTANTES
#define VELOCIDADE 1
#define ESQUERDA 4
#define DIREITA 6
#define CIMA 8
#define BAIXO 2

// Declaração de variáveis globais
GLfloat tx = 0, ty = -23;
GLfloat win = 25, tamanhoPlayer = 1;
GLint collision = 0, batidas = 0, corJanela = 0, corLabirinto = 3, corPlayer = 6,  last_move;

// Função para calcular colisões com as linhas
int colisao(GLfloat LinhaX, GLfloat comprimentoLinha, GLfloat alturaLinha){
    if ((ty+(tamanhoPlayer) >= alturaLinha)&&(ty-(tamanhoPlayer) <= alturaLinha))
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
void DesenhaPlayer()
{
	glLineWidth(3);
	glBegin(GL_LINE_LOOP);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex2f(-tamanhoPlayer/2, tamanhoPlayer/2);
		glVertex2f(tamanhoPlayer/2, tamanhoPlayer/2);
		glVertex2f(tamanhoPlayer/2, -tamanhoPlayer/2);
		glVertex2f(-tamanhoPlayer/2, -tamanhoPlayer/2);
	glEnd();
	// mudança de cor do Player
	switch (corPlayer)
	{
	case 6:
		glColor3f(1.0f, 0.0f, 0.0f);
		break;
	case 7:
		glColor3f(0.0f, 1.0f, 0.0f);
		break;
	case 8:
		glColor3f(0.0f, 0.0f, 1.0f);
		break;
	} 
	glBegin(GL_QUADS);
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
	// mudança de cor do Labirinto
	switch (corLabirinto)
	{
	case 3:
		glColor3f(0.0f, 0.0f, 0.0f);
		break;
	case 4:
		glColor3f(1.0f, 0.0f, 0.0f);
		break;
	case 5:
		glColor3f(0.0f, 1.0f, 0.0f);
		break;
	} 
	glBegin(GL_LINES);
		glVertex2f(x - (comprimento/2), altura);
		glVertex2f(x + (comprimento/2), altura);
	glEnd(); 
}

// Função para desenhar o objetivo final
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
	
	// Mudança de cor da janela
	switch (corJanela)
	{
	case 0:
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f); 
		break;
	case 1:
		glClearColor(1.0f, 0.0f, 1.0f, 1.0f); 
		break;
	case 2:
		glClearColor(1.0f, 1.0f, 0.0f, 1.0f); 
		break;
	}

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
	DesenhaPlayer();  

	// Cor do texto - vitória ou derrota
	glColor3f(0.0f,0.0f,0.0f);

	// Verificação de quantidade de colisões
    if(collision == 1){
        batidas++;
        if(batidas == 3){
            tx = 0;
            ty = -23;
            batidas = 0;
			glLoadIdentity();
			DesenhaTexto("DERROTA!!", -5, 23);
        }
    }

	// Verificação de sucesso
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
	// Verificação se colidiu
	if(collision == 0){
		if(key == GLUT_KEY_LEFT)
		{
			tx-=VELOCIDADE;
			last_move = ESQUERDA;
			
			if ( tx < -win )
				tx = -win; 
		}
		if(key == GLUT_KEY_RIGHT)
		{
			tx+=VELOCIDADE;
			last_move = DIREITA;
			
			if ( tx > win )
				tx = win; 
		}
		if(key == GLUT_KEY_UP)
		{
			ty+=VELOCIDADE;		
			last_move = CIMA;
			if ( ty > win )
				ty = win; 
		}
		if(key == GLUT_KEY_DOWN)
		{
			ty-=VELOCIDADE;
			last_move = BAIXO;
			
			if ( ty < -win )
				ty = -win; 
		} 
	}else{		// Caso tenha colidido, faz o movimento oposto ao ultimo movimento feito
		switch (last_move)
		{
		case ESQUERDA:
			tx += VELOCIDADE;
			break;
		case DIREITA:
			tx -= VELOCIDADE;
			break;
		case CIMA:
			ty -= VELOCIDADE;
			break;
		case BAIXO:
			ty += VELOCIDADE;
			break;
		
		default:
			break;
		}
	}                  
    
	glutPostRedisplay();
}

// Opções de modificação de cores da Janela
void MenuJanela(int op)
{
   switch(op) {
            case 0:
                     corJanela = 0;
                     break;
            case 1:
                     corJanela = 1;
                     break;
            case 2:
                     corJanela = 2;
                     break;
    }
    glutPostRedisplay();
}

// Opções de modificação de cores do labirinto
void MenuLabirinto(int op)
{
   switch(op) {
            case 3:
                     corLabirinto = 3;
                     break;
            case 4:
                     corLabirinto = 4;
                     break;
            case 5:
                     corLabirinto = 5;
                     break;
    }
    glutPostRedisplay();
}

// Opções de modificação de cores do Player
void MenuPlayer(int op)
{
   switch(op) {
            case 6:
                     corPlayer = 6;
                     break;
            case 7:
                     corPlayer = 7;
                     break;
            case 8:
                     corPlayer = 8;
                     break;
    }
    glutPostRedisplay();
}

// Gerenciamento do menu principal
void MenuPrincipal(int op)
{
}

// Criacao do Menu
void CriaMenu()
{
    int menu, submenu1, submenu2, submenu3;

	submenu1 = glutCreateMenu(MenuJanela);
	glutAddMenuEntry("Cor 1",0);
	glutAddMenuEntry("Cor 2",1);
	glutAddMenuEntry("Cor 3",2);

    submenu2 = glutCreateMenu(MenuLabirinto);
	glutAddMenuEntry("Cor 1",3);
	glutAddMenuEntry("Cor 2",4);
	glutAddMenuEntry("Cor 3",5);

	submenu3 = glutCreateMenu(MenuPlayer);
	glutAddMenuEntry("Cor 1",6);
	glutAddMenuEntry("Cor 2",7);
	glutAddMenuEntry("Cor 3",8);

    menu = glutCreateMenu(MenuPrincipal);
	glutAddSubMenu("Cores da janela",submenu1);
    glutAddSubMenu("Cores do labirinto",submenu2);
	glutAddSubMenu("Cores do player",submenu3);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

// Função callback chamada para gerenciar eventos do mouse
void GerenciaMouse(int button, int state, int x, int y)
{
    if (button == GLUT_RIGHT_BUTTON)
         if (state == GLUT_DOWN)
            CriaMenu();

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
	glutMouseFunc(GerenciaMouse);
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