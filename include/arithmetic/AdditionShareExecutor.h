//
// Created by 杜建璋 on 2024/7/6.
//

#ifndef MPC_PACKAGE_ADDITIONSHAREEXECUTOR_H
#define MPC_PACKAGE_ADDITIONSHAREEXECUTOR_H


class AdditionShareExecutor {
protected:
    // joined party number
    int mpiSize{};
    // mpiRank of current device
    int mpiRank{};
    // holding param
    int x{};

    // saved part (a random int)
    int x1{};
    // left part = x - x1
    int x2{};
    // received number (part of the other's holding)
    int y2{};
    // temp result (part sum)
    int temp{};
    // received temp result (from the other)
    int recvTemp{};
protected:
    // must define how to obtain holding param
    virtual void obtainX() = 0;
    // define how to generate saved part of x
    virtual void generateSaved();

public:
    void init(int argc, char** argv);
    int result() const;
private:
    // called in init
    void initMpcEnv(int argc, char **argv);
    // exchange part
    void exchangePart();
    // calculate temp result
    void calculateTemp();
    // exchange temp result
    void exchangeTemp();
};


#endif //MPC_PACKAGE_ADDITIONSHAREEXECUTOR_H
