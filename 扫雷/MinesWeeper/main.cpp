//
// Created by 86178 on 2023/7/8.
//
#include <cstdio>
#include <cstdlib>
#include <ctime>

//ʵ�����̵Ĺ������������Ų���
#define ROW 9 //��
#define COL 9 //��

//�������̵Ĺ�����ڷ�ֹԽ��
#define ROWS (ROW + 2) //��
#define COLS (COL + 2) //��

//�������ڵ����Ѷ�,���׵ĸ���
#define CURRENT_COUNT 10

//��������
void menu();                                                                    //��ӡ���˵�
void game();                                                                    //��Ϸ����
void initboard(char board[11][11], char set);           //��ʼ������
void print_board(char board[ROWS][COLS], int row, int col);                     //��ӡ����
void FineMine(char mine[ROWS][COLS], char check[ROWS][COLS], int row, int col); //�Ų���
int Get_Mine_Count(char mine[ROWS][COLS], int x, int y);                        //�������긽���׵��ܸ���
void recur(char mine[ROWS][COLS], char check[ROWS][COLS], int x, int y);        //�ݹ�����������
void SetMine(char mine[ROWS][COLS], int row, int col);
//������
int main()
{
    srand((unsigned int)time(nullptr)); //��ʼ�����ӣ���Ϊ�������ӹ�rand()����ʹ��
    int input;                       // input�����û�ѡ��
    do
    {
        menu(); //��ӡ���˵�
        printf("��ѡ��1��0����\n");
        scanf("%d", &input);
        switch (input)
        {
            case 1:
                game();
                break; //������Ϸ����
            case 0:
                exit(0); //��ֹ��������
            default:
                printf("�����������������\n");
                break;
        }
    } while (input);

    return 0;
}

//��ӡ�˵�
void menu()
{
    printf("******************************\n");
    printf("****         1.play       ****\n");
    printf("****         0.exit       ****\n");
    printf("******************************\n");
}

//��Ϸ����
void game()
{
    //��������
    char mine[ROWS][COLS] = {0};
    char check[ROWS][COLS] = {0};
    //��ʼ������
    initboard(mine, '0');
    initboard(check, '*');
    //��ӡ����
    print_board(check, ROW, COL);
    //������
    SetMine(mine, ROW, COL);
    //�����������ڼ���׵Ĳ���
    //print_board(mine, ROW, COL);
    //�Ų���
    FineMine(mine, check, ROW, COL);
    // print_board(mine, ROW, COL);�ú������ڼ������̲����׵������ԣ�ʹ���������ڴ��ڴ�ӡ���������׵����̣����׵ķֲ�ͼ
}

//��ʼ������
void initboard(char board[11][11], char set)
{
    int i, j;
    for (i = 0; i < ROWS; i++)
    {
        for (j = 0; j < COLS; j++)
        {
            board[i][j] = set;
        }
    }
}
/*�ڴ˺����У�����˫��ѭ�����������е�ÿ����Ԫ��Ȼ��������ÿ��λ�����ó�set����ָ����״̬*/

//��ӡ����
void print_board(char board[ROWS][COLS], int row, int col)
{
    int i, j;
    for (i = 0; i <= row; i++)
    {
        printf("%d ", i); //��ӡ������
    }
    printf("\n");
    for (i = 1; i <= row; i++)
    {
        printf("%d ", i); //��ӡ������
        for (j = 1; j <= col; j++)
        {
            printf("%c ", board[i][j]); //�����������Check�����ӡ �� * ��
        }
        printf("\n");
    }
    printf("\n");
}

//������
void SetMine(char mine[ROWS][COLS], int row, int col)
{
    int level_count = CURRENT_COUNT;
    while (level_count)
    {
        int x; //��
        int y; //��
        //���� 1�� row���У��� 1��col���У����������Ϊ�ף�������������ѡ���׵�λ�á�
        x = rand() % row + 1;
        y = rand() % col + 1;
        if (mine[x][y] != '1')
        {
            mine[x][y] = '1'; //���õ����������ֵΪ �� 1 �������ױ���
            level_count--;    //���׷�����������������һ��ֱ����Ϊ0���� whileѭ��
        }
        else
        {
            continue; //������ֻ�� mine[x][y]�йأ��� whileѭ���Լ���
        }
    }
}
/*�˴������������ס�����ʹ��һ�� CURRENT_COUNT �ı�����ִ��ѭ����
Ȼ��ÿ��ѭ����������һ������1��row(��)��col(��)֮���������ꡣ
������괦û����(�������ڡ�1��)����Ὣ��λ���趨Ϊ'1',
�������ִ��ѭ����ֱ��level_count������Ϊ0.*/

//�Ų���
void FineMine(char mine[ROWS][COLS], char check[ROWS][COLS], int row, int col)
{
    int x, y;
    int win = row * col - CURRENT_COUNT; // winΪ�Ų����
    while (win >= 0)
    {
        printf("��������Ҫ�Ų�����꣨��ʽ����<�ո�>�У�:");
        scanf("%d %d", &x, &y);
        printf("\n");
        //���ж���������Ƿ�Ϸ������ж�����ǲ����ף�����ж����λ����û�б��Ų��
        if (x >= 1 && x <= ROW && y >= 1 && y <= COL) //�ж��Ƿ�Ϸ�
        {
            if (mine[x][y] == '1') //�ж��Ƿ����
            {
                printf("���ź�����ȵ�����\n");
                break;
            }
            else if (check[x][y] != '*') //�ж���û�б��Ų��
            {
                printf("��������Ѿ��Ų���ˣ���ѡ����������\n");
            }
            else //�������
            {
                win--;                                //�Ų������һ
                int num = Get_Mine_Count(mine, x, y); // numΪ��������Χ8��λ�׵��ܸ���
                check[x][y] = num + '0';              //����������׵�����ת�����ַ���ʽ�����洢�� check �����С�
                if (check[x][y] == '0')
                {
                    recur(mine, check, x, y);
                }
                print_board(check, ROW, COL);
            }
        }
        else
            printf("����Ƿ�������ָ����Χ�ڽ����Ų�\n");
        if (win == 0)
        {
            printf("��ϲ�㣬�����������е���\n");
        }
    }
}

//����ĳ���긽���ж����ף����ڡ��Ų��ס������е�Ƕ�׺�����
int Get_Mine_Count(char mine[ROWS][COLS], int x, int y)
{
    return (mine[x - 1][y - 1] + mine[x - 1][y] + mine[x - 1][y + 1] +
            mine[x][y - 1] + mine[x][y + 1] +
            mine[x + 1][y - 1] + mine[x + 1][y] + mine[x + 1][y + 1] -
            8 * '0');
}
/*��δ���Ĺ����Ǽ���ĳ���긽���ж��ٸ��ס�
����ԭ���ǣ�������� (x, y) ���궨λ���������
���ڵ���Χ�˸����ӣ��ϡ��¡������ĸ��������ĸ��Խ����ϵ��ĸ����ӣ���
����˸����ӵ��׵���������һ��Ȼ���ټ�ȥ 8 ��'0'����ȥ8��'0'����Ϊ��8��λ�ö��ᱻ�ۼƣ�
��ʹ����û����Ҳ�ᱻ�ۼ�(������1)�����8��λ�ö�û���ף�����ֵ����0������
�����Ϳ��Լ������Χ�ж��ٸ��ס�*/

//�ݹ��Ų�������Χ
//ֹͣ�������Ų������Ϊ�Ƿ�����
//�ݹ���̣�x��y���ϱ����С�����Ǹ����Ų������Ϊ��ʱ��ֹͣ������ĵݹ飬
//��������Ϊ�Ѿ��Ų�������꣬��ֹͣ������ĵݹ�
//�����ڡ��Ų��ס������е�Ƕ�׺�����
void recur(char mine[ROWS][COLS], char check[ROWS][COLS], int x, int y)
{
    int count = Get_Mine_Count(mine, x, y); // countΪ��������Χ8��λ�׵��ܸ���
    if (count == 0)
    {
        check[x][y] = ' ';
        if (x - 1 >= 0 && x - 1 <= ROW && y >= 0 && y <= COL && check[x - 1][y] == '*')
            recur(mine, check, x - 1, y);
        if (x + 1 >= 0 && x + 1 <= ROW && y >= 0 && y <= COL && check[x + 1][y] == '*')
            recur(mine, check, x + 1, y);
        if (x >= 0 && x <= ROW && y - 1 >= 0 && y - 1 <= COL && check[x][y - 1] == '*')
            recur(mine, check, x, y - 1);
        if (x >= 0 && x <= ROW && y + 1 >= 0 && y + 1 <= COL && check[x][y + 1] == '*')
            recur(mine, check, x, y + 1);
    }
    else
    {
        check[x][y] = count + '0';
    }
}
/*�������������ڼ��һ���ض������꣨��x, y��ʾ�������ж����׵ġ�
���count����0��˵����λ�ø���û���ף���essay��д��check[x][y]��Ϊ' '����ǿո��ַ�����
��������������ϡ��¡������ĸ���������ꣻ���count������0��˵����λ�ø������ף�
��check[x][y]����Ϊcount+'0'����Ϊ�� ASCII ���У���0�� - 8 = ��8����
���Լ�ȥ 8 ����0���Ϳ��԰ѷ���ֵ����Ϊ 0 - 8 ֮�䡣�� 8 ��λ�ö�û���ף�����ֵӦ���� 0��
�����е� check[x][y] = num + '0' �ǽ� Get_Mine_Count()�������ص� count ���� '0'��ASCII��ֵ
����ֵ�� check[x][y]���Ա�ʾ��λ���ж����ס�*/