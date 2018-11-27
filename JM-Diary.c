#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

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
		while( (option = getopt(argc, argv, "caedf") ) != -1) {
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

	if(opt_a) {
		t = time(NULL);
		tm = localtime(&t);
		printf("%s\n", buf);
		sprintf(file_name,"%d-%d.txt", tm->tm_year+1900, tm->tm_mon+1);
		fd = open(file_name, O_CREAT | O_APPEND | O_WRONLY , mode);
		if (fd == -1) {
			perror("오픈 에러");
			exit(1);
		}
		sprintf(buf,"%d-%d-%d %d:%d %s\n", tm->tm_year+1900, tm->tm_mon+1, tm->tm_mday, tm->tm_hour, tm->tm_min, argv[2]);
		if (write(fd, buf, strlen(buf)+1) != strlen(buf)+1)
			perror("쓰기 오류");

		close(fd);
	}
	return 0;
}
