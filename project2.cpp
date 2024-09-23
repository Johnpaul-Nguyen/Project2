#include <iostream>
#include <string>
using namespace std;

class Chip {
    private:
        char chipType; // Type of the chip (A: Addition, S: Subtraction, etc.)
        string id; // Unique identifier for the chip
        Chip* input1; // Pointer to the first input chip
        Chip* input2; // Pointer to the second input chip (can be NULL)
        Chip* output; // Ptr to the output chip (is NULL for output chips)
        double inputValue; //for the input chip
    public:
        // Constructor
        Chip(); // Default Constructor
        Chip(char type, const string& id); 
        Chip(Chip* chip); // Copy Constructor
        // Method prototypes
        void setInput1(Chip* inputChip); // Sets the first input chip
        void setInput2(Chip* inputChip); // second input chip (can be NULL)
        void setOutput(Chip* outputChip); // Sets the output chip (can be NULL)
        void setInputValue(int value); // Sets the inputValue of input chips
        void compute(); // Performs the operation based on the chip type
        
        void display() const; // Displays the chip's information
        //example: I6, Output = S600 --- for the input Chip
        //example: O50, Input 1 = S600 --- for the output Chip
        //example: A100, Input 1 = I1, Input 2 = I2, Output = M300
        string getId() const; // Returns the chip ID
        char getType(); // Returns chip type
        Chip* getInput1();
        Chip* getInput2();
        int getInputValue(); // Returns input value
        ~Chip();

//****** OTHER METHODS AS NECESSARY ************//
};
Chip::Chip():chipType(' '), id(" "), input1(NULL), input2(NULL), output(NULL), inputValue(0.0){};
Chip::Chip(char type, const string& identification):chipType(type), id(identification), input1(NULL), input2(NULL), output(NULL), inputValue(0.0){};
Chip::Chip(Chip* chip):chipType(chip->chipType), id(chip->id), input1(chip->input1), input2(chip->input2), output(chip->output), inputValue(chip->inputValue){};

void Chip::setInput1(Chip* inputChip){ input1 = inputChip; }
void Chip::setInput2(Chip* inputChip){ input2 = inputChip; }
void Chip::setOutput(Chip* outputChip){ output = outputChip; }
void Chip::setInputValue(int value){ inputValue = value; }
void Chip::compute(){

}

void Chip::display() const{ // Chat const after display() // Chat: Make sure you are not displaying null pointers
    cout << "Start of Display function" << endl;
    switch (chipType)
    {
    case 'I':
        cout << "Case 'I'" << endl;
        if (output == NULL){
            cout << "Output is none" << endl;
        }
        else{
            cout << chipType << id << ", Output = " << output->getType() << output->getId() << endl;
        }
        
        break;
    case 'O':
        cout << "Case 'O'" << endl;
        if (input1 == NULL){
            cout << chipType << id << ", Input is none" << endl;
        }
        else{
            cout << chipType << id << ", Input 1 = " << input1->getType() << input1->getId() << endl;
        }

        
        break;
    default:
        cout << "Default Case" << endl;
        string in1;
        string in2;
        bool none1 = (input1 == NULL);
        bool none2 = (input2 == NULL);

        // Display chip info of chiptype, id, inputchip1 info, inputchip2 info, and outputchip info
        if (none2 && none1){
            in1 = "None";
            in2 = "None";

            cout << chipType << id << ", Input 1 = " << in1 << ", Input 2 = " << in2 << ", Output = " << output->getType() << output->getId() << endl;
        }
        else if(none1){
            in1 = "None";
            in2 = input2->getType() + input2->getId();

            cout << chipType << id << ", Input 1 = " << in1 << ", Input 2 = " << in2 << ", Output = " << output->getType() << output->getId() << endl;
        }
        else if(none2){
            in1 = input1->getType() + input1->getId();
            in2 = "None";

            cout << chipType << id << ", Input 1 = " << in1 << ", Input 2 = " << in2 << ", Output = " << output->getType() << output->getId() << endl;
        }
        else{
            in1 = input1->getType() + input1->getId();
            in2 = input2->getType() + input2->getId();

            cout << chipType << id << ", Input 1 = " << in1 << ", Input 2 = " << in2 << ", Output = " << output->getType() << output->getId() << endl;
        }
        break;
    }
}

string Chip::getId() const{ return id; }// Chat fix id error: identifier "id" is undefined
char Chip::getType(){ return chipType; }
int Chip::getInputValue(){ return inputValue; }
Chip* Chip::getInput1(){ return input1; }
Chip* Chip::getInput2(){ return input2; }

Chip::~Chip(){
    
}

int main(){
    cout << "Start Main" << endl;

    //**** ALL THE VARIABLES YOU NEED FOR THIS MAIN FUNCTION *****//
    int numChips;
    Chip** allChips;
    int numCommands;
    cin >> numChips;
    //create an array Chip objects pointers
    allChips = new Chip*[numChips];
    //each array location is a pointer to a Chip Object
    for (int i=0; i < numChips; i++) {
        //read the chip ID based on the first letter to determine its type
        string input;
        cin >> input;
        
        char chipType = input.at(0);
        string chipId = input.substr(1, input.size());
        //create the chip object and initialize it appropriately
        Chip* chip = new Chip(chipType, chipId);

        //store the chip object in the allChips array
        allChips[i] = chip;
    }

    for (int i = 0; i < numChips; i++){
        cout << "Chip type: " << allChips[i][0].getType() << ", Chip id: " << allChips[i][0].getId() << endl;
    }

    cin >> numCommands;

    for (int i = 0; i < numCommands; i++) {

        // read from input the links and make the appropriate
        //connections. You may need to search the array allChips
        //to find the chip that is referred and connect.
        // If the first letter is an O, then execute the compute method
        // on the object referred.
        
        string command;
        string firstInput;
        string secondInput;
        int secondInputInt;
        Chip* firstChip;
        Chip* secondChip;
        int firstChipIndex = 0;
        int secondChipIndex = 0;
        
        cin >> command;

        /* Note to self: Think about making a function that reads in the circuit type and id to easily store 
        inputs and outputs*/
        /* I need to find a way to assign outputs of chips. You have inputs already, How do you assign outputs?*/

        switch (command.at(0))
        {
        case 'I':
            cout << "Case I" << endl;
            cin >> firstInput >> secondInputInt;
            cout << "First Input: " << firstInput << ", Value of input: " << secondInputInt << endl;

            for (int j = 0; j < numChips; j++){
                if (allChips[j][0].getType() == firstInput.at(0) && allChips[j][0].getId() == firstInput.substr(1, firstInput.size())){
                    allChips[j][0].setInputValue(secondInputInt);
                }
            }

            break;

        case 'O':
            cout << "Case O" << endl;
            cin >> firstInput;

            int outIndex;
            for (int j = 0; j < numChips; j++){
                if (allChips[j][0].getType() == 'O'){
                    outIndex = j;
                    break;
                }
            }
           
            // allChips[outIndex][0].compute();
            //cout << "Output value of the circuit is: " << allChips[outIndex][0].getInputValue() << endl;
            break;

        default:
            cout << "Default Case" << endl;

            cin >> firstInput >> secondInput;

            for (int j = 0; j < numChips; j++){
                if (allChips[j][0].getType() == firstInput.at(0) && allChips[j][0].getId() == firstInput.substr(1, firstInput.size())){
                    firstChip = allChips[j];
                    firstChipIndex = j;
                }
                if (allChips[j][0].getType() == secondInput.at(0) && allChips[j][0].getId() == secondInput.substr(1, secondInput.size())){
                    secondChip = allChips[j];
                    secondChipIndex = j;
                }
                
                if (firstChipIndex != 0 && secondChipIndex != 0){
                    break;
                }
            }

            if (allChips[secondChipIndex][0].getInput1() == NULL){
                allChips[secondChipIndex][0].setInput1(allChips[firstChipIndex]);
                
            }
            else if(allChips[secondChipIndex][0].getInput2() == NULL){
                allChips[secondChipIndex][0].setInput2(allChips[firstChipIndex]);
            }

            allChips[firstChipIndex][0].setOutput(allChips[secondChipIndex]);

            break;
        }
    }

    
    cout << "***** Showing the connections that were established" << endl;
    //for each component created call the display () method
    
    for (int i = 0; i < numChips; i++){
        cout << "Iteration of displaying: " << i << endl;
        
        allChips[i]->display();
    }
    
    return 0;

}