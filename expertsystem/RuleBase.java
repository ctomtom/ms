package rule;

/* RuleBase class

 

*/

import java.util.*;
import java.io.*;
import java.awt.* ;

public class RuleBase {

 String name ;
 Hashtable variableList ;    // all variables in the rulebase
 Clause clauseVarList[];
 Vector ruleList ;           // list of all rules
 Vector conclusionVarList ;  // queue of variables
 Rule rulePtr ;              // working pointer to current rule
 Clause clausePtr ;          // working pointer to current clause
 Stack goalClauseStack;      // for goals (cons clauses) and subgoals

 static TextArea textArea1 ;
 public void setDisplay(TextArea txtArea) { textArea1 = txtArea; }

 RuleBase(String Name) { name = Name; }
 public static void appendText(String text) { textArea1.appendText(text); }

 // for trace purposes - display all variables and their value
 @SuppressWarnings("deprecation")
public void displayVariables(TextArea textArea) {

   Enumeration enum87 = variableList.elements() ;
   while(enum87.hasMoreElements()) {
     RuleVariable temp = (RuleVariable)enum87.nextElement() ;
     textArea.appendText("\n" + temp.name + " value = " + temp.value) ;
   }
 }

// for trace purposes - display all rules in text format
 @SuppressWarnings("deprecation")
public void displayRules(TextArea textArea) {
   textArea.appendText("\n" + name + " Rule Base: " + "\n");
   Enumeration enum87 = ruleList.elements() ;
   while(enum87.hasMoreElements()) {
     Rule temp = (Rule)enum87.nextElement() ;
     temp.display(textArea) ;
   }
 }

 public String getName() {
	return name;
}

public void setName(String name) {
	this.name = name;
}

public Hashtable getVariableList() {
	return variableList;
}

public void setVariableList(Hashtable variableList) {
	this.variableList = variableList;
}

public Clause[] getClauseVarList() {
	return clauseVarList;
}

public void setClauseVarList(Clause[] clauseVarList) {
	this.clauseVarList = clauseVarList;
}

public Vector getRuleList() {
	return ruleList;
}

public void setRuleList(Vector ruleList) {
	this.ruleList = ruleList;
}

public Vector getConclusionVarList() {
	return conclusionVarList;
}

public void setConclusionVarList(Vector conclusionVarList) {
	this.conclusionVarList = conclusionVarList;
}

public Rule getRulePtr() {
	return rulePtr;
}

public void setRulePtr(Rule rulePtr) {
	this.rulePtr = rulePtr;
}

public Clause getClausePtr() {
	return clausePtr;
}

public void setClausePtr(Clause clausePtr) {
	this.clausePtr = clausePtr;
}

public Stack getGoalClauseStack() {
	return goalClauseStack;
}

public void setGoalClauseStack(Stack goalClauseStack) {
	this.goalClauseStack = goalClauseStack;
}

public static TextArea getTextArea1() {
	return textArea1;
}

public static void setTextArea1(TextArea textArea1) {
	RuleBase.textArea1 = textArea1;
}

// for trace purposes - display all rules in the conflict set
 @SuppressWarnings("deprecation")
public void displayConflictSet(Vector ruleSet) {
   textArea1.appendText("\n" + " -- Rules in conflict set:\n");
   Enumeration enum87 = ruleSet.elements() ;
   while(enum87.hasMoreElements()) {
     Rule temp = (Rule)enum87.nextElement() ;
     textArea1.appendText(temp.name + "(" + temp.numAntecedents()+ "), " ) ;
   }
 }


 // reset the rule base for another round of inferencing
 // by setting all variable values to null
 @SuppressWarnings("deprecation")
public void reset() {
   textArea1.appendText("\n --- Setting all " + name + " variables to null");
   Enumeration enum87 = variableList.elements() ;
   while(enum87.hasMoreElements()) {
     RuleVariable temp = (RuleVariable)enum87.nextElement() ;
     temp.setValue(null) ;
   }
 }

  // for all consequent clauses which refer to this goalVar
  // try to find goalVar value via a rule being true
  //     if rule is true then pop, assign value, re-eval rule
  //     if rule is false then pop, continue
  //     if rule is null then we couldnt find a value (same as false?)
  //
 @SuppressWarnings("deprecation")
public void backwardChain(String goalVarName)
 {

  RuleVariable goalVar = (RuleVariable)variableList.get(goalVarName);
  Enumeration goalClauses = goalVar.clauseRefs.elements() ;

  while (goalClauses.hasMoreElements()) {
     Clause goalClause = (Clause)goalClauses.nextElement() ;
     if (goalClause.consequent.booleanValue() == false) continue ;

     goalClauseStack.push(goalClause) ;

     Rule goalRule = goalClause.getRule();
     Boolean ruleTruth = goalRule.backChain() ; // find rule truth value
     if (ruleTruth == null) {
        textArea1.appendText("\nRule " + goalRule.name +
                             " is null, can't determine truth value.");
      } else if (ruleTruth.booleanValue() == true) {
       // rule is OK, assign consequent value to variable
       goalVar.setValue(goalClause.rhs) ;
       goalVar.setRuleName(goalRule.name) ;
       goalClauseStack.pop() ;  // clear item from subgoal stack
       textArea1.appendText("\nRule " + goalRule.name + " is true, setting " + goalVar.name + ": = " + goalVar.value);
       if (goalClauseStack.empty() == true) {
         textArea1.appendText("\n +++ Found Solution for goal: " + goalVar.name);
         break ; // for now, only find first solution, then stop
       }
     } else {
       goalClauseStack.pop() ; // clear item from subgoal stack
       textArea1.appendText("\nRule " + goalRule.name + " is false, can't set " + goalVar.name);
     }

     // displayVariables("Backward Chaining") ;  // display variable bindings
   } // endwhile

   if (goalVar.value == null) {
      textArea1.appendText("\n +++ Could Not Find Solution for goal: " + goalVar.name);
   }
 }

 // used for forward chaining only
 // determine which rules can fire, return a Vector
 public Vector match(boolean test) {
    Vector matchList = new Vector() ;
    Enumeration enum87 = ruleList.elements() ;
    while (enum87.hasMoreElements()) {
        Rule testRule = (Rule)enum87.nextElement() ;
        if (test) testRule.check() ; // test the rule antecedents
        if (testRule.truth == null) continue ;
        // fire the rule only once for now
        if ((testRule.truth.booleanValue() == true) &&
            (testRule.fired == false)) matchList.addElement(testRule) ;
    }
    displayConflictSet(matchList) ;
    return matchList ;
 }

 // used for forward chaining only
 // select a rule to fire based on specificity
 public Rule selectRule(Vector ruleSet) {
    Enumeration enum87 = ruleSet.elements() ;
    long numClauses ;
    Rule nextRule ;

    Rule bestRule = (Rule)enum87.nextElement() ;
    long max = bestRule.numAntecedents() ;
    while (enum87.hasMoreElements()) {
        nextRule = (Rule)enum87.nextElement() ;
        if ((numClauses = nextRule.numAntecedents()) > max) {
            max = numClauses ;
            bestRule = nextRule ;
        }
    }
    System.out.print(bestRule.consequent.rhs);
    return bestRule ;
    
 }

 public void forwardChain() {
    Vector conflictRuleSet = new Vector() ;

    // first test all rules, based on initial data
    conflictRuleSet = match(true); // see which rules can fire

    while(conflictRuleSet.size() > 0) {

      Rule selected = selectRule(conflictRuleSet); // select the "best" rule
      selected.fire() ; // fire the rule
                        // do the consequent action/assignment
                        // update all clauses and rules

      conflictRuleSet = match(false); // see which rules can fire

    // displayVariables("Forward Chaining") ; // display variable bindings
    }
 }


}










