/**
 * @file Rule.h
 * @author Roman Schindlauer, Mushthofa
 *
 * @brief Rule class.
 *
 */


#ifndef _RULE_H
#define _RULE_H

#include <boost/ptr_container/indirect_fun.hpp>
#include <sstream>
#include <cmath>
#include "Literal.h"
#include "Globals.h"

typedef std::vector<AtomPtr > HeadList_t;
typedef std::vector<LiteralPtr> BodyList_t;
typedef enum {TNORM, CO_TNORM, MAX, MIN} FuzzyOp_t;

typedef std::pair<HeadList_t, FuzzyOp_t> HeadExpr_t;
typedef std::pair<BodyList_t, FuzzyOp_t> BodyExpr_t;

class Rule
{
        public:
                Rule():lineid(0){}
                Rule(const HeadExpr_t&, const BodyExpr_t&,
                        const std::string& = "",
                        unsigned = 0, bool noVars=false);
                virtual ~Rule();

                virtual const HeadExpr_t& getHead() const;
                virtual const BodyExpr_t& getBody() const;
                virtual const BodyExpr_t getPositiveBody() const;
                virtual const BodyExpr_t getNegativeBody() const;

                virtual void setHead(const HeadExpr_t&);
                virtual void setBody(const BodyExpr_t&);

                virtual void addHead(AtomPtr);
                virtual void addBody(LiteralPtr);

                std::set<std::string> getVariables() const;
                std::set<std::string> getPosVariables() const;
                std::set<std::string> getNegVariables() const;
                unsigned numberOfVars() const;

                bool isGround() const;

                Rule bindVariables(const std::vector<std::string>&);

                std::string getFile() const;
                unsigned getLine() const;

                bool operator==(const Rule&) const;
                bool operator!=(const Rule&) const;
                bool operator<(const Rule&) const;
                bool operator>(const Rule& r2) const
                {
                        return !(*this<r2 || *this==r2);
                }

                //virtual void accept(BaseVisitor&) const;

                bool isDefinite()
                {
                        if(head.first.size() != 1)
                                return false;
                        BodyList_t::iterator b_it;

                        for(b_it = body.first.begin(); b_it!=body.first.end(); ++b_it)
                        {
                                if((*b_it)->isNAF())
                                        return false;
                        }
                        return true;
                }

                bool isSmallConstraint(unsigned long maxGr) const
                {
                        if(head.first.size() == 0 && isSmall(maxGr))
                                return true;
                        return false;
                }

                bool isSmall(unsigned long maxGr) const
                {
                        int minRuleVar = Globals::Instance()->intOption("minRuleVar");
                        if(posVars.size() <= minRuleVar)
                                return true;
                        unsigned long numConstants = Atom::constantsTable.size();
                        double cv = (double)log(maxGr)/ (double)log(posVars.size());
                        //std::cout << "cv " << cv <<std::endl;
                        if(numConstants < cv)
                                return true;
                        return false;
                }

                bool isFact() const
                {
                	HeadList_t hl = head.first;
                	BodyList_t bl = body.first;
                	return (hl.size() == 1 && bl.size() == 1
                			&& typeid(*bl[0]->getAtom()) == typeid(ConstantAtom));
                }


        protected:
                HeadExpr_t head;
                BodyExpr_t body;
                std::string filename;
                unsigned lineid;
                std::set<std::string> posVars;
};

std::ostream& operator<<(std::ostream&, const Rule&);

bool operator< (const HeadExpr_t& head1, const HeadExpr_t& head2);
bool operator< (const BodyExpr_t& b1, const BodyExpr_t& b2);




#endif

//End

