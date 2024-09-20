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
        Chip(char type, const string& id);
        // Method prototypes
        void setInput1(Chip* inputChip); // Sets the first input chip
        void setInput2(Chip* inputChip); // second input chip (can be NULL)
        void setOutput(Chip* outputChip); // Sets the output chip (can be NULL)
        void compute(); // Performs the operation based on the chip type
        
        void display() const; // Displays the chip's information
        //example: I6, Output = S600 --- for the input Chip
        //example: O50, Input 1 = S600 --- for the output Chip
        //example: A100, Input 1 = I1, Input 2 = I2, Output = M300
        string getId() const; // Returns the chip ID
        char getType(); // Returns chip type
        Chip getInput1();
        Chip getInput2();

//****** OTHER METHODS AS NECESSARY ************//
};
Chip::Chip(char type, const string& identification):chipType(type), id(identification), input1(NULL), input2(NULL), output(NULL){};

void Chip::setInput1(Chip* inputChip){

}
void Chip::setInput2(Chip* inputChip){

}
void Chip::setOutput(Chip* outputChip){

}
void Chip::compute(){

}

void Chip::display() const{ // Chat const after display()
    switch (chipType)
    {
    case 'I':
        cout << chipType << id << ", Output = " << output->getType() << output->getId() << endl;
        break;
    case 'O':
        cout << chipType << id << "Input 1 = " << input1->getType() << input1->getId() << endl;
        break;
    default:
        string in2;
        bool none = false;

        if (input2 == NULL){ // Check to see if chip has a second input
            in2 = "None";
            none = true;
        }

        // Display chip info of chiptype, id, inputchip1 info, inputchip2 info, and outputchip info
        if (none){
            cout << chipType << id << "Input 1 = " << input1->getType() << input1->getId() << ", Input 2 = " << in2 << ", Output = " << output->getType() << output->getId() << endl;
        }
        else{
            cout << chipType << id << "Input 1 = " << input1->getType() << input1->getId() << ", Input 2 = " << input2->getType() << input2->getId() << 
            ", Output = " << output->getType() << output->getId() << endl;
        }
        
        break;
    }
}

string Chip::getId() const{ // Chat fix id error: identifier "id" is undefined
    return id;
}
char Chip::getType(){
    return chipType;
}

int main(){
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
        //create the chip object and initialize it appropriately
        //store the chip object in the allChips array
    }

    for (int i=0; i < numCommands; i++) {
        // read from input the links and make the appropriate
        //connections. You may need to search the array allChips
        //to find the chip that is referred and connect.
        // If the first letter is an O, then execute the compute method
        // on the object referred.
    }
    
    cout << "***** Showing the connections that were established" << endl;
    //for each component created call the display () method
    
    
    return 0;

}