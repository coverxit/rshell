#ifndef __CMD_BINARY__
#define __CMD_BINARY__

class CmdBinary : public CmdBase
{
protected:
    CmdBase *leftCmd, *rightCmd;

public:
    CmdBinary() {}
    CmdBinary(CmdBase* leftCmd,
              CmdBase* rightCmd)
            : leftCmd(leftCmd), rightCmd(rightCmd)
    {}

    CmdBase *getLeftCmd() const { return leftCmd; }
    void setLeftCmd(CmdBase *cmd) { leftCmd = cmd; }

    CmdBase *getRightCmd() const { return rightCmd; }
    void setRightCmd(CmdBase *cmd) { rightCmd = cmd; }

    virtual int execute() = 0;
};

class CmdAnd : public CmdBinary
{
public:
    CmdAnd() {}
    CmdAnd(CmdBase* leftCmd,
           CmdBase* rightCmd)
            : CmdBinary(leftCmd, rightCmd)
    {}

    int execute()
    {
        int status = leftCmd->execute();
        if (status) return 0;
        return rightCmd->execute();
    }
};

class CmdOr : public CmdBinary
{
public:
    CmdOr() {}
    CmdOr(CmdBase* leftCmd,
          CmdBase* rightCmd)
            : CmdBinary(leftCmd, rightCmd)
    {}

    int execute()
    {
        int status = leftCmd->execute();
        if (!status) return 0;
        return rightCmd->execute();
    }
};

#endif
