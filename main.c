#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

typedef struct node* Ptr;
typedef Ptr Stack;
//Stack to convert to postfix
struct node{
    char charecter;
    Ptr next;
};

struct String_{
    char str[70];
};
typedef struct node_of_int* Ptr_int;
typedef Ptr_int Stack_int;

struct node_of_int{
    int num;
    Ptr_int next;
};

//Linked List
struct List{
    char equ[50];
    int IsValid;
    char postfix[70];
    int true_result; //if there are equality sign
    char post_fst[40];
    char post_sec[40];
    int equl_sign;
    int sec_part_isValue;
    int result;
    char reason_not_valid [50];
    int fst_ans;
    int sec_ans;
    struct List* next;
};
struct List* head=NULL;
//char
int IsEmpty_char(Stack s);
Stack CreateStack_char();
void MakeEmpty_char(Stack s);
void pop_char(Stack s);
char Top_char(Stack s);
void Push_char(Stack s,char charecter);
void DisposeStack(Stack s);
//int
int IsEmpty_int(Stack_int s);
Stack_int CreateStack_int();
void MakeEmpty_int(Stack_int s);
void pop_int(Stack_int s);
int Top_int(Stack_int s);
void Push_int(Stack_int s,int num);

void Read_From_File();
void AddNode_Into_LinkedList(struct List** headRef, struct List* newNode);
int Is_balanced_parentheses(char equ[50]);
struct String_* Infix_To_Postfix(char equ[50]);

int find_priority(char op);
int has_high_Priority(char top,char x);
int two_oper(char equ[50]);
int begin_with_oper(char equ[50]);
int without_oper_between_nump_parentheses(char equ[50]);
int Is_valid(char equ[50],struct List* node);

int Evaluate(int a,int b,char oper,struct List* node);
int Evaluate_postfix(char pos[70],struct List* node);
void after_Read();
int minu();
void Print_Postfix();
void check_if_valid_or_not();
void Print_Evaluation();
void Print_Invalid();
void Print_to_file();

int main(){

    int choice=1;
    printf("  === Welcome in our system ===\n");
    printf("================================\n");
     do{
    choice= minu();
    switch(choice){
    case 1:
        Read_From_File();
        after_Read();
        break;
    case 2:
        check_if_valid_or_not();
        break;
    case 3:
        Print_Postfix();
        break;
    case 4:
        Print_Evaluation();
        break;
    case 5:
        Print_Invalid();
        break;
    case 6:
        Print_to_file();
        break;
    case 7:
        printf(" Thank you ...\n");
        break;
    default:
         printf("The number you entered dose not exist!!! \n");
    }
     printf("-------------------------------------\n");

     }while(choice!=7);

    return 0;
}

void Print_to_file(){
   struct List* temp=head;
    FILE * fp;
    fp = fopen ("output.txt","w");
     if(head==NULL)
        fprintf(fp,"The list is empty!\n");
    else{
        fprintf(fp," Equation >>> valid or not >>> postfix >>> result \n");
        fprintf(fp,"--------------------------------------------------\n");
        while(temp!=NULL){


            if(temp->IsValid){
                if(temp->equl_sign){
                    if(temp->sec_part_isValue){
                        if(temp->true_result)
                            fprintf(fp," * %s >>> valid >>> %s  >> result %d is true  \n",temp->equ,temp->post_fst,temp->result);
                        else
                            fprintf(fp," * %s >>> valid >>> %s  >> result is false >> the true result is %d\n",temp->equ,temp->post_fst,temp->result);
                    }
                    else{ // the second part is equation
                        if(temp->true_result){
                            fprintf(fp," * %s >>> valid >>>\n  >> postfix before equality sign >>> %s \n",temp->equ,temp->post_fst);
                            fprintf(fp,"  >> postfix after equality sign >>> %s \n   >>> The result is %d",temp->post_sec,temp->result);
                        }
                        else{
                            fprintf(fp," * %s >>> valid >>>\n  >> postfix before equality sign >>> %s \n",temp->equ,temp->post_fst);
                            fprintf(fp,"  >> postfix after equality sign >>> %s \n   >>> The result is false  >> %d != %d\n",temp->post_sec,temp->fst_ans,temp->sec_ans);
                        }
                    }
                }
                else //without " = "
                     fprintf(fp," * %s >>> valid >>> %s  >> the result is %d   \n",temp->equ,temp->postfix,temp->result);
            }

            else{ //if not valid
                 fprintf(fp," * %s >>> not valid >>> %s  \n",temp->equ,temp->reason_not_valid);
            }
            temp=temp->next;
        }
    }
    fclose (fp);
    printf(" Done !!!\n");


}

void Print_Invalid(){
    struct List* temp=head;
    if(head==NULL)
        printf("The list is empty!\n");
    else{
        printf("==== Invalid Equation ===========\n");
        while(temp!=NULL){
           if(!(temp->IsValid)){
                 printf(" *  %s \n ",temp->equ);
           }
            temp=temp->next;
        }
    }

}

void Print_Evaluation(){
    struct List* temp=head;
    if(head==NULL)
        printf("The list is empty!\n");
    else{
        printf("===== Evaluation of the postfix expressios ========\n");
        while(temp!=NULL){
            if(temp->IsValid){
                printf(" *  %s >>> ",temp->equ);
                if(temp->equl_sign){ //" = "
                    if(temp->true_result)
                        printf("  %d and the result  is true\n",temp->result);
                    else{//if there " = " & the result false
                        if(temp->sec_part_isValue)
                             printf(" result is false, the true result is: %d\n",temp->result);
                        else{// the second part is equation and the result is false
                            printf(" result is false >> %d != %d\n",temp->fst_ans,temp->sec_ans);
                        }
                    }
                }
                else
                    printf(" %d\n",temp->result);
            }
            temp=temp->next;
        }
    }
}

void check_if_valid_or_not(){

    struct List* temp=head;
    if(head==NULL)
        printf("The list is empty!\n");
    else{
        printf("===== Valid or not ======\n");
        while(temp!=NULL){
            printf(" *  %s >>> ",temp->equ);
            if(!(temp->IsValid)){
                printf("not valid: %s\n",temp->reason_not_valid);
            }
            else{//if valid
                if(temp->equl_sign){ //" = "
                    if(temp->true_result)
                        printf("valid and the result %d is true\n",temp->result);
                    else{//if there " = " & the result false
                        if(temp->sec_part_isValue)
                             printf("valid and the result is false, the true result is: %d\n",temp->result);
                        else{// the second part is equation and the result is false
                            printf("valid and the result is false >> %d != %d\n",temp->fst_ans,temp->sec_ans);
                        }
                    }
                }
                else //without " = "
                    printf("valid \n");
            }

            temp=temp->next;
        }
    }
}

void Print_Postfix(){
    struct List* temp=head;
    if(head==NULL)
        printf("The list is empty!\n");
    else{
        printf("===== Postfix expression ========\n");
        while(temp!=NULL){
            if(temp->IsValid){
                    printf(" * Equation: %s  >>>>> ",temp->equ);
                if(temp->equl_sign){
                    if(temp->sec_part_isValue){
                        printf("%s\n",temp->post_fst);
                    }
                    else{
                        printf("\n  before equal sign: %s\n ",temp->post_fst);
                        printf(" after equal sign: %s\n",temp->post_sec);
                    }
                }
                else{//without equal sign
                    printf("%s\n",temp->postfix);
                }
            }
            temp=temp->next;
        }
    }
}

int minu(){
    int choice=1;
    printf("----------------------------\n");
    printf("1.To read data from the file \n");
    printf("2.To check if the equations is valid or not\n");
    printf("3.To convert equations from infix to postfix \n");
    printf("4.To evaluate the postfix expression  \n");
    printf("5.To print invalid equations \n");
    printf("6.To print equations in file \n");
    printf("7.To Exit \n");
    printf("===================================\n");
    printf("pleas chose one of option \n");
    scanf("%d",&choice);
    printf("\n");
    return choice;
}

void after_Read(){
    struct List* temp=head;
    if(head==NULL)
        printf("The list is empty!\n");
    else{
        while(temp!=NULL){
            temp->equl_sign=0;
            temp->sec_part_isValue=0;
            temp->true_result=0;
            char * ptr;
            int    ch = '=';
            ptr = strchr( temp->equ, ch );

            if(ptr!=NULL){//there are equality sign
                temp->equl_sign=1;
                char fst[50],sec[50],equ[50];
                strcpy(equ,temp->equ);
                strcpy(fst,strtok (equ,"="));
                strcpy(sec,strtok (NULL,"\0"));

                if(Is_valid(fst,temp)){

                    struct String_*fst_post=Infix_To_Postfix(fst);
                    strcpy(temp->post_fst,fst_post->str);
                    int fst_ans=Evaluate_postfix(fst_post->str,temp->equ);
                    //********
                    if(temp->IsValid){
                    int len=strlen(sec);
                    int i=0,num=0;
                        while(isdigit(sec[i])||sec[i]==' '){//
                        i++;
                        }
                        if(i==len){//if the second part is value
                            temp->sec_part_isValue=1;
                            num=atoi(sec);
                            if(Is_valid(sec,temp)){
                                if(num==fst_ans){//if the value is true
                                    temp->true_result=1;
                                }
                                temp->result=fst_ans;
                            }
                        }
                        else{//if the second part is equation
                            if(Is_valid(sec,temp)){
                                struct String_*sec_post=Infix_To_Postfix(sec);
                                strcpy(temp->post_sec,sec_post->str);
                                int sec_ans=Evaluate_postfix(sec_post->str,temp->equ);
                                temp->sec_ans=sec_ans;
                                temp->fst_ans=fst_ans;
                                if(temp->IsValid){
                                    if(fst_ans==sec_ans){
                                        temp->true_result=1 ;
                                        temp->result=fst_ans;
                                    }

                                }
                            }
                        }
                    }
                }
            }
            else{//without equality sign
                if(Is_valid(temp->equ,temp)){
                    struct String_*post=Infix_To_Postfix(temp->equ);
                    strcpy(temp->postfix,post->str);
                    int answer=Evaluate_postfix(post->str,temp->equ);
                    if(temp->IsValid){
                        temp->result=answer;
                    }
                }
            }
            temp=temp->next;
        }
    }
}

struct String_* Infix_To_Postfix(char equ[50]){ // if 0: invalid == there are problems in equ

        struct String_*r=(struct String_*)malloc(sizeof(struct String_));
        Stack oper=CreateStack_char();
        char result[100]="";
        int length=strlen(equ);
        for(int i=0;i<length;i++){
            if(isdigit(equ[i])){
                strncat(result,&equ[i],1);
                //printf("%c",equ[i]);
                int j=i+1;// chick if the next char is digit
                while(isdigit(equ[j])){
                    strncat(result,&equ[j],1);//if digit add it into the result
                  // printf("%c",equ[j]);
                    i++;// to move to next char
                    j=i+1;
                }
                strcat(result," ");
               // printf("\n");
            }
            else if(equ[i]=='('||equ[i]=='{'||equ[i]=='['){
                        Push_char(oper,equ[i]);
                       // printf("Push: %c\n",equ[i]);
            }
            else if(equ[i]==']'||equ[i]=='}'||equ[i]==')'){ //their is no chance to be an empty stack //we chick that in Is_balanced_parentheses function
               // pop until first open parentheses and pop an open parentheses
                //printf("====\non top: %c\n",Top(oper));
                while((Top_char(oper)!='('&&Top_char(oper)!='{'&&Top_char(oper)!='[')){
                 char t=Top_char(oper);
                 strncat(result,&t,1);
                 strcat(result," ");
                 pop_char(oper);
                 //printf("pop (%c)\n",t);
                }
               // printf("on top: %c\n",Top(oper));
                char c=Top_char(oper);
                pop_char(oper);//pop an open parentheses
               // printf("pop (%c)\n",c);
            }
            else if(equ[i]=='+'||equ[i]=='-'||equ[i]=='*'||equ[i]=='/'||equ[i]=='^'||equ[i]=='%'){
                while(!IsEmpty_char(oper)&&!has_high_Priority(Top_char(oper),equ[i])){
                     char t=Top_char(oper);
                    strncat(result,&t,1);
                    strcat(result," ");
                    pop_char(oper);
                    //printf("pop (%c)\n",t);
                }
                 Push_char(oper,equ[i]);
                // printf("Push: %c\n",equ[i]);
            }


            //else==> invalid if its not '='
        }
        while(!IsEmpty_char(oper)){
             char t=Top_char(oper);
                    strncat(result,&t,1);
                    strcat(result," ");
                    pop_char(oper);
                    //printf("pop (%c)\n",t);
        }
       // printf("result:%s\n",result);
        strcpy(r->str,result);
        return r;

}

int Evaluate_postfix(char pos[70],struct List* node){
    Stack_int s=CreateStack_int();
    int length=strlen(pos);
    int a,b,result,num;
    for(int i=0;i<length;i++){
        if(pos[i]==' ')
            continue;
        if(pos[i]=='*'||pos[i]=='/'||pos[i]=='%'||pos[i]=='^'||pos[i]=='+'||pos[i]=='-'){
            a=Top_int(s);
            pop_int(s);
            b=Top_int(s);
            pop_int(s);
            result=Evaluate(a,b,pos[i],node);
            Push_int(s,result);
        }
        else{
            num=0;
            while(isdigit(pos[i])){
                num=num*10+(pos[i]-'0');
                i++;
            }
            i--;
            Push_int(s,num);
        }
    }

    result=Top_int(s);
    pop_int(s);
    if(!IsEmpty_int(s)){
        node->IsValid=0;
        strcpy(node->reason_not_valid," error in postfix evaluation.");
    }


    return result;

    }

int Evaluate(int a,int b,char oper,struct List* node){
    int res=0;
    switch(oper){
    case'*':
        res=b*a;
        break;
    case'/':
        if(a==0){
            node->IsValid=0;
            strcpy(node->reason_not_valid,"Divide by zero.");
            return 0;
        }
        res=b/a;
        break;
    case'%':
        res=b%a;
        break;
    case'+':
        res=b+a;
        break;
    case'-':
        res=b-a;
        break;
    case'^':
        res=pow(b,a);
        break;
    }
    return res;
}

int Is_valid(char equ[50],struct List* node){

    int IsValid=0; // at beginning let all Invalid

    if(Is_balanced_parentheses(equ)){
        if(!begin_with_oper(equ)){
            if(!two_oper(equ)){
                if(!without_oper_between_nump_parentheses(equ)){
                    IsValid=1;
                    node->IsValid=1;
                }
                strcpy(node->reason_not_valid,"There is no operator between the number and parentheses.");
                return IsValid;
            }
             strcpy(node->reason_not_valid,"There are two operator behind each other.");
            return IsValid;
        }
        strcpy(node->reason_not_valid,"The equation is beginning with operator.");
        return IsValid;
    }
   strcpy(node->reason_not_valid,"The parentheses are not balanced.");
    return IsValid;
}

int two_oper(char equ[50]){
    int length=strlen(equ);
    int j;
    for(int i=0;i<length;i++){
        if(equ[i]=='*'||equ[i]=='/'||equ[i]=='%'||equ[i]=='+'||equ[i]=='-'||equ[i]=='^'){
            j=i+1;
            if(equ[j]=='*'||equ[j]=='/'||equ[j]=='%'||equ[j]=='+'||equ[j]=='-'||equ[j]=='^')
                return 1;
        }
    }
    return 0;
}

int begin_with_oper(char equ[50]){
    int i=0;
        while(equ[i]==' ')
            i++;
        if(equ[i]=='*'||equ[i]=='/'||equ[i]=='%'||equ[i]=='+'||equ[i]=='-'||equ[i]=='^')
            return 1;
        return 0;
}

int without_oper_between_nump_parentheses(char equ[50]){ // e.g: 5[4*3] instead 5+[4*3]//or [3-1]7
    int length=strlen(equ);
    int j;
    for(int i=0;i<length;i++){
        if(isdigit(equ[i])){
            j=i+1;
            if(equ[j]=='('||equ[j]=='{'||equ[j]=='[')
                return 1;
        }
        else if(equ[i]==')'||equ[i]=='}'||equ[i]==']'){
            j=i+1;
            if(isdigit(equ[j]))
                return 1;
        }
    }
    return 0;
}

int has_high_Priority(char top,char x){// if Priority of top is higher than x return 1// else return 0
    int topPir=find_priority(top);
    int xPir=find_priority(x);
    if (xPir>topPir)
        return 1;
    return 0;
}

int find_priority(char op){
    if(op=='+'||op=='-')
        return 1;
    else if(op=='*'||op=='/'||op=='%')
        return 2;
    else if(op=='^')
        return 3;
    else if(op=='('||op=='{'||op=='[')
        return 0;
    return -1; ///*************
}

int Is_balanced_parentheses(char equ[50]){ // return 1 if balanced // 0 if not
    Stack temp=CreateStack_char();
    int siz=strlen(equ);
    for(int i=0;i<siz;i++){
        if(equ[i]=='('||equ[i]=='{'||equ[i]=='['||equ[i]==']'||equ[i]=='}'||equ[i]==')'){//if parentheses
            if(equ[i]=='('||equ[i]=='{'||equ[i]=='['){
                Push_char(temp,equ[i]);
            }
            else if(equ[i]==')'||equ[i]=='}'||equ[i]==']'){
                if(IsEmpty_char(temp))
                    return 0;
                else{
                    if (Top_char(temp)=='('&&equ[i]==')')
                        pop_char(temp);
                    else if(Top_char(temp)=='{'&&equ[i]=='}')
                        pop_char(temp);
                    else if(Top_char(temp)=='['&&equ[i]==']')
                        pop_char(temp);
                    else
                        return 0;
                }
            }
        }
    }
    return IsEmpty_char(temp)?1:0;
}

void AddNode_Into_LinkedList(struct List** headRef, struct List* newNode) {
    struct List* current = *headRef;
    newNode->next = NULL;
    // in case length is 0
    if (current == NULL)
        *headRef = newNode;
    else {
        // find the last node
        while (current->next != NULL)
            current = current->next;
        current->next = newNode;
    }
}

void Read_From_File(){
   char ch, file_name[30],line[50];
   struct List* newNode;
   FILE *fp;
   fflush(stdin);
   printf("Enter name of a file you wish to see\n");
   gets(file_name);
   fp = fopen(file_name, "r");
   if (fp == NULL){
      perror("Error while opening the file.\n");
      return 0;
   }
    while (!feof(fp)){
        fflush(stdin);
        fgets(line,50,fp);
        struct List* current=(struct List*)malloc(sizeof(struct List));
        strcpy(current->equ,strtok (line,"\n"));
        current->IsValid=0;
     // (Is_balanced_parentheses(current->equ))?(current->IsValid=1):(current->IsValid=0);
        AddNode_Into_LinkedList(&head,current);

    }
    printf(" Read from file successfully!! \n");
    fclose(fp);
}

//for stack of char
int IsEmpty_char(Stack s){ // return 1 if empty & 0 if not
return (s->next==NULL);
}
Stack CreateStack_char(){
    Stack s=(Stack)malloc(sizeof(struct node));
    if(s==NULL)
        printf("Out of space!\n");
    s->next=NULL;
   // printf("%d\n",(int)(s->next==NULL));
    MakeEmpty_char(s);
    return s;
}
void MakeEmpty_char(Stack s){
    if(s==NULL)
        printf("Out of Space!\n");
    else{
        while(!IsEmpty_char(s))
            pop_char(s);
    }
}
void pop_char(Stack s){
    Ptr atTop;
    if(!IsEmpty_char(s)){
        atTop=s->next;
        s->next=s->next->next;
        free(atTop);
    }

}
char Top_char(Stack s){
    if(!IsEmpty_char(s))
        return s->next->charecter;
    printf("Empty stack!\n");
    return 0;
}
void Push_char(Stack s,char charecter){
    Ptr temp;
    temp=(Stack)malloc(sizeof(struct node));
    if(temp==NULL)
        printf("Out Of Space!\n");
    else{
        temp->charecter=charecter;
        temp->next=s->next;
        s->next=temp;
        //printf("done\n");
    }
}
void DisposeStack(Stack s){
    MakeEmpty_char(s);
    free(s);
}

// for stack of int
int IsEmpty_int(Stack_int s){ // return 1 if empty & 0 if not
return (s->next==NULL);
}
Stack_int CreateStack_int(){
    Stack_int s=(Stack_int)malloc(sizeof(struct node_of_int));
    if(s==NULL)
        printf("Out of space!\n");
    s->next=NULL;
    MakeEmpty_int(s);
    return s;
}
void MakeEmpty_int(Stack_int s){
    if(s==NULL)
        printf("Out of Space!\n");
    else{
        while(!IsEmpty_int(s))
            pop_int(s);
    }
}
void pop_int(Stack_int s){
    Ptr_int atTop;
    if(!IsEmpty_int(s)){
        atTop=s->next;
        s->next=s->next->next;
        free(atTop);
    }
}
int Top_int(Stack_int s){
    if(!IsEmpty_int(s))
        return s->next->num;
    printf("Empty stack!\n");
    return 0;
}
void Push_int(Stack_int s,int num){
    Ptr_int temp;
    temp=(Stack_int)malloc(sizeof(struct node_of_int));
    if(temp==NULL)
        printf("Out Of Space!\n");
    else{
        temp->num=num;
        temp->next=s->next;
        s->next=temp;
    }
}
