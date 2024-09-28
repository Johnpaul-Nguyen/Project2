#include <iostream>
#include <string>
using namespace std;

/* ***************************************************************** Chip Class ***************************************************************** */
class Chip {
    private:
        char chipType; // Type of the chip (A: Addition, S: Subtraction, etc.)
        string id; // Unique identifier for the chip
        Chip* input1; // Pointer to the first input chip
        Chip* input2; // Pointer to the second input chip (can be NULL)
        Chip* output; // Ptr to the output chip (is NULL for output chips)
        double inputValue; // For the input chip
    public:
        // Constructor
        Chip(); // Default Constructor
        Chip(char type, const string& id); 
        
        // Get/Set Methods
        string getId() const; // Returns the chip ID
        char getType() const; // Returns chip type
        Chip* getInput1(); // Returns the first chip input
        Chip* getInput2(); // Returns the second chip input (if any)
        Chip* getOutput(); // Returns the output chip
        double getInputValue(); // Returns input value
        
        void setInput1(Chip* inputChip); // Sets the first input chip
        void setInput2(Chip* inputChip); // Second input chip (can be NULL)
        void setOutput(Chip* outputChip); // Sets the output chip (can be NULL)
        void setInputValue(double value); // Sets the inputValue of input chips - DOUBLE

        // Chip Methods
        void compute(); // Performs the operation based on the chip type
        void display() const; // Displays the chip's information
        // Example: I6, Output = S600 --- for the input chip
        // Example: O50, Input 1 = S600 --- for the output chip
        // Example: A100, Input 1 = I1, Input 2 = I2, Output = M300 --- for other chips

        // Destructor. More information on this at the destuctor method
        ~Chip();
};

/* ***************************************************************** Chip Methods ***************************************************************** */
// Construct constructors similar to previous project
Chip::Chip():chipType(' '), id(" "), input1(nullptr), input2(nullptr), output(nullptr), inputValue(0.0){}; // Sets input and output chips to nullpointers
Chip::Chip(char type, const string& identification):chipType(type), id(identification), input1(nullptr), input2(nullptr), output(nullptr), inputValue(0.0){};

// Get Functions
/* LLM: 
    Similar to the display method. The comiler does not lke having to get something if it has
    the chance to modify it, causing problems with the compiler. 
*/
string Chip::getId() const{ return id; }
char Chip::getType() const{ return chipType; }
Chip* Chip::getInput1(){ return input1; }
Chip* Chip::getInput2(){ return input2; }
Chip* Chip::getOutput(){ return output; }
double Chip::getInputValue(){ return inputValue; }

// Set functions
void Chip::setInput1(Chip* inputChip){ input1 = inputChip; }
void Chip::setInput2(Chip* inputChip){ input2 = inputChip; }
void Chip::setOutput(Chip* outputChip){ output = outputChip; }
void Chip::setInputValue(double value){ inputValue = value; }

// Compute Function: The purpose of this funtion is to determine the type of operation the chip is associated to and execute that operation
void Chip::compute(){
    // These bool variables are used to determine whether the input chips are 'I' chips    
    bool in1Type = false;
    bool in2Type = false;

    // Checks to see if the chips has one or two inputs
    if (input2 == nullptr){
        in1Type = (input1->getType() == 'I');
    }
    else{
        in1Type = (input1->getType() == 'I');
        in2Type = (input2->getType() == 'I');
    }

    // Operation performed based on chipType
    switch (chipType)
    {
    case 'O': // Output Chip: Recursively call compute until 'O' chip has the final value

        cout << "Computation Starts" << endl;

        // Calls compute function on input chip. Starts a chain of compute functions on the following chips (similar to recursion)
        input1->compute();

        // Outputs the final value after computation
        cout << "The output value from this circuit is " << inputValue << endl;
        break;

    case 'A': // Addition Chip: Adds input values of the corresponding input chips

        if (in1Type && in2Type){
            setInputValue(input1->getInputValue() + input2->getInputValue());
        }
        else if (in1Type){
            input2->compute();
            setInputValue(input1->getInputValue() + input2->getInputValue());
        }
        else if (in2Type){
            input1->compute();
            setInputValue(input1->getInputValue() + input2->getInputValue());
        }
        else{
            input1->compute();
            input2->compute();
            setInputValue(input1->getInputValue() + input2->getInputValue());
        }

        // Checks if the output chip is the 'O' chip (final chip)
        if (output->getType() == 'O'){
            output->setInputValue(inputValue);
        }
        break;

    case 'S': // Subtraction Chip: Subtracts input values of corresponding input chips

        if (in1Type && in2Type){
            setInputValue(input1->getInputValue() - input2->getInputValue());
        }
        else if (in1Type){
            input2->compute();
            setInputValue(input1->getInputValue() - input2->getInputValue());
        }
        else if (in2Type){
            input1->compute();
            setInputValue(input1->getInputValue() - input2->getInputValue());
        }
        else{
            input1->compute();
            input2->compute();
            setInputValue(input1->getInputValue() - input2->getInputValue());
        }

        // Checks if the output chip is the 'O' chip (final chip)
        if (output->getType() == 'O'){
            output->setInputValue(inputValue);
        }
        break;

    case 'M': // Multiplication Chip: Performs multiplication on the input values of the input chips

        if (in1Type && in2Type){
            setInputValue(input1->getInputValue() * input2->getInputValue());
        }
        else if (in1Type){
            input2->compute();
            setInputValue(input1->getInputValue() * input2->getInputValue());
        }
        else if (in2Type){
            input1->compute();
            setInputValue(input1->getInputValue() * input2->getInputValue());
        }
        else{
            input1->compute();
            input2->compute();
            setInputValue(input1->getInputValue() * input2->getInputValue());
        }

        // Checks if the output chip is the 'O' chip (final chip)
        if (output->getType() == 'O'){
            output->setInputValue(inputValue);
        }
        break;

    case 'D': // Division Chip: Performs division on the input values of the correspnding input chips

        // Checks inputValue of input2 is 0 (dividing by 0; input value of 1 / input value of 2)
        if (input2->getInputValue() != 0){
            if (in1Type && in2Type){
                setInputValue(input1->getInputValue() / input2->getInputValue());
            }
            else if (in1Type){
                input2->compute();
                setInputValue(input1->getInputValue() / input2->getInputValue());
            }
            else if (in2Type){
                input1->compute();
                setInputValue(input1->getInputValue() / input2->getInputValue());
                
            }
            else{
                input1->compute();
                input2->compute();
                setInputValue(input1->getInputValue() / input2->getInputValue());
            }
        }
        else{
            cout << "Can't divide by 0" << endl;
        }

        // Checks if the output chip is the 'O' chip (final chip)
        if (output->getType() == 'O'){
            output->setInputValue(inputValue);
        }
        break;

    case 'N': // Not Chip: Negates the input value (multiply by -1)
    
        if (in1Type){
            setInputValue(-1 * (input1->getInputValue()));
        }
        else{
            input1->compute();
            setInputValue(-1 * (input1->getInputValue()));
        }

        // Checks if the output chip is the 'O' chip (final chip)
        if (output->getType() == 'O'){
            output->setInputValue(inputValue);
        }
        break;

    default: 
    // Case 'I'. Does nothing since previous chips take input values from their corresponding input chips.
    // Since 'I' chips only have an input value and not input chips, 'I' chips are the start chips of the compute method
        break;
    }
}

/* LLM: 
        I asked Chat to help me fix an error with the display function. Chat had given me a suggestion of using the keyword const
        at the end of the funciton signature. I implemented the suggestion and the function worked. I later asked Chat, why we the 
        const keyword was used and Chat explained to me that the keyword const tells the compiler that this function, the display
        function, will not change any const objects. The compiler believes that without the const keyword, the function could
        potentially modify variables within the object. This helped me understand the reason to use const variables and functions 
*/
// Display method: This function's purpose is to show the connections of corresonding chips (i.e. A100, Input 1 = I1, Input 2 = I2, Output = M300)
void Chip::display() const{
    // Uses chipType to determine which chip display to output
    switch (chipType)
    {
    case 'I':
        // If connection was not established
        if (output == nullptr){
            cout << "Output is none" << endl;
        }
        else{
            cout << chipType << id << ", Output = " << output->getType() << output->getId() << endl;
        }
        break;

    case 'O':

        if (input1 == nullptr){
            cout << chipType << id << ", Input is none" << endl;
        }
        else{
            cout << chipType << id << ", Input 1 = " << input1->getType() << input1->getId() << endl;
        }
        break;

    default:

        string in1; // String of input1 type and id
        string in2; // String of input2 type and id

        // If input 1 or 2 are null, set bool values to true
        bool none1 = (input1 == nullptr);
        bool none2 = (input2 == nullptr);

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

// Destructor Function
/* LLM: 
        I asked Chat how I would delete the chips in my program. Chat had pointed out that the chips in the program were statically defined 
        and was automatically deleted with the ending of the program. I then asked why and how was this the case. Chat replaied that the input
        and output chips were not dynamically defined in the class, but instead was just references to other chips. I asked chat to further expand
        on that and I learned more about statically and dynamically defining and how it affects memory 
*/
Chip::~Chip(){;
    // Nothing to delete since all memory was statically defined and not dynamically defined

    /* If made dynamically, destructor will look like:
    delete input1;
    delete input2; 
    */
}

/* ***************************************************************** Main Funtion ***************************************************************** */
int main(){

    int numChips;
    Chip** allChips;
    int numCommands;
    Chip* oChip; // To place O chip in the last slot of the array
    bool oChipBool = false; // Check if oChip has been found

    // Reads in number of chips
    cin >> numChips;

    // Create an array Chip objects pointers
    allChips = new Chip*[numChips];

    // Each array location is a pointer to a Chip Object
    for (int i=0; i < numChips; i++) {
        // Read the chip ID based on the first letter to determine its type
        string input;
        cin >> input;

        char chipType = input.at(0);
        string chipId = input.substr(1, input.size());
        // Create the chip object and initialize it appropriately
        Chip* chip = new Chip(chipType, chipId);

        // Store the chip object in the allChips array
        if (chipType == 'O'){
            oChip = chip;
            oChipBool = true;
        }
        else if (!oChipBool){
            // For all chips that come before oChip
            allChips[i] = chip;
        }
        else{
            // Index offset by one since oChip takes one iteration of i
            allChips[i - 1] = chip;
        }
    }

    // Inserts 'O' chip to the end of the array
    allChips[numChips - 1] = oChip;

    // Reads in number of commands the chips need to execute
    cin >> numCommands;
    // Read from input the links and make the appropriate connections. You may need to search the array allChips to 
    // find the chip that is referred and connect
    for (int i = 0; i < numCommands; i++) {
        char command;
        string firstInput;
        string secondInput;
        
        // Used to find and store the index of the first chip in allChips
        int firstChipIndex = 0; 
        int secondChipIndex = 0;

        // For input chips
        double secondInputDouble; 

        // If the first letter is an O, then execute the compute method on the object referred.
        cin >> command;

        switch (command)
        {
            case 'I': // Case 'I': Assigns a value to input chips
                
                // Reads in input chip and value it is to be assigned
                cin >> firstInput >> secondInputDouble;

                for (int j = 0; j < numChips; j++){
                    // Finds chip and sets input value
                    if (allChips[j][0].getType() == firstInput.at(0) && allChips[j][0].getId() == firstInput.substr(1, firstInput.size())){
                        allChips[j][0].setInputValue(secondInputDouble);
                        break;
                    }
                }
                break;

            case 'O': // Case 'O': Finds O chip and executes compute function
                
                cin >> firstInput;

                int outputChipIndex;
                for (int j = 0; j < numChips; j++){
                    if (allChips[j][0].getType() == firstInput.at(0)){
                        outputChipIndex = j;
                        break;
                    }
                }
                allChips[outputChipIndex][0].compute();
                break;

            default: // Command 'A': Add chip to circuit. No other commands

                cin >> firstInput >> secondInput;

                // Searches through array allChips and grabs the indeces of both input chips
                for (int j = 0; j < numChips; j++){
                    if (allChips[j][0].getType() == firstInput.at(0) && allChips[j][0].getId() == firstInput.substr(1, firstInput.size())){
                        firstChipIndex = j;
                    }
                    if (allChips[j][0].getType() == secondInput.at(0) && allChips[j][0].getId() == secondInput.substr(1, secondInput.size())){
                        secondChipIndex = j;
                    }
                    
                    // Leaves for loop when both indeces are found
                    if (firstChipIndex != 0 && secondChipIndex != 0){
                        break;
                    }
                }

                // Checks if chip has an input chip in its first chip slot. If it does, checks second input chip slot (ex: A I1 A100, A I2 A100)
                if (allChips[secondChipIndex][0].getInput1() == nullptr){
                    allChips[secondChipIndex][0].setInput1(allChips[firstChipIndex]);
                    
                }
                else if(allChips[secondChipIndex][0].getInput2() == nullptr){
                    allChips[secondChipIndex][0].setInput2(allChips[firstChipIndex]);
                }

                // Assigns the second chip read in as the output chip to the first chip that was read in
                allChips[firstChipIndex][0].setOutput(allChips[secondChipIndex]);
                break;
        }
    }

    cout << "***** Showing the connections that were established" << endl;

    // For each component created call the display() method
    for (int i = 0; i < numChips; i++){
    allChips[i]->display();
    }

    // Delete chips in allChips array to free memory
    delete[] allChips;
    delete oChip; // Dynamically made chip. To the garbage it goes

    return 0;
}

/*
    Documentation: For this project, I have used ChatGPT less in comparison to the first project. Maybe becuase I had a 
    better grasp of how this project should be or maybe I came into this project knowing more from the last project helped 
    me understand what I was dealing with. Although I understood what the project asked me, there were times where I turned
    to ChatGPT to help me with issues I ran into. The LLM usage for this project is mainly targeted two functions, the display
    function and the destructor. 

    LLM Usage Documentation:
        Towards the beginning of the project. I wanted to first work on the display function, as it would help me debug my 
        code (using cout to check for chip connections and input values (at the time I had displayed input values of all chips 
        to see where the operations were messing up)). I began to build the display function with switch cases, which took the 
        chip type and compared it to the desired outputs. The outputs were categorized in three groups: 'I' chips which displays 
        the output chip and the input value (at the time), 'O' chips which displayed the input chip, and all other chips, which 
        displayed either one or two input chips (i.e. 'N' chips have one input, 'A' chips have two). To display the chip type and 
        chip id, I used the chipType and chipId variables to display the chip, and getters of chipType and chipId for the 
        input/output chips. This is when the first issue arose. VS Code was pointing that there was an error happening in the display 
        method. I tried using the this. technique and using this.chipType, this.getChipType(), and with little luck, none was working. 
        So I asked ChatGPT, "Hey, something is wrong with my display funciton. What's wrong with it?". Chat then suggested me to use 
        the keyword const in the function signature. I went to implement the keyword const into the display signature and low and 
        behold, it stopped showing errors and worked when I compiled it. I then asked Chat to explain to me what const meant and I'm 
        happy that I did. I learned a lot about why the const keyword is used. Essentially, the const keyword allows the compiler to feel 
        secure about using the function. The reason behind this is because without the const keyword, the compiler thinks that it could 
        change some of the data. The const keyword ensures the compiler that it will not change data when calling the display function.
        This started making sense to me after I though about it. I was using the class variables chipType and chipId, which is allowing 
        access to where it should not be. This helped me debug my code, making sure that I have made the correct conections between chips 
        and test the values of those chips when I was building the compute function. 

        The second thing that had me stumped was the destructor. I finished my code at the time and was at the end of my main function 
        when I remembered that I should build a destructor to delete memory and free space. Going into it, I wasn't sure what I would need 
        to delete. I was thinking along the lines of either both input chips, the output chip, or delete both input chips and output chip. 
        I wanted to be sure that I was thinking was correct and I approached Chat about it. I asked Chat, "for my program, what is the 
        difference between delete allChips[i] and delete[] allChips[i]?" Chat then replied in something quite interesting. Chat replied, saying 
        that the correct way to free memory from the program is to use delete allChips[i] since it would be freeing memory for single objects 
        (i.e. new int, and in our case, new Chip). I was still a bit confused about if this was the case and if I was calling delete allChips[i] 
        in the main program, what would my destructor look like? Empty? And I my guess was surprisingly right. Chat responded by saying that 
        nothing in Chip class was being dynamically defined, there was essentially no need for the destructor. I felt wary about this at first and 
        asked Chat to explain why it wasn't necessary. Chat explained to me that since there we no dynamically made chips in Chip class, there was 
        no need for a destructor, and if there were dynamically defined chips, the destructor would have delete input1 and delete input2 as the 
        only things needed in the destructor. Although we may not need to delete anything from inside the Chip class, we still need to manually 
        delete allChips and oChip from inside the main function. This played with my head for a while and I am really trying to think about why 
        this is done the way it is. 

    Debugging and Testing:
        The tests done with this program were provided in the canvas page of project2. input1.txt, input2.txt, and input3.txt. Some issues that I had 
        came from the compute function. The issue was that the input chips would try to grab input values from their input chips. I fixed that by 
        recursion only up to the chips where both input chips were 'I' chips. The reason for doing this is because eventually, at least one chip will 
        have to have both inputs chips being 'I' chips. Once that (or those) chips were found, then take the input value of the 'I' chips and execute 
        the desired operation of the chip. After the execution of the chip has been done, the value produced will be placed in the chips input value 
        and the process repeats again through recursion until the 'O' chip has the final value, which it then outputs the value into the terminal.

        Another issue that had occured was in the display function. At the time, I had displayed the input chips of 'A' chips, 'S' chips, 'M' chips, 
        etc perfectly fine. It was when I got to the 'N' chip that it started to cause issues. The reason why it caused isses was that the 'N' chip has 
        only one input. Meaning that input2 of the 'N' chip was a nullptr. The display function was trying to output a nullptr and was not liking it 
        very much. I solved that by checking whether the chip had one or two input chips, and depending on that knowledge, there would be a set path 
        for it to follow. 

        The verification of the program came in the canvas page of project2. The output text files was used to compare the output of the program and 
        correct answers of the corresponding input text files. 
*/