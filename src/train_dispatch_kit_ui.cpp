#include <iostream>
#include <vector>
#include <stack>
#include <cctype>
#include "carriage.h"
#include "carriage_buffers.h"
#include "carriage_dispatcher.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;
using std::stack;
using XXYY::CarriageDipatcher;
using XXYY::Carriage;

class TrainDispatchKitUI {
  public:
    TrainDispatchKitUI() {
        quit  = false;
        queue_exist = false;
        StartScreen();
    }

    ~TrainDispatchKitUI() {
        cout << "Good Bye!" << endl;
    }

    void OperationLoop() {
        while (!quit) {
            cout << "Command << ";
            string cmd;
            cin >> cmd;
            ExecuteCommand(cmd);
        }
    }

    void StartScreen() {
        cout << "                      (@@) (  ) (@)  ( )  @@    ()  @" << endl;
        cout << "                 (   )" << endl;
        cout << "             (@@@@)" << endl;
        cout << "          (    )" << endl;
        cout << "" << endl;
        cout << "        (@@@)" << endl;
        cout << "      ====        ________                ___________" << endl;
        cout << "  _D _|  |_______/        \\__I_I_____===__|_________|" << endl;
        cout << "   |(_)---  |   H\\________/ |   |        =|___ ___|" << endl;
        cout << "   /     |  |   H  |  |     |   |         ||_| |_||" << endl;
        cout << "  |      |  |   H  |__--------------------| [___] |" << endl;
        cout << "  | ________|___H__/__|_____/[][]~\\_______|       |" << endl;
        cout << "  |/ |   |-----------I_____I [][] []  D   |=======|___" << endl;
        cout << "__/ =| o |=-~~\\  /~~\\  /~~\\  /~~\\ ____Y___________|__|" << endl;
        cout << " |/-=|___|=    ||    ||    ||    |_____/~\\___/" << endl;
        cout << "  \\_/      \\_O=====O=====O=====O/      \\_/" << endl;
        cout << "" << endl;
        cout << "" << endl;
        cout << "_/_/_/_/_/              _/_/_/                _/    _/" << endl;
        cout << "   _/                  _/    _/              _/  _/" << endl;
        cout << "  _/                  _/_/_/                _/_/" << endl;
        cout << " _/                  _/    _/              _/  _/" << endl;
        cout << "_/                  _/    _/              _/    _/" << endl;
        cout << "\n\n" << endl;
        cout << "------------------- Train Dispatch Kit -------------------" << endl;
        cout << "     new - create new carriage queue" << endl;
        cout << "     next - next step" << endl;
        cout << "     ctn - continue for some steps" << endl;
        cout << "     check - check a certain buffer and show its detail" << endl;
        cout << "     total - show total number of the buffer" << endl;
        cout << "     quit - quit trk" << endl;
        cout << "----------------------------------------------------------" << endl;
    }

    void ExecuteCommand(string cmd) {
        if (cmd == "next") { NextStep(); }
        else if (cmd == "ctn") { ContinueForSteps(); }
        else if (cmd == "check") { CheckBuffer(); }
        else if (cmd == "quit") { quit = true; }
        else if (cmd == "total") { GetBufferNum(); }
        else if (cmd == "new") { CreateQueue(); }
        else { cout << "ERROR: Command Not Found!" << endl; }
    }

    // Operation Function
    void CreateQueue() {
        cout << "Input a string as the queue." << endl;
        cout << "(non-digit character will be automatically removed.)" << endl;
        cout << "String << ";
        string queue;
        cin >> queue;
        vector<uint32_t> carriageQueue;
        for (char ch : queue) {
            if (isdigit(ch)) carriageQueue.push_back(ch - '0');
        }
        dispatcher.reset(new CarriageDipatcher(carriageQueue));
        queue_exist = true;
    }

    void GetBufferNum() {
        int BufferNum = dispatcher->buffers_size();
        cout << "Now " << BufferNum << " buffer(s) exist." << endl;
    }

    void ContinueForSteps() {
        if (!queue_exist) {
            cout << "ERROR: You do not have a queue yet." << endl;
            return;
        }
        cout << "Please enter the number of steps that you want to continue for." << endl;
        cout << "Number << ";
        uint32_t steps;
        cin >> steps;
        dispatcher->ContinueFor(steps);
    }

    void NextStep() {
        if (!queue_exist) {
            cout << "ERROR: You do not have a queue yet." << endl;
            return;
        }
        cout << "Calculating the next step...success!" << endl;
        dispatcher->NextStep();
    }

    void CheckBuffer() {
        if (!queue_exist) {
            cout << "ERROR: You do not have a queue yet." << endl;
            return;
        }
        cout << "Please enter the index of the buffer." << endl;
        cout <<  "Number << ";
        size_t index;
        cin >> index;
        auto buffer_ptr = dispatcher->Buffer(index);
        if (buffer_ptr == nullptr) {
            cout << "ERROR: The buffer doesn't exist." << endl;
        } else {
            // TODO: Convert to stack?
            cout << "Buffer " << index << " with carriages below: " << endl;
            for (Carriage carriage : *buffer_ptr) {
                cout << "Carriage " << carriage.index;
                cout << " with destination " << carriage.destination << endl;
            }
        }
    }
  private:
    bool quit;
    bool queue_exist;
    std::unique_ptr<CarriageDipatcher> dispatcher;
};