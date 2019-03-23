#include <stdio.h>
#include<stdlib.h>
#include<time.h>
#include <iostream>
using namespace std;
#define N 19 //�����Թ���С(���������ǽ��),0Ϊͨ��1Ϊ��
#define MaxSize 99

/*int Maze[N][N] =
{
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,1,1,1,0,1,0,0,1,0,0,0,0,0,0,1,0,1},
    {1,0,0,0,1,1,1,0,1,0,1,1,1,1,1,0,0,1,1},
    {1,0,1,0,0,1,1,0,1,1,0,1,0,1,1,0,0,0,1},
    {1,0,0,0,0,0,1,0,1,1,1,1,1,0,1,1,1,0,1},
    {1,1,0,1,1,0,1,0,1,0,0,0,1,0,0,0,0,0,1},
    {1,0,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,0,1},
    {1,0,0,1,0,1,0,0,0,0,0,0,1,0,0,0,0,0,1},
    {1,1,0,1,1,1,1,1,1,1,1,0,1,0,1,1,1,0,1},
    {1,0,1,1,0,0,0,0,0,0,1,1,1,0,1,0,0,0,1},
    {1,0,1,0,1,1,1,0,0,0,1,0,1,1,1,1,1,0,1},
    {1,0,0,0,1,1,0,1,0,1,1,0,1,0,0,0,0,0,1},
    {1,1,1,0,1,0,1,1,1,1,0,0,1,0,1,1,1,1,1},
    {1,0,1,0,1,0,0,0,0,1,1,0,1,0,1,0,1,0,1},
    {1,0,1,0,1,1,1,1,1,1,0,1,0,1,1,1,1,0,1},
    {1,1,1,0,1,0,0,1,1,1,0,1,1,0,0,1,1,0,1},
    {1,0,1,0,1,0,1,0,1,1,0,1,1,1,1,0,1,1,1},
    {1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};*/
//int N = 19;

int Maze[N][N]={0};


void CreateMaze()
{
    int i,j;
    srand((unsigned)time(NULL)); ///srand()���Ǹ�rand()�ṩ����seed
    for (i=0; i<N; i++)
    {

        for(j=0; j<N; j++)
        {

            int num = (rand()+1)%2;            //��2ȡ��õ�����0����1
            //srand(unsigned(time(0)));    //��ȡϵͳʱ��
            //int num = rand()%2;         //���������
            Maze[i][j] = num ;
            if(i==0||j==0||i==N-1||j==N-1) Maze[i][j]=1;

        }
    }
    Maze[1][1]=0,Maze[N-2][N-2]=0;
}
int Maze_sy[N][N]={0};//���帨�����飬��������Ԫ�ؾ�Ϊ0

//�ö�ά���鶨��8������,�ӱ�����ʱ�뿪ʼ
int step[8][2]=
{
    {-1,0},
    {-1,1},
    {0,1},
    {1,1},
    {1,0},
    {1,-1},
    {0,-1},
    {-1,-1}
};

void printMaze()
{
    int i,j;
    for (i=0; i<N; i++)
    {
        printf("\n");
        for(j=0; j<N; j++)
        {
            //if(i==0||j==0||i==N-1||j==N-1) continue; //�����ǽ��
            if(i==0||i==N-1) printf("��");
            else if(j==0||j==N-1) printf("|");
            else printf("%d ",Maze[i][j]);
        }
    }

}
//�ڶ������⣬�ȼ򵥵㣬Ĭ�����Ͻ�Ϊ��ڣ����½�Ϊ���ڣ���8��������ߣ���ô��ʾ�أ�
typedef struct
{
    short int row;
    short int col;
    short int dir=0;//8����ֵ������8������,һ��ʼĬ��Ϊ0
} Point;
//����ջ
typedef struct
{
    Point Data[MaxSize];    // �洢Ԫ�ص�����
    int Top; //ջ��ָ��

} SeqStack;

void InitStack(SeqStack *s) //����һ��ջ
{
    s->Top=-1; //��ʾջ��
}

bool Push(SeqStack *s, Point x)//��ջ����
{
    if(s->Top==MaxSize-1)
        return false;
    else
    {
        s->Top++;
        s->Data[s->Top]=x;
        return true;
    }
}

bool Pop(SeqStack *s)  //��ջ����
{
    if(s->Top==-1)
        return false;
    else
    {
        s->Top--;
        return true;
    }
}

bool GetAllElem(SeqStack *s) //����ջ
{
    if(s->Top==-1) return false;
    else
    {
        for(int i=s->Top; i>-1; i--)
        {
            printf("(%d,%d)->",s->Data[i].col,s->Data[i].row);
        }
        return true;

    }

}
//��������dfs�㷨
int path(Point p,SeqStack s)  //�ѵ���s��&�����𣿣�����
{
    if (Maze[p.row][p.col]==1)   //
    {
        //Pop(&s); ����ɾ����Ӧ���˻ص���һ��Ԫ�أ���������û���ʹ��Ľ��
        printf("***(%d,%d)��Ч***\n",p.col,p.row);
        //printf("(A-,%d)->",s.Data[s.Top-1].dir);
        // if(p.col&&p.row==0) return 0; //�����ڴ��˳����ú���
    } //��Ч���
    else
    {
        if(p.col==N-2&&p.row==N-2)
        {
            Push(&s,p);
            printf("\n��ϲ�����յ㣡·������:\n\n");
            GetAllElem(&s);
            return 1;
        }
        else
        {
            if
            (Maze_sy[p.row][p.col]==0)
            {
                Push(&s,p);//��ջ�����ڵ㣩
                Maze_sy[p.row][p.col]=1;// ��־�Ѹ����ʹ�
                printf("ѹ���:(%d,%d)->",s.Data[s.Top].col,s.Data[s.Top].row);//����ڵ�����
            }
        }

    }

    //int len=sizeof(s.Data)/sizeof(int);//�������鳤�� Ӧ����ջ��ָ�룡
    short int dir=p.dir;
    Point next_p;
    // printf("****%d***",s.Data[s.Top].dir);  ���Ե�ǰ�Ƿ�dir�ɴﵽ7�����
    if(s.Data[s.Top].dir==7)   //�жϸ�ջ��Ԫ���Ƿ�������ɣ�
    {
        Pop(&s);    //����򵯳�
        //printf("����Ч��->");
        if( s.Top==-1 )//ջ�Ƿ�Ϊ�գ�����û��·��
        {
            printf("\n\n���ź�!û��·���߳��Թ���\n\n");
            return 0;
        }
        else
        {
            //printf("***hello2->"); ���Դ���ɷ����е��˴�
            printf("���ݵ�: (%d,%d)->",s.Data[s.Top].col,s.Data[s.Top].row); //�ص�ջ��Ԫ��
            //Maze_sy[s.Data[s.Top].col][s.Data[s.Top].row]=0;//ջ����������Ϊδ����
            path(s.Data[s.Top],s);  //����ջ��

        }
    }
    else   //����û����ɣ�ȡδ�������ĸ��ڵ㣬���ص���2��
    {


        for(; dir<=7;)  //����Ӧ����0��6����0��7����
        {
            next_p.row=p.row+step[dir][1]; //���⣬��һ�����λ�ü���
            next_p.col=p.col+step[dir][0];
            if ((Maze[next_p.row][next_p.col]!=1)&&(Maze_sy[next_p.row][next_p.col]!=1)) break;//�˴�ע��һ�£���һ���㲻��1����һ�����־��Ϊ1��
            else dir++;
        }
        if(dir==8) dir--; //dir���ջ�ӵ�8������ֻ�������Ϸ�����
        //p.dir=dir;//Ϊʲô���ַ������У�
        s.Data[s.Top].dir=dir;// ��¼�ߵķ���
        // printf("(s.top.dir)->%d->",s.Data[s.Top].dir); ����dir�Ƿ�ɹ���ֵ��p��
        printf("  ��һ��:(%d,%d)\n",next_p.col,next_p.row);
        path(next_p,s);
    }
}

int main()
{
    SeqStack s;
    InitStack(&s);
    Point startpoint;  //���忪ʼ���
    Point endpoint;    //�����յ�
    startpoint.row=1,startpoint.col=1; //���Ϊ��1,1)
    endpoint.row=N-2,endpoint.col=N-2;//�յ�Ϊ(N,N)
    //CreateMaze();
   // printMaze();
   // printf("\n\n");
   // path(startpoint,s);
   cout << "Hello, world!" << endl;

}
