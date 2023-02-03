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
}Account;//계좌 구조체 

struct PASSWORD {
    char check[5]; // 현재 비밀번호 확인
    char new1[5]; //새 비밀번호
    char new2[5]; //새 비밀번호 확인
}; // 관리자 메뉴 비밀번호 구조체

struct BANKINFO {
    char bankname[256]; //은행 이름
    char username[256]; //계좌 주인 이름
    int balance; // 계좌 잔액
    char password[256]; //계좌 비밀번호
}; //은행 기본 정보

void ACCOUNT_INFO(void);//계좌정보 파일 저장 함수
void MENU(void); //메인 메뉴 함수
int ACOUNT_MAKE(void); //계좌생성 함수
int DEPOSIT(void); //입금 함수
int WITHDRAW(void);//출금 함수
int SEND(void);//송금 함수
int BALANCE_CHECK(void);//잔액조회 함수
void PASSWORD_CHANGE(void);//비밀번호 변경 함수
void ACCOUNT_LOCK(char* acc);//계좌 정지 함수
int LOCK_CHECK(char* acc); //계좌 정지 상태 확인 함수
int ACCOUNT_CHECK(char* acc); //계좌 유무 확인 함수

int PASSWORD_CHECK(void); //관리자 메뉴 비밀번호 확인 함수
void SYSTEM_MENU(void); // 관리자 메뉴 함수
void BANKADD(void); //은행 추가 함수
void ACCOUNT_UNLOCK(void); //계좌 정지 해제 함수
void ATM_CHECK(void); //ATM 잔고 확인 함수
void ATM_ADD(void); //ATM 잔고 추가 함수
void SYSTEM_PASSWORD_CHANGE(void);// 관리자 비밀번호 변경 함수


Account person[100], tmp;

int count = 0, i, j, toAccount;

int main(void)
{
    int x;

    do
    {
        MENU();
        scanf_s("%d", &x);//메뉴를 입력 받음 
        switch (x)
        {
        case 0://프로그램 종료
            printf("ATM기 프로그램이 종료됩니다.\n");
            break;
        case 1://계좌생성
            ACOUNT_MAKE();
            break;
        case 2://입금 
            DEPOSIT();
            break;
        case 3://출금 
            WITHDRAW();
            break;
        case 4://송금 
            SEND();
            break;
        case 5://잔액조회
            BALANCE_CHECK();
            break;
        case 6://비밀번호 변경
            PASSWORD_CHANGE();
            break;
        case 7://관리자메뉴
            PASSWORD_CHECK();
            break;
        default: //잘못된 수를 입력했을 때
            printf("0~7 사이의 수를 입력해주세요.\n");
            Sleep(1000);
            break;
        }
    } while (x != 0);
    return 0;
}


////함수!!
//메인함수
void MENU(void)
{
    system("cls");
    printf("=======ATM프로그램=======\n");
    printf("1. 계좌생성\n2. 입금\n3. 출금\n4. 송금\n5. 잔액조회\n6. 비밀번호 변경\n7. 관리자 메뉴\n0. 프로그램 종료\n");
    printf("=========================\n>> ");
}//메인 메뉴 함수


void ACCOUNT_INFO(void) {

    int a;

    FILE* ftr1 = NULL;

    // 만약 파일 오픈 실패시 종료 
    if ((ftr1 = fopen("계좌정보.txt", "a")) == NULL) {
        printf("파일 열기 실패");
        exit(1);
    }

    for (a = 0; a < count; a++)
    {
        fprintf(ftr1, "%s\t|%s\t|%d\t|%s\t|%d\n", person[a].acc_bankname, person[a].acc_name, person[a].acc_number, person[a].acc_pass, person[a].acc_money);
    }
    // 파일 닫음 
    fclose(ftr1);
}

int ACOUNT_MAKE(void) {

    system("cls");

    FILE* bank, * newfile;
    char buffer[256];
    int count1 = 0, count2 = 0, END = 0, END2 = 0;

    printf("\n");

    if ((bank = fopen("은행.txt", "r")) == NULL) {
        printf("파일 열기 실패");
        exit(1);
    }

    printf("[계좌생성]\n");
    printf("\n===등록되어 있는 은행===\n");
    while (fgets(buffer, 64, bank)) {
        if (strstr(buffer, "은행")) {
            printf("%s", buffer);
            count2++;
        }
    }
    printf("========================\n");
    printf("\n");
    fclose(bank);

    if ((bank = fopen("은행.txt", "r")) == NULL) {
        printf("파일 열기 실패");
        exit(1);
    }
    if ((newfile = fopen("은행 2.txt", "w")) == NULL) {
        printf("파일 열기 실패");
        exit(1);
    }

    printf("은행 이름을 입력하시오: ");
    scanf("%s", person[count].acc_bankname);

    while ((fgets(buffer, 256, bank)) != NULL) {
        if (strstr(buffer, person[count].acc_bankname)) {
            fputs(buffer, newfile);

            printf("이름 : ");
            scanf("%s", person[count].acc_name);

            srand(time(NULL));
            int b = 9, c, d;
            c = (int)pow(10, 8);
            d = (int)pow(10, 8);

            printf("계좌번호 랜덤 생성 \n");

            person[count].acc_number = (rand() % b + 1) * d + (rand() % c);
            printf("\n계좌번호가 생성되었습니다.\n\n");
            printf("생성된 계좌번호 : %d\n", person[count].acc_number);

            fprintf(newfile, "%d\n", person[count].acc_number);
        }
        else {
            if (strstr(buffer, "은행")) {
                count1++;
            }
            fputs(buffer, newfile);
        }
    }

    if (count1 == count2) {
        printf("해당 은행은 등록되어 있지 않은 은행입니다.\n\n");
        Sleep(2500);
        fclose(bank);
        fclose(newfile);
        remove("은행.txt");
        if (rename("은행 2.txt", "은행.txt") != 0) {
            printf("이름 변경 실패\n");
        }
        return 0;
    }

    while (END2 != 1) {
        printf("비밀번호 : ");
        scanf("%s", person[count].acc_pass);

        if (strlen(person[count].acc_pass) != 4) {
            printf("\n비밀번호는 4자리 숫자로 입력해주시길 바랍니다.\n\n");
        }
        else
            END2 = 1;
    }

    printf("계좌 생성을 완료하였습니다.\n");

    person[count].acc_money = 0;

    count++;//입력된 계좌 갯수를 카운트 

    Sleep(2000);

    fclose(bank);
    fclose(newfile);

    remove("은행.txt");
    if (rename("은행 2.txt", "은행.txt") != 0) {
        printf("이름 변경 실패\n");
    }
    ACCOUNT_INFO();

    system("cls");
    for (i = 0; i < count; i++) {
        printf("======================\n\n");
        printf("은행: %s\n", person[i].acc_bankname);
        printf("계좌번호: %d\n", person[i].acc_number);
        printf("이름: %s\n", person[i].acc_name);
        printf("비밀번호: %s\n\n", person[i].acc_pass);
        printf("======================\n");
    }

    system("pause");
    //}

}//계좌생성 함수

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

    printf("[입금]\n");
    printf("계좌번호 : ");
    scanf("%d", &tmp.acc_number);
    sprintf(acc, "%d", tmp.acc_number);

    if (ACCOUNT_CHECK(acc) == 1) {
        return 0;
    }

    if (LOCK_CHECK(acc) == 1) {
        return 0;
    }

    if ((account = fopen("계좌정보.txt", "r")) == NULL) {
        printf("파일 열기 실패");
        exit(1);
    }
    if ((newfile = fopen("계좌정보2.txt", "w")) == NULL) {
        printf("파일 열기 실패");
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
                printf("비밀번호 : ");
                scanf("%s", tmp.acc_pass);
                if (strcmp(tmp.acc_pass, arr[3]) == 0) {
                    printf("입금금액 : ");
                    scanf("%d", &tmp.acc_money);
                    balance += tmp.acc_money;

                    printf("입금되었습니다.\n");

                    Sleep(2000);

                    system("cls");
                    printf("======= 명세표 =======\n");
                    struct tm* t;
                    time_t timer;
                    timer = time(NULL);
                    t = localtime(&timer);

                    printf("%d-%d-%d     %d:%d:%d\n", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);

                    printf("은행: %s\n", arr[0]);
                    printf("입금계좌: %s\n", arr[2]);
                    printf("성명: %s\n", arr[1]);
                    printf("입금금액: %d\n", tmp.acc_money);
                    printf("현재잔액: %d\n", balance);
                    printf("======================\n");

                    fprintf(newfile, "%s\t|%s\t|%s\t|%s\t|%d\n", arr[0], arr[1], arr[2], arr[3], balance);

                    END = 1;
                }
                else {
                    errcount++;
                    printf("비밀번호 오류. 다시 입력해주시길 바랍니다.\n");
                    if (errcount == 3) {
                        printf("비밀번호 %d회 오류. 계좌가 정지되었습니다.\n\n", errcount);
                        fprintf(newfile, "%s\t|%s\t|%s\t|%s\t|%s", arr[0], arr[1], arr[2], arr[3], arr[4]);
                        Sleep(2000);
                        ACCOUNT_LOCK(acc);
                        END = 1;
                    }
                    else
                        printf("비밀번호 %d회 오류. 3회 오류시 계좌가 정지됩니다.\n", errcount);
                }

            } while (END != 1);

        }
        else {
            fputs(buffer, newfile);
        }
    }

    fclose(account);
    fclose(newfile);

    remove("계좌정보.txt");
    if (rename("계좌정보2.txt", "계좌정보.txt") != 0) {
        printf("이름 변경 실패\n");
    }

    system("pause");
}//입금 함수

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

    printf("[출금]\n");
    printf("계좌번호 : ");
    scanf("%d", &tmp.acc_number);
    sprintf(acc, "%d", tmp.acc_number);

    if (LOCK_CHECK(acc) == 1) {
        return 0;
    }

    if (ACCOUNT_CHECK(acc) == 1) {
        return 0;
    }

    if ((account = fopen("계좌정보.txt", "r")) == NULL) {
        printf("파일 열기 실패");
        exit(1);
    }
    if ((newfile = fopen("계좌정보2.txt", "w")) == NULL) {
        printf("파일 열기 실패");
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
                printf("비밀번호 : ");
                scanf("%s", tmp.acc_pass);
                if (strcmp(tmp.acc_pass, arr[3]) == 0) {
                    printf("현재 잔액 : %d\n", balance);
                    printf("출금금액 : ");
                    scanf("%d", &tmp.acc_money);
                    balance -= tmp.acc_money;

                    if (balance >= 0) {
                        printf("출금되었습니다.\n");

                        Sleep(2000);

                        system("cls");
                        printf("======= 명세표 =======\n");
                        struct tm* t;
                        time_t timer;
                        timer = time(NULL);
                        t = localtime(&timer);

                        printf("%d-%d-%d     %d:%d:%d\n", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);

                        printf("은행: %s\n", arr[0]);
                        printf("출금계좌: %s\n", arr[2]);
                        printf("성명: %s\n", arr[1]);
                        printf("출금금액: %d\n", tmp.acc_money);
                        printf("현재잔액: %d\n", balance);
                        printf("======================\n");

                        fprintf(newfile, "%s\t|%s\t|%s\t|%s\t|%d\n", arr[0], arr[1], arr[2], arr[3], balance);

                        END = 1;
                    }
                    else {
                        printf("잔액이 부족합니다.\n");
                        Sleep(2000);
                        return 0;
                    }

                }
                else {
                    errcount++;
                    printf("비밀번호 오류. 다시 입력해주시길 바랍니다.\n");
                    if (errcount == 3) {
                        printf("비밀번호 %d회 오류. 계좌가 정지되었습니다.\n\n", errcount);
                        fprintf(newfile, "%s\t|%s\t|%s\t|%s\t|%s", arr[0], arr[1], arr[2], arr[3], arr[4]);
                        ACCOUNT_LOCK(acc);
                        Sleep(2000);
                        END = 1;
                    }
                    else
                        printf("비밀번호 %d회 오류. 3회 오류시 계좌가 정지됩니다.\n", errcount);
                }

            } while (END != 1);

        }
        else {
            fputs(buffer, newfile);
        }
    }

    fclose(account);
    fclose(newfile);


    remove("계좌정보.txt");
    if (rename("계좌정보2.txt", "계좌정보.txt") != 0) {
        printf("변경 실패\n");
    }

    system("pause");

}//출금 함수


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

    printf("[송금]\n");
    printf("타 은행으로 송금 시 수수료 500원이 부과됩니다.\n");
    printf("내 계좌 : ");
    scanf("%d", &tmp.acc_number);
    sprintf(acc, "%d", tmp.acc_number);

    if (LOCK_CHECK(acc) == 1) {
        return 0;
    }

    if (ACCOUNT_CHECK(acc) == 1) {
        return 0;
    }

    if ((account = fopen("계좌정보.txt", "r")) == NULL) {
        printf("파일 열기 실패");
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
                printf("비밀번호 : ");
                scanf("%s", tmp.acc_pass);
                if (strcmp(tmp.acc_pass, fileinfo[i].acc_pass) == 0) {
                    balance1 = atoi(fileinfo[i].acc_balance);
                    printf("현재 잔액 : %d\n", balance1);
                    printf("금액 : ");
                    scanf("%d", &tmp.acc_money);
                    balance1 -= tmp.acc_money;

                    if (balance1 >= 0) {
                        printf("입금 계좌 : ");
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
                                        printf("잔액이 부족합니다.\n");
                                        Sleep(2000);
                                        return 0;
                                    }
                                }

                                printf("송금 되었습니다.\n");

                                Sleep(2000);

                                system("cls");
                                printf("======= 명세표 =======\n");
                                struct tm* t;
                                time_t timer;
                                timer = time(NULL);
                                t = localtime(&timer);

                                printf("%d-%d-%d     %d:%d:%d\n", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);

                                printf("은행: %s\n", fileinfo[i].acc_bankname);
                                printf("내 계좌: %d\n", tmp.acc_number);
                                printf("예금주: %s\n\n", fileinfo[i].acc_name);
                                printf("입금 계좌: %d\n", toAccount);
                                printf("성명: %s\n", fileinfo[p].acc_name);
                                printf("보낸금액: %d\n", tmp.acc_money);
                                printf("현재잔액: %d\n", balance1);
                                printf("======================\n");

                                sprintf(fileinfo[i].acc_balance, "%d\n", balance1);
                                sprintf(fileinfo[p].acc_balance, "%d\n", balance2);

                                END = 1;
                            }

                        }
                    }

                    else {
                        printf("잔액이 부족합니다.\n");
                        Sleep(2000);
                        return 0;
                    }

                }

                else {
                    errcount++;
                    printf("비밀번호 오류. 다시 입력해주시길 바랍니다.\n");
                    if (errcount == 3) {
                        printf("비밀번호 %d회 오류. 계좌가 정지되었습니다.\n\n", errcount);
                        ACCOUNT_LOCK(acc);
                        Sleep(2000);
                        END = 1;
                    }
                    else
                        printf("비밀번호 %d회 오류. 3회 오류시 계좌가 정지됩니다.\n", errcount);
                }
            } while (END != 1);
        }
        else {
            continue;
        }
    }

    if ((newfile = fopen("계좌정보2.txt", "w")) == NULL) {
        printf("파일 열기 실패");
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

    remove("계좌정보.txt");
    if (rename("계좌정보2.txt", "계좌정보.txt") != 0) {
        printf("이름 변경 실패\n");
    }

    system("pause");

    return 0;
} //송금 함수

int BALANCE_CHECK(void) {
    Account accountinfo[100] = { NULL, };
    FILE* account;
    char buffer[256];
    char* ptr;
    char acc[20];
    int idx = 0, i = 0;

    system("cls");

    printf("[잔액조회]\n");
    printf("잔액 조회할 계좌를 입력하세요 : ");
    scanf("%d", &tmp.acc_number);
    sprintf(acc, "%d", tmp.acc_number);
    printf("\n");

    if (LOCK_CHECK(acc) == 1) {
        return 0;
    }

    if (ACCOUNT_CHECK(acc) == 1) {
        return 0;
    }

    if ((account = fopen("계좌정보.txt", "r")) == NULL) {
        printf("파일 열기 실패");
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
            printf("현재 잔액 : %s", accountinfo[i].acc_balance);
            fclose(account);
            system("pause");
            return 0;
        }
    }
}//잔액 조회 함수

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

    if ((ftr1 = fopen("계좌정보.txt", "r")) == NULL) {
        printf("파일 열기 실패");
        exit(1);
    }

    if ((newfile = fopen("계좌정보 2.txt", "w")) == NULL) {
        printf("파일 열기 실패");
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

    printf("계좌번호 : ");
    scanf("%d", &tmp.acc_number);
    sprintf(acc, "%d", tmp.acc_number);

    for (i = 0; i < idx; i++) {
        if (strcmp(acc, info[i].acc_account) == 0) {
            do {
                printf("현재 비밀번호를 입력해주세요: ");
                scanf("%s", &tmp.acc_pass);

                if (strcmp(info[i].acc_pass, tmp.acc_pass) == 0) {
                    while (END != 1) {
                        printf("\n새 비밀번호를 입력해주세요 (4자리 숫자) : ");
                        scanf("%s", new1);

                        if (strlen(new1) != 4) {
                            printf("\n비밀번호 형식이 맞지 않습니다. 다시 입력해주세요.\n");
                        }//새 비밀번호의 자리수가 4자리가 아닐 때
                        else {
                            printf("새 비밀번호를 다시 입력해주세요 (4자리 숫자) : ");
                            scanf("%s", new2);

                            //새 비밀번호 일치
                            if (strcmp(new1, new2) == 0) {
                                strcpy(info[i].acc_pass, new1);
                                END = 1;
                            }

                            //새 비밀번호 불일치
                            else {
                                printf("\n비밀번호가 일치하지 않습니다. 다시 입력해주세요.\n");
                            }
                        }
                    }
                }
                else {
                    errcount++;
                    printf("비밀번호 오류. 다시 입력해주시길 바랍니다.\n");
                    if (errcount == 3) {
                        printf("비밀번호 %d회 오류. 계좌가 정지되었습니다.\n\n", errcount);
                        ACCOUNT_LOCK(acc);
                        Sleep(2000);
                        END = 1;
                    }
                    else
                        printf("비밀번호 %d회 오류. 3회 오류시 계좌가 정지됩니다.\n", errcount);
                }
            } while (END != 1);
        }
    }

    printf("\n비밀번호가 변경되었습니다.\n");

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

    remove("계좌정보.txt");

    if (rename("계좌정보 2.txt", "계좌정보.txt") != 0) {
        printf("이름 변경 실패\n");
    }
}//비밀번호 변경 함수

void ACCOUNT_LOCK(char* acc) {
    FILE* bank, * newfile;
    char buffer[256];

    if ((bank = fopen("은행.txt", "r")) == NULL) {
        printf("파일 열기 실패");
        exit(1);
    }

    if ((newfile = fopen("은행2.txt", "w")) == NULL) {
        printf("파일 열기 실패");
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

    remove("은행.txt");
    if (rename("은행2.txt", "은행.txt") != 0) {
        printf("이름 변경 실패\n");
    }
}//계좌 정지 함수


int LOCK_CHECK(char* acc) {
    int k = 0;
    FILE* bank;
    char buffer[256];

    if ((bank = fopen("은행.txt", "r")) == NULL) {
        printf("파일 열기 실패");
        exit(1);
    }

    while ((fgets(buffer, 256, bank)) != NULL) {
        if (strstr(buffer, acc)) {
            if (strstr(buffer, "x")) {
                printf("해당 계좌는 정지 상태입니다.\n");
                Sleep(2000);
                k = 1;
            }
        }
    }

    fclose(bank);
    return k;
}//계좌 정지 확인 함수

int ACCOUNT_CHECK(char* acc) {
    int count1 = 0, count2 = 0;
    FILE* bank;
    char buffer[256];

    if ((bank = fopen("은행.txt", "r")) == NULL) {
        printf("파일 열기 실패");
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
        printf("등록되어 있지 않은 계좌번호입니다.\n");
        Sleep(2000);
        fclose(bank);
        return 1;
    }

} //계좌 유무 확인 함수




//관리자 함수
int PASSWORD_CHECK(void) {
    struct BANKINFO B;
    FILE* atm;
    char buffer[256];
    char check[256];
    int END = 0;

    if ((atm = fopen("atm잔고.txt", "r")) == NULL) {
        printf("파일 열기 실패");
        exit(1);
    }

    fgets(buffer, 256, atm);
    fscanf(atm, "%s %s %d %s", B.bankname, B.username, &B.balance, B.password);

    do {
        printf("비밀번호를 입력하세요 : ");
        scanf("%s", check);
        printf("\n");

        if (strcmp(check, B.password) == 0) {
            fclose(atm);
            SYSTEM_MENU();
            return 0;
            END = 1;
        }
        else {
            printf("\n비밀번호가 일치하지 않습니다. 다시 입력해주세요.\n");
        }
    } while (END != 1);

    fclose(atm);
}//비밀번호 확인 함수

void SYSTEM_MENU(void) {
    int choice; //메뉴 선택 변수

    do {
        system("cls");

        printf("=======관리자 메뉴=======\n");
        printf("1. 은행 추가\n2. 계좌 정지 해제\n3. ATM잔고 확인\n4. ATM잔고 보충\n5. 관리자 비밀번호 변경\n0. 메인메뉴\n");
        printf("=========================\n>> ");
        scanf("%d", &choice);
        printf("\n");

        switch (choice) {
        case 0: //메인메뉴
            printf("메인메뉴로 돌아갑니다.\n\n");
            Sleep(2000);
            break;
        case 1: //은행 추가
            BANKADD();
            break;
        case 2: //계좌 정지 해제
            ACCOUNT_UNLOCK();
            break;
        case 3: //ATM잔고 확인
            ATM_CHECK();
            break;
        case 4: //ATM잔고 보충
            ATM_ADD();
            break;
        case 5: //관리자 비밀번호 변경
            SYSTEM_PASSWORD_CHANGE();
            break;
        default: //잘못된 수를 입력했을 때
            printf("0~5 사이의 수를 입력해주세요.\n");
            Sleep(1000);
            break;
        }
    } while (choice != 0);
}// 관리자 메뉴 함수

void BANKADD(void) {
    system("cls");

    FILE* bank;
    char bank_add[256];

    if ((bank = fopen("은행.txt", "a")) == NULL) {
        printf("파일 열기 실패");
        exit(1);
    }

    printf("추가할 은행을 입력해주세요 : ");
    scanf("%s", bank_add);

    fprintf(bank, "%s\n", bank_add);
    printf("%s이(가) 추가되었습니다.\n\n", bank_add);
    fclose(bank);
    Sleep(2000);
}// 은행 추가 함수

void ACCOUNT_UNLOCK(void) {
    system("cls");

    FILE* bank, * newfile;
    char buffer[256];
    char account[256];
    int count1 = 0, count2 = 0;

    if ((bank = fopen("은행.txt", "r")) == NULL) {
        printf("파일 열기 실패");
        exit(1);
    }

    if ((newfile = fopen("은행2.txt", "w")) == NULL) {
        printf("파일 열기 실패");
        exit(1);
    }

    printf("정지를 해제할 계좌번호를 입력하세요 : ");
    scanf("%s", account);

    while ((fgets(buffer, 256, bank)) != NULL) {
        if (strstr(buffer, account)) {
            if (strstr(buffer, "x")) {
                fprintf(newfile, "%s\n", account);
                printf("%s 계좌가 해제되었습니다.\n", account);
            }
            else {
                printf("해당 계좌는 정지 상태가 아닙니다.\n");
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
        printf("%s 계좌는 없는 계좌입니다.\n", account);
    }

    fclose(bank);
    fclose(newfile);

    remove("은행.txt");
    if (rename("은행2.txt", "은행.txt") != 0) {
        printf("이름 변경 실패\n");
    }
    Sleep(2000);
}// 계좌 정지 해제 함수

void ATM_CHECK(void) {
    system("cls");

    FILE* atm;
    char buffer[256];
    struct BANKINFO B;

    if ((atm = fopen("atm잔고.txt", "r")) == NULL) {
        printf("파일 열기 실패");
        exit(1);
    }
    fgets(buffer, 256, atm);
    fscanf(atm, "%s %s %d %s", B.bankname, B.username, &B.balance, B.password);
    printf("ATM의 현재 잔고는 %d원 입니다.\n", B.balance);

    fclose(atm);
    Sleep(2000);
}// ATM 잔고 확인 함수

void ATM_ADD(void) {
    system("cls");

    FILE* atm, * newfile;
    char buffer[256];
    int money;
    struct BANKINFO B;

    if ((atm = fopen("atm잔고.txt", "r")) == NULL) {
        printf("파일 열기 실패");
        exit(1);
    }

    if ((newfile = fopen("atm잔고2.txt", "w")) == NULL) {
        printf("파일 열기 실패");
        exit(1);
    }

    fgets(buffer, 256, atm);

    fscanf(atm, "%s %s %d %s", B.bankname, B.username, &B.balance, B.password);
    printf("추가할 금액을 입력하세요 : ");
    scanf("%d", &money);
    B.balance += money;

    printf("ATM의 현재 잔고는 %d원 입니다.\n", B.balance);

    fputs(buffer, newfile);
    fprintf(newfile, "    %s   %s   %d       %s\n", B.bankname, B.username, B.balance, B.password);

    fclose(atm);
    fclose(newfile);

    remove("atm잔고.txt");
    if (rename("atm잔고2.txt", "atm잔고.txt") != 0) {
        printf("이름 변경 실패\n");
    }
    Sleep(2000);
}//ATM 잔고 추가 함수

void SYSTEM_PASSWORD_CHANGE() {
    system("cls");

    struct PASSWORD P;
    struct BANKINFO B;
    FILE* atm, * newfile;
    char buffer[256];
    int END = 0;

    if ((atm = fopen("atm잔고.txt", "r")) == NULL) {
        printf("파일 열기 실패");
        exit(1);
    }

    if ((newfile = fopen("atm잔고2.txt", "w")) == NULL) {
        printf("파일 열기 실패");
        exit(1);
    }

    fgets(buffer, 256, atm);
    fscanf(atm, "%s %s %d %s", B.bankname, B.username, &B.balance, B.password);

    do {
        printf("현재 비밀번호를 입력해주세요 : ");
        scanf("%s", P.check);

        //현재 비밀번호 일치
        if (strcmp(B.password, P.check) == 0) {
            while (END != 1) {
                printf("\n새 비밀번호를 입력해주세요 (4자리 숫자) : ");
                scanf("%s", P.new1);
                printf("새 비밀번호를 다시 입력해주세요 (4자리 숫자) : ");
                scanf("%s", P.new2);

                //새 비밀번호의 자리수가 4자리가 아닐 때
                if (strlen(P.new1) != 4) {
                    printf("\n비밀번호 형식이 맞지 않습니다. 다시 입력해주세요.\n");
                }
                else {
                    //새 비밀번호 일치
                    if (strcmp(P.new1, P.new2) == 0) {
                        fputs(buffer, newfile);
                        fprintf(newfile, "    %s   %s   %d       %s\n", B.bankname, B.username, B.balance, P.new1);
                        printf("\n비밀번호가 변경되었습니다.\n");
                        END = 1;
                    }

                    //새 비밀번호 불일치
                    else {
                        printf("\n비밀번호가 일치하지 않습니다. 다시 입력해주세요.\n");
                    }
                }
            }
        }
        //현재 비밀번호 불일치
        else {
            printf("\n비밀번호가 일치하지 않습니다. 다시 입력해주세요.\n\n");
        }
    } while (END != 1);

    fclose(atm);
    fclose(newfile);

    remove("atm잔고.txt");
    if (rename("atm잔고2.txt", "atm잔고.txt") != 0) {
        printf("이름 변경 실패\n");
    }
    Sleep(2000);
} //관리자 비밀번호 변경 함수
