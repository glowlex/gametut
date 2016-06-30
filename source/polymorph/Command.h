
class Command {
  public:
  	Command() {}
  	virtual ~Command() {}
    virtual int execute() = 0;
};
