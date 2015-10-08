namespace robot{
  class robotCommunicator{
    int baudRate;

    void setupCommunication();
    void read();
    void write();
    void onOffSensors(bool estado);
  };
}
