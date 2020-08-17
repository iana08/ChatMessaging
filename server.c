#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
awsomeham=191.281.221.23
secretbeta=19.929.211.233
*/

/*
This reads the file named dataBase.txt and saves the data to an dictionary
Should only store the person's username and their ip address.
my_dict[username] = "IP_address"
*/
struct userData {
	char * username;
	char * IP_address;
	struct userData * next;
};

/*
Head should be null so we can assume that this is the first time
we call this function
This reads the file dataBase.txt for the first time and saves it to a
linked list only problem is that it creates an empty head at the end. 
*/
int read_file(struct userData *head) {

	FILE * fp;
	char * filename = "dataBase.txt";
	fp = fopen(filename, "r");

	if (fp == NULL) {
		printf("Could not open file\n");
		return -1;
	}
	int b_size = 16;
	char buff[b_size];
	memset(buff, 0, b_size);
	char c;
	int idx = 0;
	if (head == NULL) {
		head = (struct userData *) malloc(sizeof(struct userData));
	}
	while ((c = fgetc(fp)) != EOF) {
		if (c == '=') {
			buff[idx] = '\0';
			head -> username = (char *) malloc(sizeof(char) * strlen(buff));
			memcpy(head -> username, buff, strlen(buff));
			memset(buff, 0, b_size);
			idx = 0;
			continue;
		}
		if (c ==  '\n') {
			buff[idx] = '\0';
			head -> IP_address = (char *) malloc(sizeof(char) * strlen(buff));
			memcpy(head->IP_address, buff, strlen(buff));
			memset(buff, 0, b_size);
			idx = 0;
			head -> next = (struct userData *) malloc(sizeof(struct userData));
			head = head->next;
		}
		else {
			buff[idx] = c;
			idx++;
		}
	}
	fclose(fp);
	return 0;
}

/*
Writes to the file to save the userData before closing the server
Takes in the head of the userData
*/
int write_file(struct userData * head) {

	FILE *fp;
	char* filename = "dataBase.txt";
	fp = fopen(filename, "w");

	if (fp == NULL) {
		printf("Could not open file\n");
		return -1;
	}

	while (head->next != NULL) {
		while (*head -> username) {
			fputc(*head->username++, fp);
		}
		fputc('=', fp);
		while(*head -> IP_address) {
			fputc(*head->IP_address++, fp);
		}
		head = head -> next;
		fputc('\n', fp);
	}

	fclose(fp);
	return 0;
}

void print_database(struct userData * head) {
	while (head->next != NULL) {
		printf("Outside:%s\n", head -> username);
		printf("Outside:%s\n", head -> IP_address);
		head = head->next;
	}
}

/*
Searches the database for the username returns 0 if found.
-1 if not 
*/
int search_userData(struct userData * head, char * username) {
	while (head -> next != NULL) {
		if (strcmp(head -> username, username) == 0) {
			// Same user name:
			return 0;
		}
		head = head->next;
	}
	return -1;
}

/*
Searches the dataBase returns the IP-Address to the  username
*/
char * get_IP(struct userData * head, char * username) {
	while(head -> next != NULL) {
		if (strcmp(head->username, username) == 0) {
			return head->IP_address;
		}
		head = head -> next;
	}
	return "";
}



/*
Inserts a User into the database if there is not the same User to begin with.
*/
int insert_user(struct userData * head, struct userData user) {
	// Go to the end and see if the user is  in the data base, if not 
	// then add it to the end.
	if (search_userData(head, user.username) == 0) {
		// This means the user name exists
		return -1;
	}

	while (head -> next != NULL) {
		head = head -> next;
	}

	printf("User: %s Adding. . .\n", user.username);

	head -> username = (char *) malloc(sizeof(char) * strlen(user.username));
	memcpy(head->username, user.username, strlen(user.username));

	head -> IP_address = (char *) malloc(sizeof(char) * strlen(user.IP_address));
	memcpy(head->IP_address, user.IP_address, strlen(user.IP_address));

	head -> next = (struct userData *) malloc(sizeof(struct userData));
	return 0;

}

int main(int argv, char * argc[]) {

	struct userData head;
	struct userData * head_ptr;
	head_ptr = &head;

	if (read_file(head_ptr) == -1) {
		printf("read_file(): not working dataBase.txt\n");
		return -1;
	}
/*
	struct userData user;
	user.username = "Cl4pTr4p";
	user.IP_address = "21.342.3.23";

	if (insert_user(head_ptr, user) == -1) {
		printf("User was already in the database\n");
	}
	
	char * ret;
	ret = get_IP(head_ptr, user.username);

	if (strlen(ret) == 0) {
		printf("User does not exists\n");
	}
	else {
		printf("User IP_address :%s\n",ret);
	}

	if (write_file(head_ptr) == -1) {
		printf("write_file(): not working dataBase.txt\n");
	}
*/
	return 0;
}