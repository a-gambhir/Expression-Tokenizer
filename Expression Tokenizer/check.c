

#include<stdio.h>
#include<stdlib.h>

struct Node{
int type;
char *data;
struct Node *next;
};


int numExpressions = 1;
int numLogical = 0;
int numArithmetic = 0;

char* tokenizer(char* string, const char* delim);
void insertNode(struct Node *head, struct Node *variables);
void printLinkedList(struct Node *head);
void identify(struct Node *head);
void output(struct Node *head);
void countExpr(struct Node *head);
void freeLL(struct Node *head);

int main(int argc, char** argv){

if(argc < 2){
	printf("Number of arguments is incorrect.");
}
else if(argc > 2){
	printf("Number of arguments is incorrect.");
}else if(argc == 2){

	char temp[2]= "";//cannot initialize an empty ll
	struct Node *ptr = malloc(sizeof(struct Node));
	char *pstr;
	char *token;
	ptr->data = temp;

	int i = 0;
  for (i = 0, pstr = argv[1]; ; i++, pstr = NULL)
    {


			struct Node *node = malloc(sizeof(struct Node));
        token = tokenizer(pstr, " " );

        if (token == NULL)
            break;


        node->data = token;
				node->next = NULL;



	insertNode(ptr, node);

    }


struct Node *tempptr = ptr;
while(tempptr != NULL){
	char *tokendata = tempptr->data;

i = 0;
while(tokendata[i] !='\0'){
	if(tokendata[i] == ';'){
		tokendata[i] = '\0';
		numExpressions++;

		struct Node *temp = malloc(sizeof(struct Node));


		temp->data = ";";

		temp->next = tempptr->next;

		tempptr->next=temp;

		//printLinkedList(ptr);
		if(tempptr->next != NULL){
			tempptr=tempptr->next;
		}
free(temp);
	}

	i++;

}
tempptr=tempptr->next;
}


//delete the extra empty node at the front of the LL
if(ptr != NULL){
	struct Node *temp = ptr->next;
	temp->next=ptr->next->next;
	ptr=temp;

}


identify(ptr);



countExpr(ptr);

printf("Found %d ", numExpressions);
			printf("expressions: %d ", numLogical);
			printf("logical and %d ", numArithmetic);
			printf("arithmetic. \n");
			//printf("OK. \n");


output(ptr);

freeLL(ptr);


}
return 0;
}

char *tokenizer(char* string,const char *delim)
{
    int j;
    static char *ptr;
    const char *del;
    char *p;
    if(string != NULL)
    {
        ptr=string;
        p=string;
    }
    else
    {
        if(*ptr == '\0')
            return NULL;

        p=ptr;
    }

    while(*ptr != '\0')
    {
        del=delim;
        while(*del != '\0')
        {
            if(*ptr == *del)
            {
                if(ptr == p)
                {
                    p++;
                    ptr++;
                }
                else
                {
                    *ptr='\0';
                    ptr++;

                    return p;
                }
            }
            else
            {
                del++;
            }
        }
        ptr++;
    }
    return p;
}

void insertNode(struct Node *head, struct Node *variables){
	struct Node *ptr = malloc(sizeof(struct Node*));
	for(ptr = head; ptr->next != NULL; ptr = ptr->next){
	;
	}
	ptr->next = variables;
	return;
}



void printLinkedList(struct Node *head){
	struct Node *currentNode = head;
   	while ( currentNode != NULL) {
        printf("%s\n", currentNode->data);
        currentNode = currentNode->next;
    }
}

void identify(struct Node *head){
	struct Node *currentNode = head;
	int i = 0;

	while(currentNode != NULL){

		char *nodedata = currentNode->data;

		if(nodedata[0] == '+' || nodedata[0] == '-' || nodedata[0] == '*' || nodedata[0] == '/'){
			currentNode->type = 1;//1=arith operator
		}
		else if(nodedata[0] == '0' || nodedata[0] == '1' || nodedata[0] == '2' || nodedata[0] == '3'
  || nodedata[0] == '4' || nodedata[0] == '5' || nodedata[0] == '6' || nodedata[0] == '7' ||
	nodedata[0] == '8' || nodedata[0] == '9'){

			currentNode->type = 2;//2=arith operand
		}

		else if(nodedata[0] == 'A' && nodedata[1] == 'N' && nodedata[2] == 'D' && nodedata[3] == '\0'){

			currentNode->type = 3;//3=logical operator
		}
		else if(nodedata[0] == 'O' && nodedata[1] == 'R' && nodedata[2] == '\0'){

			currentNode->type = 3;//3=logical operator
		}
		else if(nodedata[0] == 'N' && nodedata[1] == 'O' && nodedata[2] == 'T' && nodedata[3] == '\0'){

			currentNode->type = 5;//5=NOT(logical operator)
		}
		else if(nodedata[0] == 't' && nodedata[1] == 'r' && nodedata[2] == 'u'
		&& nodedata[3] == 'e' && nodedata[4] == '\0'){

			currentNode->type = 4;//4=logical operand

		}
		else if(nodedata[0] == 'f' && nodedata[1] == 'a' && nodedata[2] == 'l'
		&& nodedata[3] == 's' && nodedata[4] == 'e' && nodedata[5] == '\0'){

			currentNode->type = 4;//4=logical operand
		}
		else{
			i = 0;
			while(nodedata[i] != '\0'){
				if(nodedata[i] == ';'){
					currentNode->type = 6;//6=semicolon
				}
				i++;
			}
		}

		currentNode = currentNode->next;
	}

}

void countExpr(struct Node *head){//counts num operators per expression
	struct Node *currentNode = head;
	int i = 0;
	int currentExpression = 0;

		//for loop to iterate through numexpressions
//find 1st op, break, make another loop that loops till another semicolon, then if pointer is semicolon and ptr next isnt null, ptr=ptr next

for(currentExpression = 0; currentExpression < numExpressions; currentExpression++){

	while(currentNode->next != NULL){
		if(currentNode->type==1){
			numArithmetic++;
			break;
		}
		else if(currentNode->type==3 || currentNode->type==5){
			numLogical++;
			break;
		}
		currentNode = currentNode->next;
	}
i=0;
while(currentNode->data!=";" && currentNode->next!=NULL){

currentNode = currentNode->next;

}

if(currentNode->data==";" && currentNode->next!=NULL){

	currentNode = currentNode->next;
}


}

}

void output(struct Node *head){//create node w semicolon in it so prev wont start at null,insert this node in front

struct Node *temp = malloc(sizeof(struct Node*));
temp->data=";";
temp->type=6;
temp->next=head;



	struct Node *currentNode = head;
	struct Node *prevNode = temp;



	int expressionIndex = 0;
	int tokenNum = 0;
	int numOperands = 0; //number of operands per expression
	int numOperators = 0; //number of operators per expression
	int currentID = 0; //special case for NOT:operator comes first
	int prevID = 0;
	int i = 0;
	int isError = 0;
	int isUnknownID = 0;
	char *currentToken;
	char *prevToken;



	/*0=unknown operator/operand
		1=arithmetic operator
		2=arithmetic operand
		3=logical operator
		5=NOT logical operator
		4=logical operand
		6=semicolon
	*/



	while(currentNode != NULL){
		currentID = currentNode->type;
		currentToken = currentNode->data;

			prevToken = prevNode->data;
			prevID = prevNode->type;


		i = 0;
		isUnknownID=0;
		//Unknown identifier
		 if(currentID==0 && tokenNum==0){
					printf("Error: %s ", "Parse error");
					printf("in expression %d", expressionIndex);
					printf(": %s ", "unknown identifier");
					printf("\n\"%s\" \n", currentToken);
					isError=1;
					tokenNum = 0;//Reset parse: next token becomes first of expression
					isUnknownID=1;
		}

//currentid and previd combinations for more errors

if(currentID==1||currentID==3||currentID==5){
	numOperators++;
}
else if(currentID==2||currentID==4){
	numOperands++;
}

		//unkown operator: expecting operator after operand
		if(currentID==0 && (prevID==2 || prevID==4)){
			printf("Error: %s ", "Parse error");
			printf("in expression %d", expressionIndex);
			printf(": %s ", "unknown operator");
			printf("\n\"%s\" \n", currentToken);
			isError=1;
		}
		//unexpected operator: operator right after semicolon
		else if((currentID==1 || currentID==3) && (prevID==6 || prevID==0) && tokenNum==0){
			printf("Error: %s ", "Parse error");
			printf("in expression %d", expressionIndex);
			printf(": %s ", "unexpected operator");
			printf("\n\"%s\" \n", currentToken);
			isError=1;
		}
		//unknown operand(after operator)
		else if((currentID==0 && prevID==1) || (currentID==0 && prevID==3)){
			printf("Error: %s ", "Parse error");
			printf("in expression %d", expressionIndex);
			printf(": %s ", "unknown operand");
			printf("\n\"%s\" \n", currentToken);
			isError=1;
		}
		//unexpected operand(extra operand after expression, two operands in row)
		else if(((currentID==2 && prevID==2) || (currentID==4 && prevID==4))){
			printf("Error: %s ", "Parse error");
			printf("in expression %d", expressionIndex);
			printf(": %s ", "unexpected operand");
			printf("\n\"%s\" \n", currentToken);
			isError=1;
		}
		//type mismatch
		else if(((currentID==4 && prevID==1) || (currentID==2 && prevID==3)) || ((currentID==1 && prevID==4) || (currentID==3 && prevID==2)) ){
			printf("Error: %s ", "Parse error");
			printf("in expression %d", expressionIndex);
			printf(": %s ", "type mismatch");
			printf("\n\"%s %s\" \n", prevToken, currentToken);
			isError=1;
		}
		//incomplete exprssion
		if(((currentID==6 && currentNode->next==NULL)||(prevID==6 && numOperands==0 && numOperators==0))&& currentID!=0 && prevID==0){
			printf("Error: %s ", "Parse error");
			printf("in expression %d", expressionIndex);
			printf(": %s ", "incomplete expression");
			printf("\n\"%s\" \n", currentToken);
			isError=1;
		}




		prevNode = currentNode;
		currentNode = currentNode->next;
;

if(currentToken!=";")
		tokenNum++;

if(isUnknownID==1){
	tokenNum=0;
}

		while(currentToken[i] != '\0'){ //if token has ; reset indexes
				if(currentToken[i] == ';'){
					expressionIndex++;
					tokenNum = 0;

				}
				i++;
			}

			}

		int j = 0;
		for(j = 0;j < numExpressions; j++){

			//missing operator
			if(numOperators==0 && numOperands!=0 && currentID!=0 &&prevID!=0 &&tokenNum==1){
				printf("Error: %s ", "Scan error");
				printf("in expression %d", expressionIndex);
				printf(": %s ", "missing operator\n");
				//printf("\n\"%s %s\" \n", currentToken);
				isError=1;
			}
			//missing operand
		else if(numOperators==1 && numOperands==1 && currentID!=0 &&prevID!=0 && currentID!=5 &&prevID!=5){
				printf("Error: %s ", "Scan error");
				printf("in expression %d", expressionIndex);
				printf(": %s ", "missing operand\n");
			//	printf("\n\"%s %s\" \n", currentToken);
				isError=1;
			}
			//expression wasnt ended
			else if(tokenNum > 3 && currentID!=6  && isUnknownID==0){
				printf("Error: %s ", "Parse error");
				printf("in expression %d", expressionIndex);
				printf(": %s ", "expression was not ended\n");
				//printf("\n\"%s %s\" \n", prevToken, currentToken);
				isError=1;
			}


		}

		if(isError == 0){
			printf("OK.");

	}
free(temp);
free(prevNode);
free(currentNode);
}

void freeLL(struct Node *head){
	struct Node *temp;

	while(head !=NULL){
		temp = head;
		head = head->next;
		free(temp);
	}

}
