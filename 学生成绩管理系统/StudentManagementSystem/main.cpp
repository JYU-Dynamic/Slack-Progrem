//
// Created by 86178 on 2023/7/8.
//
/*
ѧ���ɼ�����ϵͳӦ�ð����Ĺ���

1.��¼���ܣ��������Ա��¼����¼�ɹ�����ܷ����������ܡ�
2.¼��ѧ����Ϣ����¼��ѧ����Ϣ�����磺ѧ�š��������༶���ɼ���
3.ɾ��ѧ����Ϣ������ѧ�ſ�ɾ����ѧ��¼���ȫ����Ϣ��
4.����ѧ����Ϣ������ѧ�ſ��޸ĸ�ѧ�����������༶���ɼ���
5.��ѯѧ���ɼ�������ѧ�ſɲ�ѯ��ѧ���ÿƳɼ���
6.����ѧ���ɼ�������ƽ���֡���߷֡���ͷ֡��������ߵʹ�ӡ�����벻���������������ȡ�
7.���������ɽ�¼���ѧ����Ϣ������ָ�����ĵ��ı��С�
8.�˳�ϵͳ������ָ����˳���ϵͳ��


��ʵ�����Ϲ��ܵ�C�����������룺
*/


#include <cstdio>
#include <cstdlib>
#include <cstring>
//����ѧ�����ݽṹ
typedef struct Student
{
    int id;
    char name[20];
    char classes[20];
    float score;
} Student;

//����ѧ����������
Student students[100];
int stuNum;//�궨��ѧ������
float all;//�궨���ܷ�
int pass;//�궨�弰����
int sumpass;//�궨�弰������
int sumunpass;//�궨�岻��������

//��������
void login();//�����ߵ�¼
void addStudent();//¼��ѧ����Ϣ
void delStudent();//ɾ��ѧ����Ϣ
void updateStudent();//����ѧ����Ϣ
void queryStudent();//��ѯ�ɼ�
void analyzeStudent();//�����ɼ�
void outputStudent();//��������

int main()
{
    login();//���õ�¼����
    printf("---------��ӭʹ�ñ�ϵͳ��---------\n");//����
    printf("������ÿ��ܷ֣�");
    scanf("%f",&all);//¼���ܷ�
    printf("�����ߣ�");
    scanf("%d",&pass);//¼�뼰�����
    while (true)//��ӡ���˵�
    {
        int sel;
        printf("\t\n");
        printf("��ѡ�������\n");
        printf(" ---------------\n");
        printf("|  1. ���ѧ��  |\n");
        printf("|  2. ɾ��ѧ��  |\n");
        printf("|  3. ����ѧ��  |\n");
        printf("|  4. ��ѯѧ��  |\n");
        printf("|  5. ����ѧ��  |\n");
        printf("|  6. ��������  |\n");
        printf("|  0. �˳�      |\n");
        printf(" ---------------\n");
        scanf("%d", &sel);
        switch (sel) //�����������ö�Ӧ����
        {
            case 1: addStudent(); break;
            case 2: delStudent(); break;
            case 3: updateStudent(); break;
            case 4: queryStudent(); break;
            case 5: analyzeStudent(); break;
            case 6: outputStudent(); break;
            case 0: return 0;
            default: printf("�����������������룡\n"); break;
        }
    }
}

//��¼����
void login()
{
    char password[20];
    printf("���������Ա���룺\n");
    scanf("%s", password);
    if (strcmp(password, "123456") == 0)//��stringcompare�ȶ���Կ
    {
        printf("��¼�ɹ���\n");
        printf("\t\n");
    }
    else
    {
        printf("������󣬵�¼ʧ�ܣ�\n");
        exit(0);//��ֹ�������У������˳�����
    }
}

//���ѧ��
void addStudent()
{
    Student *stu = (Student *)malloc(sizeof(Student));
    //��̬�ڴ������䣬Ϊָ��stu����һ��洢Student�������ݵ��ڴ�ռ䡣
    printf("������ѧ��ѧ�ţ�");
    scanf("%d", &stu->id);
    ///ѧ�ž���Ψһ�ԣ��ж��Ƿ��ظ����롣
    int flag = 0;
    int i;
    for(i = 0; i < stuNum; i++)
    {
        if(students[i].id == stu->id)
        {
            flag = 1;
            break;
        }
    }
    if(flag == 1)
    {
        printf("ѧ���ظ������ʧ�ܣ�\n");
        free(stu);
        return;
    }
    ///
    printf("������ѧ��������");
    scanf("%s", stu->name);
    printf("������ѧ���༶��");
    scanf("%s", stu->classes);
    printf("������ѧ���ɼ�(��)��");
    scanf("%f", &stu->score);
    if(stu->score > all)
    {
        printf("ѧ���ɼ������ܷ֣����ʧ�ܣ�\n");
        free(stu);//�ͷ�stu��ָ��Ķ�̬�ڴ棬���ͷŵ���̬���ٵ��ڴ�ռ䣬�����ڴ�й©��
        return;//�жϺ���ִ�У�����addStudent()����
    }
    else
    {
        students[stuNum] = *stu;//��stu��ָ��Ľṹ�����ݸ�ֵ��students[stuNum]��������µ�ѧ����Ϣ
        stuNum++;//ѧ��������һ����¼ѧ��������
        printf("\t\n");
        printf("��ӳɹ���\n");
    }
    free(stu);//�ͷ�stu��ָ��Ķ�̬�ڴ棬���ͷŵ���̬���ٵ��ڴ�ռ䣬�����ڴ汻����ռ�á�
}

//ɾ��ѧ��
void delStudent()
{
    int i, del_id;
    printf("������Ҫɾ����ѧ��ѧ�ţ�");
    scanf("%d", &del_id);
    for (i = 0; i < stuNum; i++)
    {
        // �ҵ�ѧ����ͬ��ѧ��
        if (students[i].id == del_id)
        {
            // �����һ��ѧ�����ݸ��ǵ���ǰλ��
            students[i] = students[stuNum - 1];
            //ѧ���������Ŵ�0��ʼ���������һ��ѧ����������Ӧ����stuNum-1��������stuNum��
            stuNum--;// ѧ��������һ
            printf("\t\n");
            printf("ɾ��ѧ���ɹ���\n");
            return;//�жϺ���ִ�У�����delStudent()����
        }
    }
    printf("δ�ҵ���ѧ�ţ�\n");
}

//����ѧ��
void updateStudent()
{
    int i, update_id;
    printf("������Ҫ���µ�ѧ��ѧ�ţ�");
    scanf("%d", &update_id);
    for (i = 0; i < stuNum; i++)
    {
        // �ҵ�ѧ����ͬ��ѧ��,�������뼴��
        if (students[i].id == update_id)
        {
            printf("��������º��ѧ��������");
            scanf("%s", students[i].name);
            printf("��������º��ѧ���༶��");
            scanf("%s", students[i].classes);
            printf("��������º��ѧ���ɼ���");
            scanf("%f", &(students[i].score));
            printf("\t\n");
            printf("����ѧ���ɹ���\n");
            return;//�жϺ���ִ�У�����updateStudent()����
        }
    }
    printf("δ�ҵ���ѧ�ţ�\n");
}

//��ѯѧ��
void queryStudent()
{
    int i, query_id;
    printf("������Ҫ��ѯ��ѧ��ѧ�ţ�");
    scanf("%d", &query_id);
    for (i = 0; i < stuNum; i++)
    {
        // �ҵ�ѧ����ͬ��ѧ��
        if (students[i].id == query_id)
        {
            printf("\t\n");
            printf("ѧ�ţ�%d\n", students[i].id);
            printf("������%s\n", students[i].name);
            printf("�༶��%s\n", students[i].classes);
            printf("�ɼ���%.2f��\n", students[i].score);
            return;//�жϺ���ִ�У�����queryStudent()����
        }
    }
    printf("δ�ҵ���ѧ�ţ�\n");
}

//����ѧ��
void analyzeStudent()
{
    if(stuNum!=0)//�ж��Ƿ��Ѿ�¼��ѧ����Ϣ
    {
        int i;
        float sum = 0;
        float max = 0;
        for (i = 0; i < stuNum; i++)
        {
            sum += students[i].score;//ͳ���ܷ�
            if (students[i].score > max)
            {
                max = students[i].score;//�ҳ���߷�
            }
            if (students[i].score < all)
            {
                all = students[i].score;//�ҳ���ͷ�
            }
        }
        printf("\t\n");
        printf("ƽ���ɼ���%.2f��\n", sum / stuNum);
        printf("��߳ɼ���%.2f��\n", max);
        printf("��ͳɼ���%.2f��\n", all);
        //ð������ɼ�
        int j;
        for (i = 0; i < stuNum - 1; i++)
        {
            for (j = 0; j < stuNum - i - 1; j++)
            {
                if (students[j].score < students[j + 1].score)
                {
                    Student temp = students[j];
                    students[j] = students[j + 1];
                    students[j + 1] = temp;
                }
            }
        }
        printf("�Ӹߵ���������ѧ���ɼ���\n");
        printf("��������\n");
        printf("ѧ��\t����\t�༶\t�ɼ�\n");
        sumpass=0;
        sumunpass=0;
        for (i = 0; i < stuNum; i++)
        {
            if(students[i].score >= pass)//��ӡ�ϸ�����
            {
                sumpass = sumpass + 1;
                printf("%d\t%s\t%s\t%.2f\n",students[i].id,students[i].name,students[i].classes,students[i].score);
            }
        }
        printf("����������\n");
        printf("ѧ��\t����\t�༶\t�ɼ�\n");
        for (i = 0; i < stuNum; i++)
        {
            if(students[i].score < pass)//��ӡ���ϸ�����
            {
                sumunpass = sumunpass + 1;
                printf("%d\t%s\t%s\t%.2f\n",students[i].id,students[i].name,students[i].classes,students[i].score);
            }
        }
        printf("����������%d ��\n",sumpass);
        printf("������������%d ��\n",sumunpass);
        printf("������Ϊ��%.2f%%\n",(float)sumpass/stuNum * 100);
    }
    else printf("����δ¼��ѧ���ɼ�����¼��ѧ�����ٷ�����\n");
}

//��������
void outputStudent()
{
    if(stuNum!=0)//�ж��Ƿ��Ѿ�¼��ѧ����Ϣ
    {
        FILE *fp = fopen("student.txt", "w");//ֻд��ʽ����student.txt�ı��ĵ�
        if (fp == nullptr)
        {
            printf("�����ļ�ʧ�ܣ�\n");
            return;//�жϺ���ִ�У�����outputStudent()����
        }
        int i;
        fprintf(fp, "ѧ��\t����\t�༶\t�ɼ�\n");
        for (i = 0; i < stuNum; i++)
        {
            fprintf(fp, "%d\t%s\t%s\t%.2f\n", students[i].id, students[i].name, students[i].classes, students[i].score);
        }
        printf("�����ѵ�����\n");
        fclose(fp);
    }
    else printf("��¼��ѧ����Ϣ�ٵ�������\n");
}