#include <stdio.h>
#include <string.h>
 
/* Converts a binary string (e.g. "1011") to its decimal value */
int binToDec(char *bin){
    int dec=0;
    for(int i=0;bin[i]!='\0';i++){
        dec = dec*2 + (bin[i]-'0');
    }
    return dec;
}
 
/* Converts a decimal value to a binary string of given width */
void decToBin(int dec,int bits,char *out){
    for(int i=bits-1;i>=0;i--){
        out[bits-1-i] = ((dec>>i)&1) + '0';
    }
    out[bits]='\0';
}
 
void gatesModule(){
    char gate[10];
    int n,tc,pass=0,fail=0;
    printf("\nGate (AND/OR/NAND/NOR/XOR/XNOR): ");
    scanf("%s",gate);
    printf("No. of inputs: ");
    scanf("%d",&n);
    printf("No. of test cases: ");
    scanf("%d",&tc);
 
    for(int t=1;t<=tc;t++){
        int in[20],actual,expected=0,ones=0;
        printf("\nTest Case %d\n",t);
 
        for(int i=0;i<n;i++){
            printf("Input %d: ",i+1);
            scanf("%d",&in[i]);
            ones += in[i];
        }
 
        printf("Actual Output: ");
        scanf("%d",&actual);
 
        if(!strcmp(gate,"AND")){
            expected=1; for(int i=0;i<n;i++) expected&=in[i];
        }else if(!strcmp(gate,"OR")){
            expected=0; for(int i=0;i<n;i++) expected|=in[i];
        }else if(!strcmp(gate,"NAND")) expected=!(ones==n);
        else if(!strcmp(gate,"NOR")) expected=!(ones>0);
        else if(!strcmp(gate,"XOR")) expected=ones%2;
        else if(!strcmp(gate,"XNOR")) expected=!(ones%2);
 
        printf("Expected=%d -> %s\n",expected,(expected==actual)?"PASS":"FAIL");
        (expected==actual)?pass++:fail++;
    }
 
    printf("\nSummary: Pass=%d Fail=%d Coverage=%.2f%%\n",pass,fail,100.0*pass/tc);
}
 
void flipflopModule(){
    int ch,Q,D,J,K,S,R,T,actual,expected;
    printf("\n1.D FF 2.JK FF 3.SR FF 4.T FF : ");
    scanf("%d",&ch);
 
    printf("Previous Q: "); scanf("%d",&Q);
 
    if(ch==1){
        printf("D: "); scanf("%d",&D);
        expected=D;
    }else if(ch==2){
        printf("J K: "); scanf("%d%d",&J,&K);
        if(J==0&&K==0) expected=Q;
        else if(J==0&&K==1) expected=0;
        else if(J==1&&K==0) expected=1;
        else expected=!Q;
    }else if(ch==3){
        printf("S R: "); scanf("%d%d",&S,&R);
        if(S==0&&R==0) expected=Q;
        else if(S==0&&R==1) expected=0;
        else if(S==1&&R==0) expected=1;
        else { printf("Invalid SR state\n"); return; }
    }else{
        printf("T: "); scanf("%d",&T);
        expected=(T)?!Q:Q;
    }
 
    printf("Actual Q(next): "); scanf("%d",&actual);
    printf("Expected=%d -> %s\n",expected,(expected==actual)?"PASS":"FAIL");
}
 
void counterModule(){
    int bits,tc,max,pass=0,fail=0,mode;
    char stateBin[21],actualBin[21],expectedBin[21];

    printf("\n1. UP Counter");
    printf("\n2. DOWN Counter");
    printf("\nChoice: ");
    scanf("%d",&mode);

    printf("Counter bits: ");
    scanf("%d",&bits);

    printf("No. of test cases: ");
    scanf("%d",&tc);

    max = 1 << bits;

    for(int t=1;t<=tc;t++){
        int state,expected;

        printf("\nTest Case %d\n",t);

        printf("Present State (binary, %d-bit): ",bits);
        scanf("%s",stateBin);

        state = binToDec(stateBin);

        /* Counter Logic */
        if(mode == 1)              // UP Counter
            expected = (state + 1) % max;
        else                       // DOWN Counter
            expected = (state - 1 + max) % max;

        decToBin(expected,bits,expectedBin);

        printf("Actual Next State (binary, %d-bit): ",bits);
        scanf("%s",actualBin);

        printf("Expected=%s -> %s\n",
               expectedBin,
               (strcmp(expectedBin,actualBin)==0) ? "PASS" : "FAIL");

        if(strcmp(expectedBin,actualBin)==0)
            pass++;
        else
            fail++;
    }

    printf("\nSummary: Pass=%d Fail=%d Coverage=%.2f%%\n",
           pass,fail,100.0*pass/tc);

    if(mode==1)
        printf("Counter Type Tested : UP COUNTER\n");
    else
        printf("Counter Type Tested : DOWN COUNTER\n");
}
int main(){
    int ch;
 
    do{
        printf("\n===== UNIVERSAL ATE SIMULATOR =====\n");
        printf("1. Gates\n2. Flip-Flops\n3. Counters\n4. Exit\n");
        printf("Choice: ");
        scanf("%d",&ch);
 
        switch(ch){
            case 1: gatesModule(); break;
            case 2: flipflopModule(); break;
            case 3: counterModule(); break;
            case 4: printf("Exiting...\n"); break;
            default: printf("Invalid Choice\n");
        }
    }while(ch!=4);
 
    return 0;
}