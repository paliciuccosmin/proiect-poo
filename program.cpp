#include <iostream>
#include <vector>
#include <ctime>
#include <string.h>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <stdexcept>
#include <exception>
#include <cmath>
#include <istream>

using namespace std;

class Step {
public:
    string stepType;
    int errorCount;
    Step(const string& type) : stepType(type), errorCount(0) {}

    virtual void execute() const = 0;
    virtual ~Step() {}
    virtual bool handleUserInput() { return false; }
    virtual void print() const = 0;
    void incrementErrorCount() { errorCount++; } // Increment error count
    void displayErrors() const { cout << "Errors: " << errorCount << endl; } // Display error count
};

class TitleStep : public Step {
public:
    string title;
    string subtitle;

    TitleStep(const string& titleValue, const string& subtitleValue)
        : Step("TITLE"), title(titleValue), subtitle(subtitleValue) {}

    void execute() const override {
        cout << "Step Type: " << stepType << endl;
        cout << "   Title: " << title << endl;
        cout << "   Subtitle: " << subtitle << endl;
        cout << "------------------------------------" << endl;
    }
    bool handleUserInput() override {
        string decision;
        cout << "Do you want to proceed to the next step? (yes/no): ";
        cin >> decision;

        if (decision != "yes" || decision !="Y" || decision !="y" || decision !="YES" ) {
            cout << "Skipping the current step." << endl;
            return true;
        }
        return false;
    }
    void print() const override {
        cout << "Step Type: " << stepType << endl;
        cout << "   Title: " << title << endl;
        cout << "   Subtitle: " << subtitle << endl;
        cout << "------------------------------------" << endl;
    }
};

class TextStep : public Step {
public:
    string title;
    string copy;

    TextStep(const string& titleValue, const string& copyValue)
        : Step("TEXT"), title(titleValue), copy(copyValue) {}

    void execute() const override {
        cout << "Step Type: " << stepType << endl;
        cout << "   Title: " << title << endl;
        cout << "   Copy: " << copy << endl;
        cout << "------------------------------------" << endl;
    }
    bool handleUserInput() override {
        string decision;
        cout << "Do you want to proceed to the next step? (yes/no): ";
        cin >> decision;

        if (decision != "yes" || decision !="Y" || decision !="y" || decision !="YES" ) {
            cout << "Skipping the current step." << endl;
            return true;
        }
        return false;
    }
    void print() const override {
        cout << "Step Type: " << stepType << endl;
        cout << "   Title: " << title << endl;
        cout << "   Copy: " << copy << endl;
        cout << "------------------------------------" << endl;
    }

};
class TextInputStep : public Step {
    public:
    string description;
    string userInput;

    TextInputStep(const string& descriptionValue)
    : Step("TEXT_INPUT"), description(descriptionValue) {}

    void execute() const override {
        try {
            cout << "Step Type: " << stepType << endl;
            cout << "   Description: " << description << endl;
            cout << "   Enter text: ";
            cin.ignore();
            string input;
            getline(cin,input);
            const_cast<string&>(userInput) = input;
            cout << "   User Input: " << userInput << endl;
            cout << "------------------------------------" << endl;
        } catch (const exception& e) {
            cerr << "Error: " << e.what() << endl;
        }
    }
    bool handleUserInput() override {
        string decision;
        cout << "Do you want to proceed to the next step? (yes/no): ";
        cin >> decision;

        if (decision != "yes" || decision !="Y" || decision !="y" || decision !="YES" ) {
            cout << "Skipping the current step." << endl;
            return true;
            }
        return false;
}
    void print () const override {
        cout << "Step Type: " << stepType << endl;
        cout << "   Description: " << description << endl;
        cout << "   User Input: " << userInput << endl;
        cout << "------------------------------------" << endl;
    }
};

class NumberInputStep : public Step {
    public:
    string description;
    double userInput;

    NumberInputStep(const string& descriptionValue): Step("NUMBER_INPUT"), description(descriptionValue) {}
    void execute() const override {
        try {
            cout << "Step Type: " << stepType << endl;
            cout << "   Description: " << description << endl;
            cout << "   Enter a number: ";
            double input;
            cin >> input;
            const_cast<double&>(userInput) = input;
            cout << "   User Input: " << userInput << endl;
            cout << "------------------------------------" << endl;
            } catch (const exception& e) {
                cerr << "Error: " << e.what() << endl;
            }
    }
    bool handleUserInput() override {
        string decision;
        cout << "Do you want to proceed to the next step? (yes/no): ";
        cin >> decision;

        if (decision != "yes" || decision !="Y" || decision !="y" || decision !="YES" ) {
            cout << "Skipping the current step." << endl;
            return true;
        }
        return false;
}
    void print () const override {
        cout << "Step Type: " << stepType << endl;
        cout << "   Description: " << description << endl;
        cout << "   User Input: " << userInput << endl;
        cout << "------------------------------------" << endl;
    }
};

class CalculusStep : public Step {
public:
    const NumberInputStep& operand1;
    const NumberInputStep& operand2;
    string operation;
    double result;
    CalculusStep(const NumberInputStep& operand1Value, const NumberInputStep& operand2Value, const string& operationValue)
    : Step("CALCULUS"), operand1(operand1Value), operand2(operand2Value), operation(operationValue) {}

    void execute() const override {
    try {
        cout << "Step Type: " << stepType << endl;
        cout << "   Operation: " << operand1.userInput << " " << operation << " " << operand2.userInput << endl;
        double r;
        if (operation == "+") {
            r = operand1.userInput + operand2.userInput;
        } else if (operation == "-") {
            r = operand1.userInput - operand2.userInput;
        } else if (operation == "*") {
            r = operand1.userInput * operand2.userInput;
        } else if (operation == "/") {
        if (operand2.userInput != 0) {
            r = operand1.userInput / operand2.userInput;
        } else {
            throw runtime_error("Division by zero.");
        }
            } else if (operation == "min") {
        r = min(operand1.userInput, operand2.userInput);
            } else if (operation == "max") {
        r = max(operand1.userInput, operand2.userInput);
            } else {
        throw invalid_argument("Invalid operation.");
            }
        const_cast<double&>(result) = r;
        cout << "   Result: " << result << endl;
        cout << "------------------------------------" << endl;
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }
        }
        bool handleUserInput() override {
    string decision;
    cout << "Do you want to proceed to the next step? (yes/no): ";
    cin >> decision;

    if (decision != "yes" || decision !="Y" || decision !="y" || decision !="YES" ) {
        cout << "Skipping the current step." << endl;
        return true;
    }
    return false;
        }
    void print () const override {
        cout << "Step Type: " << stepType << endl;
        cout << "   Operation: " << operand1.userInput << " " << operation << " " << operand2.userInput << endl;
        cout << "   Result: " << result << endl;
        cout << "------------------------------------" << endl;
    }
};

class TextFileInputStep : public Step {
    public:
        string description;
        string fileName;
        string fileContent;

        TextFileInputStep(const string& descriptionValue, const string& fileNameValue)
    : Step("TEXT_FILE_INPUT"), description(descriptionValue), fileName(fileNameValue) {readFileContent();}

        void execute() const override {
            try {
                cout << "Step Type: " << stepType << endl;
                cout << "   Description: " << description << endl;
                cout << "   File Name: " << fileName << endl;
                cout << "   File Content: " << fileContent << endl;
                cout << "------------------------------------" << endl;
            } catch (const exception& e) {
            cerr << "Error: " << e.what() << endl;
            }
        }

        bool handleUserInput() override {
            string decision;
            cout << "Do you want to proceed to the next step? (yes/no): ";
            cin >> decision;

            if (decision != "yes" || decision !="Y" || decision !="y" || decision !="YES" ) {
                cout << "Skipping the current step." << endl;
                return true;
            }
            return false;
        }
    void print () const override {
        cout << "Step Type: " << stepType << endl;
        cout << "   Description: " << description << endl;
        cout << "   File Name: " << fileName << endl;
        cout << "   File Content: " << fileContent << endl;
        cout << "------------------------------------" << endl;
    }

    private:
        void readFileContent() {
            try {
                ifstream fileStream(fileName);
                if (fileStream.is_open()) {
            string line;
            while (getline(fileStream, line)) {
                fileContent += line + "\n";
            }
            fileStream.close();
                } else {
            throw runtime_error("Unable to open file - " + fileName);
                }
            } catch (const exception& e) {
                cerr << "Error: " << e.what() << endl;
            }
        }
    
    };


class CsvFileInputStep : public Step {
public:
    string description;
    string fileName;
    string fileContent;

    CsvFileInputStep(const string& descriptionValue, const string& fileNameValue)
        : Step("CSV_FILE_INPUT"), description(descriptionValue), fileName(fileNameValue) {
                readFileContent();
            }

            void execute() const override {
                try {
                    cout << "Step Type: " << stepType << endl;
                    cout << "   Description: " << description << endl;
                    cout << "   File Name: " << fileName << endl;
                    cout << "   File Content: " << fileContent << endl;
                    cout << "------------------------------------" << endl;
                } catch (const exception& e) {
                    cerr << "Error: " << e.what() << endl;
                }
            }

            bool handleUserInput() override {
                string decision;
                cout << "Do you want to proceed to the next step? (yes/no): ";
                cin >> decision;

                if (decision != "yes" || decision !="Y" || decision !="y" || decision !="YES" ) {
                    cout << "Skipping the current step." << endl;
                    return true;
                }
                return false;
            }
        void print () const override {
        cout << "Step Type: " << stepType << endl;
        cout << "   Description: " << description << endl;
        cout << "   File Name: " << fileName << endl;
        cout << "   File Content: " << fileContent << endl;
        cout << "------------------------------------" << endl;
        }

        private:
            void readFileContent() {
                try {
                    ifstream fileStream(fileName);
                    if (fileStream.is_open()) {
                        string line;
                        while (getline(fileStream, line)) {
                            fileContent += line + "\n";
                        }
                        fileStream.close();
                    } else {
                        throw runtime_error("Unable to open file - " + fileName);
                    }
                } catch (const exception& e) {
                    cerr << "Error: " << e.what() << endl;
                }
            }
        };

class DisplayStep : public Step {
        public:
            const Step& sourceStep;

            DisplayStep(const Step& sourceStepValue)
                : Step("DISPLAY"), sourceStep(sourceStepValue) {}

            void execute() const override {
                try {
                    cout << "Step Type: " << stepType << endl;
                    cout << "   Displaying content of the previous step:" << endl;
                    sourceStep.execute();
                    cout << "------------------------------------" << endl;
                } catch (const exception& e) {
                    cerr << "Error: " << e.what() << endl;
                }
            }
            bool handleUserInput() override {
                string decision;
                cout << "Do you want to proceed to the next step? (yes/no): ";
                cin >> decision;

                if (decision != "yes" || decision !="Y" || decision !="y" || decision !="YES" ) {
                    cout << "Skipping the current step." << endl;
                    return true;
                }
                return false;
            }
            void print () const override {
                return;
            }
};

class OutputStep : public Step {
        public:
            int stepNumber;
            string fileName;
            string title;
            string description;
            const Step& sourceStep;

            OutputStep(int stepNumberValue, const string& fileNameValue, const string& titleValue,
                       const string& descriptionValue, const Step& sourceStepValue)
                : Step("OUTPUT"), stepNumber(stepNumberValue), fileName(fileNameValue),
                  title(titleValue), description(descriptionValue), sourceStep(sourceStepValue) {}

            void execute() const override {
                try {
                    cout << "Step Type: " << stepType << endl;
                    cout << "   Step Number: " << stepNumber << endl;
                    cout << "   File Name: " << fileName << endl;
                    cout << "   Title: " << title << endl;
                    cout << "   Description: " << description << endl;

                    string sourceStepInfo;
                    sourceStepInfo += "Source Step Information:\n";

                    ostringstream oss;
                    streambuf* coutBuffer = cout.rdbuf();
                    cout.rdbuf(oss.rdbuf());

                    sourceStep.print();

                    cout.rdbuf(coutBuffer);

                    sourceStepInfo += oss.str();
                    sourceStepInfo += "------------------------------------\n";

                    ofstream outputFile(fileName, ios::app); 
                    if (outputFile.is_open()) {
                        outputFile << "Output Step Information:\n";
                        outputFile << "   Step Number: " << stepNumber << "\n";
                        outputFile << "   File Name: " << fileName << "\n";
                        outputFile << "   Title: " << title << "\n";
                        outputFile << "   Description: " << description << "\n\n";
                        outputFile << sourceStepInfo;
                        outputFile.close();
                        cout << "   Output file generated successfully." << endl;
                    } else {
                        throw runtime_error("Unable to open output file - " + fileName);
                    }

                    cout << "------------------------------------" << endl;
                } catch (const exception& e) {
                    cerr << "Error: " << e.what() << endl;
                }
            }
            bool handleUserInput() override {
                string decision;
                cout << "Do you want to proceed to the next step? (yes/no): ";
                cin >> decision;

                if (decision != "yes" || decision !="Y" || decision !="y" || decision !="YES" ) {
                    cout << "Skipping the current step." << endl;
                    return true;
                }
                return false;
            }
            void print () const override {
                return;
            }

        };

class EndStep : public Step {
public:
    EndStep() : Step("END") {}

    void execute() const override {
        cout << "Step Type: " << stepType << endl;
        cout << "   End of the flow." << endl;
        cout << "------------------------------------" << endl;
    }
    bool handleUserInput() { return false; }
};

class Flow {
public:
    string name;
    vector<Step*> steps;

    // Analytics counters
    int startedCount;
    int completedCount;
    int skippedCount;
    int errorCount;

    // Function to increment the error count

    Flow(const string& flowName)
        : name(flowName), startedCount(0), completedCount(0), skippedCount(0), errorCount(0) {}

    ~Flow() {
        for (auto step : steps) {
            delete step;
        }
    }

    void addStep(Step* step) {
        steps.push_back(step);
    }

    void run() {
        startedCount++; // Increment the flow started count

        tm timestamp;
        time_t now = time(0);
        timestamp = *localtime(&now);

        cout << "Flow Name: " << name << endl;
        cout << "Timestamp: "
                  << timestamp.tm_year + 1900 << '-'
                  << timestamp.tm_mon + 1 << '-'
                  << timestamp.tm_mday << ' '
                  << timestamp.tm_hour << ':'
                  << timestamp.tm_min << ':'
                  << timestamp.tm_sec << endl;
        cout << "------------------------------------" << endl;

        for (auto& step : steps) {
            step->execute();

            // Allow the user to handle the current step's input
            bool inputHandled = step->handleUserInput();

            // Optionally, add logic to check whether to proceed to the next step or skip
            if (inputHandled) {
                string decision;
                cout << "Do you want to proceed to the next step? (yes/no): ";
                cin >> decision;

                if (decision != "yes" || decision !="Y" || decision !="y" || decision !="YES" ) {
                    cout << "Skipping the current step." << endl;
                    skippedCount++; // Increment the skipped count
                    continue; // Skip to the next iteration of the loop
                }
            }
        }

        completedCount++; // Increment the flow completed count
        cout << "Flow completed." << endl;
    }

    // Analytics methods
    void displayAnalytics() const {
        cout << "Analytics for Flow: " << name << endl;
        cout << "Started count: " << startedCount << endl;
        cout << "Completed count: " << completedCount << endl;
        cout << "Skipped count: " << skippedCount << endl;
        cout << "Error count: " << errorCount << endl;

        if (completedCount > 0) {
            double averageErrors = static_cast<double>(errorCount) / completedCount;
            cout << "Average errors per completed flow: " << averageErrors << endl;
        } else {
            cout << "Average errors per completed flow: N/A (no completed flows)" << endl;
        }
    }
};

class FlowManager {
public:
    vector<Flow*> flows;

    FlowManager() {}

    ~FlowManager() {
        for (auto flow : flows) {
            delete flow;
        }
    }

    // Create a new flow
    void createFlow() {
        string flowName;
        cout << "Enter the name of the new flow: ";
        cin >> flowName;
        Flow* newFlow = new Flow(flowName);
        flows.push_back(newFlow);
        cout << "Flow '" << flowName << "' created successfully." << endl;
        addStepsToFlow(newFlow);
    }

    // Delete an existing flow
    void deleteFlow() {
        string flowName;
        cout << "Enter the name of the flow to delete: ";
        cin >> flowName;

        auto it = find_if(flows.begin(), flows.end(), [&flowName](const Flow* flow) {
            return flow->name == flowName;
        });

        if (it != flows.end()) {
            delete *it;
            flows.erase(it);
            cout << "Flow '" << flowName << "' deleted successfully." << endl;
        } else {
            cout << "Flow '" << flowName << "' not found." << endl;
        }
    }

    // Run a selected flow
    void runFlow() {
        if (flows.empty()) {
            cout << "No flows available. Create a flow first." << endl;
            return;
        }

        cout << "Select a flow to run:" << endl;
        for (size_t i = 0; i < flows.size(); ++i) {
            cout << i + 1 << ". " << flows[i]->name << endl;
        }

        int choice;
        cout << "Enter the number of the flow to run (0 to cancel): ";
        cin >> choice;

        if (choice > 0 && static_cast<size_t>(choice) <= flows.size()) {
            flows[choice - 1]->run();
        } else {
            cout << "Invalid choice or canceled." << endl;
        }
    }
      void addStepsToFlow(Flow* flow) {
        while (true) {
            cout << "Add steps to flow '" << flow->name << "':" << endl;
            cout << "1. Add Title Step" << endl;
            cout << "2. Add Text Step" << endl;
            cout << "3. Add Text File Input Step" << endl;
            cout << "4. Add CSV File Input Step" << endl;
            cout << "5. Add Number Input Step" << endl;
            cout << "6. Add Text Input Step" << endl;
            cout << "7. Add Calculus Step" << endl;
            cout << "8. Add Display Step" << endl;
            cout << "9. Add Output Step" << endl;
            cout << "0. Add End Step" << endl;
            int choice;
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    addTitleStep(flow);
                    break;
                case 2:
                    addTextStep(flow);
                    break;
                case 3: 
                    addTextFileInputStep(flow);
                    break;
                case 4:
                    addCsvFileInputStep(flow);
                    break;
                case 5: 
                    addNumberInputStep(flow);
                    break;
                case 6:
                    addTextInputStep(flow);
                    break;
                case 7: 
                    addCalculusStep(flow);
                    break;
                case 8: 
                    addDisplayStep(flow);
                    break;
                case 9: 
                    addOutputStep(flow);
                    break;
                case 0:
                    cout << "Finished adding steps to flow '" << flow->name << "'." << endl;
                    return;
                default:
                    cout << "Invalid choice. Try again." << endl;
            }
        }
    }

private:
    void addTitleStep(Flow* flow) {
        string title, subtitle;
        cout << "Enter the title for the Title Step: ";
        cin.ignore();
        getline(cin, title);
        cout << "Enter the subtitle for the Title Step: ";
        getline(cin, subtitle);
        flow->addStep(new TitleStep(title, subtitle));
        cout << "Title Step added successfully." << endl;
    }
    void addTextStep(Flow* flow) {
        string title, copy;
        cout << "Enter the title for the Text Step: ";
        cin.ignore();
        getline(cin, title);
        cout << "Enter the copy for the Text Step: ";
        getline(cin, copy);
        flow->addStep(new TextStep(title, copy));
        cout << "Text Step added successfully." << endl;
    }
    void addTextInputStep(Flow* flow) {
        string description;
        cout << "Enter the description for the Text Input Step: ";
        cin.ignore();
        getline(cin, description);
        flow->addStep(new TextInputStep(description));
        cout << "Text Input Step added successfully." << endl;
    }
    void addTextFileInputStep(Flow* flow) {
        string description, fileName;
        cout << "Enter the description for the Text File Input Step: ";
        cin.ignore();
        getline(cin, description);
        cout << "Enter the file name for the Text File Input Step: ";
        getline(cin, fileName);
        flow->addStep(new TextFileInputStep(description, fileName));
        cout << "Text File Input Step added successfully." << endl;
    }
    void addCsvFileInputStep(Flow* flow) {
        string description, fileName;
        cout << "Enter the description for the CSV File Input Step: ";
        cin.ignore();
        getline(cin, description);
        cout << "Enter the file name for the CSV File Input Step: ";
        getline(cin, fileName);
        flow->addStep(new CsvFileInputStep(description, fileName));
        cout << "CSV File Input Step added successfully." << endl;
    }
    // Helper methods for adding specific steps
    void addNumberInputStep(Flow* flow) {
        string description;
        cout << "Enter the description for the Number Input Step: ";
        cin.ignore();
        getline(cin, description);
        flow->addStep(new NumberInputStep(description));
        cout << "Number Input Step added successfully." << endl;
    }
    
    void addCalculusStep(Flow* flow) {
        // You may need to modify this based on how you want to handle multiple Number Input Steps
        cout << "Select the first operand (Number Input Step):" << endl;
        displayNumberInputSteps(flow);
        int operand1Index = getUserChoice("Enter the index of the first operand: ", flow->steps.size());
        const NumberInputStep& operand1 = dynamic_cast<const NumberInputStep&>(*flow->steps[operand1Index - 1]);

        cout << "Select the second operand (Number Input Step):" << endl;
        displayNumberInputSteps(flow);
        int operand2Index = getUserChoice("Enter the index of the second operand: ", flow->steps.size());
        const NumberInputStep& operand2 = dynamic_cast<const NumberInputStep&>(*flow->steps[operand2Index - 1]);

        string operation;
        cout << "Enter the operation (+, -, *, /, min, max): ";
        cin >> operation;

        flow->addStep(new CalculusStep(operand1, operand2, operation));
        cout << "Calculus Step added successfully." << endl;
    }

    void addDisplayStep(Flow* flow) {
        cout << "Select the source step for Display Step:" << endl;
        displayAllSteps(flow);
        int sourceIndex = getUserChoice("Enter the index of the source step: ", flow->steps.size());
        const Step& sourceStep = *flow->steps[sourceIndex - 1];

        flow->addStep(new DisplayStep(sourceStep));
        cout << "Display Step added successfully." << endl;
    }

    void addOutputStep(Flow* flow) {
        // You may need to modify this based on how you want to handle multiple steps for output
        cout << "Select the source step for Output Step:" << endl;
        displayAllSteps(flow);
        int sourceIndex = getUserChoice("Enter the index of the source step: ", flow->steps.size());
        const Step& sourceStep = *flow->steps[sourceIndex - 1];

        string fileName, title, description;
        cout << "Enter the file name for the Output Step: ";
        cin >> fileName;
        cout << "Enter the title for the Output Step: ";
        cin.ignore();
        getline(cin, title);
        cout << "Enter the description for the Output Step: ";
        getline(cin, description);

        flow->addStep(new OutputStep(flow->steps.size() + 1, fileName, title, description, sourceStep));
        cout << "Output Step added successfully." << endl;
    }

    // Helper method to display all steps in the flow
    void displayAllSteps(const Flow* flow) {
        for (size_t i = 0; i < flow->steps.size(); ++i) {
            cout << i + 1 << ". ";
            cout << "Step Type: " << flow->steps[i]->stepType << endl;
        }
    }

    // Helper method to display only Number Input Steps
    void displayNumberInputSteps(const Flow* flow) {
        for (size_t i = 0; i < flow->steps.size(); ++i) {
            if (dynamic_cast<const NumberInputStep*>(flow->steps[i]) != nullptr) {
                cout << i + 1 << ". ";
                cout << dynamic_cast<const NumberInputStep*>(flow->steps[i])->description << endl;
            }
        }
    }

    // Helper method to get a valid user choice
    int getUserChoice(const string& prompt, int maxChoice) {
        int choice;
        do {
            cout << prompt;
            cin >> choice;
        } while (choice < 1 || choice > maxChoice);
        return choice;
    }
};

// Update your main function to use the FlowManager
int main() {
    FlowManager flowManager;

    while (true) {
        cout << "Menu:" << endl;
        cout << "1. Create a new flow" << endl;
        cout << "2. Delete a flow" << endl;
        cout << "3. Run a flow" << endl;
        cout << "0. Exit" << endl;

        int choice;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                flowManager.createFlow();
                break;
            case 2:
                flowManager.deleteFlow();
                break;
            case 3:
                flowManager.runFlow();
                break;
            case 0:
                cout << "Exiting program." << endl;
                return 0;
            default:
                cout << "Invalid choice. Try again." << endl;
        }
    }
};