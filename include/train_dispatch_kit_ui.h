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

    void ContinueUntilFinish();

    void NextStep();

    void CheckBuffer();

  private:
    bool quit_;
    bool queue_exist_;
    int m_steps_;
    std::unique_ptr<XXYY::CarriageDipatcher> dispatcher_;
};