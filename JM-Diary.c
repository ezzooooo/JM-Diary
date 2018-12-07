#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void calendar();

int main(int argc, char *argv[]) {
	int opt_a = 0;
	int opt_c = 0;
	int opt_d = 0;
	int opt_e = 0;
	int opt_f = 0;
	int option = 0;
	int fd;
	struct tm *tm;
	time_t t;
	char buf[257]= {0};
	int len;
	char file_name[50] = {0};

	t = time(NULL);
	tm = localtime(&t);

	mode_t mode;
	mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;

	if(argc<2) {
		printf("인자 입력\n");
		return 0;
	}
	else {
		while( (option = getopt(argc, argv, "ca:edf") ) != -1) {
			switch(option) {
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

	if(opt_a) { // 메모 입력 메뉴
		switch(argc)
		{
			case 3: // 인자가 3개일때 (JM-Diary -a '내용')
				t = time(NULL);
				tm = localtime(&t);
				sprintf(file_name,"%04d-%02d.txt", tm->tm_year+1900, tm->tm_mon+1);
				fd = open(file_name, O_CREAT | O_APPEND | O_WRONLY , mode);
				if (fd == -1) {
					perror("오픈 에러");
					exit(1);
				}
				sprintf(buf,"%04d-%02d-%02d %02d:%02d %s\n", 
						tm->tm_year+1900, tm->tm_mon+1, tm->tm_mday, 
						tm->tm_hour, tm->tm_min, argv[2]);
				if (write(fd, buf, strlen(buf)) != strlen(buf))
					perror("쓰기 오류");
				close(fd);
				break;
			case 4: // 인자가 4개일 때 (JM-Diary -a 2018-05-12 '내용')
				sprintf(file_name,"%c%c%c%c-%c%c.txt", 
						argv[2][0],argv[2][1], argv[2][2], argv[2][3], argv[2][5], argv[2][6]);
				fd = open(file_name, O_CREAT | O_APPEND | O_WRONLY , mode);
				if (fd == -1) {
					perror("오픈 에러");
					exit(1);
				}
				sprintf(buf,"%s 09:00 %s\n", argv[2], argv[3]);
				if (write(fd, buf, strlen(buf)) != strlen(buf))
					perror("쓰기 오류");
				close(fd);
				break;
			case 5: // 인자가 5개일 때 (JM-Diary -a 2018-07-11 12:11 '내용')
				sprintf(file_name,"%c%c%c%c-%c%c.txt", 
						argv[2][0],argv[2][1], argv[2][2], argv[2][3], argv[2][5], argv[2][6]);
				fd = open(file_name, O_CREAT | O_APPEND | O_WRONLY , mode);
				if (fd == -1) {
					perror("오픈 에러");
					exit(1);
				}
				sprintf(buf,"%s %s %s", argv[2], argv[3], argv[4]);
				if (write(fd, buf, strlen(buf)) != strlen(buf))
					perror("쓰기 오류");
				close(fd);
				break;
		}
	} else if(opt_e) {
		//수정메뉴
	} else if(opt_d) {
		//삭제메뉴
	} else if(opt_f) {
		if(argc!=3) {
			printf("jmd -f 0000-00-00\n");
		} else {
			sprintf(file_name,"%c%c%c%c-%c%c.txt", 
					argv[2][0],argv[2][1], argv[2][2], argv[2][3], argv[2][5], argv[2][6]);
			fd = open(file_name, O_RDONLY , mode);
			if (fd == -1) {
				perror("오픈 에러");
				exit(1);
			}
			int length = 0;
			int line_num=1;
			char temp[100] = {0};
			while (read(fd, temp, 1) > 0 ) {
				if(temp[0] != '\n') {
					buf[length]=temp[0];
					length++;
				} else {
					length=0;
					if(strncmp(argv[2], buf, 10) == 0) {
						printf("%d. ", line_num);
						line_num++;
						puts(buf);
					}
				}
			}
			close(fd);
		}
	} else if(opt_c) {
		calendar(); // 달력출력
	}	
	return 0;
}

void calendar(){
	struct tm *tm;
	time_t t;
	time(&t);
	tm = localtime(&t);
	//각 월별 날짜 수 저장
	int month[12]={31,0,31,30,31,30,31,31,30,31,30,31};
	int i,j,d,k;
	int totalday=0;
	int h=1;

	int year=tm->tm_year+1900;
	int _month=tm->tm_mon+1;

	printf("%10d 년 %3d 월 \n", year, _month);
	printf("------------------------------\n");
	printf("  일  월  화  수  목  금  토  \n");
	printf("------------------------------\n");
	//윤년 체크
	if(year%4==0&&year%100!=0||year%400==0){
		month[1]=29;
	}
	else month[1]=28;

	//시작일
	totalday = (year-1)*365+(year-1)/4-(year-1)/100+(year-1)/400;
	for(k=1;k<=_month-1;k++){
		totalday=totalday+month[k-1];
	}
	//출력
	for(i=1; i<=6; i++){
		for(j=1;j<=7;j++,h++){
			if(h<=month[_month-1]+1+totalday%7){
				d=h-totalday%7;
				if(d-1<=0)
					printf("    ");
				else
					printf("%4d", d-1);
			}
		}
		printf("\n");
	}
	printf("\n");
}

