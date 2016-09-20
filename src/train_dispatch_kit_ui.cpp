#include "carriage.h"
#include "carriage_buffers.h"
#include "carriage_dispatcher.h"
#include <cctype>
#include <iostream>
#include <stack>
#include <vector>

using std::cout;
using std::cin;
using std::string;
using std::vector;
using std::stack;
using XXYY::CarriageDipatcher;
using XXYY::Carriage;

class TrainDispatchKitUI {
  public:
    TrainDispatchKitUI() {
        quit = false;
        queue_exist = false;
        StartScreen();
    }

    ~TrainDispatchKitUI() {
        cout << "Good Bye!" << '\n';
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
        cout << "                      (@@) (  ) (@)  ( )  @@    ()  @" << '\n';
        cout << "                 (   )" << '\n';
        cout << "             (@@@@)" << '\n';
        cout << "          (    )" << '\n';
        cout << "" << '\n';
        cout << "        (@@@)" << '\n';
        cout << "      ====        ________                ___________" << '\n';
        cout << "  _D _|  |_______/        \\__I_I_____===__|_________|"
             << '\n';
        cout << "   |(_)---  |   H\\________/ |   |        =|___ ___|" << '\n';
        cout << "   /     |  |   H  |  |     |   |         ||_| |_||" << '\n';
        cout << "  |      |  |   H  |__--------------------| [___] |" << '\n';
        cout << "  | ________|___H__/__|_____/[][]~\\_______|       |" << '\n';
        cout << "  |/ |   |-----------I_____I [][] []  D   |=======|___"
             << '\n';
        cout << "__/ =| o |=-~~\\  /~~\\  /~~\\  /~~\\ ____Y___________|__|"
             << '\n';
        cout << " |/-=|___|=    ||    ||    ||    |_____/~\\___/" << '\n';
        cout << "  \\_/      \\_O=====O=====O=====O/      \\_/" << '\n';
        cout << "" << '\n';
        cout << "" << '\n';
        cout << "_/_/_/_/_/              _/_/_/                _/    _/"
             << '\n';
        cout << "   _/                  _/    _/              _/  _/" << '\n';
        cout << "  _/                  _/_/_/                _/_/" << '\n';
        cout << " _/                  _/    _/              _/  _/" << '\n';
        cout << "_/                  _/    _/              _/    _/" << '\n';
        cout << "\n\n" << '\n';
        cout << "------------------- Train Dispatch Kit -------------------\n";
        cout << "     new - create new carriage queue\n";
        cout << "     next - next step\n";
        cout << "     ctn - continue for some steps\n";
        cout << "     check - check a certain buffer and show its detail\n";
        cout << "     total - show total number of the buffer\n";
        cout << "     quit - quit trk\n" << '\n';
        cout << "----------------------------------------------------------\n";
    }

    void ExecuteCommand(string cmd) {
        if (cmd == "next") {
            NextStep();
        } else if (cmd == "ctn") {
            ContinueForSteps();
        } else if (cmd == "check") {
            CheckBuffer();
        } else if (cmd == "quit") {
            quit = true;
        } else if (cmd == "total") {
            GetBufferNum();
        } else if (cmd == "new") {
            CreateQueue();
        } else {
            cout << "ERROR: Command Not Found!\n";
        }
    }

    // Operation Function
    void CreateQueue() {
        cout << "Input a string as the queue.\n";
        cout << "(non-digit character will be automatically removed.)\n";
        cout << "String << ";
        string queue;
        cin >> queue;
        vector<uint32_t> carriageQueue;
        for (char ch : queue) {
            if (isdigit(ch))
                carriageQueue.push_back(ch - '0');
        }
        dispatcher.reset(new CarriageDipatcher(carriageQueue));
        queue_exist = true;
    }

    void GetBufferNum() {
        int BufferNum = dispatcher->buffers_size();
        cout << "Now " << BufferNum << " buffer(s) exist.\n";
    }

    void ContinueForSteps() {
        if (!queue_exist) {
            cout << "ERROR: You do not have a queue yet.\n";
            return;
        }
        cout << "Please enter the number of steps that you want to continue "
                "for.\n";
        cout << "Number << ";
        uint32_t steps;
        cin >> steps;
        dispatcher->ContinueFor(steps);
    }

    void NextStep() {
        if (!queue_exist) {
            cout << "ERROR: You do not have a queue yet.\n";
            return;
        }
        cout << "Calculating the next step...success!\n";
        dispatcher->NextStep();
    }

    void CheckBuffer() {
        if (!queue_exist) {
            cout << "ERROR: You do not have a queue yet.\n";
            return;
        }
        cout << "Please enter the index of the buffer.\n";
        cout << "Number << ";
        size_t index;
        cin >> index;
        auto buffer_ptr = dispatcher->Buffer(index);
        if (buffer_ptr == nullptr) {
            cout << "ERROR: The buffer doesn't exist.\n";
        } else {
            // TODO: Convert to stack?
            cout << "Buffer " << index << " with carriages below:\n";
            for (Carriage carriage : *buffer_ptr) {
                cout << "Carriage " << carriage.index;
                cout << " with destination " << carriage.destination << '\n';
            }
        }
    }

  private:
    bool quit;
    bool queue_exist;
    std::unique_ptr<CarriageDipatcher> dispatcher;
};