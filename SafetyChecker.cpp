/**
 * @file SafetyChecker.cpp
 * @author Mushthofa
 * @date Tue 24 03 2009
 *
 * @brief Safety checker class
 *
 *
 */

#include "SafetyChecker.h"

SafetyChecker::SafetyChecker(const Atom& a)
        :atom(a)
{
        type = FACT;
}

SafetyChecker::SafetyChecker(const Rule& r)
        :rule(r)
{
        type = RULE;
}

bool SafetyChecker::checkSafe() const
{
        if(type == FACT)
        {
                if(atom.isGround())
                        return true;
                else
                        return false;
        }
        else if(type == RULE)
        {
                std::set<std::string> posvars, negvars;
                posvars = rule.getPosVariables();
                negvars = rule.getNegVariables();
                std::set<std::string>::iterator it;
                std::set<std::string> diff;
                std::set_difference(negvars.begin(), negvars.end(),
                                    posvars.begin(), posvars.end(),
                                    inserter(diff, diff.begin()));
                if(diff.size()>0)
                        return false;
                else
                        return true;
        }
        else
        {
                throw GeneralError("Safety checker called for unknown type object!");
        }
}

//End
