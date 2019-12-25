#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
	char name[20];
	int score;
	struct node* next;
}node_t;

node_t* tmp_node;
node_t* new_node;
node_t* list_head = NULL;
node_t* next_p;
node_t* prev_p;

char name[20];

int how_many()
{
	int students;
	
	printf("고객의 수 : ");
	scanf("%d",&students);

	return students;
}

int make_list(int students)
{
	int *list;
	
	list=(int *)malloc(students * sizeof(int));
	if (list==NULL){
		printf("동적 메모리 할당 오류\n");
		exit(1);
	}
	return list;
}

void print_list(struct node* list_head)
{
	while(list_head !=NULL){
		printf("%d => ",list_head->score);
		list_head=list_head ->next;
	}
	printf("\n");
}

void make_nod(int students,int *list)
{
	for(int i=0 ; i<students ; i++){
		printf("고객 #%d의  예금액(-1 : 파산)  : ",i+1);
		scanf("%d",&list[i]);
		//1. 노드 생성
		new_node=(node_t*)malloc(sizeof(node_t));
		new_node ->score = list[i];

		//2. 노드 삽입 위치 검색
		next_p=list_head; //리스트 헤드부터 검색
		prev_p=NULL; //prev_p는 NULL로 초기화	
		while(next_p){
			if(next_p -> score < new_node -> score){
				break;
			}
			prev_p=next_p;
			next_p=next_p->next;
		}
		//3.노드 삽입
		new_node->next = next_p;
		if(prev_p){
			prev_p->next = new_node;
		}
		else{
			list_head = new_node;
		}	
		print_list(list_head);
	}
}

void print_allList(int students, int *list)
{
	printf("==========================\n");
	for(int i=0; i<students; i++){
		if(list[i]<0){
			printf("고객 #%d은 파산하셨습니다.\n",i+1);
		}
		else{
			printf("고객 #%d의 예금액  : %d\n",i+1,list[i]);
		}
	}
	printf("==========================\n");
}

node_t* search_node(char* name, node_t* list_head)
{
	node_t* tmp = list_head;
	while(tmp){
		if(!strcmp(tmp->name, name)){
			return tmp;
		}
		tmp = tmp->next;
	}
	return tmp;
}

void read_file()
{
	FILE *fp=NULL;
	
	fp=fopen("bank.dat","r+");
	
	if(fp==NULL){
		printf("Cannot open file!\n");
		return ;
	}
	
	while(!feof(fp)){
		new_node=(node_t*)malloc(sizeof(node_t));
		fscanf(fp,"%s %d\n",new_node->name,&new_node->score);
		printf("고객  추가 : %s %d\n",new_node->name,new_node->score);
		new_node->next=list_head;
		list_head = new_node;
	}
}

void find_file()
{
	int input=1;
	FILE *fp=NULL;	
	fp=fopen("bank.dat","r+");
	
	if(fp==NULL){
		printf("Cannot open file!\n");
		return ;
	}
	while(1){
		printf("--------------------\n");
		printf("고객조회(이름) : ");
		scanf("%s",&name);
		tmp_node=search_node(name,list_head);
		if(tmp_node){
			printf("%s : %d\n",tmp_node->name,tmp_node->score);
		}
		else{
			printf("찾는 고객이 없습니다.\n");
		}
		printf("종료는 0, 계속은 1을  누르세요 ->");
		scanf("%d",&input);
		if(input==0){
			break;
		}
	}
	while(list_head){
		tmp_node = list_head;
		list_head=list_head->next;
		free(tmp_node);
	}
	fclose(fp);	
}

void adduser()
{
	int money=0;
	
	FILE *fp = fopen("bank.dat","a+");
	while(1){
		printf("고객 이름, 예금액을 입력하세요 : (음수이면 종료) : ");
		scanf("%d",&money);
		if(money<0){
			break;
		}
		scanf("%s %d",name,&money);
		fprintf(fp,"%s %d",name,money);
	}
	fclose(fp);
	return ;	
}
void rank()
{
	double percent;
	int year;

	printf("1등 고객의 예금액 : %d\n",list_head->score);
	printf("년 이자율? : ");
	scanf("%lf",&percent);
	printf("몇년 뒤 예금액 ? : ");
	scanf("%d",&year);
	printf("%d년 예금액 : %lf원\n",2019+year,(list_head->score)*(1+percent)*year);
}
	
int main()
{
	int *list=NULL;
	int students ;	
	int number=1;
	
	while(number!=0){
		printf("@@@@@@@@@@@@@@@@은행관리 프로그램@@@@@@@@@@@@@@@@@@@\n");
		printf("1 : 고객 수 입력, 2 : 고객 정보 입력, 3 : 고객 정보 확인, 4 : 1등 예금액 고객 확인,  5 : 정보 조회, 6 : 고객 추가,  0 : 종료 -> ");
		scanf("%d",&number);
		switch(number){
			case 1:
				students = how_many();
				break;
			case 2:
				list = make_list(students);
				make_nod(students,list);
				break;
			case 3:
				print_allList(students, list);
				break;
			case 4:
				rank();
				free(list);
				break;
			case 5:
				read_file();
				find_file();
				break;
			case 6:
				adduser();
				break;
			case 0:
				exit(1);
		}
	}
	return 0;
}
