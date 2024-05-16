#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

//Function Declarations

float add(float a, float b);
float subtract(float a, float b);
float multiply(float a, float b);
float divide(float a, float b);
float logarithm(float base, float x);
float square_root(float a);
float my_pow(float a, float b);
float factorial(float a); 
float my_sin(float a);
float my_cos(float a);
float my_tan(float a);
float ln(float a);
void mod(float a, float b, int displayBoth);
void sum(char* a[], int b);
void avg(char* a[], int b);

//Function Implementation

float add(float a, float b){
    return a + b;
}

float subtract(float a, float b){
    return a - b;
}

float multiply(float a, float b){
    return a * b;
}

float divide(float a, float b){
    if(b == 0){
        printf("Error: Division by zero\n");
        exit(1);
    }
    return a / b;
}

float square_root(float a){
    if(a < 0) {
        printf("Error: Square root of a negative number is undefined\n");
        exit(1);
    }
    return sqrt(a);
}

float logarithm(float base, float x){
    if(base <= 0 || x <= 0){
        printf("Error: Logarithm requires positive operands\n");
        exit(1);
    }
    return log(x) / log(base);
}

float my_pow(float a, float b){
    float x = 1;
    for(int i = 0; i < b; i++){
        x *= a;
    }
    return x;
}

float factorial(float a){
    float x = 1;
    for(float i = a; i > 0; i--){
        x *= i;
    }
    return x;
}

float my_sin(float a){
    return sin(a);
}

float my_cos(float a){
    return cos(a);
}

float my_tan(float a){
    return tan(a);
}

float ln(float a){
    if(a > 0){
        return log(a);
    }else{
        printf("Error: Operand must be positive for natural logarithm\n");
        exit(1);
    }
}

void mod(float a, float b, int displayBoth) {
    if (b != 0) {
        float remainder = fmod(a, b);
        printf("Remainder: %.2f\n", remainder);
        if (displayBoth) {
            int result = (int)(a / b);
            printf("Result: %d\n", result);
        }
    } else {
        printf("Error: Division by zero\n");    
        exit(1);
    }
}

void sum(char* argv[], int argc){
    int sum = 0;
    for (int i = 2; i < argc; i++){ 
        float num;
        num = atof(argv[i]); 
        sum += num;
    }
    printf("Sum = %d\n", sum);
}

void avg(char* argv[], int argc){
    int count = argc - 2;
    if(count > 0){
        float sum = 0;
        for (int i = 2; i < argc; i++){ 
            float num;
            num = atof(argv[i]); 
            sum += num;
        }
        double average = sum / count;
        printf("Average = %.2lf\n", average);
    }else{
        printf("Error: No valid inputs for avg\n");
    }
}

//Main Function

int main(int argc, char *argv[]){
    char *operation;
    float operand1, operand2, result;

    //Handling 4 Arguments

    if(argc == 4 && strcmp(argv[1], "sum") != 0 && strcmp(argv[1], "avg") != 0){

        operation = argv[2];
        operand1 = atof(argv[1]);
        operand2 = atof(argv[3]);

        if(strcmp(operation, "+") == 0){
            result = add(operand1, operand2);
        }else if(strcmp(operation, "-") == 0){
            result = subtract(operand1, operand2);
        }else if(strcmp(operation, "x") == 0){ //Changed from "*" to "x".
            result = multiply(operand1, operand2);
        }else if(strcmp(operation, "/") == 0){
            result = divide(operand1, operand2);
        }else if(strcmp(operation, "log") == 0){
            result = logarithm(operand1, operand2);
        }else if(strcmp(operation, "pow") == 0){ // Changed from "^" to "Pow".
            result = my_pow(operand1, operand2);
        }else if(strcmp(operation, "div") == 0){
            result = divide(operand1, operand2);
        }else if(strcmp(operation, "%") == 0){
            mod(operand1, operand2, 1);
            return 0;
        }else if(strcmp(operation, "mod") == 0){
            mod(operand1, operand2, 0);
            return 0;
        }else{
            printf("Usage: %s <operand1> <operation> <operand2>\n", argv[0]);
            return 1;
        }
    
    //Handling 3 Arguments

    }else if(argc == 3 && strcmp(argv[1], "sum") != 0 && strcmp(argv[1], "avg") != 0){

        operation = argv[1];
        operand1 = atof(argv[2]);
        
        if(strcmp(operation, "akar") == 0){
            result = square_root(operand1);
        }else if(strcmp(operation, "log") == 0){
            result = logarithm(10, operand1);
        }else if(strcmp(operation, "factorial") == 0){
            result = factorial(operand1);
        }else if(strcmp(operation, "sin") == 0){
            result = my_sin(operand1); 
        }else if(strcmp(operation, "cos") == 0){
            result = my_cos(operand1); 
        }else if(strcmp(operation, "ln") == 0){
            result = ln(operand1);
        }else if(strcmp(operation, "tan") == 0){
            result = my_tan(operand1); 
        }else{
            printf("Usage: %s <operation> <operand1>\n", argv[0]);
            return 1;
        }
    
    //Handling just the sum and avg functions as these are excluded from argc 3 and 4

    }else if(argc >= 3){

        operation = argv[1];
        operand1 = atof(argv[2]);

        if(strcmp(operation, "sum") == 0){
            sum(argv, argc);
            return 0; // 
        }else if(strcmp(operation, "avg") == 0){
            avg(argv, argc);
            return 0; 
        }else{
            printf("Usage: %s <operation> <operand1> ...\n", argv[0]);
            return 1;
        }

    }else{
        printf("Invalid operation\n");
        return 1;
    }

    printf("Result: %.2f\n", result);
    return 0;
}
