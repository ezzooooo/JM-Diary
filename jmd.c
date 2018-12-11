#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void calendar();

char init_arr[257] = { 0 };

int main(int argc, char *argv[]) {
    int opt_a = 0;
    int opt_c = 0;
    int opt_d = 0;
    int opt_e = 0;
    int opt_f = 0;
    int option = 0;
    int fd, temp_fd;
    struct tm *tm;
    time_t t;
    char buf[257] = { 0 };
    char file_name[50] = { 0 };

    t = time(NULL);
    tm = localtime(&t);

    mode_t mode;
    mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;

    if (argc < 2) {
        printf("        인자를  입력하세요         \n");
        printf("-------------------------------------------\n");
        printf("  -c : 달력 보기\n\n");
        printf("  -a : 일정 추가\n");
        printf("       입력 형식\n");
        printf("       1. '일자없이 작은따옴표 안 내용'\n");
        printf("       2. 년-월-일 '내용'\n");
        printf("       3. 년-월-일 시:분 '내용'\n\n");
        printf("  -e : 일정 수정\n");
        printf("       년-월-일 형태로 일자 선택 후\n");
        printf("       수정할 항목 선택\n");
        printf("       c. 내용 수정\n");
        printf("       t. 시간 수정\n\n");
        printf("  -d : 일정 삭제\n");
        printf("       년-월-일 형태로 일자 선택 후\n");
        printf("       삭제할 항목 선택 후\n");
        printf("       y. 삭제\n");
        printf("       n. 취소\n\n");
        printf("  -f : 일정 검색\n");
        printf("       년-월-일 입력 후 특정일자 검색\n");
        printf("--help: 옵션 설명\n");
        printf("-------------------------------------------\n");
        return 0;
    }
    else {
        if (strcmp(argv[1], "--help") == 0) {
            printf("        인자를  입력하세요         \n");
            printf("-------------------------------------------\n");
            printf("  -c : 달력 보기\n\n");
            printf("  -a : 일정 추가\n");
            printf("       입력 형식\n");
            printf("       1. '일자없이 작은따옴표 안 내용'\n");
            printf("       2. 년-월-일 '내용'\n");
            printf("       3. 년-월-일 시:분 '내용'\n\n");
            printf("  -e : 일정 수정\n");
            printf("       년-월-일 형태로 일자 선택 후\n");
            printf("       수정할 항목 선택\n");
            printf("       c. 내용 수정\n");
            printf("       t. 시간 수정\n\n");
            printf("  -d : 일정 삭제\n");
            printf("       년-월-일 형태로 일자 선택 후\n");
            printf("       삭제할 항목 선택 후\n");
            printf("       y. 삭제\n");
            printf("       n. 취소\n\n");
            printf("  -f : 일정 검색\n");
            printf("       년-월-일 입력 후 특정일자 검색\n");
            printf("--help: 옵션 설명\n");
            printf("-------------------------------------------\n");
            return 0;
        }
        while ((option = getopt(argc, argv, "ca:e:d:f:")) != -1) {
            switch (option) {
                case 'c':
                    opt_c++;
                    break;
                case 'a':
                    opt_a++;
                    break;
                case 'e':
                    opt_e++;
                    break;
                case 'd':
                    opt_d++;
                    break;
                case 'f':
                    opt_f++;
                    break;
                default:
                    break;
            }
        }
    }

    // 메모 입력 옵션
    if (opt_a) {
        switch (argc)
        {
            case 3: // 인자가 3개일때 (JM-Diary -a '내용')
                t = time(NULL);
                tm = localtime(&t);
                sprintf(file_name, "%04d-%02d.txt", tm->tm_year + 1900, tm->tm_mon + 1);
                fd = open(file_name, O_CREAT | O_APPEND | O_WRONLY, mode);
                if (fd == -1) {
                    perror("오픈 에러");
                    exit(1);
                }
                sprintf(buf, "%04d-%02d-%02d %02d:%02d %s\n",
                        tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday,
                        tm->tm_hour, tm->tm_min, argv[2]);
                if (write(fd, buf, strlen(buf)) != strlen(buf))
                    perror("쓰기 오류");
                close(fd);
                break;
            case 4: // 인자가 4개일 때 (JM-Diary -a 2018-05-12 '내용')
                sprintf(file_name, "%c%c%c%c-%c%c.txt",
                        argv[2][0], argv[2][1], argv[2][2], argv[2][3], argv[2][5], argv[2][6]);
                fd = open(file_name, O_CREAT | O_APPEND | O_WRONLY, mode);
                if (fd == -1) {
                    perror("오픈 에러");
                    exit(1);
                }
                sprintf(buf, "%s 09:00 %s\n", argv[2], argv[3]);
                if (write(fd, buf, strlen(buf)) != strlen(buf))
                    perror("쓰기 오류");
                close(fd);
                break;
            case 5: // 인자가 5개일 때 (JM-Diary -a 2018-07-11 12:11 '내용')
                sprintf(file_name, "%c%c%c%c-%c%c.txt",
                        argv[2][0], argv[2][1], argv[2][2], argv[2][3], argv[2][5], argv[2][6]);
                fd = open(file_name, O_CREAT | O_APPEND | O_WRONLY, mode);
                if (fd == -1) {
                    perror("오픈 에러");
                    exit(1);
                }
                sprintf(buf, "%s %s %s\n", argv[2], argv[3], argv[4]);
                if (write(fd, buf, strlen(buf)) != strlen(buf))
                    perror("쓰기 오류");
                close(fd);
                break;
        }
    }

    //메모 수정 옵션
    else if (opt_e) {
        if (argc != 3) {
            printf("형식에 맞게 입력해주세요\n");
            printf("jmd -e 0000-00-00\n");
        }
        else {
            //수정을 원하는 일자를 입력받아 해당 메모가 들어있는 파일을 오픈
            sprintf(file_name, "%c%c%c%c-%c%c.txt", argv[2][0], argv[2][1], argv[2][2], argv[2][3], argv[2][5], argv[2][6]);    //입력된 일자의 년 월을 참조해 파일명 확보

            fd = open(file_name, O_RDWR, mode);     //해당일자 파일 오픈

            if (fd == -1) {
                perror("오픈 에러");
                exit(1);
            }

            temp_fd = open("temp.txt", O_RDWR | O_CREAT, mode);     //수정된 사항을 적용시킬 임시 파일
            if (fd == -1) {
                perror("오픈 에러");
                exit(1);
            }

            int length = 0;
            int line_num = 0;
            int file_line_num = 0;
            int file_line_nums[100] = { 0 };
            int sel_line = 0;
            char edit_sel[5] = { 0 };
            char edit_content[100] = { 0 };
            char edit_time[100] = { 0 };
            char origin_cont[100] = { 0 };
            int edit_set = 0;
            char temp[100] = { 0 };

            //현재 해당 일자에 입력되어 있는 메모 내용 전체 출력
            while (read(fd, temp, 1) > 0) {
                if (temp[0] != '\n') {
                    buf[length] = temp[0];
                    length++;
                }
                else {
                    buf[length] = '\0';
                    length = 0;

                    file_line_num++;

                    if (strncmp(argv[2], buf, 10) == 0) {
                        file_line_nums[line_num] = file_line_num;
                        printf("%d. ", line_num + 1);
                        line_num++;
                        puts(buf);
                    }
                }
            }

            if (line_num == 0) {
                printf("수정할 항목이 없습니다.\n");
                exit(1);
            }
            else {
                printf("수정할 항목을 선택하세요\n->");

                fflush(stdout);

                scanf("%d", &sel_line);
                length = 0;

                printf("-------------------------------\n");
                printf("선택 하세요\n\n");
                printf("c. 내용 수정\n");
                printf("t. 시간 수정\n");
                printf("-------------------------------\n");
                printf("->");
                scanf("%s", &edit_sel);

                if (strcmp(edit_sel, "c") == 0) {
                    edit_set = 1;
                    printf("수정할 내용을 입력하세요\n->");
                    rewind(stdin);
                    gets(edit_content);
                }
                else if (strcmp(edit_sel, "t") == 0) {
                    edit_set = 2;
                    printf("수정할 시간을 입력하세요 (입력 형식 00:00)\n->");
                    scanf("%s", &edit_time);
                }
                else if (strcmp(edit_sel, "t") != 0 || strcmp(edit_sel, "c") != 0) {
                    printf("잘못 입력되었습니다.\n");
                    printf("다시 선택해주세요\n");
                    return 0;
                }
                if (sel_line >= 1 && sel_line < line_num + 1) {
                    line_num = 0;
                    lseek(fd, 0, SEEK_SET);
                    while (read(fd, temp, 1) > 0) {
                        if (temp[0] != '\n') {
                            buf[length] = temp[0];
                            length++;
                        }
                        else {
                            buf[length] = '\0';
                            length = 0;

                            line_num++;

                            //수정하려는 줄이 아닌 경우
                            if (line_num != file_line_nums[sel_line - 1]) {
                                write(temp_fd, buf, strlen(buf));
                                write(temp_fd, "\n", 1);
                            }
                            //수정하려는 줄일 경우
                            else if (line_num == file_line_nums[sel_line - 1]) {
                                //입력한 내용으로 임시파일에 입력
                                if (edit_set == 1) {
                                    write(temp_fd, buf, 17);
                                    write(temp_fd, edit_content, strlen(edit_content));
                                    write(temp_fd, "\n", 1);
                                }
                                else if (edit_set == 2) {
                                    strcpy(origin_cont, buf + 17);
                                    write(temp_fd, buf, 11);
                                    write(temp_fd, edit_time, strlen(edit_time));
                                    write(temp_fd, " ", 1);
                                    write(temp_fd, origin_cont, strlen(origin_cont));
                                    write(temp_fd, "\n", 1);
                                }
                            }
                        }
                    }

                    close(fd);
                    remove(file_name);

                    lseek(temp_fd, 0, SEEK_SET);

                    //본 파일에 수정된 내용을 덮어씌움
                    fd = open(file_name, O_CREAT | O_WRONLY, mode);
                    int n;
                    while ((n = read(temp_fd, buf, 6)) > 0) {
                        if (write(fd, buf, n) != n)
                            perror("Write");
                    }
                    close(fd);
                    close(temp_fd);
                    remove("temp.txt");
                }
                else {
                    printf("수정할 항목이 없습니다.\n");
                    exit(1);
                }
            }
            close(fd);
        }
    }
    //delete 메모 삭제 옵션
    else if (opt_d) {
        if (argc != 3) {
            printf("형식에 맞게 입력해주세요\n");
            printf("jmd -d 0000-00-00\n");
        }
        else {
            //삭제를 원하는 일자를 입력받아 해당 메모가 들어있는 파일을 오픈
            sprintf(file_name, "%c%c%c%c-%c%c.txt",
                    argv[2][0], argv[2][1], argv[2][2], argv[2][3], argv[2][5], argv[2][6]);    //입력된 일자를 이용해 파일명 확보

            fd = open(file_name, O_RDWR, mode);     //해당 일자 메모가 들어있는 파일 오픈
            if (fd == -1) {
                perror("오픈 에러");
                exit(1);
            }

            temp_fd = open("temp.txt", O_RDWR | O_CREAT, mode);     //삭제된 내용을 잠시 담을 임시파일 오픈
            if (fd == -1) {
                perror("오픈 에러");
                exit(1);
            }

            int length = 0;
            int line_num = 0;
            int file_line_num = 0;
            int file_line_nums[100] = { 0 };
            int sel_line = 0;
            char temp[100] = { 0 };
            while (read(fd, temp, 1) > 0) {
                if (temp[0] != '\n') {
                    buf[length] = temp[0];
                    length++;
                }
                else {
                    buf[length] = '\0';
                    length = 0;

                    file_line_num++;

                    if (strncmp(argv[2], buf, 10) == 0) {
                        file_line_nums[line_num] = file_line_num;
                        printf("%d. ", line_num + 1);
                        line_num++;
                        puts(buf);
                    }
                }
            }

            if (line_num == 0) {
                printf("삭제할 항목이 없습니다.\n");
                exit(1);
            }
            else {
                printf("삭제할 항목을 선택하세요\n->");

                fflush(stdout);

                scanf("%d", &sel_line);
                length = 0;

                if (sel_line >= 1 && sel_line < line_num + 1) {
                    line_num = 0;
                    lseek(fd, 0, SEEK_SET);
                    while (read(fd, temp, 1) > 0) {
                        if (temp[0] != '\n') {
                            buf[length] = temp[0];
                            length++;
                        }
                        else {
                            buf[length] = '\0';
                            length = 0;

                            line_num++;

                            //삭제를 원하는 내용을 제외한 나머지 내용을 임시파일에 담음
                            if (line_num != file_line_nums[sel_line - 1]) {
                                write(temp_fd, buf, strlen(buf));
                                write(temp_fd, "\n", 1);
                            }
                        }
                    }

                    close(fd);
                    remove(file_name);

                    lseek(temp_fd, 0, SEEK_SET);

                    //임시 파일에 저장된 내용을 본 파일에 덮어 씌움
                    fd = open(file_name, O_CREAT | O_WRONLY, mode);
                    int n;
                    while ((n = read(temp_fd, buf, 6)) > 0) {
                        if (write(fd, buf, n) != n)
                            perror("Write");
                    }
                    close(fd);
                    close(temp_fd);
                    remove("temp.txt");
                }
                else {
                    printf("삭제할 항목이 없습니다.\n");
                    exit(1);
                }
            }
            close(fd);
        }
    }
    //find 메모 검색 옵션
    else if (opt_f) {
        if (argc != 3) {
            printf("형식에 맞게 입력하세요\n");
            printf("jmd -f 0000-00-00\n");
        }
        else {
            //입력된 날짜 형식 기준 저장되어있는 파일 오픈
            sprintf(file_name, "%c%c%c%c-%c%c.txt",
                    argv[2][0], argv[2][1], argv[2][2], argv[2][3], argv[2][5], argv[2][6]);
            fd = open(file_name, O_RDONLY, mode);
            if (fd == -1) {
                perror("오픈 에러");
                exit(1);
            }
            int length = 0;
            int line_num = 1;
            char temp[100] = { 0 };
            while (read(fd, temp, 1) > 0) {
                if (temp[0] != '\n') {
                    buf[length] = temp[0];
                    length++;
                }
                else {
                    buf[length] = '\0';
                    length = 0;
                    if (strncmp(argv[2], buf, 10) == 0) {
                        printf("%d. ", line_num);
                        line_num++;
                        puts(buf);
                    }
                }
            }
            if (line_num == 1) {
                printf("조회할 항목이 없습니다.\n");
                exit(1);
            }
            close(fd);
        }
    }
    else if (opt_c) {
        calendar(); // 달력출력
    }
    return 0;
}

//달력 출력 함수
void calendar() {
    struct tm *tm;
    time_t t;
    time(&t);
    tm = localtime(&t);
    //각 월별 날짜 수 저장
    int month[12] = { 31,0,31,30,31,30,31,31,30,31,30,31 };
    int i, j, d, k;
    int totalday = 0;
    int h = 1;

    int year = tm->tm_year + 1900;
    int _month = tm->tm_mon + 1;

    printf("%10d 년 %3d 월 \n", year, _month);
    printf("------------------------------\n");
    printf("  일  월  화  수  목  금  토  \n");
    printf("------------------------------\n");
    //윤년 체크
    if (year % 4 == 0 && year % 100 != 0 || year % 400 == 0) {
        month[1] = 29;
    }
    else month[1] = 28;

    //시작일
    totalday = (year - 1) * 365 + (year - 1) / 4 - (year - 1) / 100 + (year - 1) / 400;
    for (k = 1; k <= _month - 1; k++) {
        totalday = totalday + month[k - 1];
    }
    //출력
    for (i = 1; i <= 6; i++) {
        for (j = 1; j <= 7; j++, h++) {
            if (h <= month[_month - 1] + 1 + totalday % 7) {
                d = h - totalday % 7;
                if (d - 1 <= 0)
                    printf("    ");
                else
                    printf("%4d", d - 1);
            }
        }
        printf("\n");
    }
    printf("\n");
}

                                                                                                                                                                                            