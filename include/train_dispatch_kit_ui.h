#include "carriage_dispatcher.h"

class TrainDispatchKitUI {
  public:
    TrainDispatchKitUI();

    ~TrainDispatchKitUI();

    void OperationLoop();

    void StartScreen();

    void ExecuteCommand(std::string cmd);

    void CreateQueue();

    void GetBufferNum();

    void ContinueForSteps();

    void NextStep();

    void CheckBuffer();

  private:
    bool quit;
    bool queue_exist;
    std::unique_ptr<XXYY::CarriageDipatcher> dispatcher;
};