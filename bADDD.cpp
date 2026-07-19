#include <stdio.h>
#include <string.h>
void deposit(void)
{
int accno, fileacc, balance, depositamt;
int found = 0;
char name[20], filename[20];

FILE *fp, *temp;
fp = fopen("deposit.txt", "r");
temp = fopen("temp.txt", "w");

   if (temp == NULL)
    {
        printf("File error!\n");
        return;
    }

    printf("Enter Account Number: ");
    scanf("%d", &accno);

    printf("Enter Deposit Amount: ");
    scanf("%d", &depositamt);

    if (fp != NULL)
    {
        while (fscanf(fp, "%d,%19[^,],%d", &fileacc, filename, &balance) == 3)
        {
            if (fileacc == accno)
            {
                balance += depositamt;
                found = 1;
            }

            fprintf(temp, "%d,%s,%d\n", fileacc, filename, balance);
        }

        fclose(fp);
    }

    /* Account not found -> Create new account */
    if (!found)
    {
        printf("Account not found.\n");
        printf("Enter Customer Name: ");
        scanf("%19s", name);
        fprintf(temp, "%d,%s,%d\n", accno, name, depositamt);
    }

    fclose(temp);

    remove("deposit.txt");
    rename("temp.txt", "deposit.txt");

    if (found)
        printf("Deposit Successful.\n");
    else
        printf("New Account Created Successfully.\n");
}

void check_balance(void){
int accno,checkaccno,balance;
int count=0;
char name[20];
FILE *fp;
fp=fopen("deposit.txt","r");
if(fp==NULL){
printf("File doesn't exist");
return;
}
printf("enter the acc no to check the balance\n");
scanf("%d",&checkaccno);
while(fscanf(fp,"%d,%[^,],%d",&accno,name,&balance)==3){
if(checkaccno==accno){
//printf("account no is :%d\n name is :%s\n balance is :%d\n",accno,name,balance);
printf("account no :%d\n",accno);
printf("name is    :%s\n",name);
printf("balance    :%d\n",balance);
count=1;
break;
} 
}
if(count==0){
printf("cannot find the account details check once");
}
else{
printf("succesfully completly the task");
}
fclose(fp);
}
void loan(){
char name[20];
int loan;
printf("enter the details in the blanks which is related to loan\n ");
FILE *fp;
fp=fopen("loandetails.txt","a");
printf( "enter the loan details\n");
fprintf(fp," Name: %s, loan amount:%d",name, loan);
fclose(fp);
}
void withdrawal(void){
int accno,checkacc,found=0;
char name[20];
int balance,withdrawal;
FILE *fp,*temp;
printf("enter the accoount no to withdrawal\n");
scanf("%d",&checkacc);
fp=fopen("deposit.txt","r");
temp=fopen("temp.txt","w");
while(fscanf(fp,"%d,%[^,],%d",&accno,name,&balance)==3){
if(checkacc==accno){
found=1;
printf("Enter withdrawal amount");
scanf("%d",&withdrawal);
if(withdrawal>balance){
printf("balance insufficient");
}
else{

balance-=withdrawal;
printf("account holder name     : %s\n",name);
printf("the withdrawal amount is: %d\n",withdrawal);
printf("the remaining balance is:%d\n",balance);}}
fprintf(temp,"%d,%s,%d",accno,name,balance);
}
fclose(fp);
if(found=1){
	printf("account founded");
}else{
	printf("account not founded");
}
fclose(temp);
remove("deposit.txt");
rename("temp.txt","deposit.txt");
}
void transfer(void)
{
    int senderAcc, receiverAcc;
    int accno, balance, amount;
    char name[20];

    int senderFound = 0;
    int receiverFound = 0;
    int senderBalance = 0;

    FILE *fp, *temp;

    fp = fopen("deposit.txt", "r");
    temp = fopen("temp.txt", "w");

    if (fp == NULL || temp == NULL)
    {
        printf("File Error!\n");
        return;
    }

    printf("Enter Sender Account Number : ");
    scanf("%d", &senderAcc);

    printf("Enter Receiver Account Number : ");
    scanf("%d", &receiverAcc);

    if(senderAcc == receiverAcc)
    {
        printf("Sender and Receiver account cannot be same.\n");
        fclose(fp);
        fclose(temp);
        remove("temp.txt");
        return;
    }

    printf("Enter Transfer Amount : ");
    scanf("%d", &amount);

    while (fscanf(fp, "%d,%[^,],%d", &accno, name, &balance) == 3)
    {
        /* Sender */
        if (accno == senderAcc)
        {
            senderFound = 1;

            if (balance >= amount)
            {
                balance -= amount;
                senderBalance = balance;
            }
            else
            {
                printf("Insufficient Balance.\n");
                fclose(fp);
                fclose(temp);
                remove("temp.txt");
                return;
            }
        }

        /* Receiver */
        if (accno == receiverAcc)
        {
            receiverFound = 1;
            balance += amount;
        }

        fprintf(temp, "%d,%s,%d\n", accno, name, balance);
    }

    fclose(fp);
    fclose(temp);

    if (!senderFound)
    {
        printf("Sender Account Not Found.\n");
        remove("temp.txt");
        return;
    }

    if (!receiverFound)
    {
        printf("Receiver Account Not Found.\n");
        remove("temp.txt");
        return;
    }

    remove("deposit.txt");
    rename("temp.txt", "deposit.txt");

    printf("\nTransfer Successful.\n");
    printf("Transferred Amount : %d\n", amount);
    printf("Remaining Sender Balance : %d\n", senderBalance);
}
int main(){
int n;
char user1[10]="vivek123",pass1[10]="vivek@123";
char user[10],pass[10];

printf("---------------------------------\n");
printf("WELCOME TO THE ADB BANK OF INDIA\n");
printf("---------------------------------\n");


printf("\n Enter your username:\n");
scanf("%s",user);
printf("enter your password:\n");
scanf("%s",pass);

if(strcmp(user,user1)==0&&strcmp(pass1,pass)==0){
printf("choose your service by entering options\n");
printf("enter  1 to get to check the balance\n");
printf("enter 2 to get the deposit options\n");
printf("enter 3 to get the withdrawal options\n");
printf("enter 4 to get the transfer the money\n");
scanf("%d",&n);
switch(n){
	case 1:check_balance();
		break;
	case 2:deposit();
		break;
	case 3:withdrawal();
	    break;
	case 4:transfer();
	   break;
	default :printf("your option is invalid");
}}

else{
	printf("you entered invalid username or password ");
}
	
	return 0;
}
