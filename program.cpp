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

//clasa abstracta pentru Step
class Step {
private:
    string stepType;
    int errorCount;
    int skippedCount;
    int completedCount;

public:
    Step(const string& type) : stepType(type), errorCount(0), skippedCount(0), completedCount(0) {}

    virtual void execute() = 0;
    virtual void print() const = 0;

    void incrementErrorCount() { errorCount++; } 
    void incrementSkippedCount() { skippedCount++; }
    void incrementCompletedCount() { completedCount++; } 
    void displayErrors() const { cout << "Errors: " << errorCount << endl; } 
    void displaySkippedCount() const { cout << "Skipped: " << skippedCount << endl; } 
    void displayCompletedCount() const { cout << "Completed: " << completedCount << endl; }


    int getErrorCount() const { return errorCount; }
    int getSkippedCount() const { return skippedCount; }
    int getCompletedCount() const { return completedCount; }

    const string& getStepType() const { return stepType; }
    void setStepType(const string& type) { stepType = type; }
    void setErrorCount(int count) { errorCount = count; }
    void setSkippedCount(int count) { skippedCount = count; }
    void setCompletedCount(int count) { completedCount = count; }

    //destructor
    virtual ~Step() {}
};

//clasa pentru TitleStep
class TitleStep : public Step {
private:
    string title;
    string subtitle;

public:
    TitleStep(const string& titleValue, const string& subtitleValue)
        : Step("TITLE"), title(titleValue), subtitle(subtitleValue) {}

    void execute() override {
        cout << "Step Type: " << getStepType() << endl;
        cout << "   Title: " << title << endl;
        cout << "   Subtitle: " << subtitle << endl;
        cout << "------------------------------------" << endl;
    }
    void print() const override {
        cout << "Step Type: " << getStepType() << endl;
        cout << "   Title: " << title << endl;
        cout << "   Subtitle: " << subtitle << endl;
        cout << "------------------------------------" << endl;
    }

    const string& getTitle() const { return title; }
    const string& getSubtitle() const { return subtitle; }
    void setTitle(const string& titleValue) { title = titleValue; }
    void setSubtitle(const string& subtitleValue) { subtitle = subtitleValue; }
};
//clasa pentru TextStep
class TextStep : public Step {
private:
    string title;
    string copy;

public:
    TextStep(const string& titleValue, const string& copyValue)
        : Step("TEXT"), title(titleValue), copy(copyValue) {}
    void execute() override {
        cout << "Step Type: " << getStepType() << endl;
        cout << "   Title: " << title << endl;
        cout << "   Copy: " << copy << endl;
        cout << "------------------------------------" << endl;
    }
    void print() const override {
        cout << "Step Type: " << getStepType() << endl;
        cout << "   Title: " << title << endl;
        cout << "   Copy: " << copy << endl;
        cout << "------------------------------------" << endl;
    }

    const string& getTitle() const { return title; }
    const string& getCopy() const { return copy; }
    void setTitle(const string& titleValue) { title = titleValue; }
    void setCopy(const string& copyValue) { copy = copyValue; }
};

//clasa pentru TextInputStep
class TextInputStep : public Step {
private:
    string description;
    string userInput;

public:
    TextInputStep(const string& descriptionValue)
        : Step("TEXT_INPUT"), description(descriptionValue) {}

    void execute() override {
        try {
            cout << "Step Type: " << getStepType() << endl;
            cout << "   Description: " << description << endl;
            cout << "   Enter text: ";
            cin.ignore();
            string input;
            getline(cin, input);
            setUserInput(input);
            cout << "   User Input: " << getUserInput() << endl;
            cout << "------------------------------------" << endl;
        } catch (const exception& e) {
            incrementErrorCount();
            cerr << "Error: " << e.what() << endl;
        }
    }

    void print() const override {
        cout << "Step Type: " << getStepType() << endl;
        cout << "   Description: " << description << endl;
        cout << "   User Input: " << getUserInput() << endl;
        cout << "------------------------------------" << endl;
    }

    const string& getDescription() const { return description; }
    const string& getUserInput() const { return userInput; }
    void setDescription(const string& descriptionValue) { description = descriptionValue; }
    void setUserInput(const string& userInputValue) { userInput = userInputValue; }
};
//clasa pentru NumberInputStep
class NumberInputStep : public Step {
private:
    string description;
    double userInput;

public:
    void execute() override {
        try {
            cout << "Step Type: " << getStepType() << endl;
            cout << "   Description: " << description << endl;
            cout << "   Enter a number: ";
            double input;
            cin >> input;
            setUserInput(input);
            cout << "   User Input: " << getUserInput() << endl;
            cout << "------------------------------------" << endl;
        } catch (const exception& e) {
            if(e.what() == string("basic_ios::clear")) {
                cerr << "Error: Invalid input." << endl;
            } else {
                cerr << "Error: " << e.what() << endl;
            }
            incrementErrorCount();
        }
    }

    void print() const override {
        cout << "Step Type: " << getStepType() << endl;
        cout << "   Description: " <<description << endl;
        cout << "   User Input: " << userInput << endl;
        cout << "------------------------------------" << endl;
    }

    NumberInputStep(const string& descriptionValue) : Step("NUMBER_INPUT"), description(descriptionValue) {}
    const string& getDescription() const { return description; }
    double getUserInput() const { return userInput; }
    void setDescription(const string& descriptionValue) { description = descriptionValue; }
    void setUserInput(double userInputValue) { userInput = userInputValue; }
    
};
//clasa pentru CalculusStep
class CalculusStep : public Step {
private:
    const NumberInputStep& operand1;
    const NumberInputStep& operand2;
    string operation;
    double result;

public:
    CalculusStep(const NumberInputStep& operand1Value,const NumberInputStep& operand2Value, const string& operationValue)
        : Step("CALCULUS"), operand1(operand1Value), operand2(operand2Value), operation(operationValue) {}

    void execute() override {
        try {
            cout << "Step Type: " << getStepType() << endl;
            cout << "   Operation: " << operand1.getUserInput() << " " << operation << " " << operand2.getUserInput() << endl;
            double r;
            //selectarea operatiei
            if (operation == "+") {
                r = operand1.getUserInput() + operand2.getUserInput();
            } else if (operation == "-") {
                r = operand1.getUserInput() - operand2.getUserInput();
            } else if (operation == "*") {
                r = operand1.getUserInput() * operand2.getUserInput();
            } else if (operation == "/") {
                //caz de exceptie pentru impartirea la 0
                if (operand2.getUserInput() != 0) {
                    r = operand1.getUserInput() / operand2.getUserInput();
                } else {
                    throw runtime_error("Division by zero.");
                }
            } else if (operation == "min") {
                r = min(operand1.getUserInput(), operand2.getUserInput());
            } else if (operation == "max") {
                r = max(operand1.getUserInput(), operand2.getUserInput());
            } else {
                throw invalid_argument("Invalid operation.");
            }
            result = r;
            cout << "   Result: " << result << endl;
            cout << "------------------------------------" << endl;
        } catch (const exception& e) {
            if(e.what() == "basic_ios::clear") {
                cerr << "Error: Invalid input." << endl;
            } else {
                cerr << "Error: " << e.what() << endl;
            }
            incrementErrorCount();
        }
    }

    void print() const override {
        cout << "Step Type: " << getStepType() << endl;
        cout << "   Operation: " << operand1.getUserInput() << " " << operation << " " << operand2.getUserInput() << endl;
        cout << "   Result: " << result << endl;
        cout << "------------------------------------" << endl;
    }
    const NumberInputStep& getOperand1() const { return operand1; }
    const NumberInputStep& getOperand2() const { return operand2; }
    const string& getOperation() const { return operation; }
    double getResult() const { return result; }
    void setOperation(const string& operationValue) { operation = operationValue; }
    void setResult(double resultValue) { result = resultValue; }
};

//clasa pentru TextFileInputStep
class TextFileInputStep : public Step {
private:
    string description;
    string fileName;
    string fileContent;

public:
    TextFileInputStep(const string& descriptionValue, const string& fileNameValue)
        : Step("TEXT_FILE_INPUT"), description(descriptionValue), fileName(fileNameValue) {
        readFileContent();
    }

    void execute() override {
        try {
            cout << "Step Type: " << getStepType() << endl;
            cout << "   Description: " << description << endl;
            cout << "   File Name: " << fileName << endl;
            cout << "   File Content: " << fileContent << endl;
            cout << "------------------------------------" << endl;
        } catch (const exception& e) {
            if(e.what() == "basic_ios::clear") {
                cerr << "Error: Invalid input." << endl;
            } else {
                cerr << "Error: " << e.what() << endl;
            }
            incrementErrorCount();
        }
    }

    void print() const override {
        cout << "Step Type: " << getStepType() << endl;
        cout << "   Description: " << description << endl;
        cout << "   File Name: " << fileName << endl;
        cout << "   File Content: " << fileContent << endl;
        cout << "------------------------------------" << endl;
    }

    const string& getDescription() const { return description; }
    const string& getFileName() const { return fileName; }
    const string& getFileContent() const { return fileContent; }
    void setDescription(const string& descriptionValue) { description = descriptionValue; }
    void setFileName(const string& fileNameValue) { fileName = fileNameValue; }
    void setFileContent(const string& fileContentValue) { fileContent = fileContentValue; }

private:
    // Metoda pentru citirea continutului fisierului
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
            if(e.what() == "basic_ios::clear") {
                cerr << "Error: Invalid input." << endl;
            } else {
                cerr << "Error: " << e.what() << endl;
            }
            incrementErrorCount();
        }
    }
};

//clasa pentru CsvFileInputStep
class CsvFileInputStep : public Step {
private:
    string description;
    string fileName;
    string fileContent;

public:
    CsvFileInputStep(const string& descriptionValue, const string& fileNameValue)
        : Step("CSV_FILE_INPUT"), description(descriptionValue), fileName(fileNameValue) {
        readFileContent();
    }

    void execute() override {
        try {
            cout << "Step Type: " << getStepType() << endl;
            cout << "   Description: " << description << endl;
            cout << "   File Name: " << fileName << endl;
            cout << "   File Content: " << fileContent << endl;
            cout << "------------------------------------" << endl;
        } catch (const exception& e) {
            if(e.what() == "basic_ios::clear") {
                cerr << "Error: Invalid input." << endl;
            } else {
                cerr << "Error: " << e.what() << endl;
            }
            incrementErrorCount();
        }
    }

    void print() const override {
        cout << "Step Type: " << getStepType() << endl;
        cout << "   Description: " << description << endl;
        cout << "   File Name: " << fileName << endl;
        cout << "   File Content: " << fileContent << endl;
        cout << "------------------------------------" << endl;
    }

    const string& getDescription() const { return description; }
    const string& getFileName() const { return fileName; }
    const string& getFileContent() const { return fileContent; }
    void setDescription(const string& descriptionValue) { description = descriptionValue; }
    void setFileName(const string& fileNameValue) { fileName = fileNameValue; }
    void setFileContent(const string& fileContentValue) { fileContent = fileContentValue; }

private:
    // Metoda pentru citirea continutului fisierului csv
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
            if(e.what() == "basic_ios::clear") {
                cerr << "Error: Invalid input." << endl;
            } else {
                cerr << "Error: " << e.what() << endl;
            }
            incrementErrorCount();
        }
    }
};
//clasa pentru DisplayStep
class DisplayStep : public Step {
        public:
            const Step& sourceStep;

            DisplayStep(const Step& sourceStepValue)
                : Step("DISPLAY"), sourceStep(sourceStepValue) {}

            void execute() override {
                try {
                    cout << "Step Type: " << getStepType() << endl;
                    cout << "   Displaying content of the previous step:" << endl;
                    const_cast<Step&>(sourceStep).execute();
                    cout << "------------------------------------" << endl;
                } catch (const exception& e) {
                   if(e.what() == "basic_ios::clear") {
                        cerr << "Error: Invalid input." << endl;
                    } else {
                         cerr << "Error: " << e.what() << endl;
                     }
                    incrementErrorCount();
                }
            }
            void print () const override {
                return;
            }
};
//clasa pentru OutputStep
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

            void execute() override {
                try {
                    cout << "Step Type: " << getStepType()<< endl;
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
                   if(e.what() == "basic_ios::clear") {
                        cerr << "Error: Invalid input." << endl;
                    } else {
                        cerr << "Error: " << e.what() << endl;
                    }
                    incrementErrorCount();
                    }
            }
            void print () const override {
                return;
            }

        };

//clasa pentru EndStep
class EndStep : public Step {
public:
    EndStep() : Step("END") {}

    void execute() override {
        cout << "Step Type: " << getStepType()<< endl;
        cout << "   End of the flow." << endl;
        cout << "------------------------------------" << endl;
    }
    bool handleUserInput() { return false; }
};

class Flow {
public:
    string name;
    vector<Step*> steps;

    // Variabilele pentru analytics
    int startedCount;
    int completedCount;
    int skippedCount;
    int errorCount;

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
        startedCount++;

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
            // Verificam daca vrea sa sara peste pas sau sa il execute
            cout << "Step: " << step->getStepType() << endl;
            cout << "Do you want to skip to the next step? (yes(1)/no(0)): ";
            int decision;
            cin >> decision;
            if (decision == 1) {
                cout << "Skipping the current step." << endl;
                step->incrementSkippedCount();
                skippedCount++;
                continue;
            }
            if (decision == 0) {
                step->execute();
                step->incrementCompletedCount();
            }
        }

        completedCount++; // Incrementam numarul de flow-uri completate
        cout << "Flow completed." << endl;
    }

    //Metoda pentru afisarea datelor
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
        for (const auto& step : steps) {
            cout << "Step: " << step->getStepType() << endl;
            step->displayErrors();
            step->displaySkippedCount();
            step->displayCompletedCount();
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


    void createFlow() {
        string flowName;
        cout << "Enter the name of the new flow: ";
        cin >> flowName;
        Flow* newFlow = new Flow(flowName);
        flows.push_back(newFlow);
        cout << "Flow '" << flowName << "' created successfully." << endl;
        addStepsToFlow(newFlow);
    }


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
            flows[choice - 1]->displayAnalytics();
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
    // Metode pentru adaugarea pasilor in flow
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
    void addNumberInputStep(Flow* flow) {
        string description;
        cout << "Enter the description for the Number Input Step: ";
        cin.ignore();
        getline(cin, description);
        flow->addStep(new NumberInputStep(description));
        cout << "Number Input Step added successfully." << endl;
    }
    
    void addCalculusStep(Flow* flow) {
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

    void displayAllSteps(const Flow* flow) {
        for (size_t i = 0; i < flow->steps.size(); ++i) {
            cout << i + 1 << ". ";
            cout << "Step Type: " << flow->steps[i]->getStepType()<< endl;
        }
    }

    void displayNumberInputSteps(const Flow* flow) {
        for (size_t i = 0; i < flow->steps.size(); ++i) {
            if (dynamic_cast<const NumberInputStep*>(flow->steps[i]) != nullptr) {
                cout << i + 1 << ". ";
                cout << dynamic_cast<const NumberInputStep*>(flow->steps[i])->getDescription() << endl;
            }
        }
    }

    int getUserChoice(const string& prompt, int maxChoice) {
        int choice;
        do {
            cout << prompt;
            cin >> choice;
        } while (choice < 1 || choice > maxChoice);
        return choice;
    }
};

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