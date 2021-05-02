// Student: Jarin Musarrat
// Program Description:
// This program takes a txt file of inputs and prints the lexical analyzer along with the parser of a given line statement

#include <stdio.h>
#include <ctype.h>

//Global variables
int charClass;
char lexeme[100];
int nextCharInt;
char nextChar;
int lexLen;
int token;
int nextToken;
FILE * in_fp, * fopen();

// Function Declarations
void expr();
void term();
void factor();

void ifstmt();
void whilestmt();
void stmt();
void booexpr();

void addChar();
void getChar();
void getNonBlank();
double lex();

//Character classes
#define LETTER 0
#define DIGIT 1
#define UNKNOWN 99
//
#define PERIOD 35

//Token codes
#define INT_LIT 10
#define IDENT 11
#define ASSIGN_OP 20
#define ADD_OP 21
#define SUB_OP 22
#define MULT_OP 23
#define DIV_OP 24
#define LEFT_PAREN 25
#define RIGHT_PAREN 26
//
#define EQUAL 27
#define GREATER_THAN 29
//
#define IF_CODE 30
#define ELSE_CODE 31
#define WHILE_CODE 32
#define FLOAT_LIT 9 


//Main class to read the file 
int main(int argc, char *argv[]) {
    char *fileName= argv[1];
    if ((in_fp = fopen(fileName, "r")) == NULL)
       { printf("ERROR - cannot open front.txt \n");}
    else {
        getChar();
        do {
            lex();
            if (nextToken == IF_CODE || nextToken == ELSE_CODE){
                ifstmt();
            }
            else if (nextToken == WHILE_CODE){
                whilestmt();
            }
            else{
                expr();
            }
        } while (nextToken != EOF);
    }
}
// this method calls the <expr> method 
void expr() {
    printf("Enter <expr>\n");
    term();

    while (nextToken == ADD_OP || nextToken == SUB_OP) {
        lex();
        term();
    }
    printf("Exit <expr>\n");
} /* End expr() */

//this method calls the <term> method 
void term() {
    printf("Enter <term>\n");
    factor();

    while (nextToken == MULT_OP || nextToken == DIV_OP) {
        lex();
        factor();
    }
    printf("Exit <term>\n");
} /* End term() */

//this method calls the <term> method 
void factor() {
    printf("Enter <factor>\n");

    if (nextToken == IDENT || nextToken == INT_LIT || nextToken == FLOAT_LIT)
        lex();

    else {
        if (nextToken == LEFT_PAREN) {
            lex();
            expr();
            if (nextToken == RIGHT_PAREN)
                lex();
            else
                printf("Error factor Right Paren \n");
        } else
            printf("Error factor Left Paren \n");
    }

    printf("Exit <factor>\n");
} /* End factor() */

//this method calls the <idstmt> method  
void ifstmt(){
    printf("Enter <ifstmt>\n");
    if (nextToken != IF_CODE)
    printf("Error");
    else{
        lex();
        if (nextToken != LEFT_PAREN)
        printf("Error in ifstmt Left Paren \n");
        else{
            
            booexpr();
            if (nextToken != RIGHT_PAREN)
            printf("Error in ifstmt Right Paren \n");
            
            else {
                lex();
                stmt();
                if (nextToken == ELSE_CODE){
                    lex();
                    stmt();
                }
            }
        }
    }
    printf("Exit <ifstmt>\n");
}

//this method calls the <whilestmt> method 
void whilestmt(){
    printf("Enter <whilestmt>\n");
if (nextToken != WHILE_CODE)

printf("Error in while while code");
else {
        lex();}
if (nextToken != LEFT_PAREN)
        printf("Error in while left paren");
else{
        booexpr();}
if (nextToken != RIGHT_PAREN)
        printf("Error in while right paren");
else {
        lex();
        stmt();
     }    
    printf("Exit <whilestmt>\n");
}

//this method calls the <stmt> method 
void stmt(){
     printf("Enter <stmt>\n");
if (nextToken != IDENT) {
 	printf("Error in stmt ident \n");	
}else {
    lex();
}  
if (nextToken != EQUAL) {
    printf("Error in stmt equal \n");
}else {
     lex();    
     expr();
}       
     printf("Exit <stmt>\n");
}
 
//this method calls the <booexpr> method 
void booexpr(){
    printf("Enter <booexpr>\n");
    if (nextToken != LEFT_PAREN)
        printf("Error in bool left paren \n");
    else {
        lex();
    }
    if (nextToken != IDENT)
            printf("Error in bool ident\n");
    else {
        lex();
    }
    if (nextToken != GREATER_THAN)
            printf("Error in bool greater \n");
    else {
        lex();
    }
    if (nextToken != INT_LIT && nextToken != FLOAT_LIT)
            printf("Error in bool constant \n");
    else {
        lex();
    }
    if (nextToken != RIGHT_PAREN)
            printf("Error in bool right paren \n");
 printf("Exit <booexpr>\n");
}
                         
//-------------

// lookUp for all the characters
int lookup(char ch) {
    switch (ch) {
    case '(':
        addChar();
        nextToken = LEFT_PAREN;
        break;

    case ')':
        addChar();
        nextToken = RIGHT_PAREN;
        break;

    case '+':
        addChar();
        nextToken = ADD_OP;
        break;

    case '-':
        addChar();
        nextToken = SUB_OP;
        break;

    case '*':
        addChar();
        nextToken = MULT_OP;
        break;

    case '/':
        addChar();
        nextToken = DIV_OP;
        break;

    case '=':
        addChar();
        nextToken = EQUAL;
        break;
    
    case '>':
        addChar();
        nextToken = GREATER_THAN;
        break;
    
    default:
        addChar();
        nextToken = EOF;
        break;
    }
    return nextToken;
}

//AddChar adds char to the lexeme array
void addChar() {
    if (lexLen <= 98) {
        lexeme[lexLen++] = nextChar;
        lexeme[lexLen] = 0;
    } else
        printf("Error - lexeme is too long \n");
}

//getChar helps to get next char based on function call
void getChar() {
    if ((nextCharInt = getc(in_fp)) != -1) {
        nextChar = (char) nextCharInt;
        if (isalpha(nextChar))
            charClass = LETTER;
        else if (isdigit(nextChar))
            charClass = DIGIT;
        else if (nextChar == '.')
            charClass = PERIOD;
        else charClass = UNKNOWN;
    } else
        charClass = EOF;
}

// getNonBlank
void getNonBlank() {
    while (isspace(nextChar))
        getChar();
}

//lex
double lex() {
    lexLen = 0;
    getNonBlank();
    switch (charClass) {
    case LETTER:
    //checks if the token word is if 
    if (nextChar == 'i'){
        addChar();
        getChar();
        if (nextChar == 'f')
        { 
            addChar();
            getChar();
            if (nextChar==' '){
                nextToken = IF_CODE;
            }
        }
    }
    //checks if the token word is else 
    else if (nextChar == 'e'){
        addChar();
        getChar();
        if (nextChar == 'l'){
            addChar();
            getChar();
            if (nextChar == 's'){
                addChar();
                getChar();
                if (nextChar=='e'){
                    addChar();
                    getChar();
                   if (nextChar==' '){ 
                       nextToken = ELSE_CODE;
                   }
                }
            }
        }
    }
    //checks if the token word is while
    else if (nextChar == 'w'){
        addChar();
        getChar();
        if (nextChar == 'h'){
            addChar();
            getChar();
            if (nextChar == 'i'){
                addChar();
                getChar();
                if (nextChar == 'l'){
                    addChar();
                    getChar();
                    if (nextChar == 'e'){
                        addChar();
                        getChar();
                        if (nextChar==' '){
                            nextToken = WHILE_CODE;
                        }
                    }
                }
            } 
        }
    }
       else{
        addChar();
        getChar();
        while (charClass == LETTER || charClass == DIGIT) {
            addChar();
            getChar();
        }
        nextToken = IDENT;}

    break;

    //parse period or any float value starting with a . 
    case PERIOD:
        addChar();
        getChar();
            
        if (charClass == PERIOD){
                nextToken = FLOAT_LIT;
            }
            
        while (charClass == DIGIT)
        {            
            addChar();            
            getChar();        
        }
        nextToken = FLOAT_LIT;
        break;  


        // parse int lits
    case DIGIT:
        addChar();
        getChar();
        nextToken = INT_LIT;
        while (charClass == DIGIT) {
            addChar();
            getChar();
        }
        if (charClass == PERIOD){
                nextToken = FLOAT_LIT;
                addChar();
                getChar();
            }
            
        while (charClass == DIGIT)
         {            
            addChar();            
            getChar();        
            }        
        //
        
        break;

        //pares and ops
    case UNKNOWN:
        lookup(nextChar);
        getChar();
        break;

        //EOF
    case EOF:
        nextToken = EOF;
        lexeme[0] = 'E';
        lexeme[1] = 'O';
        lexeme[2] = 'F';
        lexeme[3] = 0;
        break;
    }
    // end of switch
    printf("Next token is: %d, next lexeme is %s\n", nextToken, lexeme);
    return nextToken;
}
