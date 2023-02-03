#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <Windows.h>


typedef struct _account {
    char acc_name[20];
    char acc_bankname[20];
    int acc_number;
    char acc_account[20];
    char acc_pass[5];
    int acc_money;
    char acc_balance[20];
}Account;//���� ����ü 

struct PASSWORD {
    char check[5]; // ���� ��й�ȣ Ȯ��
    char new1[5]; //�� ��й�ȣ
    char new2[5]; //�� ��й�ȣ Ȯ��
}; // ������ �޴� ��й�ȣ ����ü

struct BANKINFO {
    char bankname[256]; //���� �̸�
    char username[256]; //���� ���� �̸�
    int balance; // ���� �ܾ�
    char password[256]; //���� ��й�ȣ
}; //���� �⺻ ����

void ACCOUNT_INFO(void);//�������� ���� ���� �Լ�
void MENU(void); //���� �޴� �Լ�
int ACOUNT_MAKE(void); //���»��� �Լ�
int DEPOSIT(void); //�Ա� �Լ�
int WITHDRAW(void);//��� �Լ�
int SEND(void);//�۱� �Լ�
int BALANCE_CHECK(void);//�ܾ���ȸ �Լ�
void PASSWORD_CHANGE(void);//��й�ȣ ���� �Լ�
void ACCOUNT_LOCK(char* acc);//���� ���� �Լ�
int LOCK_CHECK(char* acc); //���� ���� ���� Ȯ�� �Լ�
int ACCOUNT_CHECK(char* acc); //���� ���� Ȯ�� �Լ�

int PASSWORD_CHECK(void); //������ �޴� ��й�ȣ Ȯ�� �Լ�
void SYSTEM_MENU(void); // ������ �޴� �Լ�
void BANKADD(void); //���� �߰� �Լ�
void ACCOUNT_UNLOCK(void); //���� ���� ���� �Լ�
void ATM_CHECK(void); //ATM �ܰ� Ȯ�� �Լ�
void ATM_ADD(void); //ATM �ܰ� �߰� �Լ�
void SYSTEM_PASSWORD_CHANGE(void);// ������ ��й�ȣ ���� �Լ�


Account person[100], tmp;

int count = 0, i, j, toAccount;

int main(void)
{
    int x;

    do
    {
        MENU();
        scanf_s("%d", &x);//�޴��� �Է� ���� 
        switch (x)
        {
        case 0://���α׷� ����
            printf("ATM�� ���α׷��� ����˴ϴ�.\n");
            break;
        case 1://���»���
            ACOUNT_MAKE();
            break;
        case 2://�Ա� 
            DEPOSIT();
            break;
        case 3://��� 
            WITHDRAW();
            break;
        case 4://�۱� 
            SEND();
            break;
        case 5://�ܾ���ȸ
            BALANCE_CHECK();
            break;
        case 6://��й�ȣ ����
            PASSWORD_CHANGE();
            break;
        case 7://�����ڸ޴�
            PASSWORD_CHECK();
            break;
        default: //�߸��� ���� �Է����� ��
            printf("0~7 ������ ���� �Է����ּ���.\n");
            Sleep(1000);
            break;
        }
    } while (x != 0);
    return 0;
}


////�Լ�!!
//�����Լ�
void MENU(void)
{
    system("cls");
    printf("=======ATM���α׷�=======\n");
    printf("1. ���»���\n2. �Ա�\n3. ���\n4. �۱�\n5. �ܾ���ȸ\n6. ��й�ȣ ����\n7. ������ �޴�\n0. ���α׷� ����\n");
    printf("=========================\n>> ");
}//���� �޴� �Լ�


void ACCOUNT_INFO(void) {

    int a;

    FILE* ftr1 = NULL;

    // ���� ���� ���� ���н� ���� 
    if ((ftr1 = fopen("��������.txt", "a")) == NULL) {
        printf("���� ���� ����");
        exit(1);
    }

    for (a = 0; a < count; a++)
    {
        fprintf(ftr1, "%s\t|%s\t|%d\t|%s\t|%d\n", person[a].acc_bankname, person[a].acc_name, person[a].acc_number, person[a].acc_pass, person[a].acc_money);
    }
    // ���� ���� 
    fclose(ftr1);
}

int ACOUNT_MAKE(void) {

    system("cls");

    FILE* bank, * newfile;
    char buffer[256];
    int count1 = 0, count2 = 0, END = 0, END2 = 0;

    printf("\n");

    if ((bank = fopen("����.txt", "r")) == NULL) {
        printf("���� ���� ����");
        exit(1);
    }

    printf("[���»���]\n");
    printf("\n===��ϵǾ� �ִ� ����===\n");
    while (fgets(buffer, 64, bank)) {
        if (strstr(buffer, "����")) {
            printf("%s", buffer);
            count2++;
        }
    }
    printf("========================\n");
    printf("\n");
    fclose(bank);

    if ((bank = fopen("����.txt", "r")) == NULL) {
        printf("���� ���� ����");
        exit(1);
    }
    if ((newfile = fopen("���� 2.txt", "w")) == NULL) {
        printf("���� ���� ����");
        exit(1);
    }

    printf("���� �̸��� �Է��Ͻÿ�: ");
    scanf("%s", person[count].acc_bankname);

    while ((fgets(buffer, 256, bank)) != NULL) {
        if (strstr(buffer, person[count].acc_bankname)) {
            fputs(buffer, newfile);

            printf("�̸� : ");
            scanf("%s", person[count].acc_name);

            srand(time(NULL));
            int b = 9, c, d;
            c = (int)pow(10, 8);
            d = (int)pow(10, 8);

            printf("���¹�ȣ ���� ���� \n");

            person[count].acc_number = (rand() % b + 1) * d + (rand() % c);
            printf("\n���¹�ȣ�� �����Ǿ����ϴ�.\n\n");
            printf("������ ���¹�ȣ : %d\n", person[count].acc_number);

            fprintf(newfile, "%d\n", person[count].acc_number);
        }
        else {
            if (strstr(buffer, "����")) {
                count1++;
            }
            fputs(buffer, newfile);
        }
    }

    if (count1 == count2) {
        printf("�ش� ������ ��ϵǾ� ���� ���� �����Դϴ�.\n\n");
        Sleep(2500);
        fclose(bank);
        fclose(newfile);
        remove("����.txt");
        if (rename("���� 2.txt", "����.txt") != 0) {
            printf("�̸� ���� ����\n");
        }
        return 0;
    }

    while (END2 != 1) {
        printf("��й�ȣ : ");
        scanf("%s", person[count].acc_pass);

        if (strlen(person[count].acc_pass) != 4) {
            printf("\n��й�ȣ�� 4�ڸ� ���ڷ� �Է����ֽñ� �ٶ��ϴ�.\n\n");
        }
        else
            END2 = 1;
    }

    printf("���� ������ �Ϸ��Ͽ����ϴ�.\n");

    person[count].acc_money = 0;

    count++;//�Էµ� ���� ������ ī��Ʈ 

    Sleep(2000);

    fclose(bank);
    fclose(newfile);

    remove("����.txt");
    if (rename("���� 2.txt", "����.txt") != 0) {
        printf("�̸� ���� ����\n");
    }
    ACCOUNT_INFO();

    system("cls");
    for (i = 0; i < count; i++) {
        printf("======================\n\n");
        printf("����: %s\n", person[i].acc_bankname);
        printf("���¹�ȣ: %d\n", person[i].acc_number);
        printf("�̸�: %s\n", person[i].acc_name);
        printf("��й�ȣ: %s\n\n", person[i].acc_pass);
        printf("======================\n");
    }

    system("pause");
    //}

}//���»��� �Լ�

int DEPOSIT(void) {

    FILE* account, * newfile;
    char bankbuffer[256];
    char buffer[256];
    char* ptr;
    char* arr[5] = { NULL, };
    char acc[20];
    int END = 0;
    int errcount = 0;
    int i = 0;
    int balance;

    system("cls");

    printf("[�Ա�]\n");
    printf("���¹�ȣ : ");
    scanf("%d", &tmp.acc_number);
    sprintf(acc, "%d", tmp.acc_number);

    if (ACCOUNT_CHECK(acc) == 1) {
        return 0;
    }

    if (LOCK_CHECK(acc) == 1) {
        return 0;
    }

    if ((account = fopen("��������.txt", "r")) == NULL) {
        printf("���� ���� ����");
        exit(1);
    }
    if ((newfile = fopen("��������2.txt", "w")) == NULL) {
        printf("���� ���� ����");
        exit(1);
    }

    while (fgets(buffer, 256, account) != NULL) {
        if (strstr(buffer, acc)) {
            ptr = strtok(buffer, "\t|");
            while (ptr != NULL) {
                arr[i] = ptr;
                i++;
                ptr = strtok(NULL, "\t|");
            }
            balance = atoi(arr[4]);

            do {
                printf("��й�ȣ : ");
                scanf("%s", tmp.acc_pass);
                if (strcmp(tmp.acc_pass, arr[3]) == 0) {
                    printf("�Աݱݾ� : ");
                    scanf("%d", &tmp.acc_money);
                    balance += tmp.acc_money;

                    printf("�ԱݵǾ����ϴ�.\n");

                    Sleep(2000);

                    system("cls");
                    printf("======= ��ǥ =======\n");
                    struct tm* t;
                    time_t timer;
                    timer = time(NULL);
                    t = localtime(&timer);

                    printf("%d-%d-%d     %d:%d:%d\n", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);

                    printf("����: %s\n", arr[0]);
                    printf("�Աݰ���: %s\n", arr[2]);
                    printf("����: %s\n", arr[1]);
                    printf("�Աݱݾ�: %d\n", tmp.acc_money);
                    printf("�����ܾ�: %d\n", balance);
                    printf("======================\n");

                    fprintf(newfile, "%s\t|%s\t|%s\t|%s\t|%d\n", arr[0], arr[1], arr[2], arr[3], balance);

                    END = 1;
                }
                else {
                    errcount++;
                    printf("��й�ȣ ����. �ٽ� �Է����ֽñ� �ٶ��ϴ�.\n");
                    if (errcount == 3) {
                        printf("��й�ȣ %dȸ ����. ���°� �����Ǿ����ϴ�.\n\n", errcount);
                        fprintf(newfile, "%s\t|%s\t|%s\t|%s\t|%s", arr[0], arr[1], arr[2], arr[3], arr[4]);
                        Sleep(2000);
                        ACCOUNT_LOCK(acc);
                        END = 1;
                    }
                    else
                        printf("��й�ȣ %dȸ ����. 3ȸ ������ ���°� �����˴ϴ�.\n", errcount);
                }

            } while (END != 1);

        }
        else {
            fputs(buffer, newfile);
        }
    }

    fclose(account);
    fclose(newfile);

    remove("��������.txt");
    if (rename("��������2.txt", "��������.txt") != 0) {
        printf("�̸� ���� ����\n");
    }

    system("pause");
}//�Ա� �Լ�

int WITHDRAW(void) {
    FILE* account, * newfile;
    char buffer[256];
    char* ptr;
    char* arr[5] = { NULL, };
    char acc[20];
    int END = 0;
    int errcount = 0;
    int i = 0;
    int balance;

    system("cls");

    printf("[���]\n");
    printf("���¹�ȣ : ");
    scanf("%d", &tmp.acc_number);
    sprintf(acc, "%d", tmp.acc_number);

    if (LOCK_CHECK(acc) == 1) {
        return 0;
    }

    if (ACCOUNT_CHECK(acc) == 1) {
        return 0;
    }

    if ((account = fopen("��������.txt", "r")) == NULL) {
        printf("���� ���� ����");
        exit(1);
    }
    if ((newfile = fopen("��������2.txt", "w")) == NULL) {
        printf("���� ���� ����");
        exit(1);
    }

    while (fgets(buffer, 256, account) != NULL) {
        if (strstr(buffer, acc)) {
            ptr = strtok(buffer, "\t|");
            while (ptr != NULL) {
                arr[i] = ptr;
                i++;
                ptr = strtok(NULL, "\t|");
            }
            balance = atoi(arr[4]);

            do {
                printf("��й�ȣ : ");
                scanf("%s", tmp.acc_pass);
                if (strcmp(tmp.acc_pass, arr[3]) == 0) {
                    printf("���� �ܾ� : %d\n", balance);
                    printf("��ݱݾ� : ");
                    scanf("%d", &tmp.acc_money);
                    balance -= tmp.acc_money;

                    if (balance >= 0) {
                        printf("��ݵǾ����ϴ�.\n");

                        Sleep(2000);

                        system("cls");
                        printf("======= ��ǥ =======\n");
                        struct tm* t;
                        time_t timer;
                        timer = time(NULL);
                        t = localtime(&timer);

                        printf("%d-%d-%d     %d:%d:%d\n", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);

                        printf("����: %s\n", arr[0]);
                        printf("��ݰ���: %s\n", arr[2]);
                        printf("����: %s\n", arr[1]);
                        printf("��ݱݾ�: %d\n", tmp.acc_money);
                        printf("�����ܾ�: %d\n", balance);
                        printf("======================\n");

                        fprintf(newfile, "%s\t|%s\t|%s\t|%s\t|%d\n", arr[0], arr[1], arr[2], arr[3], balance);

                        END = 1;
                    }
                    else {
                        printf("�ܾ��� �����մϴ�.\n");
                        Sleep(2000);
                        return 0;
                    }

                }
                else {
                    errcount++;
                    printf("��й�ȣ ����. �ٽ� �Է����ֽñ� �ٶ��ϴ�.\n");
                    if (errcount == 3) {
                        printf("��й�ȣ %dȸ ����. ���°� �����Ǿ����ϴ�.\n\n", errcount);
                        fprintf(newfile, "%s\t|%s\t|%s\t|%s\t|%s", arr[0], arr[1], arr[2], arr[3], arr[4]);
                        ACCOUNT_LOCK(acc);
                        Sleep(2000);
                        END = 1;
                    }
                    else
                        printf("��й�ȣ %dȸ ����. 3ȸ ������ ���°� �����˴ϴ�.\n", errcount);
                }

            } while (END != 1);

        }
        else {
            fputs(buffer, newfile);
        }
    }

    fclose(account);
    fclose(newfile);


    remove("��������.txt");
    if (rename("��������2.txt", "��������.txt") != 0) {
        printf("���� ����\n");
    }

    system("pause");

}//��� �Լ�


int SEND(void) {
    Account fileinfo[100] = { NULL, };
    FILE* account, * newfile;
    char buffer[256];
    char* ptr;
    char acc[20], acc2[20];
    int END = 0;
    int errcount = 0;
    int idx = 0, i = 0;
    int balance1, balance2;

    system("cls");

    printf("[�۱�]\n");
    printf("Ÿ �������� �۱� �� ������ 500���� �ΰ��˴ϴ�.\n");
    printf("�� ���� : ");
    scanf("%d", &tmp.acc_number);
    sprintf(acc, "%d", tmp.acc_number);

    if (LOCK_CHECK(acc) == 1) {
        return 0;
    }

    if (ACCOUNT_CHECK(acc) == 1) {
        return 0;
    }

    if ((account = fopen("��������.txt", "r")) == NULL) {
        printf("���� ���� ����");
        exit(1);
    }

    while (fgets(buffer, 256, account) != NULL) {
        ptr = strtok(buffer, "\t|");
        strcat(fileinfo[idx].acc_bankname, ptr);
        ptr = strtok(NULL, "\t|");
        strcat(fileinfo[idx].acc_name, ptr);
        ptr = strtok(NULL, "\t|");
        strcat(fileinfo[idx].acc_account, ptr);
        ptr = strtok(NULL, "\t|");
        strcat(fileinfo[idx].acc_pass, ptr);
        ptr = strtok(NULL, "\t|");
        strcat(fileinfo[idx].acc_balance, ptr);
        ptr = strtok(NULL, "\t|");
        idx++;
    }

    for (i = 0; i < idx; i++) {
        if (strcmp(acc, fileinfo[i].acc_account) == 0) {
            do {
                printf("��й�ȣ : ");
                scanf("%s", tmp.acc_pass);
                if (strcmp(tmp.acc_pass, fileinfo[i].acc_pass) == 0) {
                    balance1 = atoi(fileinfo[i].acc_balance);
                    printf("���� �ܾ� : %d\n", balance1);
                    printf("�ݾ� : ");
                    scanf("%d", &tmp.acc_money);
                    balance1 -= tmp.acc_money;

                    if (balance1 >= 0) {
                        printf("�Ա� ���� : ");
                        scanf("%d", &toAccount);
                        sprintf(acc2, "%d", toAccount);

                        if (LOCK_CHECK(acc2) == 1) {
                            return 0;
                        }

                        if (ACCOUNT_CHECK(acc2) == 1) {
                            return 0;
                        }

                        for (int p = 0; p < idx; p++) {
                            if (strcmp(acc2, fileinfo[p].acc_account) == 0) {
                                balance2 = atoi(fileinfo[p].acc_balance);
                                if (strcmp(fileinfo[i].acc_bankname, fileinfo[p].acc_bankname) == 0) {
                                    balance2 += tmp.acc_money;
                                }
                                else {
                                    balance1 -= 500;
                                    if (balance1 >= 0) {
                                        balance2 += tmp.acc_money;
                                    }
                                    else {
                                        printf("�ܾ��� �����մϴ�.\n");
                                        Sleep(2000);
                                        return 0;
                                    }
                                }

                                printf("�۱� �Ǿ����ϴ�.\n");

                                Sleep(2000);

                                system("cls");
                                printf("======= ��ǥ =======\n");
                                struct tm* t;
                                time_t timer;
                                timer = time(NULL);
                                t = localtime(&timer);

                                printf("%d-%d-%d     %d:%d:%d\n", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);

                                printf("����: %s\n", fileinfo[i].acc_bankname);
                                printf("�� ����: %d\n", tmp.acc_number);
                                printf("������: %s\n\n", fileinfo[i].acc_name);
                                printf("�Ա� ����: %d\n", toAccount);
                                printf("����: %s\n", fileinfo[p].acc_name);
                                printf("�����ݾ�: %d\n", tmp.acc_money);
                                printf("�����ܾ�: %d\n", balance1);
                                printf("======================\n");

                                sprintf(fileinfo[i].acc_balance, "%d\n", balance1);
                                sprintf(fileinfo[p].acc_balance, "%d\n", balance2);

                                END = 1;
                            }

                        }
                    }

                    else {
                        printf("�ܾ��� �����մϴ�.\n");
                        Sleep(2000);
                        return 0;
                    }

                }

                else {
                    errcount++;
                    printf("��й�ȣ ����. �ٽ� �Է����ֽñ� �ٶ��ϴ�.\n");
                    if (errcount == 3) {
                        printf("��й�ȣ %dȸ ����. ���°� �����Ǿ����ϴ�.\n\n", errcount);
                        ACCOUNT_LOCK(acc);
                        Sleep(2000);
                        END = 1;
                    }
                    else
                        printf("��й�ȣ %dȸ ����. 3ȸ ������ ���°� �����˴ϴ�.\n", errcount);
                }
            } while (END != 1);
        }
        else {
            continue;
        }
    }

    if ((newfile = fopen("��������2.txt", "w")) == NULL) {
        printf("���� ���� ����");
        exit(1);
    }

    for (i = 0; i < idx; i++) {
        if (i == 0) {
            fprintf(newfile, "%s\t|%s\t|%s\t\t|%s\t|%s", fileinfo[i].acc_bankname, fileinfo[i].acc_name, fileinfo[i].acc_account, fileinfo[i].acc_pass, fileinfo[i].acc_balance);
        }
        else {
            fprintf(newfile, "%s\t|%s\t|%s\t|%s\t|%s", fileinfo[i].acc_bankname, fileinfo[i].acc_name, fileinfo[i].acc_account, fileinfo[i].acc_pass, fileinfo[i].acc_balance);
        }
    }

    fclose(account);
    fclose(newfile);

    remove("��������.txt");
    if (rename("��������2.txt", "��������.txt") != 0) {
        printf("�̸� ���� ����\n");
    }

    system("pause");

    return 0;
} //�۱� �Լ�

int BALANCE_CHECK(void) {
    Account accountinfo[100] = { NULL, };
    FILE* account;
    char buffer[256];
    char* ptr;
    char acc[20];
    int idx = 0, i = 0;

    system("cls");

    printf("[�ܾ���ȸ]\n");
    printf("�ܾ� ��ȸ�� ���¸� �Է��ϼ��� : ");
    scanf("%d", &tmp.acc_number);
    sprintf(acc, "%d", tmp.acc_number);
    printf("\n");

    if (LOCK_CHECK(acc) == 1) {
        return 0;
    }

    if (ACCOUNT_CHECK(acc) == 1) {
        return 0;
    }

    if ((account = fopen("��������.txt", "r")) == NULL) {
        printf("���� ���� ����");
        exit(1);
    }

    while (fgets(buffer, 256, account) != NULL) {
        ptr = strtok(buffer, "\t|");
        strcat(accountinfo[idx].acc_bankname, ptr);
        ptr = strtok(NULL, "\t|");
        strcat(accountinfo[idx].acc_name, ptr);
        ptr = strtok(NULL, "\t|");
        strcat(accountinfo[idx].acc_account, ptr);
        ptr = strtok(NULL, "\t|");
        strcat(accountinfo[idx].acc_pass, ptr);
        ptr = strtok(NULL, "\t|");
        strcat(accountinfo[idx].acc_balance, ptr);
        ptr = strtok(NULL, "\t|");
        idx++;
    }

    for (i = 0; i < idx; i++) {
        if (strcmp(acc, accountinfo[i].acc_account) == 0) {
            printf("���� �ܾ� : %s", accountinfo[i].acc_balance);
            fclose(account);
            system("pause");
            return 0;
        }
    }
}//�ܾ� ��ȸ �Լ�

void PASSWORD_CHANGE(void) {
    Account info[100] = { NULL, };
    system("cls");

    char buffer[256];
    char* ptr;
    char acc[20];
    int idx = 0, i = 0;
    int errcount = 0;

    char new1[5], new2[5];
    int END = 0;

    FILE* ftr1, * newfile = NULL;

    if ((ftr1 = fopen("��������.txt", "r")) == NULL) {
        printf("���� ���� ����");
        exit(1);
    }

    if ((newfile = fopen("�������� 2.txt", "w")) == NULL) {
        printf("���� ���� ����");
        exit(1);
    }

    while (fgets(buffer, 256, ftr1) != NULL) {
        ptr = strtok(buffer, "\t|");
        strcat(info[idx].acc_bankname, ptr);
        ptr = strtok(NULL, "\t|");
        strcat(info[idx].acc_name, ptr);
        ptr = strtok(NULL, "\t|");
        strcat(info[idx].acc_account, ptr);
        ptr = strtok(NULL, "\t|");
        strcat(info[idx].acc_pass, ptr);
        ptr = strtok(NULL, "\t|");
        strcat(info[idx].acc_balance, ptr);
        ptr = strtok(NULL, "\t|");
        idx++;
    }

    printf("���¹�ȣ : ");
    scanf("%d", &tmp.acc_number);
    sprintf(acc, "%d", tmp.acc_number);

    for (i = 0; i < idx; i++) {
        if (strcmp(acc, info[i].acc_account) == 0) {
            do {
                printf("���� ��й�ȣ�� �Է����ּ���: ");
                scanf("%s", &tmp.acc_pass);

                if (strcmp(info[i].acc_pass, tmp.acc_pass) == 0) {
                    while (END != 1) {
                        printf("\n�� ��й�ȣ�� �Է����ּ��� (4�ڸ� ����) : ");
                        scanf("%s", new1);

                        if (strlen(new1) != 4) {
                            printf("\n��й�ȣ ������ ���� �ʽ��ϴ�. �ٽ� �Է����ּ���.\n");
                        }//�� ��й�ȣ�� �ڸ����� 4�ڸ��� �ƴ� ��
                        else {
                            printf("�� ��й�ȣ�� �ٽ� �Է����ּ��� (4�ڸ� ����) : ");
                            scanf("%s", new2);

                            //�� ��й�ȣ ��ġ
                            if (strcmp(new1, new2) == 0) {
                                strcpy(info[i].acc_pass, new1);
                                END = 1;
                            }

                            //�� ��й�ȣ ����ġ
                            else {
                                printf("\n��й�ȣ�� ��ġ���� �ʽ��ϴ�. �ٽ� �Է����ּ���.\n");
                            }
                        }
                    }
                }
                else {
                    errcount++;
                    printf("��й�ȣ ����. �ٽ� �Է����ֽñ� �ٶ��ϴ�.\n");
                    if (errcount == 3) {
                        printf("��й�ȣ %dȸ ����. ���°� �����Ǿ����ϴ�.\n\n", errcount);
                        ACCOUNT_LOCK(acc);
                        Sleep(2000);
                        END = 1;
                    }
                    else
                        printf("��й�ȣ %dȸ ����. 3ȸ ������ ���°� �����˴ϴ�.\n", errcount);
                }
            } while (END != 1);
        }
    }

    printf("\n��й�ȣ�� ����Ǿ����ϴ�.\n");

    for (i = 0; i < idx; i++) {
        if (i == 0) {
            fprintf(newfile, "%s\t|%s\t|%s\t\t|%s\t|%s", info[i].acc_bankname, info[i].acc_name, info[i].acc_account, info[i].acc_pass, info[i].acc_balance);
        }
        else {
            fprintf(newfile, "%s\t|%s\t|%s\t|%s\t|%s", info[i].acc_bankname, info[i].acc_name, info[i].acc_account, info[i].acc_pass, info[i].acc_balance);
        }
    }
    system("pause");

    fclose(ftr1);
    fclose(newfile);

    remove("��������.txt");

    if (rename("�������� 2.txt", "��������.txt") != 0) {
        printf("�̸� ���� ����\n");
    }
}//��й�ȣ ���� �Լ�

void ACCOUNT_LOCK(char* acc) {
    FILE* bank, * newfile;
    char buffer[256];

    if ((bank = fopen("����.txt", "r")) == NULL) {
        printf("���� ���� ����");
        exit(1);
    }

    if ((newfile = fopen("����2.txt", "w")) == NULL) {
        printf("���� ���� ����");
        exit(1);
    }

    while ((fgets(buffer, 256, bank)) != NULL) {
        if (strstr(buffer, acc)) {
            fprintf(newfile, "%s x\n", acc);
        }
        else {
            fputs(buffer, newfile);
        }
    }

    fclose(bank);
    fclose(newfile);

    remove("����.txt");
    if (rename("����2.txt", "����.txt") != 0) {
        printf("�̸� ���� ����\n");
    }
}//���� ���� �Լ�


int LOCK_CHECK(char* acc) {
    int k = 0;
    FILE* bank;
    char buffer[256];

    if ((bank = fopen("����.txt", "r")) == NULL) {
        printf("���� ���� ����");
        exit(1);
    }

    while ((fgets(buffer, 256, bank)) != NULL) {
        if (strstr(buffer, acc)) {
            if (strstr(buffer, "x")) {
                printf("�ش� ���´� ���� �����Դϴ�.\n");
                Sleep(2000);
                k = 1;
            }
        }
    }

    fclose(bank);
    return k;
}//���� ���� Ȯ�� �Լ�

int ACCOUNT_CHECK(char* acc) {
    int count1 = 0, count2 = 0;
    FILE* bank;
    char buffer[256];

    if ((bank = fopen("����.txt", "r")) == NULL) {
        printf("���� ���� ����");
        exit(1);
    }

    while ((fgets(buffer, 256, bank)) != NULL) {
        if (strstr(buffer, acc)) {
            fclose(bank);
            return 0;
        }
        else
            count2++;
        count1++;
    }

    if (count1 == count2) {
        printf("��ϵǾ� ���� ���� ���¹�ȣ�Դϴ�.\n");
        Sleep(2000);
        fclose(bank);
        return 1;
    }

} //���� ���� Ȯ�� �Լ�




//������ �Լ�
int PASSWORD_CHECK(void) {
    struct BANKINFO B;
    FILE* atm;
    char buffer[256];
    char check[256];
    int END = 0;

    if ((atm = fopen("atm�ܰ�.txt", "r")) == NULL) {
        printf("���� ���� ����");
        exit(1);
    }

    fgets(buffer, 256, atm);
    fscanf(atm, "%s %s %d %s", B.bankname, B.username, &B.balance, B.password);

    do {
        printf("��й�ȣ�� �Է��ϼ��� : ");
        scanf("%s", check);
        printf("\n");

        if (strcmp(check, B.password) == 0) {
            fclose(atm);
            SYSTEM_MENU();
            return 0;
            END = 1;
        }
        else {
            printf("\n��й�ȣ�� ��ġ���� �ʽ��ϴ�. �ٽ� �Է����ּ���.\n");
        }
    } while (END != 1);

    fclose(atm);
}//��й�ȣ Ȯ�� �Լ�

void SYSTEM_MENU(void) {
    int choice; //�޴� ���� ����

    do {
        system("cls");

        printf("=======������ �޴�=======\n");
        printf("1. ���� �߰�\n2. ���� ���� ����\n3. ATM�ܰ� Ȯ��\n4. ATM�ܰ� ����\n5. ������ ��й�ȣ ����\n0. ���θ޴�\n");
        printf("=========================\n>> ");
        scanf("%d", &choice);
        printf("\n");

        switch (choice) {
        case 0: //���θ޴�
            printf("���θ޴��� ���ư��ϴ�.\n\n");
            Sleep(2000);
            break;
        case 1: //���� �߰�
            BANKADD();
            break;
        case 2: //���� ���� ����
            ACCOUNT_UNLOCK();
            break;
        case 3: //ATM�ܰ� Ȯ��
            ATM_CHECK();
            break;
        case 4: //ATM�ܰ� ����
            ATM_ADD();
            break;
        case 5: //������ ��й�ȣ ����
            SYSTEM_PASSWORD_CHANGE();
            break;
        default: //�߸��� ���� �Է����� ��
            printf("0~5 ������ ���� �Է����ּ���.\n");
            Sleep(1000);
            break;
        }
    } while (choice != 0);
}// ������ �޴� �Լ�

void BANKADD(void) {
    system("cls");

    FILE* bank;
    char bank_add[256];

    if ((bank = fopen("����.txt", "a")) == NULL) {
        printf("���� ���� ����");
        exit(1);
    }

    printf("�߰��� ������ �Է����ּ��� : ");
    scanf("%s", bank_add);

    fprintf(bank, "%s\n", bank_add);
    printf("%s��(��) �߰��Ǿ����ϴ�.\n\n", bank_add);
    fclose(bank);
    Sleep(2000);
}// ���� �߰� �Լ�

void ACCOUNT_UNLOCK(void) {
    system("cls");

    FILE* bank, * newfile;
    char buffer[256];
    char account[256];
    int count1 = 0, count2 = 0;

    if ((bank = fopen("����.txt", "r")) == NULL) {
        printf("���� ���� ����");
        exit(1);
    }

    if ((newfile = fopen("����2.txt", "w")) == NULL) {
        printf("���� ���� ����");
        exit(1);
    }

    printf("������ ������ ���¹�ȣ�� �Է��ϼ��� : ");
    scanf("%s", account);

    while ((fgets(buffer, 256, bank)) != NULL) {
        if (strstr(buffer, account)) {
            if (strstr(buffer, "x")) {
                fprintf(newfile, "%s\n", account);
                printf("%s ���°� �����Ǿ����ϴ�.\n", account);
            }
            else {
                printf("�ش� ���´� ���� ���°� �ƴմϴ�.\n");
                fputs(buffer, newfile);
            }
        }
        else {
            fputs(buffer, newfile);
            count2++;
        }
        count1++;
    }
    if (count2 == count1) {
        printf("%s ���´� ���� �����Դϴ�.\n", account);
    }

    fclose(bank);
    fclose(newfile);

    remove("����.txt");
    if (rename("����2.txt", "����.txt") != 0) {
        printf("�̸� ���� ����\n");
    }
    Sleep(2000);
}// ���� ���� ���� �Լ�

void ATM_CHECK(void) {
    system("cls");

    FILE* atm;
    char buffer[256];
    struct BANKINFO B;

    if ((atm = fopen("atm�ܰ�.txt", "r")) == NULL) {
        printf("���� ���� ����");
        exit(1);
    }
    fgets(buffer, 256, atm);
    fscanf(atm, "%s %s %d %s", B.bankname, B.username, &B.balance, B.password);
    printf("ATM�� ���� �ܰ�� %d�� �Դϴ�.\n", B.balance);

    fclose(atm);
    Sleep(2000);
}// ATM �ܰ� Ȯ�� �Լ�

void ATM_ADD(void) {
    system("cls");

    FILE* atm, * newfile;
    char buffer[256];
    int money;
    struct BANKINFO B;

    if ((atm = fopen("atm�ܰ�.txt", "r")) == NULL) {
        printf("���� ���� ����");
        exit(1);
    }

    if ((newfile = fopen("atm�ܰ�2.txt", "w")) == NULL) {
        printf("���� ���� ����");
        exit(1);
    }

    fgets(buffer, 256, atm);

    fscanf(atm, "%s %s %d %s", B.bankname, B.username, &B.balance, B.password);
    printf("�߰��� �ݾ��� �Է��ϼ��� : ");
    scanf("%d", &money);
    B.balance += money;

    printf("ATM�� ���� �ܰ�� %d�� �Դϴ�.\n", B.balance);

    fputs(buffer, newfile);
    fprintf(newfile, "    %s   %s   %d       %s\n", B.bankname, B.username, B.balance, B.password);

    fclose(atm);
    fclose(newfile);

    remove("atm�ܰ�.txt");
    if (rename("atm�ܰ�2.txt", "atm�ܰ�.txt") != 0) {
        printf("�̸� ���� ����\n");
    }
    Sleep(2000);
}//ATM �ܰ� �߰� �Լ�

void SYSTEM_PASSWORD_CHANGE() {
    system("cls");

    struct PASSWORD P;
    struct BANKINFO B;
    FILE* atm, * newfile;
    char buffer[256];
    int END = 0;

    if ((atm = fopen("atm�ܰ�.txt", "r")) == NULL) {
        printf("���� ���� ����");
        exit(1);
    }

    if ((newfile = fopen("atm�ܰ�2.txt", "w")) == NULL) {
        printf("���� ���� ����");
        exit(1);
    }

    fgets(buffer, 256, atm);
    fscanf(atm, "%s %s %d %s", B.bankname, B.username, &B.balance, B.password);

    do {
        printf("���� ��й�ȣ�� �Է����ּ��� : ");
        scanf("%s", P.check);

        //���� ��й�ȣ ��ġ
        if (strcmp(B.password, P.check) == 0) {
            while (END != 1) {
                printf("\n�� ��й�ȣ�� �Է����ּ��� (4�ڸ� ����) : ");
                scanf("%s", P.new1);
                printf("�� ��й�ȣ�� �ٽ� �Է����ּ��� (4�ڸ� ����) : ");
                scanf("%s", P.new2);

                //�� ��й�ȣ�� �ڸ����� 4�ڸ��� �ƴ� ��
                if (strlen(P.new1) != 4) {
                    printf("\n��й�ȣ ������ ���� �ʽ��ϴ�. �ٽ� �Է����ּ���.\n");
                }
                else {
                    //�� ��й�ȣ ��ġ
                    if (strcmp(P.new1, P.new2) == 0) {
                        fputs(buffer, newfile);
                        fprintf(newfile, "    %s   %s   %d       %s\n", B.bankname, B.username, B.balance, P.new1);
                        printf("\n��й�ȣ�� ����Ǿ����ϴ�.\n");
                        END = 1;
                    }

                    //�� ��й�ȣ ����ġ
                    else {
                        printf("\n��й�ȣ�� ��ġ���� �ʽ��ϴ�. �ٽ� �Է����ּ���.\n");
                    }
                }
            }
        }
        //���� ��й�ȣ ����ġ
        else {
            printf("\n��й�ȣ�� ��ġ���� �ʽ��ϴ�. �ٽ� �Է����ּ���.\n\n");
        }
    } while (END != 1);

    fclose(atm);
    fclose(newfile);

    remove("atm�ܰ�.txt");
    if (rename("atm�ܰ�2.txt", "atm�ܰ�.txt") != 0) {
        printf("�̸� ���� ����\n");
    }
    Sleep(2000);
} //������ ��й�ȣ ���� �Լ�
