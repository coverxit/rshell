#ifndef __CMD_UNARY__
#define __CMD_UNARY__

//! The class for single (unary) command.
class CmdUnary : public CmdBase
{
    typedef std::vector<std::string> ArgVector;

private:
    std::string executable;
    ArgVector argList;
    Executor* executor;

public:
    CmdUnary() : executor(NULL) {}
    /**
     * @brief Construct a single command by a vector generated by CmdParser
     *        with a given Executor.
     *
     * Note that @c rawCmd is required to be at least 1 element.
     *
     * @param rawCmd The vector from CmdParser.
     * @param executor The Executor used in @c execute().
     */
    CmdUnary(std::vector<std::string> rawCmd,
             Executor* executor = NULL)
            : executor(executor)
    {
        executable = rawCmd.at(0);
        argList = std::vector<string>(rawCmd.begin() + 1, rawCmd.end());
    }

    /**
     * @brief Construct a single command by given executable, argument list
     *        and Executor.
     * @param executable The executable's path or filename.
     * @param argList The argument list.
     * @param executor The Executor used in @c execute().
     * @return
     */
    CmdUnary(std::string executable,
             std::vector<std::string> argList,
             Executor* executor = NULL)
            : executable(executable), argList(argList), executor(executor)
    {}

    std::string getExecutable() const { return executable; }
    void setExecutable(std::string exec) { this->executable = exec; }

    ArgVector getArgumentList() const { return this->argList; }
    void setArgumentList(ArgVector argList) { this->argList = argList; }

    Executor* getExecutor() const { return executor; }
    void setExecutor(Executor* executor) { this->executor = executor; }

    int execute() 
    {
        // execvp() requires the executable as the first element of arguments,
        // and NULL as the last element in argument list, so we need to
        // construct a new argument list for the executor.
        std::vector<char*> args;
        args.push_back((char*) executable.c_str());
        for (unsigned int i = 0; i < argList.size(); i++)
            args.push_back((char*) argList[i].c_str());
        args.push_back(NULL);

        return executor->execute(executable, args);
    }

    std::string toString()
    {
        std::string ret = executable;
        for (unsigned int i = 0; i < argList.size(); i++)
            ret += " " + argList[i];
        return ret;
    }
};

#endif
