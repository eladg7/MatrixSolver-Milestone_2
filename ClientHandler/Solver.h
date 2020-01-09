#ifndef MILESTONE_2_SOLVER_H
#define MILESTONE_2_SOLVER_H

template<typename P, typename S>
class Solver {
public:
    virtual S solve(P problem) = 0;

};

#endif //MILESTONE_2_SOLVER_H
