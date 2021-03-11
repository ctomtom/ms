package rule;
/* Rule class

  
    
 */

import java.util.*;
import java.io.*;
import java.awt.* ;

public class Rule {
  RuleBase rb ;
  String name ;
  Clause antecedents[] ;  // allow up to 3 antecedents for now
  Clause consequent ;     //only 1 consequent clause allowed
  Boolean truth;       // states = (null=unknown, true, or false)
  boolean fired=false;
  Rule(RuleBase Rb, String Name, Clause lhs, Clause rhs) {
    rb = Rb ;
    name = Name ;
    antecedents = new Clause[1] ;
    antecedents[0] = lhs ;
    lhs.addRuleRef(this) ;
    consequent = rhs ;
    rhs.addRuleRef(this) ;
    rhs.isConsequent() ;
    rb.ruleList.addElement(this) ;  // add self to rule list
    truth = null ;
  }
  Rule(RuleBase Rb, String Name, Clause lhss ) {
	    rb = Rb ;
	    name = Name ;
	    antecedents = new Clause[0] ;
	    antecedents[0] = lhss ;
	    lhss.addRuleRef(this) ;
	    
	    rb.ruleList.addElement(this) ;  // add self to rule list
	    truth = null ;
	  }
   
 Rule(RuleBase Rb, String Name, Clause lhs1, Clause lhs2, Clause rhs) {
    rb = Rb ;
    name = Name ;
    antecedents = new Clause[2] ;
    antecedents[0] = lhs1 ;
    lhs1.addRuleRef(this) ;
    antecedents[1] = lhs2 ;
    lhs2.addRuleRef(this) ;
    consequent = rhs ;
    rhs.addRuleRef(this) ;
    rhs.isConsequent() ;
    rb.ruleList.addElement(this) ;  // add self to rule list
    truth = null ;
  }
 Rule(RuleBase Rb, String Name, Clause lhs1, Clause lhs2,
                                Clause lhs3, Clause rhs) {
    rb = Rb ;
    name = Name ;
    antecedents = new Clause[3] ;
    antecedents[0] = lhs1 ;
    lhs1.addRuleRef(this) ;
    antecedents[1] = lhs2 ;
    lhs2.addRuleRef(this) ;
    antecedents[2] = lhs3 ;
    lhs3.addRuleRef(this) ;
    consequent = rhs ;
    rhs.addRuleRef(this) ;
    rhs.isConsequent() ;
    rb.ruleList.addElement(this) ;  // add self to rule list
    truth = null ;
  }
Rule(RuleBase Rb, String Name, Clause lhs1, Clause lhs2,
                               Clause lhs3, Clause lhs4,
                               Clause rhs) {
    rb = Rb ;
    name = Name ;
    antecedents = new Clause[4] ;
    antecedents[0] = lhs1 ;
    lhs1.addRuleRef(this) ;
    antecedents[1] = lhs2 ;
    lhs2.addRuleRef(this) ;
    antecedents[2] = lhs3 ;
    lhs3.addRuleRef(this) ;
    antecedents[3] = lhs4 ;
    lhs4.addRuleRef(this) ;
    consequent = rhs ;
    rhs.addRuleRef(this) ;
    rhs.isConsequent() ;
    rb.ruleList.addElement(this) ;  // add self to rule list
    truth = null ;
  }
Rule(RuleBase Rb, String Name, Clause lhs1, Clause lhs2,Clause lhs3, Clause lhs4,Clause lhs5, Clause rhs) {
rb = Rb ;
name = Name ;
antecedents = new Clause[5] ;
antecedents[0] = lhs1 ;
lhs1.addRuleRef(this) ;
antecedents[1] = lhs2 ;
lhs2.addRuleRef(this) ;
antecedents[2] = lhs3 ;
lhs3.addRuleRef(this) ;
antecedents[3] = lhs4 ;
lhs4.addRuleRef(this) ;
antecedents[4] = lhs5 ;
lhs5.addRuleRef(this) ;
consequent = rhs ;
rhs.addRuleRef(this) ;
rhs.isConsequent() ;
rb.ruleList.addElement(this) ;  // add self to rule list
truth = null ;
}
//////modif
Rule(RuleBase Rb, String Name, Clause lhs1, Clause lhs2,
        Clause lhs3, Clause lhs4,Clause lhs5, 
        Clause rhs12,Clause rhs) {
rb = Rb ;
name = Name ;
antecedents = new Clause[6] ;
antecedents[0] = lhs1 ;
lhs1.addRuleRef(this) ;
antecedents[1] = lhs2 ;
lhs2.addRuleRef(this) ;
antecedents[2] = lhs3 ;
lhs3.addRuleRef(this) ;
antecedents[3] = lhs4 ;
lhs4.addRuleRef(this) ;
antecedents[4] = lhs5 ;
lhs5.addRuleRef(this) ;
antecedents[5] = rhs12 ;
rhs12.addRuleRef(this) ;
consequent = rhs ;
rhs.addRuleRef(this) ;
rhs.isConsequent() ;
rb.ruleList.addElement(this) ;  // add self to rule list
truth = null ;
}

Rule(RuleBase Rb, String Name, Clause lhs1, Clause lhs2, Clause lhs3, Clause lhs4, Clause lhs5, Clause lhs6, Clause lhs7, Clause lhs8, Clause lhs9, Clause lhs10, Clause lhs11, Clause lhs12, Clause lhs13, Clause rhs) {
    rb = Rb ;
    name = Name ;
    antecedents = new Clause[13] ;
    antecedents[0] = lhs1 ;
    lhs1.addRuleRef(this) ;
    antecedents[1] = lhs2 ;
    lhs2.addRuleRef(this) ;
    ////
    antecedents[2] = lhs3 ;
    lhs3.addRuleRef(this) ;
    antecedents[3] = lhs4 ;
    lhs4.addRuleRef(this) ;
    antecedents[4] = lhs5 ;
    lhs5.addRuleRef(this) ;
    antecedents[5] = lhs6 ;
    lhs6.addRuleRef(this) ;
    antecedents[6] = lhs7 ;
    lhs7.addRuleRef(this) ;
    antecedents[7] = lhs8 ;
    lhs8.addRuleRef(this) ;
    antecedents[8] = lhs9 ;
    lhs9.addRuleRef(this) ;
    antecedents[9] = lhs10 ;
    lhs10.addRuleRef(this) ;
    antecedents[10] = lhs11 ;
    lhs11.addRuleRef(this) ;

    antecedents[11] = lhs12 ;
    lhs12.addRuleRef(this) ;
    antecedents[12] = lhs13 ;
    lhs13.addRuleRef(this) ;

    ///
    consequent = rhs ;
    rhs.addRuleRef(this) ;
    rhs.isConsequent() ;
    rb.ruleList.addElement(this) ;  // add self to rule list
    truth = null ;
  }

Rule(RuleBase Rb, String Name, Clause lhs1, Clause lhs2, Clause lhs3, Clause lhs4, Clause lhs5, Clause lhs6, Clause lhs7, Clause lhs8, Clause lhs9, Clause lhs10, Clause lhs11, Clause lhs12,Clause rhs) {
    rb = Rb ;
    name = Name ;
    antecedents = new Clause[12] ;
    antecedents[0] = lhs1 ;
    lhs1.addRuleRef(this) ;
    antecedents[1] = lhs2 ;
    lhs2.addRuleRef(this) ;
    ////
    antecedents[2] = lhs3 ;
    lhs3.addRuleRef(this) ;
    antecedents[3] = lhs4 ;
    lhs4.addRuleRef(this) ;
    antecedents[4] = lhs5 ;
    lhs5.addRuleRef(this) ;
    antecedents[5] = lhs6 ;
    lhs6.addRuleRef(this) ;
    antecedents[6] = lhs7 ;
    lhs7.addRuleRef(this) ;
    antecedents[7] = lhs8 ;
    lhs8.addRuleRef(this) ;
    antecedents[8] = lhs9 ;
    lhs9.addRuleRef(this) ;
    antecedents[9] = lhs10 ;
    lhs10.addRuleRef(this) ;
    antecedents[10] = lhs11 ;
    lhs11.addRuleRef(this) ;

    antecedents[11] = lhs12 ;
    lhs12.addRuleRef(this) ;


    ///
    consequent = rhs ;
    rhs.addRuleRef(this) ;
    rhs.isConsequent() ;
    rb.ruleList.addElement(this) ;  // add self to rule list
    truth = null ;
  }

//////


  long numAntecedents() { return antecedents.length; }

     public static void checkRules(Vector clauseRefs) {
   Enumeration enum87 = clauseRefs.elements();
  while(enum87.hasMoreElements()) {
    Clause temp = (Clause)enum87.nextElement();
    Enumeration enum2 = temp.ruleRefs.elements() ;
    while(enum2.hasMoreElements()) {
        ((Rule)enum2.nextElement()).check() ; // retest the rule
    }
  }
}

   // used by forward chaining only !
  Boolean check() {  // if antecedent is true and rule has not fired
   RuleBase.appendText("\nTesting rule " + name ) ;
   for (int i=0 ; i < antecedents.length ; i++ ) {
    if (antecedents[i].truth == null) return null ;
    if (antecedents[i].truth.booleanValue() == true) {
        continue ;
    } else {
        return truth = new Boolean(false) ; //don't fire this rule
    }
   } // endfor
   return truth = new Boolean(true) ;  // could fire this rule
  }

  // used by forward chaining only !
  // fire this rule -- perform the consequent clause
  // if a variable is changes, update all clauses where
  //  it is references, and then all rules which contain
  //  those clauses
  void fire() {
    RuleBase.appendText("\nFiring rule " + name ) ;
    truth = new Boolean(true) ;
    fired = true ;
    // set the variable value and update clauses
    consequent.lhs.setValue(consequent.rhs) ;
    // now retest any rules whose clauses just changed
    checkRules(consequent.lhs.clauseRefs) ;
  }

  // determine is a rule is true or false
  // by recursively trying to prove its antecedent clauses are true
  // if any are false, the rule is false
  Boolean backChain()
  {
    RuleBase.appendText("\nEvaluating rule " + name) ;
    for (int i=0 ; i < antecedents.length ; i++) { // test each clause
     if (antecedents[i].truth == null) rb.backwardChain(antecedents[i].lhs.name);
     if (antecedents[i].truth == null) { // we couldn't prove true or false
         antecedents[i].lhs.askUser() ; // so ask user for help
         truth = antecedents[i].check() ; // redundant?
     } // endif
     if (antecedents[i].truth.booleanValue() == true) {
         continue ;    // test the next antecedent (if any)
     } else {
         return truth = new Boolean(false) ; // exit, if any are false
     }
    } // endfor
    return truth = new Boolean(true) ; // all antecedents are true
  }

  // display the rule in text format
  @SuppressWarnings("deprecation")
void display(TextArea textArea) {
    textArea.appendText(name +": IF ") ;
    for(int i=0 ; i < antecedents.length ; i++) {
      Clause nextClause = antecedents[i] ;
      textArea.appendText(nextClause.lhs.name +
                          nextClause.cond.asString() +
                          nextClause.rhs + " ") ;
      if ((i+1) < antecedents.length) textArea.appendText("\n     AND ") ;
    }
    textArea.appendText("\n     THEN ") ;
       textArea.appendText(consequent.lhs.name +
                          consequent.cond.asString() +
                          consequent.rhs + "\n") ;
  }
};






